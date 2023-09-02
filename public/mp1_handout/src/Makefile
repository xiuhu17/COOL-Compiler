SUPPORT_DIR=../cool-support
FLEX_SRC=cool.flex
BISON_SRC=cool.y
COMMON_OBJS=stringtab.o handle_flags.o utilities.o
FLEX_OBJS=lex_main.o
BISON_OBJS=parser_phase.o dumptype.o tree.o cool_tree.o tokens_lex.o
SUPPORT_DIR_OBJS=${FLEX_OBJS} ${BISON_OBJS} ${COMMON_OBJS}
CC=g++ -g -Wall -Wno-register -DDEBUG -I${SUPPORT_DIR}/include -I.
FLEX=flex -d
BISON=bison -d -v -y -b cool --debug -p cool_yy

# Disable built-in rules and variables
.SUFFIXES:

all: lexer parser
lexer: ${FLEX_SRC}.o ${FLEX_OBJS} ${COMMON_OBJS}
	${CC} $^ -o $@
parser: ${BISON_SRC}.o ${BISON_OBJS} ${COMMON_OBJS}
	${CC} $^ -o $@

${SUPPORT_DIR_OBJS}: %.o: ${SUPPORT_DIR}/src/%.cc
	${CC} -c $< -o $@
%.o: %.cc
	${CC} -c $< -o $@

${FLEX_SRC}.cc: ${FLEX_SRC}
	${FLEX} -o$@ $<
${BISON_SRC}.cc ${BISON_SRC}.h: ${BISON_SRC}
	${BISON} --header=${BISON_SRC}.h --output=${BISON_SRC}.cc $<

clean:
	-rm -f ${FLEX_SRC}.o ${BISON_SRC}.o ${SUPPORT_DIR_OBJS} ${BISON_SRC}.cc ${BISON_SRC}.h ${FLEX_SRC}.cc ${BISON_SRC}.output lexer parser
