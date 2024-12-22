NAME = M1
FLAG = LEO

COMP:
	clear; g++ -Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self -Wswitch-default -Wfloat-equal -Wshadow -Wpointer-arith -Wtype-limits -Wempty-body -Wlogical-op -Wmissing-field-initializers -Wctor-dtor-privacy -Wnon-virtual-dtor -Wstrict-null-sentinel -Wold-style-cast -Woverloaded-virtual -Wsign-promo -std=gnu++11 -g -lm ${NAME}.cpp -o ${NAME} -D${FLAG}

comp: 
	clear; g++ ${NAME}.cpp -o ${NAME} -D${FLAG}
	
	
run: 
	./${NAME}
vrun: 
	valgrind ./${NAME}

gdb:
	gdb ./${NAME}
clean:
	rm ${NAME} || clear
	clear
