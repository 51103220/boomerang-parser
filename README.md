# boomerang-parser 
Detail: Toolkit for Boomerang Decompiler Framework <br>
Feature: automatically generate decoder file from .spec files and .m files <br>
# installation  
1. Ruby: https://www.ruby-lang.org/en/documentation/installation <br>
2. Parslet Gem (commandline): gem install parslet <br>
# files and directories
1. input : must have at least one .m file and at least one .spec file <br>
2. output : decoder.cpp is the final result, m_result is the result of parsing .m files, spec_result is the result of .spec files <br>
3. main.rb : main Program 
4. specParser.rb : parser Class 
# run
run this toolkit by command: sudo ruby main.rb <br>