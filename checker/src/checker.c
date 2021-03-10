#include <stack.h>
#include <libft.h>

void	print_val(t_stack_val val)
{
	ft_dprintf(1, "%hhu, ", val);
}

int	main(int ac, char const **av)
{
	t_stack	*stack;

	if (ac > 1)
	{
		stack = stack_load(&av[1]);
		if (!stack)
		{
			ft_dprintf(STDERR_FILENO, "Could not load stack!\n");
			return (1);
		}
		stack_iter(stack, &print_val);
		ft_dprintf(STDOUT_FILENO, "\n");
	}
	return (0);
}
