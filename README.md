# AlgoForge CLI

## Problem It Solves
Practice and benchmark algorithmic strategies using reproducible datasets.

## Tech
- C++17
- STL algorithms and containers
- Command-driven CLI patterns

## MVP Features
- Command-based runner (`sort`, `stable_sort`, `prefix_sum`)
- Deterministic input generator with seed
- Complexity report output
- Basic test checks

## Advanced Features Included
- Profiling mode: `--profile`
- Memory estimate mode: `--memory`
- Plugin-style extension via algorithm registry

## Build and Run
```powershell
g++ -std=c++17 -O2 .\src\main.cpp -o algoforge.exe
.\algoforge.exe sort 10000 42 --profile --memory
```

## Notes
- Running without args now starts an interactive prompt mode (double-click friendly).
- Numeric input validation is included for `size` and optional `seed`.
- The app waits with `Press Enter to exit...` after interactive runs and on input errors.

## Suggested Commands
```powershell
.\algoforge.exe sort 200000 7 --profile
.\algoforge.exe stable_sort 200000 7 --profile
.\algoforge.exe prefix_sum 200000 7 --profile --memory
```

## Folder Explanation
- `src/`: CLI and algorithm registry
- `tests/`: quick correctness checks
- `docs/`: complexity and design notes
- `scripts/`: build/test helpers

## What It Proves
- You can compare algorithms with controlled inputs.
- You can reason about runtime and memory behavior.
- You can design a simple extensible architecture.
