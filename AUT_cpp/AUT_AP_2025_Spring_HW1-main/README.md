<h1 align="center">
<strong>AUT_AP_2025_Spring Homework 1</strong>
</h1>

<p align="center">
<strong> Deadline: 27th of Bahman - 23:59 o'clock</strong>
</p>

---

# **1st Question: File Organizer Script**

## **Objective**

Develop a bash script that automatically organizes files in a specified directory by sorting them into subdirectories based on their file extensions. This exercise will strengthen your understanding of file system manipulation, loops, conditional logic, and logging within bash scripts.

## **Script Requirements**

-   **Shebang Line:** Start your script with `#!/bin/bash`.
-   **Input Validation:**

    -   **Required Parameter:** The path to the target directory.
    -   Display an error message and exit if the directory does not exist or if the parameter is missing.

-   **File Organization Process:**

    -   **Iteration:** Traverse all directories and subdirectories in the provided directory.
    -   **Extension-Based Sorting:**
        -   For each file, determine its extension (e.g., `.txt`, `.jpg`).
        -   Create a subdirectory for that extension if it doesn’t already exist.
        -   Move the file into the corresponding subdirectory.
    -   **Optional Flags:**
        -   Include a `--dry-run` option that simulates the organization process without moving any files. This allows users to preview actions before applying changes. (This option is optional for the script but mandatory to implemented.)
        -   For each file processed, the script should print a message detailing the action it would take. For example:
        ```plaintext
        [DRY-RUN] Would move 'example.txt' to '<TARGET_DIR>/txt/example.txt'
        ```

-   **Logging:**
    -   Generate a log file (e.g., `organizer_log.txt`) in the target directory.
    -   Log key details for each file moved: original location, destination subdirectory, file name, and timestamp.
    -   Ensure the log format is clear and structured.
    -   **Format of the log file is up to you, (Surprise Me 😎)**

## **Example Usage**

```bash
./organize_files.sh <TARGET_DIR>
```

_With dry-run mode:_

```bash
./organize_files.sh <TARGET_DIR> --dry-run
```

---

# **2nd Question: Sorting Points by Euclidean Distance**

## **Objective:**

Implement a function that takes a vector of 3D points (each represented as a `std::array<double, 3>`) and sorts the vector **in-place** based on the Euclidean distance of each point from the origin (0, 0, 0).

### **Function Prototype:**

```cpp
void sort_points_by_distance(std::vector<std::array<double, 3>>& points);
```

## **Task Details:**

-   **Euclidean Distance Calculation:**  
    For each point `(x, y, z)`, the Euclidean distance from the origin is given by:
    \[
    \text{distance} = \sqrt{x^2 + y^2 + z^2}
    \]
    _Note:_ Since you are only comparing distances, you can compare the squared values (`x*x + y*y + z*z`) to avoid computing the square root.

-   **In-Place Sorting:**  
    The function must sort the input vector directly without using additional containers to store a copy of the data.

-   **Error Handling:**  
    Assume the input vector is valid. If it is empty, the function should simply return without performing any operations.

-   **Example:**  
    Given the input:
    ```cpp
    std::vector<std::array<double, 3>> points = { { {3, 4, 0} }, { {1, 1, 1} }, { {0, 0, 5} } };
    ```
    After sorting, the vector should have points ordered from the closest to the farthest from the origin.

---

# **3rd Question: Counting Islands in a 2D Grid**

## **Objective:**

Implement a function that takes a 2D grid (a `std::vector<std::vector<int>>`) where `1` represents land and `0` represents water, and returns the number of distinct "islands" in the grid. An island is defined as a group of horizontally or vertically adjacent `1`s surrounded by `0`s.

### **Function Prototype:**

```cpp
int count_islands(const std::vector<std::vector<int>>& grid);
```

## **Task Details:**

-   **Island Definition:**  
    An island is a collection of one or more adjacent `1`s. Cells are considered adjacent if they are horizontally or vertically next to each other. Diagonal connections should **not** be counted.

-   **Algorithm Hint:**  
    You can use either Depth-First Search (DFS) or Breadth-First Search (BFS) to traverse the grid and mark cells that belong to the same island.

-   **Edge Cases:**

    -   If the grid is empty, the function should return `0`.
    -   If there are no `1`s in the grid, the function should return `0`.

-   **Example:**  
    For the grid:
    ```cpp
    std::vector<std::vector<int>> grid = {
        {1, 1, 0, 0, 0},
        {1, 1, 0, 0, 1},
        {0, 0, 1, 0, 1},
        {0, 0, 0, 1, 1}
    };
    ```
    The function should return `3` because there are three separate islands in the grid.

---

# **Final Step: How To Test Your Program**

If you want to debug your code, set the `if` statement to `true`. This will allow you to place your debugging code in the designated section. Once you're done with the debugging process, remember to set the `if` statement back to `false` to test your program using the provided `unit-test.cpp`.

```cpp
#include <iostream>
#include <gtest/gtest.h>

#include "Q2_Sort_By_Distance.h"
#include "Q3_Count_Islands.h"


int main(int argc, char **argv)
{
    if (true) // Set to false to run unit-tests
    {
        // Debug section: Place your debugging code here
    }
    else
    {
        ::testing::InitGoogleTest(&argc, argv);
        std::cout << "RUNNING TESTS ..." << std::endl;
        int ret{RUN_ALL_TESTS()};
        if (!ret)
            std::cout << "<<<SUCCESS>>>" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    return 0;
}
```

<p align="center">
  <img src="./resource/Isnt_CPP_Fun.jpeg" alt="Cpp is Hard but worth it." style="width: 50%;">
</p>

**Best Regards, [Hamidi](https://github.com/smhamidi)**
