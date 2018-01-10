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
 * File:   Plan.cpp
 * Author: buele
 * 
 * Created on December 3, 2017, 10:56 PM
 */

#include <iostream>
#include <vector>
class State;
#include "Action.h"
#include "State.h"
#include "Edge.h"
#include "World.h"

#include "Plan.h"

using namespace std;
Plan::Plan() {
    this->actions = std::vector<Action *>();
    this->finish = nullptr;
    this->start = nullptr;
    this->links = std::vector<Edge *>();
    this->open_preconditions = std::vector<State *>();
    
}

Plan::Plan(const Plan& orig) {
}

Plan::~Plan() {
    this->links.clear();    
    this->actions.clear();
          
}

void Plan::PrintNodes(Action * node){
    
    
    if(node->name == "FINISH"){
        node->Print();
        cout << endl;
    }
    
        
    
    // find edges with node as source
    std::vector<Edge *> node_edges = std::vector<Edge *>();
    for(Edge* edge : this->links){
        if(node == edge->source){
            node_edges.push_back(edge);
        }
    }
        
    for(Edge* edge: node_edges){
        node->Print();
        cout << " -> ";
        this->PrintNodes(edge->destination);
    }
}




void Plan::PrintPlan() {
    cout << "PRINT PLAN: " << endl;
    this->PrintNodes(this->start);
    this->finish->Print();
    cout << endl;
}

std::vector<Edge*> Plan::GetEdgeByDestination(Action* destination) {
    std::vector<Edge *> list = std::vector<Edge *>();
    for(Edge* edge : this->links){
        if(destination == edge->destination){
            list.push_back(edge);
        }
    }
    
    return list;
}

std::vector<Edge*> Plan::GetEdgeBySource(Action* source) {
    std::vector<Edge *> list = std::vector<Edge *>();
    for(Edge* edge : this->links){
        if(source == edge->destination){
            list.push_back(edge);
        }
    }
    
    return list;
}




