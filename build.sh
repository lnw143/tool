source emsdk_env.sh

for dir in ./*
do
if [[ -d "$dir" && "$dir" != "./base" ]] 
then
  	echo "processing $dir"
	emcc $dir/main.cpp -o $dir/main.js \
	-s EXPORTED_FUNCTIONS="['_malloc','_free','ccall','allocate','UTF8ToString','intArrayFromString']" \
	-s WASM=1
fi
done

python -m http.server
