#Directories
IDIR = ./include
SDIR = ./src
ODIR = ./obj

#FILE = func
HEAD = header
#TESTFILE = test

#Echo color print pattern
red=`tput smso; tput bold; tput setaf 1`
green=`tput smso; tput bold; tput setaf 2`
reset=`tput sgr0`
dim=`tput smso; tput dim`

#Compiler
#CC=g++
CC=gcc
EXT=c
EXE=leitor-exibidor

CFLAGS= -I$(IDIR) -std=c99

FILE?=default_value_if_not_set_in_environment
SYS?=default_value_if_not_set_in_environment

_DEPS = $(HEAD).h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o func.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.$(EXT) $(DEPS)
	@ $(CC) -c -o $@ $< $(CFLAGS)

compile: $(OBJ)
	@if [ $(SYS) = "WINDOWS" ]; then\
        $(CC) -o $(EXE).out $^ $(CFLAGS) -lws2_32;\
	else \
        $(CC) -o $(EXE).out $^ $(CFLAGS);\
    fi
	@ echo ${dim}Objetos Gerados${reset}

exec: $(OBJ)
	@ make compile -s;
	@ ./$(EXE).out

arquivo: $(OBJ)
	@ make clean --no-print-directory;
	@ make compile --no-print-directory; 
	@ ./$(EXE).out > saida.txt
	@ echo ${green}Escrito em saida.txt${reset}

#Escrever o .class em saida, tb para controle
#Utilizavel na versão final do prog
binary:
	@ xxd assets/$(FILE).class > saida.txt
	@ echo ${green}Bytecodes escritos em saida.txt${reset}

#Utilizado para controle, prog ainda não passou neste teste
#Nao utilizavel na versao final do prog
diff:
	@- diff -y saida.txt esperado.txt

clean:
	@ rm -f $(ODIR)/*.o; rm -f ./$(EXE).out;
	@ rm -f saida.txt;
	@ echo ${red}Arquivos limpos!${reset}