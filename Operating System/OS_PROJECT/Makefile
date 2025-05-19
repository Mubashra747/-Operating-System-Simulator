CC = g++
CFLAGS = -Wall -pthread
TASKS = calculator notepad clock calendar file_create file_delete file_copy file_info file_move task_manager music_player number_guessing print_file instruction_guide dice_roller

all: main $(TASKS)

main: main.cpp
	$(CC) $(CFLAGS) -o main main.cpp

$(TASKS): %: %.cpp
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f main $(TASKS)
