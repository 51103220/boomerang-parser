#include <algorithm>
#include <iostream>
#include <sstream>
#include <iterator>
#include <vector>
#include <sstream>
#include <string>
#include <assert.h>
#include <cstring>
using namespace std;
inline bool isInteger(const std::string & s) {
	if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false ;
	char * p ;
	strtol(s.c_str(), &p, 10) ;
	return (*p == 0) ;
}
unsigned magic_process(std::string name) {
	std::string str = name;
	if (name == "%G0") return 0;
	else if (name == "%G1") return 1;
	else if (name == "%G2") return 2;
	else if (name == "%G3") return 3;
	else if (name == "%G4") return 4;
	else if (name == "%G5") return 5;
	else if (name == "%G6") return 6;
	else if (name == "%G7") return 7;
	else if (name == "%O0") return 8;
	else if (name == "%O1") return 9;
	else if (name == "%O2") return 10;
	else if (name == "%O3") return 11;
	else if (name == "%O4") return 12;
	else if (name == "%O5") return 13;
	else if (name == "%SP") return 14;
	else if (name == "%O7") return 15;
	else if (name == "%L0") return 16;
	else if (name == "%L1") return 17;
	else if (name == "%L2") return 18;
	else if (name == "%L3") return 19;
	else if (name == "%L4") return 20;
	else if (name == "%L5") return 21;
	else if (name == "%L6") return 22;
	else if (name == "%L7") return 23;
	else if (name == "%I0") return 24;
	else if (name == "%I1") return 25;
	else if (name == "%I2") return 26;
	else if (name == "%I3") return 27;
	else if (name == "%I4") return 28;
	else if (name == "%I5") return 29;
	else if (name == "%FP") return 30;
	else if (name == "%I7") return 31;
	else if (name == "%F0") return 0;
	else if (name == "%F1") return 1;
	else if (name == "%F2") return 2;
	else if (name == "%F3") return 3;
	else if (name == "%F4") return 4;
	else if (name == "%F5") return 5;
	else if (name == "%F6") return 6;
	else if (name == "%F7") return 7;
	else if (name == "%F8") return 8;
	else if (name == "%F9") return 9;
	else if (name == "%F10") return 10;
	else if (name == "%F11") return 11;
	else if (name == "%F12") return 12;
	else if (name == "%F13") return 13;
	else if (name == "%F14") return 14;
	else if (name == "%F15") return 15;
	else if (name == "%F16") return 16;
	else if (name == "%F17") return 17;
	else if (name == "%F18") return 18;
	else if (name == "%F19") return 19;
	else if (name == "%F20") return 20;
	else if (name == "%F21") return 21;
	else if (name == "%F22") return 22;
	else if (name == "%F23") return 23;
	else if (name == "%F24") return 24;
	else if (name == "%F25") return 25;
	else if (name == "%F26") return 26;
	else if (name == "%F27") return 27;
	else if (name == "%F28") return 28;
	else if (name == "%F29") return 29;
	else if (name == "%F30") return 30;
	else if (name == "%F31") return 31;
	else if (name == "%F0TO1") return 0;
	else if (name == "A") return 1;
	else if (name == "%F2TO3") return 2;
	else if (name == "B") return 3;
	else if (name == "%F4TO5") return 4;
	else if (name == "C") return 5;
	else if (name == "%F6TO7") return 6;
	else if (name == "D") return 7;
	else if (name == "%F8TO9") return 8;
	else if (name == "E") return 9;
	else if (name == "%F10TO11") return 10;
	else if (name == "F") return 11;
	else if (name == "%F12TO13") return 12;
	else if (name == "G") return 13;
	else if (name == "%F14TO15") return 14;
	else if (name == "H") return 15;
	else if (name == "%F16TO17") return 16;
	else if (name == "I") return 17;
	else if (name == "%F18TO19") return 18;
	else if (name == "J") return 19;
	else if (name == "%F20TO21") return 20;
	else if (name == "K") return 21;
	else if (name == "%F22TO23") return 22;
	else if (name == "L") return 23;
	else if (name == "%F24TO25") return 24;
	else if (name == "M") return 25;
	else if (name == "%F26TO27") return 26;
	else if (name == "N") return 27;
	else if (name == "%F28TO29") return 28;
	else if (name == "O") return 29;
	else if (name == "%F30TO31") return 30;
	else if (name == "P") return 31;
	else if (name == "%F0TO3") return 0;
	else if (name == "Q") return 1;
	else if (name == "R") return 2;
	else if (name == "S") return 3;
	else if (name == "%F4TO7") return 4;
	else if (name == "T") return 5;
	else if (name == "U") return 6;
	else if (name == "V") return 7;
	else if (name == "%F8TO11") return 8;
	else if (name == "W") return 9;
	else if (name == "X") return 10;
	else if (name == "Y") return 11;
	else if (name == "%F12TO15") return 12;
	else if (name == "Z") return 13;
	else if (name == "A") return 14;
	else if (name == "B") return 15;
	else if (name == "%F16TO19") return 16;
	else if (name == "C") return 17;
	else if (name == "D") return 18;
	else if (name == "E") return 19;
	else if (name == "%F20TO23") return 20;
	else if (name == "F") return 21;
	else if (name == "G") return 22;
	else if (name == "H") return 23;
	else if (name == "%F24TO27") return 24;
	else if (name == "I") return 25;
	else if (name == "J") return 26;
	else if (name == "K") return 27;
	else if (name == "%F28TO31") return 28;
	else if (name == "L") return 29;
	else if (name == "M") return 30;
	else if (name == "N") return 31;
	else if (name == "%C0") return 0;
	else if (name == "%C1") return 1;
	else if (name == "%C2") return 2;
	else if (name == "%C3") return 3;
	else if (name == "%C4") return 4;
	else if (name == "%C5") return 5;
	else if (name == "%C6") return 6;
	else if (name == "%C7") return 7;
	else if (name == "%C8") return 8;
	else if (name == "%C9") return 9;
	else if (name == "%C10") return 10;
	else if (name == "%C11") return 11;
	else if (name == "%C12") return 12;
	else if (name == "%C13") return 13;
	else if (name == "%C14") return 14;
	else if (name == "%C15") return 15;
	else if (name == "%C16") return 16;
	else if (name == "%C17") return 17;
	else if (name == "%C18") return 18;
	else if (name == "%C19") return 19;
	else if (name == "%C20") return 20;
	else if (name == "%C21") return 21;
	else if (name == "%C22") return 22;
	else if (name == "%C23") return 23;
	else if (name == "%C24") return 24;
	else if (name == "%C25") return 25;
	else if (name == "%C26") return 26;
	else if (name == "%C27") return 27;
	else if (name == "%C28") return 28;
	else if (name == "%C29") return 29;
	else if (name == "%C30") return 30;
	else if (name == "%C31") return 31;
	else if (name == "") return 0;
	else if (name == ",A") return 1;
	else if (isInteger(str)) {
		int i = std::atoi((str).c_str());
		if (i < 0) return i;
		else return 100 + i;
	}
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
	if (tokens.at(0) == "CALL" ) {
		unsigned addr = magic_process(tokens.at(1));
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
	if (tokens.at(0) == "BN,a" || tokens.at(0) == "BE,a" || tokens.at(0) == "BLE,a" || tokens.at(0) == "BL,a" || tokens.at(0) == "BLEU,a" || tokens.at(0) == "BCS,a" || tokens.at(0) == "BNEG,a" || tokens.at(0) == "BVS,a" || tokens.at(0) == "BA,a" || tokens.at(0) == "BNE,a" || tokens.at(0) == "BG,a" || tokens.at(0) == "BGE,a" || tokens.at(0) == "BGU,a" || tokens.at(0) == "BCC,a" || tokens.at(0) == "BPOS,a" || tokens.at(0) == "BVC,a" || tokens.at(0) == "FBN,a" || tokens.at(0) == "FBNE,a" || tokens.at(0) == "FBLG,a" || tokens.at(0) == "FBUL,a" || tokens.at(0) == "FBL,a" || tokens.at(0) == "FBUG,a" || tokens.at(0) == "FBG,a" || tokens.at(0) == "FBU,a" || tokens.at(0) == "FBA,a" || tokens.at(0) == "FBE,a" || tokens.at(0) == "FBUE,a" || tokens.at(0) == "FBGE,a" || tokens.at(0) == "FBUGE,a" || tokens.at(0) == "FBLE,a" || tokens.at(0) == "FBULE,a" || tokens.at(0) == "FBO,a" || tokens.at(0) == "CBN,a" || tokens.at(0) == "CB123,a" || tokens.at(0) == "CB12,a" || tokens.at(0) == "CB13,a" || tokens.at(0) == "CB1,a" || tokens.at(0) == "CB23,a" || tokens.at(0) == "CB2,a" || tokens.at(0) == "CB3,a" || tokens.at(0) == "CBA,a" || tokens.at(0) == "CB0,a" || tokens.at(0) == "CB03,a" || tokens.at(0) == "CB02,a" || tokens.at(0) == "CB023,a" || tokens.at(0) == "CB01,a" || tokens.at(0) == "CB013,a" || tokens.at(0) == "CB012,a") {
		unsigned tgt = magic_process(tokens.at(1));
		char *name =  new char[tokens.at(0).length() + 1];
		strcpy(name, tokens.at(0).c_str());
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
	if (tokens.at(0) == "BPN,a" || tokens.at(0) == "BPE,a" || tokens.at(0) == "BPLE,a" || tokens.at(0) == "BPL,a" || tokens.at(0) == "BPLEU,a" || tokens.at(0) == "BPCS,a" || tokens.at(0) == "BPNEG,a" || tokens.at(0) == "BPVS,a" || tokens.at(0) == "BPA,a" || tokens.at(0) == "BPNE,a" || tokens.at(0) == "BPG,a" || tokens.at(0) == "BPGE,a" || tokens.at(0) == "BPGU,a" || tokens.at(0) == "BPCC,a" || tokens.at(0) == "BPPOS,a" || tokens.at(0) == "BPVC,a") {
		unsigned cc01 = magic_process(tokens.at(1));
		unsigned tgt = magic_process(tokens.at(2));
		char *name =  new char[tokens.at(0).length() + 1];
		strcpy(name, tokens.at(0).c_str());
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
	if (tokens.at(0) == "BN" || tokens.at(0) == "BE" || tokens.at(0) == "BLE" || tokens.at(0) == "BL" || tokens.at(0) == "BLEU" || tokens.at(0) == "BCS" || tokens.at(0) == "BNEG" || tokens.at(0) == "BVS" || tokens.at(0) == "BA" || tokens.at(0) == "BNE" || tokens.at(0) == "BG" || tokens.at(0) == "BGE" || tokens.at(0) == "BGU" || tokens.at(0) == "BCC" || tokens.at(0) == "BPOS" || tokens.at(0) == "BVC" || tokens.at(0) == "FBN" || tokens.at(0) == "FBNE" || tokens.at(0) == "FBLG" || tokens.at(0) == "FBUL" || tokens.at(0) == "FBL" || tokens.at(0) == "FBUG" || tokens.at(0) == "FBG" || tokens.at(0) == "FBU" || tokens.at(0) == "FBA" || tokens.at(0) == "FBE" || tokens.at(0) == "FBUE" || tokens.at(0) == "FBGE" || tokens.at(0) == "FBUGE" || tokens.at(0) == "FBLE" || tokens.at(0) == "FBULE" || tokens.at(0) == "FBO" || tokens.at(0) == "CBN" || tokens.at(0) == "CB123" || tokens.at(0) == "CB12" || tokens.at(0) == "CB13" || tokens.at(0) == "CB1" || tokens.at(0) == "CB23" || tokens.at(0) == "CB2" || tokens.at(0) == "CB3" || tokens.at(0) == "CBA" || tokens.at(0) == "CB0" || tokens.at(0) == "CB03" || tokens.at(0) == "CB02" || tokens.at(0) == "CB023" || tokens.at(0) == "CB01" || tokens.at(0) == "CB013" || tokens.at(0) == "CB012") {
		unsigned tgt = magic_process(tokens.at(1));
		char *name =  new char[tokens.at(0).length() + 1];
		strcpy(name, tokens.at(0).c_str());
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
	if (tokens.at(0) == "BPA" ) {
		unsigned cc01 = magic_process(tokens.at(1));
		unsigned tgt = magic_process(tokens.at(2));
		unused(cc01);
		GotoStatement* jump = new GotoStatement;
		result.type = SD;
		result.rtl = new RTL(pc, stmts);
		result.rtl->appendStmt(jump);
		jump->setDest(tgt - delta);
	}
	if (tokens.at(0) == "BPN" || tokens.at(0) == "BPE" || tokens.at(0) == "BPLE" || tokens.at(0) == "BPL" || tokens.at(0) == "BPLEU" || tokens.at(0) == "BPCS" || tokens.at(0) == "BPNEG" || tokens.at(0) == "BPVS" || tokens.at(0) == "BPA" || tokens.at(0) == "BPNE" || tokens.at(0) == "BPG" || tokens.at(0) == "BPGE" || tokens.at(0) == "BPGU" || tokens.at(0) == "BPCC" || tokens.at(0) == "BPPOS" || tokens.at(0) == "BPVC") {
		unsigned cc01 = magic_process(tokens.at(1));
		unsigned tgt = magic_process(tokens.at(2));
		char *name =  new char[tokens.at(0).length() + 1];
		strcpy(name, tokens.at(0).c_str());
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
	if (tokens.at(0) == "JMPL" ) {
		unsigned addr = magic_process(tokens.at(1));
		unsigned rd = magic_process(tokens.at(2));
		CaseStatement* jump = new CaseStatement;
		jump->setIsComputed();
		result.rtl = new RTL(pc, stmts);
		result.rtl->appendStmt(jump);
		result.type = DD;
		jump->setDest(dis_Eaddr(addr));
		unused(rd);
	}
	if (tokens.at(0) == "SAVE" ) {
		unsigned rs1 = magic_process(tokens.at(1));
		unsigned roi = magic_process(tokens.at(2));
		unsigned rd = magic_process(tokens.at(3));
		stmts = instantiate(pc, "SAVE", DIS_RS1, DIS_ROI, DIS_RD);
	}
	if (tokens.at(0) == "RESTORE" ) {
		unsigned rs1 = magic_process(tokens.at(1));
		unsigned roi = magic_process(tokens.at(2));
		unsigned rd = magic_process(tokens.at(3));
		stmts = instantiate(pc, "RESTORE", DIS_RS1, DIS_ROI, DIS_RD);
	}
	if (tokens.at(0) == "NOP" ) {
		char *name =  new char[tokens.at(0).length() + 1];
		strcpy(name, tokens.at(0).c_str());
		result.type = NOP;
		stmts = instantiate(pc,	 name);
	}
	if (tokens.at(0) == "SETHI" ) {
		unsigned imm22 = magic_process(tokens.at(1));
		unsigned rd = magic_process(tokens.at(2));
		stmts = instantiate(pc,	 "sethi", dis_Num(imm22), DIS_RD);
	}
	if (tokens.at(0) == "LDSB" || tokens.at(0) == "LDSH" || tokens.at(0) == "LDUB" || tokens.at(0) == "LDUH" || tokens.at(0) == "LD" || tokens.at(0) == "LDSTUB" || tokens.at(0) == "SWAP." || tokens.at(0) == "LDD") {
		unsigned addr = magic_process(tokens.at(1));
		unsigned rd = magic_process(tokens.at(2));
		char *name =  new char[tokens.at(0).length() + 1];
		strcpy(name, tokens.at(0).c_str());
		stmts = instantiate(pc,	 name, DIS_ADDR, DIS_RD);
	}
	if (tokens.at(0) == "LDF" ) {
		unsigned addr = magic_process(tokens.at(1));
		unsigned fds = magic_process(tokens.at(2));
		char *name =  new char[tokens.at(0).length() + 1];
		strcpy(name, tokens.at(0).c_str());
		stmts = instantiate(pc,	 name, DIS_ADDR, DIS_FDS);
	}
	if (tokens.at(0) == "LDDF" ) {
		unsigned addr = magic_process(tokens.at(1));
		unsigned fdd = magic_process(tokens.at(2));
		char *name =  new char[tokens.at(0).length() + 1];
		strcpy(name, tokens.at(0).c_str());
		stmts = instantiate(pc,	 name, DIS_ADDR, DIS_FDD);
	}
	if (tokens.at(0) == "LDSBA" || tokens.at(0) == "LDSHA" || tokens.at(0) == "LDUBA" || tokens.at(0) == "LDUHA" || tokens.at(0) == "LDA" || tokens.at(0) == "LDSTUBA" || tokens.at(0) == "SWAPA" || tokens.at(0) == "LDDA") {
		unsigned addr = magic_process(tokens.at(1));
		unsigned asi = magic_process(tokens.at(2));
		unsigned rd = magic_process(tokens.at(3));
		char *name =  new char[tokens.at(0).length() + 1];
		strcpy(name, tokens.at(0).c_str());
		unused(asi);
		stmts = instantiate(pc,	 name, DIS_RD, DIS_ADDR);
	}
	if (tokens.at(0) == "STB" || tokens.at(0) == "STH" || tokens.at(0) == "ST" || tokens.at(0) == "STD") {
		unsigned rd = magic_process(tokens.at(1));
		unsigned addr = magic_process(tokens.at(2));
		char *name =  new char[tokens.at(0).length() + 1];
		strcpy(name, tokens.at(0).c_str());
		stmts = instantiate(pc,	 name, DIS_RDR, DIS_ADDR);
	}
	if (tokens.at(0) == "STF" ) {
		unsigned fds = magic_process(tokens.at(1));
		unsigned addr = magic_process(tokens.at(2));
		char *name =  new char[tokens.at(0).length() + 1];
		strcpy(name, tokens.at(0).c_str());
		stmts = instantiate(pc,	 name, DIS_FDS, DIS_ADDR);
	}
	if (tokens.at(0) == "STDF" ) {
		unsigned fdd = magic_process(tokens.at(1));
		unsigned addr = magic_process(tokens.at(2));
		char *name =  new char[tokens.at(0).length() + 1];
		strcpy(name, tokens.at(0).c_str());
		stmts = instantiate(pc,	 name, DIS_FDD, DIS_ADDR);
	}
	if (tokens.at(0) == "STBA" || tokens.at(0) == "STHA" || tokens.at(0) == "STA" || tokens.at(0) == "STDA") {
		unsigned rd = magic_process(tokens.at(1));
		unsigned addr = magic_process(tokens.at(2));
		unsigned asi = magic_process(tokens.at(3));
		char *name =  new char[tokens.at(0).length() + 1];
		strcpy(name, tokens.at(0).c_str());
		unused(asi);
		stmts = instantiate(pc,	 name, DIS_RDR, DIS_ADDR);
	}
	if (tokens.at(0) == "LDFSR" ) {
		unsigned addr = magic_process(tokens.at(1));
		char *name =  new char[tokens.at(0).length() + 1];
		strcpy(name, tokens.at(0).c_str());
		stmts = instantiate(pc,	 name, DIS_ADDR);
	}
	if (tokens.at(0) == "LDCSR" ) {
		unsigned addr = magic_process(tokens.at(1));
		char *name =  new char[tokens.at(0).length() + 1];
		strcpy(name, tokens.at(0).c_str());
		stmts = instantiate(pc,	 name, DIS_ADDR);
	}
	if (tokens.at(0) == "STFSR" ) {
		unsigned addr = magic_process(tokens.at(1));
		char *name =  new char[tokens.at(0).length() + 1];
		strcpy(name, tokens.at(0).c_str());
		stmts = instantiate(pc,	 name, DIS_ADDR);
	}
	if (tokens.at(0) == "STCSR" ) {
		unsigned addr = magic_process(tokens.at(1));
		char *name =  new char[tokens.at(0).length() + 1];
		strcpy(name, tokens.at(0).c_str());
		stmts = instantiate(pc,	 name, DIS_ADDR);
	}
	if (tokens.at(0) == "STDFQ" ) {
		unsigned addr = magic_process(tokens.at(1));
		char *name =  new char[tokens.at(0).length() + 1];
		strcpy(name, tokens.at(0).c_str());
		stmts = instantiate(pc,	 name, DIS_ADDR);
	}
	if (tokens.at(0) == "STDCQ" ) {
		unsigned addr = magic_process(tokens.at(1));
		char *name =  new char[tokens.at(0).length() + 1];
		strcpy(name, tokens.at(0).c_str());
		stmts = instantiate(pc,	 name, DIS_ADDR);
	}
	if (tokens.at(0) == "RDY" ) {
		unsigned rd = magic_process(tokens.at(1));
		char *name =  new char[tokens.at(0).length() + 1];
		strcpy(name, tokens.at(0).c_str());
		stmts = instantiate(pc,	 name, DIS_RD);
	}
	if (tokens.at(0) == "RDPSR" ) {
		unsigned rd = magic_process(tokens.at(1));
		char *name =  new char[tokens.at(0).length() + 1];
		strcpy(name, tokens.at(0).c_str());
		stmts = instantiate(pc,	 name, DIS_RD);
	}
	if (tokens.at(0) == "RDWIM" ) {
		unsigned rd = magic_process(tokens.at(1));
		char *name =  new char[tokens.at(0).length() + 1];
		strcpy(name, tokens.at(0).c_str());
		stmts = instantiate(pc,	 name, DIS_RD);
	}
	if (tokens.at(0) == "RDTBR" ) {
		unsigned rd = magic_process(tokens.at(1));
		char *name =  new char[tokens.at(0).length() + 1];
		strcpy(name, tokens.at(0).c_str());
		stmts = instantiate(pc,	 name, DIS_RD);
	}
	if (tokens.at(0) == "WRY" ) {
		unsigned rs1 = magic_process(tokens.at(1));
		unsigned roi = magic_process(tokens.at(2));
		char *name =  new char[tokens.at(0).length() + 1];
		strcpy(name, tokens.at(0).c_str());
		stmts = instantiate(pc,	 name, DIS_RS1, DIS_ROI);
	}
	if (tokens.at(0) == "WRPSR" ) {
		unsigned rs1 = magic_process(tokens.at(1));
		unsigned roi = magic_process(tokens.at(2));
		char *name =  new char[tokens.at(0).length() + 1];
		strcpy(name, tokens.at(0).c_str());
		stmts = instantiate(pc,	 name, DIS_RS1, DIS_ROI);
	}
	if (tokens.at(0) == "WRWIM" ) {
		unsigned rs1 = magic_process(tokens.at(1));
		unsigned roi = magic_process(tokens.at(2));
		char *name =  new char[tokens.at(0).length() + 1];
		strcpy(name, tokens.at(0).c_str());
		stmts = instantiate(pc,	 name, DIS_RS1, DIS_ROI);
	}
	if (tokens.at(0) == "WRTBR" ) {
		unsigned rs1 = magic_process(tokens.at(1));
		unsigned roi = magic_process(tokens.at(2));
		char *name =  new char[tokens.at(0).length() + 1];
		strcpy(name, tokens.at(0).c_str());
		stmts = instantiate(pc,	 name, DIS_RS1, DIS_ROI);
	}
	if (tokens.at(0) == "AND" || tokens.at(0) == "ANDcc" || tokens.at(0) == "ANDN" || tokens.at(0) == "ANDNcc" || tokens.at(0) == "OR" || tokens.at(0) == "ORcc" || tokens.at(0) == "ORN" || tokens.at(0) == "ORNcc" || tokens.at(0) == "XOR" || tokens.at(0) == "XORcc" || tokens.at(0) == "XNOR" || tokens.at(0) == "XNORcc" || tokens.at(0) == "SLL" || tokens.at(0) == "SRL" || tokens.at(0) == "SRA" || tokens.at(0) == "ADD" || tokens.at(0) == "ADDcc" || tokens.at(0) == "ADDX" || tokens.at(0) == "ADDXcc" || tokens.at(0) == "TADDcc" || tokens.at(0) == "TADDccTV" || tokens.at(0) == "SUB" || tokens.at(0) == "SUBcc" || tokens.at(0) == "SUBX" || tokens.at(0) == "SUBXcc" || tokens.at(0) == "TSUBcc" || tokens.at(0) == "TSUBccTV" || tokens.at(0) == "MULScc" || tokens.at(0) == "UMUL" || tokens.at(0) == "SMUL" || tokens.at(0) == "UMULcc" || tokens.at(0) == "SMULcc" || tokens.at(0) == "UDIV" || tokens.at(0) == "SDIV" || tokens.at(0) == "UDIVcc" || tokens.at(0) == "SDIVcc" || tokens.at(0) == "SAVE" || tokens.at(0) == "RESTORE") {
		unsigned rs1 = magic_process(tokens.at(1));
		unsigned roi = magic_process(tokens.at(2));
		unsigned rd = magic_process(tokens.at(3));
		char *name =  new char[tokens.at(0).length() + 1];
		strcpy(name, tokens.at(0).c_str());
		stmts = instantiate(pc,	 name, DIS_RS1, DIS_ROI, DIS_RD);
	}
	if (tokens.at(0) == "FMOVs" || tokens.at(0) == "FNEGs" || tokens.at(0) == "FABSs" || tokens.at(0) == "FSQRTs") {
		unsigned fs2s = magic_process(tokens.at(1));
		unsigned fds = magic_process(tokens.at(2));
		char *name =  new char[tokens.at(0).length() + 1];
		strcpy(name, tokens.at(0).c_str());
		stmts = instantiate(pc,	 name, DIS_FS2S, DIS_FDS);
	}
	if (tokens.at(0) == "FADDs" || tokens.at(0) == "FSUBs" || tokens.at(0) == "FMULs" || tokens.at(0) == "FDIVs") {
		unsigned fs1s = magic_process(tokens.at(1));
		unsigned fs2s = magic_process(tokens.at(2));
		unsigned fds = magic_process(tokens.at(3));
		char *name =  new char[tokens.at(0).length() + 1];
		strcpy(name, tokens.at(0).c_str());
		stmts = instantiate(pc,	 name, DIS_FS1S, DIS_FS2S, DIS_FDS);
	}
	if (tokens.at(0) == "FADDd" || tokens.at(0) == "FSUBd" || tokens.at(0) == "FMULd" || tokens.at(0) == "FDIVd") {
		unsigned fs1d = magic_process(tokens.at(1));
		unsigned fs2d = magic_process(tokens.at(2));
		unsigned fdd = magic_process(tokens.at(3));
		char *name =  new char[tokens.at(0).length() + 1];
		strcpy(name, tokens.at(0).c_str());
		stmts = instantiate(pc,	 name, DIS_FS1D, DIS_FS2D, DIS_FDD);
	}
	if (tokens.at(0) == "FADDq" || tokens.at(0) == "FSUBq" || tokens.at(0) == "FMULq" || tokens.at(0) == "FDIVq") {
		unsigned fs1q = magic_process(tokens.at(1));
		unsigned fs2q = magic_process(tokens.at(2));
		unsigned fdq = magic_process(tokens.at(3));
		char *name =  new char[tokens.at(0).length() + 1];
		strcpy(name, tokens.at(0).c_str());
		stmts = instantiate(pc,	 name, DIS_FS1Q, DIS_FS2Q, DIS_FDQ);
	}
	if (tokens.at(0) == "FCMPs" || tokens.at(0) == "FCMPEs") {
		unsigned fs1s = magic_process(tokens.at(1));
		unsigned fs2s = magic_process(tokens.at(2));
		char *name =  new char[tokens.at(0).length() + 1];
		strcpy(name, tokens.at(0).c_str());
		stmts = instantiate(pc,	 name, DIS_FS1S, DIS_FS2S);
	}
	if (tokens.at(0) == "FCMPd" || tokens.at(0) == "FCMPEd") {
		unsigned fs1d = magic_process(tokens.at(1));
		unsigned fs2d = magic_process(tokens.at(2));
		char *name =  new char[tokens.at(0).length() + 1];
		strcpy(name, tokens.at(0).c_str());
		stmts = instantiate(pc,	 name, DIS_FS1D, DIS_FS2D);
	}
	if (tokens.at(0) == "FCMPq" || tokens.at(0) == "FCMPEq") {
		unsigned fs1q = magic_process(tokens.at(1));
		unsigned fs2q = magic_process(tokens.at(2));
		char *name =  new char[tokens.at(0).length() + 1];
		strcpy(name, tokens.at(0).c_str());
		stmts = instantiate(pc,	 name, DIS_FS1Q, DIS_FS2Q);
	}
	if (tokens.at(0) == "FiTOs" || tokens.at(0) == "FsTOi") {
		unsigned fs2s = magic_process(tokens.at(1));
		unsigned fds = magic_process(tokens.at(2));
		char *name =  new char[tokens.at(0).length() + 1];
		strcpy(name, tokens.at(0).c_str());
		stmts = instantiate(pc, name, DIS_FS2S, DIS_FDS);
	}
	if (tokens.at(0) == "FiTOd" ) {
		unsigned fs2s = magic_process(tokens.at(1));
		unsigned fdd = magic_process(tokens.at(2));
		char *name =  new char[tokens.at(0).length() + 1];
		strcpy(name, tokens.at(0).c_str());
		stmts = instantiate(pc, name, DIS_FS2S, DIS_FDD);
	}
	if (tokens.at(0) == "FdTOi" ) {
		unsigned fs2d = magic_process(tokens.at(1));
		unsigned fds = magic_process(tokens.at(2));
		char *name =  new char[tokens.at(0).length() + 1];
		strcpy(name, tokens.at(0).c_str());
		stmts = instantiate(pc, name, DIS_FS2D, DIS_FDS);
	}
	if (tokens.at(0) == "FiTOq" ) {
		unsigned fs2s = magic_process(tokens.at(1));
		unsigned fdq = magic_process(tokens.at(2));
		char *name =  new char[tokens.at(0).length() + 1];
		strcpy(name, tokens.at(0).c_str());
		stmts = instantiate(pc, name, DIS_FS2S, DIS_FDQ);
	}
	if (tokens.at(0) == "FqTOi" ) {
		unsigned fs2q = magic_process(tokens.at(1));
		unsigned fds = magic_process(tokens.at(2));
		char *name =  new char[tokens.at(0).length() + 1];
		strcpy(name, tokens.at(0).c_str());
		stmts = instantiate(pc, name, DIS_FS2Q, DIS_FDS);
	}
	if (tokens.at(0) == "FsTOd" ) {
		unsigned fs2s = magic_process(tokens.at(1));
		unsigned fdd = magic_process(tokens.at(2));
		char *name =  new char[tokens.at(0).length() + 1];
		strcpy(name, tokens.at(0).c_str());
		stmts = instantiate(pc, name, DIS_FS2S, DIS_FDD);
	}
	if (tokens.at(0) == "FdTOs" ) {
		unsigned fs2d = magic_process(tokens.at(1));
		unsigned fds = magic_process(tokens.at(2));
		char *name =  new char[tokens.at(0).length() + 1];
		strcpy(name, tokens.at(0).c_str());
		stmts = instantiate(pc, name, DIS_FS2D, DIS_FDS);
	}
	if (tokens.at(0) == "FsTOq" ) {
		unsigned fs2s = magic_process(tokens.at(1));
		unsigned fdq = magic_process(tokens.at(2));
		char *name =  new char[tokens.at(0).length() + 1];
		strcpy(name, tokens.at(0).c_str());
		stmts = instantiate(pc, name, DIS_FS2S, DIS_FDQ);
	}
	if (tokens.at(0) == "FqTOs" ) {
		unsigned fs2q = magic_process(tokens.at(1));
		unsigned fds = magic_process(tokens.at(2));
		char *name =  new char[tokens.at(0).length() + 1];
		strcpy(name, tokens.at(0).c_str());
		stmts = instantiate(pc, name, DIS_FS2Q, DIS_FDS);
	}
	if (tokens.at(0) == "FdTOq" ) {
		unsigned fs2d = magic_process(tokens.at(1));
		unsigned fdq = magic_process(tokens.at(2));
		char *name =  new char[tokens.at(0).length() + 1];
		strcpy(name, tokens.at(0).c_str());
		stmts = instantiate(pc, name, DIS_FS2D, DIS_FDQ);
	}
	if (tokens.at(0) == "FqTOd" ) {
		unsigned fs2q = magic_process(tokens.at(1));
		unsigned fdd = magic_process(tokens.at(2));
		char *name =  new char[tokens.at(0).length() + 1];
		strcpy(name, tokens.at(0).c_str());
		stmts = instantiate(pc, name, DIS_FS2Q, DIS_FDD);
	}
	if (tokens.at(0) == "FSQRTd" ) {
		unsigned fs2d = magic_process(tokens.at(1));
		unsigned fdd = magic_process(tokens.at(2));
		char *name =  new char[tokens.at(0).length() + 1];
		strcpy(name, tokens.at(0).c_str());
		stmts = instantiate(pc, name, DIS_FS2D, DIS_FDD);
	}
	if (tokens.at(0) == "FSQRTq" ) {
		unsigned fs2q = magic_process(tokens.at(1));
		unsigned fdq = magic_process(tokens.at(2));
		char *name =  new char[tokens.at(0).length() + 1];
		strcpy(name, tokens.at(0).c_str());
		stmts = instantiate(pc, name, DIS_FS2Q, DIS_FDQ);
	}
	if (tokens.at(0) == "RETURN" ) {
		unsigned addr = magic_process(tokens.at(1));
		char *name =  new char[tokens.at(0).length() + 1];
		strcpy(name, tokens.at(0).c_str());
		stmts = instantiate(pc, name, DIS_ADDR);
		result.rtl = new RTL(pc, stmts);
		result.rtl->appendStmt(new ReturnStatement);
		result.type = DD;
	}
	if (tokens.at(0) == "TN" || tokens.at(0) == "TE" || tokens.at(0) == "TLE" || tokens.at(0) == "TL" || tokens.at(0) == "TLEU" || tokens.at(0) == "TCS" || tokens.at(0) == "TNEG" || tokens.at(0) == "TVS" || tokens.at(0) == "TA" || tokens.at(0) == "TNE" || tokens.at(0) == "TG" || tokens.at(0) == "TGE" || tokens.at(0) == "TGU" || tokens.at(0) == "TCC" || tokens.at(0) == "TPOS" || tokens.at(0) == "TVC") {
		unsigned addr = magic_process(tokens.at(1));
		char *name =  new char[tokens.at(0).length() + 1];
		strcpy(name, tokens.at(0).c_str());
		stmts = instantiate(pc,	 name, DIS_ADDR);
	}
	if (tokens.at(0) == "UNIMP" ) {
		unsigned n = magic_process(tokens.at(1));
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
	if(pc >=100)
	{
		int i = 100 - pc;
		if(pc >= 4196)
		i = pc - 4294967296;
		Exp* expr = new Const(i);
		return expr;
	}
	else return dis_RegRhs(pc);
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
SparcDecoder::SparcDecoder(Prog* prog) : NJMCDecoder(prog)
{
	std::string file = Boomerang::get()->getProgPath() + "frontend/machine/sparc/sparc.ssl";
	RTLDict.readSSLFile(file.c_str());
}
int SparcDecoder::decodeAssemblyInstruction(unsigned,int)
{
	return 0;
}
