#ifndef CONFIG_PRIV_H
# define CONFIG_PRIV_H

# include <stdbool.h>
# include <stdlib.h>
# include <sys/types.h>

// ALGO_1			(8 lowest bits)
# define ALGO_1_OFFSET	1
# define NAIVE			1U			/* 00000000 00000000 00000001 */
# define LIS 			2U			/* 00000000 00000000 00000010 */
# define CHUNK			4U			/* 00000000 00000000 00000100 */
# define K_SORT			8U			/* 00000000 00000000 00001000 */

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

# define SWAP			65536U		/* 00000001 00000000 00000000 */
# define SWAP_COMPAT	1U			/* 00000000 00000000 00000001 */

/* config (int) represents the whole config on 24 bits:
*	8 lowest bits	= ALGO_1
*	8 mid bits		= ALGO_2
*	8 highest bits	= OPTI_LIST
*
*		USAGE EXAMPLE
*	add an ALGO_1 to config:	config + CHUNK
*	add an ALGO_2 to config:	config + GREEDY
*	add an OPTI to config:		config + ((SWAP >> 8) & OPTI_MASK)
*	add another OPTI to config:	config + ((OPTI_2 >> 8) & OPTI_MASK)
*	=> 00000000 00000011 00000001 00000100 => [ALGO_1 = CHUNK] + [ALGO_2 = GREEDY] + [OPTIs = SWAP + OPTI_2]
*	usage for algo_1:	if ((config & ALGO_1_MASK) == CHUNK)							=> { config.algo_1 = CHUNK }
*	usage for algo_2:	if ((config & ALGO_2_MASK) == GREEDY)							=> { config.algo_2 = GREEDY }
*	usage for options:	if (((config & OPTI_MASK) & ((SWAP >> 8) & OPTI_MASK)) != 0)	=> { config.swap = true }
*	usage for options:	if (((config & OPTI_MASK) & ((OPTI_2 >> 8) & OPTI_MASK)) != 0)	=> { config.opti_2 = true }
*/

typedef struct s_input
{
	const uint	*algos_1;
	const uint	*algos_2;
	const uint	*optis;
	const uint	*optis_compat;
	size_t		algos_1_count;
	size_t		algos_2_count;
	size_t		optis_count;
	size_t		couples_count;
	size_t		optis_max_combo_count;
	size_t		configs_count;
}	t_input;

uint	*generate_configs(size_t *count_ret);

#endif
