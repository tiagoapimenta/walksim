#
# Author: Tiago Augusto Pimenta <tiagoapimenta@gmail.com>
#

TARGET  = walksim

SOURCES = walksim.cpp environment.cpp ragdoll.cpp controller.cpp renderer.cpp \
          simulator.cpp sys/physics.cpp sys/graphics.cpp sys/microtime.cpp

OBJS    = $(SOURCES:.cpp=.o)

CFLAGS  = -O3 `pkg-config --cflags gl glu ode`
LDFLAGS =

LIBS    = `pkg-config --libs gl glu ode` -lglut

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $@ $(LIBS)

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

clean:
	@rm $(TARGET) $(OBJS)
