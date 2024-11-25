Finished, not submitted yet

Mandatory + every Bonus part

Tested on Linux


## Computorv1

* program has 6 significant digits as same as default precision value in C++<br>
<br>

1. check basic equation form<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- if equal sign is not missing<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- if equal sign used only once<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- if left term and right term are both not empty<br>
2. set variable<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- set variable, which is a character between a to z or A to Z<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- check if variable exists<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- check if variable used properly without duplicate<br>
3. check invalid character<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- only allow variable, 0 to 9, float point, caret, brackets,<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;operations, equal sign, space and tab<br>
4. check numbers<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- check if numbers used properly, without any gaps on each number<br>
5. remove every space and tab<br>
6. check syntax: brackets, operators, float point, and caret<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1) brackets: check right and left term seperately<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- if open and close brackets used same times<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- check if brackets are brackets are pair,<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;by removing one by one<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;2) operators(+, -, *, /): check right and left term seperately<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- if operation used properly without dulipicate<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- if the position of operation is appropriate,<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;should not exists front and end of string<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- if it used correctly between each term<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;: the next string of each operation should be considered of<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(+-)number including float point, variable, caret or and brackets<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- if any operation exists between terms enclosed in brackets<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;3) float point<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- if it exists between 0 to 9<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- if it exists only once per number<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- limit the maximum decimal place to 5<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;4) caret<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- if it exists between variable and number of 0 to 9<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- do not allow any sign or bracket after caret<br>
7. remove brackets: right and left term seperately<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1) remove brackets when the expression enclosed in bracket is consisted of a term<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;: does not need caluclate<br>
<details>
<summary><b><ins>how to check if the expression enclosed in bracket is consisted of a term<br></ins></b></summary>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- void Parse::remove_bracket_one_term(std::string &str)<br>
<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1. find start and end index of open and close bracket,<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;split string to 3 part, s[FRONT], s[BRACKET], and s[BACK]<br>

		```	
			ex. 1+2-(-3)+4 → s[FRONT] = "1+2-"
					s[BRACET] = "-3"
					s[BACK] = "+4"
		```
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;2. check s[BRACKET] string, using split_term()<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;3. if size of returned std::vector<std::string> is 1 : remove brackets<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- check last of s[FRONT] and first of s[BRACKET] to determinate sign<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1) s[FRONT][s[FRONT].length() - 1] == '+'<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- if (s[BRACKET] == '+'): result sign is +<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;: remove last character of s[FRONT]<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- else if (s[BRACKET] == '-'): result sign is -<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;: remove last character of s[FRONT]<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- else: result sign is is +, do not remove anything<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;2) s[FRONT][s[FRONT].length() - 1] == '-'<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- if (s[BRACKET] == '+'): result sign is is -<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;: remove first charactor of s[BRACKET]<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- else if (s[BRACKET] == '-'): result sign is +<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;: remove first charactor of s[BRACKET],<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;remove last vcharactor of s[FRONT],<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;s[FRONT] += '+'<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- else: result sign is -, do not remove anything<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;4. else: find next bracket and repeat<br>
<br>
</details>
<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;2) remove brackets when the expression enclosed in bracket is consisted of multiple term<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;: need to calculate<br>
<details>
<summary><b><ins>how to check if the expression enclosed in bracket is consisted of multiple term<br></ins></b></summary>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- void Parse::remove_bracket_multiple_term(std::string &str)<br>
<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1. find start and end index of open and close bracket,<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;split string to 3 part, s[FRONT], s[BRACKET], and s[BACK]<br>

		```	
			ex1. 1+2*3*(4-x)*(5+x)*6 → s[FRONT] = "1+2*3*("
						s[BRACET] = "4-x"
						s[BACK] = "*(5+x)*6"
			ex2. 1-(2+x)*3 → s[FRONT] = "1-("
					s[BRACET] = "2+x"
					s[BACK] = "*3"

		```
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;2. find term and degree of s[BRACKET] string, using get_term()<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;: each term and degree is saved on<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;std::pair<std::vector<std::string>, std::vector<float>><br>

		```
			s[BRACKET] = "4-x"
				→ term: pair<std::vector<std::string>, std::vector<float>>.first
					: {"4", "-1"}
				→ degree: pair<std::vector<std::string>, std::vector<float>>.second
					: {0, 1}
		```
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;3. check * and / operation from s[FRONT],<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;update s[FRONT], std::pair<std::vector<std::string>, std::vector<float>><br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- if s[FRONT] ends with "+(" or "-("<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;: remove last character of s[FRONT],<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;s[FRONT] *= "1*"<br>

			```
				ex2. s[FRONT] = "1-("
					→ s[FRONT] = "1-1*"
			```

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- else: remove last character of s[FRONT]<br>

			```
				ex1. s[FRONT] = "1+2*3("
					→ s[FRONT] = "1+2*3"
			```

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- find * or / from s[FRONT]<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;* make tmp for coefficient of '*' or '/'<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;* make std::pair<std::vector<std::string>, std::vector<float>><br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;for tmp's term and degree<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;* find tmp's term and degree using get_term()<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;* if s[FRONT][s[FRONT].length() -1] is '*'<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;⋅ update original term[i] to original term[i] * tmp term[j]<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;⋅ update original degree[i] to original degree[i] + tmp degree[j]<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;* if s[FRONT][s[FRONT].length() -1] is '/'<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;⋅ check each original degree is 0,<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;because this program does not support calculating<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;expressions with variables in the denominator.<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;⋅ make nb to store every term's coefficient<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;⋅ if nb is not 0, replace original term and degree<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;to tmp term and degree<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;⋅ update original term[i] to original term[i] / nb<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;* remove tmp from s[FRONT]<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;* repeat until s[FRONT][s[FRONT].length() - 1] is not '*' nor '/'<br>

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;4. check * and / operation from s[BACK],<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;update s[BACK], std::pair<std::vector<std::string>, std::vector<float>><br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- if s[BACK] starts with "*(" or "/("<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;* make tmp for string enclosed in brackets, in front of s[BACK]<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;* make std::pair<std::vector<std::string>, std::vector<float>><br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;for tmp's term and degree<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;* find tmp's term and degree using get_term()<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;* if s[BACK][0] is '*'<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;⋅ update original term[i] to original term[i] * tmp term[j]<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;⋅ update original degree[i] to original degree[i] + tmp degree[j]<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;* if s[BACK][0] is '/'<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;⋅ check each tmp degree is 0,<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;because this program does not support calculating<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;expressions with variables in the denominator.<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;⋅ when i > 0, do tmp term[0] = tmp term[0] * tmp term[i]<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;to  store every term's coefficient<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;⋅ update original term[i] to original term[i] / tmp term[0]<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;* remove tmp from s[BACK]<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;* repeat until s[BACK][0] is not '*' nor '/'<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- if s[BACK] is '*' or '/'<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;: do same step as above, but tmp is coefficient of '*' or '/'<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;5. make new s[BRACKET] string using updated term and degree<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;6. change entire string to updated s[FRONT], s[BRACKET], s[BACK]<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;7. repeat until str.find(")") == std::string::npos <br>
<br>
</details>
<br>
8. get terms: right and left term seperately<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1) split each term, seperated by + and -<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;2) find degree of each term<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;3) replace every variable to 1, to calculate easily<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;4) calculate each terms<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;5) merge terms which degrees are same<br>
10. move left term to right term<br>
11. make reduced form<br>
12. set equation type<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- degree < 0: TYPE_FRACTIONAL(= -1)<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- degree == 0: TYPE_ZERO(= 0)<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- 0 < degree <= 2: max degree<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- 2 < degree : TYPE_HIGH_DEGREE(= -2)<br>
13. solve equation if equation type >= 0<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- type == TYPE_CONSTANT(= 0)<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;* 0 = 0: indeterminate equation: infinitely many solution<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;* a = 0 (a != 0): inconsistent equation: no solution<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- type == TYPE_LINEAR(= 1)<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;* solution = -b / a<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- type == TYPE_QUADRATIC(= 2)<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;* discriminant = b * b - 4 * a * c<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;* solution = (-b±√(discriminant))/(2a)<br>
<br>
