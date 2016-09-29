#include <mips/regdef.h>
#include <sys/syscall.h>

#define A0	SS
#define A1	((SS) + 4)
#define SS	8
#define FP 	4
#define GP	0

	.text
	.align 2
	.globl main
	.ent main
/*
 * Writes on stdout what comes in through stdin. 
 * On syscall failure, return the error code. Otherwise return 0
 */ 
main:
	subu	sp, sp, 
	sw	$fp, FP(sp)	
	sw	gp, GP(sp)	
	move	$fp, sp

	sw	a0, A0 ($fp)
	sw	a1, A1($fp)
/*
 * Empieza el codigo...
 * los nombres de los registros estan mal es para ubicarlos facil y despues cambiarlos
 * la cosa es asi las 8 comparaciones i +/- j +/- si pasa entra a la funcion donde se accede
 * a i j de la matriz y verifica que sea igual a 1 devuelve 1 sino 0, falta allocar bien los stack
 * de la principal y de la funcion
 */
 	move $s1, i #i
 	move $s2, j #j
	addi $s3, $s1, 1 #imasuno
	addi $s4, $s2, 1 #jmasuno
	addi $s5, $s1, -1	#imenosuno
	addi $s6, $s2, -1 #jmenosuno
	move $s0, regm #m
	move $s7, regn #n
	move $t8, matriz #matriz
	#sub $s5, i, regcon1
	#sub $s6, j, regcon1
	ble $s3, $s0, imas #compara si i + 1 <= m 
comp2:
	ble $s4, $s7, jmas #compara si j + 1 <= n 
comp3:
	bge $s5, zero, imenos #compara si i - 1 >= 0 
comp4:
	bge $s6, zero, jmenos #compara si j - 1 >= 0
comp5:
	bge $s3, $s0 , comp6 #compara si i + 1 >= m
	ble $s4, $s7, imasjmas #compara si j + 1 <= n
comp6:
	bge $s3, $s0 , comp7 #compara si i + 1 >= m
	bge $s6, zero, imasjmenos #compara si j - 1 >= 0 
comp7:
	blt $s5, zero , comp8 #compara si i + 1 < 0
	ble $s4, $s7 , imenosjmas #compara si j + 1 <= n 
comp8:
	blt $s5, zero , fin #compara si i + 1 < 0
	ble $s6, zero, imenosjmenos #compara si j + 1 >= 0 
	#falta desapilar stack
fin:
	jr $ra

imas:
	move $a0, $s3
	move $a1, $s2
	move $a2, $s7
	move $a3, $matriz
	jal accessijpos
	b comp2
jmas:
	move $a0, $s1
	move $a1, $s4
	move $a2, $s7
	move $a3, $matriz
	jal accessijpos
	b comp3
imenos:
	move $a0, $s5
	move $a1, $s2
	move $a2, $s7
	move $a3, $matriz
	jal accessijpos
	b comp4
jmenos:
	move $a0, $s1
	move $a1, $s6
	move $a2, $s7
	move $a3, $matriz
	jal accessijpos
	b comp5
imasjmas:
	move $a0, $s3
	move $a1, $s4
	move $a2, $s7
	move $a3, $matriz
	jal accessijpos
	b comp6
imasjmenos:
	move $a0, $s4
	move $a1, $s6
	move $a2, $s7
	move $a3, $matriz
	jal accessijpos
	b comp7
imenosjmas:
	move $a0, $s4
	move $a1, $s6
	move $a2, $s7
	move $a3, $matriz
	jal accessijpos
	b comp8
imenosjmenos:
	move $a0, $s5
	move $a1, $s6
	move $a2, $s7
	move $a3, $matriz
	jal accessijpos
	b fin

accessijpos:
	#reservar stack, cargar argumentos
	move $t2, $a0 # pos i
	move $t4, $a1 # pos j
	move $t3, $a2 # n de la matriz
	move $t0, $a3 # pos 0,0 de la matriz
    mul $t5, $t3, $t2 # $t5 <-- width * i
    add $t5, $t5, $t4 # $t5 <-- width * i + j
    sll $t5, $t5, 2 # $t5 <-- 2^2 * (width * i + j)
    add $t5, $t0, $t5 # $t5 <-- base address + (2^2 * (width * i + j))
    lb $t6, $t5 #carga el 1 o 0 de la matriz
    li $t7, 49 # carga '1' en t7 para comparar
    beq $t6, $t7, sumaruno #igual suma uno
    b finaccessijpos
finaccessijpos:
	#falta desapilar stack 
	jr $ra
sumaruno:
	addi $v0, 1
	b finaccessijpos
