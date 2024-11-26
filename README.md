Finished, not submitted yet

Mandatory + every Bonus part

Tested on Linux

<br>

Bonus: Manage entry mistakes(vocabulary and syntax),<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Manage free form entrie,<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Display solutions asd an irreducible fraction,<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Display the intermediate steps,<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Find the solutions within imaginary range<br>

- program has 6 significant digits as same as default precision value in C++<br>
<br>

<br>

## Installation
```
	git clone https://github.com/sleepychloe/computorv1.git
	bash test.sh
	bash test_bonus.sh
```

or

```
	git clone https://github.com/sleepychloe/computorv1.git
	cd computorv1
	make
	make bonus
```

## Usage

```
	./computer "POLYNOMIAL_SECOND_OR_LOWER_DEGREE_EQUATION"
	./computor_bonus "POLYNOMIAL_SECOND_OR_LOWER_DEGREE_EQUATION"
	./computor --help
	./computor -h
```

example

```
	./computer "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0"
	./computer_bonus "5 * X^0 + 4 * X^1 = 4 * X^0"
```

<br>


## Computorv1

### 1. check basic equation form

- if equal sign is not missing<br>
- if equal sign used only once<br>
- if left term and right term are both not empty<br>

### 2. set variable

- set variable, which is a character between a to z or A to Z<br>
- check if variable exists<br>
- check if variable used properly without duplicate<br>

### 3. check invalid character

- only allow variable, 0 to 9, float point, caret, brackets,<br>
&nbsp;&nbsp;&nbsp;&nbsp;operations, equal sign, space and tab<br>

### 4. check numbers

- check if numbers used properly, without any gaps on each number<br>

### 5. remove every space and tab

### 6. check syntax: brackets, operators, float point, and caret

##### 1) brackets: check right and left term seperately
- if open and close brackets used same times<br>
- check if brackets are brackets are pair,<br>
&nbsp;&nbsp;&nbsp;&nbsp;by removing one by one<br>
##### 2) operators(+, -, *, /): check right and left term seperately
- if operation used properly without dulipicate<br>
- if the position of operation is appropriate,<br>
&nbsp;&nbsp;&nbsp;&nbsp;should not exists front and end of string<br>
- if it used correctly between each term<br>
&nbsp;&nbsp;&nbsp;&nbsp;: the next string of each operation should be considered of<br>
&nbsp;&nbsp;&nbsp;&nbsp;(+-)number including float point, variable, caret or and brackets<br>
- if any operation exists between terms enclosed in brackets<br>
##### 3) float point
- if it exists between 0 to 9<br>
- if it exists only once per number<br>
- limit the maximum decimal place to 5<br>
##### 4) caret
- if it exists between variable and number of 0 to 9<br>
- do not allow any sign or bracket after caret<br>

### 7. remove brackets: right and left term seperately
##### 1) remove brackets when the expression enclosed in bracket is consisted of a term
- does not need caluclate<br>
<details>
<summary><b><ins>how to check if the expression enclosed in bracket is consisted of a term<br></ins></b></summary>
<br>
- void Parse::remove_bracket_one_term(std::string &str)<br>
<br>

```
1. find start and end index of open and close bracket,
	split string to 3 part, s[FRONT], s[BRACKET], and s[BACK]

	ex. 1+2-(-3)+4 → s[FRONT] = "1+2-"
			s[BRACET] = "-3"
			s[BACK] = "+4"

2. check s[BRACKET] string, using split_term()

3. if size of returned std::vector<std::string> is 1
	: remove brackets
	
	- check last of s[FRONT] and first of s[BRACKET] to determinate sign
		* s[FRONT][s[FRONT].length() - 1] == '+'
			⋅ if (s[BRACKET] == '+'): result sign is +
				: remove last character of s[FRONT]
			⋅ else if (s[BRACKET] == '-'): result sign is -
				: remove last character of s[FRONT]
			⋅ else: result sign is is +, do not remove anything
		* s[FRONT][s[FRONT].length() - 1] == '-'
			⋅ if (s[BRACKET] == '+'): result sign is is -
				: remove first charactor of s[BRACKET]
			⋅ else if (s[BRACKET] == '-'): result sign is +
				: remove first charactor of s[BRACKET],
				remove last vcharactor of s[FRONT], s[FRONT] += '+'
			⋅ else: result sign is -, do not remove anything

4. else: find next bracket and repeat
```

<br>
</details>

##### 2) remove brackets when the expression enclosed in bracket is consisted of multiple term
- need to calculate<br>
<details>
<summary><b><ins>how to check if the expression enclosed in bracket is consisted of multiple term<br></ins></b></summary>
<br>
- void Parse::remove_bracket_multiple_term(std::string &str)<br>
<br>

```
1. find start and end index of open and close bracket,
	split string to 3 part, s[FRONT], s[BRACKET], and s[BACK]

	ex1. 1+2*3*(4-x)*(5+x)*6 → s[FRONT] = "1+2*3*("
				s[BRACET] = "4-x"
				s[BACK] = "*(5+x)*6"
	ex2. 1-(2+x)*3 → s[FRONT] = "1-("
			s[BRACET] = "2+x"
			s[BACK] = "*3"

2. find term and degree of s[BRACKET] string, using get_term()
	: each term and degree is saved on
	std::pair<std::vector<std::string>, std::vector<float>>
	
	ex1. s[BRACKET] = "4-x"
		→ term: pair<std::vector<std::string>, std::vector<float>>.first
			: {"4", "-1"}
		→ degree: pair<std::vector<std::string>, std::vector<float>>.second
			: {0, 1}

3. check * and / operation from s[FRONT],
	update s[FRONT], std::pair<std::vector<std::string>, std::vector<float>>
	- if s[FRONT] ends with "+(" or "-("
		: remove last character of s[FRONT], s[FRONT] *= "1*"

		ex2. s[FRONT] = "1-("
			→ s[FRONT] = "1-1*"

	- else: remove last character of s[FRONT]

		ex1. s[FRONT] = "1+2*3("
			→ s[FRONT] = "1+2*3"

	- find * or / from s[FRONT]
		* make tmp for coefficient of '*' or '/'
		* make std::pair<std::vector<std::string>, std::vector<float>>
			for tmp's term and degree
		* find tmp's term and degree using get_term()
		* if s[FRONT][s[FRONT].length() -1] is '*'
			⋅ update original term[i] to original term[i] * tmp term[j]
			⋅ update original degree[i] to original degree[i] + tmp degree[j]
		* if s[FRONT][s[FRONT].length() -1] is '/'
			⋅ check each original degree is 0,
				because this program does not support calculating
				expressions with variables in the denominator.
			⋅ make nb to store every term's coefficient
			⋅ if nb is not 0, replace original term and degree
				to tmp term and degree
			⋅ update original term[i] to original term[i] / nb
		* remove tmp from s[FRONT]
		* repeat until s[FRONT][s[FRONT].length() - 1] is not '*' nor '/'

4. check * and / operation from s[BACK],
	update s[BACK], std::pair<std::vector<std::string>, std::vector<float>>
	- if s[BACK] starts with "*(" or "/("
		make tmp for string enclosed in brackets, in front of s[BACK]
			* make std::pair<std::vector<std::string>, std::vector<float>>
				for tmp's term and degree
			* find tmp's term and degree using get_term()
			* if s[BACK][0] is '*'
				⋅ update original term[i] to original term[i] * tmp term[j]
				⋅ update original degree[i] to original degree[i] + tmp degree[j]
			* if s[BACK][0] is '/'
				⋅ check each tmp degree is 0,
					because this program does not support calculating
					expressions with variables in the denominator.
				⋅ when i > 0, do tmp term[0] = tmp term[0] * tmp term[i]
					to  store every term's coefficient
					update original term[i] to original term[i] / tmp term[0]
			* remove tmp from s[BACK]
			* repeat until s[BACK][0] is not '*' nor '/'
	- if s[BACK] is '*' or '/'
		: do same step as above, but tmp is coefficient of '*' or '/'
5. make new s[BRACKET] string using updated term and degree
6. change entire string to updated s[FRONT], s[BRACKET], s[BACK]
7. repeat until str.find(")") == std::string::npos
```

<br>
</details>

### 8. get terms: right and left term seperately

- split each term, seperated by + and -<br>
- find degree of each term<br>
- replace every variable to 1, to calculate easily<br>
- calculate each terms<br>
- merge terms which degrees are same<br>

### 9. move left term to right term

### 10. make reduced form

### 11. set equation type

- degree < 0: TYPE_FRACTIONAL(= -1)<br>
- degree == 0: TYPE_ZERO(= 0)<br>
- 0 < degree <= 2: max degree<br>
- 2 < degree : TYPE_HIGH_DEGREE(= -2)<br>

### 12. solve equation if equation type >= 0
- type == TYPE_CONSTANT(= 0)<br>
&nbsp;&nbsp;&nbsp;&nbsp;* 0 = 0: indeterminate equation: infinitely many solution<br>
&nbsp;&nbsp;&nbsp;&nbsp;* a = 0 (a != 0): inconsistent equation: no solution<br>
- type == TYPE_LINEAR(= 1)<br>
&nbsp;&nbsp;&nbsp;&nbsp;* solution = -b / a<br>
- type == TYPE_QUADRATIC(= 2)<br>
&nbsp;&nbsp;&nbsp;&nbsp;* discriminant = b * b - 4 * a * c<br>
&nbsp;&nbsp;&nbsp;&nbsp;* solution = (-b±√(discriminant))/(2a)<br>
<br>
