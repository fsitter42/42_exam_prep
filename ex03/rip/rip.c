#include <stdio.h>
#include <unistd.h>

int f_balance(char *s)
{
    int balance = 0;
    int i = 0;
    while (s[i])
    {
        if (s[i] == '(')
            balance++;
        else if (s[i] == ')')
            balance--;
        i++;
    }
    return (balance);
}

int f_len(char *s, int print)
{
    int i = 0;
    while (s[i])
    {
        if (print)
            write(1, &s[i], 1);
        i++;
    }
    return (i);
}

void rip(char *s, int start, int end, int l_count, int r_count, int balance)
{
    if (start == end)
    {
        if (l_count == r_count && l_count + r_count == end - balance)
        {
            f_len(s, 1);
            write(1, "\n", 1);
        }
    }
    else
    {
        if (s[start] == '(')
        {
            rip(s, start + 1, end, l_count + 1, r_count, balance);
            s[start] = 32;
            rip(s, start + 1, end, l_count, r_count, balance);
            s[start] = '(';
        }
        else if (s[start] == ')')
        {
            if (l_count > r_count)
            {
            rip(s, start + 1, end, l_count, r_count + 1, balance);
            s[start] = 32;
            rip(s, start + 1, end, l_count, r_count, balance);
            s[start] = ')';
            }
            else 
            {
            s[start] = 32;
            rip(s, start + 1, end, l_count, r_count, balance);    
            s[start] = ')';          
            }
        }
    }
}

// int main(int ac, char **av)
// {
//     if (ac != 2)
//         return (-1);

//     int len = f_len(av[1], 0);

//     rip(av[1], 0, len, 0, 0);


    
// }

int main()
{
    char av[] = "(()(()(";
    int len = f_len(av, 0);

    int balance = f_balance(av);


    rip(av, 0, len, 0, 0, balance);




    
}