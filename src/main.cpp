/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: buele
 *
 * Created on December 3, 2017, 10:48 PM
 */

#include <cstdlib>
#include <iostream>
#include <vector>
class State;
#include "Action.h"
#include "State.h"
#include "BlocksWorldExample.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    BlocksWorldExample example = BlocksWorldExample();
    example.run();
    
    return 0;
}

