#Parse Functions
def parse_functions (file)
	functions = []
	function_type = ''
	function_name = ''
	function_parameters = ''
	function_content = ''
	is_content = 0 # 0 if content is not inside a specific function, 1 is otherwise
	count_braces = 0 
	function_pattern = Regexp.new '((DecodeResult&|RTL\*)\s+(\w+|\w+:+\w+)\s*\((.*)\))'
	File.open(file).each do |line|
		if line =~ function_pattern
			is_content = 1
			function_type = line.match(function_pattern)[2]
			function_name = line.match(function_pattern)[3]
			function_parameters = line.match(function_pattern)[4]
			function_content = ''	
		end
		if(is_content == 1)
			if not(count_braces == 0) and not(count_braces == 1 and line.include? "}" )
				function_content += line
			end
			if line.include? "{"
				count_braces += 1
			end
			if line.include? "}"
				count_braces -= 1
				if count_braces == 0 
					is_content = 0
					functions << Hash[:returnType => function_type, 
						:name => function_name,
						:parameters => function_parameters, 
						:content => function_content ]
				end
			end

		end
	end
	functions
end

#Parse Instructions
def parse_inst (file) 
	inst_pattern = /\|\s*(?<name>[a-zA-Z_]+)\s*([a-zA-Z,\"\^=]*)\s*(\((?<para>.*)\))?\s*(\[(?<branch>.*)\])?\s*=>/
	functions = parse_functions(file)
	content = []
	#parse decodeInstruction only 
	functions.each do |f|
		if f[:name] =~ /.*decodeInstruction/
			content = f[:content].lines.map(&:chomp) #this is what decides what output format looks like
		end
	end
	
	instructions = []
	is_inst = 0 
	inst_name = ''
	inst_parameters = 'NULL'
	inst_branch = 'NULL'
	code_list = ''

	content.each_cons(2) do |line,next_line|
		if line =~ inst_pattern
			is_inst = 1
			inst_name = line.match(inst_pattern)[:name]
			if line.match(inst_pattern)[:para] != '' && (line.match(inst_pattern)[:para].nil? == false)
				inst_parameters = line.match(inst_pattern)[:para].split(',')
			else
				inst_parameters = []
			end

			if line.match(inst_pattern)[:branch] != '' && (line.match(inst_pattern)[:para].nil? == false)
				inst_branch = line.match(inst_pattern)[:branch]
			else
				inst_branch = 'NULL'
			end
			
			code_list = ''	
		end
		if line =~ /\| inst = n =>/
			is_inst = 1
			inst_name = 'inst'
			inst_parameters = ['= n']
			inst_branch = 'NULL'
			code_list = ''	
		end
		if (is_inst == 1)
			if !(line =~ inst_pattern) and !(line =~ /\| inst = n =>/)
				code_list += line + "\n"
			end
			if next_line.nil? == false and (next_line =~ inst_pattern || (next_line.include? "endmatch") || next_line =~ /\| inst = n =>/ )
				is_inst = 0
				instructions << Hash[:name => inst_name,
									 :parameters => inst_parameters,
									 :branch => inst_branch,
									 :codes => code_list					
									]

			end 
		end
	end
	instructions
end
