#include "minishell.h"

char	*ft_strstr(char *s1, char *s2)
{
	int	i;

	i = 0;
	if ((!s1 || !s2) || (!s1[0] || !s2[0]))
		return (NULL);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (&s2[i]);
}

// int	ft_cmd_built_ins(t_master *master)
// {
// 	int	i;

// 	i = 0;
// 	i += ft_pwd(master, master->in);
// 	i += ft_echo(master->in);
// 	i += ft_env(master);
// 	return (i);
// }

void	*ft_realloc(void *ptr, size_t new_size)
{
	void	*new_ptr;
	size_t	old_size;
	size_t	size;

	if (new_size <= 0)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
		return (malloc(new_size));
	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);
	old_size = (sizeof(ptr) * 1024);
	if ((old_size < new_size))
		size = old_size;
	else
		size = new_size;
	ft_memcpy(new_ptr, ptr, size);
	free(ptr);
	return (new_ptr);
}

void	ft_arrtab(char **arr)
{
	char	*temp;
	int		i;
	int		j;

	i = -1;
	while (++i < ft_count_matriz(arr))
	{
		j = i + 1;
		while (j < ft_count_matriz(arr))
		{
			if (ft_strcmp(arr[i], arr[j]) > 0)
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
			j++;
		}
	}
}

int	ft_countrp(char *str, char *to_find)
{
	int	i;
	int	k;
	int	j;

	i = -1;
	k = 0;
	j = 0;
	while (str && str[++i])
	{
		k = 0;
		while ((str[i] == to_find[k]) && to_find[k])
		{
			i++;
			k++;
		}
		if (str[i] == to_find[0])
			return (-1);
		if (to_find[k] == '\0')
			j++;
	}
	return (j);
}

char	*ft_slice(char *str, char ch)
{
	int		i;
	int		start;
	int		end;
	int		j;
	char	*tmp;

	i = -1;
	start = -1;
	end = -1;
	j = 0;
	while (str[++i])
		if (str[i] == ch)
			start = i;
	i = ft_strlen(str);
	while (str[--i])
		if (str[i] == ch)
			end = i;
	if (start < 0 || end < 0 || start == end)
		return (str);
	i = -1;
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(str) - 1));
	while (str[++i])
		if (i != end && i != start)
			tmp[j++] = str[i];
	tmp[j] = '\0';
	// free(str);
	return (tmp);
}

void	ft_concert_env(t_master *master)
{
	char	**env;

	env = master->environ;
	while (*env)
	{
		remove_if_even(*env, '"');
		remove_if_even(*env, '\'');
		env++;
	}
}

char	*remove_if_even(char *str, char ch)
{
	int		count;
	char	*tmp;
	int		i;
	int		j;

	count = 0;
	i = -1;
	while (str[++i])
		if (str[i] == ch)
			count++;
	if (count % 2 == 0 && count > 1)
	{
		j = 0;
		i = -1;
		tmp = (char *)malloc(sizeof(char) * ft_strlen(str) - count + 1);
		ft_memset(tmp, 0, ft_strlen(tmp));
		while (str[++i])
		{
			if (str[i] != ch)
				tmp[j++] = str[i];
		}
		tmp[j] = '\0';
		return (free(str), tmp);
	}
	return (str);
}
