.data
L1:
.fill 256
.text
.global _start
_start:

mov $L1,%ebx

loop:

cmpb $0,(%ebx)
jna endloop

cmpb $99,(%ebx)
jnz loopfail

add $1,%ebx
cmpb $111,(%ebx)
jnz loopfail

add $1,%ebx
cmpb $99,(%ebx)
jnz loopfail

add $1,%ebx
cmpb $111,(%ebx)
jnz loopfail

add $1,%ebx
cmpb $110,(%ebx)
jnz loopfail

add $1,%ebx
cmpb $117,(%ebx)
jnz loopfail

add $1,%ebx
cmpb $116,(%ebx)
jnz loopfail
sub $6,%ebx
jmp success

loopfail:
add $1,%ebx
jmp loop

endloop:
mov $0x00000000,%ebx

success:

checkHere:

movl $1,%eax
movl $0,%ebx
int  $0x80
