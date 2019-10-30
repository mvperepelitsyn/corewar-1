/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thansen <thansen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:09:22 by thansen           #+#    #+#             */
/*   Updated: 2019/10/30 16:09:23 by thansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm_asm.h"

void	add_label(t_label **list, t_label *new)
{
	t_label	*current;

	if (list)
	{
		if (*list)
		{
			current = *list;
			while (current->next)
				current = current->next;
			current->next = new;
		}
		else
			*list = new;
	}
}

void	add_mention(t_mention **list, t_mention *new)
{
	t_mention	*current;

	if (list)
	{
		if (*list)
		{
			current = *list;
			while (current->next)
				current = current->next;
			current->next = new;
		}
		else
			*list = new;
	}
}

t_label	*find_label(t_label *list, char *name)
{
	t_label	*label;

	label = list;
	while (label)
	{
		if (!ft_strcmp(label->name, name))
			return (label);
		label = label->next;
	}
	return (label);
}

void	replace_mentions(t_parser *file)
{
	t_label		*label;
	t_mention	*mention;

	label = file->labels;
	while (label)
	{
		if (label->op_pos == -1)
			label_error(label);
		else
		{
			mention = label->mentions;
			while (mention)
			{
				if (mention->size == 2)
					int32_to_bytecode(file->code, mention->pos,
								(int16_t)(label->op_pos - mention->op_pos),
								mention->size);
				else
					int32_to_bytecode(file->code, mention->pos,
						label->op_pos - mention->op_pos, mention->size);
				mention = mention->next;
			}
		}
		label = label->next;
	}
}
