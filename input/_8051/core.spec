# FILE:     _8051-core.spec by Dedo
# OVERVIEW: This is the New Jersey Machine Code Toolkit core specification file
#           for the 8051 processor

fieldinfo
[ Rn ] is [ 
names [ "r0"  "r1"  "r2"  "r3"  "r4"  "r5"  "r6"  "r7"]
       "a" "b" "c" "dptr" "ab" "p0" "p1" "p2" "p3"]

patterns    
 mov_   is MOV | MOVC | MOVX
 add_ 	is ADD | ADDC | SUBB
 NOP    is NOP
 ret 	is RET | RETI
 inst_1 is DEC | INC
 sp_1 	is PUSH | POP
 rr 	is RR | RRC | RLC

patterns
 logical is ORL | ANL | XRL
 div_mul is DIV | MUL
 CLR is  CLR
 SETB is SETB

patterns
 _JMP   is LJMP | AJMP | SJMP
 JMP    is JMP
 jb_ 	is JNB | JB | JBC
 ACALL  is ACALL
 LCALL  is LCALL
 jz_  	is JZ | JNZ

patterns
 JC is JC
 JNC is JNC

patterns
 CJNE is CJNE
 SWAP is SWAP
 xch_   is XCH | XCHD
 DA 	is A 

constructors
 mov_ operand1, operand2
 ACALL address
 LCALL address
 add_ operand1, operand2
 NOP
 ret 

constructors 
 _JMP 	address
 JMP
 jb_ 	operand1, operand2
 JC 	operand1
 JNC	operand1
 rr A

constructors
 inst_1        operand1
 logical       operand1, operand2
 div_mul	operand1
 sp_1 		operand1
 CLR 		operand1
 SETB		operand1
 
constructors
 jz_ 	address

constructors
 CPL operand1

constructors 
 CJNE operand1, operand2, operand3
 SWAP operand1
 xch_   A, operand2
 DA 	A
 RL 	A