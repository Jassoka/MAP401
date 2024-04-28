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
EXECUTABLES = eps_points eps_segments


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

contours_segments.o : contours_segments.c contours_segments.h contour_calcul.h image.h geometrie_2d.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module contours_segments"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

eps_segments.o: eps_segments.c contours_segments.h contours_detection.h contour_calcul.h image.h geometrie_2d.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module eps_segments"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

		
########################################################
# regles explicites de creation des executables

eps_points : eps_points.o contours_detection.o contour_calcul.o image.o geometrie_2d.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

eps_segments : eps_segments.o contours_segments.o contours_detection.o contour_calcul.o image.o geometrie_2d.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@


# regle pour "nettoyer" le r�pertoire
clean:
	rm -fR $(EXECUTABLES) *.o 
