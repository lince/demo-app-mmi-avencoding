CC=g++

SOURCES= 	src/Arm.cpp \
			src/Body.cpp \
			src/GLPiece.cpp \
			src/Head.cpp \
			src/Puppet.cpp \
			src/Leg.cpp \
			src/Utils.cpp \
			src/SimpleScenario.cpp \
			src/Camera.cpp \
			src/EventHandler.cpp \
			src/Color.cpp \
			src/StateCircularQuee.cpp
			
INCLUDES=	include/Arm.h \
			include/Body.h \
			include/GLPiece.h \
			include/Head.h \
			include/Puppet.h \
			include/Leg.h \
			include/SimpleScenario.h \
			include/Camera.h \
			include/EventHandler.h \
			include/Color.h \
			include/Utils.h \
			include/StateCircularQuee.h
			
LIBS= -lglut -lGL -lGLU -lmmi -lmmiwii -lcpputil -lstreaming

PROGRAMS= demoRTP demoWooza

DEBUG= demoRTP_Debug demoWooza_Debug demoHoldOn_Debug

ALL: $(PROGRAMS) $(DEBUG)
		
demoRTP: $(SOURCES) $(INCLUDES) demoRTP.cpp
	$(CC) $(SOURCES) demoRTP.cpp $(INCLUDES) $(LIBS) -o demoRTP
	
demoWooza: $(SOURCES) $(INCLUDES) demoWooza.cpp
	$(CC) $(SOURCES) demoWooza.cpp $(INCLUDES) $(LIBS) -o demoWooza
	
demoRTP_Debug: $(SOURCES) $(INCLUDES) demoRTP.cpp
	$(CC) $(SOURCES) demoRTP.cpp $(INCLUDES) $(LIBS) -o demoRTP_Debug
	
demoWooza_Debug: $(SOURCES) $(INCLUDES) demoWooza.cpp
	$(CC) $(SOURCES) demoWooza.cpp $(INCLUDES) $(LIBS) -o demoWooza_Debug
	
demoHoldOn_Debug: $(SOURCES) $(INCLUDES) demoHoldOn.cpp
	$(CC) $(SOURCES) demoHoldOn.cpp $(INCLUDES) $(LIBS) -o demoHoldOn_Debug
	
clean:
	rm -f $(PROGRAMS) $(DEBUG)
	
#dgb debug
#
