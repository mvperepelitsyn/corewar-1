#ifndef VM_H
# define VM_H

# include "./libft/libft.h"
# include "op.h"

typedef struct s_vm	t_vm;
typedef	void		(*t_command)(t_vm *vm);


/*
** Carriage params: cr
*/

typedef struct	s_carry
{
	unsigned int		car_nbr;
	unsigned char		carry;
	unsigned char		cmd_code;
	unsigned int		reg[16];
	struct s_carry		*next;
	struct s_carry		*prev;
}				t_carry;

/*
** Process params: p
*/

typedef struct	s_process
{
	int					cmp_nbr;
	char				*cmp_name;
	char				*cmp_cmnt;
	size_t				code_size;
	unsigned char		*code;
	struct s_process	*next;
	struct s_process	*prev;
}				t_process;

/*
** Command params: cmd
*/

typedef struct	s_cmd_prms
{
	unsigned char		cmd_code;
	unsigned char		dir_size;
	unsigned char		descript;
	unsigned short		cycles;
}				t_cmd_prms;

/*
** Virtual Maschine params: vm
*/

struct			s_vm
{
	//
	unsigned char		*area;
	t_command			command[16];
	t_cmd_prms			cmd_prms[16];
};

/*
** Main command's functions:
*/

void	live(t_vm *vm);
void	ld(t_vm *vm);
void	st(t_vm *vm);
void	add(t_vm *vm);
void	sub(t_vm *vm);
void	and(t_vm *vm);
void	or(t_vm *vm);
void	xor(t_vm *vm);
void	zjmp(t_vm *vm);
void	ldi(t_vm *vm);
void	sti(t_vm *vm);
void	frk(t_vm *vm);
void	lld(t_vm *vm);
void	lldi(t_vm *vm);
void	lfrk(t_vm *vm);
void	aff(t_vm *vm);

/*
** Common functions:
*/

int		display_usage();
void	parsing(int argc, char **argv, t_vm	*vm);
void	vm_init(t_vm *vm);

#endif
