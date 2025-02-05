.data  # store string in data segment
    
    inp: .asciiz "Please input integer: "
    str:    .asciiz "The result is "
    array1: .word 0 0 0 0 0   #declare storage to hold array of integers
    space:  .asciiz " "
    
.text
.globl main     
    
main:
    la   $t0, array1   # load address of array into register $t0
    move $t3, $t0     	# copy address of the array
    
    li   $t1, 5
    li   $t2, 0
    
loop_input:
    
    beq $t2, $t1, out_put 
    
    li   $v0, 4             # system call to print_string
    la   $a0,inp
    syscall
    
    li   $v0,5             # system call code for read_int
    syscall                # read a integer from the console
    
    sw   $v0, 0($t3)		    # save number into current array slot
    
    addi $t3, $t3, 4
    addi $t2, $t2, 1
    
    j loop_input              
    
out_put:
    li   $v0,4             # system call to print_string
    la   $a0,str
    syscall
    
    li   $t1, 5
    li   $t2, 0
    
loop_output:   
    
    beq $t2, $t1, exit 
    
    lw   $t4,0($t0)
    
    li   $v0,1             # system call to print_int
    move $a0,$t4
    syscall
    
    li   $v0,4             # system call to print_space
    la   $a0,space
    syscall
    
    addi $t0, $t0, 4
    addi $t2, $t2, 1
    
    j loop_output
    
exit: 
    li $v0, 10
    syscall
