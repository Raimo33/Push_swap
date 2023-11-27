/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <craimond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:26:27 by craimond          #+#    #+#             */
/*   Updated: 2023/11/27 19:31:30 by craimond         ###   ########.fr       */
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
static void	handle_cases(t_list **stack_a, t_list **stack_b, int *sorted_arr, char **result);
static char	is_sorted(t_list *stack, int *sorted_arr);

// int main(void)
// {
//     char *numbers[] = {"./push_swap", "-230", "228", "175", "219", "221", "-154", "149", "-205", "40", "-216", "-11", "195", "-188", "129", "-93", "140", "212", "113", "-244", "-208", "104", "166", "-241", "-156", "19", "-152", "25", "226", "-7", "92", "203", "230", "46", "71", "-46", "23", "69", "-142", "-200", "-24", "-82", "196", "-129", "100", "-160", "-195", "-170", "-186", "-60", "-168", "236", "231", "-10", "63", "-63", "-120", "-190", "-4", "-35", "-148", "191", "-178", "-125", "-114", "217", "-113", "147", "1", "127", "146", "2", "97", "103", "-100", "-27", "177", "-137", "83", "223", "36", "-81", "94", "56", "-225", "59", "-136", "-141", "-233", "-34", "-6", "-32", "116", "-85", "-146", "84", "-189", "189", "-211", "99", "12", "-14", "-19", "-214", "-69", "-16", "-147", "144", "242", "68", "-23", "-187", "-181", "134", "-99", "169", "-209", "150", "198", "-132", "159", "-150", "4", "164", "247", "130", "131", "-246", "58", "21", "-185", "-163", "-184", "-5", "148", "-106", "-242", "-161", "194", "-221", "-139", "133", "205", "249", "-162", "-41", "-231", "5", "-40", "-94", "-26", "-83", "-123", "-176", "10", "-226", "-103", "-96", "96", "34", "-207", "-31", "14", "-153", "-239", "-1", "101", "-201", "186", "155", "7", "3", "-247", "-238", "-12", "-72", "76", "208", "72", "24", "-198", "-3", "86", "45", "-42", "-68", "163", "165", "-49", "11", "188", "168", "-50", "88", "124", "-9", "121", "-135", "-112", "91", "-173", "-77", "229", "-138", "-21", "119", "-223", "-134", "29", "-36", "-228", "232", "-248", "179", "-45", "67", "211", "143", "238", "184", "111", "-89", "28", "170", "-227", "42", "-29", "44", "79", "-194", "174", "-124", "136", "102", "128", "224", "37", "206", "-44", "-75", "245", "-121", "-67", "118", "-249", "15", "181", "8", "-61", "-117", "52", "73", "75", "126", "-73", "123", "-111", "30", "139", "-97", "-232", "-217", "80", "222", "-213", "41", "0", "-116", "250", "-64", "-177", "-2", "-167", "-108", "200", "32", "-70", "142", "-87", "215", "-118", "-30", "-105", "213", "209", "-180", "-109", "-192", "-37", "16", "-219", "-39", "110", "-199", "-59", "-115", "-182", "105", "22", "182", "117", "81", "38", "154", "-179", "17", "-220", "151", "62", "115", "220", "-55", "108", "-52", "-74", "244", "-145", "-57", "-92", "-90", "193", "176", "-174", "201", "172", "-25", "-236", "234", "243", "31", "-191", "-166", "-164", "135", "167", "6", "61", "-204", "178", "20", "-18", "218", "-22", "246", "152", "-43", "225", "241", "-215", "187", "-212", "214", "162", "-143", "74", "120", "55", "-169", "-172", "-104", "-133", "70", "-158", "-157", "-126", "-110", "-91", "57", "107", "-33", "-119", "49", "-175", "204", "82", "95", "-165", "197", "18", "-71", "192", "-13", "54", "132", "-140", "53", "-28", "-131", "235", "153", "43", "51", "-98", "190", "-76", "39", "-102", "-101", "-159", "171", "156", "-95", "-222", "-84", "65", "141", "93", "-80", "-51", "-203", "64", "-171", "-234", "199", "237", "106", "-88", "-210", "114", "-47", "-206", "183", "-237", "239", "9", "-183", "138", "210", "-48", "137", "-54", "-58", "-243", "-151", "85", "227", "-8", "-245", "-149", "-15", "-155", "233", "-86", "35", "-107", "27", "-56", "122", "157", "202", "13", "145", "-130", "-17", "-122", "-197", "158", "-78", "112", "248", "-240", "-127", "-235", "-20", "-202", "89", "-79", "26", "-193", "78", "50", "125", "66", "90", "47", "-62", "60", "-128", "160", "180", "33", "216", "-196", "-229", "87", "-144", "98", "173", "185", "-65", "48", "-38", "109", "207", "77", "240", "-224", "-218", "161", "-66", "-53"};
//     main2(501, numbers);
// }

int	main(int argc, char **argv)
{
	char	buffer[N_MOVES];
	t_list	**stack_a;
	t_list	**stack_b;
	int		*sorted_arr;
	char	*result;

	if (argc < 3 || !argv || !(*argv))
		return (0);
	result = buffer;
	sorted_arr = malloc(sizeof(int) * (argc - 1));
	stack_a = malloc(sizeof(t_list *));
	stack_b = malloc(sizeof(t_list *));
	*stack_a = 0;
	*stack_b = 0;
	if (!result++ || !stack_a || !stack_b || !sorted_arr)
		error(1);
	init(argc, &sorted_arr, argv, stack_a);
	if (check_duplicates(sorted_arr, argc - 1))
		handle_cases(stack_a, stack_b, sorted_arr, &result);
	merge_moves(&result);
	f_lstclear(stack_a);
	free(sorted_arr);
}

static void	init(int argc, int **sorted_arr, char **argv, t_list **stack_a)
{
	t_list	*new_node;
	int		i;

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
		if (sorted_arr[size - 1] == sorted_arr[size])
			error(2);
	return (1);
}

static void	handle_cases(t_list **stack_a, t_list **stack_b, int *sorted_arr, char **result)
{
	t_list	*min;
	int		key_nbr;
	short	i;
	short	j;
	short	size;

	size = lst_len(*stack_a);
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
			i = SHRT_MAX - 1;
			j = N_CHUNKS(size);
			while (*stack_b)
			{
				if (++i >= size / N_CHUNKS(size))
				{
					j--;
					key_nbr = sorted_arr[size / N_CHUNKS(size) * j - (2 * j > 0)];
					i = -1;
				}
				push_easiest(stack_b, stack_a, key_nbr, result);
			}
		}
		adjust(stack_a, sorted_arr, result);
	}
}

static char	is_sorted(t_list *stack, int *sorted_arr)
{
	t_list	*tmp;
	short	i;
	short	arr_len;

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
