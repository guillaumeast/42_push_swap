# Push_swap

## High-level flow

1. Parse `args`
2. Validate `args` (`arg is not an integer`, `arg > INT_MAX`, `arg < INT_MIN`, duplicate args, ...)
3. Replace each `value` with `sorted_index`
4. Vider `A` par `chunks`
5. Reconstruire `A` depuis `B` avec méthode `greedy`

## Extraction

Extract values from `A` to `B` in `chunks` of `k` size.

### Find the (approximate) best `k` value

`k ≈ c * √n`:
- `c` depends on `B` organisation strategy
- `n` is the number of value to sort (aka initial `A` size)

1. First approximation: `k = 2√n`:
	- `√n`	=> Split complexity equaly between `extraction` and `reconstruction`
	- `2`	=> bad `k` impacts ~2 times more `reconstruction` than `extraction`
2. Test few `k` values around this approximation to find a "good enough" `k` value
	- `k`, `1.5k`, `2k` => and re-do it inside two best options

### Push `A` values to `B`, `chunk` by `chunk`

1. Find the nearest `A` value within current `chunk`
2. Push it to `B`
3. If `value > (chunk.min + chunk.max) / 2` => rotate `B` to put it at the bottom of `B`

- 1. and 2. pre-sort `B`
- 3. Ensures `B.min` and `B.max` are close enough to `B` ends

## Reconstruction

### (Option A) Max-first reconstruction

1. Find `max` value in `B`
2. Push it to `A`

### (Option B) Optimized max-first reconstruction

1. Find `max` value in `B`
2. Find `max-1` value in `B`
3. Push the closest one to `A`
4. Push the other one to `A`
5. Swap `A` 2 first values if `max-1` has been pushed to `A` before `max`

Checking also `max-1` avoid to do unnecessary `B` rotations to directly reach `max` when a simple swap of `A` can be done after pushing both values.

### (Option C) Greedy

1. For each `value` in `B`, compute:
	- Necessary rotations to bring `value` on top of `B`
	- Necessary rotations to bring correct position to `A`
	- Mutualisation possibilites (`rr`, `rrr`)
	- **Total estimated cost**
2. Execute the **minimal cost** action
