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
 * de la principal y de la funcion, tambien faltan algunas comparaciones
 */
	addi regimasuno, i, 1
	addi regjmasuno, j, 1
	addi regimenosuno, i, -1
	addi regjmenosuno, j, -1
	#sub regimenosuno, i, regcon1
	#sub regjmenosuno, j, regcon1
	ble regm, regimasuno, imas
comp2:
	ble regn, regjmasuno, jmas
comp3:
	bge zero, regimenosuno, imenos
comp4:
	bge zero, regjmenosuno, jmenos
comp5:
	bge regimasuno, regm , comp6
	ble regn, regjmasuno, imasjmas
comp6:
	bge regimasuno, regm , comp7
	ble zero, regjmenosuno, imasjmenos
comp7:
	blt regimenosuno, zero , comp8
	ble regn, regjmasuno, imenosjmas
comp8:
	blt regimenosuno, zero , fin
	ble zero, regjmenosuno, imenosjmenos
	#falta desapilar stack
fin:
	jr $ra

imas:
	move $a0, $regimasuno
	move $a1, $j
	move $a2, $regn
	jal accessijpos
	b comp2
jmas:
	move $a0, $i
	move $a1, $regjmasuno
	move $a2, $regn
	jal accessijpos
	b comp3
imenos:
	move $a0, $regimenosuno
	move $a1, $j
	move $a2, $regn
	jal accessijpos
	b comp4
jmenos:
	move $a0, $i
	move $a1, $regimenosuno
	move $a2, $regn
	jal accessijpos
	b comp5
imasjmas:
	move $a0, $regjmasuno
	move $a1, $regjmasuno
	move $a2, $regn
	jal accessijpos
	b comp6
imasjmenos:
	move $a0, $regjmasuno
	move $a1, $regjmenosuno
	move $a2, $regn
	jal accessijpos
	b comp7
imenosjmas:
	move $a0, $regjmasuno
	move $a1, $regjmenosuno
	move $a2, $regn
	jal accessijpos
	b comp8
imenosjmenos:
	move $a0, $regimenosuno
	move $a1, $regjmenosuno
	move $a2, $regn
	jal accessijpos
	b fin

accessijpos:
	#reservar stack, cargar argumentos
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
