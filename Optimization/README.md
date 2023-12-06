From the directory containing this file, execute the following commands
```
mkdir build; cd build; cmake ..; make -j
```
This should configure and then build the four passes into a single file ``
which you'll then need to run with LLVM `opt`.
Note that you should use the `opt` of LLVM installation that `cmake` found.
If you're not certain which LLVM that is, search for `LLVM_DIR` in `build/CMakeCache.txt`.
You can run _just_ your passes like this:
```
opt -load-pass-plugin=build/libUnitProject.so -passes="unit-licm,unit-sccp" <input> -o <output>
```
which will probably not do much on their own; or use the full optimization sequence given in the PDF.
