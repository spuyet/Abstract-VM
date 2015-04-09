require_relative "../lib/should_equal.rb"

file = "misc/files/#{File.basename(__FILE__)}"
test = "misc/files/#{File.basename(__FILE__, ".*")}.avm"
output = "misc/output/#{File.basename(__FILE__, ".*")}.txt"
r = system "./avm #{test} > #{output}"

fd = File.open(output, "rb")
content = fd.read
should_equal_n("#{42 + 2987 + 98755 + 84 + 3457.409 + 67 + 890 + 0.678909}\n", content, 7, file)