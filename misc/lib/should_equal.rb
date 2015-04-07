require_relative 'colors.rb'

def should_equal(a, b, file)
	if a != b
		puts "Equality problem on #{file}".red
	else
		puts "#{file} passed with success !".green
	end
end

def should_not_equal(a, b, file)
	if a == b
		puts "Equality problem on #{file}".red
	else
		puts "#{file} passed with success !".green
	end
end