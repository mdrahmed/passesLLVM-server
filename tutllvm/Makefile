CXXFLAGS=-O3 -funroll-loops -Wall -D_FORTIFY_SOURCE=2 -g -Wno-pointer-sign -DVERSION=1  -Wno-variadic-macros
CLANG_CFL=$(shell llvm-config-14 --cxxflags) -Wl,-znodelete -fno-rtti -fpic $(CXXFLAGS)
CLANG_LFL=$(shell llvm-config-14 --ldflags --libs)

PASS=condition_pass.so
PASS_SRC=condition_pass.cpp

test: test.processed.o
	clang++-14 $^ -o $@

$(PASS): $(PASS_SRC)
	clang++-14 $(CLANG_CFL) -shared $^ -o $@ $(CLANG_LFL)

%.processed.o: %.cpp $(PASS)
	clang++-14 -flegacy-pass-manager -fno-discard-value-names -g -Xclang -load -Xclang $(PASS) $< -o $@ -c

%.processed.ll: %.cpp $(PASS)
	clang++-14 -flegacy-pass-manager -g -Xclang -load -Xclang $(PASS) $< -o $@ -c -S -emit-llvm

