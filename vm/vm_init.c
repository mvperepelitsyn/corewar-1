# include "vm.h"

void		carriages_init(t_vm *vm, int champ_nbr, int position)
{
	t_carry	*cr;

	if (!(cr = ft_memalloc(sizeof(t_carry))))
		ft_error("Malloc couldn't allocate the memory!\n");
	cr->reg[0] = (unsigned int)(-champ_nbr);
	cr->car_nbr = (unsigned int)champ_nbr;
	cr->color = champ_nbr;
	cr->position = position;
	cr->vm = vm;
	cr->next = vm->carriages;
	vm->carriages = cr;
	vm->car_count++;
}

static int alloc_back(t_vm *vm)
{
	int		i;

	if (!(vm->back = malloc(MEM_SIZE)))
		return (0);
	i = 0;
	while (i < MEM_SIZE)
	{
		vm->back[i] = 255;
		i++;
	}
	return (1);
}

static void	area_init(t_vm *vm)
{
	int		champ_area;
	int		champ_nbr;
	int		i;
	int		j;

	champ_area = MEM_SIZE / vm->champs_count;
	champ_nbr = 0;
	if (!(vm->area = ft_memalloc(MEM_SIZE)))
		ft_error("Malloc couldn't allocate the memory!\n");
	if (vm->v && !alloc_back(vm))
		ft_error("Malloc couldn't allocate the memory!\n");
	while (champ_nbr < vm->champs_count)
	{
		i = champ_area * champ_nbr;
		carriages_init(vm, champ_nbr + 1, i);
		j = 0;
		while (j < vm->processes[champ_nbr].code_size)
		{
			vm->area[i] = vm->processes[champ_nbr].code[j];
			vm->back[i] = champ_nbr - 1;
			i++;
			j++;
		}
		champ_nbr++;
	}
}

void		vm_init(t_vm *vm)
{
	vm->command[0] = (t_command) & live;
	vm->command[1] = (t_command) & ld;
	vm->command[2] = (t_command) & st;
	vm->command[3] = (t_command) & add;
	vm->command[4] = (t_command) & sub;
	vm->command[5] = (t_command) & and;
	vm->command[6] = (t_command) & or;
	vm->command[7] = (t_command) & xor;
	vm->command[8] = (t_command) & zjmp;
	vm->command[9] = (t_command) & ldi;
	vm->command[10] = (t_command) & sti;
	vm->command[11] = (t_command) & frk;
	vm->command[12] = (t_command) & lld;
	vm->command[13] = (t_command) & lldi;
	vm->command[14] = (t_command) & lfrk;
	vm->command[15] = (t_command) & aff;
	vm->last_alive = vm->champs_count;
	vm->cycles_to_die = CYCLE_TO_DIE;
	area_init(vm);
}
