g++ -std=c++17 -O2 ./solutions/sol.cc -o ./solutions/sol

mkdir data

cd generator
pwd
g++ -std=c++17 -O2 gen.cc -o gen
./gen

cd ..

cd input_format_validator
g++ -std=c++17 -O2 checker.cc -o checker

cd ..
