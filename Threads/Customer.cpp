/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Customer.cpp
 * Author: passe
 * 
 * Created on 03. Oktober 2018, 18:22
 */

#include "Customer.h"

Customer::Customer(int ticketNr, Display *display) {
    this->ticketNr = ticketNr;
    this->display = display;
}

Customer::~Customer() {
}

void Customer::signalForDisplay(){
    display->blank = true;
    display->response.notify_all();
    
}

void Customer::waitForCounter(){
    display->lock.lock();
    waitForNumber();
    signalForDisplay();
    
    Counter *counter = display->getCounter();
    
    display->lock.unlock();
}

void Customer::waitForNumber(){
    while(display->getTicketNr() != ticketNr){
        std::unique_lock<std::mutex> lk(display->lock);
        display->freeCounter.wait(lk, []{return 1;});
    }
}


int Customer::getTicketNr(){
    return ticketNr;
}