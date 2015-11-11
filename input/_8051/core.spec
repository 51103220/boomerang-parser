# FILE:     _8051-core.spec by Dedo
# OVERVIEW: This is the New Jersey Machine Code Toolkit core specification file
#           for the 8051 processor

fieldinfo
[ Rn ] is [ 
names [ "r0"  "r1"  "r2"  "r3"  "r4"  "r5"  "r6"  "r7"
       "a" "b" "c" "dptr" "ab" "p0" "p1" "p2" "p3"]
       ]

patterns
 [ MOV  MOVC  MOVX  ADD  
   ADDC  SUBB  RET  RETI
   DEC  INC  PUSH  POP
   RR   RRC  RLC  ORL 
   ANL  XRL  ORL  ANL  XRL
   DIV  MUL  CLR  SETB
   LJMP  AJMP  SJMP  JMP
   JNB  JB  JBC  ACALL
   LCALL  JZ  JNZ  JNC
   JC  XCH  XCHD  SWAP  
   CJNE  DA  CPL  RL ] is TABLE_OPCODE  & op = {0 to 43}

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
 _JMP  is LJMP | AJMP | SJMP
 JMP  is JMP
 RL   is RL
 jb_  is JNB | JB | JBC
 ACALL  is ACALL
 LCALL  is LCALL
 jz_  is JZ | JNZ

patterns
 JC  is JC
 JNC  is JNC

patterns
 CJNE  is CJNE
 CPL    is CPL
 SWAP  is SWAP
 xch_  is XCH | XCHD
 DA  is DA 

constructors
 mov_ op1, op2
 ACALL address_
 LCALL address_
 add_ op1, op2
 NOP
 ret 

constructors 
 _JMP address_
 JMP
 jb_  op1, op2
 JC  op1
 JNC  op1
 rr  A

constructors
 inst_1  op1
 logical  op1, op2
 div_mul  op1
 sp_1  op1
 CLR  op1
 SETB  op1
 
constructors
 jz_  address_

constructors
 CPL  op1

constructors 
 CJNE  op1, op2, op3
 SWAP  op1
 xch_  A, op2
 DA  A
 RL  A