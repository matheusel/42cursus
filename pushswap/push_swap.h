#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdarg.h>
# include <limits.h>
# include <stdbool.h>

typedef struct s_stack {
	int	num;
	int	current_position;
	struct s_stack *target_node;
	struct s_stack *next;
	struct s_stack *prev;
} t_stack;

#endif
