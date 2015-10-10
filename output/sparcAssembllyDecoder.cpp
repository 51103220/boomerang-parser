/*Sparc Assemblly Decoder automatically generated*/
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
#if 0		// Can't do this without patterns. It was a bit of a hack anyway
#endif

DecodeResult& SparcDecoder::decodeAssembly (ADDRESS pc, std::string line) {
	
	if(lines.at(0) == "JMPL"{
			/*
		 * A JMPL with rd == %o7, i.e. a register call
		 */
		CallStatement* newCall = new CallStatement;

		// Record the fact that this is a computed call
		newCall->setIsComputed();

		// Set the destination expression
		newCall->setDest(dis_Eaddr(addr));
		result.rtl = new RTL(pc, stmts);
		result.rtl->appendStmt(newCall);
		result.type = DD;

		SHOW_ASM("call_ " << dis_Eaddr(addr))
		DEBUG_STMTS


	}
	if(lines.at(0) == "RETT"{
			/*
		 * Just a ret (non leaf)
		 */
		result.rtl = new RTL(pc, stmts);
		result.rtl->appendStmt(new ReturnStatement);
		result.type = DD;
		SHOW_ASM("ret_")
		DEBUG_STMTS

	}
	if(lines.at(0) == "JMPL"{
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
	if(lines.at(0) == "SAVE"{
			// Decided to treat SAVE as an ordinary instruction
		// That is, use the large list of effects from the SSL file, and
		// hope that optimisation will vastly help the common cases
		stmts = instantiate(pc, "SAVE", DIS_RS1, DIS_ROI, DIS_RD);

	}
	if(lines.at(0) == "RESTORE"{
			// Decided to treat RESTORE as an ordinary instruction
		stmts = instantiate(pc, "RESTORE", DIS_RS1, DIS_ROI, DIS_RD);

	}
	if(lines.at(0) == "NOP"{
			result.type = NOP;
		stmts = instantiate(pc,	 name);

	}
	if(lines.at(0) == "SETHI"{
			stmts = instantiate(pc,	 "sethi", dis_Num(imm22), DIS_RD);

	}
{
			stmts = instantiate(pc,	 "sethi", dis_Num(imm22), DIS_RD);

	}
	if(lines.at(0) == "ST"||lines.at(0) == "STD"){
			// Note: RD is on the "right hand side" only for stores
		stmts = instantiate(pc,	 name, DIS_RDR, DIS_ADDR);

	}
	if(lines.at(0) == "UNIMP"{
			unused(n);
		stmts = NULL;
		result.valid = false;

	}
}

Exp* SparcDecoder::dis_Register(std::string str){
	if(str == %G0) return Location::regOf(0);
	if(str == %G1) return Location::regOf(1);
	if(str == %G2) return Location::regOf(2);
	if(str == %G3) return Location::regOf(3);
	if(str == %G4) return Location::regOf(4);
	if(str == %G5) return Location::regOf(5);
	if(str == %G6) return Location::regOf(6);
	if(str == %G7) return Location::regOf(7);
	if(str == %O0) return Location::regOf(8);
	if(str == %O1) return Location::regOf(9);
	if(str == %O2) return Location::regOf(10);
	if(str == %O3) return Location::regOf(11);
	if(str == %O4) return Location::regOf(12);
	if(str == %O5) return Location::regOf(13);
	if(str == %SP) return Location::regOf(14);
	if(str == %O7) return Location::regOf(15);
	if(str == %L0) return Location::regOf(16);
	if(str == %L1) return Location::regOf(17);
	if(str == %L2) return Location::regOf(18);
	if(str == %L3) return Location::regOf(19);
	if(str == %L4) return Location::regOf(20);
	if(str == %L5) return Location::regOf(21);
	if(str == %L6) return Location::regOf(22);
	if(str == %L7) return Location::regOf(23);
	if(str == %I0) return Location::regOf(24);
	if(str == %I1) return Location::regOf(25);
	if(str == %I2) return Location::regOf(26);
	if(str == %I3) return Location::regOf(27);
	if(str == %I4) return Location::regOf(28);
	if(str == %I5) return Location::regOf(29);
	if(str == %FP) return Location::regOf(30);
	if(str == %I7) return Location::regOf(31);
	return NULL;
}
