/* OBSOLETE TESTS!
#include "minishell.h"

#define NC		"\e[0m"

#define BGREY	"\e[1;30m"
#define BRED	"\e[1;31m"
#define BGREEN	"\e[1;32m"
#define BYELLOW	"\e[1;33m"
#define BBLUE	"\e[1;34m"
#define BPURPLE	"\e[1;35m"
#define BCYAN	"\e[1;36m"
#define BWHITE	"\e[1;37m"

#define BLACK	"\e[30m"
#define RED		"\e[31m"
#define GREEN	"\e[32m"
#define YELLOW	"\e[33m"
#define BLUE	"\e[34m"
#define PURPLE	"\e[35m"
#define CYAN	"\e[36m"
#define GREY	"\e[37m"

void is_var_in_env(char *arg)
{
	int		idx;
	char	*equal_sign;
	char	*check;

	if (!arg)
	{
		printf("%sVar %s cannot be in env.%s\n", RED, arg, NC);
		return ;
	}
	if ((equal_sign = ft_strchr(arg, '=')) != NULL)
		{
			idx = equal_sign - arg;
			check = ft_substr(arg, 0, idx);
		}
		else
			check = ft_strdup(arg);
		idx = get_env_var_index(check);
		free(check);
		if (idx != -1)
			printf("Var in env: [%s%s%s]\n", GREEN, g_env_vars[idx], NC);
		else
			printf("%sNo var with key [%s] in env.%s\n", RED, arg, NC);
}

void	test_minishell(int ac, char **av)
{
	if (ac == 2)
		printf("Test minishell: usage: ./minishell <t> <option>\nOptions are:\t<b>: builtins\n\t\t<e>: execution\n\t\t<a>: both builtins and execution\n");
	else if (ac == 3)
	{
		if (av[2][0] == 'b' || av[2][0] == 'B')
			test_builtins();
		else if (av[2][0] == 'e' || av[2][0] == 'E')
			test_execution();
		else if (av[2][0] == 'a' || av[2][0] == 'A')
		{
			test_builtins();
			test_execution();
		}
	}
}
*/