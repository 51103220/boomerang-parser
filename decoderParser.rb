require './mParse'
require 'yaml'

class DecoderParser
	def initialize (content)
		@content = content
		@machine = "unknown"
	end
	def read_decoder_file file
		File.open(file).each do |line|
			if line =~ /#include./ 
				@content << line 
			end
		end
		@content <<"\nDecodeResult& SparcDecoder::decodeAssembly (ADDRESS pc, std::string line) {\n"
		instructions = parse_inst (file)
		instructions.each do |inst|
			@mapper.each do |m|
				if m[:mnemonic].downcase =~ /#{inst[:name].downcase}/
					opcode = m[:opcode]
					@content << "\tif(lines.at(0) == #{opcode}){\n"
					@content << "\t"<< inst[:codes] << "\t}\n"

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
		output = "./output/#{@machine}AssembllyDecoder.cpp"
		write_to_output(output)
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
