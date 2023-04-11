	     .equ     INICIAL,    0xBF88   
             .equ     TRISE,      0x6100
             .equ     TRISB,      0x6040
             .equ     PORTE,      0x6110
             .equ     PORTB,      0x6050
             .equ     LATE,       0x6120
             .equ     LATB,       0x6060
             .equ     TRISD,      0x60C0
             .equ     PORTD,      0x60D0
             .equ     READ_CORE_TIMER,     11
             .equ     RESET_CORE_TIMER,    12
             .equ     printInt10,          7
             .equ     printInt,            6
             .equ     putChar,             3
             .data
             .text
             .globl                        main

main:        addiu $sp,            $sp,      -24
             sw	      $ra,          0($sp)
             sw       $s0,          4($sp)
             sw       $s1,          8($sp)
             sw       $s2,         12($sp)
             sw       $s3,         16($sp)
             sw       $s4,         20($sp)

             lui      $s4,         INICIAL
             lw       $t1,      TRISE($s4)
             andi     $t1,            $t1,     0xFFE1                   ## 1111 1111 1110 0001
             sw       $t1,      TRISE($s4)


             lw       $t1,       LATE($s4)
             andi     $t1,            $t1,     0xFFE1
             sw       $t1,       LATE($s4) 

             li       $s0,          0x0009
             li       $s1,               2
             li       $s2,               4


loop:        lw       $t1,       LATE($s4)
             andi     $t1,            $t1,    0xFFE1

             sll      $t2,            $s0,    1
             or       $s3,            $t1,    $t2


             sw       $s3,       LATE($s4)

             move     $a0,            $s0
             sll      $t2,            $s2,    16
             ori      $a1,            $t2,    2

             li       $v0,            printInt
             syscall


             li       $a0,            '\n'
             li       $v0,            putChar
             syscall


             li       $a0,            143
             jal      delay


             xori     $s3,            $s3,     0x001E
             sw       $s3,        LATE($s4)  

             sll      $t2,            $s2,    16
             ori      $a1,            $t2,    2
             xori     $a0,            $s0,    0x000F
             li       $v0,            printInt
             syscall   


             li       $a0,            '\n'
             li       $v0,            putChar
             syscall

             li       $a0,            143 
             jal      delay

             j        loop


endprog:     lw       $ra,           0($sp)
             lw       $s0,           4($sp)
             lw       $s1,           8($sp)
             lw       $s2,          12($sp)
             lw       $s3,          16($sp)
             lw       $s4,          20($sp)

             addiu    $sp,             $sp,       24

             jr       $ra




######################################################################################################

delay:    mul   $t0,    $a0,       20000
          li    $v0, RESET_CORE_TIMER
          syscall

loop2:    li    $v0, READ_CORE_TIMER
          syscall

          blt   $v0,    $t0,     loop2

enddelay: jr          $ra
