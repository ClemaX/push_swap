#include <stack.h>

#include <stdio.h>
void	print_val(t_stack_val val)
{
	dprintf(1, "%hhu, ", val);
}

int	main(int ac, char const **av)
{
	t_stack	*stack;

	if (ac > 1)
	{
		stack = stack_load(&av[1]);
		if (!stack)
		{
			dprintf(2, "Could not load stack!\n");
			return (1);
		}
		stack_iter(stack, &print_val);
		dprintf(1, "\n");
	}
	return (0);
}
