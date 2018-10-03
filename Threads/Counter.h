/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Counter.h
 * Author: passe
 *
 * Created on 03. Oktober 2018, 18:30
 */

#ifndef COUNTER_H
#define COUNTER_H

#include "Display.h"
#include "Customer.h"

class Counter {
public:
    Counter(int num, Display *display);
    virtual ~Counter();
    void ready();
    void servCustomer(Customer *customer);
private:
    int num;
    Display *display;
};

#endif /* COUNTER_H */

