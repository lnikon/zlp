# Specify stack size
#.STACK = 1024

# Some variable for fun and profit :)))))
.DATA:
  WORD age = 12;
  CHAR sex = 'f';

# All the silly work goes here
.CODE:
Func f_age:
  ASSIGN B A4, 6
  MOVE B R2, R6
EndF

Func f_sex1:
  MOVE B R2, R6
  MOVE_NEQ W R5, R6
  MOVE QW R1, R2
  MOVE_EQ R3, R4
EndF
