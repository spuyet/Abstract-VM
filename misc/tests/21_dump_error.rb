require_relative "../lib/should_equal.rb"

file = "misc/files/#{File.basename(__FILE__)}"
test = "misc/files/#{File.basename(__FILE__, ".*")}.avm"
# output = "misc/output/#{File.basename(__FILE__, ".*")}.txt"
# r = system "./avm #{test}"
pid = fork {
    system "./avm #{test}";
    if $?.to_i != 0
        puts "#{file} passed with sucess !".green
    else
        puts "#{file} failed !".red
    end
}
Process.waitpid pid
