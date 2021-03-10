#include <stack.h>
#include <libft.h>

void	print_val(t_stack_val val)
{
	ft_dprintf(1, "%hhu, ", val);
}

int		stack_exec(int fd, t_stack *a)
{
	t_stack	*b;
	char	*line;

	b = NULL;
	while (get_next_line(fd, &line) != 0)
	{
		ft_dprintf(STDOUT_FILENO, "op: %s\n", line);
	}
	return (0);
}

int	main(int ac, char const **av)
{
	t_stack	*input_stack;

	if (ac > 1)
	{
		input_stack = stack_load(&av[1]);
		if (!input_stack)
		{
			ft_dprintf(STDERR_FILENO, "Could not load stack!\n");
			return (1);
		}
		stack_exec(STDIN_FILENO, input_stack);
	}
	return (0);
}
