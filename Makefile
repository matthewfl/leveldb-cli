TARGET=level-cli

SOURCE= main.cc

OBJS= $(SOURCE:.cc=.o)

LD=g++
CXX=g++

$(TARGET): $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) -lleveldb
