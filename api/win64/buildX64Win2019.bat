mkdir build
cd build
#del CMakeCache.txt
cmake .. -DT2SDK=on -G"Visual Studio 16 2019" -Ax64 -DWIN32MT=off -D_CRT_NO_TIME_T=on -DTESTOR=on
cd ..