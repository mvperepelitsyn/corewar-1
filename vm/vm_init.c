# include "vm.h"

/*static void	op_init(t_vm *vm)
{
	vm->cmd_prms =
	{
		{1, 4, 0, 10, {T_DIR}},
		{2, 4, 1, 5, {T_DIR | T_IND, T_REG}},
		{3, 4, 1, 5, {T_REG, T_IND | T_REG}},
		{4, 4, 1, 10, {T_REG, T_REG, T_REG}},
		{5, 4, 1, 10, {T_REG, T_REG, T_REG}},
		{6, 4, 1, 6, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}},
		{7, 4, 1, 6, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}},
		{8, 4, 1, 6, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}},
		{9, 2, 0, 20, {T_DIR}},
		{10, 2, 1, 25, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}},
		{11, 2, 1, 25, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}},
		{12, 2, 0, 800, {T_DIR}},
		{13, 4, 1, 10, {T_DIR | T_IND, T_REG}},
		{14, 2, 1, 50, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}},
		{15, 2, 0, 1000, {T_DIR}},
		{16, 4, 1, 2, {T_REG}}
	}
}*/

void		vm_init(t_vm *vm)
{
	vm->command[0] = &live;
	vm->command[1] = &ld;
	vm->command[2] = &st;
	vm->command[3] = &add;
	vm->command[4] = &sub;
	vm->command[5] = &and;
	vm->command[6] = &or;
	vm->command[7] = &xor;
	vm->command[8] = &zjmp;
	vm->command[9] = &ldi;
	vm->command[10] = &sti;
	vm->command[11] = &frk;
	vm->command[12] = &lld;
	vm->command[13] = &lldi;
	vm->command[14] = &lfrk;
	vm->command[15] = &aff;
	// op_init(vm);
}
