/*Sparc Assemblly Decoder automatically generated*/
#include <assert.h>
#include <cstring>
#include "signature.h"
#include "decoder.h"
#include "exp.h"
#include "prog.h"
#include "proc.h"
#include "sparcdecoder.h"
#include "rtl.h"
#include "BinaryFile.h"		// For SymbolByAddress()
#include "boomerang.h"

DecodeResult& SparcDecoder::decodeAssembly (ADDRESS pc, std::string line) {
	if(lines.at(0) == RETT){
			/*
		 * Just a ret (non leaf)
		 */
		result.rtl = new RTL(pc, stmts);
		result.rtl->appendStmt(new ReturnStatement);
		result.type = DD;
		SHOW_ASM("ret_")
		DEBUG_STMTS

	}
	if(lines.at(0) == JMPL){
			/*
		 * JMPL, with rd != %o7, i.e. register jump
		 * Note: if rd==%o7, then would be handled with the call_ arm
		 */
		CaseStatement* jump = new CaseStatement;
		// Record the fact that it is a computed jump
		jump->setIsComputed();
		result.rtl = new RTL(pc, stmts);
		result.rtl->appendStmt(jump);
		result.type = DD;
		jump->setDest(dis_Eaddr(addr));
		unused(rd);
		SHOW_ASM("JMPL ")
		DEBUG_STMTS


	//	//	//	//	//	//	//	//
	//							//
	//	 Ordinary instructions	//
	//							//
	//	//	//	//	//	//	//	//

	}
	if(lines.at(0) == SAVE){
			// Decided to treat SAVE as an ordinary instruction
		// That is, use the large list of effects from the SSL file, and
		// hope that optimisation will vastly help the common cases
		stmts = instantiate(pc, "SAVE", DIS_RS1, DIS_ROI, DIS_RD);

	}
	if(lines.at(0) == RESTORE){
			// Decided to treat RESTORE as an ordinary instruction
		stmts = instantiate(pc, "RESTORE", DIS_RS1, DIS_ROI, DIS_RD);

	}
	if(lines.at(0) == NOP){
			result.type = NOP;
		stmts = instantiate(pc,	 name);

	}
	if(lines.at(0) == SETHI){
			stmts = instantiate(pc,	 "sethi", dis_Num(imm22), DIS_RD);

	}
	if(lines.at(0) == ){
			stmts = instantiate(pc,	 "sethi", dis_Num(imm22), DIS_RD);

	}
	if(lines.at(0) == UNIMP){
			unused(n);
		stmts = NULL;
		result.valid = false;

	}
}
