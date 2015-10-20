/*
 * Copyright (C) 1996-2001, The University of Queensland
 *
 * See the file "LICENSE.TERMS" for information on usage and
 * redistribution of this file, and for a DISCLAIMER OF ALL
 * WARRANTIES.
 *
 */

/*==============================================================================
 * FILE:	   decoder.m
 * OVERVIEW:   Implementation of the SPARC specific parts of the
 *			   SparcDecoder class.
 *============================================================================*/

/* $Revision: 1.24 $	
 *
 * 26 Apr 02 - Mike: Mods for boomerang
 * 19 May 02 - Mike: Added many (int) casts: variables from toolkit are unsgnd
 * 21 May 02 - Mike: SAVE and RESTORE have full semantics now
 * 30 Oct 02 - Mike: dis_Eaddr mode indirectA had extra memof
 * 22 Nov 02 - Mike: Support 32 bit V9 branches
 * 04 Dec 02 - Mike: r[0] -> 0 automatically (rhs only)
 * 30 May 02 - Mike: Also fixed r[0] -> 0 for store instructions
 * 03 Nov 04 - Mike: DIS_FDS was returning numbers for the double precision registers
*/

/*==============================================================================
 * Dependencies.
 *============================================================================*/

#include <assert.h>
#include <cstring>
#if defined(_MSC_VER) && _MSC_VER <= 1100
#include "signature.h"
#endif

#include "decoder.h"
#include "exp.h"
#include "prog.h"
#include "proc.h"
#include "sparcdecoder.h"
#include "rtl.h"
#include "BinaryFile.h"		
#include "boomerang.h"

#define DIS_ROI		(dis_RegImm(roi))
#define DIS_ADDR	(dis_Eaddr(addr))
#define DIS_RD		(dis_RegLhs(rd))
#define DIS_RDR		(dis_RegRhs(rd))
#define DIS_RS1		(dis_RegRhs(rs1))
#define DIS_FS1S	(dis_RegRhs(fs1s+32))
#define DIS_FS2S	(dis_RegRhs(fs2s+32))


#define DIS_FDS		(dis_RegLhs(fds+32))
#define DIS_FS1D	(dis_RegRhs((fs1d>>1)+64))
#define DIS_FS2D	(dis_RegRhs((fs2d>>1)+64))
#define DIS_FDD		(dis_RegLhs((fdd>>1)+64))
#define DIS_FDQ		(dis_RegLhs((fdq>>2)+80))
#define DIS_FS1Q	(dis_RegRhs((fs1q>>2)+80))
#define DIS_FS2Q	(dis_RegRhs((fs2q>>2)+80))

/*==============================================================================
 * FUNCTION:	   unused
 * OVERVIEW:	   A dummy function to suppress "unused local variable" messages
 * PARAMETERS:	   x: integer variable to be "used"
 * RETURNS:		   Nothing
 *============================================================================*/
void SparcDecoder::unused(int x)
{
}
/*==============================================================================
 * FUNCTION:	   createBranchRtl
 * OVERVIEW:	   Create an RTL for a Bx instruction
 * PARAMETERS:	   pc - the location counter
 *				   stmts - ptr to list of Statement pointers
 *				   name - instruction name (e.g. "BNE,a", or "BPNE")
 * RETURNS:		   Pointer to newly created RTL, or NULL if invalid
 *============================================================================*/
static DecodeResult result;
RTL* SparcDecoder::createBranchRtl(ADDRESS pc,std::list<Statement*>* stmts,const char* name)
{
	RTL* res = new RTL(pc, stmts);
	BranchStatement* br = new BranchStatement();
	res->appendStmt(br);
	if(name[0] == 'F')
	{
		if(name[2] == 'U')
		name++;
		switch(name[2])
		{
			case 'E':
			br->setCondType(BRANCH_JE, true);
			break;
			case 'L':
			if(name[3] == 'G')
			br->setCondType(BRANCH_JNE, true);
			if(name[3] == 'E')
			br->setCondType(BRANCH_JSLE, true);
			br->setCondType(BRANCH_JSL, true);
			break;
			case 'G':
			if(name[3] == 'E')
			br->setCondType(BRANCH_JSGE, true);
			br->setCondType(BRANCH_JSG, true);
			break;
			case 'N':
			if(name[3] == 'E')
			br->setCondType(BRANCH_JNE, true);
			break;
			default:
			std::cerr << "unknown float branch " << name << std::endl;
			delete res;
			res = NULL;
		}
		return res;
	}
	switch(name[1])
	{
		case 'E':
		br->setCondType(BRANCH_JE);
		break;
		case 'L':
		if(name[2] == 'E')
		{
			if(name[3] == 'U')
			br->setCondType(BRANCH_JULE);
			br->setCondType(BRANCH_JSLE);
		}
		br->setCondType(BRANCH_JSL);
		break;
		case 'N':
		if(name[3] == 'G')
		br->setCondType(BRANCH_JMI);
		br->setCondType(BRANCH_JNE);
		break;
		case 'C':
		if(name[2] == 'C')
		br->setCondType(BRANCH_JUGE);
		br->setCondType(BRANCH_JUL);
		break;
		case 'V':
		if(name[2] == 'C')
		std::cerr << "Decoded BVC instruction\n";
		std::cerr << "Decoded BVS instruction\n";
		break;
		case 'G':
		if(name[2] == 'E')
		br->setCondType(BRANCH_JSGE);
		if(name[2] == 'U')
		br->setCondType(BRANCH_JUG);
		br->setCondType(BRANCH_JSG);
		break;
		case 'P':
		if(name[2] == 'O')
		{
			br->setCondType(BRANCH_JPOS);
			break;
		}
		char temp[8];
		temp[0] = 'B';
		strcpy(temp+1, name+2);
		delete res;
		return createBranchRtl(pc, stmts, temp);
		default:
		std::cerr << "unknown non-float branch " << name << std::endl;
	}
	return res;
}
/*==============================================================================
 * FUNCTION:	   SparcDecoder::decodeInstruction
 * OVERVIEW:	   Attempt to decode the high level instruction at a given address and return the corresponding HL type
 *					(e.g. CallStatement, GotoStatement etc). If no high level instruction exists at the given address,
 *					then simply return the RTL for the low level instruction at this address. There is an option to also
 *				   include the low level statements for a HL instruction.
 * PARAMETERS:	   pc - the native address of the pc
 *				   delta - the difference between the above address and the host address of the pc (i.e. the address
 *					that the pc is at in the loaded object file)
 *				   proc - the enclosing procedure. This can be NULL for those of us who are using this method in an
 *					interpreter
 * RETURNS:		   a DecodeResult structure containing all the information gathered during decoding
 *============================================================================*/
DecodeResult& SparcDecoder::decodeInstruction(ADDRESS pc,int delta)
{
	static DecodeResult result;
	ADDRESS hostPC = pc+delta;
	result.reset();
	std::list<Statement*>* stmts = NULL;
	ADDRESS nextPC = NO_ADDRESS;
	//ADDRESS nextPC = NO_ADDRESS;
	dword MATCH_p = hostPC;
	if (lines(0) == call__ ) {
		addr = magic_process(addr);
	}
	if (lines(0) == call_ ) {
		addr = magic_process(addr);
	}
	if (lines(0) == ret ) {
	}
	if (lines(0) == retl ) {
	}
	if (lines(0) == branch^",a" ) {
		tgt = magic_process(tgt);
	}
	if (lines(0) == pbranch^",a" ) {
		cc01 = magic_process(cc01);
		tgt = magic_process(tgt);
	}
	if (lines(0) == branch ) {
		tgt = magic_process(tgt);
	}
	if (lines(0) == BPA ) {
		cc01 = magic_process(cc01);
		tgt = magic_process(tgt);
	}
	if (lines(0) == pbranch ) {
		cc01 = magic_process(cc01);
		tgt = magic_process(tgt);
	}
	if (lines(0) == JMPL ) {
		addr = magic_process(addr);
		rd = magic_process(rd);
	}
	if (lines(0) == SAVE ) {
		rs1 = magic_process(rs1);
		roi = magic_process(roi);
		rd = magic_process(rd);
	}
	if (lines(0) == RESTORE ) {
		rs1 = magic_process(rs1);
		roi = magic_process(roi);
		rd = magic_process(rd);
	}
	if (lines(0) == sethi ) {
		imm22 = magic_process(imm22);
		rd = magic_process(rd);
	}
	if (lines(0) == load_greg ) {
		addr = magic_process(addr);
		rd = magic_process(rd);
	}
	if (lines(0) == LDF ) {
		addr = magic_process(addr);
		fds = magic_process(fds);
	}
	if (lines(0) == LDDF ) {
		addr = magic_process(addr);
		fdd = magic_process(fdd);
	}
	if (lines(0) == load_asi ) {
		addr = magic_process(addr);
		asi = magic_process(asi);
		rd = magic_process(rd);
	}
	if (lines(0) == sto_greg ) {
		rd = magic_process(rd);
		addr = magic_process(addr);
	}
	if (lines(0) == STF ) {
		fds = magic_process(fds);
		addr = magic_process(addr);
	}
	if (lines(0) == STDF ) {
		fdd = magic_process(fdd);
		addr = magic_process(addr);
	}
	if (lines(0) == sto_asi ) {
		rd = magic_process(rd);
		addr = magic_process(addr);
		asi = magic_process(asi);
	}
	if (lines(0) == LDFSR ) {
		addr = magic_process(addr);
	}
	if (lines(0) == LDCSR ) {
		addr = magic_process(addr);
	}
	if (lines(0) == STFSR ) {
		addr = magic_process(addr);
	}
	if (lines(0) == STCSR ) {
		addr = magic_process(addr);
	}
	if (lines(0) == STDFQ ) {
		addr = magic_process(addr);
	}
	if (lines(0) == STDCQ ) {
		addr = magic_process(addr);
	}
	if (lines(0) == RDY ) {
		rd = magic_process(rd);
	}
	if (lines(0) == RDPSR ) {
		rd = magic_process(rd);
	}
	if (lines(0) == RDWIM ) {
		rd = magic_process(rd);
	}
	if (lines(0) == RDTBR ) {
		rd = magic_process(rd);
	}
	if (lines(0) == WRY ) {
		rs1 = magic_process(rs1);
		roi = magic_process(roi);
	}
	if (lines(0) == WRPSR ) {
		rs1 = magic_process(rs1);
		roi = magic_process(roi);
	}
	if (lines(0) == WRWIM ) {
		rs1 = magic_process(rs1);
		roi = magic_process(roi);
	}
	if (lines(0) == WRTBR ) {
		rs1 = magic_process(rs1);
		roi = magic_process(roi);
	}
	if (lines(0) == alu ) {
		rs1 = magic_process(rs1);
		roi = magic_process(roi);
		rd = magic_process(rd);
	}
	if (lines(0) == float2s ) {
		fs2s = magic_process(fs2s);
		fds = magic_process(fds);
	}
	if (lines(0) == float3s ) {
		fs1s = magic_process(fs1s);
		fs2s = magic_process(fs2s);
		fds = magic_process(fds);
	}
	if (lines(0) == float3d ) {
		fs1d = magic_process(fs1d);
		fs2d = magic_process(fs2d);
		fdd = magic_process(fdd);
	}
	if (lines(0) == float3q ) {
		fs1q = magic_process(fs1q);
		fs2q = magic_process(fs2q);
		fdq = magic_process(fdq);
	}
	if (lines(0) == fcompares ) {
		fs1s = magic_process(fs1s);
		fs2s = magic_process(fs2s);
	}
	if (lines(0) == fcompared ) {
		fs1d = magic_process(fs1d);
		fs2d = magic_process(fs2d);
	}
	if (lines(0) == fcompareq ) {
		fs1q = magic_process(fs1q);
		fs2q = magic_process(fs2q);
	}
	if (lines(0) == FTOs ) {
		fs2s = magic_process(fs2s);
		fds = magic_process(fds);
	}
	if (lines(0) == FiTOd ) {
		fs2s = magic_process(fs2s);
		fdd = magic_process(fdd);
	}
	if (lines(0) == FdTOi ) {
		fs2d = magic_process(fs2d);
		fds = magic_process(fds);
	}
	if (lines(0) == FiTOq ) {
		fs2s = magic_process(fs2s);
		fdq = magic_process(fdq);
	}
	if (lines(0) == FqTOi ) {
		fs2q = magic_process(fs2q);
		fds = magic_process(fds);
	}
	if (lines(0) == FsTOd ) {
		fs2s = magic_process(fs2s);
		fdd = magic_process(fdd);
	}
	if (lines(0) == FdTOs ) {
		fs2d = magic_process(fs2d);
		fds = magic_process(fds);
	}
	if (lines(0) == FsTOq ) {
		fs2s = magic_process(fs2s);
		fdq = magic_process(fdq);
	}
	if (lines(0) == FqTOs ) {
		fs2q = magic_process(fs2q);
		fds = magic_process(fds);
	}
	if (lines(0) == FdTOq ) {
		fs2d = magic_process(fs2d);
		fdq = magic_process(fdq);
	}
	if (lines(0) == FqTOd ) {
		fs2q = magic_process(fs2q);
		fdd = magic_process(fdd);
	}
	if (lines(0) == FSQRTd ) {
		fs2d = magic_process(fs2d);
		fdd = magic_process(fdd);
	}
	if (lines(0) == FSQRTq ) {
		fs2q = magic_process(fs2q);
		fdq = magic_process(fdq);
	}
	if (lines(0) == RETURN ) {
		addr = magic_process(addr);
	}
	if (lines(0) == trap ) {
		addr = magic_process(addr);
	}
	if (lines(0) == UNIMP ) {
		n = magic_process(n);
	}
	result.numBytes = nextPC - hostPC;
	if(result.valid && result.rtl == 0)
	result.rtl = new RTL(pc, stmts);
	return result;
}
/***********************************************************************
 * These are functions used to decode instruction operands into
 * expressions (Exp*s).
 **********************************************************************/

/*==============================================================================
 * FUNCTION:		SparcDecoder::dis_RegLhs
 * OVERVIEW:		Decode the register on the LHS
 * PARAMETERS:		r - register (0-31)
 * RETURNS:			the expression representing the register
 *============================================================================*/
Exp* SparcDecoder::dis_RegLhs(unsigned r)
{
	return Location::regOf(r);
}
/*==============================================================================
 * FUNCTION:		SparcDecoder::dis_RegRhs
 * OVERVIEW:		Decode the register on the RHS
 * NOTE:			Replaces r[0] with const 0
 * NOTE:			Not used by DIS_RD since don't want 0 on LHS
 * PARAMETERS:		r - register (0-31)
 * RETURNS:			the expression representing the register
 *============================================================================*/
Exp* SparcDecoder::dis_RegRhs(unsigned r)
{
	if(r == 0)
	return new Const(0);
	return Location::regOf(r);
}
/*==============================================================================
 * FUNCTION:		SparcDecoder::dis_RegImm
 * OVERVIEW:		Decode the register or immediate at the given address.
 * NOTE:			Used via macro DIS_ROI
 * PARAMETERS:		pc - an address in the instruction stream
 * RETURNS:			the register or immediate at the given address
 *============================================================================*/
Exp* SparcDecoder::dis_RegImm(unsigned pc)
{
	dword MATCH_p = pc;
	if (lines(0) == imode ) {
		i = magic_process(i);
	}
	if (lines(0) == rmode ) {
		rs2 = magic_process(rs2);
	}
}
/*==============================================================================
 * FUNCTION:		SparcDecoder::dis_Eaddr
 * OVERVIEW:		Converts a dynamic address to a Exp* expression.
 *					E.g. %o7 --> r[ 15 ]
 * PARAMETERS:		pc - the instruction stream address of the dynamic address
 *					ignore - redundant parameter on SPARC
 * RETURNS:			the Exp* representation of the given address
 *============================================================================*/
Exp* SparcDecoder::dis_Eaddr(ADDRESS pc,int ignore)
{
	Exp* expr;
	dword MATCH_p = pc;
	if (lines(0) == indirectA ) {
		rs1 = magic_process(rs1);
	}
	if (lines(0) == indexA ) {
		rs1 = magic_process(rs1);
		rs2 = magic_process(rs2);
	}
	if (lines(0) == absoluteA ) {
		i = magic_process(i);
	}
	if (lines(0) == dispA ) {
		rs1 = magic_process(rs1);
		i = magic_process(i);
	}
	return expr;
}
/*==============================================================================
 * FUNCTION:	  isFuncPrologue()
 * OVERVIEW:	  Check to see if the instructions at the given offset match any callee prologue, i.e. does it look
 *					like this offset is a pointer to a function?
 * PARAMETERS:	  hostPC - pointer to the code in question (host address)
 * RETURNS:		  True if a match found
 *============================================================================*/
bool SparcDecoder::isFuncPrologue(ADDRESS hostPC)
{
	return false;
}
/*==============================================================================
 * FUNCTION:	  isRestore()
 * OVERVIEW:	  Check to see if the instruction at the given offset is a restore instruction
 * PARAMETERS:	  hostPC - pointer to the code in question (host address)
 * RETURNS:		  True if a match found
 *============================================================================*/
bool SparcDecoder::isRestore(ADDRESS hostPC)
{
	dword MATCH_p = hostPC;
	if (lines(0) == RESTORE ) {
		a = magic_process(a);
		b = magic_process(b);
		c = magic_process(c);
	}
}
/**********************************
 * These are the fetch routines.
 **********************************/

/*==============================================================================
 * FUNCTION:		getDword
 * OVERVIEW:		Returns the double starting at the given address.
 * PARAMETERS:		lc - address at which to decode the double
 * RETURNS:			the decoded double
 *============================================================================*/
DWord SparcDecoder::getDword(ADDRESS lc)
{
	Byte* p = (Byte*)lc;
	return (p[0] << 24) + (p[1] << 16) + (p[2] << 8) + p[3];
}
/*==============================================================================
 * FUNCTION:	   SparcDecoder::SparcDecoder
 * OVERVIEW:	   
 * PARAMETERS:	   None
 * RETURNS:		   N/A
 *============================================================================*/
SparcDecoder::SparcDecoder(Prog* prog)
{
	std::string file = Boomerang::get()->getProgPath() + "frontend/machine/sparc/sparc.ssl";
	RTLDict.readSSLFile(file.c_str());
}
int SparcDecoder::decodeAssemblyInstruction(unsigned,int)
{
	return 0;
}
