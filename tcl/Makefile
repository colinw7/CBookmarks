CDEBUG = -g
LDEBUG = -g

PROG = CTclBookmarks

CPP_SRC = \
CTclBookmarks.cpp

TCL_FILES = \
CTclBookmarks.tcl

EXTRA_CFLAGS = \
-I$(INC_DIR)/CTclApp \
-I$(INC_DIR)/CBookmarksLib \
-I$(INC_DIR)/CHtml \
-I$(INC_DIR)/CXML \
-I$(INC_DIR)/CUrl \
-I$(INC_DIR)/CFile \
-I$(INC_DIR)/CFileType \
-I$(INC_DIR)/CStrUtil \
-I$(INC_DIR)/CAutoPtr \
-I$(INC_DIR)/CStrNCase \
-I$(INC_DIR)/COptVal \

LIBS = \
-lCTclApp -lCBookmarksLib -lCHtml \
-lCGlob -lCFile -lCOSFile -lCStrUtil -lCUtil \
-lCPrintF -lCReadLine -lCHistory -lreadline -lcurses \
-lCUrl -lCRegExp -lCGlob -lCOSUser -lCOSTime -lCEnv -lCStrNCase -lCPrintF \
-lCStrNCase -ltix -ltk -ltcl -lpthread -ltre \
-lXft -lXt -lX11 -lXext -lXss -lfontconfig -ldl -lm -lc

include $(MAKE_DIR)/bin.mk
