require_relative "../lib/should_equal.rb"

file = "misc/files/#{File.basename(__FILE__)}"
test = "misc/files/#{File.basename(__FILE__, ".*")}.avm"
output = "misc/output/#{File.basename(__FILE__, ".*")}.txt"
r = system "./avm #{test} > #{output}"

fd = File.open(output, "rb")
content = fd.read
should_equal("0.42424242\n42.42\n42424242\n4242\n42\n"	, content, file)