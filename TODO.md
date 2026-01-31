# SUBMIT

✅ `Norminette`
- Update `README.md` => perso version (explication old_src, visualizer, tester, tester perso...)
- Update `README.md` => 42 version
- Copy `libft` **files** instead of **submodule**
- Remove `push_swap_visualizer`
- Remove `tester_SimonCROS`
- Remove `tests`
- Remove `docs`
- Remove `.gitmodules`
- Remove `imgui.ini`
- Remove `TODO.md`

# TODO

- `opti_sort_b()`:
	- if (config->opti_median && B[0] < median(B)):						=> `rb()`
	- if (B[1] > B[0] > B[2]):
		- if		(config->opti_lis_swap && config->lis.swap[A[0]])	=> `ss()` + config->lis.swap[A[0]] = false; config->lis.swap_count--
		- else if	(!config->opti_lis_swap && A[1] < A[0] < A[2])		=> `ss()`
		- else															=> `sb()`
- `opti_rebuild()`:
	- if B contains value(s) between a_last_keep and A[0] => push them to A using greedy method:
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
- `opti_backtracking()`: branch and bound

🧪 Tests **4 nombres** (`sort_three()` will handle it so **don't compute swaps** if stack->len <= 3)
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
✅ `3 0 2 1 4`		=> BEST => swaps (2) = `2, 4`		| lis (5) = `0 1 2 3 4`
✅ `0 3 2 1 4`		=> BEST => swaps (3) = `0, 2, 4`	| lis (5) = `0 1 2 3 4`
✅ `0 2 3 4 5 1`		=> BEST => swaps (1) = `1`			| lis (6) = `0 1 2 3 4 5`
✅ `2 0 3 4 5 1`		=> BEST => swaps (2) = `2, 1`		| lis (6) = `0 1 2 3 4 5`
✅ `5 3 6 2 0 4 1`	=> BEST => swaps (1) = `5`			| lis (5) = `0 1 3 5 6`

🚨 Conflict = 1 with this input
`./push_swap 5 13 7 8 9 6 11 4 0 12 2 14 3 10 1` => ✅ solved correctly

🚨 Conflict = 1 with this input
`./push_swap 42 35 80 50 36 85 52 98 30 76 9 69 54 96 24 97 66 56 40 25 53 37 41 34 74 65 5 6 71 88 46 45 75 81 49 55 47 78 14 0 32 2 60 70 4 7 27 12 38 21 59 64 33 73 82 19 90 77 95 99 1 68 26 22 13 15 94 39 72 86 23 87 11 89 20 63 92 31 79 93 28 61 48 29 3 84 10 67 16 62 91 58 17 57 43 8 18 51 83 44`

🚨 Conflict = 1 with this input
`./push_swap 44 16 53 27 67 34 14 61 43 49 18 10 63 65 73 8 86 80 30 25 9 99 69 82 62 75 35 40 45 41 64 3 23 78 79 91 47 13 46 56 96 54 5 15 95 51 98 20 36 60 71 26 93 38 39 76 0 84 32 85 12 94 97 88 33 59 66 77 70 89 57 52 58 22 74 21 55 90 11 68 7 1 72 83 2 42 48 6 31 81 50 87 37 92 17 19 29 28 4 24`
