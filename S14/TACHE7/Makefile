#############################################################################
# Fichier Makefile 
# UE MAP401 - DLST - UGA - 2020/2021
#############################################################################
# utilisation des variables internes $@ $< $^ $*
# $@ : correspond au nom de la cible
# $< : correspond au nom de la premiere dependance
# $^ : correspond � toutes les d�pendances
# $* : correspond au nom du fichier sans extension 
#       (dans les regles generiques uniquement)
#############################################################################
# information sur la regle executee avec la commande @echo
# (une commande commancant par @ n'est pas affichee a l'ecran)
#############################################################################


#############################################################################
# definition des variables locales
#############################################################################

# compilateur C
CC = clang

# chemin d'acces aux librairies (interfaces)
INCDIR = .

# chemin d'acces aux librairies (binaires)
LIBDIR = .

# options pour l'�dition des liens
LDOPTS = -L$(LIBDIR) -lm

# options pour la recherche des fichiers .o et .h
INCLUDEOPTS = -I$(INCDIR)

# options de compilation
COMPILOPTS = -g -Wall $(INCLUDEOPTS)

# liste des executables
EXECUTABLES = eps_bezier2 eps_bezier3 test_courbe


#############################################################################
# definition des regles
#############################################################################

########################################################
# la r�gle par d�faut
all : $(EXECUTABLES)

########################################################
# regle generique : 
#  remplace les regles de compilation separee de la forme
#	module.o : module.c module.h
#		$(CC) -c $(COMPILOPTS) module.c
%.o : %.c %.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module "$*
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

########################################################
# regles explicites de compilation separee de modules
# n'ayant pas de fichier .h ET/OU dependant d'autres modules

image.o : image.c image.h types_macros.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module image"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

contour_calcul.o : contour_calcul.c contour_calcul.h image.h geometrie_2d.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module contour_calcul"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

contours_detection.o : contours_detection.c contours_detection.h contour_calcul.h image.h geometrie_2d.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module contours_detection"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

contours_bezier2.o : contours_bezier2.c contours_bezier2.h contour_calcul.h image.h geometrie_2d.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module contours_bezier2"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

eps_bezier2.o: eps_bezier2.c contours_bezier2.h contours_detection.h contour_calcul.h image.h geometrie_2d.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module eps_bezier2"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

contours_bezier3.o : contours_bezier3.c contours_bezier3.h contours_bezier2.h contour_calcul.h image.h geometrie_2d.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module contours_bezier3"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

eps_bezier3.o: eps_bezier3.c contours_bezier3.h contours_detection.h contour_calcul.h image.h geometrie_2d.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module eps_bezier3"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

test_courbe.o: test_courbe.c contours_bezier3.h contours_detection.h contour_calcul.h image.h geometrie_2d.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_courbe"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

		
########################################################
# regles explicites de creation des executables

eps_bezier2 : eps_bezier2.o contours_bezier2.o contours_detection.o contour_calcul.o image.o geometrie_2d.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

eps_bezier3 : eps_bezier3.o contours_bezier3.o contours_bezier2.o contours_detection.o contour_calcul.o image.o geometrie_2d.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

test_courbe: test_courbe.o contours_bezier3.o contours_bezier2.o contours_detection.o contour_calcul.o image.o geometrie_2d.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

# regle pour "nettoyer" le r�pertoire
clean:
	rm -fR $(EXECUTABLES) *.o 
