#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdarg.h>
# include <limits.h>
# include <stdbool.h>

/*-------------LIBRARIES INCLUDED-------------*/

# include "../libs/printf/ft_printf.h"
# include "../libs/libft/libft.h"

/*-------------STRUCT TYPEDEFS-------------*/

typedef struct s_stack {
	int	value;
	unsigned int	index;
	struct s_stack *next;
	struct s_stack *prev;
} t_stack;

typedef struct s_data
{
	t_stack *a;
	t_stack *b;
} t_data;

#endif