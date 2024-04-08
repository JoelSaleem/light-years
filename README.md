from within build dir
cmake -S .. -B . 

cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_OSX_ARCHITECTURES=arm64 -S .. -B .


lldb LightYearsGame/LightYearsGame 