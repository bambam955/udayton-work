# CPS 444, Homework 5

## Question 1: Identify/Correct Errors in Statements

a. The format string is missing a percent sign. Also, you must pass pointers to variables as the arguments following the format specifier. The correct code is `scanf("%d", &value);`.
b. The quotation mark precedes the `\n`, which is wrong. The newline character is part of the string. Also, no third argument is given for the third `%d`. The correct code is `printf( "The product of %d and %d is %d\n", x, y, x * y);`.
c. Assignments must always have the lvalue on the left-hand side of the assignment operator and the rvalue on the right-hand side. The correct code is `sumOfNumbers = firstNumber + secondNumber;`.
d. There are two issues. First, `==` is the equality operator, not the assignment operator. Second, `=>` is not an operator; it should be `>=`. The correct code is:

```c
if (number >= largest)
{
    largest = number;
}
```

e. The comment markers `/*` and `*/` are flipped. They should be in the order I just listed. The correct code is `/* Program to determine the largest of three integers */`.
f. Function calls are case-sensitive, and `scanf` is all lowercase. Also, you must pass pointers to variables as the arguments following the format specifier. The correct code is `scanf("%d", &anInteger);`.
g. There are three value arguments given but only two specifiers in the format string. There needs to be a third place for the third argument. The correct code is `printf("Remainder of %d divided by %d is %d\n", x, y, x % y );`.
h. This is the reverse of part d. The assignment operator is _not_ an equality operator. Also, you cannot put a semicolon at the end of the `if` condition because it's not an actual statement. The correct code is:

```c
if (x == y)
{
    printf("%d is equal to %d\n", x, y );
}
```

i. The comma is inside the format string. There needs to be a comma following the string to tell the compiler to look for the next argument. Also, you need `printf` not `print`. The correct code is `printf("The sum is %d\n", x + y);`.
j. Again, function calls are case-sensitive; we need `printf` instead of `Printf`. Also missing a quotation mark. Also can't pass a pointer when `printf` is expecting an integer value. The correct code is `printf( "The value you entered is: %d\n", value);`.
k. Can't put a semicolon at the end of the if-condition. Correct code:

```c
if( age>= 65)
{
    printf("Age is greater than or equal to 65");
}
else
{
    printf("Age is less than 65");
}
```

l. The `total` variable is not initialized. The correct code is:

```c
int x = 1, total = 0;
while (x <= 10)
{
    total += x;
    ++x;
}
```

m. `while` needs to be all lowercase. Also, braces are needed around the loop block to include both statements in the loop. The correct code is:

```c
while (x<=100)
{
    total += x;
    ++x;
}
```

n. The code is syntatically correct but will cause an infinite loop because `y > 0` will always be true. The correct code would be something like:

```c
while (y < 20)
{
    printf("%d\n", y);
    ++y;
}
```

o. There are a lot of issues here. `x` needs to be declared. The loop condition must use semicolons instead of commas. Finally, there is an infinite loop because `x` will always be greater than 1, so use `x--` instead. The corrected code is:

```c
for (int x = 100; x >= 1; --x)
{
    printf("%d\n", x);
}
```

p. The variable `x` needs declared as a `double`. The termination condition is false when the loop starts so the body will never execute. The correct code is:

```c
for (double x = .000001; x <= .0001; x += .000001)
{
    printf( "%.7f\n", x );
}
```

q. The variable `x` needs declared, and the increment expression should be decrementing not incrementing. The correct code is:

```c
for (int x = 999; x >= 1; x -= 2)
{
    printf("%d\n", x);
}
```

r. The variable `x` needs declared and there cannot be a semicolon at the end of the loop condition, same as if-conditions. The correct code is:

```c
for (int x = 100; x <= 150; ++x)
{
    total += x;
}
```

## Question 2: Write a Single Statement

a. `puts("Enter two numbers.");`
b. `a = b * c;`
c. `// This program performs a sample payroll calculation.`
d. `scanf("%d %d %d", &a, &b, &c);`

## Question 3: True/False

a. False. C operators are evaluated in order of precedence; operators of the same precedence are then evaluated left-to-right.
b. True
c. False. That will just print the text `a = 5;`. There is no assignment statement, just text to be printed.
d. False. Operators are still evaluated in order of precedence, and precedence follows PEMDAS.
e. False. `h22` is a valid variable name.

## Question 4: What Prints?

a. 2
b. 4
c. x=
d. x=2
e. 5=5
f. Nothing
g. Nothing
h. Nothing
i. blank line

## Question 5: Which Variables' Values are Replaced?

a. b, c, d, e, f
b. p
c. none
d. none

## Question 6: Valid Math Statements

a. correct
b. incorrect
c. incorrect
d. correct
e. correct
f. incorrect

## Question 7: Order of Evaluation of Operators

a. `*, /, +, -` is the order. `x` will equal `15`.
b. `%, *, /, +, -` is the order. `x` will equal `3`.
c. `(), *, /, (), +, *, *` is the order. `x` will equal `324`.

## Question 8: Program Output

It will print:

```
1
4
9
16
25
36
49
64
81
100
Total is 385
```

## Question 9: Values of Control Variables

a. `2,4,6,8,10,12`
b. `5,12,19`
c. `3,6,9,12,15`
d. `1`
e. `12,9,6,3`

## Question 10: Writing `for` Loops

a. `for (int i = 1; i <= 7; ++i) printf("%d\n", i);`
b. `for (int i = 3; i <= 23; i += 5) printf("%d\n", i);`
c. `for (int i = 20; i >= -10; i -= 6) printf("%d\n", i);`
d. `for (int i = 19; i <= 51; i += 8) printf("%d\n", i);`

## Question 11: Truth Tables

| Condition 1 | Condition 2 | Condition 1 && Condition 2 |
| ----------- | ----------- | -------------------------- |
| 0           | 0           | 0                          |
| 0           | nonzero     | 0                          |
| nonzero     | 0           | 0                          |
| nonzero     | nonzero     | 1                          |

| Condition 1 | Condition 2 | Condition 1 OR Condition 2 |
| ----------- | ----------- | -------------------------- |
| 0           | 0           | 0                          |
| 0           | nonzero     | 1                          |
| nonzero     | 0           | 1                          |
| nonzero     | nonzero     | 1                          |

| Condition 1 | !Condition 1 |
| ----------- | ------------ |
| 0           | 1            |
| nonzero     | 0            |
