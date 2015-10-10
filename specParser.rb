#Parser for the language that MLTK Toolkits uses to describe the encodings of machine instructions
=begin
	GRAMMAR
	-NonTerminal appears in italic
	-Terminal appears in slanted
	-keywords and literal text appear in typewrite font	
	-Terminals ending in -name are identifiers
	-Terminals with no special names are integer literals unless otherwise stated
	class Parslet::Atoms::Context
  def lookup(obj, pos)
    p obj
    @cache[pos][obj]
  end
end
=end


$:.unshift( "../lib" );
require 'parslet'


class SpecParser < Parslet::Parser
	
#--------- TOKEN --------------------------
	rule(:token_spec) do
		space? >>
		str("fields of") >> space? >> 
		token_name >> space? >> 
		str('(') >> space? >>
		width >> space? >>
		str(')') >> space? >> 
		field_specs.repeat >> 
		space?
	end
	rule(:token_name) { id }
	rule(:width) { digit }
	rule(:field_specs) do 
		space? >> field_name >> space? >> bits >> space?
	end
	rule(:field_name) { id}
	rule(:bits) { digit >> str(':') >> digit }

#--------- FIELD --------------------------
	rule(:field_spec) do
		space? >>
		str("fieldinfo") >> space? >> 
		fieldinfo_spec.repeat(1) >>
		space?
	end
	rule(:fieldinfo_spec) do 
		space? >>
		field_specifier >> space? >> 
		str("is") >> space? >>
		str("[") >> space? >>
		field_item >> space? >>
		str("]") >> 
		space?
	end
	rule(:field_specifier) do
		id | 
		str("[") >> space? >> id >> (space? >> id).repeat.maybe >> space? >> str("]")
	end
	rule(:field_item) do
		str("checked")| 
		str("unchecked") | 
		str("guaranteed") | 
		str("sparse") >> space? >> str("[") >> space? >> binding >> (str(",") >> binding).repeat.maybe >> space? >> str("]") |
		str("names") >> space? >> str("[") >> space? >> (id|string) >> (space >> (id|string)).repeat.maybe >> space? >> str("]")
	end
	rule(:binding) do
		(id|string) >> space? >> str("=") >> space? >> integer
	end

#--------- PATTERN ------------------------
	rule(:pattern_spec) do
		space? >>
		(str("patterns") >> space? >> 
		pattern_binding.repeat(1)) >>
		space?
	end
	rule(:pattern_binding) do
		space? >> (
		id >> space >> str("is") >> space >> patterns |
		str("[") >> space? >> id >> (space? >> id).repeat.maybe >> space? >> str("]") >> space? >> str("is") >> space? >> patterns |
		id >> space >> str("is any of") >> space >> str("[") >> space? >> id >> (space? >> id).repeat.maybe >> space? >> str("]") >> space? >> str(",") >> space? >> str("which is") >> space >> patterns
		) >>
		space? 
	end
	rule(:patterns) do
		pattern >> (space? >> str("&") >> space? >> pattern).repeat.maybe >> 
		(space? >> str(";") >> space? >> pattern).repeat.maybe >>
		(space? >> str("|") >> space? >> pattern).repeat.maybe
	end
	rule(:pattern) do 
		opcode >> space? >> str("(") >> space? >> arguments >> space? >> str(")") |
		#field_binding |
		constraint |
		id.as(:field_name) |
		str("epsilon") |
		str("some") >> space >> id |
		str("[") >> space? >> id >> (space? >> id).repeat.maybe >> space? >> str("]")
	end
	rule(:constraint) do
	 	id.as(:field_name) >> space? >> relational_operator >> space? >> (integer|generating_expression|expr)
	end
	rule(:generating_expression) do
		str("{") >> space? >> digit >> space >> str("to") >> space >> digit >> space? >> str("}") |
		str("{") >> space? >> digit >> space >> str("to") >> space >> digit >> space >> str("columns") >> space >> digit >> space? >> str("}") |
		str("[") >> space? >> id >> (space? >> id).repeat.maybe >> space? >> str("]") 
	end

#--------- GENERAL ASSETS -----------------
	rule(:space) { match('\s').repeat(1) }
	rule(:space?) { space.maybe} 
	rule(:digit) { match("[0-9]").repeat(1)}
	rule(:id) {  keyword.absent? >> (match('[a-zA-Z0-9_\.]').repeat(1))}
	rule(:string) {
	    str('"') >>
	    	((str('\\') >> any) | (str('"').absent? >> any)).repeat	>>
	    str('"')
  	}
  	rule(:integer) do
    	str("-").maybe >> match("[1-9]") >> digit.repeat 
  	end
  	rule(:hecxa) do
  		match("[0-9a-z]").repeat(1) >> str("x") >> match("[0-9a-z]").repeat(1)
  	end 
  	rule(:expr) do 
  		(integer | id >> bit_slice.maybe >> str("!").maybe) |
  		(integer | id >> bit_slice.maybe >> str("!").maybe) >> space? >> binary_operator >> space? >> expr|
  		str("(") >> space? >> expr >> space? >> str(")")
  	end
  	rule(:binary_operator) do 
  		str("+") |
  		str("-") |
  		str("*") |
  		str("/") 
  	end
  	rule(:relational_operator) do
		str("<") |
		str("<=") |
		str("=") |
		str("!=") |
		str(">") |
		str(">=") 
	end
  	rule(:bit_slice) do
  		str("@[") >> space? >> digit >> (str(":")>>space?>>digit).maybe >> space? >> str("]")
  	end
  	rule(:opcode) do
  		opname >> space? >> str("^") >> opname
  	end
  	rule(:opname) do
  		string | 
  		id
  	end
  	rule(:arguments) do 
  		string | 
  		expr 
  	end
  	rule(:keyword) { str('is') | str('any') | str('of') }
#--------- AST ROOT -----------------------
	rule(:specification) {
		token_spec.as(:token) >> field_spec.as(:spec).repeat(1) |
		field_spec.as(:spec).repeat(1) >> token_spec.as(:token) |
		pattern_spec.repeat(1) }
	root(:specification)
end
test = %q(patterns
 [ TABLE_F2 CALL TABLE_F3 TABLE_F4 ] is op  = {0 to 3}
patterns
 [ UNIMP Bpcc Bicc SETHI FBfcc CBccc ] is TABLE_F2 & op2 = [0 1 2 4 6 7]
 NOP                              is SETHI & rd = 0 & imm22 = 0
patterns
 [ ADD  ADDcc  TADDcc   WRxxx
   AND  ANDcc  TSUBcc   WRPSR
   OR   ORcc   TADDccTV WRWIM
   XOR  XORcc  TSUBccTV WRTBR
   SUB  SUBcc  MULScc   FPop1
   ANDN ANDNcc SLL      FPop2
   ORN  ORNcc  SRL      CPop1
   XNOR XNORcc SRA      CPop2
   ADDX ADDXcc RDxxx    JMPL
   _    _      RDPSR    RETURN
   UMUL UMULcc RDWIM    Ticc
   SMUL SMULcc RDTBR    FLUSH
   SUBX SUBXcc MOVcc    SAVE
   _    _      _        RESTORE
   UDIV UDIVcc _        _
   SDIV SDIVcc _        _       ] is TABLE_F3 & op3 = {0 to 63 columns 4}
patterns
  WRASR          is WRxxx & rd != 0   # should be rdi != 0
  WRY            is WRxxx & rd = 0
  RDASR          is RDxxx & rs1 != 0  # should be rs1i != 0
  RDY            is RDxxx & rs1 = 0
  STBAR          is RDxxx & rs1 = 15 & rd = 0
patterns
 [ LD     LDA     LDF   LDC
   LDUB   LDUBA   LDFSR LDCSR
   LDUH   LDUHA   _ _
   LDD    LDDA    LDDF  LDDC
   ST     STA     STF   STC
   STB    STBA    STFSR STCSR
   STH    STHA    STDFQ STDCQ
   STD    STDA    STDF  STDC
   _      _       _     _
   LDSB   LDSBA   _     _
   LDSH   LDSHA   _     _
   _      _       _     _
   _      _       _     _
   LDSTUB LDSTUBA _     _
   _      _       _     _
   SWAP.  SWAPA   _     _  ]  is TABLE_F4 & op3 = {0 to 63 columns 4}
patterns
  float2 is any of [ FMOVs FNEGs FABSs FSQRTs FSQRTd FSQRTq
                     FiTOs FdTOs FqTOs FiTOd  FsTOd  FqTOd
                     FiTOq FsTOq FdTOq FsTOi  FdTOi  FqTOi ],
  which is FPop1 & opf =  
                   [ 0x1   0x5   0x9   0x29   0x2a   0x2b
                     0xc4  0xc6  0xc7  0xc8   0xc9   0xcb
                     0xcc  0xcd  0xce  0xd1   0xd2   0xd3 ]
  float2s is FMOVs | FNEGs | FABSs | FSQRTs
  FTOs    is FiTOs | FsTOi
  FTOd    is FiTOd | FsTOd 
  FTOq    is FiTOq | FsTOq 
  FdTO    is FdTOi | FdTOs 
  FqTO    is FqTOs | FqTOi

  float3 is any of [ FADDs FADDd FADDq FSUBs FSUBd FSUBq  FMULs
                     FMULd FMULq FDIVs FDIVd FDIVq FsMULd FdMULq ],
    which is FPop1 & opf =
                   [ 0x41  0x42  0x43  0x45  0x46  0x47   0x49
                     0x4a  0x4b  0x4d  0x4e  0x4f  0x69   0x6e ]
  float3s is  FADDs | FSUBs | FMULs | FDIVs
  float3d is  FADDd | FSUBd | FMULd | FDIVd
  float3q is  FADDq | FSUBq | FMULq | FDIVq
patterns
 fcompares is any of      [ FCMPs FCMPEs ],
   which is FPop2 & opf = [ 0x51  0x55 ]
 fcompared is any of      [ FCMPd FCMPEd ],
   which is FPop2 & opf = [ 0x52  0x56 ]
 fcompareq is any of      [ FCMPq FCMPEq ],
   which is FPop2 & opf = [ 0x53  0x57 ]
patterns
  ibranch is any of [ BN BE  BLE BL  BLEU BCS BNEG BVS
                      BA BNE BG  BGE BGU  BCC BPOS BVC ],
    which is Bicc & cond = {0 to 15}

  pbranch is any of [ BPN BPE  BPLE BPL  BPLEU BPCS BPNEG BPVS
                      BPA BPNE BPG  BPGE BPGU  BPCC BPPOS BPVC ],
    which is Bpcc & cond = {0 to 15}

  fbranch is any of [ FBN FBNE FBLG FBUL FBL   FBUG FBG   FBU
                      FBA FBE  FBUE FBGE FBUGE FBLE FBULE FBO ],
    which is FBfcc & cond = {0 to 15}

  cbranch is any of [ CBN CB123 CB12 CB13 CB1   CB23 CB2   CB3
                      CBA CB0   CB03 CB02 CB023 CB01 CB013 CB012 ],
    which is CBccc & cond = {0 to 15}

  trap is any of    [ TN TE  TLE TL  TLEU TCS TNEG TVS
                      TA TNE TG  TGE TGU  TCC TPOS TVC ],
    which is Ticc & cond = {0 to 15
}
  branch is ibranch | fbranch | cbranch
   ).gsub(/#.*/,'')

parser = SpecParser.new
begin
	result = parser.parse(test)
rescue Parslet::ParseFailed => error
	puts error.cause.ascii_tree
end
p result
