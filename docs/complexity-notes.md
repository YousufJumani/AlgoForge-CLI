# Complexity Notes

## Algorithms
- `sort`: O(n log n)
- `stable_sort`: O(n log n)
- `prefix_sum`: O(n)

## Why This Matters
Comparing runtime with identical seeds helps isolate algorithmic behavior from random data variance.

## Profiling Guidance
- Test multiple sizes: 1k, 10k, 100k, 1M
- Repeat each run 3 times and average results
- Keep machine conditions similar when benchmarking
