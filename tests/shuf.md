```bash
for i in {1..10}; do shuf --input-range=0-2147483647 -n 100 | tr '\n' ' '; echo; done > tests/inputs_100.txt
```
