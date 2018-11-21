CC=g++
CFLAGS=-pthread

prototype: utils/io/can.o data.o main.o receiver.o utils/concurrent/lock.o utils/concurrent/thread.o utils/system.o utils/concurrent/barrier.o utils/logger.o utils/concurrent/condition_variable.o
	$(CC) $(CFLAGS) -o prototype main.o receiver.o data.o utils/io/can.o utils/concurrent/lock.o utils/concurrent/thread.o utils/system.o utils/concurrent/barrier.o utils/logger.o utils/concurrent/condition_variable.o

