.global strdcpy
oldEbp = 0
retAddr = oldEbp + 4
strDest = retAddr + 4
strSrc = strDest + 4
delim = strSrc + 4

strdcpy:
pushl %ebp
movl %esp,%ebp

movl strDest(%ebp),%ecx
movl strSrc(%ebp),%edx

while:
cmpb $0,(%ecx)
jz whileEnd

#movl %ebp,%eax
#addl $strSrc,%eax
leal strSrc(%ebp),%eax
pushl %eax
movl %ebp,%eax
addl $delim,%eax
pushl (%eax)
call strchr
addl $8,%esp
cmp $0,%eax
jz whileEnd

leal strSrc(%ebp),%eax
movb (%eax),%bl
leal strDest(%ebp),%eax
movb %bl,(%eax)
addl $1,strDest(%ebp)
addl $1,strSrc(%ebp)

jmp while
whileEnd:

addl $1,strDest(%ebp)
movl $0,strDest(%ebp)

movl %ebp,%eax
addl $strDest,%eax

movl %ebp,%esp
popl %ebp
ret