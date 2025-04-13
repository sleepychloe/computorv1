#!/bin/bash

YELLOW='\033[0;33m'
RED='\033[0;31m'
RESET='\033[0m'

declare -a wrong_equation_form=(
	"adfasdfasf"
	"adfasdf="
	"adfasdf=     "
	"       =sfsdf"
	"a == a"
	"a = a = a"
)

declare -a wrong_variable=(
	"adfasdf=asdfasdf"
	"aaaaa = aaaaa"
)

declare -a wrong_number=(
	"x^2+1 1=0"
	"x^2+1=0 0"
)

declare -a wrong_syntax_brackets=(
	"x^2+((1)=0"
	"x^2+(1))=0"
	"x^2+(1=0)"
	"x^2+)1(=0"
	"x^2+1()=0"
	"(x^2))+((1)=0"
)

declare -a wrong_syntax_operator=(
	"x^2++1=0"
	"x^2+-1=0"
	"x^2+*1=0"
	"x^2+/1=0"
	"x^2-+1=0"
	"x^2--1=0"
	"x^2-*1=0"
	"x^2-/1=0"
	"x^2*+1=0"
	"x^2*-1=0"
	"x^2**1=0"
	"x^2*/1=0"
	"x^2/+1=0"
	"x^2/-1=0"
	"x^2//1=0"
	"x^2//1=0"
	"*x^2+1=0"
	"/x^2+1=0"
	"x^2+1+=0"
	"x^2+1-=0"
	"x^2+1*=0"
	"x^2+1/=0"
	"x^2+1=*0"
	"x^2+1=/0"
	"x^2+1=0+"
	"x^2+1=0-"
	"x^2+1=0*"
	"x^2+1=0/"
)

declare -a wrong_syntax_float_point=(
	"x^2+.1=0"
	"x^2+1.=0"
	"x^2+1..0=0"
	"x^2+1.0.0=0"
)

declare -a wrong_syntax_caret=(
	"(x)^2+1=0"
	"x^2+(1)^2=0"
	"x^^2+1=0"
	"x^+2+1=0"
	"x^-2+1=0"
	"x^2.1+1=0"
)

declare -a complicated_expression=(
	"(5*3/2+1)*x*x^1+(+(-1))/(-2)*x^1+3*1/2=0"
	"((2+4+6x-1*(3x-3+1*3*(-2)*(+1*2*(-1)*(-1)*(+3x)*2+x+3)*(-1)*(2)))+3)-1=0"
	"2*(2x+3)*(x+x)*2/2/2+1+x= 0"
)

declare -a reduced_form_complicated_expression=(
	"1.5 + 0.5 * x + 8.5 * x^2 = 0"
	"- 25 - 153 * x = 0"
	"1 + 7 * x^1 + 4 * x^2 = 0"
)

declare -a answer_complicated_expression=(
	"x = -1/34 - √(203)i/34 = -0.0294118 - 0.419053i,\n\t\t   x = -1/34 + √(203)i/34 = -0.0294118 + 0.419053i"
	"x = -25/153 = -0.163399"
	"x = -7/8 - √(33)/8 = -1.59307,\n\t\t   x = -7/8 + √(33)/8 = -0.15693"
)

declare -a inconsistent_equation=(
	"3x+5=3x"
	"6x+1=6x+22"
	"2x^2+x+1=2x^2+x+7"
	"x^2-2x+1=x^2-2x+4"
)

declare -a answer_inconsistent_equation=(
	"It has no solution"
	"It has no solution"
	"It has no solution"
	"It has no solution"
)

declare -a indeterminate_equation=(
	"9x+1=9x+1"
	"2x-5=2x-5"
	"-x^2-x+2=-x^2-x+2"
	"4x^2-3x+8=4x^2-3x+8"
)

declare -a answer_indeterminate_equation=(
	"It has infinitely many solutions(any real number is a solution)"
	"It has infinitely many solutions(any real number is a solution)"
	"It has infinitely many solutions(any real number is a solution)"
	"It has infinitely many solutions(any real number is a solution)"
)

declare -a linear_equation=(
	"2x+3=11"
	"5x-7=18"
	"7x-9=20"
	"9x-5=22"
	"x+7=15"
	"7x+3=10"
	"5x-7=2"
	"4x+3=10"
	"3x+5=14"
	"6x-2=7"
)

declare -a answer_linear_equation=(
	"x = 4"
	"x = 5"
	"x = 29/7 = 4.14286"
	"x = 3"
	"x = 8"
	"x = 1"
	"x = 9/5 = 1.8"
	"x = 7/4 = 1.75"
	"x = 3"
	"x = 3/2 = 1.5"
)


declare -a quadratic_equation_d_positive=(
	"x^2-3x+2=0"
	"x^2-5x+6=0"
	"x^2+2x-8=0"
	"x^2-7x+12=0"
	"2x^2-10x+12=0"
	"x^2-8x+15=0"
	"3x^2-13x+12=0"
	"4x^2-12x+8=0"
	"x^2+4x-1=0"
	"x^2-6x+1=0"
	"x^2-3x-7=0"
	"x^2+5x-2=0"
	"x^2+3x-8=0"
	"x^2-7x+11=0"
	"x^2+2x-9=0"
)

declare -a answer_quadratic_equation_d_positive=(
	"x = 1,\n\t\t   x = 2"
	"x = 2,\n\t\t   x = 3"
	"x = -4,\n\t\t   x = 2"
	"x = 3,\n\t\t   x = 4"
	"x = 2,\n\t\t   x = 3"
	"x = 3,\n\t\t   x = 5"
	"x = 4/3 = 1.33333,\n\t\t   x = 3"
	"x = 1,\n\t\t   x = 2"
	"x = -2 - √(5) = -4.23607,\n\t\t   x = -2 + √(5) = 0.236068"
	"x = 3 - 2√(2) = 0.171573,\n\t\t   x = 3 + 2√(2) = 5.82843"
	"x = 3/2 - √(37)/2 = -1.54138,\n\t\t   x = 3/2 + √(37)/2 = 4.54138"
	"x = -5/2 - √(33)/2 = -5.37228,\n\t\t   x = -5/2 + √(33)/2 = 0.372281"
	"x = -3/2 - √(41)/2 = -4.70156,\n\t\t   x = -3/2 + √(41)/2 = 1.70156"
	"x = 7/2 - √(5)/2 = 2.38197,\n\t\t   x = 7/2 + √(5)/2 = 4.61803"
	"x = -1 - √(10) = -4.16228,\n\t\t   x = -1 + √(10) = 2.16228"
)

declare -a quadratic_equation_d_zero=(
	"x^2-4x+4=0"
	"x^2+6x+9=0"
	"2x^2-8x+8=0"
	"x^2-10x+25=0"
	"4x^2-4x+1=0"
	"3x^2-18x+27=0"
	"x^2+14x+49=0"
)

declare -a answer_quadratic_equation_d_zero=(
	"x = 2"
	"x = -3"
	"x = 2"
	"x = 5"
	"x = 1/2 = 0.5"
	"x = 3"
	"x = -7"
)

declare -a quadratic_equation_d_negative=(
	"x^2+2x+5=0"
	"x^2-4x+10=0"
	"x^2+6x+13=0"
	"x^2-2x+5=0"
	"x^2+8x+20=0"
	"x^2-6x+25=0"
	"x^2+10x+29=0"
	"x^2-x+2=0"
	"x^2+3x+10=0"
	"x^2-5x+15=0"
)

declare -a answer_quadratic_equation_d_negative=(
	"x = -1 + 2i,\n\t\t   x = -1 - 2i"
	"x = 2 - √(6)i = 2 - 2.44949i,\n\t\t   x = 2 + √(6)i = 2 + 2.44949i"
	"x = -3 + 2i,\n\t\t   x = -3 - 2i"
	"x = 1 + 2i,\n\t\t   x = 1 - 2i"
	"x = -4 + 2i,\n\t\t   x = -4 - 2i"
	"x = 3 + 4i,\n\t\t   x = 3 - 4i"
	"x = -5 + 2i,\n\t\t   x = -5 - 2i"
	"x = 1/2 - √(7)i/2 = 0.5 - 1.32288i,\n\t\t   x = 1/2 + √(7)i/2 = 0.5 + 1.32288i"
	"x = -3/2 - √(31)i/2 = -1.5 - 2.78388i,\n\t\t   x = -3/2 + √(31i)/2 = -1.5 + 2.78388i"
	"x = 5/2 - √(35)i/2 = 2.5 - 2.95804i,\n\t\t   x = 5/2 + √(35)i/2 = 2.5 + 2.95804i"

)


echo -e "${YELLOW}Compiling computor...${RESET}"
echo -e ""
make -C ./computorv1
echo -e ""
echo -e "${YELLOW}Created executable computor!${RESET}"
echo -e ""


echo -e "${YELLOW}╔═════════════════════════════════════════════════════════════════════════╗${RESET}"
echo -e "${YELLOW}║ Test01: wrong equation form                                             ║${RESET}"
echo -e "${YELLOW}╚═════════════════════════════════════════════════════════════════════════╝${RESET}"
echo -e ""
for input in "${wrong_equation_form[@]}"; do
	echo -e "${YELLOW}Testing input:${RESET} \"$input\""
	./computorv1/computor "$input"
	echo -e ""
done
echo -e "${YELLOW}═══════════════════════════════════════════════════════════════════════════${RESET}"


echo -e "${YELLOW}╔═════════════════════════════════════════════════════════════════════════╗${RESET}"
echo -e "${YELLOW}║ Test02: wrong variable                                                  ║${RESET}"
echo -e "${YELLOW}╚═════════════════════════════════════════════════════════════════════════╝${RESET}"
echo -e ""
for input in "${wrong_variable[@]}"; do
	echo -e "${YELLOW}Testing input:${RESET} \"$input\""
	./computorv1/computor "$input"
	echo -e ""
done
echo -e "${YELLOW}═══════════════════════════════════════════════════════════════════════════${RESET}"


echo -e "${YELLOW}╔═════════════════════════════════════════════════════════════════════════╗${RESET}"
echo -e "${YELLOW}║ Test03: wrong number                                                    ║${RESET}"
echo -e "${YELLOW}╚═════════════════════════════════════════════════════════════════════════╝${RESET}"
echo -e ""
for input in "${wrong_number[@]}"; do
	echo -e "${YELLOW}Testing input:${RESET} \"$input\""
	./computorv1/computor "$input"
	echo -e ""
done
echo -e "${YELLOW}═══════════════════════════════════════════════════════════════════════════${RESET}"


echo -e "${YELLOW}╔═════════════════════════════════════════════════════════════════════════╗${RESET}"
echo -e "${YELLOW}║ Test04: wrong syntax: brackets                                          ║${RESET}"
echo -e "${YELLOW}╚═════════════════════════════════════════════════════════════════════════╝${RESET}"
echo -e ""
for input in "${wrong_syntax_brackets[@]}"; do
	echo -e "${YELLOW}Testing input:${RESET} \"$input\""
	./computorv1/computor "$input"
	echo -e ""
done
echo -e "${YELLOW}═══════════════════════════════════════════════════════════════════════════${RESET}"


echo -e "${YELLOW}╔═════════════════════════════════════════════════════════════════════════╗${RESET}"
echo -e "${YELLOW}║ Test05: wrong syntax: operator                                          ║${RESET}"
echo -e "${YELLOW}╚═════════════════════════════════════════════════════════════════════════╝${RESET}"
echo -e ""
for input in "${wrong_syntax_operator[@]}"; do
	echo -e "${YELLOW}Testing input:${RESET} \"$input\""
	./computorv1/computor "$input"
	echo -e ""
done
echo -e "${YELLOW}═══════════════════════════════════════════════════════════════════════════${RESET}"


echo -e "${YELLOW}╔═════════════════════════════════════════════════════════════════════════╗${RESET}"
echo -e "${YELLOW}║ Test06: wrong syntax: float point                                       ║${RESET}"
echo -e "${YELLOW}╚═════════════════════════════════════════════════════════════════════════╝${RESET}"
echo -e ""
for input in "${wrong_syntax_float_point[@]}"; do
	echo -e "${YELLOW}Testing input:${RESET} \"$input\""
	./computorv1/computor "$input"
	echo -e ""
done
echo -e "${YELLOW}═══════════════════════════════════════════════════════════════════════════${RESET}"


echo -e "${YELLOW}╔═════════════════════════════════════════════════════════════════════════╗${RESET}"
echo -e "${YELLOW}║ Test07: wrong syntax: caret                                             ║${RESET}"
echo -e "${YELLOW}╚═════════════════════════════════════════════════════════════════════════╝${RESET}"
echo -e ""
for input in "${wrong_syntax_caret[@]}"; do
	echo -e "${YELLOW}Testing input:${RESET} \"$input\""
	./computorv1/computor "$input"
	echo -e ""
done
echo -e "${YELLOW}═══════════════════════════════════════════════════════════════════════════${RESET}"


echo -e "${YELLOW}╔═════════════════════════════════════════════════════════════════════════╗${RESET}"
echo -e "${YELLOW}║ Test08: complicated expression                                          ║${RESET}"
echo -e "${YELLOW}╚═════════════════════════════════════════════════════════════════════════╝${RESET}"
echo -e ""
for i in "${!complicated_expression[@]}"; do
	echo -e "${YELLOW}Testing input:${RESET} \"${complicated_expression[i]}\""
	echo -e "${YELLOW}Expected reduced form:${RESET} ${reduced_form_complicated_expression[i]}"
	echo -e "${YELLOW}Expected solution:${RESET} ${answer_complicated_expression[i]}"
	echo ""
	./computorv1/computor "${complicated_expression[i]}"
	echo -e ""
	if [[ $i -lt $((${#complicated_expression[@]} - 1)) ]]; then
		echo -e "${YELLOW}⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅${RESET}"
		echo -e ""
	fi
done
echo -e "${YELLOW}═══════════════════════════════════════════════════════════════════════════${RESET}"


echo -e "${YELLOW}╔═════════════════════════════════════════════════════════════════════════╗${RESET}"
echo -e "${YELLOW}║ Test09: inconsistent equation                                           ║${RESET}"
echo -e "${YELLOW}╚═════════════════════════════════════════════════════════════════════════╝${RESET}"
echo -e ""
for i in "${!inconsistent_equation[@]}"; do
	echo -e "${YELLOW}Testing input:${RESET} \"${inconsistent_equation[i]}\""
	echo -e "${YELLOW}Expected solution:${RESET} ${answer_inconsistent_equation[i]}"
	echo ""
	./computorv1/computor "${inconsistent_equation[i]}"
	echo -e ""
	if [[ $i -lt $((${#inconsistent_equation[@]} - 1)) ]]; then
		echo -e "${YELLOW}⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅${RESET}"
		echo -e ""
	fi
done
echo -e "${YELLOW}═══════════════════════════════════════════════════════════════════════════${RESET}"


echo -e "${YELLOW}╔═════════════════════════════════════════════════════════════════════════╗${RESET}"
echo -e "${YELLOW}║ Test10: indeterminate equation                                          ║${RESET}"
echo -e "${YELLOW}╚═════════════════════════════════════════════════════════════════════════╝${RESET}"
echo -e ""
for i in "${!indeterminate_equation[@]}"; do
	echo -e "${YELLOW}Testing input:${RESET} \"${indeterminate_equation[i]}\""
	echo -e "${YELLOW}Expected solution:${RESET} ${answer_indeterminate_equation[i]}"
	echo ""
	./computorv1/computor "${indeterminate_equation[i]}"
	echo -e ""
	if [[ $i -lt $((${#indeterminate_equation[@]} - 1)) ]]; then
		echo -e "${YELLOW}⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅${RESET}"
		echo -e ""
	fi
done
echo -e "${YELLOW}═══════════════════════════════════════════════════════════════════════════${RESET}"


echo -e "${YELLOW}╔═════════════════════════════════════════════════════════════════════════╗${RESET}"
echo -e "${YELLOW}║ Test11: linear equation                                                 ║${RESET}"
echo -e "${YELLOW}╚═════════════════════════════════════════════════════════════════════════╝${RESET}"
echo -e ""
for i in "${!linear_equation[@]}"; do
	echo -e "${YELLOW}Testing input:${RESET} \"${linear_equation[i]}\""
	echo -e "${YELLOW}Expected solution:${RESET} ${answer_linear_equation[i]}"
	echo ""
	./computorv1/computor "${linear_equation[i]}"
	echo -e ""
	if [[ $i -lt $((${#linear_equation[@]} - 1)) ]]; then
		echo -e "${YELLOW}⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅${RESET}"
		echo -e ""
	fi
done
echo -e "${YELLOW}═══════════════════════════════════════════════════════════════════════════${RESET}"


echo -e "${YELLOW}╔═════════════════════════════════════════════════════════════════════════╗${RESET}"
echo -e "${YELLOW}║ Test12: quadratic equation: D > 0                                       ║${RESET}"
echo -e "${YELLOW}╚═════════════════════════════════════════════════════════════════════════╝${RESET}"
echo -e ""
for i in "${!quadratic_equation_d_positive[@]}"; do
	echo -e "${YELLOW}Testing input:${RESET} \"${quadratic_equation_d_positive[i]}\""
	echo -e "${YELLOW}Expected solution:${RESET} ${answer_quadratic_equation_d_positive[i]}"
	echo ""
	./computorv1/computor "${quadratic_equation_d_positive[i]}"
	echo -e ""
	if [[ $i -lt $((${#quadratic_equation_d_positive[@]} - 1)) ]]; then
		echo -e "${YELLOW}⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅${RESET}"
		echo -e ""
	fi
done
echo -e "${YELLOW}═══════════════════════════════════════════════════════════════════════════${RESET}"


echo -e "${YELLOW}╔═════════════════════════════════════════════════════════════════════════╗${RESET}"
echo -e "${YELLOW}║ Test13: quadratic equation: D = 0                                       ║${RESET}"
echo -e "${YELLOW}╚═════════════════════════════════════════════════════════════════════════╝${RESET}"
echo -e ""
for i in "${!quadratic_equation_d_zero[@]}"; do
	echo -e "${YELLOW}Testing input:${RESET} \"${quadratic_equation_d_zero[i]}\""
	echo -e "${YELLOW}Expected solution:${RESET} ${answer_quadratic_equation_d_zero[i]}"
	echo ""
	./computorv1/computor "${quadratic_equation_d_zero[i]}"
	echo -e ""
	if [[ $i -lt $((${#quadratic_equation_d_zero[@]} - 1)) ]]; then
		echo -e "${YELLOW}⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅${RESET}"
		echo -e ""
	fi
done
echo -e "${YELLOW}═══════════════════════════════════════════════════════════════════════════${RESET}"


echo -e "${YELLOW}╔═════════════════════════════════════════════════════════════════════════╗${RESET}"
echo -e "${YELLOW}║ Test14: quadratic equation: D > 0                                       ║${RESET}"
echo -e "${YELLOW}╚═════════════════════════════════════════════════════════════════════════╝${RESET}"
echo -e ""
for i in "${!quadratic_equation_d_negative[@]}"; do
	echo -e "${YELLOW}Testing input:${RESET} \"${quadratic_equation_d_negative[i]}\""
	echo -e "${YELLOW}Expected solution:${RESET} ${answer_quadratic_equation_d_negative[i]}"
	echo ""
	./computorv1/computor "${quadratic_equation_d_negative[i]}"
	echo -e ""
	if [[ $i -lt $((${#quadratic_equation_d_negative[@]} - 1)) ]]; then
		echo -e "${YELLOW}⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅⋅${RESET}"
		echo -e ""
	fi
done
echo -e "${YELLOW}═══════════════════════════════════════════════════════════════════════════${RESET}"


echo -e ""
echo -e "\n${YELLOW}All tests completed${RESET}"
echo -e ""
make fclean -C ./computorv1
echo -e ""
echo -e "${YELLOW}All .o files and executable removed!${RESET}"
echo -e ""
