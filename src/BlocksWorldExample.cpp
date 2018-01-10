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
 * File:   BlocksWorldExample.cpp
 * Author: buele
 * 
 * Created on December 3, 2017, 11:01 PM
 */

#include <string>
#include <vector>
#include <stack>
#include <set>
class State;
#include "Action.h"
#include "State.h"
#include "Edge.h"
#include "World.h"

#include "Plan.h"
#include "Pop.h"
#include "BlocksWorldExample.h"
#include "BWUnstackAction.h"
#include "BWStackAction.h"
#include "BWClearState.h"
#include "BWTableState.h"
#include "BWOnState.h"
#include <iostream>

using namespace std;

BlocksWorldExample::BlocksWorldExample() {
}

BlocksWorldExample::BlocksWorldExample(const BlocksWorldExample& orig) {
}

BlocksWorldExample::~BlocksWorldExample() {
}

std::vector<State*> BlocksWorldExample::generateFinishPreconditions(Action * finish) {
    
    // on(A,B)
    
    std::vector<std::string> on_a_b_params = std::vector<std::string>();
    on_a_b_params.push_back("A");
    on_a_b_params.push_back("B");
    BWOnState * on_a_b = new BWOnState(true, finish, on_a_b_params);
    
    // on(B,C)
    std::vector<std::string> on_b_c_params = std::vector<std::string>();
    on_b_c_params.push_back("B");
    on_b_c_params.push_back("C");
    BWOnState * on_b_c = new BWOnState(true, finish, on_b_c_params);
    
    std::vector<State *> preconditions = std::vector<State *>();
    preconditions.push_back(on_a_b);
    preconditions.push_back(on_b_c);
    
    return preconditions;
    
}

std::vector<State*> BlocksWorldExample::generateStartEffects(Action * start) {

    // on(C,A)
    std::vector<std::string> on_c_a_params = std::vector<std::string>();
    on_c_a_params.push_back("C");
    on_c_a_params.push_back("A");
    BWOnState * on_c_a = new BWOnState(true, start, on_c_a_params);
    
    // clear(C)
    std::vector<std::string> clear_c_params = std::vector<std::string>();
    clear_c_params.push_back("C");
    BWClearState * clear_c = new BWClearState(true, start, clear_c_params);
    
    // clear(B)
    std::vector<std::string> clear_b_params = std::vector<std::string>();
    clear_b_params.push_back("B");
    BWClearState * clear_b = new BWClearState(true, start, clear_b_params);
    
    // table(A)
    std::vector<std::string> table_a_params = std::vector<std::string>();
    table_a_params.push_back("A");
    BWTableState * table_a = new BWTableState(true, start, table_a_params); 
    
    // table(B)
    std::vector<std::string> table_b_params = std::vector<std::string>();
    table_b_params.push_back("B");
    BWTableState * table_b = new BWTableState(true, start, table_b_params); 
    
    std::vector<State *> effects = std::vector<State *>();
    effects.push_back(on_c_a);
    effects.push_back(clear_c);
    effects.push_back(clear_b);
    effects.push_back(table_a);
    effects.push_back(table_b);
    
    return effects;
}

void BlocksWorldExample::run(){
    cout << " *** Artificial Intelligence Fundamentals - UNIPI 2017/2018 ***\n";
    cout << " Partial Order Planning - 4th assignment \n";
    cout << " Raffaele Bua - raffaele.bua@gmail.com \n";
    cout << " Example of Block World \n\n" << endl;
    
    // define world actions
    std::vector<Action*> actions = std::vector<Action *>();
    actions.push_back(new BWStackAction());
    actions.push_back(new BWUnstackAction());
                                                         
    // start
    Action * start = new Action();
    start->name = "START";
    start->effects = this->generateStartEffects(start);
    
    // finish
    Action * finish = new Action();
    finish->name = "FINISH";
    finish->preconditions = this->generateFinishPreconditions(finish);
    
    
    
    std::vector<string> items = std::vector<string>();
    items.push_back("A");
    items.push_back("B");
    items.push_back("C");
    
    // create world
    World * world = new World(items, actions, start, finish);
    
    // create pop
    Pop pop = Pop(world);
    
    // run pop
    pop.Compute();
            
    // print plan
    pop.PrintPlan();
            
    // free memory
    actions.clear();
    delete start;
    delete finish;
    delete world;
    
}