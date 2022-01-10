#.SILENT:

CC = g++
AR = ar
RM = rm

CDEBUG = -g
LDEBUG = -g

INC_DIR = ../include
OBJ_DIR = ../obj
LIB_DIR = ../lib
BIN_DIR = ../bin

all: dirs $(BIN_DIR)/CBookmarks

dirs:
	@if [ ! -e ../obj ]; then mkdir ../obj; fi
	@if [ ! -e ../lib ]; then mkdir ../lib; fi
	@if [ ! -e ../bin ]; then mkdir ../bin; fi

clean:
	$(RM) -f $(OBJ_DIR)/*.o
	$(RM) -f $(BIN_DIR)/CBookmarks

SRC = \
CBookmarks.cpp \

OBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRC))

CPPFLAGS = \
-std=c++14 \
-I. \
-I$(INC_DIR) \
-I../../CHtml/include \
-I../../CFile/include \
-I../../COS/include \
-I../../CStrUtil/include \
-I../../CGlob/include \
-I../../CUtil/include \

LFLAGS = \
-L$(LIB_DIR) \
-L../../CBookmarks/lib \
-L../../CHtml/lib \
-L../../CFile/lib \
-L../../CRegExp/lib \
-L../../COS/lib \
-L../../CStrUtil/lib \
-L../../CGlob/lib \
-L../../CUtil/lib \

LIBS = \
-lCBookmarks -lCHtml -lCFile -lCOS -lCRegExp -lCStrUtil -lCGlob -lCUtil \
-ltre -lncurses

.SUFFIXES: .cpp

$(OBJS): $(OBJ_DIR)/%.o: %.cpp
	$(CC) $(CDEBUG) -c $< -o $(OBJ_DIR)/$*.o $(CPPFLAGS)

$(BIN_DIR)/CBookmarks: $(OBJS)
	$(CC) $(LDEBUG) -o $(BIN_DIR)/CBookmarks $(OBJS) $(LFLAGS) $(LIBS)
