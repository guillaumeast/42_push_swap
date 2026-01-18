#ifndef CONFIG_H
# define CONFIG_H

# include "state.h"
# include <stdbool.h>
# include <sys/types.h>

/*
* Note: to add a new algo:
* 1. Add the corresponding binary value to the following defines
* 2. Add the corresponding macro to the input_init() array (algos_1 or algos_2) in generator.c
* 3. Add the corresponding logic to config_convert() in config.c
* Note: to add a new opti:
* 1. Add the corresponding bool to the following t_config struct
* 2. Add the corresponding binary values to the above defines (OPTI + OPTI_COMPAT)
* 3. Add the corresponding macros to the input_init() arrays (optis and optis_compat) in generator.c
* 4. Add the corresponding logic to config_convert() in config.c
*/

// ALGO_1			(8 lowest bits)
# define ALGO_1_OFFSET	1
# define NAIVE			1U			/* 00000000 00000000 00000001 */
# define CHUNK			2U			/* 00000000 00000000 00000010 */
# define K_SORT			4U			/* 00000000 00000000 00000100 */

// ALGO_2			(8 mid bits)
# define ALGO_2_OFFSET	8
# define GREEDY			256U		/* 00000000 00000001 00000000 */

/* OPTIMIZATIONS	(8 highest bits)
*	8 lowest bits	= ALGO_1 compatibilities
*	8 previous bits	= ALGO_2 compatibilities
*	8 previous bits	= OPTI compatibilities
*/
# define OPTI_OFFSET	16
# define ALGO_1_MASK	255U		/* 00000000 00000000 11111111 */
# define ALGO_2_MASK	65280U		/* 00000000 11111111 00000000 */
# define OPTI_MASK		16711680U	/* 11111111 00000000 00000000 */
// OPTI macros			(bits 17-24)	=> opti identifier
// OPTI_COMPAT macros	(bits  1-24)	=> opti compatibilities (bits 1-8: ALGO_1, bits 9-17: ALGO_2, bits 18-24: OPTI)
# define SWAP			65536U		/* 00000001 00000000 00000000 */
# define SWAP_COMPAT	131073U		/* 00000111 00000000 00000001 */
# define MEDIAN			131072U		/* 00000010 00000000 00000000 */
# define MEDIAN_COMPAT	65537U		/* 00000111 00000000 00000001 */
# define LIS			262144U		/* 00000100 00000000 00000000 */
# define LIS_COMPAT		458753U		/* 00000111 00000000 00000001 */

/* config (uint) represents the whole config on 24 bits:
*	8 lowest bits	= ALGO_1
*	8 mid bits		= ALGO_2
*	8 highest bits	= OPTI_LIST
*/

typedef struct s_config
{
	const char	*algo_1_name;
	bool 		(*algo_1)(t_state *state, struct s_config *config);
	const char	*algo_2_name;
	bool 		(*algo_2)(t_state *state, struct s_config *config);
	const char	*opti_names;
	bool		swap;
	bool		median;
	bool		lis;
}	t_config;

// Returns a NULL terminated list of t_config (owned by the caller, use config_list_free() to free it)
t_config	**config_get_list(void);
// Frees each t_config and the array (array pointer is set to NULL)
void		config_list_free(t_config ***config_list);

// TODO: tmp debug
void	config_print_all(t_config **configs);
void	config_print(t_config *config, size_t index, bool print_index);

#endif
