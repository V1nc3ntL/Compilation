
EXE=minicc
UTILS=utils
OBJ_DIR=obj
OBJ=y.tab.o lex.yy.o arch.o common.o passe_1.o passe_2.o

DEBUG_LEX=1
DEBUG_YACC=0

ifeq ($(DEBUG_YACC),1)
	YACC_FLAGS=-DYYDEBUG=1
else
	YACC_FLAGS=
endif

ifeq ($(DEBUG_LEX),1)
	LEX_FLAGS=-d
else
	LEX_FLAGS=
endif

CFLAGS=-O0 -g -std=c99 -DYY_NO_LEAKS -Wno-implicit-function-declaration
INCLUDE=-I$(UTILS)

all: minicc

minicc: $(OBJ)
	@echo "| Linking / Creating binary $@"
	@cd obj/;gcc $(CFLAGS) $(INCLUDE) -L../$(UTILS) ../$^ -o $@ -lminiccutils;mv $^ ../$^

y.tab.c: grammar.y Makefile
	@echo "| yacc -d grammar.y"
	@yacc -d grammar.y

lex.yy.c: lexico.l Makefile
	@echo "| lex $(LEX_FLAGS) lexico.l"
	@lex $(LEX_FLAGS) lexico.l

lex.yy.o: lex.yy.c
	@echo "| Compiling $@"
	@gcc $(YACC_FLAGS) $(CFLAGS) $(INCLUDE) -o $(OBJ_DIR)/$@ -c $<

y.tab.o: y.tab.c
	@echo "| Compiling $@"
	@gcc $(YACC_FLAGS) $(CFLAGS) $(INCLUDE) -o $(OBJ_DIR)/$@ -c $<

arch.o: arch.c arch.h Makefile
	@echo "| Compiling $@"
	@gcc $(CFLAGS) $(INCLUDE) -o $(OBJ_DIR)/$@ -c $<

common.o: common.c common.h arch.h defs.h Makefile
	@echo "| Compiling $@"
	@gcc $(CFLAGS) $(INCLUDE) -o $(OBJ_DIR)/$@ -c $<

passe_1.o: passe_1.c passe_1.h defs.h common.h Makefile
	@echo "| Compiling $@"
	@gcc $(CFLAGS) $(INCLUDE) -o $(OBJ_DIR)/$@ -c $<

passe_2.o: passe_2.c passe_2.h arch.h defs.h common.h Makefile
	@echo "| Compiling $@"
	@gcc $(CFLAGS) $(INCLUDE) -o $(OBJ_DIR)/$@ -c $<

clean:
	@echo "| Cleaning .o files"
	@rm -f $(OBJ_DIR)/*.o

realclean: clean
	@echo "| Cleaning lex and yacc files, and executable"
	@rm -f y.tab.c y.tab.h lex.yy.c $(EXE)

