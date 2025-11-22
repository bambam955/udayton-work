# CPS 444, Homework 6

## Question 1

The program will print:

```
8 8
4 4
0 0
2 2
```

## Question 7

The program will print:

```
See you at the snack bar.
ee you at the snack bar.
See you
e you
```

## Question 8

The program will print:

```
y
my
mmy
ummy
Yummy
```

## Question 9

The program will print:

```
I read part of it all the way through.
```

## Question 10

a. `Ho Ho Ho!!oH oH oH`
b. `const char*`
c. `Ho Ho Ho!`
d. The expression `*--pc` means decrement the pointer and then dereference it. In the `pr` function, it gives you the value of the previous character. This is different from `--*pc` because the pointer is dereferenced first and _then_ the value is decremented. The pointer's value will not change, but the result of the expression will be the character one below the actual character. If `*pc` is `b`, then `--*pc` will be `a`.
e. In that case the character will be printed _before_ the pointer is decremented. This won't matter until the end, when the pointer decrements before printing the last character. The output will be `Ho Ho Ho!!oH oH o`.
f. THe first expression ensures the next character to be printed is not `\0`. The second expression compares the memory addresses of `pc` and `str`. If they are equal, then `pc` is back to the beginning of the string again, and we can stop. This works because `0 == false`.
g. The first `while` condition causes a seg-fault because `*pc` tries to dereference a `NULL` pointer and that is not allowed.
h. You just have to add the type for `x`...so you get `const char *x = pr("Ho Ho Ho!");`.

## Question 11

The program will print:

```
How are ya, sweetie? How are ya, sweetie?
Beat the clock.
eat the clock.
Beat the clock. Win a toy.
Beat
chat
hat
at
t
t
at
How are ya, sweetie?
```

## Question 12

The program will print:

```
faavrhee
*le*on*sm
```

## Question 19

The `structure` keyword does not exist in C. Use the `struct` keyword instead.

## Question 23

a. Combined, the 3 statements will print:

```
6
Arcturan
cturan
```

b. You could do `deb.title.first` or `pb->title.first`.
c.
