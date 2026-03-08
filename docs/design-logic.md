# Design Logic

## Core Mental Model
AlgoForge is a command runner with pluggable algorithms and deterministic data generation.

## Reproducible Benchmarking
A fixed random seed makes input generation repeatable. This allows fair algorithm comparisons.

## Plugin Architecture
`unordered_map<string, function>` acts as a registry. Adding an algorithm requires only implementing a function and registering it.

## Profiling and Memory Estimate
Runtime is measured with high-resolution clock; memory estimate uses vector capacity * element size. This is a practical approximation for learning.

## Why This Matters
The project teaches not only algorithm coding, but also benchmark discipline, extensibility, and evidence-based performance reasoning.
