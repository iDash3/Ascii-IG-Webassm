## Image to ascii with web assembly

Dir structure is a mess

./web-implementation has the real web assembly working files

./img has the image test files

./stb has headers for a img lib (not necessary, really)

res.txt is just the result

# compiled with emcc

'''
emcc web-implementation/resize.c -o web-implementation/resize.html -s WASM=1 -s EXTRA_EXPORTED_RUNTIME_METHODS=["cwrap"]
'''

# Should run a sever (JS does not work well with unstrusted async)

'''
python -m http.server
'''

This will eventually be a chrome extension, when i find the time
