	.data
	.text
	.globl main
	
main:
	li	$v0,2 
	syscall
	move	$t0,$v0
	move	$a0,$v0
	li	$v0,3
	syscall	
	
while:	
	beq	$t0,'\n',endw
	j	while
	
endw:	
	jr	$ra
	
	
