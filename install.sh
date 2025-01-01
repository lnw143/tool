git clone https://github.com/emscripten-core/emsdk.git 

if [[ $? -ne 0 ]]; then
  echo "Git clone failed"
  exit 1
fi

cd emsdk

./emsdk install latest
./emsdk activate latest --permanent
