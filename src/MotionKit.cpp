//============================================================================
// Name        : MotionKit.cpp
// Author      : Bill Snook
// Version     : 0.1
// Created on  : Nov 14, 2014
// Copyright   :
// Description : Base for MotionKit
//============================================================================

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "MotionKit.hpp"
//#include "mkInterrupts.hpp"
#include "mkInterface.hpp"
#include "mkTime.hpp"

//#include "mraa.hpp"


int defaultPin = 13;
int running = 0;

void sig_handler(int signo) {
    if (signo == SIGINT) {
        printf("\nClosing IO nicely\n");
        running = -1;
    }
}


int main (int argc, char **argv) {

	if (argc < 2) {
		fprintf(stdout, "\nProvide an int arg if you want to flash an LED on some other IO port than IO %d\n", defaultPin);
    } else {
    	defaultPin = strtol(argv[1], NULL, 10);
    }

    signal(SIGINT, sig_handler);

    double targetTime = 1.0;

    mkInterface ifObj;
//    ifObj.setupGPIO( defaultPin );
    ifObj.setupADC( 0 );

	fprintf(stdout, "\nMotionKit Version %.02f\n", 0.11);

    mkTime timeObj;
    timeObj.startElapsedTime();

    while (running == 0) {
    	if ( timeObj.getElapsedTime() > targetTime ) {
    		timeObj.startElapsedTime();
//    		targetTime += 0.5;
//    		if (targetTime > 10.0 ) {
//        		targetTime = 0.5;
//    		}

//            ifObj.togglePin();
            int pinValue = ifObj.readPin();
        	fprintf(stdout, "ADC A0 read %X - %d\n", pinValue, pinValue);

    	}
    }
    return 0;
}

