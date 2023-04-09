	.data
	.equ SFR_BASE_HI, 0xBF88
	.equ TRISB, 0x6040
	.equ TRISE, 0x6100
	.equ PORTB, 0x6050
	.equ LATE, 0x6120
	.text
	.globl main
	
main:


	lui 	$t0, SFR_BASE_HI
	lw	$t1, TRISB($t0)
	ori	$t1,$t1,0x000F
	sw	$t1, TRISB($t0)
	
	lw	$t1, TRISE($t0)
	andi	$t1,$t1,0xFFF0
	sw	$t1, TRISE($t0)
	
	
while:	
	lw	$t1, PORTB ($t0)
	andi	$t2, $t2, 0x000F
	li	$t4, 0
while2:
	bgt	$t4,3,endw2
	andi	$t5,$t1, 0x0001
	srl	$t1,$t1,1
	sll	$t3,$t3,1
	or	$t3,$t3,$t5
	addi	$t4,$t4,1
	j	while2
	
endw2:
		
	lw	$t2, LATE ($t0)
	andi	$t2,$t2,0xFFF0
	move	$t2,$t3
	sw	$t2, LATE ($t0)
	
	j	while

