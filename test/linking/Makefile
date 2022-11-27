CXXFLAGS=-O3 -funroll-loops -Wall -D_FORTIFY_SOURCE=2 -g -Wno-pointer-sign -DVERSION=1  -Wno-variadic-macros
CLANG_CFL=$(shell llvm-config-14 --cxxflags) -Wl,-znodelete -fno-rtti -fpic $(CXXFLAGS)
CLANG_LFL=$(shell llvm-config-14 --ldflags --libs)

CLANG=clang++-14
PASS=simple_print.so
PASS_SRC=simple_print.cpp

sim: sim.rewritten.o basic_log.o
	$(CLANG) -o $@ $^

%.o: %.cpp
	$(CLANG) -c -o $@ $<
	

%.rewritten.o: %.cpp $(PASS)
	$(CLANG) -c -o $@ -flegacy-pass-manager -g -Xclang -load -Xclang $(PASS) $<

#sim: sim.rewritten.o hello.o
#	$(CLANG) -o $@ $^



$(PASS): $(PASS_SRC)
	$(CLANG) $(CLANG_CFL) -shared $< -o $@
