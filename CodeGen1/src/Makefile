CXX = g++
CC = gcc
LEXER = ../reference-binaries/lexer
PARSER = ../reference-binaries/parser
SEMANT = ../reference-binaries/semant

CXXFLAGS = -I. -I../cool-support/include -std=c++17 -Wall -Wno-register -Wno-write-strings

debug = true
ifeq ($(debug),true)
  CXXFLAGS := $(CXXFLAGS) -DDEBUG -g
endif

SRCS := $(wildcard *.cl)

SUPPORT_SRC = ast_lex.cc ast_parse.cc stringtab.cc dumptype.cc cool_tree.cc tree.cc cgen_main.cc utils.cc
SUPPORT_OBJS = $(SUPPORT_SRC:.cc=.o)
MP_SRC = operand.cc value_printer.cc
MP_OBJS = $(MP_SRC:.cc=.o)
INCL = $(wildcard *.h) $(wildcard ../include/*.h)

default: all
all: cgen-1 cgen-2

cgen-1: cgen-1.o $(MP_OBJS) $(SUPPORT_OBJS)
	$(CXX) -o $@ $+
cgen-1.o: cgen.cc $(INCL)
	$(CXX) -c $(CXXFLAGS) $< -o $@

cgen-2: cgen-2.o $(MP_OBJS) $(SUPPORT_OBJS)
	$(CXX) -o $@ $+
cgen-2.o : cgen.cc $(INCL)
	$(CXX) -c $(CXXFLAGS) -DMP3 $< -o $@

coolrt.o : coolrt.cc coolrt.h
	$(CXX) -g $(CXXFLAGS) -c $< -o $@
coolrt.bc : coolrt.cc coolrt.h
	$(LLVMGCC) $(CXXFLAGS) -emit-llvm -c coolrt.c -o $@

$(SUPPORT_OBJS): %.o: ../cool-support/src/%.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@
$(MP_OBJS): %.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f cgen-1.o cgen-2.o $(SUPPORT_OBJS) $(MP_OBJS) cgen-1 cgen-2
