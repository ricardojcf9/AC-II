	.data
	.equ SFR_BASE_HI, 0xBF88
	.equ TRISB, 0x6040
	.equ TRISE, 0x6100
	.equ PORTB, 0x6050
	.equ LATE, 0x6120
	.text
	.globl main
	
main:


	lui	$t0, SFR_BASE_HI
	lw	$t1, TRISB($t0)
	ori	$t1,$t1,0x000F
	sw	$t1, TRISB($t0)
	
	lw	$t1, TRISE($t0)
	andi	$t1,$t1,0xFF00
	sw	$t1, TRISE($t0)
	
	
while:
	lw	$t1, PORTB ($t0)
	andi	$t1, $t1, 0x000F
	li	$t4,0
	
	lw	$t2, LATE ($t0)
	andi	$t2,$t2,0xFFF0
	or	$t3,$t1,$t2
	sw	$t3, LATE ($t0)
	
while2:
	bgt	$t4,3,endw2		# 4 iteracoes, 1 iteracao para cada bit
	andi	$t5,$t1, 0x0001		# $t5 tem apenas o valor do bit menos significativo nessa iteracao
	srl	$t1,$t1,1		# shift a direita para ler todos os bits na posicao dos bits menos significativos
	sll	$t3,$t3,1		# o shift foi feito antes de escrever para os bits ficarem na posicao certa
	or	$t3,$t3,$t5		# escrita (o bit isolado do bit $t5 vai se juntar aos bits do $t3)
	addi	$t4,$t4,1		# incrementacao da iteracao
	j	while2
	
endw2:
	sll	$t3,$t3,4
	lw	$t2, LATE ($t0)
	andi	$t2,$t2,0xFF0F
	or	$t3,$t3,$t2
	sw	$t3, LATE ($t0)
	
	j	while
