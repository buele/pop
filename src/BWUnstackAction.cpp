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
 * File:   BWUnstackAction.cpp
 * Author: buele
 * 
 * Created on December 4, 2017, 11:57 PM
 */

#include <string>
#include <vector>
class State;
#include "Action.h"
#include "State.h"
#include "BWUnstackAction.h"
#include "BWClearState.h"
#include "BWTableState.h"
#include "BWOnState.h"


std::vector<State *> BWUnstackAction::generatePreconditions(){
    // clear(x)
    std::vector<std::string> clear_x_params = std::vector<std::string>();
    clear_x_params.push_back("x");
    BWClearState * clear_x = new BWClearState(true, this, clear_x_params);
    // on(x,y)
    std::vector<std::string> on_x_y_params = std::vector<std::string>();
    on_x_y_params.push_back("x");
    on_x_y_params.push_back("y");
    BWOnState * on_x_y = new BWOnState(true, this, on_x_y_params);
    
    // return preconditions
    std::vector<State*> preconditions = std::vector<State*>();
    preconditions.push_back(clear_x);
    preconditions.push_back(on_x_y);
    return preconditions;
    
}

std::vector<State*> BWUnstackAction::generateEffects() {
    // clear(y)
    std::vector<std::string> clear_y_params = std::vector<std::string>();
    clear_y_params.push_back("y");
    BWClearState * clear_y = new BWClearState(true, this, clear_y_params);
    // table (x)
    std::vector<std::string> table_x_params = std::vector<std::string>();
    table_x_params.push_back("x");
    BWTableState * table_x = new BWTableState(true, this, table_x_params);    
    // ! on(x,y)
    std::vector<std::string> not_on_x_y_params = std::vector<std::string>();
    not_on_x_y_params.push_back("x");
    not_on_x_y_params.push_back("y");
    BWOnState * not_on_x_y = new BWOnState(false, this, not_on_x_y_params);
    
    // return effects
    std::vector<State *> effects = std::vector<State*>();
    effects.push_back(clear_y);
    effects.push_back(table_x);
    effects.push_back(not_on_x_y);
    return effects;
}


BWUnstackAction::BWUnstackAction() {
    this->name = "UNSTACK";
     // define parameters
    this->parameters.push_back("x");
    this->parameters.push_back("y");
    // preconditions    
    this->preconditions = this->generatePreconditions();
    // effects
    this->effects = this->generateEffects();
}

BWUnstackAction::BWUnstackAction(const BWUnstackAction& orig) {
}

BWUnstackAction::~BWUnstackAction() {
    this->preconditions.clear();
    this->effects.clear();
}

