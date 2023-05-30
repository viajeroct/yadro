if [ ! -d ./build ]; then
  mkdir build
fi
cd build
cmake ..
cmake --build .

./yadro ../input_data/input.txt ../input_data/output.txt
