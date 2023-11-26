/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <craimond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:26:27 by craimond          #+#    #+#             */
/*   Updated: 2023/11/26 18:14:26 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// #include "a_to_b.c"
// #include "b_to_a.c"
// #include "general_utils.c"
// #include "lst_utils.c"
// #include "display.c"
// #include "stack_operations.c"

static void	init(int argc, int **sorted_arr, char **argv, t_list **stack_a);
static char	check_duplicates(int *sorted_arr, short size);
static void	handle_cases(t_list **stack_a, t_list **stack_b, int *sorted_arr, short size, char **result);
static char	is_sorted(t_list *stack, int *sorted_arr);

// int	main(void)
// {
//     main2(501, (char *[]){"./push_swap", "278", "-287", "408", "-348", "63", "-254", "243", "228", "-249", "121", "336", "-118", "369", "-375", "10", "-72", "252", "162", "-36", "255", "-385", "42", "244", "-468", "120", "497", "-115", "452", "-288", "139", "426", "-386", "137", "216", "-455", "29", "164", "-306", "434", "457", "-50", "147", "-458", "133", "246", "-431", "435", "474", "-394", "355", "184", "-18", "102", "-209", "195", "291", "-475", "2", "258", "-419", "477", "149", "-354", "339", "143", "-240", "395", "-311", "361", "166", "-343", "62", "-13", "285", "200", "-428", "127", "203", "-299", "125", "471", "-150", "218", "191", "-80", "1", "-197", "74", "-146", "168", "388", "-293", "233", "78", "-59", "317", "-257", "377", "263", "-405", "177", "292", "-356", "488", "86", "109", "-192", "463", "-202", "105", "28", "-500", "493", "-407", "70", "309", "-113", "483", "-414", "332", "338", "-93", "204", "85", "-79", "222", "-160", "242", "268", "-196", "181", "-351", "69", "-302", "207", "-424", "171", "290", "-27", "213", "-378", "31", "-469", "281", "-6", "182", "-438", "376", "350", "-461", "289", "145", "-236", "106", "-379", "413", "382", "-179", "326", "282", "-344", "320", "294", "301", "-211", "433", "-345", "205", "-194", "193", "23", "-415", "398", "110", "-201", "251", "64", "-167", "248", "-449", "56", "409", "-286", "274", "358", "129", "-447", "334", "-215", "270", "131", "-136", "490", "33", "92", "-214", "126", "-155", "47", "-473", "212", "156", "-439", "132", "265", "-117", "198", "38", "-329", "397", "324", "-273", "8", "492", "-389", "15", "221", "-406", "272", "335", "-97", "420", "77", "-250", "51", "396", "-199", "429", "-224", "170", "-450", "443", "-491", "472", "-436", "174", "-141", "46", "340", "-34", "370", "-122", "485", "-98", "422", "-30", "24", "-367", "496", "-277", "322", "-381", "45", "-296", "12", "-342", "456", "337", "-217", "95", "-430", "43", "-183", "100", "-76", "401", "-159", "41", "-176", "465", "-84", "314", "227", "-48", "130", "-261", "157", "260", "-234", "325", "-441", "498", "321", "303", "-52", "310", "39", "-262", "267", "225", "-135", "54", "-304", "384", "-466", "440", "247", "-9", "279", "-499", "101", "-365", "58", "-165", "112", "134", "-190", "331", "187", "-89", "280", "220", "-313", "316", "103", "-494", "353", "271", "-448", "208", "-241", "482", "300", "178", "-142", "295", "-61", "489", "116", "-82", "417", "-104", "453", "-111", "373", "371", "-67", "481", "245", "-480", "186", "399", "-467", "94", "-53", "346", "-108", "73", "-479", "119", "-333", "161", "-158", "231", "-484", "154", "5", "-151", "114", "-235", "185", "-206", "26", "-391", "423", "387", "-410", "276", "44", "-402", "368", "253", "-172", "476", "-232", "444", "-418", "68", "-3", "259", "-446", "462", "-312", "393", "-189", "210", "-283", "239", "-432", "81", "-223", "315", "-256", "400", "-99", "427", "-383", "107", "-140", "372", "308", "-128", "71", "-412", "229", "-323", "266", "-341", "307", "-442", "318", "-363", "4", "-96", "362", "-219", "175", "-470", "445", "-153", "374", "238", "-124", "57", "-264", "75", "65", "-66", "357", "-411", "87", "347", "-390", "275", "-437", "60", "-330", "32", "11", "-22", "226", "380", "-366", "152", "305", "-352", "14", "-328", "403", "-298", "486", "392", "-230", "425", "-148", "83", "-487", "55", "40", "-173", "460", "-359", "478", "-144", "188", "-90", "49", "-169", "464", "-138", "451", "163", "-269", "35", "-327", "237", "-421", "459", "91", "-284", "19", "-495", "37", "360", "-17", "20", "-16", "297", "-416", "7", "-25", "454", "-319", "364", "-88", "123", "-404", "21", "-180", "349"});
// }

int	main(int argc, char **argv)
{
	t_list	**stack_a;
	t_list	**stack_b;
	int		*sorted_arr;
	char	*result;

	if (argc < 3 || !argv || !(*argv))
		return (0);
	result = ft_calloc(20000, sizeof(char));
	sorted_arr = malloc(sizeof(int) * (argc - 1));
	stack_a = malloc(sizeof(t_list *));
	stack_b = malloc(sizeof(t_list *));
	if (!result++ || !stack_a || !stack_b || !sorted_arr)
		error(2);
	init(argc, &sorted_arr, argv, stack_a);
	if (check_duplicates(sorted_arr, argc - 1))
		handle_cases(stack_a, stack_b, sorted_arr, argc - 1, &result);
	merge_moves(&result);
	f_lstclear(stack_a);
	free(sorted_arr);
}

static void	init(int argc, int **sorted_arr, char **argv, t_list **stack_a)
{
	int		i;
	t_list	*new_node;

	i = 0;
	while (++i < argc)
		(*sorted_arr)[i - 1] = ft_atoi(argv[i]);
	while (--i > 0)
	{
		new_node = f_lstnew((*sorted_arr)[i - 1]);
		if (!new_node)
			error(2);
		ft_lstadd_front(stack_a, new_node);
	}
	quicksort((*sorted_arr), 0, argc - 2);
}

static char	check_duplicates(int *sorted_arr, short size)
{
	while (--size > 0)
	{
		if (sorted_arr[size - 1] == sorted_arr[size])
			return (0);
	}
	return (1);
}

static void	handle_cases(t_list **stack_a, t_list **stack_b, int *sorted_arr, short size, char **result)
{
	t_list	*min;
	short	i;
	short	j;
	int		key_nbr;

	if (size == 2 && (*stack_a)->n > (*stack_a)->next->n)
		write(1, "sa\n", 3);
	else if (size == 3)
		handle_three(stack_a, 'a', result);
	else
	{
		if (is_sorted(*stack_a, sorted_arr) == 0)
		{
			divide_into_chunks(stack_a, stack_b, sorted_arr, N_CHUNKS(size), result);
			handle_three(stack_a, 'a', result);
			i = 2; //perche' ho gia' 3 elementi (appartenenti al primo stack) in A
			j = N_CHUNKS(size) - 1;
			key_nbr = sorted_arr[size / N_CHUNKS(size) * j - 1];
			while (*stack_b)
			{
				push_easiest(stack_b, stack_a, key_nbr, result);
				if (++i >= size / N_CHUNKS(size))
				{
					j--;
					key_nbr = sorted_arr[size / N_CHUNKS(size) * j - 1];
					i = 0;
				}
			}
		}
		adjust(stack_a, sorted_arr, result);
	}
}

static char	is_sorted(t_list *stack, int *sorted_arr)
{
	short	i;
	short	arr_len;
	t_list	*tmp;

	i = -1;
	arr_len = lst_len(stack);
	tmp = stack;
	while (tmp && tmp->n == sorted_arr[++i])
		tmp = tmp->next;
	if (!tmp)
		return (1);
	while (sorted_arr[i] != tmp->n)
		i++;
	while (sorted_arr[++i - 1] == tmp->n)
	{
		if (i >= arr_len)
			i = 0;
		tmp = tmp->next;
		if (!tmp)
			return (-1);
	}
	return (0);
}
