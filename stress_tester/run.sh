./clean.sh
g++ first.cpp -o first.exe
g++ second.cpp -o second.exe
g++ input_generator.cpp -o input_generator.exe
for (( i = 1; i<= 10000; i++));
do
    echo $i
    ./input_generator $i > input.txt
    ./first < input.txt > output_first.txt
    ./second < input.txt > output_second.txt
    diff -w output_first.txt output_second.txt || break
done
