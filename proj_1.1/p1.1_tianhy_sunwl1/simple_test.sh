make translator
# gcc translator.c src/compression.c src/utils.c -o translator
./translator test/in/my_test/input_1.s out.s
cat out.s