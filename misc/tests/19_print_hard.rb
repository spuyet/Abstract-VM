require_relative "../lib/should_equal.rb"

file = "misc/files/#{File.basename(__FILE__)}"
test = "misc/files/#{File.basename(__FILE__, ".*")}.avm"
output = "misc/output/#{File.basename(__FILE__, ".*")}.txt"
r = system "./avm #{test} > #{output}"
if r
    fd = File.open(output, "rb")
    content = fd.read
    should_equal(14, content.length, file)
    should_equal(content, "*\n7\nw\nV\nL\nE\n \n", file)
else
    puts "Error returned by avm !".red
end