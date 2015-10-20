require './specParser'
require "pp"

class DecoderParser
	def initialize 
		@input = "./input"
		@output = "./output"
		@spec_filter = /#.*/
		@m_filter = /(SHOW_ASM.*)|(DEBUG_STMTS)|(\/\*.*\*\/)|(\/\/.*)/
		@output_content = ""
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
				p "Done! Check out result in ouput/m_result"
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
			p "Done! Check out result in ouput/spec_result"
		end
	end 

	def mapping_handler

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
									is_matching = true
									@output_content += "\t"*index + "if (lines(0) == #{v[:opcode]} ) {\n"
								end
								if v.key?(:argument)
									@output_content +=  "\t"*(index+1) + "#{v[:argument][:lhs]} = magic_process(#{v[:argument][:lhs]});\n"
								end
							else
								v.each do |element|
									element.each_pair do |kk,vv|
										case kk
										when :opcode
											is_matching = true 
											@output_content += "\t"*index + "if (lines(0) == #{vv} ) {\n"
										when :argument
											@output_content +=  "\t"*(index+1) + "#{vv[:lhs]} = magic_process(#{vv[:lhs]});\n"
										end
									end
								end
							end  
						end	
					end
			when :codes
				if is_matching
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
			when :match_sentences
				handle_matching(value,index) 					
			end	
		end
	end

	def write_to_cpp
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
							@output_content += ")\n"
						when :function_body
							magic(v,0)
						end
					end			
				end
			end
		end
		File.open("#{@output}/decoder.cpp", 'w') { |file| file.write(@output_content) }
		p "Done! Check out decoder.cpp in ouput folder"
	end

	def process_parse 
		p "----Parsing .m file-------"
		parse_m_file
		p "----Parsing .spec files---"
		parse_spec_files
		p "----write_to_cpp----------"
		write_to_cpp
	end

	private :parse_m_file, :parse_spec_files, :write_to_cpp
end
parser = DecoderParser.new
parser.process_parse