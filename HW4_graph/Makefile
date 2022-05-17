OBJECTS = TripPlanner.cpp
TARGET = TripPlanner.exe
.PHONY: debug clean
all: $(TARGET)
	TripPlanner.exe
%.exe: $(OBJECTS)
	g++ $^ -o TripPlanner.exe
debug: $(OBJECTS)
	g++ $^ -o TripPlanner.exe -D_WYNNE_DEBUG_