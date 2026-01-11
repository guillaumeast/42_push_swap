# Modules

## Parser
1. Parse	=> [`argv`]		_raw_ `string` **args**		=>	[`values`]	_real_ `int` **count** + _splitted_ `int` **values**
2. Sort		=> [`values`]	_splitted_ `int` **values**	=>	[`indexes`]	_sorted_ `int` **indexes**

## Stack manager
1. Stack	=> [`indexes`]	_sorted_ `int` **indexes**	=>	[`stack`]	_populated_ `t_stack` **stack**
2. Moves	=> `pa`, `pb`, ...

## Solver
1. LIS		=> Returns an array of `e_lis` (`KEEP`, `SWAP`, `PUSH`)
2. CHUNK	=> Returns an array of `t_chunk` (`min`, `max`, `pivot`)
3. WINDOW	=> Returns a `t_window` (`min`, `max`, `pivot`) and provides `update()` (grow / shrink following internal conditions compared to passed `t_context`)
4. COST		=> Returns the minimal `t_cost` for a given move (needs `index_from_range` and `index_to_range`)
5. BCKTRACK	=> Run a given `function` recursively on an initial `t_context` (context_0 -> function -> context_1 -> function -> context_2...)

---

1. LIS
2. while (A->value[0] is in LIS) => `ra`
3. `pb`
4. while (A->value[0] is in LIS) => `ra`
5. `pb`
6. 

---

- Do **bonus**
- Nominette `args.c`
- Add `README.md`
- Remove `debug_print.c`
- Copy `libft` files instead of submodule
- Remove **tester**
- Remove **docs**
