require './mParse'
require 'yaml'

class DecoderParser
	def initialize (content)
		@content = content
		@machine = "unknown"
	end
	def read_decoder_file file
		File.open(file).each do |line|
			if line =~ /#include./ or line =~ /#if./ or line =~ /#endif/ or line =~ /#define/#Get line begin with #include #if #define #endif
				@content << line 
			end
		end
		@content <<"\nDecodeResult& SparcDecoder::decodeAssembly (ADDRESS pc, std::string line) {\n"
		instructions = parse_inst (file)
		instructions.each do |inst|
			@mapper.each do |m|
				if m[:mnemonic].downcase =~ /#{inst[:name].downcase}/
					opcode = m[:opcode]
					opcode.split(",").each_with_index do |element, index|
					if index == 0 	
						@content << "\tif(lines.at(0) == \"#{element}\""
					else
						@content <<"||lines.at(0) == \"#{element}\""
					end
					end
					@content << "){\n\t"<< inst[:codes] << "\t}\n"
					

				end
			end
			
		end
		@content << "}\n"
	end

	def read_instruction_file file
		begin
			@mapper = YAML.load(File.read(file))
		rescue
			raise "Can't load #{@machine}mapper"
		end
	end 


	def parse file
		if file =~ /\.\/input\/(?<machine>[a-zA-Z0-9_]+)decoder.m/
			@machine = file.match(/\.\/input\/(?<machine>[a-zA-Z0-9_]+)decoder.m/)[:machine]
		end
		read_instruction_file "./input/#{@machine}mapper"
		read_decoder_file(file)
		read_register_transform "./input/#{@machine}reg"
		output = "./output/#{@machine}AssembllyDecoder.cpp"
		write_to_output(output)
	end


	def read_register_transform file #for transform register 
		begin
			transform = YAML.load(File.read(file))
		rescue
			raise "Can't load #{file}"
		end
		@content <<"\nExp* SparcDecoder::dis_Register(std::string str){\n"
		#if(str=="%SP") return Location::regOf(14);
		transform.each do |line|
			@content << "\tif(str == #{line[:reg_name].upcase}) return Location::regOf(#{line[:reg_no]});\n"
		end
		@content << "\treturn NULL;\n"
		@content << "}\n"

	end


	def write_to_output file
		File.open(file, "w") do |f|
			f.puts @content
		end
	end

	private :read_decoder_file, :read_instruction_file, :write_to_output
end

parser = DecoderParser.new "\/*Sparc Assemblly Decoder automatically generated*\/\n"
parser.parse "./input/sparcdecoder.m"
