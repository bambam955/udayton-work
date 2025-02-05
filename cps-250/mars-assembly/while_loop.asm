.data  # store string in data segment
    
    str: .asciiz "while loop is done."
    space: .asciiz ", "
    inp: .asciiz "Please input the integer: "
    
.text
.globl main     
    
	main:  
		# ask a user to input a number
		li $v0, 4
		la $a0, inp
		syscall
		
		li $v0, 5
		syscall
		move $t1, $v0
		
		# while loop begins
		move $t2, $0				# i = 0
		whileLoop:
		beq $t2, $t1, exit
		addi $t2, $t2, 1
		move $a0, $t2
		li $v0, 1
		syscall
		li $v0, 4
		la $a0, space
		syscall
		j whileLoop
		
		exit:
		li $v0, 4
		la $a0, str
		syscall

		# end of program
		li $v0, 10
		syscall
	
	# print out a number if the whileloop continues
	printNumber:
	addi $t2, $t2, 1
	move $a0, $t2
	li $v0, 11
	syscall
	li $v0, 4
	la $a0, space
	syscall
	j whileLoop
	
