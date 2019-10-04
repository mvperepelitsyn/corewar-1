#include "vm.h"
/*
void		ft_open_tetr(char *argv, t_atetr *mtetr)
{
	int		fd;

	if ((fd = open(argv, O_RDONLY)) < 0)
		ft_exit();
	ft_read_tetr(fd, mtetr);
}

void		ft_read_tetr(int fd, t_atetr *mtetr)
{
	char	*buf;
	int		i;
	int		n;
	int		l;

	i = 0;
	l = 0;
	buf = ft_strnew(21);
	while ((n = read(fd, buf, 21)))
	{
		l = n;
		ft_create_tetr(buf, i, mtetr);
		if (((*mtetr).count = i + 1) > 26)
			ft_exit();
		i++;
	}
	ft_strdel(&buf);
	if (n != 0 || l != 20)
		ft_exit();
}

static void	parce_ant_farm(t_intldta **indta)
{
	char	*things;
	char	**rms;
	int		fd;

	if ((fd = open(NAME, O_RDONLY)) < 0)
		fd = 0;
	get_next_line(fd, &things);
	(things == NULL) ? ft_error() : ft_println(things);
	while (things && (things[0] == '#' && things[1] != '#'))
	{
		ft_strdel(&things);
		get_next_line(fd, &things);
		if (things)
			ft_println(things);
	}
	(*indta)->num_ants = ft_latoi(things);
	if (ft_hm_wrd(things, ' ') != 1 || ((*indta)->num_ants <= 0 || (*indta)->
			num_ants != (int)ft_latoi(things)))
		ft_error();
	ft_strdel(&things);
	rms = NULL;
	graph_parser(indta, &things, rms, fd);
	if ((*indta)->li == -1)
		ft_error();
	links_assignment(indta);
}
*/

static void	check_magic_header(const unsigned char *rd_mag)
{
	unsigned char	*cnst_mag;
	unsigned int	cnst_int_mag;
	int 			i;

	i = 0;
	cnst_mag = (unsigned char *)ft_memalloc(sizeof(unsigned char) * 4);
	cnst_int_mag = COREWAR_EXEC_MAGIC;
	if (ft_islitendian())
		cnst_int_mag = ft_reverseint(cnst_int_mag);
	cnst_mag = (unsigned char *)&cnst_int_mag;
	while (i <= 3)
	{
//		ft_printf("rd_mag[%d] = %x\ncnst_mag[%d] = %x\n", i, rd_mag[i], i, cnst_mag[i]);
		if (rd_mag[i] != cnst_mag[i])
			ft_error("Wrong magic header!\n");
		i++;
	}
}

static void fill_the_name_champ(t_process *chmp, int fd)
{
	unsigned char	*champ_name;

	if (!(champ_name = (unsigned char *)ft_memalloc(sizeof(unsigned char) *
			128)))
		ft_error("Malloc couldn't allocate the memory!\n");
	if (read(fd, champ_name, 128) < 0)
		ft_error("There is no name in one of the champ files!\n");
	chmp->cmp_name = ft_strsub(champ_name, 0, ft_strlen(champ_name));
	ft_strdel(&champ_name);
	if (!(champ_name = (unsigned char *)ft_memalloc(sizeof(unsigned char) * 4)))
		ft_error("Malloc couldn't allocate the memory!\n");
	if (read(fd, champ_name, 4) < 0)
		ft_error("There is no NULL after champ name in one of the champ "
		   "files!\n");
	if (champ_name != NULL)
		ft_error("There is no NULL after champ name in one of the champ "
		   "files!\n");


}

static void fill_the_champ(t_process *chmp, char *file_name)
{
	unsigned char	*insight;
	char 			*clion_file_name;
	int				fd;

	clion_file_name = ft_strjoin("../", file_name);
	if ((fd = open(clion_file_name, O_RDONLY)) < 0)
		ft_error("There is nothing to open from champ file!\n");
	if (!(insight = (unsigned char *)ft_memalloc(sizeof(unsigned char) * 4)))
		ft_error("Malloc couldn't allocate the memory!\n");
	if ((read(fd, insight, 4)) < 0)
		ft_error("There is nothing to read from champ file!\n");
	check_magic_header(insight);
	ft_strdel(&insight);
	fill_the_name_champ(chmp, fd);
}


static void	check_num(t_process *champs, int num, char *champ_name)
{
	int i;

	i = 0;
	if (num > MAX_PLAYERS)
	{
		ft_printf("Wrong number for the champion %s! ", champ_name);
		ft_error("The number is too big!\n");
	}
	if (num < 1)
	{
		ft_printf("Wrong number for the champion %s! ", champ_name);
		ft_error("The number is too small!\n");
	}
	while (i < MAX_PLAYERS)
	{
		if (champs[i].cmp_nbr == num)
		{
			ft_printf("Wrong number for the champion %s! ", champ_name);
			ft_error("The number is a duplicate! "
			"Be more creative next time!\n");
		}
		i++;
	}
}

static void check_file_name(char *file_name, t_process *chmp, int num)
{
	int		i;
	char 	*tmp;

	i = ft_strlen(file_name);
	tmp = ft_strsub(file_name, i - 4, 4);
	if (!ft_strequ(tmp, ".cor"))
		ft_error("Wrong type of the champion file!\n");
	ft_strdel(&tmp);
	i = 0;
	if (num != 0)
	{
		chmp[num - 1].cmp_nbr = num;
		fill_the_champ(&chmp[num - 1], file_name);
	}
	else
	{
		while (i < MAX_PLAYERS)
		{
			if (chmp[i].cmp_nbr == 0)
			{
				chmp[i].cmp_nbr = i + 1;
				fill_the_champ(&chmp[i], file_name);
				break ;
			}
			i++;
		}
	}
}

static void	parse_champ(int argc, char **argv, t_vm *vm)
{
	int			l;
	long int 	num;

	l = 1;
	while (l <= argc)
	{
		if (ft_strequ(argv[l], "-n"))
		{
			l++;
			check_num(vm->processes, num = ft_atoi(argv[l]), argv[l + 1]);
			l++;
			check_file_name(argv[l], vm->processes, num);
		}
		else if (ft_strequ(argv[l], "-dump"))
		{
			l++;
			if ((num = ft_atoi(argv[l])) < 0 || num != (long long int)ft_latoi
			(argv[l]))
				ft_error("Invalid number after after flag -dump.\n");
		}
		else
			check_file_name(argv[l], vm->processes, 0);
		l++;
	}
}

static void	ft_set_champs_to_null(t_process *champs)
{
	int i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		champs[i].cmp_nbr = 0;
		champs[i].cmp_name = NULL;
		champs[i].cmp_cmnt = NULL;
		champs[i].code_size = 0;
		champs[i].code = NULL;
		i++;
	}
}

void		parsing(int argc, char **argv, t_vm	*vm)
{
	if (argc > 15)
		ft_error("Too many arguments");
	else
	{
		ft_set_champs_to_null(vm->processes);
		parse_champ(argc, argv, vm);
	}
}
