#include "../../inc/so_long.h"

int	ft_strlen_without_newline(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	return (i);
}
