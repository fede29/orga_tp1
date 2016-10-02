#include <mips/regdef.h>
#include <sys/syscall.h>

	.text
	.align 2
	.globl vecinos
	.ent vecinos
vecinos:
	subu	sp, sp, 76 #creo stack
	sw	ra,	40(sp) #guardo el ra en stack
	sw	$fp, 36(sp)	#guardo el fp en stack
	sw	gp, 32(sp) #guardo el gp en stack
	sw	s0, 44(sp) #guardo el s0 en stack
	sw	s1, 48(sp) #guardo el s1 en stack
	sw	s2, 52(sp) #guardo el s2 en stack
	sw	s3, 56(sp) #guardo el s3 en stack
	sw	s4, 60(sp) #guardo el s4 en stack
	sw	s5, 64(sp) #guardo el s5 en stack
	sw	s6, 68(sp) #guardo el s6 en stack
	sw	s7, 72(sp) #guardo el s7 en stack
	sw	t0, 16(sp) #guardo el 5to parametro N en el stack  en stack
	move	$fp, sp #muevo el fp al inicio del stack
	move	t1, a0 #cargo el 1er parametro a* en t1 
	move	t2, a1 #cargo el 2do parametro i en t2
	move	t3, a2 #cargo el 3er parametro j en t3
	move	t4, a3 #cargo el 4tp parametro M en t4
/*
 * Empieza el codigo...
 * los nombres de los registros estan mal es para ubicarlos facil y despues cambiarlos
 * la cosa es asi las 8 comparaciones i +/- j +/- si pasa entra a la funcion donde se accede
 * a i j de la matriz y verifica que sea igual a 1 devuelve 1 sino 0, falta allocar bien los stack
 * de la principal y de la funcion
 */
 	move	s1, t2 #i
 	move	s2, t3 #j
	addi	s3, s1, 1 #imasuno
	addi	s4, s2, 1 #jmasuno
	addi	s5, s1, -1	#imenosuno
	addi	s6, s2, -1 #jmenosuno
	move	s0, t4 #m
	move	s7, t0 #n
	move	t8, t1 #matriz
	move	t6, zero #en t6 se va a ir acumulando el valor
	ble	s3, s0, imas #compara si i + 1 <= m 
comp2:
	ble	s4, s7, jmas #compara si j + 1 <= n 
comp3:
	bge	s5, zero, imenos #compara si i - 1 >= 0 
comp4:
	bge	s6, zero, jmenos #compara si j - 1 >= 0
comp5:
	bge	s3, s0 , comp6 #compara si i + 1 >= m
	ble	s4, s7, imasjmas #compara si j + 1 <= n
comp6:
	bge	s3, s0 , comp7 #compara si i + 1 >= m
	bge	s6, zero, imasjmenos #compara si j - 1 >= 0 
comp7:
	blt	s5, zero , comp8 #compara si i + 1 < 0
	ble	s4, s7 , imenosjmas #compara si j + 1 <= n 
comp8:
	blt	s5, zero , fin #compara si i + 1 < 0
	ble	s6, zero, imenosjmenos #compara si j + 1 >= 0 
	#falta desapilar stack
fin:
	move	vo,t6
	jr	ra
	.end	vecinos

imas: #se llama a a[i+1][j] para ver si esta vivo o no
	move	a0, s3
	move	a1, s2
	move	a2, s7
	move	a3, t8
	jal	accessijpos
	add	t6, v0, t6
	b	comp2
jmas: #se llama a a[i][j+1] para ver si esta vivo o no
	move	a0, s1
	move	a1, s4
	move	a2, s7
	move	a3, t8
	jal	accessijpos
	add	t6, v0, t6
	b	comp3
imenos: #se llama a a[i-1][j] para ver si esta vivo o no
	move	a0, s5
	move	a1, s2
	move	a2, s7
	move	a3, t8
	jal accessijpos
	add t6, v0, t6
	b comp4
jmenos: #se llama a a[i][j-1] para ver si esta vivo o no
	move	a0, s1
	move	a1, s6
	move	a2, s7
	move	a3, t8
	jal accessijpos
	add t6, v0, t6
	b comp5
imasjmas: #se llama a a[i+1][j+1] para ver si esta vivo o no
	move	a0, s3
	move	a1, s4
	move	a2, s7
	move	a3, t8
	jal accessijpos
	add t6, v0, t6
	b comp6
imasjmenos: #se llama a a[i+1][j-1] para ver si esta vivo o no
	move	a0, s4
	move	a1, s6
	move	a2, s7
	move	a3, t8
	jal accessijpos
	add t6, v0, t6
	b comp7
imenosjmas: #se llama a a[i-1][j+1] para ver si esta vivo o no
	move	a0, s4
	move	a1, s6
	move	a2, s7
	move	a3, t8
	jal accessijpos
	add t6, v0, t6
	b comp8
imenosjmenos: #se llama a a[i-1][j-1] para ver si esta vivo o no
	move	a0, s5
	move	a1, s6
	move	a2, s7
	move	a3, t8
	jal accessijpos
	add t6, v0, t6
	lw	ra, 40(sp) #empiezo a liberar stack, cargo el ra del stack
	lw	$fp, 36(sp) #cargo el fp del stack
	lw	gp, 32(sp) #cargo el gp del stack
	lw	s0, 44(sp) #cargo el s0 del stack
	lw	s1, 48(sp) #cargo el s1 del stack
	lw	s2, 52(sp) #cargo el s2 del stack
	lw	s3, 56(sp) #cargo el s3 del stack
	lw	s4, 60(sp) #cargo el s4 del stack
	lw	s5, 64(sp) #cargo el s5 del stack
	lw	s6, 68(sp) #cargo el s6 del stack
	lw	s7, 72(sp) #cargo el s7 del stack
	addiu	sp, sp, 76
	jr	ra

accessijpos:
	subu	sp, sp, 32 #creo stack
	sw	ra,	24(sp) #guardo el ra en stack
	sw	$fp, 20(sp)	#guardo el fp en stack
	sw	gp, 16(sp) #guardo el gp en stack
	move	t2, a0 # pos i
	move	t4, a1 # pos j
	move	t3, a2 # n de la matriz
	move	t0, a3 # pos 0,0 de la matriz
	mul	t5, t3, t2 # $t5 <-- width * i
	add	t5, t5, t4 # $t5 <-- width * i + j
	add	t5, t0, t5 # $t5 <-- base address + (2^2 * (width * i + j))
	lb	t6, t5 #carga el 1 o 0 de la matriz
	li	t7, 49 # carga '1' en t7 para comparar
	beq	t6, t7, sumaruno #igual suma uno
	li	v0, 0
	b finaccessijpos
finaccessijpos:
	lw	ra, 24(sp) #empiezo a liberar stack, cargo el ra del stack
	lw	$fp, 20(sp) #cargo el fp del stack
	lw	gp, 16(sp) #cargo el gp del stack
	jr	ra
sumaruno:
	li	v0, 1
	b	finaccessijpos
