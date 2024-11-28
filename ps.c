#include <stdio.h>
#include <unistd.h>

int	main(int ac, char **av)
{
	if (!av[1])
		return (printf("Nao tem nada\n"), 0);
	printf("%s\n", av[1]);
	return (0);
}
