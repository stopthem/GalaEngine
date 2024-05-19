-- This is a lua global variable

some_variable = 7 * 6

-- This is a lua table

config = {
	title = "My Game Engine",
	fulscreen = false,
	resolution =
	{
		width = 800,
		height = 600
	}
}

-- This is a lua function thatr calculates factorial of a given number

function factorial(n)

	if n == 1 
	then
		return 1
	end

	return n * factorial(n - 1)

end

print("cube of the number 3 is " ..cube(3))