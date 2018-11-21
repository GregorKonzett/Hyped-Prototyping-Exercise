#include "sender.hpp"
#include "utils/system.hpp"
#include <iostream>
#include <unistd.h>
#include <pthread.h>

using hyped::Sender;
using hyped::utils::System;

//Sender* sender;

void *createThread(void* id) {
	Sender* sender = new Sender();
	//sender->sendData(0x10,0xFF);

	
	uint8_t data;

	std::cin >> data;	
	sender->sendData(0x10,data);
	std::cout << "Data sent 0x10 " << data << std::endl;
	usleep(200000);
	sender->readData(0x10);
}

int main(int argc, char* argv[])
{
  System::parseArgs(argc, argv);
  System& sys = System::getSystem();
  //sender = new Sender();
  //sender->sendData(0x10,0xFF);
  //std::cout << "Data sent 0x10 0xFF" << std::endl;  
//usleep(2000000);  
	pthread_t thread;

	int rc = pthread_create(&thread,NULL,createThread,(void *)1);

	if(rc) {
		std:: cout << "Error creating Thread" << std::endl;
		exit(-1);
	}

	while(true);
}
