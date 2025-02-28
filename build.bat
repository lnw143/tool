@echo off
call ./emsdk/emsdk_env.bat

for /d %%D in (*) do (
    if exist %%D\main.cpp (
        echo processing %%D
        emcc %%D\main.cpp -o %%D\main.js ^
        -s EXPORTED_FUNCTIONS="['_malloc','_free','ccall','allocate','UTF8ToString','intArrayFromString']" ^
        -s WASM=1
    )
)

python -m http.server
