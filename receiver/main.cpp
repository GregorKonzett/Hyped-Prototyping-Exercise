#include "receiver.hpp"
#include "utils/system.hpp"
#include <iostream>
#include <pthread.h>

using hyped::Receiver;
using hyped::utils::System;

//Receiver* receiver;

void *createReceiver(void *id) {
	Receiver* receiver = new Receiver();
}

int main(int argc, char* argv[])
{
  System::parseArgs(argc, argv);
  System& sys = System::getSystem();
  pthread_t thread;

  int rc = pthread_create(&thread,NULL,createReceiver,(void *)1);

  if (rc) {
	  std::cout << "Error in creating thread " << rc;
	exit(-1);
  }

  while(true);

}
