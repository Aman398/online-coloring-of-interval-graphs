# Online Coloring of 2-Colorable Unit Interval Graphs

This project implements three algorithms for the online coloring of 2-colorable unit interval graphs. Each version improves upon the previous one, aiming to reduce time complexity and improve performance under different assumptions about the input order.

## Folder Structure

- **Algo_v1.cpp:** First approach with worst-case complexity of O(n^2)  
- **Algo_v2.cpp:** Optimized for sorted intervals, achieving O(n) complexity  
- **Algo_v3.cpp:** Further optimized Algo_v1 approach using a research-based algorithm  
- **testCases.txt:** Input file for Algo_v1   
- **testCases2.txt:** Input file for Algo_v2

## Algorithm Versions

### 1. Algo_v1 (Initial Approach)

- **Description**: This initial version attempts to color each interval optimally as it arrives.
- **Complexity**: In the worst case, the complexity is `O(n^2)` due to repeated checks across intervals.
- **Input File**: Uses `testCases.txt` for input.

### 2. Algo_v2 (Sorted Intervals, O(n) Complexity)

- **Description**: In this version, the algorithm assumes that the input intervals are provided in sorted order. This assumption allows the algorithm to achieve `O(n)` complexity by simplifying the coloring logic.
- **Complexity**: Achieves `O(n)` complexity with sorted input.
- **Input File**: Uses `testCases2.txt` for input.

### 3. Algo_v3 (Research-Based Optimization)

- **Description**: This version uses an optimized algorithm from a research paper to color intervals efficiently, achieving better performance in scenarios where intervals are not sorted or pre-ordered.
- **Complexity**: More efficient than `Algo_v1`, especially in cases with high input density, due to optimized logic.

## Test Cases

- **testCases.txt**: Contains test inputs for `Algo_v1`.
- **testCases2.txt**: Contains test inputs for `Algo_v2`, where intervals are assumed to be sorted.

## Usage

1. **Compile** any of the versions, e.g., for `Algo_v1`:
   ```bash
   g++ Algo_v1.cpp -o Algo_v1
