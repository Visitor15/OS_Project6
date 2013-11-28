CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =		OS_Project6.o

LIBS =

TARGET =	OS_Project6

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
