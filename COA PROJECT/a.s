addi x1,x0,377
addi x2,x0,1
addi x3,x0,2
rem x5,x1,x3
beq x5,x0,20
addi x3,x3,1
mul x5,x3,x3
blt x5,x1,-20
add x2,x0,x0
jal x0,4
add x2,x0,x3


