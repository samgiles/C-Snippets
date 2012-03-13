CC       := gcc
CFLAGS   := -g
INCLUDES := -I
LIBS     :=
OBJECTS  := MemoryManager.c
MMNAME   := mm


mm: 
	@echo "Building MemoryManager"
	$(CC) $(CFLAGS) -o $(MMNAME) $(OBJECTS) $(LIBS)

clean: 
	rm -r $(MMNAME)
