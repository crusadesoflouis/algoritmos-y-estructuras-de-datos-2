CXXFLAGS = -g -Wall -Wno-reorder #ojo -wno -reorder le quita algo respecto al orden 

SOURCES = testsModulos.cpp
HEADERS = DiccString.h DiccAbb.h Cola.h DiccMatriz.hpp
OBJS = $(SOURCES:.cpp=.o)

LIBS =

TARGET = tests

$(TARGET): $(OBJS) $(HEADERS)  
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all: $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

valgrind: all
	valgrind --leak-check=full ./$(TARGET)
