.data  # store string in data segment
    
    inp1: .asciiz "Please input a char: "
    inp2: .asciiz "\nPlease enter the number of move:"
    str:    .asciiz "\nThe result is "
    space:  .asciiz " "
    
.text
.globl main     
    
main:  
    
    li   $v0, 4 		# system call to print_inp1
    la   $a0, inp1
    syscall
    
    li   $v0,12              	# system call code for read_char
    syscall                	# read a char from the console
    move $a2, $v0    		# save character to $a2

    li   $v0, 4	             	# system call to print_inp2
    la   $a0, inp2
    syscall
    
    li   $v0, 5	            	# system call code for read_int
    syscall                	# read a integer from the console
    move $a1, $v0         	# save moves to $a1

    li   $v0, 4	          	# print "the result is"
    la   $a0, str
    syscall

    add  $a0, $a1, $a2		# move char with the move
    li   $v0, 11		# print char $a0 holds the target
    syscall


 

exit: 
    li $v0, 10
    syscall
