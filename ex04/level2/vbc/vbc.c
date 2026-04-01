#include "vbc.h"

char *s;

int f_sum();
int f_product();
int f_factor();

void unexpected(char c)
{
    if(c)
        printf("Unexpected token '%c'\n", c);
    else
        printf("Unexpected end of file\n");
}

int check_input(char *str)
{
	int i = 0;
	int bal = 0;
	char last;

	while (str[i])
	{
		if (str[i] == '(')
			bal++;
		else if (str[i] == ')')
			bal--;
		else if (isdigit(str[i]) && isdigit(str[i+1]))
			return (unexpected(str[i+1]), 1);
		else if (!isdigit(str[i]) && str[i] != '*' && str[i] != '+' && str[i] != '(' && str[i] != ')')
			return (unexpected(str[i]), 1);
		last = str[i];
		i++;
	}
	if (bal > 0)
		return (unexpected('('), 1);
	if (bal < 0)
		return (unexpected(')'), 1);
	if (last == '+' || last == '*')
		return (unexpected(last), 1);	
}

int f_sum()
{
	int sum = f_product();
	while (*s == '+')
	{
		s++;
		sum += f_product();
	}
	return (sum);
}

int f_product()
{
	int prod = f_factor();
	
	while (*s == '*')
	{
		s++;
		prod *= f_factor();
	}
	return (prod);
}

int f_factor()
{
	int fact = 0;
	if (isdigit(*s))
		return (*s++ - '0');
	if (*s == '(')
	{
		s++;
		fact = f_sum();
		s++;
	}
	return (fact);
}

int main(int ac, char *av[])
{
	if (ac != 2)
		return (1);
	if (check_input(av[1]))
		return (1);
	s = av[1];
	int res = f_sum();
	printf("%i\n", res);
}
