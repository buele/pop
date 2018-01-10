/*
 * The MIT License
 *
 * Copyright 2017 buele.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/* 
 * File:   Action.cpp
 * Author: buele
 * 
 * Created on December 3, 2017, 11:27 PM
 */
#include <vector>
#include <string>
#include <iostream>
class State;
#include "Action.h"
#include "State.h"

using namespace std;
Action::Action() {
    this->name = "";   
    this->effects = std::vector<State*>();
    this->preconditions = std::vector<State*>();
    this->parameters = std::vector<std::string>();

    
}
Action::Action(Action * action){
    // copy name    
    this->name = action->name;
    this->parameters = action->parameters;
    // precondition
    for(State * precondition : action->preconditions){
        State * new_precondition = new State(precondition);
        new_precondition->owner = this;
        this->preconditions.push_back(new_precondition);
    }
    
    // effects
    for(State * effect : action->effects){
        State * new_effect = new State(effect);
        new_effect->owner = this;
        this->effects.push_back(new_effect);
    }
    
    
    
}


Action::Action(const Action& orig) {
}

Action::~Action() {
    this->effects.clear();
    this->preconditions.clear();

}

void Action::Print(){
    cout << this->name << "(" ;
    for(int i = 0; i < this->parameters.size(); i++ ){
        cout << this->parameters[i] ;
        if(i < (this->parameters.size() -1 )){
            cout << ",";
        }
    }
    cout << ")";
}




