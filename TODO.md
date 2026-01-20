# LIS optimization

- Store LIS in config to avoid recomputing it each time
- Store two types of LIS:
	- LIS without swaps => compute all LIS => Tie break = LIS with less swap_count for the same len
	- LIS with swaps:
		- Compute all possible swaps (values[i] > values[i + 1] && (values[i + 2] = 0 || values[i] < values[i + 2]))
		- Compute LIS (with swapped stack)
		- Remove useless swaps (if swap[values[i]] = true && keep[values[i]] = false => swap[values[i] = false])
		- Tie break = LIS with less swap_count for the same len
- Add opti lis_swap:
	- if opti = lis => use config->lis data
	- if opti = lis_swap => user config->lis_swap data

⚠️ ===> Tests
- [3, 0, 2, 1, 4]		=> should swap [2 - 1] + [4 - 3]	=> [4, 0, 1, 2, 3]			=> LIS = 5
- [3, 2, 1, 0]			=> should swap [3 - 2] + [1 - 0]	=> [2, 3, 0, 1]				=> LIS = 4
- [5, 3, 6, 2, 0, 4, 1]	=> should swap [5 - 3] + [2 - 0]	=> [3, 5, 6, 0, 2, 4, 1]	=> LIS = 5

# Implement LIS vs LIS_SWAP in NAIVE and CHUNK algos

(use config->lis if config->opti_lis = true || use config->lis_swap if config->opti_lis_swap = true)

# Fix chunk + LIS

1. Swap if lis->swap[value] = true (even if values[i] is not in chunk !) (with optis!)
2. Rotate if lis->keep[value] || value < chunk.min || value > chunk.max
3. Else => push (with optis!)

# TODO

- Use hill climbing instead of bruteforce to find the best chunksize to use
- Add chunksize reduction to optis
- Add moves_normalize to delete useless moves: [`PB` -> `PA`], [`RA` -> `RRA`], swap combos, etc

# ALGO_1

1. K_SORT

# OPTI

1. BACKTRACK

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
