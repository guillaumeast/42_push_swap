```bash
# Choose generated numbers range with --input-range=
# Choose generated numbers count with -n
# Replace `\n` by ' ' with tr command
shuf --input-range=0-10000 -n 10 | tr '\n' ' '
```

Works fine:	`300 5060 4669 6629 5381 3045 8870 9529 8388 7265`
Broken:		`2039 1984 4953 2537 5618 4152 4225 4380 9386 3485`
