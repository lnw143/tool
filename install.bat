@REM set http_proxy=http://127.0.0.1:<port>
@REM set https_proxy=https://127.0.0.1:<port>

cd emsdk

emsdk install latest

emsdk activate latest --permanent
