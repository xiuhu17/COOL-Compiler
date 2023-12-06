LEXER = ../reference-binaries/lexer
PARSER = ../reference-binaries/parser
SEMANT = ../reference-binaries/semant
CGENREF = ../reference-binaries/cgen-1
CLANG = clang-15
OPT = opt-15

debug = true
mp3 = false
proj_dir = ../src

ifeq ($(debug),true)
  CGENOPTS = -d
else
  CGENOPTS =
endif

ifeq ($(mp3),true)
  CGEN = cgen-2
  COOLRT = ../reference-binaries/coolrt.o
else
  CGEN = cgen-1
  COOLRT =
endif

SRCS := $(wildcard *.cl)

# Disable built-in rules and variables
.SUFFIXES:

.PRECIOUS: %.ast %.ll %-o3.ll %.bin %.llref %-o3.llref %.binref %.outref

default: all
all: $(SRCS:%.cl=%.out)
verify: $(SRCS:%.cl=%.verify)
check: $(SRCS:%.cl=%.check)

cgen-1:
	make -j -C $(proj_dir) cgen-1

cgen-2:
	make -j -C $(proj_dir) cgen-2

%.ast: %.cl
	$(LEXER) $< | $(PARSER) | $(SEMANT) > $@

%.ll: %.ast $(CGEN)
	$(proj_dir)/$(CGEN) $(CGENOPTS) < $< > $@

%-o3.ll: %.ll
	$(OPT) -O3 -S $< -f -o $*-o3.ll

%.bin: %-o3.ll $(COOLRT)
	$(CLANG) -g $+ -o $@

%.verify: %.ll
	$(OPT) -S -verify $<

%.out: %.bin
	./$< > $@ || true

%.check: %.out
	diff -u $< $(<:%.out=%.refout)

%.llref: %.cl
	$(LEXER) $< | $(PARSER) | $(SEMANT) | $(CGENREF) > $@

%-o3.llref: %.llref
	$(OPT) -O3 -S $< -f -o $*-o3.llref

%.binref: %-o3.llref $(COOLRT)
	$(CLANG) -g -x ir - -o $@ < $<

%.outref: %.binref
	./$< > $@ || true

clean:
	-rm -f *.bin *.ll *.out *.ast *.verify *.llref *.binref *.outref 
	make -C $(proj_dir) clean