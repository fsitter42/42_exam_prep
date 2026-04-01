#include "vbc.h"

char *s;

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

int main(int ac, char *av[])
{
	if (ac != 2)
		return (1);
	if (check_input(av[1]))
		return (1);
	printf("correct\n");
	// s = av[1];
	// int res = f_sum();
	// printf("%i\n", res);
}
