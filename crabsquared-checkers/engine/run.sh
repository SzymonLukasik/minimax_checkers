mkdir -p build
cd build
cmake ..
make
make check
#tests/test_8x8_forward_only
#tests/test_simple_movements
cd ..
