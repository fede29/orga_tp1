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
	subu	sp, sp, SS
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
 * de la principal y de la funcion, tambien faltan algunas comparaciones
 */
	addi regimasuno, i, 1
	addi regjmasuno, i, 1
	sub regimenosuno, i, regcon1
	sub regjmenosuno, i, regcon1
	bgtz regm, regimasuno, imasunomenorquem
comp2:
	bgtz regn, regjmasuno, jmasunomenorquen
comp3:
	bltz zero, regimenosuno, imenosunomenorquezero
comp4:
	bltz zero, regjmenosuno, jmenosunomenorquezero
comp5:

comp6:

comp7:

comp8:

	#falta desapilar stack 
	jr $ra

imasunomenorquem:
	jal accessijpos
	b comp2
jmasunomenorquen:
	jal accessijpos
	b comp3
imenosunomenorquezero:
	jal accessijpos
	b comp4
jmenosunomenorquezero:
	jal accessijpos
	b comp5


accessijpos:
    mul $t5, $t3, $t2       # $t5 <-- width * i
    add $t5, $t5, $t4       # $t5 <-- width * i + j
    sll $t5, $t5, 2         # $t5 <-- 2^2 * (width * i + j)
    add $t5, $t0, $t5       # $t5 <-- base address + (2^2 * (width * i + j))
    lb $t6, $t5
    beq $t6, $regconuno, sumaruno
    b finaccessijpos
finaccessijpos:
	#falta desapilar stack 
	jr $ra
sumaruno:
	addi $v0, 1
	b finaccessijpos



.data
	b: .byte

