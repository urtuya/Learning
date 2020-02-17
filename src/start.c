#include "head.h"

void	get_oper_code(t_cursor *cursor, unsigned char *arena)
{
	if (cursor->cycles_before_op == 0)
	{
		cursor->op_code = arena[ft_addr(cursor->cur_position)] - 1;
		if (cursor->op_code >= 0 && cursor->op_code <= 0xF)
			cursor->cycles_before_op = op_tab[cursor->op_code].cycles_to_exec;
		else
			cursor->cycles_before_op = 0;
	}
	if ((cursor->cycles_before_op) > 0)
		cursor->cycles_before_op--;
}

void	set_types(t_cursor *cursor, int num, unsigned char *arena)
{	
	int i;

	cursor->arg_type[0] = (arena[ft_addr(cursor->cur_position + 1)] & 0b11000000) >> 6;
	cursor->arg_type[1] = (arena[ft_addr(cursor->cur_position + 1)] & 0b00110000) >> 4;
	cursor->arg_type[2] = (arena[ft_addr(cursor->cur_position + 1)] & 0b00001100) >> 2;
	i = 0;
	while (i < num)
	{
		if (cursor->arg_type[i] == IND_CODE)
			cursor->arg_type[i] = T_IND;
		else if (cursor->arg_type[i] != IND_CODE && cursor->arg_type[i] != DIR_CODE
				&& cursor->arg_type[i] != REG_CODE)
			return ;
		i++;
	}
}

int		try_exec_oper(t_cursor *cursor, unsigned char *arena) // 	NEED CHECK FOR EVERY OPERATION
{
	if (!(cursor->op_code >= 0 && cursor->op_code <= 0xF))
	{
		cursor->cur_position = ft_addr(cursor->cur_position + 1);
		return (0);
	}
	if (op_tab[cursor->op_code].code_type_args) // 1 = exist, 0 - non
		set_types(cursor, op_tab[cursor->op_code].arg_num, arena);
	else
		cursor->arg_type[0] = op_tab[cursor->op_code].arg[0]; //  -- T_REG or T_DIR
	if (!check_arg_type(cursor) || !check_registers(cursor, arena))
		return (0);
	return (1);
}

void	run_cursor(t_vm *vm, t_cursor *cursor)
{
	while (cursor)
	{
		get_oper_code(cursor, vm->arena);
		if (cursor->cycles_before_op == 0)
		{
			if (try_exec_oper(cursor, vm->arena))					// get ready before exec_oper
				vm->do_oper[cursor->op_code](cursor, vm);		 // do_oper is operation №op_code from operations.c YOU NEED FULL VM FOR LIVE AND OTHER OPERS, NOT JUST ARENA
			cursor->cur_position = ft_addr(cursor->cur_position + cursor->bytes_to_next_op);
			cursor->bytes_to_next_op = 0;
		}
		cursor = cursor->next;
	}
}

void	in_cycle(t_vm *vm) //25 lines)))))))
{
	t_cursor *cursor;

	cursor = vm->cursor;
	// if (!cursor)
	
	// 	ft_printf("hmmmm\n");
	while (cursor)
	{
		if (vm->num_of_cycles == vm->flag.num)
			print_dump(vm->flag, vm->arena);
		(vm->num_of_cycles)++;
		vm->cycles_before_check--;
		run_cursor(vm, cursor);
		// while (cursor)
		// {
		// 	get_oper_code(cursor, vm->arena);
		// 	if (cursor->cycles_before_op == 0)
		// 	{
		// 		if (try_exec_oper(cursor, vm->arena))					// get ready before exec_oper
		// 			vm->do_oper[cursor->op_code](cursor, vm);		 // do_oper is operation №op_code from operations.c YOU NEED FULL VM FOR LIVE AND OTHER OPERS, NOT JUST ARENA
		// 		cursor->cur_position = ft_addr(cursor->cur_position + cursor->bytes_to_next_op);
		// 		cursor->bytes_to_next_op = 0;
		// 	}
		// 	cursor = cursor->next;
		// }
		if ((vm->cycles_to_die > 0 && vm->cycles_before_check == 0)
			|| vm->cycles_to_die <= 0)
			inspection(vm, vm->cursor);
		cursor = vm->cursor;
	}
}
