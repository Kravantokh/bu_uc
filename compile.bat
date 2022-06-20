@ECHO OFF
gcc -fanalyzer -g examples/ex1.c src/*.c -I include
PAUSE
