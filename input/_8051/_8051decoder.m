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
#include "BinaryFile.h"		// For SymbolByAddress()
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
{}
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
DecodeResult& _8051Decoder::decodeInstruction (ADDRESS pc, std::string line) { 
	static DecodeResult result;
	ADDRESS hostPC = pc+delta;
	int delta = 0;
	// Clear the result structure;
	result.reset();

	// The actual list of instantiated statements
	std::list<Statement*>* stmts = NULL;
	std::string sentence = line;
    std::transform(sentence.begin(), sentence.end(),sentence.begin(), ::toupper);
    sentence.erase(std::remove(sentence.begin(), sentence.end(), ','), sentence.end());
    std::istringstream iss(sentence);
    std::vector <std::string> tokens;
    copy(istream_iterator<std::string>(iss),istream_iterator<std::string>(),back_inserter(tokens));

	ADDRESS nextPC = NO_ADDRESS;

	match [nextPC] hostPC to

	| mov_ (op1,op2) =>
		if(tokens.at(0) == "MOV"){
			if (tokens.at(1) == "@R0"){ // Indirect R0
				if (op2 < 8){ //Direct
					stmts = instantiate(pc, "MOV_RI0_DIR", Location::regOf(op2));
				}
				else if (op2 == 8){
					stmts = instantiate(pc, "MOV_RI0_A");
				}
				else if (op2 >= 100 ){ // Immediate
					if (op2 < 4000000000)
						stmts = instantiate(pc, "MOV_RI0_IMM" , new Const(op2-100)); // Immediate positive integer
					else
						stmts = instantiate(pc,  "MOV_RI0_IMM", new Const(op2-4294967296)); // Immediate Negative Integer
				}
			}
			else if (tokens.at(1) == "@R1"){ // Indirect R1
				if (op2 < 8){ //Direct
					stmts = instantiate(pc, "MOV_RI1_DIR", Location::regOf(op2));
				}
				else if (op2 == 8){
					stmts = instantiate(pc, "MOV_RI1_A");
				}
				else if (op2 >= 100 ){ // Immediate
					if (op2 < 4000000000)
						stmts = instantiate(pc, "MOV_RI1_IMM" , new Const(op2-100)); // Immediate positive integer
					else
						stmts = instantiate(pc,  "MOV_RI1_IMM", new Const(op2-4294967296)); // Immediate Negative Integer
				}	
			}
			else if (op1 < 8){ // MOV Rn, *
				std::string name = "MOV_R";
				std::stringstream sstm;
				sstm << name << op1;
				if (op2 < 8 ){ // Direct
					sstm << "_DIR";
					name = sstm.str();
					char *name_ =  new char[name.length() + 1];
    				strcpy(name_, name.c_str());
					stmts = instantiate(pc, name_, Location::regOf(op2));
				}
				else if(op2 == 8 ){ //MOV_R*_A Accumulate
					sstm << "_A";
					name = sstm.str();
					char *name_ =  new char[name.length() + 1];
    				strcpy(name_, name.c_str());
					stmts = instantiate(pc, name_);
				}
				else if (op2 >= 100 ){ // Immediate
					sstm << "_IMM";
					name = sstm.str();
					char *name_ =  new char[name.length() + 1];
    				strcpy(name_, name.c_str());
					if (op2 < 4000000000)
						stmts = instantiate(pc, name_ , new Const(op2-100)); // Immediate positive integer
					else
						stmts = instantiate(pc, name_, new Const(op2-4294967296)); // Immediate Negative Integer
				}

			}
			else if (op1 == 8){ // MOV A, *
				if (tokens.at(2) == "@R0"){ // Indirect R0
					stmts = instantiate(pc, "MOV_A_RI0");
				}
				else if (tokens.at(2) == "@R1"){ // Indirect R1
					stmts = instantiate(pc, "MOV_A_RI1");
				} 
				else if(op2 < 8){ //Rn R0-R7 or 
					std::string name = "MOV_A_R";
					std::stringstream sstm;
					sstm << name << op2;
					name = sstm.str();
					stmts = instantiate(pc, name);
				}
				else if (op2 >= 100){ // Immediate positive integer
					if (op2 < 4000000000)
						stmts = instantiate(pc, "MOV_A_IMM", new Const(op2-100));
					else 
						stmts = instantiate(pc, "MOV_A_IMM", new Const(op2-4294967296));
				}
				
			}
			else if (op1 >= 13 && op1 <= 16 ){
				std::string name = "MOV_DIR_";
				std::stringstream sstm;
				sstm << name;
				if (op2 < 8 ){ // Direct
					sstm << "R" << op2;
					name = sstm.str();
					char *name_ =  new char[name.length() + 1];
    				strcpy(name_, name.c_str());
					stmts = instantiate(pc, name_, Location::regOf(op1));
				}
				else if(op2 == 8 ){ //MOV_R*_A Accumulate
					sstm << "A";
					name = sstm.str();
					char *name_ =  new char[name.length() + 1];
    				strcpy(name_, name.c_str());
					stmts = instantiate(pc, name_, Location::regOf(op1) );
				}
				else if (op2 >= 100 ){ // Immediate
					sstm << "_IMM";
					name = sstm.str();
					char *name_ =  new char[name.length() + 1];
    				strcpy(name_, name.c_str());
					if (op2 < 4000000000)

						stmts = instantiate(pc, name_ , Location::regOf(op1), new Const(op2-100)); // Immediate positive integer
					else
						stmts = instantiate(pc, name_,  Location::regOf(op1), new Const(op2-4294967296)); // Immediate Negative Integer
				}

			}
		}
		else if (tokens.at(0) == "MOVC"){
			if (tokens.at(4) == "DPTR"){
				stmts = instantiate(pc, "MOVC_A_AADDDPTR");
			}
			else if (tokens.at(4) == "PC"){
				stmts = instantiate(pc, "MOVC_A_AADDPC");
			}
		}
		else if (tokens.at(0) == "MOVX"){
			if (tokens.at(1) == "@R0"){
				stmts = instantiate(pc, "MOVX_RI0_A");
			}
			else if (tokens.at(1) == "@R1"){
				stmts = instantiate(pc, "MOVX_RI1_A");
			}
			else if (op1 == 8){
				if(tokens.at(2) == "@R0"){
					stmts = instantiate(pc, "MOVX_A_RI0");
				}
				else if (tokens.at(2) == "@R1"){
					stmts = instantiate(pc, "MOVX_A_RI1");
				}
				else if (tokens.at(2) == "@DPTR"){
					stmts = instantiate(pc, "MOVX_A_DPTRA");
				} 
			}
		}
		
	| ACALL (address) =>
		bool is_lib = false;
	    if (tokens.at(1) == "PRINTF" || tokens.at(1) == "PUTS"){
	      address = 132912;
	      is_lib = true;
	    }
	    else {
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

	| add_ (op1,op2) =>

    	std::stringstream sstm;
    	sstm << tokens.at(0) << "_A_";
    	std::string name;
    	if (tokens.at(2) == "@R0"){
    		sstm << "RI0";
    		name = sstm.str();
    		char *name_ =  new char[name.length() + 1];
    		strcpy(name_, name.c_str());
    		stmts = instantiate(pc,name_);
    	}
    	else if (tokens.at(2) == "@R1"){
    		sstm << "RI1";
    		name = sstm.str();
    		char *name_ =  new char[name.length() + 1];
    		strcpy(name_, name.c_str());
    		stmts = instantiate(pc,name_);
    	}
    	else if(op2 < 8){
    		sstm << "R" << op2;
    		name = sstm.str();
    		char *name_ =  new char[name.length() + 1];
    		strcpy(name_, name.c_str());
			stmts = instantiate(pc, name_);
    	}
    	else if (op2 >= 13 && op2 <= 16){
    		sstm << "DIR";
    		name = sstm.str();
    		char *name_ =  new char[name.length() + 1];
    		strcpy(name_, name.c_str());
    		stmts = instantiate(pc, name_, Location::regOf(op2));
    	}
    	else if (op2 >= 100){
    		sstm << "IMM";
    		name = sstm.str();
    		char *name_ =  new char[name.length() + 1];
    		strcpy(name_, name.c_str());
			if (op2 < 4000000000)
				stmts = instantiate(pc, name_, new Const(op2-100)); // Immediate positive integer
			else
				stmts = instantiate(pc, name_, new Const(op2-4294967296)); // Immediate Negative Integer
    	}

    | NOP =>
		result.type = NOP;
		stmts = instantiate(pc,	 "NOP");

	| _JMP (address) =>
		CaseStatement* jump = new CaseStatement;
		// Record the fact that it is a computed jump
		jump->setIsComputed();
		result.rtl = new RTL(pc, stmts);
		result.rtl->appendStmt(jump);
		result.type = DD;
		jump->setDest(address);

	| JMP =>
		stmts = instantiate(pc,	 "JMP_AADDDPTR");

	| rr (op1) =>
		if (op1 == 8){
			std::stringstream sstm;
	    	sstm << tokens.at(0) << "_A";
	    	std::string name;
	    	name = sstm.str();
	    	char *name_ =  new char[name.length() + 1];
    		strcpy(name_, name.c_str());
			stmts = instantiate(pc,	 name_);
		}

	| inst_1 (o1) =>
	    std::stringstream sstm;
    	sstm << tokens.at(0) << "_";
    	std::string name;
    	if (tokens.at(1) == "@R0"){
    		sstm << "RI0";
    		name = sstm.str();
    		char *name_ =  new char[name.length() + 1];
    		strcpy(name_, name.c_str());
    		stmts = instantiate(pc,name_);
    	}
    	else if (tokens.at(1) == "@R1"){
    		sstm << "RI1";
    		name = sstm.str();
    		char *name_ =  new char[name.length() + 1];
    		strcpy(name_, name.c_str());
    		stmts = instantiate(pc,name_);
    	}
    	else if (tokens.at(1) == "DPTR"){
    		sstm << "DPTR";
    		name = sstm.str();
    		char *name_ =  new char[name.length() + 1];
    		strcpy(name_, name.c_str());
    		stmts = instantiate(pc, name_);
    	}
    	else if(op1 < 8){
    		sstm << "R" << op1;
    		name = sstm.str();
    		char *name_ =  new char[name.length() + 1];
    		strcpy(name_, name.c_str());
			stmts = instantiate(pc, name_);
    	}
    	else if (op1 == 8){
    		sstm << "A";
    		name = sstm.str();
    		char *name_ =  new char[name.length() + 1];
    		strcpy(name_, name.c_str());
			stmts = instantiate(pc, name_);
    	}  	
    	else if (op1 >= 100){
    		sstm << "DIR";
    		name = sstm.str();
    		char *name_ =  new char[name.length() + 1];
    		strcpy(name_, name.c_str());
			if (op2 < 4000000000)
				stmts = instantiate(pc, name_, new Const(op2-100)); // Immediate positive integer
			else
				stmts = instantiate(pc, name_, new Const(op2-4294967296)); // Immediate Negative Integer
    	}

    | jb_ (op1, op2) =>
        std::stringstream sstm;
    	sstm << tokens.at(0) << "_DIR_IMM";
    	std::string name;
		name = sstm.str();
		char *name_ =  new char[name.length() + 1];
		strcpy(name_, name.c_str());
		if (op2 < 4000000000)
			stmts = instantiate(pc, name_, Location::regOf(op1), new Const(op2-100)); // Immediate positive integer
		else
			stmts = instantiate(pc, name_,  Location::regOf(op1),new Const(op2-4294967296)); // Immediate Negative Integer
    	
	| LCALL (address) =>
		bool is_lib = false;
	    if (tokens.at(1) == "PRINTF" || tokens.at(1) == "PUTS"){
	      address = 132912;
	      is_lib = true;
	    }
	    else {
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

	| ret =>
		result.rtl = new RTL(pc, stmts);
		result.rtl->appendStmt(new ReturnStatement);
		result.type = DD;

	| JC (op1) =>
		if (op1 < 4000000000)
			stmts = instantiate(pc, "JC_IMM", new Const(op1-100)); // Immediate positive integer
		else
			stmts = instantiate(pc, "JC_IMM", new Const(op1-4294967296)); // Immediate Negative Integer

	| JNC (op1) =>
		if (op1 < 4000000000)
			stmts = instantiate(pc, "JC_IMM", new Const(op1-100)); // Immediate positive integer
		else
			stmts = instantiate(pc, "JC_IMM", new Const(op1-4294967296)); // Immediate Negative Integer	

	| logical (op1,op2) =>

		std::stringstream sstm;
    	sstm << tokens.at(0) << "_";
    	std::string name;
 		if(op1 == 10 ){
 			sstm << "C_";
 			name = sstm.str();
    		char *name_ =  new char[name.length() + 1];
    		strcpy(name_, name.c_str());
    		stmts = instantiate(pc,name_, new Const(op2));
 		}
    	if (op1 == 8){
    		sstm << "A_";
    		if (tokens.at(2) == "@R0"){
    		sstm << "RI0";
    		name = sstm.str();
    		char *name_ =  new char[name.length() + 1];
    		strcpy(name_, name.c_str());
    		stmts = instantiate(pc,name_);
	    	}
	    	else if (tokens.at(2) == "@R1"){
	    		sstm << "RI1";
	    		name = sstm.str();
	    		char *name_ =  new char[name.length() + 1];
	    		strcpy(name_, name.c_str());
	    		stmts = instantiate(pc,name_);
	    	}
	    	else if(op2 < 8){
	    		sstm << "R" << op2;
	    		name = sstm.str();
	    		char *name_ =  new char[name.length() + 1];
	    		strcpy(name_, name.c_str());
				stmts = instantiate(pc, name_);
    		}
    		else if (op2 >= 100){
	    		sstm << "IMM";
	    		name = sstm.str();
	    		char *name_ =  new char[name.length() + 1];
	    		strcpy(name_, name.c_str());
				if (op2 < 4000000000)
					stmts = instantiate(pc, name_, new Const(op2-100)); // Immediate positive integer
				else
					stmts = instantiate(pc, name_, new Const(op2-4294967296)); // Immediate Negative Integer
    		}
    		else if (op2 >= 13 && op2 <= 16){ // NOT SURE
	    		sstm << "DIR";
	    		name = sstm.str();
	    		char *name_ =  new char[name.length() + 1];
	    		strcpy(name_, name.c_str());
	    		stmts = instantiate(pc, name_, Location::regOf(op2));
	    	}
    	}
    	else if (op1 >= 13 && op1 <= 16 ){
    		sstm << "DIR_";
    		if (op2 == 8){
    			sstm << "A";
    			stmts = instantiate(pc, name_, Location::regOf(op1));
    		}
    		else if (op2 >= 100){
	    		sstm << "IMM";
	    		name = sstm.str();
	    		char *name_ =  new char[name.length() + 1];
	    		strcpy(name_, name.c_str());
				if (op2 < 4000000000)
					stmts = instantiate(pc, name_,Location::regOf(op1), new Const(op2-100)); // Immediate positive integer
				else
					stmts = instantiate(pc, name_,Location::regOf(op1), new Const(op2-4294967296)); // Immediate Negative Integer
    		}
    	}

    | jz_ (address) =>  // NOT SURE
    	std::stringstream sstm;
    	sstm << tokens.at(0) << "_IMM";
    	std::string name;
    	name = sstm.str();
    	char *name_ =  new char[name.length() + 1];
    	strcpy(name_, name.c_str());
    	stmts = instantiate(pc,name_, new Const(address));

    | div_mul (op1) =>
    	if (op1 == 12){
	    	std::stringstream sstm;
	    	sstm << tokens.at(0) << "_AB";
	    	std::string name;
	    	name = sstm.str();
	    	char *name_ =  new char[name.length() + 1];
	    	strcpy(name_, name.c_str());
	    	stmts = instantiate(pc,name_);
    	}
    | CPL (op1) =>

    	if (op1 == 8){
    		stmts = instantiate(pc,"CPL_A");
    	}
    	else if (op1 == 10){
    		stmts = instantiate(pc,"CPL_C");
    	}
    	else if (op1 >= 100){
    		if (op1 < 4000000000)
					stmts = instantiate(pc, "CPL_DIR", new Const(op2-100)); // Immediate positive integer
			else
				stmts = instantiate(pc, "CPL_DIR", new Const(op2-4294967296)); // Immediate Negative Integer
    	}

    | CJNE (op1, op2, op3) =>

    	if (tokens.at(0) == "@R0"){

    		if (op2 >= 100 && op3 >= 100){
    			int operand2 = 0;
    			int operand3 = 0;

	    		if (op2 < 4000000000)
					operand2 = op2 -100;
				else
					operand2 = op2 - 4294967296;

				if (op3 < 4000000000)
					operand3 = op3 -100;
				else
					operand3 = op3 - 4294967296;
				
				stmts = instantiate(pc, "CJNE_RI0_IMM_IMM", new Const(operand2), new Const(operand3));
			} 
    	}
    	else if (tokens.at(0) == "@R1"){

    		if (op2 >= 100 && op3 >= 100){
    			int operand2 = 0;
    			int operand3 = 0;

	    		if (op2 < 4000000000)
					operand2 = op2 -100;
				else
					operand2 = op2 - 4294967296;

				if (op3 < 4000000000)
					operand3 = op3 -100;
				else
					operand3 = op3 - 4294967296;
				
				stmts = instantiate(pc, "CJNE_RI1_IMM_IMM", new Const(operand2), new Const(operand3));
			} 
    	}
    	else if (op1 < 8){

			std::stringstream sstm;
	    	sstm << "CJNE_R" << tokens.at(0) << "_IMM_IMM";
	    	std::string name;
	    	name = sstm.str();
	    	char *name_ =  new char[name.length() + 1];
	    	strcpy(name_, name.c_str());
    		if (op2 >= 100 && op3 >= 100){
    			int operand2 = 0;
    			int operand3 = 0;

	    		if (op2 < 4000000000)
					operand2 = op2 -100;
				else
					operand2 = op2 - 4294967296;

				if (op3 < 4000000000)
					operand3 = op3 -100;
				else
					operand3 = op3 - 4294967296;
				
				stmts = instantiate(pc,name_, new Const(operand2), new Const(operand3)); 
    		}

    	}
    	else if (op1 == 8){
    		if (op2 >= 100 && op3 >= 100){
    			int operand2 = 0;
    			int operand3 = 0;

	    		if (op2 < 4000000000)
					operand2 = op2 -100;
				else
					operand2 = op2 - 4294967296;

				if (op3 < 4000000000)
					operand3 = op3 -100;
				else
					operand3 = op3 - 4294967296;
				
				stmts = instantiate(pc, "CJNE_A_IMM_IMM", new Const(operand2), new Const(operand3)); 
    		}
    		else { // CJNE A,direct, Offset TODO:

    		}
    	}

    | sp_1 (op1) => //PUSH AND POP DIRECT
    	std::stringstream sstm;
    	sstm << tokens.at(0) << "_DIR";
    	std::string name;
    	name = sstm.str();
    	char *name_ =  new char[name.length() + 1];
    	strcpy(name_, name.c_str());
    	
    	if (op1 < 8){
    		stmts = instantiate(pc, name_, Location::regOf(op1)); 
    	}
    	else {
    		stmts = instantiate(pc, name_, new Const(op1)); 
    	}

    | CLR (op1) =>

    	if (op1 == 8){
    		stmts = instantiate(pc, "CLR_A");
    	}
    	else if (op1 == 10) {
    		stmts = instantiate(pc, "CLR_C");
    	}
    	else { // DIRECT, TODO:
    		stmts = instantiate(pc, "CLR_DIR", new Const(op1-100));
    	}


    | SETB (op1) =>

    	else if (op1 == 10) {
    		stmts = instantiate(pc, "SETB_C");
    	}
    	else { // DIRECT, TODO:
    		stmts = instantiate(pc, "SETB_DIR", new Const(op1 - 100));
    	}

    | SWAP (op1) =>

    	if (op1 == 8){
    		stmts = instantiate(pc,"SWAP_A");
    	}

    | xch_ (op1, op2) =>
    	std::stringstream sstm;
    	sstm << tokens.at(0) << "_A_";
    	std::string name;
    	
    	if (op1 == 8){
    		if (tokens.at(2) == "@R0"){
    			sstm << "RI0";
    			name = sstm.str();
		    	char *name_ =  new char[name.length() + 1];
		    	strcpy(name_, name.c_str());
		    	stmts = instantiate(pc, name_);
    		}	
    		else if (tokens.at(2) == "@R1"){
    			sstm << "RI1";
    			name = sstm.str();
		    	char *name_ =  new char[name.length() + 1];
		    	strcpy(name_, name.c_str());
		    	stmts = instantiate(pc, name_);
    		}
    		else if (op2 < 8){
    			sstm << "R" << op2;
    			name = sstm.str();
		    	char *name_ =  new char[name.length() + 1];
		    	strcpy(name_, name.c_str());
		    	stmts = instantiate(pc, name_);
    		}
    		else { //DIRECT TODO:
    			sstm << "DIR";
    			name = sstm.str();
		    	char *name_ =  new char[name.length() + 1];
		    	strcpy(name_, name.c_str());
		    	stmts = instantiate(pc, name_, new Const(op2-100));
    		}

    	}

    | DA (op1) =>

    	if (op1 == 8){
    		stmts = instantiate(pc, "DA");
    	}

    | RL (op1) =>
    
    	if (op1 == 8){
    		stmts = instantiate(pc, "RL_A");
    	}	

	endmatch

	else {
		stmts = NULL;
		result.valid = false;
		result.numBytes = 4;
	}

	result.numBytes = nextPC - hostPC;
	if (result.valid && result.rtl == 0)	// Don't override higher level res
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
	if (r == 0)
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
	if (pc >=100){
		int i = 100 - pc;
		if (pc >= 4196)
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
Exp* _8051Decoder::dis_Eaddr(ADDRESS pc, int ignore /* = 0 */)
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
#if 0		// Can't do this without patterns. It was a bit of a hack anyway
	int hiVal, loVal, reg, locals;
	if ((InstructionPatterns::new_reg_win(prog.csrSrc,hostPC, locals)) != NULL)
			return true;
	if ((InstructionPatterns::new_reg_win_large(prog.csrSrc, hostPC,
		hiVal, loVal, reg)) != NULL)
			return true;
	if ((InstructionPatterns::same_reg_win(prog.csrSrc, hostPC, locals))
		!= NULL)
			return true;
	if ((InstructionPatterns::same_reg_win_large(prog.csrSrc, hostPC,
		hiVal, loVal, reg)) != NULL)
			return true;
#endif

	return false;
}

/*==============================================================================
 * FUNCTION:	  isRestore()
 * OVERVIEW:	  Check to see if the instruction at the given offset is a restore instruction
 * PARAMETERS:	  hostPC - pointer to the code in question (host address)
 * RETURNS:		  True if a match found
 *============================================================================*/
bool _8051Decoder::isRestore(ADDRESS hostPC) {
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

// For now...
int _8051Decoder::decodeAssemblyInstruction(unsigned, int)
{ return 0; }

