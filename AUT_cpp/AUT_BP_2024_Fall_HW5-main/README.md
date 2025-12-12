<h1 align="center">
<strong>AUT_BP_2024_Fall Homework 5</strong>
</h1>

<p align="center">
<strong> Deadline: 16th of Azar - Friday - 23:59 o'clock</strong>
</p>

---

## **Question 1: Implementing Newton-Raphson Method for Root Finding**

### **Objective**

In this question, you will implement the Newton-Raphson method for finding the root of a function. The function should accept a pointer to the function whose root is to be found, along with the initial guess. The algorithm must continue iterating until the difference between two consecutive iterations is less than `1e-6`.

### **Explanation of Newton-Raphson Method**

The Newton-Raphson method is an iterative technique used to find the root of a real-valued function. The algorithm begins with an initial guess `initial`, and then iteratively refines this guess to get closer to the actual root.

The formula used in each iteration is:

<p align="center">
<img src="https://latex.codecogs.com/svg.latex?x_{n+1}=x_n-\frac{f(x_n)}{f'(x_n)}" alt="Newton-Raphson formula" style="width: 250px;">
</p>

In this implementation, the algorithm will continue iterating until the absolute difference between two consecutive approximations is smaller than a tolerance of \( 1e-6 \), indicating that the solution has converged.

**For simplicity, You may assume that the function passed to `newtonRaphson` has exactly one real root.**

### **Function Prototype**

```c
double newtonRaphson(double (*func)(double), double initial);

double derivative(double (*func)(double), double x);
```

### **Detailed Description**

1. **`newtonRaphson`**: This function takes a function pointer `func` (to the function whose root we are trying to find) and an initial guess `initial`. It applies the Newton-Raphson method iteratively until the difference between two consecutive approximations is less than \( 1e-6 \). The function will return the estimated root.

2. **`derivative`**: This function computes the derivative of the given function `func` at a point `x`. The derivative is approximated using the difference quotient:

<p align="center">
<img src="https://latex.codecogs.com/svg.latex?f'(x)%20%5Capprox%20%5Cfrac%7Bf(x+h)%20-%20f(x)%7D%7Bh%7D" alt="Derivative approximation formula" style="width: 250px">
</p>

Where \( h \) is a small value (e.g., \( h = 0.0001 \)).

The Newton-Raphson method is stopped when the difference between two consecutive approximations is smaller than \( 1e-6 \), which ensures that the algorithm has converged to a solution.

<p align="center">
  <img src="./resource/NewtonIteration_Ani.gif" alt="Newton Raphson Animation" style="width: 80%;">
</p>

### **Example**

#### **Input**

```c
double func(double x) {
    return x*x - 4;  // Example function f(x) = x^2 - 4
}
```

#### **Function Call**

```c
double root = newtonRaphson(func, -1.0);
```

#### **Expected Output**

For the example function \( f(x) = x^2 - 4 \), the root should be approximately \( 2.0 \), since the exact root is \( x = 2 \). The function `newtonRaphson` should return a value close to \( 2.0 \) after running the algorithm.

### **Notes**

-   The `newtonRaphson` function should stop when the absolute difference between two consecutive guesses is less than \( 1e-6 \).
-   You may assume that the function passed to `newtonRaphson` has exactly one real root.

---

## **Question 2: Implementing Map and Filter Functions Using Pointer to Function**

### **Objective**

In this question, you will implement two functions, `map` and `filter`, which operate on an array and a function provided as a pointer. Both functions should accept the array size and a pointer to the function to be applied to each element of the array. The `map` function modifies the array in place, while the `filter` function creates a new array containing only the elements that pass a certain condition.

### **Function Prototypes**

```c
void map(double *arr, int size, double (*func)(double));

double* filter(const double *arr, int size, bool (*func)(double));
```

### **Detailed Description**

1. **`map`**:
   - The `map` function takes an array of integers `arr`, the size of the array `size`, and a pointer to a function `func` that outputs a number on each element of the array.
   - The `map` function should apply the function `func` to each element of the array and modify the array in place. The map function should not return anything.

   **Example Usage**:

   ```c
   double square(double x) {
       return x*x;  // Example function to square the number
   }

   double arr[] = {1, 2, 3, 4};
   int size = sizeof(arr) / sizeof(arr[0]);

   map(arr, size, square);
   ```

   After running the `map` function, the array `arr` should be modified to `{1.0, 4.0, 9.0, 16.0}`.

2. **`filter`**:
   - The `filter` function takes an array of integers `arr`, the size of the array `size`, and a pointer to a function `func` that returns a boolean indicating whether an element should be included in the resulting array.
   - The `filter` function should create a new array that contains only the elements for which `func` returns `true`. You should dynamically allocate memory for the result array as you identify elements that pass the test.

   **Example Usage**:

   ```c
   bool isEven(double x) {
       return ((int)x % 2 == 0);  // Example function to check if the number is even
   }

   int arr[] = {1, 2, 3, 4, 5, 6};
   int size = sizeof(arr) / sizeof(arr[0]);

   int *result = filter(arr, size, isEven);
   ```

   After running the `filter` function, the new array `result` should contain `{2, 4, 6}`.

### **Notes**

- The `map` function will modify the original array directly and does not return anything.
- The `filter` function will dynamically allocate memory for a new array. Make sure to reallocate memory each time a new element passes the filter, and ensure you return the new array.

---

## **Question 3: Creating an HTML Tag Generator Using Variable Length Arguments**

### **Objective**

In this question, you will implement a function that dynamically generates an HTML tag with attributes using variable-length arguments in C. This exercise will help you understand how to work with variable-length arguments and how to build dynamic strings based on input.

### **Explanation**

The function will take a tag name as a string, followed by a series of attribute-value pairs. It will generate a string representing an HTML tag with the given attributes.

The concept of variable-length arguments (`...`) in C allows you to pass a variable number of arguments to a function. You will use the `stdarg.h` library to handle these arguments.

### **Function Prototype**

```c
#include <stdarg.h>

char* createHTMLTag(const char* tag, int count, ...);
```

### **Detailed Description**

1. **`createHTMLTag`**: This function generates an HTML tag as a string.
   - It takes the tag name as a string (e.g., `"a"`, `"div"`) and an integer `count`, which indicates how many attribute-value pairs will follow.
   - The function uses variable-length arguments to accept pairs of attribute names and their corresponding values. The attributes are provided as `const char*` pairs.
   - The function constructs the HTML tag string by appending each attribute to the tag in the form of `attribute="value"`.
   - The function must return a dynamically allocated string that represents the complete HTML tag.

   **Key Concepts**:
   - Use `va_list`, `va_start()`, and `va_arg()` to handle variable-length arguments.
   - Dynamically allocate memory for the resulting string since the size of the tag depends on the number of attributes.
   - Ensure proper memory management by allocating enough space and returning the string.

### **Example Usage**

```c
int main() {

    char* html = createHTMLTag("a", 2, "href", "https://example.com", "target", "_blank");
    printf("%s\n", html);  // Output: <a href="https://example.com" target="_blank"></a>
    
    free(html);
    return 0;

}
```

### **Expected Output**

For the example call:

```c
char* html = createHTMLTag("a", 2, "href", "https://example.com", "target", "_blank");
```

The output will be:

```html
<a href="https://example.com" target="_blank"></a>
```

### **Notes**

- The function uses variable-length arguments to handle a flexible number of attribute-value pairs.
- You must ensure the memory allocated is sufficient to hold the resulting string. The string will contain the tag name, the attributes, and the closing tag.
- After building the string, ensure that it is null-terminated and properly formatted.

---

If you have any questions regarding the homework, feel free to reach out:

-   **Teaching Assistant**: Seyyed Mohammad Hamidi
-   **Telegram Group**: [t.me/AUT_BP_Fall_2024](https://t.me/AUT_BP_Fall_2024)
-   **Github**: [github.com/smhamidi](https://github.com/smhamidi)

---

<p align="center">
  <img src="./resource/NoWarInBaSingSe.webp" alt="No War in ba sing se" style="width: 40%;">
</p>

**Best Regards, [Hamidi](https://github.com/smhamidi)**
