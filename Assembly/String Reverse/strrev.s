.data
original:
.=. + 256
reversed:
.=. + 256
.text
.global _start
_start:
  movl $original,%eax
  movl $reversed,%ebx
  
  loop1:
  
  cmpb $0,(%eax)
  jna endloop1
  
  add $1,%eax
  jmp loop1
  
  endloop1:
	
  sub $1,%eax
	
  loop2:
  
  cmpl $original,%eax
  jl endloop2
  
  movb (%eax),%cl
  movb %cl,(%ebx)
  add $1,%ebx
  sub $1,%eax
  jmp loop2
  
  endloop2:
  
  movl $0,(%ebx)
	
  checkHere:
  
  movl $1,%eax
  movl $0,%ebx
  int $0x80
  