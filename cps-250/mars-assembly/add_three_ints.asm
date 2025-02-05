	.data   # store string in data segment
inp:	.asciiz "Please input the integer: "
str:	.asciiz "The result is "
.text
	.globl main     
main:         
	li   $v0,4        # system call to print_string
	la   $a0,inp
	syscall
	li   $v0,5        # system call code for read_int
	syscall           # read a integer from the console
	move $a1,$v0      # save n1 into $a1

	li   $v0,4        # system call to print_string
	la   $a0,inp
	syscall
	li   $v0,5        # system call code for read_int
	syscall           # read a integer from the console
	move $a2,$v0      # save n2 into $a2
	
	li   $v0, 4       # system call code for print_string
	la   $a0, inp     # load the string to print
	syscall
	li   $v0, 5       # system call code for read_int
	syscall           
	move $a3,$v0      # save n1 into $a3

	add  $a1, $a2, $a1 # add 2 integers
	add  $a1, $a3, $a1 # add 3 integers

	li   $v0,4        # system call to print_string
	la   $a0,str
	syscall
	li   $v0,1        # system call to print_int
	move $a0,$a1
	syscall
	li $v0, 10		# system call code for exit = 10
	syscall			# call operating sys
          
