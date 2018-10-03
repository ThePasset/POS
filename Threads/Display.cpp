/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Display.cpp
 * Author: passe
 * 
 * Created on 03. Oktober 2018, 17:59
 */

#include "Display.h"

Display::Display() {
    this->ticketNr = 0;
    this->blank = true;
}

Display::~Display() {
}

void Display::waitForResponse(){
    while(!blank){
        std::unique_lock<std::mutex> lk(this->lock);
        this->response.wait(lk, [this]{
            return 1;
        });
    }
}

void Display::setFreeCounter(Counter *counter){
    lock.lock();
    waitForResponse();
    blank = false;
    this->counter = counter;
    ticketNr++;
    freeCounter.notify_all();
    lock.unlock();
}

Counter* Display::getCounter(){
    return this->counter;
}

int Display::getTicketNr(){
    return this->ticketNr;
}