# CPS 444, Homework 7

## Question 1

```
one
two
three
four
```

## Question 2

`date\@` says `date@: not found` because the `lnext` command makes the character an escape character that just replaces `\` with whatever character is typed next.

`date` just works as the normal command and prints the current date.

`#date` also works as the normal command because all `#` characters are ignored/erased.

`\#date` prints nothing. `\#` results in a `#` actually being printed, and since `#` comments out the line, running `#date` is effectively running nothing at all.

## Question 3

`ls` is normally used to show directory contents. When you run `ls` on a file, which is what `ls junk` does, it just shows the file output.

`echo` prints its arguments to stdout. So, `echo junk` just prints `junk` to the terminal.

`ls /` shows the contents of the root directory. So, a list of all the files/directories contained in your rootfs will be printed out.

`echo /` just prints `/` to stdout.

`ls` with no arguments shows the contents of the current directory.

`echo` with no arguments just prints a blank line. This is because `echo` automatically appends a newline character to its output unless `-n` is specified.

`ls *` prints the contents of each file/directory contained in your current directory. Files are printed as if you ran `ls <file>`, while directory contents are printed as `ls <dir>`. This is because BASH expands the `*` to all files in the current directory.

`echo *` prints the names of all files in the current directory. Again, the `*` expands (before `echo` is even run) to a list of all files. So, the effective command is `echo <file1> <file2> ...`.

`ls ' * '` gives an error. BASH handles single-quoted strings a bit different than double-quoted strings. With double-quotes it expands any variables inside the string, but with single-quotes it just treats everything inside as literal text with no extra parsing. Since there is (probably) no directory named `' * '`, it results in an error.

`echo ' * '` just prints `*` to stdout. Again, the single-quoted string is treated as literal text with no extra parsing.

## Question 4

`echo 'Go $HOME'` will just print `Go $HOME` to stdout. If it was double quotes then BASH would expand `$HOME` to be the absolute path of the current user's home directory, and that would be printed. But single-quotes eliminates BASH variable parsing.

`echo "$5.00 is too much!"` will print `.00 is too much!`. Since the string is double-quoted, `$5` will be expanded to the value of the sixth argument (zero-indexed). However, only two arguments (including the name of the command itself) were passed, which means `$5` is nothing. Everything else is printed normally.

`echo $(who | wc -l) users is not very many` will print the number of users in the system. The `who` command prints a list of all registered users in the system, one per line. Then, `wc -l` counts the number of lines in the output that was piped to it, which results in a simple count of users.

## Question 5

a. `Send output of "command" to file descriptor 2`
b. `Well, isn’t that "special"?`
c. `You have 9 files in /home/linda`
d. `You have $(ls | wc -l) files in $(pwd)`
e. `You have $(ls | wc -l) files in $(pwd)`
f. `The value of $x is 10`
g. `The value of 10 is $x`
h. `Go $HOME`
i. `.00 is too much!`
j. `1 users is not very many`

## Question 6

`mystery 2>&1 | wc -l`

## Question 7

There is no real difference among the three commands. `pr` with no arguments just reads from stdin, which works with the pipe from `cat`. `pr <file` and `pr file` do the same thing; `pr <file` uses BASH's input redirection syntax, which just feeds the contents of `file` into stdin for `pr` to use.

## Question 8

`ls .*` prints the contents of all hidden directories. BASH doesn't expand regexes, so the `.` is treated as a regular character (the start of dot-dirs) and `*` is the wildcard that expands to all dot-dirs.

## Question 9

No, it does not produce all names in all directories. It prints all files inside the directories contained in the current directory. The first `*` matches all directories in the current directory, the `/` descends into each one, and the second `*` matches all files in each of those directories.

The names appear in alphabetical order because that is the order of ASCII.

## Question 10

```bash
# older f:
# list files older than f
ls -1rt | sed '/^'$1'$/d'
```

```bash
# newer f:
# list files newer than f
ls -1t | sed '/^'$1'$/d'
```

## Question 11

```bash
awk '1' <file>
```
