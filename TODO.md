# LIS optimization

- Store two types of LIS:
	- LIS without swaps => compute all LIS => Tie break = LIS with less swap_count for the same len
	- LIS with swaps:
		- Compute all possible swaps (values[i] > values[i + 1] && (values[i + 2] = 0 || values[i] < values[i + 2]))
		- Compute LIS (with swapped stack)
		- Remove useless swaps (if swap[values[i]] = true && (keep[values[i]] = false || keep[values[i + 1]] = false) => swap[values[i] = false])
		- Tie break = LIS with less swap_count for the same len

**LIS_SWAP MANAGEMENT**
1. STACK_1 => Compute swaps except the two last indexes (they depend on indexes 0 and 1 possible swaps)
2. If STACK_1 didn't swap 0 and didn't swap 1:
	- Compute two last indexes swaps
3. If STACK_1 did swap 0 or did swap 1:
	- STACK_2 = stack_dup(STACK_1)
	- Compute 2 last swaps from STACK_1 (with swap 0/1)
	- Remove first swap (0 or 1) from STACK_2
	- Compute 2 last swaps from STACK_2 (without swap 0/1)
4. Run LIS (best = highest len => if equality => lowest swap_count wins):
	- LIS_1 = best LIS of STACK_1
	- LIS_2 = best LIS of STACK_2 (**only if STACK_2 exists**)
5. Return best LIS between LIS_1 and LIS_2

🧪 Tests **<= 3 nombres**
- `sort_three()` will handle it so **don't compute swaps**

🧪 Tests **4 nombres**
✅ `0 1 2 3`			=> BEST => swaps (0)				| lis (4) = `0 1 2 3`		| 🐛
✅ `0 1 3 2`			=> BEST => swaps (1) = `3`			| lis (4) = `0 1 2 3`		| 🐛
✅ `0 2 1 3`			=> BEST => swaps (1) = `2`			| lis (4) = `0 1 2 3`		| 🐛
✅ `0 2 3 1`			=> BEST => swaps (1) = `1`			| lis (4) = `0 1 2 3`		| 🐛
✅ `0 3 1 2`			=> BEST => swaps (1) = `0`			| lis (4) = `0 1 2 3`		| 🐛
✅ `0 3 2 1`			=> BEST => swaps (2) = `0 2`		| lis (4) = `0 1 2 3`		| 🐛

✅ `1 0 2 3`			=> BEST => swaps (1) = `1`			| lis (4) = `0 1 2 3`		| 🐛 
✅ `1 0 3 2`			=> BEST => swaps (2) = `0 2`		| lis (4) = `0 1 2 3`		| 🐛 
✅ `1 2 0 3`			=> BEST => swaps (1) = `0`			| lis (4) = `0 1 2 3`		| 🐛 
✅ `1 2 3 0`			=> BEST => swaps (0)				| lis (4) = `0 1 2 3`		| 🐛 
✅ `1 3 0 2`			=> BEST => swaps (1) = `2`			| lis (4) = `0 1 2 3`		| 🐛 
✅ `1 3 2 0`			=> BEST => swaps (1) = `3`			| lis (4) = `0 1 2 3`		| 🐛 

✅ `2 0 1 3`			=> BEST => swaps (1) = `3`			| lis (4) = `0 1 2 3`		| 🐛 
✅ `2 0 3 1`			=> BEST => swaps (1) = `0`			| lis (4) = `0 1 2 3`		| 🐛 
✅ `2 1 0 3`			=> BEST => swaps (2) = `0 2`		| lis (4) = `0 1 2 3`		| 🐛 
✅ `2 1 3 0`			=> BEST => swaps (1) = `2`			| lis (4) = `0 1 2 3`		| 🐛 
✅ `2 3 0 1`			=> BEST => swaps (0)				| lis (4) = `0 1 2 3`		| 🐛 
✅ `2 3 1 0`			=> BEST => swaps (1) = `1`			| lis (4) = `0 1 2 3`		| 🐛 

✅ `3 0 1 2`			=> BEST => swaps (0)				| lis (4) = `0 1 2 3`		| 🐛 
✅ `3 0 2 1`			=> BEST => swaps (1) = `2`			| lis (4) = `0 1 2 3`		| 🐛 
✅ `3 1 0 2`			=> BEST => swaps (1) = `1`			| lis (4) = `0 1 2 3`		| 🐛 
✅ `3 1 2 0`			=> BEST => swaps (1) = `0`			| lis (4) = `0 1 2 3`		| 🐛 
✅ `3 2 0 1`			=> BEST => swaps (1) = `3`			| lis (4) = `0 1 2 3`		| 🐛 
✅ `3 2 1 0`			=> BEST => swaps (1) = `0 2`		| lis (4) = `0 1 2 3`		| 🐛 

🧪 Tests **>= 5 nombres**
⚠️ `3 0 2 1 4`		=> BEST => swaps (2) = `2, 4`		| lis (5) = `0 1 2 3 4`
⚠️ `0 3 2 1 4`		=> BEST => swaps (3) = `0, 2, 4`	| lis (5) = `0 1 2 3 4`
⚠️ `0 2 3 4 5 1`	=> BEST => swaps (1) = `1`			| lis (6) = `0 1 2 3 4 5`
⚠️ `2 0 3 4 5 1`	=> BEST => swaps (2) = `2, 1`		| lis (6) = `0 1 2 3 4 5`
⚠️ `5 3 6 2 0 4 1`	=> BEST => swaps (1) = `5`			| lis (5) = `0 1 3 5 6`

# Implement LIS vs LIS_SWAP in NAIVE and CHUNK algos

(use config->lis if config->opti_lis = true || use config->lis_swap if config->opti_lis_swap = true)

# Fix chunk + LIS

1. Swap if lis->swap[value] = true (even if values[i] is not in chunk !) (with optis!)
2. Rotate if lis->keep[value] || value < chunk.min || value > chunk.max
3. Else => push (with optis!)

# TODO

- Use hill climbing instead of bruteforce to find the best chunksize to use
- Add chunksize reduction to optis
- Add moves_normalize to delete useless moves: `NO_OP`, [`PB` -> `PA`], [`RA` -> `RRA`], swap combos, etc

# ALGO_1

1. K_SORT

# OPTI

1. BACKTRACK
2. EARLY_REINTEGRATION
	- if (keep[A[0] == true]):
		- if (KEEP_LAST == NULL):
			- KEEP_LAST = A[0]
		- else
			- KEEP_CURRENT = A[0]
			- TARGET_COUNT = values in B which are > KEEP_LAST and are < KEEP_CURRENT
			- while (TARGET_COUNT > 0)
				- PA(greedy/highest value of B between KEEP_LAST and KEEP_CURRENT)
				- keep[A[0]] = true
				- TARGET_COUNT--
			- KEEP_LAST = KEEP_CURRENT

# CHECKER

1. Do it!

---

- `Nominette`
- Update `README.md`
- Copy `libft` **files** instead of **submodule**
- Remove all `TMP: remove before submit` targets (don't forget Makefile!)
- Remove `push_swap_visualizer`
- Remove `tester_SimonCROS`
- Remove `tests`
- Remove `docs`
- Remove `.gitmodules`
- Remove `imgui.ini`
- Remove `TODO.md`
