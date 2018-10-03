/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Counter.cpp
 * Author: passe
 * 
 * Created on 03. Oktober 2018, 18:30
 */

#include "Counter.h"

#include <thread>
#include <cstdlib>

Counter::Counter(int num, Display *display) {
    this->num = num;
    this->display = display;
}

Counter::~Counter() {
}

void Counter::ready(){
    display->setFreeCounter(this);
}

void Counter::servCustomer(Customer* customer){
    //this_thread::sleep_for(5s);
}

