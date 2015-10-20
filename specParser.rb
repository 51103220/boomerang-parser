require 'parslet'


#--------OVERRIDE OUTPUT METHOD-----------
class Parslet::Slice 
	def inspect
    	str
  	end
end

class SpecParser < Parslet::Parser
#--------- TOKEN --------------------------
	rule(:token_spec) do
		space? >>
		(str("fields of") >> space? >> 
		token_name >> space? >> 
		str('(') >> space? >>
		width >> space? >>
		str(')') >> space? >> 
		field_specs.repeat.as(:field_specs)) >> 
		space?
	end
	rule(:token_name) { id.as(:token_name) }
	rule(:width) { digit.as(:width) }
	rule(:field_specs) do 
		space? >> field_name >> space? >> bits >> space?
	end
	rule(:field_name) { id.as(:field_name) }
	rule(:bits) { digit.as(:low_bit) >> str(':') >> digit.as(:high_bit) }

#--------- FIELD --------------------------
	rule(:field_spec) do
		space? >>
		(str("fieldinfo") >> space? >> 
		fieldinfo_spec.repeat(1).as(:fieldinfo_spec)) >>
		space?
	end
	rule(:fieldinfo_spec) do 
		space? >>
		(field_specifier.as(:field_specifier) >> space? >> 
		str("is") >> space? >>
		str("[") >> space? >>
		field_item.as(:field_item) >> space? >>
		str("]")) >> 
		space?
	end
	rule(:field_specifier) do
		id.as(:field_name) | 
		str("[") >> space? >> id.as(:field_name) >> (space? >> id.as(:field_name)).repeat.maybe >> space? >> str("]")
	end
	rule(:field_item) do
		str("checked")| 
		str("unchecked") | 
		str("guaranteed") | 
		str("sparse") >> space? >> str("[") >> space? >> binding.as(:binding) >> (str(",") >> binding.as(:binding)).repeat.maybe >> space? >> str("]") |
		str("names") >> space? >> str("[") >> space? >> (id|string).as(:item) >> (space >> (id|string).as(:item)).repeat.maybe >> space? >> str("]")
	end
	rule(:binding) do
		(id|string).as(:item) >> space? >> str("=") >> space? >> integer.as(:item_value)
	end

#--------- PATTERN ------------------------
	rule(:pattern_spec) do
		space? >>
		(str("patterns") >> space? >> 
		pattern_binding.as(:pattern_binding).repeat(1)) >>
		space?
	end
	rule(:pattern_binding) do
		space? >> ( 
			pattern_specifier.as(:pattern_specifier) >> space >> str("is") >> space >> 
			((str("any of") >> space >> str("[") >> space? >> id.as(:pattern_name) >> (space >> id.as(:pattern_name)).repeat.maybe >> space? >> str("]")).as(:list_pattern_name) >> space? >> str(",") >> space? >> str("which is") >> space? ).maybe  >> patterns.as(:list_pattern)
		) >>
		space?
	end
	rule(:pattern_specifier) do
		id.as(:pattern_name) | 
		(str("[") >> space? >> id.as(:pattern_name) >> (space? >> id.as(:pattern_name)).repeat.maybe >> space? >> str("]"))
	end
	rule(:patterns) do
		pattern.as(:pattern) >> (space? >> str("&") >> space? >> pattern.as(:pattern)).repeat.maybe >> 
		(space? >> str(";") >> space? >> pattern.as(:pattern)).repeat.maybe >>
		(space? >> str("|") >> space? >> pattern.as(:pattern)).repeat.maybe  
	end
	rule(:pattern) do 
		opcode.as(:opcode) >> space? >> str("(") >> space? >> (arguments.as(:argument) >> (str(",") >> space? >> arguments.as(:argument)).repeat.maybe).maybe >> space? >> str(")") |
		#field_binding |
		constraint.as(:constraint) |
		(id.as(:label_name) >> str(":") >> space).maybe >> id.as(:field_name) |
		str("epsilon").as(:epsilon) |
		str("some") >> space >> id.as(:token_name) |
		str("[") >> space? >> id.as(:pattern_name) >> (space? >> id.as(:pattern_name)).repeat.maybe >> space? >> str("]")
	end
	rule(:constraint) do
	 	id.as(:field_name) >> space? >> relational_operator.as(:operator) >> space? >> (integer.as(:integer)|generating_expression.as(:generating_expression)|expr.as(:expr))
	end
	rule(:generating_expression) do
		str("{") >> space? >> digit.as(:lo) >> space >> str("to") >> space >> digit.as(:high) >> space? >> str("}") |
		str("{") >> space? >> digit.as(:lo) >> space >> str("to") >> space >> digit.as(:high) >> space >> str("columns") >> space >> digit.as(:columns) >> space? >> str("}") |
		str("[") >> space? >> id.as(:hecxa)>> (space? >> id.as(:hecxa)).repeat.maybe >> space? >> str("]") 
	end

#--------- CONSTRUCTOR --------------------
	rule(:constructor_spec) do
		space? >>
		(str("constructors") >>
			space? >>
		 	constructor.as(:constructor).repeat(1)
		 	) >>
		space?
	end
	rule(:constructor) do 
		space? >>
		(opcode.as(:opcode) >>
			space? >>
			operands.as(:operands) >>
			space? >>
			(str(":") >> space? >> id.as(:type_name)).maybe  >> 
			space? >>
			(branches).maybe
			) >>
		space?
	end
	rule(:operands) {
		operand_comma|
		operand_space |
		operand.as(:op)
	}
	rule(:operand_comma) {
		operand.as(:op) >> (str(",") >> space? >>  operand.as(:op)).repeat(1)
	}
	rule(:operand_space) {
		operand.as(:op) >> (space? >> binary_operator.as(:binary_operator)>> space? >> operand.as(:op)).repeat(1)
	}
	rule(:operand) do 
		id >> str("!").maybe >> (literal.repeat >> id >> literal.repeat).maybe |
		literal.repeat >> (id >> str("!").maybe).maybe >> literal.repeat 
	end
	rule(:branches) do
		(equations.as(:equations).maybe >> space? >> (str("is") >> space? >> patterns.as(:list_pattern)).maybe).as(:branches)
	end
	rule(:equations) { 
		str("{") >> space? >>
		equation.as(:equation) >> (str(",") >> space? >> equation.as(:equation)).repeat.maybe >>
		space? >>
		str("}")
	}
	rule(:equation) { expr.as(:left_expr) >> space? >> relational_operator.as(:relational_operator) >> space? >> expr.as(:right_expr) }

#--------- PLACEHOLDER --------------------
	rule(:placeholder_spec) do 
		space? >>
		(str("placeholder for") >>
			space? >>
		 	id.as(:token_name) >> space? >>
		 	str("is") >> space? >>
		 	patterns
		) >>
		space?
	end

#--------- RELOCATABLE --------------------
	rule(:relocatable_spec) do 
		space? >>
		(str("relocatable") >>
			space? >>
		 	id.as(:identifiers) >> (space >> id.as(:identifiers)).repeat.maybe
		) >>
		space?
	end

#--------- TEMPLATES ----------------------
 	rule(:template_spec) do
 		space? >>
 		(str("fetch") >> space >> (digit.as(:width)|str("any")) >> space >> str("using") >> space >> string.as(:template) |
 		str("address") >> space >> (str("type is")|str("add using")|str("address add using")|str("to integer using")) >> space? >> string.as(:template)) >>
 		space?
  	end

#--------- LEXCICAL DETAILS ---------------
	rule(:space) { match('\s').repeat(1) }
	rule(:space?) { space.maybe} 
	rule(:digit) { match("[0-9]").repeat(1)}
	rule(:id) {  keyword.absent? >> (match('[a-zA-Z0-9_\.]').repeat(1))}
	rule(:string) {
	    str('"') >>
	    	((str('\\') >> any) | (str('"').absent? >> any)).repeat	>>
	    str('"')
  	}
  	rule(:integer) { str("-").maybe >> match("[1-9]") >> digit.repeat }
  	rule(:hecxa) {match("[0-9a-z]").repeat(1) >> str("x") >> match("[0-9a-z]").repeat(1)}
  	rule(:expr) do 
  		(integer | id >> bit_slice.maybe >> str("!").maybe).as(:lhs) >> (space? >> binary_operator.as(:operator) >> space? >> expr.as(:rhs)).repeat.maybe |
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
	rule(:literal) do
		string |
		integer |
		str("<") | str(">") |
		str("=") | str("[") | 
		str("]") | str("(") |
		str(")") | str("+") |
		str("-") | str("/") |
		str("&") | str("@") |
		str("#") | str("%") |
		str(";") | str("*") |
		str("|") | str("$") 
		#str(",")
	end
  	rule(:bit_slice) do
  		str("@[") >> space? >> 
  		digit >> (str(":") >> space? >> digit).maybe >> 
  		space? >>
  		str("]")
  	end
  	rule(:opcode) {opname >> (str("^") >> opname).repeat.maybe}
  	rule(:opname) do
  		string | 
  		id
  	end
  	rule(:arguments) do
  		opcode.as(:opcode) >> space? >> str("(") >> space? >> arguments.as(:argument) >> (str(",") >> space? >> arguments.as(:argument)).repeat.maybe >> space? >> str(")") | 
  		string | 
  		expr 
  	end
  	rule(:keyword) { 
		str('is') | str('any') |
  	 	str('of') | str('patterns') |
  		str('constructors') | str('placeholder') |
  		str('for') | str('relocatable') |
  		str('columns') | match('\saddress\s') |
  		str('bit') | str('component') |
  		str('epsilon') | str('fetch') |
  		str('field') | str('field_info') |
  		str('fields') | str('names') |
  		str('opcode') | str('operand') |
  		str('syntax') | str('to') |
  		str('type') | str('some') |
  		str('sparse') | str('syntax') |
  		str('type') | str('using') |
  		str('when') | str('which') |
  		str('wordsize')
  	 }

#--------- AST ROOT -----------------------
	rule(:specification) {
		token_spec.as(:tokens) |
		field_spec.as(:fields)  |
		pattern_spec.as(:patterns)| 
		constructor_spec.as(:constructors) |
		placeholder_spec.as(:placeholder) |
		relocatable_spec.as(:relocatable) |
		template_spec.as(:templates)
	}
	rule(:mix) { specification.repeat(1) >> mix.maybe }
	root(:mix)
end

class MParser < Parslet::Parser 
#--------- COMMENT ------------------------
	rule(:comment){ space? >> (multiple_comment | single_comment) >> space?  }
	rule(:single_comment){ (str('//') >> (newline.absent? >> any).repeat) }
	rule(:multiple_comment){ (str('/*') >> (str('*/').absent? >> any).repeat >> str('*/'))}

#--------- INCLUDE IF ENDIF DEFINE --------
	rule(:includes){ (str("#include") >> (newline.absent? >> any).repeat)}
	rule(:if_end_if){(str('#if') >> (str('#endif').absent? >> any).repeat >> str('#endif')) }
	rule(:define){ (str("#define") >> (newline.absent? >> any).repeat)}
	rule(:head){space? >> ( includes | if_end_if | define ) >> space? }

#--------- FUNCTION -----------------------
	rule(:function_decl) do
		space? >> (
			(type.as(:function_type) >> space).maybe  >> function_name.as(:function_name) >> space? >>
			str("(") >> space? >> parameters.as(:parameters).maybe >> space? >> str(")") >> space? >> (str(":") >> space? >> function_name >> space? >>
			str("(") >> space? >> parameters >> space? >> str(")") >> space?).maybe >>
			block.as(:function_body)  
			) >>
		space?
	end
	rule(:type) {(match("[a-zA-Z0-9_]")|str("&")|str("*")|str(":")|str("<")|str(">")).repeat(1)}
	rule(:function_name) {id >> (str("::") >> id).repeat.maybe}
	rule(:parameters) {
		variables_decl.as(:variables_decl) >> space? >> (str(",") >> space? >> variables_decl.as(:variables_decl)).repeat.maybe
	}	
	rule(:variables_decl) {
		((str("static") | str("const")) >> space).maybe  >> type >> (space >> id).maybe
	}
	rule(:statements) {
		(( (comment.absent?) >> match('[^;\n\{\}]')).repeat(1) >> str(";")).as(:statements)
	}
	rule(:if_statements) {
		(str("if") >> space? >> expression.as(:expression) >>
		(space? >> block).maybe).as(:if_statements)
	}
	rule(:while_statements) {
		(str("while") >> space? >> expression.as(:expression) >>
		(space? >> block).maybe).as(:while_statements)
	}
	rule(:expression) {
		 (str("(") >> body_expression.repeat >> str(")"))
	}
	rule(:body_expression){
		expression |  match('[a-zA-Z0-9_\,\+\-\*\/\s\!\=\|\[\]\&\.\>\<]') | string
	}
	rule(:else_statements) {
		(str("else") >>
		(space? >> block).maybe).as(:else_statements)
	}
	rule(:switch_statements) {
		(str("switch") >> space? >> expression.as(:expression) >>
		space? >> block).as(:switch_statements)
	}
	rule(:case_statements) {
		(str("case") >> space >> (string|match('[0-9]').repeat(1)) >> space? >> str(":") >>
		(space? >> block).maybe).as(:case_statements)
	}
	rule(:default_statements) {
		(str("default") >> space? >> str(":") >>
		(space? >> block).maybe).as(:default_statements)
	}
	rule(:block) {
		(str("{") >> space? >> body >> space?  >> str("}")).as(:block)
	}
	rule(:body){
		((statements | comment | if_end_if | if_statements | while_statements | block | switch_statements | else_statements |case_statements | default_statements | match_sentences) >> space?).repeat
	}

#--------- MATCH SENTENCES ----------------
	spec = SpecParser.new
	rule(:match_sentences) do
		(str("match") >> space >> (str("[") >> space? >> id.as(:var_name) >> space? >> str("]")).maybe >> space? >>  (match('[a-zA-Z0-9_\+\-\*\/\!\=\|\[\]\&\.]')).repeat(1).as(:code) >> space >> str("to") >> arms >> str("endmatch")).as(:match_sentences)		
	end
	rule(:match_header) do
		str("|") >> space? >> spec.pattern.as(:pattern) >> space? >> 
			(str("{") >> space? >> spec.equation >> space? >> str("}") >> space?).maybe >> (str("[") >> space? >> id >> space? >> str("]") >> space?).maybe >> str("=>") >> space
	end
	rule(:code) {
		(statements | comment  | if_end_if | if_statements | block | switch_statements | else_statements |case_statements | default_statements | while_statements)
	}

	rule(:codes){
		code >> (space? >> code).repeat.maybe
	}
	rule(:arm) {
		(match_header.as(:header) >> codes.as(:codes)).as(:arm)
	}
	rule(:arms) {
		space? >> (arm >> (space >> arm).repeat.maybe) >> space?
	}

#--------- LEXICAL ------------------------
	rule(:space) { match('\s').repeat(1)}
	rule(:space?) { space.maybe} 	
	rule(:newline) { str("\n") >> str("\r").maybe }
	rule(:id) {  keyword.absent? >> (match('[a-zA-Z0-9_\.]').repeat(1))}
	rule(:keyword) { 
		str("if") | str("switch") | str("else") | str("case") | str("default") | str("match") | str("endmatch") | str("to")
	}
	rule(:string) {
	    (str("'") >> ((str('\\') >> any) | (str("'").absent? >> any)).repeat >> str("'")) |
	    (str('"') >> ((str('\\') >> any) | (str('"').absent? >> any)).repeat >> str('"'))
	}	

#--------- ROOT ---------------------------
	rule(:m) {
		comment.as(:comments) | head.as(:head)| function_decl.as(:functions) | statements
	}
	rule(:mix) {
		m.repeat(1) >> mix.maybe
	}
	root(:mix)
end



