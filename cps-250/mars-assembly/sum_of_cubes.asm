.data
	inputstr: .asciiz "Please input the integer: "
	errorstr: .asciiz "Invalid!!! Try again.\n"
	resultstr: .asciiz "The result is: "
.text
main:
	whileLoop:
	jal get_num
	move $t0, $v0
	
	sle $t1, $t0, 5
	sge $t2, $t0, 0
	add $t1, $t1, $t2
	beq $t1, 2, cont
	li $v0, 4
	la $a0, errorstr
	syscall
	li $v0, 0
	j whileLoop
	cont:
	
	move $a0, $t0
	jal calc_result
	move $t0, $v0
	
	li $v0, 4
	la $a0, resultstr
	syscall
	
	li $v0, 1
	move $a0, $t0
	syscall
	
	li $v0, 10
	syscall
	
.text
get_num:
	addi $sp, $sp, -4
	sw $ra, 0($sp)

	li $v0, 4
	la $a0, inputstr
	syscall
	
	li $v0, 5
	syscall
	
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	jr $ra
	
.text
calc_result:
	addi $sp, $sp, -8
	sw $a0, 4($sp)
	sw $ra, 0($sp)
	
	beq $a0, 0, basecase
	addi $a0, $a0, -1
	jal calc_result
	lw $a0, 4($sp)
	
	mul $t0, $a0, $a0
	mul $t0, $t0, $a0
	
	add $v0, $v0, $t0
	j reg_return
	basecase:
	li $v0, 0
	reg_return:
	lw $ra, 0($sp)
	lw $a0, 4($sp)
	addi $sp, $sp, 8
	jr $ra
	