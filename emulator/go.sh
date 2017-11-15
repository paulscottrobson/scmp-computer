#rm scmpmc
make
asl -L test.asm
p2bin -l 0 test.p test.bin
./scmpmc test.bin
