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
	if (name == "R0") return 0;
	else if (name == "R1") return 1;
	else if (name == "R2") return 2;
	else if (name == "R3") return 3;
	else if (name == "R4") return 4;
	else if (name == "R5") return 5;
	else if (name == "R6") return 6;
	else if (name == "R7") return 7;
	else if (name == "A") return 8;
	else if (name == "B") return 9;
	else if (name == "C") return 10;
	else if (name == "DPTR") return 11;
	else if (name == "AB") return 12;
	else if (name == "P0") return 13;
	else if (name == "P1") return 14;
	else if (name == "P2") return 15;
	else if (name == "P3") return 16;
	else if (isInteger(str)) {
		int i = std::atoi((str).c_str());
		if (i < 0) return i;
		else return 100 + i;
	}
}
/*
	Intel 8051 decoder
	Created in 09/11/2015 at HCMUT by Dedo

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
#include "_8051Decoder.h"
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
void _8051Decoder::unused(int x)
{
}
static DecodeResult result;


/*==============================================================================
 * FUNCTION:	   _8051Decoder::decodeInstruction
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
DecodeResult& _8051Decoder::decodeInstruction(ADDRESS pc,std::string line)
{
	static DecodeResult result;
	ADDRESS hostPC = pc+delta;
	int delta = 0;
	result.reset();
	std::list<Statement*>* stmts = NULL;
	std::string sentence = line;
	std::transform(sentence.begin(), sentence.end(),sentence.begin(), ::toupper);
	sentence.erase(std::remove(sentence.begin(), sentence.end(), ','), sentence.end());
	std::istringstream iss(sentence);
	std::vector <std::string> tokens;
	copy(istream_iterator<std::string>(iss),istream_iterator<std::string>(),back_inserter(tokens));
	ADDRESS nextPC = NO_ADDRESS;
	//ADDRESS nextPC = NO_ADDRESS;
	dword MATCH_p = hostPC;
	if (tokens.at(0) == "MOV" || tokens.at(0) == "MOVC" || tokens.at(0) == "MOVX") {
		unsigned op1 = magic_process(tokens.at(1));
		unsigned op2 = magic_process(tokens.at(2));
		if(tokens.at(0) == "MOV")
		{
			if(tokens.at(1) == "@R0")
			{
				if(op2 < 8)
				{
					stmts = instantiate(pc, "MOV_RI0_DIR", Location::regOf(op2));
				}
				else
				if(op2 == 8)
				{
					stmts = instantiate(pc, "MOV_RI0_A");
				}
				else
				if(op2 >= 100 )
				{
					if(op2 < 4000000000)
					stmts = instantiate(pc, "MOV_RI0_IMM" , new Const(op2-100));
					else
					stmts = instantiate(pc,  "MOV_RI0_IMM", new Const(op2-4294967296));
				}
			}
			else
			if(tokens.at(1) == "@R1")
			{
				if(op2 < 8)
				{
					stmts = instantiate(pc, "MOV_RI1_DIR", Location::regOf(op2));
				}
				else
				if(op2 == 8)
				{
					stmts = instantiate(pc, "MOV_RI1_A");
				}
				else
				if(op2 >= 100 )
				{
					if(op2 < 4000000000)
					stmts = instantiate(pc, "MOV_RI1_IMM" , new Const(op2-100));
					else
					stmts = instantiate(pc,  "MOV_RI1_IMM", new Const(op2-4294967296));
				}
			}
			else
			if(op1 < 8)
			{
				std::string name = "MOV_R";
				std::stringstream sstm;
				sstm << name << op1;
				if(op2 < 8 )
				{
					sstm << "_DIR";
					name = sstm.str();
					char *name_ =  new char[name.length() + 1];
					strcpy(name_, name.c_str());
					stmts = instantiate(pc, name_, Location::regOf(op2));
				}
				else
				if(op2 == 8 )
				{
					sstm << "_A";
					name = sstm.str();
					char *name_ =  new char[name.length() + 1];
					strcpy(name_, name.c_str());
					stmts = instantiate(pc, name_);
				}
				else
				if(op2 >= 100 )
				{
					sstm << "_IMM";
					name = sstm.str();
					char *name_ =  new char[name.length() + 1];
					strcpy(name_, name.c_str());
					if(op2 < 4000000000)
					stmts = instantiate(pc, name_ , new Const(op2-100));
					else
					stmts = instantiate(pc, name_, new Const(op2-4294967296));
				}
			}
			else
			if(op1 == 8)
			{
				if(tokens.at(2) == "@R0")
				{
					stmts = instantiate(pc, "MOV_A_RI0");
				}
				else
				if(tokens.at(2) == "@R1")
				{
					stmts = instantiate(pc, "MOV_A_RI1");
				}
				else
				if(op2 < 8)
				{
					std::string name = "MOV_A_R";
					std::stringstream sstm;
					sstm << name << op2;
					name = sstm.str();
					stmts = instantiate(pc, name);
				}
				else
				if(op2 >= 100)
				{
					if(op2 < 4000000000)
					stmts = instantiate(pc, "MOV_A_IMM", new Const(op2-100));
					else
					stmts = instantiate(pc, "MOV_A_IMM", new Const(op2-4294967296));
				}
			}
			else
			if(op1 >= 13 && op1 <= 16 )
			{
				std::string name = "MOV_DIR_";
				std::stringstream sstm;
				sstm << name;
				if(op2 < 8 )
				{
					sstm << "R" << op2;
					name = sstm.str();
					char *name_ =  new char[name.length() + 1];
					strcpy(name_, name.c_str());
					stmts = instantiate(pc, name_, Location::regOf(op1));
				}
				else
				if(op2 == 8 )
				{
					sstm << "A";
					name = sstm.str();
					char *name_ =  new char[name.length() + 1];
					strcpy(name_, name.c_str());
					stmts = instantiate(pc, name_, Location::regOf(op1) );
				}
				else
				if(op2 >= 100 )
				{
					sstm << "_IMM";
					name = sstm.str();
					char *name_ =  new char[name.length() + 1];
					strcpy(name_, name.c_str());
					if(op2 < 4000000000)
					stmts = instantiate(pc, name_ , Location::regOf(op1), new Const(op2-100));
					else
					stmts = instantiate(pc, name_,  Location::regOf(op1), new Const(op2-4294967296));
				}
			}
		}
		else
		if(tokens.at(0) == "MOVC")
		{
			if(tokens.at(4) == "DPTR")
			{
				stmts = instantiate(pc, "MOVC_A_AADDDPTR");
			}
			else
			if(tokens.at(4) == "PC")
			{
				stmts = instantiate(pc, "MOVC_A_AADDPC");
			}
		}
		else
		if(tokens.at(0) == "MOVX")
		{
			if(tokens.at(1) == "@R0")
			{
				stmts = instantiate(pc, "MOVX_RI0_A");
			}
			else
			if(tokens.at(1) == "@R1")
			{
				stmts = instantiate(pc, "MOVX_RI1_A");
			}
			else
			if(op1 == 8)
			{
				if(tokens.at(2) == "@R0")
				{
					stmts = instantiate(pc, "MOVX_A_RI0");
				}
				else
				if(tokens.at(2) == "@R1")
				{
					stmts = instantiate(pc, "MOVX_A_RI1");
				}
				else
				if(tokens.at(2) == "@DPTR")
				{
					stmts = instantiate(pc, "MOVX_A_DPTRA");
				}
			}
		}
	}
	if (tokens.at(0) == "ACALL"tokens.at(0) == "ACALL") {
		unsigned address = magic_process(tokens.at(1));
		bool is_lib = false;
		if(tokens.at(1) == "PRINTF" || tokens.at(1) == "PUTS")
		{
			address = 132912;
			is_lib = true;
		}
		else
		{
			address= 66752;
		}
		CallStatement* newCall = new CallStatement;
		ADDRESS nativeDest = addr - delta;
		newCall->setDest(nativeDest);
		Proc* destProc;
		std::transform(tokens.at(1).begin(), tokens.at(1).end(),tokens.at(1).begin(), ::tolower);
		char *name =  new char[tokens.at(1).length() + 1];
		strcpy(name, tokens.at(1).c_str());
		destProc = prog->newProc(name, nativeDest, is_lib);
		newCall->setDestProc(destProc);
		result.rtl = new RTL(pc, stmts);
		result.rtl->appendStmt(newCall);
		result.type = SD;
	}
	if (tokens.at(0) == "ADD" || tokens.at(0) == "ADDC" || tokens.at(0) == "SUBB") {
		unsigned op1 = magic_process(tokens.at(1));
		unsigned op2 = magic_process(tokens.at(2));
		std::stringstream sstm;
		sstm << tokens.at(0) << "_A_";
		std::string name;
		if(tokens.at(2) == "@R0")
		{
			sstm << "RI0";
			name = sstm.str();
			char *name_ =  new char[name.length() + 1];
			strcpy(name_, name.c_str());
			stmts = instantiate(pc,name_);
		}
		else
		if(tokens.at(2) == "@R1")
		{
			sstm << "RI1";
			name = sstm.str();
			char *name_ =  new char[name.length() + 1];
			strcpy(name_, name.c_str());
			stmts = instantiate(pc,name_);
		}
		else
		if(op2 < 8)
		{
			sstm << "R" << op2;
			name = sstm.str();
			char *name_ =  new char[name.length() + 1];
			strcpy(name_, name.c_str());
			stmts = instantiate(pc, name_);
		}
		else
		if(op2 >= 13 && op2 <= 16)
		{
			sstm << "DIR";
			name = sstm.str();
			char *name_ =  new char[name.length() + 1];
			strcpy(name_, name.c_str());
			stmts = instantiate(pc, name_, Location::regOf(op2));
		}
		else
		if(op2 >= 100)
		{
			sstm << "IMM";
			name = sstm.str();
			char *name_ =  new char[name.length() + 1];
			strcpy(name_, name.c_str());
			if(op2 < 4000000000)
			stmts = instantiate(pc, name_, new Const(op2-100));
			else
			stmts = instantiate(pc, name_, new Const(op2-4294967296));
		}
	}
	if (tokens.at(0) == "NOP" ) {
		result.type = NOP;
		stmts = instantiate(pc,	 "NOP");
	}
	if (tokens.at(0) == "LJMP" || tokens.at(0) == "AJMP" || tokens.at(0) == "SJMP") {
		unsigned address = magic_process(tokens.at(1));
		CaseStatement* jump = new CaseStatement;
		jump->setIsComputed();
		result.rtl = new RTL(pc, stmts);
		result.rtl->appendStmt(jump);
		result.type = DD;
		jump->setDest(address);
	}
	if (tokens.at(0) == "JMP"tokens.at(0) == "JMP") {
		stmts = instantiate(pc,	 "JMP_AADDDPTR");
	}
	if (tokens.at(0) == "RR" || tokens.at(0) == "RRC" || tokens.at(0) == "RLC") {
		unsigned op1 = magic_process(tokens.at(1));
		if(op1 == 8)
		{
			std::stringstream sstm;
			sstm << tokens.at(0) << "_A";
			std::string name;
			name = sstm.str();
			char *name_ =  new char[name.length() + 1];
			strcpy(name_, name.c_str());
			stmts = instantiate(pc,	 name_);
		}
	}
	if (tokens.at(0) == "DEC" || tokens.at(0) == "INC") {
		unsigned o1 = magic_process(tokens.at(1));
		std::stringstream sstm;
		sstm << tokens.at(0) << "_";
		std::string name;
		if(tokens.at(1) == "@R0")
		{
			sstm << "RI0";
			name = sstm.str();
			char *name_ =  new char[name.length() + 1];
			strcpy(name_, name.c_str());
			stmts = instantiate(pc,name_);
		}
		else
		if(tokens.at(1) == "@R1")
		{
			sstm << "RI1";
			name = sstm.str();
			char *name_ =  new char[name.length() + 1];
			strcpy(name_, name.c_str());
			stmts = instantiate(pc,name_);
		}
		else
		if(tokens.at(1) == "DPTR")
		{
			sstm << "DPTR";
			name = sstm.str();
			char *name_ =  new char[name.length() + 1];
			strcpy(name_, name.c_str());
			stmts = instantiate(pc, name_);
		}
		else
		if(op1 < 8)
		{
			sstm << "R" << op1;
			name = sstm.str();
			char *name_ =  new char[name.length() + 1];
			strcpy(name_, name.c_str());
			stmts = instantiate(pc, name_);
		}
		else
		if(op1 == 8)
		{
			sstm << "A";
			name = sstm.str();
			char *name_ =  new char[name.length() + 1];
			strcpy(name_, name.c_str());
			stmts = instantiate(pc, name_);
		}
		else
		if(op1 >= 100)
		{
			sstm << "DIR";
			name = sstm.str();
			char *name_ =  new char[name.length() + 1];
			strcpy(name_, name.c_str());
			if(op2 < 4000000000)
			stmts = instantiate(pc, name_, new Const(op2-100));
			else
			stmts = instantiate(pc, name_, new Const(op2-4294967296));
		}
	}
	if (tokens.at(0) == "JNB" || tokens.at(0) == "JB" || tokens.at(0) == "JBC") {
		unsigned op1 = magic_process(tokens.at(1));
		unsigned op2 = magic_process(tokens.at(2));
		std::stringstream sstm;
		sstm << tokens.at(0) << "_DIR_IMM";
		std::string name;
		name = sstm.str();
		char *name_ =  new char[name.length() + 1];
		strcpy(name_, name.c_str());
		if(op2 < 4000000000)
		stmts = instantiate(pc, name_, Location::regOf(op1), new Const(op2-100));
		else
		stmts = instantiate(pc, name_,  Location::regOf(op1),new Const(op2-4294967296));
	}
	if (tokens.at(0) == "LCALL"tokens.at(0) == "LCALL") {
		unsigned address = magic_process(tokens.at(1));
		bool is_lib = false;
		if(tokens.at(1) == "PRINTF" || tokens.at(1) == "PUTS")
		{
			address = 132912;
			is_lib = true;
		}
		else
		{
			address= 66752;
		}
		CallStatement* newCall = new CallStatement;
		ADDRESS nativeDest = addr - delta;
		newCall->setDest(nativeDest);
		Proc* destProc;
		std::transform(tokens.at(1).begin(), tokens.at(1).end(),tokens.at(1).begin(), ::tolower);
		char *name =  new char[tokens.at(1).length() + 1];
		strcpy(name, tokens.at(1).c_str());
		destProc = prog->newProc(name, nativeDest, is_lib);
		newCall->setDestProc(destProc);
		result.rtl = new RTL(pc, stmts);
		result.rtl->appendStmt(newCall);
		result.type = SD;
	}
	if (tokens.at(0) == "RET" || tokens.at(0) == "RETI") {
		result.rtl = new RTL(pc, stmts);
		result.rtl->appendStmt(new ReturnStatement);
		result.type = DD;
	}
	if (tokens.at(0) == "JC"tokens.at(0) == "JC") {
		unsigned op1 = magic_process(tokens.at(1));
		if(op1 < 4000000000)
		stmts = instantiate(pc, "JC_IMM", new Const(op1-100));
		else
		stmts = instantiate(pc, "JC_IMM", new Const(op1-4294967296));
	}
	if (tokens.at(0) == "JNC"tokens.at(0) == "JNC") {
		unsigned op1 = magic_process(tokens.at(1));
		if(op1 < 4000000000)
		stmts = instantiate(pc, "JC_IMM", new Const(op1-100));
		else
		stmts = instantiate(pc, "JC_IMM", new Const(op1-4294967296));
	}
	if (tokens.at(0) == "ORL" || tokens.at(0) == "ANL" || tokens.at(0) == "XRL") {
		unsigned op1 = magic_process(tokens.at(1));
		unsigned op2 = magic_process(tokens.at(2));
		std::stringstream sstm;
		sstm << tokens.at(0) << "_";
		std::string name;
		if(op1 == 10 )
		{
			sstm << "C_";
			name = sstm.str();
			char *name_ =  new char[name.length() + 1];
			strcpy(name_, name.c_str());
			stmts = instantiate(pc,name_, new Const(op2));
		}
		if(op1 == 8)
		{
			sstm << "A_";
			if(tokens.at(2) == "@R0")
			{
				sstm << "RI0";
				name = sstm.str();
				char *name_ =  new char[name.length() + 1];
				strcpy(name_, name.c_str());
				stmts = instantiate(pc,name_);
			}
			else
			if(tokens.at(2) == "@R1")
			{
				sstm << "RI1";
				name = sstm.str();
				char *name_ =  new char[name.length() + 1];
				strcpy(name_, name.c_str());
				stmts = instantiate(pc,name_);
			}
			else
			if(op2 < 8)
			{
				sstm << "R" << op2;
				name = sstm.str();
				char *name_ =  new char[name.length() + 1];
				strcpy(name_, name.c_str());
				stmts = instantiate(pc, name_);
			}
			else
			if(op2 >= 100)
			{
				sstm << "IMM";
				name = sstm.str();
				char *name_ =  new char[name.length() + 1];
				strcpy(name_, name.c_str());
				if(op2 < 4000000000)
				stmts = instantiate(pc, name_, new Const(op2-100));
				else
				stmts = instantiate(pc, name_, new Const(op2-4294967296));
			}
			else
			if(op2 >= 13 && op2 <= 16)
			{
				sstm << "DIR";
				name = sstm.str();
				char *name_ =  new char[name.length() + 1];
				strcpy(name_, name.c_str());
				stmts = instantiate(pc, name_, Location::regOf(op2));
			}
		}
		else
		if(op1 >= 13 && op1 <= 16 )
		{
			sstm << "DIR_";
			if(op2 == 8)
			{
				sstm << "A";
				stmts = instantiate(pc, name_, Location::regOf(op1));
			}
			else
			if(op2 >= 100)
			{
				sstm << "IMM";
				name = sstm.str();
				char *name_ =  new char[name.length() + 1];
				strcpy(name_, name.c_str());
				if(op2 < 4000000000)
				stmts = instantiate(pc, name_,Location::regOf(op1), new Const(op2-100));
				else
				stmts = instantiate(pc, name_,Location::regOf(op1), new Const(op2-4294967296));
			}
		}
	}
	if (tokens.at(0) == "JZ" || tokens.at(0) == "JNZ") {
		unsigned address = magic_process(tokens.at(1));
		std::stringstream sstm;
		sstm << tokens.at(0) << "_IMM";
		std::string name;
		name = sstm.str();
		char *name_ =  new char[name.length() + 1];
		strcpy(name_, name.c_str());
		stmts = instantiate(pc,name_, new Const(address));
	}
	if (tokens.at(0) == "DIV" || tokens.at(0) == "MUL") {
		unsigned op1 = magic_process(tokens.at(1));
		if(op1 == 12)
		{
			std::stringstream sstm;
			sstm << tokens.at(0) << "_AB";
			std::string name;
			name = sstm.str();
			char *name_ =  new char[name.length() + 1];
			strcpy(name_, name.c_str());
			stmts = instantiate(pc,name_);
		}
	}
	if (tokens.at(0) == "CPL"tokens.at(0) == "CPL") {
		unsigned op1 = magic_process(tokens.at(1));
		if(op1 == 8)
		{
			stmts = instantiate(pc,"CPL_A");
		}
		else
		if(op1 == 10)
		{
			stmts = instantiate(pc,"CPL_C");
		}
		else
		if(op1 >= 100)
		{
			if(op1 < 4000000000)
			stmts = instantiate(pc, "CPL_DIR", new Const(op2-100));
			else
			stmts = instantiate(pc, "CPL_DIR", new Const(op2-4294967296));
		}
	}
	if (tokens.at(0) == "CJNE"tokens.at(0) == "CJNE") {
		unsigned op1 = magic_process(tokens.at(1));
		unsigned op2 = magic_process(tokens.at(2));
		unsigned op3 = magic_process(tokens.at(3));
		if(tokens.at(0) == "@R0")
		{
			if(op2 >= 100 && op3 >= 100)
			{
				int operand2 = 0;
				int operand3 = 0;
				if(op2 < 4000000000)
				operand2 = op2 -100;
				else
				operand2 = op2 - 4294967296;
				if(op3 < 4000000000)
				operand3 = op3 -100;
				else
				operand3 = op3 - 4294967296;
				stmts = instantiate(pc, "CJNE_RI0_IMM_IMM", new Const(operand2), new Const(operand3));
			}
		}
		else
		if(tokens.at(0) == "@R1")
		{
			if(op2 >= 100 && op3 >= 100)
			{
				int operand2 = 0;
				int operand3 = 0;
				if(op2 < 4000000000)
				operand2 = op2 -100;
				else
				operand2 = op2 - 4294967296;
				if(op3 < 4000000000)
				operand3 = op3 -100;
				else
				operand3 = op3 - 4294967296;
				stmts = instantiate(pc, "CJNE_RI1_IMM_IMM", new Const(operand2), new Const(operand3));
			}
		}
		else
		if(op1 < 8)
		{
			std::stringstream sstm;
			sstm << "CJNE_R" << tokens.at(0) << "_IMM_IMM";
			std::string name;
			name = sstm.str();
			char *name_ =  new char[name.length() + 1];
			strcpy(name_, name.c_str());
			if(op2 >= 100 && op3 >= 100)
			{
				int operand2 = 0;
				int operand3 = 0;
				if(op2 < 4000000000)
				operand2 = op2 -100;
				else
				operand2 = op2 - 4294967296;
				if(op3 < 4000000000)
				operand3 = op3 -100;
				else
				operand3 = op3 - 4294967296;
				stmts = instantiate(pc,name_, new Const(operand2), new Const(operand3));
			}
		}
		else
		if(op1 == 8)
		{
			if(op2 >= 100 && op3 >= 100)
			{
				int operand2 = 0;
				int operand3 = 0;
				if(op2 < 4000000000)
				operand2 = op2 -100;
				else
				operand2 = op2 - 4294967296;
				if(op3 < 4000000000)
				operand3 = op3 -100;
				else
				operand3 = op3 - 4294967296;
				stmts = instantiate(pc, "CJNE_A_IMM_IMM", new Const(operand2), new Const(operand3));
			}
			else
			{
			}
		}
	}
	if (tokens.at(0) == "PUSH" || tokens.at(0) == "POP") {
		unsigned op1 = magic_process(tokens.at(1));
		std::stringstream sstm;
		sstm << tokens.at(0) << "_DIR";
		std::string name;
		name = sstm.str();
		char *name_ =  new char[name.length() + 1];
		strcpy(name_, name.c_str());
		if(op1 < 8)
		{
			stmts = instantiate(pc, name_, Location::regOf(op1));
		}
		else
		{
			stmts = instantiate(pc, name_, new Const(op1));
		}
	}
	if (tokens.at(0) == "CLR"tokens.at(0) == "CLR") {
		unsigned op1 = magic_process(tokens.at(1));
		if(op1 == 8)
		{
			stmts = instantiate(pc, "CLR_A");
		}
		else
		if(op1 == 10)
		{
			stmts = instantiate(pc, "CLR_C");
		}
		else
		{
			stmts = instantiate(pc, "CLR_DIR", new Const(op1-100));
		}
	}
	if (tokens.at(0) == "SETB"tokens.at(0) == "SETB") {
		unsigned op1 = magic_process(tokens.at(1));
		else
		if(op1 == 10)
		{
			stmts = instantiate(pc, "SETB_C");
		}
		else
		{
			stmts = instantiate(pc, "SETB_DIR", new Const(op1 - 100));
		}
	}
	if (tokens.at(0) == "SWAP"tokens.at(0) == "SWAP") {
		unsigned op1 = magic_process(tokens.at(1));
		if(op1 == 8)
		{
			stmts = instantiate(pc,"SWAP_A");
		}
	}
	if (tokens.at(0) == "XCH" || tokens.at(0) == "XCHD") {
		unsigned op1 = magic_process(tokens.at(1));
		unsigned op2 = magic_process(tokens.at(2));
		std::stringstream sstm;
		sstm << tokens.at(0) << "_A_";
		std::string name;
		if(op1 == 8)
		{
			if(tokens.at(2) == "@R0")
			{
				sstm << "RI0";
				name = sstm.str();
				char *name_ =  new char[name.length() + 1];
				strcpy(name_, name.c_str());
				stmts = instantiate(pc, name_);
			}
			else
			if(tokens.at(2) == "@R1")
			{
				sstm << "RI1";
				name = sstm.str();
				char *name_ =  new char[name.length() + 1];
				strcpy(name_, name.c_str());
				stmts = instantiate(pc, name_);
			}
			else
			if(op2 < 8)
			{
				sstm << "R" << op2;
				name = sstm.str();
				char *name_ =  new char[name.length() + 1];
				strcpy(name_, name.c_str());
				stmts = instantiate(pc, name_);
			}
			else
			{
				sstm << "DIR";
				name = sstm.str();
				char *name_ =  new char[name.length() + 1];
				strcpy(name_, name.c_str());
				stmts = instantiate(pc, name_, new Const(op2-100));
			}
		}
	}
	if (tokens.at(0) == "DA"tokens.at(0) == "DA") {
		unsigned op1 = magic_process(tokens.at(1));
		if(op1 == 8)
		{
			stmts = instantiate(pc, "DA");
		}
	}
	if (tokens.at(0) == "RL"tokens.at(0) == "RL") {
		unsigned op1 = magic_process(tokens.at(1));
		if(op1 == 8)
		{
			stmts = instantiate(pc, "RL_A");
		}
	}
	else
	{
		stmts = NULL;
		result.valid = false;
		result.numBytes = 4;
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
 * FUNCTION:		_8051Decoder::dis_RegLhs
 * OVERVIEW:		Decode the register on the LHS
 * PARAMETERS:		r - register (0-31)
 * RETURNS:			the expression representing the register
 *============================================================================*/
Exp* _8051Decoder::dis_RegLhs(unsigned r)
{
	return Location::regOf(r);
}
/*==============================================================================
 * FUNCTION:		_8051Decoder::dis_RegRhs
 * OVERVIEW:		Decode the register on the RHS
 * NOTE:			Replaces r[0] with const 0
 * NOTE:			Not used by DIS_RD since don't want 0 on LHS
 * PARAMETERS:		r - register (0-31)
 * RETURNS:			the expression representing the register
 *============================================================================*/
Exp* _8051Decoder::dis_RegRhs(unsigned r)
{
	if(r == 0)
	return new Const(0);
	return Location::regOf(r);
}
/*==============================================================================
 * FUNCTION:		_8051Decoder::dis_RegImm
 * OVERVIEW:		Decode the register or immediate at the given address.
 * NOTE:			Used via macro DIS_ROI
 * PARAMETERS:		pc - an address in the instruction stream
 * RETURNS:			the register or immediate at the given address
 *============================================================================*/
Exp* _8051Decoder::dis_RegImm(unsigned pc)
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
 * FUNCTION:		_8051Decoder::dis_Eaddr
 * OVERVIEW:		Converts a dynamic address to a Exp* expression.
 *					E.g. %o7 --> r[ 15 ]
 * PARAMETERS:		pc - the instruction stream address of the dynamic address
 *					ignore - redundant parameter on 8051
 * RETURNS:			the Exp* representation of the given address
 *============================================================================*/
Exp* _8051Decoder::dis_Eaddr(ADDRESS pc,int ignore)
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
bool _8051Decoder::isFuncPrologue(ADDRESS hostPC)
{
	return false;
}
/*==============================================================================
 * FUNCTION:	  isRestore()
 * OVERVIEW:	  Check to see if the instruction at the given offset is a restore instruction
 * PARAMETERS:	  hostPC - pointer to the code in question (host address)
 * RETURNS:		  True if a match found
 *============================================================================*/
bool _8051Decoder::isRestore(ADDRESS hostPC)
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
DWord _8051Decoder::getDword(ADDRESS lc)
{
	Byte* p = (Byte*)lc;
	return (p[0] << 24) + (p[1] << 16) + (p[2] << 8) + p[3];
}
/*==============================================================================
 * FUNCTION:	   _8051Decoder::_8051Decoder
 * OVERVIEW:	   
 * PARAMETERS:	   None
 * RETURNS:		   N/A
 *============================================================================*/
_8051Decoder::_8051Decoder(Prog* prog) : NJMCDecoder(prog)
{
	std::string file = Boomerang::get()->getProgPath() + "frontend/machine/8051/_8051.ssl";
	RTLDict.readSSLFile(file.c_str());
}
int _8051Decoder::decodeAssemblyInstruction(unsigned,int)
{
	return 0;
}
