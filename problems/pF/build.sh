g++ -std=c++17 -O2 sol.cc -o sol

cd input_format_validator
g++ -std=c++17 -O2 checker.cc -o checker

cd ..

cd output_validator
g++ -std=c++17 -O2 judge.cc -o judge

cd ..
