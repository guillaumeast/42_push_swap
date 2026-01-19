#ifndef CONFIG_PRIV_H
# define CONFIG_PRIV_H

# include "config.h"
# include <sys/types.h>

/*
* Note: to add a new algo:
* 1. Add the corresponding binary value to the following defines
* 2. Add the corresponding macro to the input_init() array (algos_1 or algos_2) in config_generator.c
* 3. Add the corresponding logic to config_convert() in config.c
* Note: to add a new opti:
* 1. Add the corresponding bool to the following t_config struct
* 2. Add the corresponding binary values to the above defines (OPTI + OPTI_COMPAT)
* 3. Add the corresponding macros to the input_init() arrays (optis and optis_compat) in config_generator.c
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
# define MEDIAN			65536U		/* 00000001 00000000 00000000 */
# define MEDIAN_COMPAT	131073U		/* 00000111 00000000 00000001 */
# define LIS			131072U		/* 00000010 00000000 00000000 */
# define LIS_COMPAT		458755U		/* 00000111 00000000 00000011 */
# define SWAP			262144U		/* 00000100 00000000 00000000 */
# define SWAP_COMPAT	458755U		/* 00000111 00000000 00000011 */

typedef struct s_chunk_list
{
	t_chunk	*data;
	size_t	count;
}	t_chunk_list;

/* ---------- config_generator.c ---------- */

uint	*generate_configs(size_t *count_ret);

/* ---------- chunk_generator.c ---------- */

bool	chunk_generate(t_chunk_list *chunks, size_t values_count);

#endif
