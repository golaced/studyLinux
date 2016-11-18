rm -r CMakeFiles
rm CMakeCache.txt
rm myapp
cmake .
touch mavlink/*
touch mavlink/common/*
touch *
make

