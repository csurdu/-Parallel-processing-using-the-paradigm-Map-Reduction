# Map-Reduce with Pthreads: Identifying Perfect Powers

## Description
This project implements a parallel program using Pthreads to identify numbers greater than 0 that are perfect powers from a set of files. The program uses the **Map-Reduce** model to parallelize the processing of input files and count the unique values for each exponent.

## Requirements
The program processes a set of files, identifies numbers that are perfect powers, and organizes them by exponents. Each exponent will have an output file containing the count of unique values identified.

### Map-Reduce Paradigm
1. **Mapper**: Identifies perfect powers from input files and creates partial lists for each exponent.
2. **Reducer**: Combines the partial lists and counts unique values for each exponent, writing the results to an output file.

## Input and Output File Structure

### Input File
The main input file contains the list of files to be processed:
```
<number_of_files>
<file1>
<file2>
...
<fileN>
```

Each file in the list contains numerical values:
```
<number_of_values>
<value1>
<value2>
...
<valueN>
```

### Output Files
For each exponent `E`, an output file named `outE.txt` is created, containing a single value:
```
<number_of_unique_values>
```

## Execution Instructions
The program can be compiled and executed as follows:

1. **Compilation:**
   ```bash
   gcc -pthread -o tema1 tema1.c
   ```

2. **Execution:**
   ```bash
   ./tema1 <number_of_mappers> <number_of_reducers> <input_file>
   ```

   - `<number_of_mappers>`: The number of Mapper threads.
   - `<number_of_reducers>`: The number of Reducer threads.
   - `<input_file>`: The file containing the list of files to be processed.

### Example Execution

Input file:
```
4
in1.txt
in2.txt
in3.txt
in4.txt
```

Files to be processed:
- `in1.txt`:
  ```
  6
  243
  9
  27
  243
  81
  243
  ```
- `in2.txt`:
  ```
  6
  81
  9
  27
  243
  27
  27
  ```
- `in3.txt`:
  ```
  6
  9
  27
  9
  81
  9
  53
  ```
- `in4.txt`:
  ```
  5
  243
  243
  243
  1
  0
  ```

Command:
```bash
./tema1 3 5 test.txt
```

Generated output files:
- `out2.txt` (perfect squares): `3`
- `out3.txt` (perfect cubes): `2`
- `out4.txt`: `2`
- `out5.txt`: `2`
- `out6.txt`: `1`

## Technical Details

1. **Map Operations:**
   - Mapper threads process dynamically assigned files.
   - For each value in a file:
     - Check if it is a perfect power for an exponent (from 2 up to `<number_of_reducers>`).
     - Values are saved into partial lists for each exponent.

2. **Reduce Operations:**
   - Each Reducer combines the partial lists for its assigned exponent into a single aggregated list.
   - Counts the unique values in the aggregated list.
   - Writes the result to an output file.

## Important Notes
- **Synchronization:** Reducers begin execution only after all Mappers complete their tasks.
- **Dynamic Allocation:** Mappers receive files dynamically to balance the workload.
- **Input Validation:** The program only processes valid positive integers.

## Limitations
- The program assumes that all input files contain valid data.
- Only numbers greater than 0 are considered for identifying perfect powers.

## Authors
This project was created as part of the **Parallel and Distributed Algorithms** course.





![image](https://user-images.githubusercontent.com/73692534/220130863-08e4dd70-2aee-4657-9d4d-1ea5f15dcde3.png)
