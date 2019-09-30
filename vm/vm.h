#ifndef VM_H
# define VM_H

# include "./libft/libft.h"
# include "op.h"

typedef struct s_vm		t_vm;
typedef struct s_carry	t_carry;
typedef	void			(*t_command)(t_vm *vm, t_carry *cr);


/*
** Carriage params: cr
*/

struct	s_carry
{
	unsigned int		car_nbr;//carry number
	unsigned char		alive;// are you still alive?
	unsigned char		carry;//flag "carry"
	unsigned char		cmd_code;//current operation code
	unsigned char		jump_len;//bytes to second instruction
	unsigned int		last_live;//cycles from last live call
	unsigned int		cycles_before;//cycles before current operation
	unsigned int		position;//carry position in game memory area
	unsigned int		color;//carry color (champ color)
	unsigned int		reg[16];//registr
	struct s_carry		*next;
};

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
	unsigned char		dir_size;//
	unsigned char		descript;
	unsigned short		cycles_before;
}				t_cmd_prms;

/*
** Virtual Maschine params: vm
*/

struct			s_vm
{
	unsigned char		champs_count;
	unsigned char		last_alive;//number of last alive champion
	unsigned char		*area;
	unsigned int		cycles_from_start;
	unsigned int		dump;
	int					cycles_to_die;
	int					ctd_counter;//cycles to die counter
	int					check_counter;
	unsigned int		live_counter;//summary cycles_to_die alive counter
	t_carry				*carriages;
	t_process			*processes;
	t_command			command[16];
	t_cmd_prms			cmd_prms[16];
};

/*
** Main command's functions:
*/

void	live(t_vm *vm, t_carry *cr);
void	ld(t_vm *vm, t_carry *cr);
void	st(t_vm *vm, t_carry *cr);
void	add(t_vm *vm, t_carry *cr);
void	sub(t_vm *vm, t_carry *cr);
void	and(t_vm *vm, t_carry *cr);
void	or(t_vm *vm, t_carry *cr);
void	xor(t_vm *vm, t_carry *cr);
void	zjmp(t_vm *vm, t_carry *cr);
void	ldi(t_vm *vm, t_carry *cr);
void	sti(t_vm *vm, t_carry *cr);
void	frk(t_vm *vm, t_carry *cr);
void	lld(t_vm *vm, t_carry *cr);
void	lldi(t_vm *vm, t_carry *cr);
void	lfrk(t_vm *vm, t_carry *cr);
void	aff(t_vm *vm, t_carry *cr);

/*
** Common functions:
*/

int		display_usage();
void	parsing(int argc, char **argv, t_vm	*vm);
void	vm_init(t_vm *vm);

#endif
