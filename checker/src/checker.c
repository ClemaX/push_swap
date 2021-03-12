#include <stack.h>
#include <stack_op.h>

#include <libft.h>
#include <gnl/get_next_line.h>

static void	print_val(t_stack_val val)
{
	ft_dprintf(1, "%hhu ", val);
}

static void	print_stack(t_stack *stack, char const *label)
{
	ft_dprintf(STDOUT_FILENO, "stack %s:\n", label);
	if (stack)
	{
		stack_iter(stack, &print_val);
		ft_dprintf(STDOUT_FILENO, "\n");
	}
	else
		ft_dprintf(STDOUT_FILENO, "empty\n");
}

static int	checker_exec(int fd, t_stack **a)
{
	t_stack		*b;
	t_stack_op	op;
	char		*line;
	int			op_err;
	int			gnl_err;

	b = NULL;
	op_err = 0;
	while (!op_err && (gnl_err = get_next_line(fd, &line) ) == GNL_CONTINUE)
	{
		if (*line)
		{
			if ((op = stack_op(line)))
			{
				ft_dprintf(STDOUT_FILENO, "executing %s...\n", line);
				op(a, &b);
				print_stack(*a, "a");
				print_stack(b, "b");
			}
			else
			{
				op_err = 1;
				ft_dprintf(STDERR_FILENO, "unknown operation: %s!\n", line);
			}
		}
		free(line);
	}
	return (gnl_err == GNL_ERROR ? gnl_err : op_err);
}

int			checker_validate(t_stack *input_stack)
{
	t_stack const*const	end = input_stack;
	t_stack_val			prev_val;

	if (input_stack)
	{
		prev_val = input_stack->val;
		input_stack = input_stack->next;
		while (input_stack != end && input_stack->val >= prev_val)
		{
			prev_val = input_stack->val;
			input_stack = input_stack->next;
		}
	}
	return (input_stack != end);
}

int			main(int ac, char const **av)
{
	t_stack	*input_stack;
	int		validation_err;

	validation_err = 0;
	if (ac > 1)
	{
		input_stack = stack_load(&av[1]);
		if (!input_stack)
			return (1);
		if (checker_exec(STDIN_FILENO, &input_stack) == 0)
		{
			validation_err = checker_validate(input_stack);
			if (validation_err)
				ft_dprintf(STDERR_FILENO,
					"The input stack has not been sorted!\n");
		}
		stack_clear(&input_stack);
	}
	return (validation_err);
}
