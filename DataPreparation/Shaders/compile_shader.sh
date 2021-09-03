echo "Compiling for iOS (es 120)"
shaderc -f vertex.sc -o bin/essl/vertex.bin --type vertex -i ../../Vendor/bgfx/bgfx/src -p 100_es --platform ios
shaderc -f fragment.sc -o bin/essl/fragment.bin --type fragment -i ../../Vendor/bgfx/bgfx/src -p 100_es --platform ios

# echo "Compiling for iOS (metal)"
# shaderc -f vertex.sc -o bin/metal/vertex.bin --type vertex -i ../../Vendor/bgfx/bgfx/src -p metal --platform ios
# shaderc -f fragment.sc -o bin/metal/fragment.bin --type fragment -i ../../Vendor/bgfx/bgfx/src -p metal --platform ios

# echo "Compiling for OSX (metal)"
# shaderc -f vertex.sc -o bin/metal/vertex.bin --type vertex -i ../../Vendor/bgfx/bgfx/src -p metal --platform osx
# shaderc -f fragment.sc -o bin/metal/fragment.bin --type fragment -i ../../Vendor/bgfx/bgfx/src -p metal --platform osx

# echo "Compiling for OSX (OpenGl)"
# shaderc -f vertex.sc -o bin/glsl/vertex.bin --type vertex -i ../../Vendor/bgfx/bgfx/src -p 150 --platform osx
# shaderc -f fragment.sc -o bin/glsl/fragment.bin --type fragment -i ../../Vendor/bgfx/bgfx/src -p 150 --platform osx