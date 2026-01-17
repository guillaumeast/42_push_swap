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
// OPTI macros			(bits 17-24)	=> define each opti identifier
// OPTI_COMPAT macros	(bits  1-24)	=> define each opti compatibilities (bits 1-8: ALGO_1, bits 9-17: ALGO_2, bits 18-24: OPTI)
# define SWAP			65536U		/* 00000001 00000000 00000000 */
# define SWAP_COMPAT	1U			/* 00000000 00000000 00000001 */	/* only compatible with NAIVE ALGO_1 */

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
*	usage for algo_1:	config.algo_1	= (raw_config & ALGO_1_MASK)
*	usage for algo_2:	config.algo_2	= (raw_config & ALGO_2_MASK)
*	usage for options:	config.swap		= ((raw_config & OPTI_MASK) & SWAP) != 0
*	usage for options:	config.opti_2	= ((raw_config & OPTI_MASK) & OPTI_2) != 0
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
