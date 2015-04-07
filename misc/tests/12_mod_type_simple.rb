require_relative "../lib/should_equal.rb"

file = "misc/files/#{File.basename(__FILE__)}"
test = "misc/files/#{File.basename(__FILE__, ".*")}.avm"
output = "misc/output/#{File.basename(__FILE__, ".*")}.txt"
r = system "./avm #{test} > #{output}"

fd = File.open(output, "rb")
content = fd.read
should_equal("21\n42\n#{42 % 21}\n", content, file)