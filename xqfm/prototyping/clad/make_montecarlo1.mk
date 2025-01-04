/usr/lib/llvm-11/bin/clang++ -fplugin=/home/acea/Software/build_dir/./lib/clad.so  -I /home/acea/Software/clad/include/ -std=c++14 .cpp

/usr/lib/llvm-11/bin/clang++ -Xclang -add-plugin -Xclang clad -Xclang -load -Xclang /home/acea/Software/build_dir/./lib/clad.so  -I /home/acea/Software/clad/include/ -std=c++14 .cpp 
