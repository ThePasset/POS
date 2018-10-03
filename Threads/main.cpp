/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: passe
 *
 * Created on 03. Oktober 2018, 15:42
 */
#include "Display.h"
#include "Customer.h"
#include "Counter.h"

#include <cstdlib>
#include <iostream>
#include <thread>

#define COUNTERS 4

using namespace std;

void createCustomer(Display *display){
    cout << "Create Customer" << endl;
    int n{1};
    while(!n){
        Customer *customer = new Customer(n, display);
        thread th(&Customer::waitForCounter, customer);
        th.detach();
        this_thread::sleep_for(1s);
    }
}

void createCounter(Display *display){
    cout << "Create Counter" << endl;
    for (int i{0}; i < COUNTERS; i++){
        Counter *counter = new Counter(i, display);
        thread th(&Counter::ready(), counter);
        th.detach();
    }
}

/*
 * 
 */
int main(int argc, char** argv) {
    cout << "Programm started..." << endl;
    
    Display *display = new Display();
    
    thread createCustomer_Thread{createCustomer, display};
    thread createCounter_Thread{createCounter, display};
    createCustomer_Thread.join();
    createCounter_Thread.join();
    
    this_thread::sleep_for(1min);
    return 0;
}

