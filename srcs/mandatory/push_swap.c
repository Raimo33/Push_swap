/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <craimond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:26:27 by craimond          #+#    #+#             */
/*   Updated: 2023/12/02 15:20:04 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// #include "a_to_b.c"
// #include "b_to_a.c"
// #include "general_utils.c"
// #include "lst_utils.c"
// #include "display.c"
// #include "stack_operations.c"
// #include "macros.c"
// int	main2(int argc, char **argv);

static void	init(int argc, int **sorted_arr, char **argv, t_list **stack_a);
static char	check_duplicates(int *sorted_arr, short size);
static void	free_everything(char id, t_stacks stacks, int *sorted_arr,
				char *result);
static void	handle_cases(t_stacks stacks, int *sorted_arr, char **result,
				unsigned short size);

// int main(void)
// {
//     char *numbers[] = {"push_swap", "144", "414", "7", "181", "60", "481", "205", "321", "253", "439", "316", "146", "364", "500", "221", "199", "475", "227", "486", "465", "196", "40", "324", "233", "232", "386", "271", "449", "176", "341", "294", "390", "494", "182", "313", "234", "420", "351", "302", "322", "118", "159", "406", "241", "315", "363", "56", "327", "210", "418", "171", "125", "124", "57", "184", "131", "193", "137", "425", "172", "65", "344", "325", "222", "470", "371", "92", "160", "177", "108", "58", "207", "380", "31", "123", "87", "223", "299", "407", "266", "185", "226", "74", "430", "296", "98", "480", "46", "496", "228", "318", "338", "192", "79", "427", "51", "68", "225", "204", "377", "95", "173", "404", "140", "469", "403", "452", "369", "323", "358", "261", "431", "410", "183", "272", "200", "113", "305", "429", "293", "126", "168", "276", "311", "408", "163", "33", "461", "291", "409", "213", "14", "402", "388", "150", "355", "450", "466", "279", "319", "269", "284", "247", "489", "45", "178", "274", "462", "242", "91", "384", "295", "145", "136", "437", "438", "53", "493", "499", "36", "195", "389", "224", "288", "216", "218", "127", "396", "19", "260", "477", "153", "240", "382", "440", "434", "264", "482", "490", "243", "43", "298", "217", "188", "332", "167", "256", "154", "497", "307", "263", "116", "362", "474", "63", "280", "252", "258", "26", "329", "428", "492", "381", "473", "348", "349", "445", "83", "166", "239", "158", "3", "82", "250", "236", "426", "231", "411", "244", "23", "120", "353", "219", "314", "317", "273", "151", "476", "471", "8", "354", "383", "198", "47", "49", "453", "303", "73", "156", "375", "385", "238", "312", "76", "237", "75", "201", "105", "230", "206", "447", "143", "464", "416", "155", "100", "186", "10", "444", "335", "265", "301", "495", "190", "81", "352", "289", "94", "44", "129", "229", "84", "106", "21", "255", "138", "463", "297", "487", "179", "35", "187", "310", "119", "38", "17", "379", "6", "485", "248", "454", "304", "115", "423", "52", "246", "16", "212", "458", "132", "24", "211", "268", "412", "27", "28", "399", "191", "13", "367", "285", "128", "161", "457", "361", "251", "25", "135", "109", "86", "165", "421", "366", "468", "405", "278", "202", "422", "343", "133", "488", "340", "245", "162", "32", "472", "257", "235", "357", "378", "30", "368", "175", "401", "376", "397", "424", "275", "262", "215", "12", "88", "287", "398", "270", "141", "372", "164", "174", "72", "42", "77", "130", "342", "11", "393", "259", "99", "254", "448", "15", "460", "5", "39", "478", "374", "333", "331", "350", "64", "90", "443", "483", "283", "107", "267", "48", "67", "309", "169", "391", "360", "61", "89", "387", "117", "346", "9", "290", "281", "330", "435", "395", "498", "71", "22", "456", "149", "345", "467", "62", "442", "103", "66", "432", "4", "392", "451", "121", "104", "134", "300", "101", "2", "85", "441", "370", "96", "197", "400", "356", "373", "50", "365", "479", "97", "93", "203", "110", "249", "55", "139", "148", "29", "59", "37", "69", "336", "459", "194", "1", "157", "180", "214", "292", "102", "152", "436", "415", "80", "209", "142", "78", "446", "339", "34", "359", "220", "111", "484", "491", "334", "328", "282", "417", "419", "306", "20", "455", "277", "18", "147", "326", "308", "114", "189", "112", "122", "433", "286", "394", "208", "320", "54", "337", "70", "413", "170", "347", "41"};
//     main2(501, numbers);
// }

int	main(int argc, char **argv)
{
	t_stacks	stacks;
	int			*sorted_arr;
	char		*result;

	if (argc < 3)
	{
		if (argv[1])
			f_atol(argv[1]);
		return (0);
	}
	result = ft_calloc(N_MOVES, sizeof(char));
	sorted_arr = malloc(sizeof(int) * (argc - 1));
	stacks.sa = malloc(sizeof(t_list *));
	stacks.sb = malloc(sizeof(t_list *));
	*stacks.sa = 0;
	*stacks.sb = 0;
	if (!result++ || !stacks.sa || !stacks.sb || !sorted_arr)
		free_everything(1, stacks, sorted_arr, result - 1);
	init(argc, &sorted_arr, argv, stacks.sa);
	if (check_duplicates(sorted_arr, argc - 1))
		handle_cases(stacks, sorted_arr, &result, argc - 1);
	merge_moves(&result);
	f_lstclear(stacks.sa);
	free_everything(0, stacks, sorted_arr, result - 1);
}

static void	handle_cases(t_stacks stacks, int *sorted_arr, char **result,
unsigned short size)
{
	int	first;
	int	second;
	int	third;

	first = (*stacks.sa)->n;
	second = (*stacks.sa)->next->n;
	if (size == 2 && first > second)
		write(1, "sa\n", 3);
	else if (size == 3)
		handle_three(stacks.sa, 'a', result);
	else
	{
		third = (*stacks.sa)->next->next->n;
		if (is_sorted(*stacks.sa, sorted_arr) == 0)
		{
			if (first < second && third < second)
				swap(stacks.sa, 'a', result);
			divide_into_chunks(stacks, sorted_arr, result, size);
			handle_three(stacks.sa, 'a', result);
			while (*stacks.sb)
				push_cheapest(stacks, sorted_arr[size - 1], result);
		}
		adjust(stacks.sa, sorted_arr, result);
	}
}

static void	init(int argc, int **sorted_arr, char **argv, t_list **stack_a)
{
	t_list	*new_node;
	int		i;

	i = 0;
	while (++i < argc)
		(*sorted_arr)[i - 1] = f_atol(argv[i]);
	while (--i > 0)
	{
		new_node = f_lstnew((*sorted_arr)[i - 1]);
		if (!new_node)
			error(1);
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

static void	free_everything(char id, t_stacks stacks, int *sorted_arr,
	char *result)
{
	free(stacks.sa);
	free(stacks.sb);
	free(sorted_arr);
	free(result);
	if (id != 0)
		error(id);
}
