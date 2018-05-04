lex test.l
yacc -d test.y
gcc lex.yy.c y.tab.c -o f -ly -ll
./f
