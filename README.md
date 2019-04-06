# Sort (Quick Sort)

Implement of qsort, is much faster than stdlib.

## Test
```
  c++ test_sort.cc -O3 -I.
  ./a.out
```

## Benchmark 
### speed of qsort_recursive(or qsort_iterative) is about 1.76 times of stdlib's qsort. 
```
  qsort_recursive 100000 elements, average speed is 9.8297 ms
  qsort_iterative 100000 elements, average speed is 9.9478 ms
  qsort_stdlib    100000 elements, average speed is 15.9294 ms
```
(test on MacBook Pro 2.3GHZ I5).


## License

It is released under the MIT license.
