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
 * File:   World.cpp
 * Author: buele
 * 
 * Created on December 3, 2017, 10:55 PM
 */

/*
void SetItems(Item *items);
    void SetMetaActions(MetaAction * meta_actions);
    void SetStates(State * states);
    void SetMetaItems(Item * meta_items);
 * */

#include <string>
#include <vector>
class State;
#include "Action.h"
#include "State.h"
#include "World.h"

World::World() {
    this->start = nullptr;
    this->finish = nullptr;
    
}

World::World(  std::vector<std::string> items, 
            std::vector<Action *> actions, 
            Action * start, 
            Action * finish){
    
    this->items = items;
    this->actions = actions;
    this->start = start;
    this->finish = finish;
    
}

World::World(const World& orig) {
}

World::~World() {
}




