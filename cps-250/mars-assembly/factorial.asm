.data
    str: .asciiz "Please input an integer n: "
    result: .asciiz "The result is Fact(n) = "
.text
main:

    	li	$v0, 4		# system call to print_string 
    	la	$a0, str
    	syscall
    
    	# read input integer
    	li	$v0, 5		    			# system call code for read_int
    	syscall	           		# read a integer from the console

    	# function call
    	move    $a0, $v0  
    	jal   	fact        		# call factorial function
    	move    $t0, $v0        		# $t0 = $v0
    
    	# print result
	li 	$v0, 4
	la 	$a0, result
	syscall
	li	$v0, 1
	move	$a0, $t0
	syscall
                   	
    	# exit program
    	li        $v0, 10        	# $v0 = 10
    	syscall


.text
fact:
    	addi    $sp, $sp, -8 	 # save $s0 and $ra
    	sw      $a0, 4($sp)
    	sw      $ra, 0($sp)
       	bne	$a0, 0, gen 			# gen?
   	li	$v0, 1    		# base case, return 1
    	j	reg_return      			# retrieve adddress and argument saved on stack

gen:
    	addi    $a0, $a0, -1			# n = n - 1
      	jal fact		# recursively call fact with n - 1
    	addi	$a0, $a0, 1         		# get n
    	mul  	$v0, $a0, $v0    			# n * fact(n - 1)

reg_return:
    	lw     	$ra, 0($sp)
    	lw     	$a0, 4($sp)
    	addi	$sp, $sp, 8
    	jr     	$ra
