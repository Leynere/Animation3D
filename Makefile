#
# Les variables d'environnement libG2X, incG2X
# sont definies dans le fichier ~/.bashrc par le script ../install.sh
#
#compilateur
CC = gcc

#compil en mode 'debug' ou optmis�e (-O2)
DBG = no

ifeq ($(DBG),yes) #en mode debug
  CFLAGS = -g -Wpointer-arith -Wall -ansi
else               #en mode normal
  CFLAGS = -O2 -ansi
endif

# assemblage des infos de lib. et inc.
lib =   $(libG2X)
# fichiers *.c locaux
src = src/
# fichiers *.h locaux et lib.
inc = -I./include $(incG2X) 

projet : circle.o draw.o anim.o init.o projet.o
	@echo "assemblage [$^]->$@"
	@$(CC) $^ $(lib) -o $@
	@echo "------------------------"

exo1 : circle.o draw.o anim.o init.o exo1.o
	@echo "assemblage [$^]->$@"
	@$(CC) $^ $(lib) -o $@
	@echo "------------------------"

democercles : circle.o democercles.o
	@echo "assemblage [$^]->$@"
	@$(CC) $^ $(lib) -o $@
	@echo "------------------------"

# r�gle g�n�rique de cr�ation de xxx.o � partir de src/xxx.c
%.o : $(src)%.c
	@echo "module $@"
	@$(CC) $(CFLAGS) $(inc) -c $< -o $@
	@echo "------------------------"

# r�gle g�n�rique de cr�ation de l'executable xxx � partir de src/xxx.c (1 seul module)
% : circle.o %.o
	@echo "assemblage [$^]->$@"
	@$(CC) $^ $(lib) -o $@
	@echo "------------------------"
	
.PHONY : clean cleanall ?

# informations sur les param�tres de compilation       
? :
	@echo "---------compilation informations----------"
	@echo "  processor      : $(PROCBIT)"
	@echo "  compiler       : $(CC)"
	@echo "  options        : $(CFLAGS)"
	@echo "  lib g2x/OpenGl : $(libG2X)$(COMP)"
	@echo "  headers        : $(incG2X)"
clean : 
	@rm -f *.o
cleanall :
	@rm -f *.o $(exec)
	
