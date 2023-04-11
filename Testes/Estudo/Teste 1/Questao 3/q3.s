	.data
	.equ SFR_BASE_HI, 0xBF88
	.equ TRISE, 0x6100
	.equ LATE, 0x6120
	.equ resetCoreTimer, 12
	.equ readCoreTimer, 11
	.text
	.globl main
	
main:
	
	lui	$t0, SFR_BASE_HI
	lw	$t1, TRISE($t0)
	andi	$t1, $t1, 0xFF83
	sw	$t1, TRISE($t0)
	
	li	$t2, 0
	
loop:
	bgt 	$t2,25,endfor
	
	lw	$t3, LATE($t0)
	andi	$t3,$t3,0xFF83
	sll	$t4,$t2,2
	or	$t4,$t4,$t3
	sw	$t4, LATE($t0)
	
	move	$a0, $t2
	li	$a1, 0x00050002
	li	$v0, 6
	syscall
	li      $a0, '\n'
        li      $v0, 3
        syscall
	la	$a0,285
	jal	delay
	addi	$t2,$t2,-1
	
if:
	bge	$t2,0,loop
	li	$t2, 24
	
	j loop
	
delay:

for:    ble     $a0,0,endfor
        li      $v0, resetCoreTimer
        syscall

while: 
        li      $v0, readCoreTimer
        syscall
        blt     $v0,20000, while
        
        addi    $a0,$a0, -1
        j for
endfor:
        jr      $ra
	


