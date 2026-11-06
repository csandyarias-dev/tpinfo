################################################################
# AUTHOR INFORMATION #
################################################################

AUTHOR        = "Grupo_Las_Marmotas"
CLASS         = "r1023"
TP            = "Veterinaria"
YEAR          = "2026"

################################################################
# COMPILER AND ARGUMENTS                                       #
################################################################

CC            = gcc
CFLAGS        = -c -Wall -pthread -I.
LDFLAGS       = -Wall -pthread
LIBS          =

################################################################
# SOURCES, HEADERS, OBJECTS AND EXECUTABLE                     #
################################################################

BUILD_DIR     = build
BIN_DIR       = bin
VPATH         = MENU_1 MENU_3 MENU_4 MENU_5 .

SOURCES       = mainPrincipal.c funciones_principal.c m1_desarrollodefunciones.c m1menu.c m3funciones.c m3menu.c m4funciones.c m4menu.c m5funciones.c m5menu.c
OBJS          = mainPrincipal.o funciones_principal.o m1_desarrollodefunciones.o m1menu.o m3funciones.o m3menu.o m4funciones.o m4menu.o m5funciones.o m5menu.o
OBJS_PATHS    = $(addprefix $(BUILD_DIR)/, $(OBJS))

EXEC          = veterinaria

################################################################
# TAR FILE INFORMATION                                         #
################################################################

FILE_NAME   = $(AUTHOR)-$(CLASS)-$(TP)-$(YEAR).tar.gz

################################################################
# MAKE TARGETS                                                 #
################################################################

.PHONY: all clean compress help

all: $(EXEC)

$(EXEC): $(OBJS_PATHS)
	@echo ''
	@echo '*****************************************************'
	@echo '---> $(EXEC)'
	@echo '---> Linking...'
	mkdir -p $(BIN_DIR)
	$(CC) $(OBJS_PATHS) $(LDFLAGS) $(LIBS) -o $(BIN_DIR)/$@
	@echo '---> Linking Complete!'
	@echo '*****************************************************'
	@echo ''

$(BUILD_DIR)/%.o: %.c Makefile
	@echo ''
	@echo '*****************************************************'
	@echo '---> Compiling... $@ '
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@
	@echo '---> Compiling Complete!'
	@echo '*****************************************************'
	@echo ''

clean:
	@echo ''
	@echo '*****************************************************'
	@echo '---> Cleaning...'
	rm -rf $(BUILD_DIR) $(BIN_DIR)
	@echo '---> Cleaning Complete!'
	@echo '*****************************************************'
	@echo ''

compress: clean 
	@echo ''
	@echo '*****************************************************'
	@echo '---> Packing...'
	tar -zcvf $(FILE_NAME) MENU_1 MENU_3 MENU_4 MENU_5 *.c *.h Makefile
	@echo '---> Packing Complete!'
	@echo '*****************************************************'
	@echo ''

help:
	@echo ''
	@echo '*****************************************************'
	@echo '  Uso:'
	@echo '    make all:        Compiles and Links $(EXEC)'
	@echo '    make clean:      Removes objects and executable'
	@echo '    make compress:   Generates .tar.gz file'
	@echo '    make help:       Shows help'
	@echo '*****************************************************'
	@echo ''
