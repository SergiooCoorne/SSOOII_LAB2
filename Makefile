# Makefile para el programa SSOOIIGLE

# Compilador
CXX = g++
# Opciones del compilador
CXXFLAGS = -std=c++11 -Wall -Wextra

# Directorio de código fuente
SRCDIR = src
# Directorio de objetos
OBJDIR = obj
# Directorio ejecutable
EXECUTABLEDIR = exec
# Directorio de los libros
TESTDIR = Libros

# Archivos .cpp
SRCS := $(wildcard $(SRCDIR)/*.cpp)
# Archivos objeto
OBJS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))
# Nombre del ejecutable que se va a ejecutar como principal
TARGET = $(EXECUTABLEDIR)/SSOOIIGLE

# Regla para enlazar los archivos objeto y crear el ejecutable
$(TARGET): $(OBJS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Regla para compilar los archivos fuente en archivos objeto
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@
	$(CXX) -MM -MT $@ -MF $(@:.o=.d) $(CXXFLAGS) $<

# Regla para limpiar el directorio

clean:
	rm -rf $(OBJDIR)/* $(EXECUTABLEDIR)/*

# Regla para crear los directorios

directories:
	@mkdir -p $(OBJDIR) $(EXECUTABLEDIR)

# Regla para compilar

all: directories $(TARGET)

# Incluir archivos de dependencia 
-include $(OBJDIR)/*.d

# Reglas para ejecutar el programa con todos los libros
Libro1: $(TARGET)
	@./$(TARGET) $(TESTDIR)/17_LEYES_DEL_TRABAJO_EN_EQUIPO.txt la 10

Libro2: $(TARGET)
	@./$(TARGET) $(TESTDIR)/21_LEYES_DE_LIDERAZGO_-_JOHN_C._MAXWELL.txt la 10
	
Libro3: $(TARGET)
	@./$(TARGET) $(TESTDIR)/25_MANERAS_DE_GANARSE_A_LA_GENTE_-_.txt la 10

Libro4: $(TARGET)
	@./$(TARGET) $(TESTDIR)/Abe_Shana_-_La_última_sirena.txt la 10

Libro5: $(TARGET)
	@./$(TARGET) $(TESTDIR)/ACTITUD_DE_VENCEDOR_-_JOHN_C._MAXWELL.txt la 10

Libro6: $(TARGET)
	@./$(TARGET) $(TESTDIR)/El_Oro_Y_La_Ceniza_-_Abecassis_Eliette.txt la 10

Libro7: $(TARGET)
	@./$(TARGET) $(TESTDIR)/SEAMOS_PERSONAS_DE_INFLUENCIA_-_JOHN_MAXWELL.txt la 10

Libro8: $(TARGET)
	@./$(TARGET) $(TESTDIR)/VIVE_TU_SUEÑO_-_JOHN_MAXWELL.txt la 10
