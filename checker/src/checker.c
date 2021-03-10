#include <stack.h>

#include <stdio.h>
void	print_val(t_stack_val val)
{
	dprintf(1, "%hhu, ", val);
}

t_stack_val	stack_eval(char const **str)
{
	t_ustack_val	value;
	t_stack_val		sign;

	value = 0;
	sign = 1;
	while (**str == '-' || **str == '+')
	{
		if (*(*str++) == '-')
			sign *= -1;
	}
	while (**str && '0' <= **str && **str <= '9' && value < STACK_VAL_MAX)
		value = value * 10 + *(*str)++ - '0';
	return (value);
}

t_stack	*stack_load(char const **values)
{
	char const		*current;
	t_ustack_val	value;
	t_stack			*new_elem;
	t_stack			*stack;

	stack = NULL;
	while ((current = *values))
	{
		value = stack_eval(&current);
		if (*current)
		{
			dprintf(2, "stack_load: Invalid argument: '%s'\n", current);
			stack_clear(&stack);
			return (stack);
		}
		if (!(new_elem = stack_new(value)))
		{
			perror("stack_new");
			stack_clear(&stack);
			return (stack);
		}
		stack_push_back(&stack, new_elem);
		values++;
	}
	return (stack);
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
	//stack_riter(stack, &print_val);
	return (0);
}
