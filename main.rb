require './specParser'
require "pp"

class DecoderParser
	def initialize 
		@input = "./input"
		@output = "./output"
		@spec_filter = /#.*/
		@m_filter = /(SHOW_ASM.*)|(DEBUG_STMTS)|(\/\*.*\*\/)|(\/\/.*)/
		@output_content = ""
		@constructors = []
	end

	def parse_m_file 
		parser = MParser.new
		files = Dir.glob("#{@input}/*.m")
		if !files.length
			puts "Must have at least one .m file in input folder"
		else 
			File.open(files[0], "r") do |f|
				content = f.read
				p "Parsing #{files[0]}"
				begin
					@m_result = parser.parse(content.gsub(@m_filter,''))
				rescue Parslet::ParseFailed => error
					puts error.cause.ascii_tree
				end
				File.open("#{@output}/m_result", 'w') { |file| PP.pp(@m_result,file) }
				p "Done! Check out result in #{@output}/m_result"
			end			
		end
	end

	def parse_spec_files 
		parser = SpecParser.new
		files = Dir.glob("#{@input}/*.spec")
		if !files.length
			puts "Must have at least one .spec file in input folder"
		else
			@spec_result = []
			files.each do |file| 
				File.open(file, "r") do |f|
					content = f.read
					p "Parsing #{file}"
					begin
						@spec_result += parser.parse(content.gsub(@spec_filter,''))
					rescue Parslet::ParseFailed => error
						puts error.cause.ascii_tree
					end
					p "Done."
				end			
			end
			File.open("#{@output}/spec_result", 'w') { |file| PP.pp(@spec_result,file) }
			p "Done! Check out result in #{@output}/spec_result"
		end
	end 

	def handle_list_pattern (hs,opcode)
		if hs[:disjunction].empty?
			@possible_names << opcode
		else
			iterate_patterns hs[:pattern][:field_name]
			hs[:disjunction].each do |element|
				iterate_patterns element[:pattern][:field_name]
			end
		end
	end

	def handle_pattern_binding (hs,opcode)
		hs.each_pair do |key,value|
			case key
			when :pattern_specifier
				if value.is_a?(Array)
					value = value.map(&:values).flatten
					if value.include? opcode
						@possible_names << opcode
					end
				else
					if value[:pattern_name] == opcode
						if !hs.has_key?(:list_pattern_name)
							handle_list_pattern(hs[:list_pattern],opcode)
						else
							names = hs[:list_pattern_name].map(&:values).flatten
							names.each do |n|
								@possible_names << n
							end 
						end
						
					end
				end
			when :list_pattern_name
				value = value.map(&:values).flatten
				if value.include? opcode
					@possible_names << opcode
				end
			end
		end
	end

	def iterate_patterns opcode
		@spec_result.each do |element|
			element.each_pair do |key,value|
				case key
				when :patterns
					value.each do |e|
						e.each_pair do |k,v|
							case k
							when :pattern_binding
								handle_pattern_binding(v,opcode)
							end
						end
					end
				end
			end
		end
	end

	def handle_constructor hs
		constructor = {}
		synthetic = {}
		@possible_names = []
		hs.each_pair do |key,value|
			case key
			when :opcode
				constructor[:opcode] = value
				if hs[:branches] != ""
					hs[:branches].each_pair do |k,v|
						case k
						when :list_pattern
							if v[:pattern].is_a?(Array) #Synthetic
								synthetic[:opcode] = constructor[:opcode]
								synthetic[:name] = v[:pattern][0][:opcode] 
							else
								iterate_patterns(v[:pattern][:field_name])
							end
						end
					end
				else 
					iterate_patterns(value)	
				end

				constructor[:possible_names] = @possible_names
			end 
		end
		@constructors << constructor
		if !synthetic.empty?
			@synthetic << synthetic
		end
	end

	def handle_constructors
		@synthetic = []
		@spec_result.each do |element|
			element.each_pair do |key,value|
				case key
				when :constructors
					value.each do |e|
						e.each_pair do |k,v|
							case k
							when :constructor
								handle_constructor v
							end
						end
					end
				end
			end
		end
		File.open("#{@output}/possible_names", 'w') { |file| PP.pp(@constructors,file) }
		p "Done! Check Possible Assembly Names in #{@output}/possible_names"
	end

	def handle_opcode (opcode,index)
		opcode_arr = @constructors.map {|cons| cons[:opcode]}
		if !opcode_arr.include?(opcode) # In case opcodes in .m file do not exist in @constructors 
			constructor = {}
			@possible_names = []

			constructor[:opcode] = opcode
			iterate_patterns(opcode)
			constructor[:possible_names] = @possible_names
			@constructors << constructor
		end
		@constructors.each do |element|
			if opcode == element[:opcode]
				if element[:possible_names].length != 0
					name_pattern = /[a-zA-Z0-9_]+\^\"(?<opname>.*)\"/
					opname = ""
					if name_pattern  =~ opcode
						opname = name_pattern.match(opcode)[:opname]
					end
					names = element[:possible_names]
					if names.length > 1
						@output_content += "\t"*index + "if ("
						names.each do |name|
							if name == names.first
								@output_content += "tokens.at(0) == \"#{name}#{opname}\""
							else
								@output_content += " || tokens.at(0) == \"#{name}#{opname}\""
							end
						end
						@output_content += ") {\n"
					else
						@output_content += "\t"*index + "if (tokens.at(0) == \"#{names[0]}#{opname}\" ) {\n"
					end
					return true
				else 
					#@output_content += "\t"*index + "if (lines(0) == \'#{opcode}\' ) {\n"
					return false
				end
			end
		end
		return false
	end

	def handle_arm (arm,index)
		is_matching = false
		arm.each_pair do |key,value|
			case key 
			when :header
					value.each_pair do |k,v|
						case k
						when :pattern
							if v.is_a?(Hash)
								if v.key?(:opcode)
									is_matching = handle_opcode(v[:opcode],index)
								end
								if v.key?(:field_name)
									is_matching = handle_opcode(v[:field_name],index)
									if v.key?(:name) and is_matching 
										@output_content +=  "\t"*(index+1) + "char *#{v[:name]} =  new char[tokens.at(0).length() + 1];\n"
										@output_content +=  "\t"*(index+1) + "strcpy(#{v[:name]}, tokens.at(0).c_str());\n"
									end
								end
								if v.key?(:argument) and is_matching 
									@output_content +=  "\t"*(index+1) + "unsigned #{v[:argument][:lhs]} = magic_process(tokens.at(1));\n"
								end
							else
								count = 0
								v.each do |element| 
									element.each_pair do |kk,vv|
										case kk
										when :opcode
											is_matching = handle_opcode(vv,index) 
											
										when :argument
											count = count + 1
											if is_matching
												@output_content +=  "\t"*(index+1) + "unsigned #{vv[:lhs]} = magic_process(tokens.at(#{count}));\n"
											end
										end
									end

								end
							end
						when :name 
							if is_matching
								@output_content +=  "\t"*(index+1) + "char *#{v} =  new char[tokens.at(0).length() + 1];\n"
								@output_content +=  "\t"*(index+1) + "strcpy(#{v}, tokens.at(0).c_str());\n"
							end
						end	
					end
			when :codes
				if is_matching
					if value.is_a?(Array)
						value.each do |element|
							magic(element,index+1)
						end
					else
						magic(value,index+1)
					end
					@output_content += "\t"*index + "}\n"
				end
			end			
		end 
	end

	def handle_matching (sentences,index) 
		if sentences.is_a?(Array)
			sentences.first.each_pair do |key,value|
				case key
				when :code
					@output_content += "\t"*index + "dword MATCH_p = #{value};\n"
				when :var_name 
					@output_content += "\t"*index + "//ADDRESS #{value} = NO_ADDRESS;\n"
				end
			end
			sentences.delete_at(0)
			sentences.each do |element|
				handle_arm(element[:arm],index)		
			end
		else
			sentences.each_pair do |key,value|
				case key
				when :code
					@output_content += "\t"*index + "dword MATCH_p = #{value};\n"
				when :var_name 
					@output_content += "\t"*index + "//ADDRESS #{value} = NO_ADDRESS;\n"
				when :arm
					handle_arm(value,index)
				end
			end
		end 
	end

	def magic (arr,index)
		arr.each_pair do |key,value|
			case key
			when :block
				@output_content += "\t"*index + "{\n"
				if value.is_a?(Array)
					value.each do |element|
						magic(element,index+1)
					end
				end
				@output_content += "\t"*index + "}\n"
			when :statements
				@output_content += "\t"*index + value +"\n"
			when :if_statements
				@output_content += "\t"*index + "if"
				magic(value,index)
			when :expression
				@output_content +=  value +"\n"
			when :switch_statements
				@output_content += "\t"*index + "switch"
				magic(value,index)
			when :case_statements
				@output_content += "\t"*index + value +"\n"
			when :default_statements
				@output_content += "\t"*index + value +"\n"
			when :else_statements
				@output_content += "\t"*index +"else" +"\n"
				if value.is_a?(Hash)
					magic(value,index)
				end
			when :match_sentences
				handle_matching(value,index) 					
			end	
		end
	end

	def is_number # Write to ouput function: is_number(char *name)
		#Write includes
		includes = ["#include <algorithm>",
			"#include <iostream>",
			"#include <sstream>",
			"#include <iterator>",
			"#include <vector>",
			"#include <sstream>",
			"#include <string>",
			"#include <assert.h>",
			"#include <cstring>",
			"using namespace std;"
			]
		includes.each {|i| @output_content += i + "\n"} 
		#Write is_Number function
		@output_content += "inline bool isInteger(const std::string & s) {\n"
		@output_content += "\tif(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false ;\n"
		@output_content += "\tchar * p ;\n"
		@output_content += "\tstrtol(s.c_str(), &p, 10) ;\n\treturn (*p == 0) ;\n}\n"
	end

	def magic_process  # Write to ouput function: unsigned magic_process(char *name)
		is_number
		@output_content += "unsigned magic_process(std::string name) {\n"
		@output_content += "\tstd::string str = name;\n"
		count = 0
		@spec_result.each do |element|
			element.each_pair do |key,value|
				case key
				when :fields
					value[:fieldinfo_spec].each do |e|
						e.each_pair do |k,v|
							case k
							when :field_item
								if v.is_a?(Array)
									v = v.map {|v_e| v_e[:item]}
									v.each_with_index  do |name,index|
										if count == 0
											@output_content += "\tif (name == #{name.inspect.upcase}) return #{index};\n"
										else
											@output_content += "\telse if (name == #{name.inspect.upcase}) return #{index};\n"
										end
										count = count +1
									end
								else
									@output_content += "\tif (name == #{v[:item].inspect.upcase}) return 0;\n"
									count = count +1
								end
							end
						end
					end
				end
			end
		end
		@output_content += "\telse if (isInteger(str)) {\n"
		@output_content += "\t\tint i = std::atoi((str).c_str());\n"
		@output_content += "\t\tif (i < 0) return i;\n\t\telse return 100 + i;\n"
		@output_content += "\t}\n"
		@output_content += "}\n"
	end

	def write_to_cpp
		magic_process
		@m_result.each do |element|
			element.each_pair do |key,value|
				case key
				when :comments
					@output_content += value 
				when :head
					@output_content += value
				when :statements
					@output_content += value + "\n"
				when :functions
					value.each_pair do |k,v|
						case k
						when :function_type 
							@output_content += v + " " 
						when :function_name 
							@output_content += v  
						when :parameters
							@output_content += "("
							if !v.is_a?(Hash)
								v = v.map(&:values).flatten
								
								v.each do |vv|
									if (vv == v.last)
										@output_content += vv
									else
										@output_content += vv +"," 
									end
								end
							else
								@output_content += v[:variables_decl]	 
							end
							if value.has_key?(:second_name)
								@output_content += ") : #{value[:second_name]}"
								@output_content += "("
								second_parameters = value[:second_parameters]
								if !second_parameters.is_a?(Hash)
									v = second_parameters.map(&:values).flatten
									
									v.each do |vv|
										if (vv == v.last)
											@output_content += vv
										else
											@output_content += vv +"," 
										end
									end
								else
									@output_content += second_parameters[:variables_decl]	 
								end
								@output_content += ")\n"
							else
								@output_content += ")\n"
							end
						when :function_body
							magic(v,0)
						end
					end			
				end
			end
		end
		File.open("#{@output}/decoder.cpp", 'w') { |file| file.write(@output_content) }
		p "Done! Check out decoder.cpp in #{@output} folder"
	end

	def process_parse input
		if !File.directory?(input)
			abort("Directory #{input} doesnt exist! Program terminated!")
		end
		@input = input
		name = /\.\/input\/(?<name>[a-zA-Z0-9_]+)/.match(input)[:name]
		@output = "#{@output}/#{name}"
		if !File.directory?(@output)
			Dir.mkdir @output
		end
		p "----Parsing .m file-------"
		parse_m_file
		p "----Parsing .spec files---"
		parse_spec_files
		p "----Handle constructors---"
		handle_constructors
		p "----write_to_cpp----------"
		write_to_cpp
		
	end

	private :parse_m_file, :parse_spec_files, :write_to_cpp
end
parser = DecoderParser.new
parser.process_parse ARGV[0]