/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Customer.h
 * Author: passe
 *
 * Created on 03. Oktober 2018, 18:22
 */

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "Display.h"

class Customer {
public:
    Customer(int ticketNr, Display *display);
    virtual ~Customer();
    
    void waitForCounter();
    
    int getTicketNr();
private:
    Display *display;
    int ticketNr;
    
    void signalForDisplay();
    void waitForNumber();

};

#endif /* CUSTOMER_H */

