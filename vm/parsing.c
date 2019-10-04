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

static void	check_magic_header(unsigned char *rd_mag)
{
	unsigned char	*cnst_mag;
	unsigned int	cnst_int_mag;
	int 			i;
	int 			j;

	i = 0;
	j = 3;
	cnst_mag = (unsigned char *)ft_memalloc(sizeof(unsigned char) * 4);
	cnst_int_mag = COREWAR_EXEC_MAGIC;
	cnst_mag = (unsigned char *)&cnst_int_mag;
	while (i <= 3)
	{
		if (rd_mag[j] != cnst_mag[i])
			ft_error("Wrong magic header!\n");
		i++;
		j--;
	}
}

static void fill_the_champ(t_process *chmp, char *file_name)
{
	unsigned char	*insight;
	char 			*clion_file_name;
	int				fd;

	clion_file_name = ft_strjoin("../", file_name);
	if ((fd = open(clion_file_name, O_RDONLY)) < 0)
		ft_error("There is nothing to open from champ file!\n");
	insight = (unsigned char *)ft_memalloc(sizeof(unsigned char) * 4);
	if ((read(fd, insight, 4)) < 0)
		ft_error("There is nothing to read from champ file!\n");
	check_magic_header(insight);
}


static void	check_num(t_process *champs, int num)
{
	int i;

	i = 0;
	if (num < 1 || num > MAX_PLAYERS)
		ft_error("Wrong number of champion file!\n");
	while (i < MAX_PLAYERS)
	{
		if (champs[i].cmp_nbr == num)
			ft_error("Wrong number of champion file!\n");
		i++;
	}
}

static void check_file_name(char *file_name, t_process *chmp, int num)
{
	int		i;
	char 	*tmp;

	tmp = NULL;
	i = ft_strlen(file_name);
	tmp = ft_strsub(file_name, i - 4, 4);
	if (!ft_strequ(tmp, ".cor"))
		ft_error("Wrong type of the champion file!\n");
	ft_strdel(&tmp);
	i = 0;
	if (num != 0)
		chmp->cmp_nbr = num;
	else
	{
		while (i < MAX_PLAYERS)
		{
			if (chmp[i].cmp_nbr == 0)

			i++;
		}
	}

	fill_the_champ(chmp, file_name);
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
			check_num(vm->processes, num = ft_atoi(argv[l]));
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

void		parsing(int argc, char **argv, t_vm	*vm)
{
	if (argc > 15)
		ft_error("Too many arguments");
	else
		parse_champ(argc, argv, vm);
}
