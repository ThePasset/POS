/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Display.h
 * Author: passe
 *
 * Created on 03. Oktober 2018, 17:59
 */

#ifndef DISPLAY_H
#define DISPLAY_H

#include "Counter.h"

#include <thread>
#include <condition_variable>

class Display {
public:
    bool blank;
    
    std::condition_variable freeCounter;
    std::condition_variable response;
    std::mutex lock;
    
    Display();
    virtual ~Display();
    
    void setFreeCounter(Counter *counter);
    Counter* getCounter();
    int getTicketNr();
    
private:
    Counter *counter;
    int ticketNr;
    
    void waitForResponse();
};

#endif /* DISPLAY_H */

