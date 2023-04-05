

all: include/ast.h ast.c  include/show_tree.h show_tree.c parser.y tokenizer.l
	make clean
	make aql_parser
	make run

aql_parser: ast.c  show_tree.c
	bison -d parser.y -Wcounterexamples
	flex tokenizer.l
	gcc -g -o $@ parser.tab.c lex.yy.c $^

run:
	./aql_parser

clean:
	rm -f aql_parser lex.yy.c parser.tab.c parser.tab.h


flex:
	 flex tokenizer.l

bison:
	bison -d parser.y


