	.data
	.equ SFR_BASE_HI, 0xBF88
	.equ TRISE, 0x6100
	.equ LATE, 0x6120
	.text
	.globl main
		
		
main:
	lui	$t0, SFR_BASE_HI
	lw	$t1, TRISE ($t0)
	andi	$t1, $t1, 0xFFF0
	sw	$t1, TRISE ($t0)
	
	
while:
	li	$v0, 2
	syscall

if:
	bne	$v0,'0',if2
	lw	$t2, LATE($t0)
	andi	$t2,$t2,0xFFF0
	ori	$t2,$t2,0x0001
	sw	$t2, LATE($t0)
	
	j 	while

if2:
	bne	$v0,'1',if3
	lw	$t2, LATE($t0)
	andi	$t2,$t2,0xFFF0
	ori	$t2,$t2,0x0002
	sw	$t2, LATE($t0)
	
	j 	while
	
if3:
	bne	$v0,'2',if4
	lw	$t2, LATE($t0)
	andi	$t2,$t2,0xFFF0
	ori	$t2,$t2,0x0004
	sw	$t2, LATE($t0)
	
	j 	while
	
if4:
	bne	$v0,'3', else
	lw	$t2, LATE($t0)
	andi	$t2,$t2,0xFFF0
	ori	$t2,$t2,0x0008
	sw	$t2, LATE($t0)
	
	j 	while
	
else:
	lw	$t2, LATE($t0)
	andi	$t2,$t2,0xFFF0
	ori	$t2,$t2,0x000F
	sw	$t2, LATE($t0)
	li	$a0, 1000
	jal	delay
	
	j	while
	
delay:
	li	$v0,12
	syscall
	mul	$a0,$a0,20000
loop:
	li	$v0,11
	syscall
	blt	$v0,$a0,loop
	
	jr	$ra
	
	
	
	
	
