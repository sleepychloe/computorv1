Currently working on the project

flow

1. check if it's equation form
	- if equal sign used multiple time
	- if equal sign exists
2. determine variable
3. syntax check
	- if invalid character exists
	- if brackets used properly
	- if operator(+, -, *, /) used properly
		* position of operator, if it exists between numbers
	- if operator exists between numbers
		* do not allow space or tab between numbers
	- if float point used properly
		* position, if it used multiple time
		* supports up to the third decimal place
	- if caret used properly
		* position, do not allow to use brackets
		* ok: x^1, x^+1, x^-1, x^1.1
		* ko: x^(+1)
4. check each term
	- split term
		* remove every space and tab, and then split each term: seperator: + or -
	- find degree of each term
	- remove variable since each term's degree already saved
	- calculate expression inside bracket to remove brackets
		* check if it needs to be calculate by checking if + or - exists
			and return if it doesn't need
		* if it needs calculate, save numbers and operation seperately
		* calculate *, /
		* calculate +, -
	- calculate terms of same degree if it exists
5. make reduced form
6. check degree if it's calculable
	- set equation type: rational(-1), high degree(-2), or max degree(> 0)
	- make ascending order: form of a + bx + cx^2 = 0
	- set equation string for printing reudced form
7. solve the equation
	- equation type < 0: don't calculate
