.data
	inputstr: .asciiz "Input an index of the Fibonacci sequence: "
	resultstr: .asciiz "The value is: "
.text
main:
	li $v0, 4
	la $a0, inputstr
	syscall
	
	li $v0, 5
	syscall

	move $a0, $v0
	jal fib
	move $t0, $v0
		
	li $v0, 4
	la $a0, resultstr
	syscall
	
	li $v0, 1
	move $a0, $t0
	syscall

	li $v0, 10
	syscall
	
fib:
	addi $sp, $sp, -12
	sw $a0, 4($sp)
	sw $ra, 0($sp)
	
	ble $a0, 1, basecase
	addi $a0, $a0, -1
	jal fib
	sw $v0 8($sp)
	lw $a0, 4($sp)
	addi $a0, $a0, -2
	jal fib
	lw $t0, 8($sp)
	add $v0, $v0, $t0
	j return
	
	basecase:
	move $v0, $a0
	
	return:
	lw $ra, 0($sp)
	lw $a0, 4($sp)
	addi $sp, $sp, 12
	jr $ra