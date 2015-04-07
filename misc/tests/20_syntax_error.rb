require_relative "../lib/should_equal.rb"

file = "misc/files/#{File.basename(__FILE__)}"
test = "misc/files/#{File.basename(__FILE__, ".*")}.avm"
# output = "misc/output/#{File.basename(__FILE__, ".*")}.txt"
begin
    r = system "./avm #{test}"
rescue Lexer::LexerException => e
    puts "#{file} passed with sucess !".green
    p e
end