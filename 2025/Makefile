all: 01 02 03 05 08

01: src/01.c
	gcc -g -Wall -Werror -o 01.out ./src/01.c

02: src/02.c
	gcc -g -Wall -Werror -o 02.out ./src/02.c

03: src/03.c
	gcc -g -Wall -Werror -o 03.out ./src/03.c

05: src/05.cpp
	clang++ -g -Wall -Werror -o 05.out ./src/05.cpp

08: src/08.cpp
	clang++ -g -Wall -Werror -o 08.out ./src/08.cpp

clean:
	rm -f  01.out
	rm -rf 01.out.dSYM
	rm -f  02.out
	rm -rf 02.out.dSYM
	rm -f  03.out
	rm -rf 03.out.dSYM
	rm -f  05.out
	rm -rf 05.out.dSYM
	rm -f  08.out
	rm -rf 08.out.dSYM