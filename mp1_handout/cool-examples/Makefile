default: all

debug = true

CLSDIR  = /home/class/cs426
## MPDIR   = $(CLSDIR)/mp/mp2
MPDIR   = ..
LLVMDIR = $(CLSDIR)/llvm-1.4-new/local
LLVMGCC = $(CLSDIR)/llvm-1.4-new/cfrontend/x86/llvm-gcc/bin/llvm-gcc

LEXER   = $(MPDIR)/support_code/lexer
PARSER  = $(MPDIR)/support_code/parser
SEMANT  = $(MPDIR)/support_code/semant
CGEN    = $(MPDIR)/src/cgen
COOLRT  = $(MPDIR)/src/coolrt.o

COOLEX  = $(CLSDIR)/mp/cool-examples/

TESTS = $(wildcard *.cl)

all:  $(TESTS:.cl=.out)

.PRECIOUS: %.exe %.bc %.ll

%.ast: %.cl $(LEXER) $(PARSER) $(SEMANT)
	$(LEXER) $< | $(PARSER) | $(SEMANT) > $@

%.ll: %.ast $(CGEN)
	$(CGEN) $(CGENOPTS) < $< > $@

%.bc: %.ll
	cpp $< | sed -e"s/#.*//" > $@.exp
	llvm-as -f -o $@ $@.exp  
	@rm $@.exp

%.verify: %.bc
	opt -verify $< | llvm-dis > $@

%.exe: %.bc $(COOLRT)
	gccld $< $(COOLRT) -o $@

%-opt.bc: %.exe
	opt-cvs -internalize -heap2stack -scalarrepl -mem2reg -adce \
	  -instcombine -load-vn -dse -adce < $*.exe.bc > $*-opt.bc

%-optmax.bc: %.exe
	opt-cvs -adce -instcombine -simplifycfg -inline -internalize \
	-globaldce -instcombine -simplifycfg -heap2stack -scalarrepl \
	-mem2reg -adce -load-vn -dse -licm -gcse -adce  -instcombine -simplifycfg \
	< $*.exe.bc > $*-optmax.bc

%.out: %.exe
	./$< > $@

arith.out: arith.exe arith.in
	./arith.exe < arith.in > $@

graph.out: graph.exe g1.graph
	./graph.exe < g1.graph > $@

## Spaces and case are both significant in this palindrome test
palindrome.out: palindrome.exe
	echo "able was i ere i saw elba" | ./$< > $@

sort_list.out: sort_list.exe 
	echo "8" | ./$< > $@

atoi.ast: atoi.cl atoi_test.cl $(LEXER) $(PARSER) $(SEMANT)
	$(LEXER) atoi.cl atoi_test.cl | $(PARSER) | $(SEMANT) > $@

atoi.out: atoi.exe
	 sh -c "echo 8; echo 7; echo 6" | ./$< > $@

life.out: life.exe
	sh -c "echo y; echo 8; echo y; echo y; echo n" | ./$< > $@

%.diff: %.out
	@diff $< $*.std > /dev/null || \
		echo "Test failed: run 'diff $*.out $*.std' ."

clean:
	-rm -f core *.exe *.bc *.ll *.exp *.verify *.out

realclean: clean
