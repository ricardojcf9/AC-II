	.equ READ_CORE_TIMER,11
	.equ RESET_CORE_TIMER,12
	.equ PUT_CHAR,3
	.equ PRINT_INT,6
	.data
	.text
	.globl main
	
main: 	li	$t0,0 			# counter=0
while: 					# while (1) {
	li	$v0,RESET_CORE_TIMER 	#
	syscall
while2:
	li	$v0,READ_CORE_TIMER
	syscall 			# resetCoreTimer()
	li	$t1,200000
	blt	$v0,$t1,while2
	li	$a1,4
	sll	$a1,$a1,16
	ori	$a1,$a1,10
	move	$a0,$t0
	li	$v0,PRINT_INT
	syscall
	addi	$t0,$t0,1
	li	$a0,'\r'
	li	$v0,PUT_CHAR
	syscall
	j	while
	li	$v0,0
	jr	$ra
