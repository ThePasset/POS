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

#include <cstdlib>
#include <iostream>
#include <thread>
#include <condition_variable>

#define COUNTERS 1

using namespace std;
class Display;
class Customer;
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

Counter::Counter(int num, Display *display) {
    this->num = num;
    this->display = display;
}

Counter::~Counter() {
}

void Counter::servCustomer(Customer* customer){
    this_thread::sleep_for(5s);
    cout << "Counter" << num << "finished one Customer" << endl;
    ready();
}

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

Display::Display() {
    this->ticketNr = 0;
    this->blank = true;
}

Display::~Display() {
}

void Display::waitForResponse(){
    while(blank){
        std::unique_lock<std::mutex> lk(this->lock);
        this->response.wait(lk);
    }
}

void Display::setFreeCounter(Counter *counter){
    lock.lock();
    waitForResponse();
    blank = true;
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

void Counter::ready(){
    display->setFreeCounter(this);
}

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

void Customer::waitForNumber(){
    while(display->getTicketNr() != ticketNr){
        std::unique_lock<std::mutex> lk(display->lock);
        display->freeCounter.wait(lk);
    }
}

void Customer::waitForCounter(){
    display->lock.lock();
    waitForNumber();
    signalForDisplay();
    Counter *counter = display->getCounter();
    display->lock.unlock();
}

int Customer::getTicketNr(){
    return ticketNr;
}

void createCustomer(Display *display){
    cout << "Creating Customers..." << endl;
    int n{1};
    while(n){
        Customer *customer = new Customer(n, display);
        cout << "Created Customer with Number: " << n << "\n" << endl;
        n++;
        thread th(&Customer::waitForCounter, customer);
        th.detach();
        this_thread::sleep_for(1s);
    }
}

void createCounter(Display *display){
    cout << "Creating Counters..." << endl;
    for (int i{0}; i < COUNTERS; i++){
        Counter *counter = new Counter(i, display);
        thread th(&Counter::ready, counter);
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
    
    this_thread::sleep_for(1min);
    return 0;
}

