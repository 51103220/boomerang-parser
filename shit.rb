pattern = /^\b([a-zA-Z0-9_\.]+)\b(?<!^is$|^any$|^of$)/
puts "fiss".match(pattern)