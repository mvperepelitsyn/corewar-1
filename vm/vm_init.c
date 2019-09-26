# include "vm.h"

void	vm_init(t_vm *vm)
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
}
