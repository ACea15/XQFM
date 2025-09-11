all:
	/usr/lib/llvm-11/bin/clang++ -fplugin=/home/acea/Software/build_dir/lib/clad.so -I /home/acea/Software/clad/include/ -std=c++14 dClasses.cpp
