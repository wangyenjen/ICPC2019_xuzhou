g++ -std=c++17 -O2 sol.cc -o sol

mkdir data

cd generator
pwd
g++ -std=c++17 -O2 gen_small.cc -o gen_small
g++ -std=c++17 -O2 gen_random.cc -o gen_random
./gen_small
./gen_random

cd ..

cd input_format_validator
g++ -std=c++17 -O2 checker.cc -o checker


cd ..
