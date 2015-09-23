require 'roo'
require 'yaml'
def mapper_handler
	file = Roo::Spreadsheet.open('./sparc.ods')
	f = file.sheet(0)
	sprac_data = []
	f.each(opcode: 'Opcode', mnemonic: 'Mnemonic',parameters: 'Argument List') do |hash|
		if hash[:opcode].nil? == true
			hash[:opcode] = ""
		end
		if hash[:mnemonic].nil? == true
			hash[:mnemonic] = ""
		end
		if hash[:parameters].nil? == true
			hash[:parameters] = ""
		end
		sprac_data << Hash[:opcode => hash[:opcode].gsub(/\s+/, ""),
						   :mnemonic => hash[:mnemonic].gsub(/\s+/, ""),
						   :parameters => hash[:parameters].gsub(/\s+/, "").split(',')
						   ]
	end
	File.open("./input/sparcmapper", "w") do |file|
		file.puts sprac_data.to_yaml
	end
end

def transform_handler
	sparc_transform = [
			[:name => "rs1" , :function => "dis_Register(*)"],
			[:name => "rd" , :function => "dis_Register(*)"],
			[:name => "roi" , :function => "dis_Number(*)"],
			[:name => "imm22" , :function => "dis_Number(*)"]
		]
	File.open("./input/sparctransform", "w") do |file|
		file.puts sparc_transform.to_yaml
	end	
end
def register_handle
    sparc_register = []
    reg_count = 0
    File.open("./rawdata/sparcreg").each do |line|
    	line.split(" ").each do |element|
    		sparc_register<<Hash[:reg_name => "#{element[1..3]}".gsub(/\s+/, ""), :reg_no => "#{reg_count}".gsub(/\s+/, "")]
    		reg_count = reg_count + 1
    	end

    end

    File.open("./input/sparcreg", "w") do |file|
   		file.puts sparc_register.to_yaml
   	end

end
register_handle