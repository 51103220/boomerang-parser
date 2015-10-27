unsigned magic_process(char *name) {
	if (strcmp(name,"%g0") == 0) return 0;
	if (strcmp(name,"%g1") == 0) return 1;
	if (strcmp(name,"%g2") == 0) return 2;
	if (strcmp(name,"%g3") == 0) return 3;
	if (strcmp(name,"%g4") == 0) return 4;
	if (strcmp(name,"%g5") == 0) return 5;
	if (strcmp(name,"%g6") == 0) return 6;
	if (strcmp(name,"%g7") == 0) return 7;
	if (strcmp(name,"%o0") == 0) return 8;
	if (strcmp(name,"%o1") == 0) return 9;
	if (strcmp(name,"%o2") == 0) return 10;
	if (strcmp(name,"%o3") == 0) return 11;
	if (strcmp(name,"%o4") == 0) return 12;
	if (strcmp(name,"%o5") == 0) return 13;
	if (strcmp(name,"%sp") == 0) return 14;
	if (strcmp(name,"%o7") == 0) return 15;
	if (strcmp(name,"%l0") == 0) return 16;
	if (strcmp(name,"%l1") == 0) return 17;
	if (strcmp(name,"%l2") == 0) return 18;
	if (strcmp(name,"%l3") == 0) return 19;
	if (strcmp(name,"%l4") == 0) return 20;
	if (strcmp(name,"%l5") == 0) return 21;
	if (strcmp(name,"%l6") == 0) return 22;
	if (strcmp(name,"%l7") == 0) return 23;
	if (strcmp(name,"%i0") == 0) return 24;
	if (strcmp(name,"%i1") == 0) return 25;
	if (strcmp(name,"%i2") == 0) return 26;
	if (strcmp(name,"%i3") == 0) return 27;
	if (strcmp(name,"%i4") == 0) return 28;
	if (strcmp(name,"%i5") == 0) return 29;
	if (strcmp(name,"%fp") == 0) return 30;
	if (strcmp(name,"%i7") == 0) return 31;
	if (strcmp(name,"%f0") == 0) return 0;
	if (strcmp(name,"%f1") == 0) return 1;
	if (strcmp(name,"%f2") == 0) return 2;
	if (strcmp(name,"%f3") == 0) return 3;
	if (strcmp(name,"%f4") == 0) return 4;
	if (strcmp(name,"%f5") == 0) return 5;
	if (strcmp(name,"%f6") == 0) return 6;
	if (strcmp(name,"%f7") == 0) return 7;
	if (strcmp(name,"%f8") == 0) return 8;
	if (strcmp(name,"%f9") == 0) return 9;
	if (strcmp(name,"%f10") == 0) return 10;
	if (strcmp(name,"%f11") == 0) return 11;
	if (strcmp(name,"%f12") == 0) return 12;
	if (strcmp(name,"%f13") == 0) return 13;
	if (strcmp(name,"%f14") == 0) return 14;
	if (strcmp(name,"%f15") == 0) return 15;
	if (strcmp(name,"%f16") == 0) return 16;
	if (strcmp(name,"%f17") == 0) return 17;
	if (strcmp(name,"%f18") == 0) return 18;
	if (strcmp(name,"%f19") == 0) return 19;
	if (strcmp(name,"%f20") == 0) return 20;
	if (strcmp(name,"%f21") == 0) return 21;
	if (strcmp(name,"%f22") == 0) return 22;
	if (strcmp(name,"%f23") == 0) return 23;
	if (strcmp(name,"%f24") == 0) return 24;
	if (strcmp(name,"%f25") == 0) return 25;
	if (strcmp(name,"%f26") == 0) return 26;
	if (strcmp(name,"%f27") == 0) return 27;
	if (strcmp(name,"%f28") == 0) return 28;
	if (strcmp(name,"%f29") == 0) return 29;
	if (strcmp(name,"%f30") == 0) return 30;
	if (strcmp(name,"%f31") == 0) return 31;
	if (strcmp(name,"%f0to1") == 0) return 0;
	if (strcmp(name,"a") == 0) return 1;
	if (strcmp(name,"%f2to3") == 0) return 2;
	if (strcmp(name,"b") == 0) return 3;
	if (strcmp(name,"%f4to5") == 0) return 4;
	if (strcmp(name,"c") == 0) return 5;
	if (strcmp(name,"%f6to7") == 0) return 6;
	if (strcmp(name,"d") == 0) return 7;
	if (strcmp(name,"%f8to9") == 0) return 8;
	if (strcmp(name,"e") == 0) return 9;
	if (strcmp(name,"%f10to11") == 0) return 10;
	if (strcmp(name,"f") == 0) return 11;
	if (strcmp(name,"%f12to13") == 0) return 12;
	if (strcmp(name,"g") == 0) return 13;
	if (strcmp(name,"%f14to15") == 0) return 14;
	if (strcmp(name,"h") == 0) return 15;
	if (strcmp(name,"%f16to17") == 0) return 16;
	if (strcmp(name,"i") == 0) return 17;
	if (strcmp(name,"%f18to19") == 0) return 18;
	if (strcmp(name,"j") == 0) return 19;
	if (strcmp(name,"%f20to21") == 0) return 20;
	if (strcmp(name,"k") == 0) return 21;
	if (strcmp(name,"%f22to23") == 0) return 22;
	if (strcmp(name,"l") == 0) return 23;
	if (strcmp(name,"%f24to25") == 0) return 24;
	if (strcmp(name,"m") == 0) return 25;
	if (strcmp(name,"%f26to27") == 0) return 26;
	if (strcmp(name,"n") == 0) return 27;
	if (strcmp(name,"%f28to29") == 0) return 28;
	if (strcmp(name,"o") == 0) return 29;
	if (strcmp(name,"%f30to31") == 0) return 30;
	if (strcmp(name,"p") == 0) return 31;
	if (strcmp(name,"%f0to3") == 0) return 0;
	if (strcmp(name,"q") == 0) return 1;
	if (strcmp(name,"r") == 0) return 2;
	if (strcmp(name,"s") == 0) return 3;
	if (strcmp(name,"%f4to7") == 0) return 4;
	if (strcmp(name,"t") == 0) return 5;
	if (strcmp(name,"u") == 0) return 6;
	if (strcmp(name,"v") == 0) return 7;
	if (strcmp(name,"%f8to11") == 0) return 8;
	if (strcmp(name,"w") == 0) return 9;
	if (strcmp(name,"x") == 0) return 10;
	if (strcmp(name,"y") == 0) return 11;
	if (strcmp(name,"%f12to15") == 0) return 12;
	if (strcmp(name,"z") == 0) return 13;
	if (strcmp(name,"A") == 0) return 14;
	if (strcmp(name,"B") == 0) return 15;
	if (strcmp(name,"%f16to19") == 0) return 16;
	if (strcmp(name,"C") == 0) return 17;
	if (strcmp(name,"D") == 0) return 18;
	if (strcmp(name,"E") == 0) return 19;
	if (strcmp(name,"%f20to23") == 0) return 20;
	if (strcmp(name,"F") == 0) return 21;
	if (strcmp(name,"G") == 0) return 22;
	if (strcmp(name,"H") == 0) return 23;
	if (strcmp(name,"%f24to27") == 0) return 24;
	if (strcmp(name,"I") == 0) return 25;
	if (strcmp(name,"J") == 0) return 26;
	if (strcmp(name,"K") == 0) return 27;
	if (strcmp(name,"%f28to31") == 0) return 28;
	if (strcmp(name,"L") == 0) return 29;
	if (strcmp(name,"M") == 0) return 30;
	if (strcmp(name,"N") == 0) return 31;
	if (strcmp(name,"%c0") == 0) return 0;
	if (strcmp(name,"%c1") == 0) return 1;
	if (strcmp(name,"%c2") == 0) return 2;
	if (strcmp(name,"%c3") == 0) return 3;
	if (strcmp(name,"%c4") == 0) return 4;
	if (strcmp(name,"%c5") == 0) return 5;
	if (strcmp(name,"%c6") == 0) return 6;
	if (strcmp(name,"%c7") == 0) return 7;
	if (strcmp(name,"%c8") == 0) return 8;
	if (strcmp(name,"%c9") == 0) return 9;
	if (strcmp(name,"%c10") == 0) return 10;
	if (strcmp(name,"%c11") == 0) return 11;
	if (strcmp(name,"%c12") == 0) return 12;
	if (strcmp(name,"%c13") == 0) return 13;
	if (strcmp(name,"%c14") == 0) return 14;
	if (strcmp(name,"%c15") == 0) return 15;
	if (strcmp(name,"%c16") == 0) return 16;
	if (strcmp(name,"%c17") == 0) return 17;
	if (strcmp(name,"%c18") == 0) return 18;
	if (strcmp(name,"%c19") == 0) return 19;
	if (strcmp(name,"%c20") == 0) return 20;
	if (strcmp(name,"%c21") == 0) return 21;
	if (strcmp(name,"%c22") == 0) return 22;
	if (strcmp(name,"%c23") == 0) return 23;
	if (strcmp(name,"%c24") == 0) return 24;
	if (strcmp(name,"%c25") == 0) return 25;
	if (strcmp(name,"%c26") == 0) return 26;
	if (strcmp(name,"%c27") == 0) return 27;
	if (strcmp(name,"%c28") == 0) return 28;
	if (strcmp(name,"%c29") == 0) return 29;
	if (strcmp(name,"%c30") == 0) return 30;
	if (strcmp(name,"%c31") == 0) return 31;
	if (strcmp(name,"") == 0) return 0;
	if (strcmp(name,",a") == 0) return 1;
}
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
			else
			if(name[3] == 'E')
			br->setCondType(BRANCH_JSLE, true);
			else
			br->setCondType(BRANCH_JSL, true);
			break;
			case 'G':
			if(name[3] == 'E')
			br->setCondType(BRANCH_JSGE, true);
			else
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
			else
			br->setCondType(BRANCH_JSLE);
		}
		else
		br->setCondType(BRANCH_JSL);
		break;
		case 'N':
		if(name[3] == 'G')
		br->setCondType(BRANCH_JMI);
		else
		br->setCondType(BRANCH_JNE);
		break;
		case 'C':
		if(name[2] == 'C')
		br->setCondType(BRANCH_JUGE);
		else
		br->setCondType(BRANCH_JUL);
		break;
		case 'V':
		if(name[2] == 'C')
		std::cerr << "Decoded BVC instruction\n";
		else
		std::cerr << "Decoded BVS instruction\n";
		break;
		case 'G':
		if(name[2] == 'E')
		br->setCondType(BRANCH_JSGE);
		else
		if(name[2] == 'U')
		br->setCondType(BRANCH_JUG);
		else
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
	if (lines(0) == 'CALL' ) {
		unsigned addr = magic_process(lines(1));
		CallStatement* newCall = new CallStatement;
		ADDRESS nativeDest = addr - delta;
		newCall->setDest(nativeDest);
		Proc* destProc = prog->setNewProc(nativeDest);
		if (destProc == (Proc*)-1) destProc = NULL;
		newCall->setDestProc(destProc);
		result.rtl = new RTL(pc, stmts);
		result.rtl->appendStmt(newCall);
		result.type = SD;
	}
	if (lines(0) == 'BN,a' || lines(0) == 'BE,a' || lines(0) == 'BLE,a' || lines(0) == 'BL,a' || lines(0) == 'BLEU,a' || lines(0) == 'BCS,a' || lines(0) == 'BNEG,a' || lines(0) == 'BVS,a' || lines(0) == 'BA,a' || lines(0) == 'BNE,a' || lines(0) == 'BG,a' || lines(0) == 'BGE,a' || lines(0) == 'BGU,a' || lines(0) == 'BCC,a' || lines(0) == 'BPOS,a' || lines(0) == 'BVC,a' || lines(0) == 'FBN,a' || lines(0) == 'FBNE,a' || lines(0) == 'FBLG,a' || lines(0) == 'FBUL,a' || lines(0) == 'FBL,a' || lines(0) == 'FBUG,a' || lines(0) == 'FBG,a' || lines(0) == 'FBU,a' || lines(0) == 'FBA,a' || lines(0) == 'FBE,a' || lines(0) == 'FBUE,a' || lines(0) == 'FBGE,a' || lines(0) == 'FBUGE,a' || lines(0) == 'FBLE,a' || lines(0) == 'FBULE,a' || lines(0) == 'FBO,a' || lines(0) == 'CBN,a' || lines(0) == 'CB123,a' || lines(0) == 'CB12,a' || lines(0) == 'CB13,a' || lines(0) == 'CB1,a' || lines(0) == 'CB23,a' || lines(0) == 'CB2,a' || lines(0) == 'CB3,a' || lines(0) == 'CBA,a' || lines(0) == 'CB0,a' || lines(0) == 'CB03,a' || lines(0) == 'CB02,a' || lines(0) == 'CB023,a' || lines(0) == 'CB01,a' || lines(0) == 'CB013,a' || lines(0) == 'CB012,a') {
		unsigned tgt = magic_process(lines(1));
		char *name = lines(0);
		if(name[0] == 'C')
		{
			result.valid = false;
			result.rtl = new RTL;
			result.numBytes = 4;
			return result;
		}
		GotoStatement* jump = 0;
		RTL* rtl = NULL;
		if(strcmp(name,"BA,a") == 0 || strcmp(name,"BN,a") == 0)
		{
			jump = new GotoStatement;
			rtl = new RTL(pc, stmts);
			rtl->appendStmt(jump);
		}
		else
		if(strcmp(name,"BVS,a") == 0 || strcmp(name,"BVC,a") == 0)
		{
			jump = new GotoStatement;
			rtl = new RTL(pc, stmts);
			rtl->appendStmt(jump);
		}
		else
		{
			rtl = createBranchRtl(pc, stmts, name);
			jump = (GotoStatement*) rtl->getList().back();
		}
		result.type = SCDAN;
		if((strcmp(name,"BA,a") == 0) || (strcmp(name, "BVC,a") == 0))
		{
			result.type = SU;
		}
		else
		{
			result.type = SKIP;
		}
		result.rtl = rtl;
		jump->setDest(tgt - delta);
	}
	if (lines(0) == 'BPN,a' || lines(0) == 'BPE,a' || lines(0) == 'BPLE,a' || lines(0) == 'BPL,a' || lines(0) == 'BPLEU,a' || lines(0) == 'BPCS,a' || lines(0) == 'BPNEG,a' || lines(0) == 'BPVS,a' || lines(0) == 'BPA,a' || lines(0) == 'BPNE,a' || lines(0) == 'BPG,a' || lines(0) == 'BPGE,a' || lines(0) == 'BPGU,a' || lines(0) == 'BPCC,a' || lines(0) == 'BPPOS,a' || lines(0) == 'BPVC,a') {
		unsigned cc01 = magic_process(lines(1));
		unsigned tgt = magic_process(lines(2));
		char *name = lines(0);
		if(cc01 != 0)
		{
			result.valid = false;
			result.rtl = new RTL;
			result.numBytes = 4;
			return result;
		}
		GotoStatement* jump = 0;
		RTL* rtl = NULL;
		if(strcmp(name,"BPA,a") == 0 || strcmp(name,"BPN,a") == 0)
		{
			jump = new GotoStatement;
			rtl = new RTL(pc, stmts);
			rtl->appendStmt(jump);
		}
		else
		if(strcmp(name,"BPVS,a") == 0 || strcmp(name,"BPVC,a") == 0)
		{
			jump = new GotoStatement;
			rtl = new RTL(pc, stmts);
			rtl->appendStmt(jump);
		}
		else
		{
			rtl = createBranchRtl(pc, stmts, name);
			jump = (GotoStatement*) rtl->getList().back();
		}
		result.type = SCDAN;
		if((strcmp(name,"BPA,a") == 0) || (strcmp(name, "BPVC,a") == 0))
		{
			result.type = SU;
		}
		else
		{
			result.type = SKIP;
		}
		result.rtl = rtl;
		jump->setDest(tgt - delta);
	}
	if (lines(0) == 'BN' || lines(0) == 'BE' || lines(0) == 'BLE' || lines(0) == 'BL' || lines(0) == 'BLEU' || lines(0) == 'BCS' || lines(0) == 'BNEG' || lines(0) == 'BVS' || lines(0) == 'BA' || lines(0) == 'BNE' || lines(0) == 'BG' || lines(0) == 'BGE' || lines(0) == 'BGU' || lines(0) == 'BCC' || lines(0) == 'BPOS' || lines(0) == 'BVC' || lines(0) == 'FBN' || lines(0) == 'FBNE' || lines(0) == 'FBLG' || lines(0) == 'FBUL' || lines(0) == 'FBL' || lines(0) == 'FBUG' || lines(0) == 'FBG' || lines(0) == 'FBU' || lines(0) == 'FBA' || lines(0) == 'FBE' || lines(0) == 'FBUE' || lines(0) == 'FBGE' || lines(0) == 'FBUGE' || lines(0) == 'FBLE' || lines(0) == 'FBULE' || lines(0) == 'FBO' || lines(0) == 'CBN' || lines(0) == 'CB123' || lines(0) == 'CB12' || lines(0) == 'CB13' || lines(0) == 'CB1' || lines(0) == 'CB23' || lines(0) == 'CB2' || lines(0) == 'CB3' || lines(0) == 'CBA' || lines(0) == 'CB0' || lines(0) == 'CB03' || lines(0) == 'CB02' || lines(0) == 'CB023' || lines(0) == 'CB01' || lines(0) == 'CB013' || lines(0) == 'CB012') {
		unsigned tgt = magic_process(lines(1));
		char *name = lines(0);
		if(name[0] == 'C')
		{
			result.valid = false;
			result.rtl = new RTL;
			result.numBytes = 4;
			return result;
		}
		GotoStatement* jump = 0;
		RTL* rtl = NULL;
		if(strcmp(name,"BA") == 0 || strcmp(name,"BN") == 0)
		{
			jump = new GotoStatement;
			rtl = new RTL(pc, stmts);
			rtl->appendStmt(jump);
		}
		else
		if(strcmp(name,"BVS") == 0 || strcmp(name,"BVC") == 0)
		{
			jump = new GotoStatement;
			rtl = new RTL(pc, stmts);
			rtl->appendStmt(jump);
		}
		else
		{
			rtl = createBranchRtl(pc, stmts, name);
			jump = (BranchStatement*) rtl->getList().back();
		}
		result.type = SCD;
		if((strcmp(name,"BA") == 0) || (strcmp(name, "BVC") == 0))
		result.type = SD;
		if((strcmp(name,"BN") == 0) || (strcmp(name, "BVS") == 0))
		result.type = NCT;
		result.rtl = rtl;
		jump->setDest(tgt - delta);
	}
	if (lines(0) == 'BPA' ) {
		unsigned cc01 = magic_process(lines(1));
		unsigned tgt = magic_process(lines(2));
		unused(cc01);
		GotoStatement* jump = new GotoStatement;
		result.type = SD;
		result.rtl = new RTL(pc, stmts);
		result.rtl->appendStmt(jump);
		jump->setDest(tgt - delta);
	}
	if (lines(0) == 'BPN' || lines(0) == 'BPE' || lines(0) == 'BPLE' || lines(0) == 'BPL' || lines(0) == 'BPLEU' || lines(0) == 'BPCS' || lines(0) == 'BPNEG' || lines(0) == 'BPVS' || lines(0) == 'BPA' || lines(0) == 'BPNE' || lines(0) == 'BPG' || lines(0) == 'BPGE' || lines(0) == 'BPGU' || lines(0) == 'BPCC' || lines(0) == 'BPPOS' || lines(0) == 'BPVC') {
		unsigned cc01 = magic_process(lines(1));
		unsigned tgt = magic_process(lines(2));
		char *name = lines(0);
		if(cc01 != 0)
		{
			result.valid = false;
			result.rtl = new RTL;
			result.numBytes = 4;
			return result;
		}
		GotoStatement* jump = 0;
		RTL* rtl = NULL;
		if(strcmp(name,"BPN") == 0)
		{
			jump = new GotoStatement;
			rtl = new RTL(pc, stmts);
			rtl->appendStmt(jump);
		}
		else
		if(strcmp(name,"BPVS") == 0 || strcmp(name,"BPVC") == 0)
		{
			jump = new GotoStatement;
			rtl = new RTL(pc, stmts);
			rtl->appendStmt(jump);
		}
		else
		{
			rtl = createBranchRtl(pc, stmts, name);
			jump = (GotoStatement*)rtl->getList().back();
		}
		result.type = SCD;
		if(strcmp(name, "BPVC") == 0)
		result.type = SD;
		if((strcmp(name,"BPN") == 0) || (strcmp(name, "BPVS") == 0))
		result.type = NCT;
		result.rtl = rtl;
		jump->setDest(tgt - delta);
	}
	if (lines(0) == 'JMPL' ) {
		unsigned addr = magic_process(lines(1));
		unsigned rd = magic_process(lines(2));
		CaseStatement* jump = new CaseStatement;
		jump->setIsComputed();
		result.rtl = new RTL(pc, stmts);
		result.rtl->appendStmt(jump);
		result.type = DD;
		jump->setDest(dis_Eaddr(addr));
		unused(rd);
	}
	if (lines(0) == 'SAVE' ) {
		unsigned rs1 = magic_process(lines(1));
		unsigned roi = magic_process(lines(2));
		unsigned rd = magic_process(lines(3));
		stmts = instantiate(pc, "SAVE", DIS_RS1, DIS_ROI, DIS_RD);
	}
	if (lines(0) == 'RESTORE' ) {
		unsigned rs1 = magic_process(lines(1));
		unsigned roi = magic_process(lines(2));
		unsigned rd = magic_process(lines(3));
		stmts = instantiate(pc, "RESTORE", DIS_RS1, DIS_ROI, DIS_RD);
	}
	if (lines(0) == 'NOP' ) {
		char *name = lines(0);
		result.type = NOP;
		stmts = instantiate(pc,	 name);
	}
	if (lines(0) == 'SETHI' ) {
		unsigned imm22 = magic_process(lines(1));
		unsigned rd = magic_process(lines(2));
		stmts = instantiate(pc,	 "sethi", dis_Num(imm22), DIS_RD);
	}
	if (lines(0) == 'LDSB' || lines(0) == 'LDSH' || lines(0) == 'LDUB' || lines(0) == 'LDUH' || lines(0) == 'LD' || lines(0) == 'LDSTUB' || lines(0) == 'SWAP.' || lines(0) == 'LDD') {
		unsigned addr = magic_process(lines(1));
		unsigned rd = magic_process(lines(2));
		char *name = lines(0);
		stmts = instantiate(pc,	 name, DIS_ADDR, DIS_RD);
	}
	if (lines(0) == 'LDF' ) {
		unsigned addr = magic_process(lines(1));
		unsigned fds = magic_process(lines(2));
		char *name = lines(0);
		stmts = instantiate(pc,	 name, DIS_ADDR, DIS_FDS);
	}
	if (lines(0) == 'LDDF' ) {
		unsigned addr = magic_process(lines(1));
		unsigned fdd = magic_process(lines(2));
		char *name = lines(0);
		stmts = instantiate(pc,	 name, DIS_ADDR, DIS_FDD);
	}
	if (lines(0) == 'LDSBA' || lines(0) == 'LDSHA' || lines(0) == 'LDUBA' || lines(0) == 'LDUHA' || lines(0) == 'LDA' || lines(0) == 'LDSTUBA' || lines(0) == 'SWAPA' || lines(0) == 'LDDA') {
		unsigned addr = magic_process(lines(1));
		unsigned asi = magic_process(lines(2));
		unsigned rd = magic_process(lines(3));
		char *name = lines(0);
		unused(asi);
		stmts = instantiate(pc,	 name, DIS_RD, DIS_ADDR);
	}
	if (lines(0) == 'STB' || lines(0) == 'STH' || lines(0) == 'ST' || lines(0) == 'STD') {
		unsigned rd = magic_process(lines(1));
		unsigned addr = magic_process(lines(2));
		char *name = lines(0);
		stmts = instantiate(pc,	 name, DIS_RDR, DIS_ADDR);
	}
	if (lines(0) == 'STF' ) {
		unsigned fds = magic_process(lines(1));
		unsigned addr = magic_process(lines(2));
		char *name = lines(0);
		stmts = instantiate(pc,	 name, DIS_FDS, DIS_ADDR);
	}
	if (lines(0) == 'STDF' ) {
		unsigned fdd = magic_process(lines(1));
		unsigned addr = magic_process(lines(2));
		char *name = lines(0);
		stmts = instantiate(pc,	 name, DIS_FDD, DIS_ADDR);
	}
	if (lines(0) == 'STBA' || lines(0) == 'STHA' || lines(0) == 'STA' || lines(0) == 'STDA') {
		unsigned rd = magic_process(lines(1));
		unsigned addr = magic_process(lines(2));
		unsigned asi = magic_process(lines(3));
		char *name = lines(0);
		unused(asi);
		stmts = instantiate(pc,	 name, DIS_RDR, DIS_ADDR);
	}
	if (lines(0) == 'LDFSR' ) {
		unsigned addr = magic_process(lines(1));
		char *name = lines(0);
		stmts = instantiate(pc,	 name, DIS_ADDR);
	}
	if (lines(0) == 'LDCSR' ) {
		unsigned addr = magic_process(lines(1));
		char *name = lines(0);
		stmts = instantiate(pc,	 name, DIS_ADDR);
	}
	if (lines(0) == 'STFSR' ) {
		unsigned addr = magic_process(lines(1));
		char *name = lines(0);
		stmts = instantiate(pc,	 name, DIS_ADDR);
	}
	if (lines(0) == 'STCSR' ) {
		unsigned addr = magic_process(lines(1));
		char *name = lines(0);
		stmts = instantiate(pc,	 name, DIS_ADDR);
	}
	if (lines(0) == 'STDFQ' ) {
		unsigned addr = magic_process(lines(1));
		char *name = lines(0);
		stmts = instantiate(pc,	 name, DIS_ADDR);
	}
	if (lines(0) == 'STDCQ' ) {
		unsigned addr = magic_process(lines(1));
		char *name = lines(0);
		stmts = instantiate(pc,	 name, DIS_ADDR);
	}
	if (lines(0) == 'RDY' ) {
		unsigned rd = magic_process(lines(1));
		char *name = lines(0);
		stmts = instantiate(pc,	 name, DIS_RD);
	}
	if (lines(0) == 'RDPSR' ) {
		unsigned rd = magic_process(lines(1));
		char *name = lines(0);
		stmts = instantiate(pc,	 name, DIS_RD);
	}
	if (lines(0) == 'RDWIM' ) {
		unsigned rd = magic_process(lines(1));
		char *name = lines(0);
		stmts = instantiate(pc,	 name, DIS_RD);
	}
	if (lines(0) == 'RDTBR' ) {
		unsigned rd = magic_process(lines(1));
		char *name = lines(0);
		stmts = instantiate(pc,	 name, DIS_RD);
	}
	if (lines(0) == 'WRY' ) {
		unsigned rs1 = magic_process(lines(1));
		unsigned roi = magic_process(lines(2));
		char *name = lines(0);
		stmts = instantiate(pc,	 name, DIS_RS1, DIS_ROI);
	}
	if (lines(0) == 'WRPSR' ) {
		unsigned rs1 = magic_process(lines(1));
		unsigned roi = magic_process(lines(2));
		char *name = lines(0);
		stmts = instantiate(pc,	 name, DIS_RS1, DIS_ROI);
	}
	if (lines(0) == 'WRWIM' ) {
		unsigned rs1 = magic_process(lines(1));
		unsigned roi = magic_process(lines(2));
		char *name = lines(0);
		stmts = instantiate(pc,	 name, DIS_RS1, DIS_ROI);
	}
	if (lines(0) == 'WRTBR' ) {
		unsigned rs1 = magic_process(lines(1));
		unsigned roi = magic_process(lines(2));
		char *name = lines(0);
		stmts = instantiate(pc,	 name, DIS_RS1, DIS_ROI);
	}
	if (lines(0) == 'AND' || lines(0) == 'ANDcc' || lines(0) == 'ANDN' || lines(0) == 'ANDNcc' || lines(0) == 'OR' || lines(0) == 'ORcc' || lines(0) == 'ORN' || lines(0) == 'ORNcc' || lines(0) == 'XOR' || lines(0) == 'XORcc' || lines(0) == 'XNOR' || lines(0) == 'XNORcc' || lines(0) == 'SLL' || lines(0) == 'SRL' || lines(0) == 'SRA' || lines(0) == 'ADD' || lines(0) == 'ADDcc' || lines(0) == 'ADDX' || lines(0) == 'ADDXcc' || lines(0) == 'TADDcc' || lines(0) == 'TADDccTV' || lines(0) == 'SUB' || lines(0) == 'SUBcc' || lines(0) == 'SUBX' || lines(0) == 'SUBXcc' || lines(0) == 'TSUBcc' || lines(0) == 'TSUBccTV' || lines(0) == 'MULScc' || lines(0) == 'UMUL' || lines(0) == 'SMUL' || lines(0) == 'UMULcc' || lines(0) == 'SMULcc' || lines(0) == 'UDIV' || lines(0) == 'SDIV' || lines(0) == 'UDIVcc' || lines(0) == 'SDIVcc' || lines(0) == 'SAVE' || lines(0) == 'RESTORE') {
		unsigned rs1 = magic_process(lines(1));
		unsigned roi = magic_process(lines(2));
		unsigned rd = magic_process(lines(3));
		char *name = lines(0);
		stmts = instantiate(pc,	 name, DIS_RS1, DIS_ROI, DIS_RD);
	}
	if (lines(0) == 'FMOVs' || lines(0) == 'FNEGs' || lines(0) == 'FABSs' || lines(0) == 'FSQRTs') {
		unsigned fs2s = magic_process(lines(1));
		unsigned fds = magic_process(lines(2));
		char *name = lines(0);
		stmts = instantiate(pc,	 name, DIS_FS2S, DIS_FDS);
	}
	if (lines(0) == 'FADDs' || lines(0) == 'FSUBs' || lines(0) == 'FMULs' || lines(0) == 'FDIVs') {
		unsigned fs1s = magic_process(lines(1));
		unsigned fs2s = magic_process(lines(2));
		unsigned fds = magic_process(lines(3));
		char *name = lines(0);
		stmts = instantiate(pc,	 name, DIS_FS1S, DIS_FS2S, DIS_FDS);
	}
	if (lines(0) == 'FADDd' || lines(0) == 'FSUBd' || lines(0) == 'FMULd' || lines(0) == 'FDIVd') {
		unsigned fs1d = magic_process(lines(1));
		unsigned fs2d = magic_process(lines(2));
		unsigned fdd = magic_process(lines(3));
		char *name = lines(0);
		stmts = instantiate(pc,	 name, DIS_FS1D, DIS_FS2D, DIS_FDD);
	}
	if (lines(0) == 'FADDq' || lines(0) == 'FSUBq' || lines(0) == 'FMULq' || lines(0) == 'FDIVq') {
		unsigned fs1q = magic_process(lines(1));
		unsigned fs2q = magic_process(lines(2));
		unsigned fdq = magic_process(lines(3));
		char *name = lines(0);
		stmts = instantiate(pc,	 name, DIS_FS1Q, DIS_FS2Q, DIS_FDQ);
	}
	if (lines(0) == 'FCMPs' || lines(0) == 'FCMPEs') {
		unsigned fs1s = magic_process(lines(1));
		unsigned fs2s = magic_process(lines(2));
		char *name = lines(0);
		stmts = instantiate(pc,	 name, DIS_FS1S, DIS_FS2S);
	}
	if (lines(0) == 'FCMPd' || lines(0) == 'FCMPEd') {
		unsigned fs1d = magic_process(lines(1));
		unsigned fs2d = magic_process(lines(2));
		char *name = lines(0);
		stmts = instantiate(pc,	 name, DIS_FS1D, DIS_FS2D);
	}
	if (lines(0) == 'FCMPq' || lines(0) == 'FCMPEq') {
		unsigned fs1q = magic_process(lines(1));
		unsigned fs2q = magic_process(lines(2));
		char *name = lines(0);
		stmts = instantiate(pc,	 name, DIS_FS1Q, DIS_FS2Q);
	}
	if (lines(0) == 'FiTOs' || lines(0) == 'FsTOi') {
		unsigned fs2s = magic_process(lines(1));
		unsigned fds = magic_process(lines(2));
		char *name = lines(0);
		stmts = instantiate(pc, name, DIS_FS2S, DIS_FDS);
	}
	if (lines(0) == 'FiTOd' ) {
		unsigned fs2s = magic_process(lines(1));
		unsigned fdd = magic_process(lines(2));
		char *name = lines(0);
		stmts = instantiate(pc, name, DIS_FS2S, DIS_FDD);
	}
	if (lines(0) == 'FdTOi' ) {
		unsigned fs2d = magic_process(lines(1));
		unsigned fds = magic_process(lines(2));
		char *name = lines(0);
		stmts = instantiate(pc, name, DIS_FS2D, DIS_FDS);
	}
	if (lines(0) == 'FiTOq' ) {
		unsigned fs2s = magic_process(lines(1));
		unsigned fdq = magic_process(lines(2));
		char *name = lines(0);
		stmts = instantiate(pc, name, DIS_FS2S, DIS_FDQ);
	}
	if (lines(0) == 'FqTOi' ) {
		unsigned fs2q = magic_process(lines(1));
		unsigned fds = magic_process(lines(2));
		char *name = lines(0);
		stmts = instantiate(pc, name, DIS_FS2Q, DIS_FDS);
	}
	if (lines(0) == 'FsTOd' ) {
		unsigned fs2s = magic_process(lines(1));
		unsigned fdd = magic_process(lines(2));
		char *name = lines(0);
		stmts = instantiate(pc, name, DIS_FS2S, DIS_FDD);
	}
	if (lines(0) == 'FdTOs' ) {
		unsigned fs2d = magic_process(lines(1));
		unsigned fds = magic_process(lines(2));
		char *name = lines(0);
		stmts = instantiate(pc, name, DIS_FS2D, DIS_FDS);
	}
	if (lines(0) == 'FsTOq' ) {
		unsigned fs2s = magic_process(lines(1));
		unsigned fdq = magic_process(lines(2));
		char *name = lines(0);
		stmts = instantiate(pc, name, DIS_FS2S, DIS_FDQ);
	}
	if (lines(0) == 'FqTOs' ) {
		unsigned fs2q = magic_process(lines(1));
		unsigned fds = magic_process(lines(2));
		char *name = lines(0);
		stmts = instantiate(pc, name, DIS_FS2Q, DIS_FDS);
	}
	if (lines(0) == 'FdTOq' ) {
		unsigned fs2d = magic_process(lines(1));
		unsigned fdq = magic_process(lines(2));
		char *name = lines(0);
		stmts = instantiate(pc, name, DIS_FS2D, DIS_FDQ);
	}
	if (lines(0) == 'FqTOd' ) {
		unsigned fs2q = magic_process(lines(1));
		unsigned fdd = magic_process(lines(2));
		char *name = lines(0);
		stmts = instantiate(pc, name, DIS_FS2Q, DIS_FDD);
	}
	if (lines(0) == 'FSQRTd' ) {
		unsigned fs2d = magic_process(lines(1));
		unsigned fdd = magic_process(lines(2));
		char *name = lines(0);
		stmts = instantiate(pc, name, DIS_FS2D, DIS_FDD);
	}
	if (lines(0) == 'FSQRTq' ) {
		unsigned fs2q = magic_process(lines(1));
		unsigned fdq = magic_process(lines(2));
		char *name = lines(0);
		stmts = instantiate(pc, name, DIS_FS2Q, DIS_FDQ);
	}
	if (lines(0) == 'RETURN' ) {
		unsigned addr = magic_process(lines(1));
		char *name = lines(0);
		stmts = instantiate(pc, name, DIS_ADDR);
		result.rtl = new RTL(pc, stmts);
		result.rtl->appendStmt(new ReturnStatement);
		result.type = DD;
	}
	if (lines(0) == 'TN' || lines(0) == 'TE' || lines(0) == 'TLE' || lines(0) == 'TL' || lines(0) == 'TLEU' || lines(0) == 'TCS' || lines(0) == 'TNEG' || lines(0) == 'TVS' || lines(0) == 'TA' || lines(0) == 'TNE' || lines(0) == 'TG' || lines(0) == 'TGE' || lines(0) == 'TGU' || lines(0) == 'TCC' || lines(0) == 'TPOS' || lines(0) == 'TVC') {
		unsigned addr = magic_process(lines(1));
		char *name = lines(0);
		stmts = instantiate(pc,	 name, DIS_ADDR);
	}
	if (lines(0) == 'UNIMP' ) {
		unsigned n = magic_process(lines(1));
		unused(n);
		stmts = NULL;
		result.valid = false;
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
	if (lines(0) == 'RESTORE' ) {
		unsigned a = magic_process(lines(1));
		unsigned b = magic_process(lines(2));
		unsigned c = magic_process(lines(3));
		unused(a);
		unused(b);
		unused(c);
		return true;
		else
		return false;
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
