Mandatory + every Bonus part

Tested on Linux

Success 125/100

- program has 6 significant digits as same as default precision value in C++

<br>

## Demo

<details>
<summary><b><ins>error cases</ins></b></summary>
	
![image](https://github.com/user-attachments/assets/6b3aa231-e199-4e3f-b18d-983b6f597407)
###### ↳ test01: wrong equation form
<br>

![image](https://github.com/user-attachments/assets/26bbc8e8-a140-4575-a8e4-b16028a03c2f)
###### ↳ test02: wrong variable
<br>

![image](https://github.com/user-attachments/assets/72e6555b-5a18-4581-8509-216001e15c2e)
###### ↳ test03: wrong number
<br>

![image](https://github.com/user-attachments/assets/763fdf95-5717-4a46-8e1c-cf2aacf362b8)
###### ↳ test04: wrong syntax: brackets
<br>

![image](https://github.com/user-attachments/assets/e6e06462-5ad4-4fd8-8128-cefd86f5886b)
###### ↳ test05: wrong syntax: operator
<br>

![image](https://github.com/user-attachments/assets/f0fd0c4d-8e7f-4198-8454-4e747baf63d6)
###### ↳ test06: wrong syntax: float point
<br>

![image](https://github.com/user-attachments/assets/89d96f76-4882-4ee8-ae2f-e3562f8d6176)
###### ↳ test07: wrong syntax: caret
<br>
<br>

</details>

### Mandatory Part
![image](https://github.com/user-attachments/assets/31e1752f-52a1-42db-a23b-8e988f415416)
###### ↳ complicated expression
<br>

![image](https://github.com/user-attachments/assets/33f912b6-a519-447f-a523-026bc894cedf)
###### ↳ inconsistent equation
<br>

![image](https://github.com/user-attachments/assets/564d3b2c-0b66-4102-8b9e-40244f55ca09)
###### ↳ indeterminate equation
<br>

![image](https://github.com/user-attachments/assets/01dd3075-c319-4a79-a787-8a34b33d6628)
###### ↳ linear equation
<br>

![image](https://github.com/user-attachments/assets/32507f50-c7f4-4391-b27a-78b81236ed3c)
###### ↳ quadratic equation D > 0
<br>

![image](https://github.com/user-attachments/assets/db38abe9-3d73-4eee-a949-036dd132d4cc)
###### ↳ quadratic equation D = 0
<br>

![image](https://github.com/user-attachments/assets/302fdbfa-0ec7-482e-b04e-d2079b6b23e1)
###### ↳ quadratic equation D < 0
<br>
<br>

### Bonus Part
![image](https://github.com/user-attachments/assets/5e15f6b4-a97f-4695-87d7-8bba9b8db163)
###### ↳ complicated expression
<br>

![image](https://github.com/user-attachments/assets/40e699ae-fa47-459e-a9a1-91f11785fae0)
###### ↳ linear equation
<br>

![image](https://github.com/user-attachments/assets/486f5ae2-2e2e-4787-8772-62d303dc1f5b)
###### ↳ quadratic equation D > 0
<br>

![image](https://github.com/user-attachments/assets/6d3e7ec9-827f-473e-8ad8-f2f849c97dfd)
###### ↳ quadratic equation D = 0
<br>

![image](https://github.com/user-attachments/assets/f41fa0c0-f2e5-4713-8671-4382c14b07f0)
###### ↳ quadratic equation D < 0
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


### Introduction

This project introduces polynomial equations as a fundamental mathematical tool.

It builds a foundation for handling functions in programming and computational logic

while encouraging error management and user-friendly outputs.



### Mandatory Part

- Solve second or lower-degree polynomial equations (every input term respect the form of a ∗ xᵖ)
- Display:
	+ The reduced form of the equation
	+ The degree of the polynomial
	+ The solution(s), along with discriminant details
- Handle various edge cases such as inconsistent or indeterminate equations



### Bonus Part

- Manage entry mistakes(vocabulary and syntax)
- Manage free form entrie
- Display solutions asd an irreducible fraction
- Display the intermediate steps
- Find the solutions within imaginary range


<br>


## Project Breakdown

#### 1. check basic equation form

- if equal sign is not missing
- if equal sign used only once
- if left term and right term are both not empty

#### 2. set variable

- set variable, which is a character between a to z or A to Z
- check if variable exists
- check if variable used properly without duplicate

#### 3. check invalid character

- only allow variable, 0 to 9, float point, caret, brackets, operations, equal sign, space and tab

#### 4. check numbers

- check if numbers used properly, without any gaps on each number

#### 5. remove every space and tab

#### 6. check syntax: brackets, operators, float point, and caret

1) brackets: check right and left term seperately
	- if open and close brackets used same times
	- check if brackets are brackets are pair, by removing one by one

2) operators(+, -, *, /): check right and left term seperately
	- if operation used properly without dulipicate
	- if the position of operation is appropriate, should not exists front and end of string
	- if it used correctly between each term
	: the next string of each operation should be considered of (+-)number including float point, variable, caret or and brackets
	- if any operation exists between terms enclosed in brackets

3) float point
	- if it exists between 0 to 9
	- if it exists only once per number
	- limit the maximum decimal place to 5

4) caret
	- if it exists between variable and number of 0 to 9
	- do not allow any sign or bracket after caret

#### 7. remove brackets: right and left term seperately

1) remove brackets when the expression enclosed in bracket is consisted of a term

- does not need caluclate
<details>
<summary><b><ins>how to check if the expression enclosed in bracket is consisted of a term</ins></b></summary>

- void Parse::remove_bracket_one_term(std::string &str)


1. find start and end index of open and close bracket,
	split string to 3 part, s[FRONT], s[BRACKET], and s[BACK]
	```
	ex. 1+2-(-3)+4 → s[FRONT] = "1+2-"
			s[BRACET] = "-3"
			s[BACK] = "+4"
	```
2. check s[BRACKET] string, using split_term()

3. if size of returned std::vector<std::string> is 1
	: remove brackets
	
	- check last of s[FRONT] and first of s[BRACKET] to determinate sign
		* s[FRONT][s[FRONT].length() - 1] == '+'
			+ if (s[BRACKET] == '+'): result sign is +
				: remove last character of s[FRONT]
			+ else if (s[BRACKET] == '-'): result sign is -
				: remove last character of s[FRONT]
			+ else: result sign is is +, do not remove anything
		* s[FRONT][s[FRONT].length() - 1] == '-'
			+ if (s[BRACKET] == '+'): result sign is is -
				: remove first charactor of s[BRACKET]
			+ else if (s[BRACKET] == '-'): result sign is +
				: remove first charactor of s[BRACKET],
				remove last vcharactor of s[FRONT], s[FRONT] += '+'
			+ else: result sign is -, do not remove anything

4. else: find next bracket and repeat
</details>

2) remove brackets when the expression enclosed in bracket is consisted of multiple term
- need to calculate
<details>
<summary><b><ins>how to check if the expression enclosed in bracket is consisted of multiple term</ins></b></summary>

- void Parse::remove_bracket_multiple_term(std::string &str)


1. find start and end index of open and close bracket,
	```
	split string to 3 part, s[FRONT], s[BRACKET], and s[BACK]

	ex1. 1+2*3*(4-x)*(5+x)*6 → s[FRONT] = "1+2*3*("
				s[BRACET] = "4-x"
				s[BACK] = "*(5+x)*6"
	ex2. 1-(2+x)*3 → s[FRONT] = "1-("
			s[BRACET] = "2+x"
			s[BACK] = "*3"
	```
2. find term and degree of s[BRACKET] string, using get_term()
	: each term and degree is saved on
	std::pair<std::vector<std::string>, std::vector<float>>
	```
	ex1. s[BRACKET] = "4-x"
		→ term: pair<std::vector<std::string>, std::vector<float>>.first
			: {"4", "-1"}
		→ degree: pair<std::vector<std::string>, std::vector<float>>.second
			: {0, 1}
	```
3. check * and / operation from s[FRONT],
	update s[FRONT], std::pair<std::vector<std::string>, std::vector<float>>
	- if s[FRONT] ends with "+(" or "-("
		: remove last character of s[FRONT], s[FRONT] *= "1*"

		ex2. s[FRONT] = "1-("
	```
			→ s[FRONT] = "1-1*"
	```
	- else: remove last character of s[FRONT]
	```
		ex1. s[FRONT] = "1+2*3("
			→ s[FRONT] = "1+2*3"
	```
	- find * or / from s[FRONT]
		* make tmp for coefficient of '*' or '/'
		* make std::pair<std::vector<std::string>, std::vector<float>>
			for tmp's term and degree
		* find tmp's term and degree using get_term()
		* if s[FRONT][s[FRONT].length() -1] is '*'
			+ update original term[i] to original term[i] * tmp term[j]
			+ update original degree[i] to original degree[i] + tmp degree[j]
		* if s[FRONT][s[FRONT].length() -1] is '/'
			+ check each original degree is 0,
				because this program does not support calculating
				expressions with variables in the denominator.
			+ make nb to store every term's coefficient
			+ if nb is not 0, replace original term and degree
				to tmp term and degree
			+ update original term[i] to original term[i] / nb
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
</details>

#### 8. get terms: right and left term seperately
- split each term, seperated by + and -
- find degree of each term
- replace every variable to 1, to calculate easily
- calculate each terms
- merge terms which degrees are same

#### 9. move left term to right term

#### 10. make reduced form

#### 11. set equation type
- degree < 0: TYPE_FRACTIONAL(= -1)
- degree == 0: TYPE_ZERO(= 0)
- 0 < degree <= 2: max degree
- 2 < degree : TYPE_HIGH_DEGREE(= -2)

#### 12. solve equation if equation type >= 0
- type == TYPE_ZERO(= 0)
	+ 0 = 0: indeterminate equation: infinitely many solution
	+ a = 0 (a != 0): inconsistent equation: no solution
- type == TYPE_LINEAR(= 1)
	+ solution = -b / a
- type == TYPE_QUADRATIC(= 2)
	+ discriminant = b * b - 4 * a * c
	+ solution = (-b±√(discriminant))/(2a)

