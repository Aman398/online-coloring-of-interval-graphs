# KT Algorithm Project

This project implements three versions of the KT (Kuhn-Tucker) algorithm to assign levels to intervals based on their relationships. Each version improves upon the previous one, with optimizations and flexibility in input handling. The project is organized into three algorithm versions, each in its own file, along with test cases for validation.

## Folder Structure

- **KT_v1.cpp:** First implementation using linear search   
- **KT_v2.cpp:** Second implementation using binary search   
- **KT_v3.cpp:** Third implementation without assuming known chromatic number   
- **testCases.txt:** Input file for KT_v1 and KT_v2   
- **testCases2.txt:** Input file for KT_v3


## Algorithm Versions

### 1. KT_v1 (Linear Search)

- **Description**: This initial implementation of the KT algorithm uses a linear search to assign levels to each interval.
- **Assumption**: Assumes that the chromatic number `k` (number of colors or levels) is known beforehand.
- **Performance**: May be slower for larger datasets due to the linear search approach.
- **Input**: Uses `testCases.txt` for input.

### 2. KT_v2 (Binary Search)

- **Description**: This version improves upon `KT_v1` by using binary search for more efficient level assignment.
- **Assumption**: Similar to `KT_v1`, it assumes the chromatic number `k` is known in advance.
- **Performance**: Faster than `KT_v1` due to binary search, improving efficiency on larger datasets.
- **Input**: Also uses `testCases.txt` for input.

### 3. KT_v3 (No Prior Assumption of `k`)

- **Description**: This version further enhances flexibility by eliminating the need for a known chromatic number `k`. It dynamically calculates `k` during the algorithm.
- **Assumption**: No assumption of the chromatic number `k` as a priori; `k` is calculated based on the input data.
- **Performance**: Slightly more complex but more adaptable, suitable for varied input without prior knowledge of `k`.
- **Input**: Uses `testCases2.txt` for input.

## Test Cases

- **testCases.txt**: Contains test inputs for `KT_v1` and `KT_v2`, where the chromatic number `k` is assumed to be known.
- **testCases2.txt**: Contains test inputs for `KT_v3`, where `k` is not provided beforehand and must be computed by the algorithm.

## Usage

1. **Compile** any of the versions, e.g., for `KT_v1`:
   ```bash
   g++ KT_v1.cpp -o KT_v1
