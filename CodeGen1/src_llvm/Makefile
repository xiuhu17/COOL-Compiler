CXX = g++
CC = gcc
LEXER = ../reference-binaries/lexer
PARSER = ../reference-binaries/parser
SEMANT = ../reference-binaries/semant
LLVM_CONF = llvm-config-15

CXXFLAGS = -std=c++17 -Wall -Wno-register -Wno-write-strings -I. -I../cool-support/include -I $(shell ${LLVM_CONF} --includedir)
CXX_LN_FLAGS = $(shell ${LLVM_CONF} --ldflags --libs --system-libs)

debug = true
ifeq ($(debug),true)
  CXXFLAGS := $(CXXFLAGS) -DDEBUG -g
endif

SRCS := $(wildcard *.cl)

SUPPORT_SRC = ast_lex.cc ast_parse.cc stringtab.cc dumptype.cc cool_tree.cc tree.cc cgen_main.cc utils.cc
SUPPORT_OBJS = $(SUPPORT_SRC:.cc=.o)
INCL = $(wildcard *.h) $(wildcard ../include/*.h)

default: all
all: cgen-1 cgen-2

cgen-1: cgen-1.o $(SUPPORT_OBJS)
	$(CXX) $+ $(CXX_LN_FLAGS) -o $@
cgen-1.o: cgen.cc $(INCL)
	$(CXX) -c $(CXXFLAGS) $< -o $@

cgen-2: cgen-2.o $(SUPPORT_OBJS)
	$(CXX) $+ $(CXX_LN_FLAGS) -o $@
cgen-2.o : cgen.cc $(INCL)
	$(CXX) -c $(CXXFLAGS) -DMP3 $< -o $@

$(SUPPORT_OBJS): %.o: ../cool-support/src/%.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f cgen-1.o cgen-2.o $(SUPPORT_OBJS) cgen-1 cgen-2
