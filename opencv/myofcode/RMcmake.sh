rm -r CMakeFiles
rm CMakeCache.txt
cmake .
touch mavlink/*
touch mavlink/common/*
touch *
make

