#include <stack.h>

#include <stdio.h>
void	print_val(t_stack_val val)
{
	dprintf(1, "%hhu, ", val);
}

int main(int ac, char const **av)
{
	t_stack	*input_stack;

	if (ac > 1)
	{
		input_stack = stack_load(&av[1]);
		if (!input_stack)
			return (1);
		stack_iter(input_stack, &print_val);
		dprintf(1, "\n");
	}
	return (0);
}
