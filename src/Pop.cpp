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
 * File:   Pop.cpp
 * Author: buele
 *
 * Created on December 3, 2017, 10:56 PM
 */

#include <string>
#include <vector>
#include <stack>
#include <map>
#include <iostream>
#include <algorithm>
#include <set>
class State;
#include "Action.h"
#include "State.h"
#include "World.h"
#include "Edge.h"
#include "Plan.h"
#include "Pop.h"


using namespace std;


Pop::Pop(World * world) {
    this->world = world;
    this->plan = Plan();
    this->InitiatePlan();
}

void Pop::PrintState(State* state) {
    cout << ((state->logic_op)?"":"!") << state->name;
        cout << "(";
        for(int param_i = 0;
            param_i < state->parameters.size();
            param_i++){
            cout << state->parameters[param_i];
            if(param_i < (state->parameters.size() - 1))
                cout << ",";
        }
        cout << ")" << endl;
}

void Pop::PrintAction(Action * action,std::vector<std::string>parameters){
    cout  << action->name << "(" ;
    for(int j = 0; j < parameters.size(); j++){
        cout << parameters[j] ;
        if(j < (parameters.size() -1)){
          cout << ",";
        }
    }
    cout << ") ";
}

void Pop::CheckFinishPrecodsWithStartEffects(){
    std::vector<int> preconds_to_remove = std::vector<int>();

    for( int i = 0;  i < this->plan.open_preconditions.size(); i++){
        State * f_precond = this->plan.open_preconditions[i];
        // check state logic operator and name
        cout << "check open precondition:";
        this->PrintState(f_precond);
        for(State * s_effect : this->plan.start->effects){
            if(s_effect->logic_op == f_precond->logic_op &&
               s_effect->name == f_precond->name &&
               s_effect->parameters.size() == f_precond->parameters.size()){
                // check parameters
                for(int i = 0; i < s_effect->parameters.size(); i++){
                    if(s_effect->parameters[i] == f_precond->parameters[i]){
                        // same state: remove the open_precondition
                        preconds_to_remove.push_back(i);
                        cout << "found precondition to remove: " ;
                        this->PrintState(f_precond);
                    }
                }
            }
        }
    }
    cout << "remove precondition resolved by start effects" << endl;
    for (int i : preconds_to_remove){
      this->plan.open_preconditions.erase(this->plan.open_preconditions.begin()+i);
    }
}

bool Pop::FindParameter(std::vector<string> parameters, std::string parameter) {
    for(std::string param : parameters)
        if(param == parameter)
            return true;       
    return false;
}


Action * Pop::FindActionForOpenPrecondition(State * oprec){
    // find an action that effects resolve this precondition
      std::vector<Action *> actions = this->world->actions;
      cout << "explore actions" << endl;
      // explore actions
      for (Action * action : actions)
      {
          cout << "for action with name: " << action->name << endl;
          cout << "explore effects" <<endl;
          // explore effects
          for(State * effect : action->effects){
              cout << "COMPARE PRECONDITION : " ;
              this->PrintState(oprec);
              cout << " WITH effect: " ;
              this->PrintState(effect);
              // compare
              if(oprec->logic_op == effect->logic_op &&
                oprec->name == effect->name){               
                this->PrintState(oprec);
                // print the action
                cout <<"the action: ";
                this->PrintAction(action, oprec->parameters);
                cout << " solves the open precondition ";                              
                this->PrintState(oprec);
                  
                // ADD ACTION
                // clone generic action ---                  
                Action * new_action = new Action(action);                
                // 1. check parameters number
                if(new_action->parameters.size() == oprec->parameters.size()){
                    cout << "PRECONDITION WITH SAME PARAMETERS CASE" << endl;
                    
                    std::vector<std::string> oprec_params = oprec->parameters;
                    std::vector<std::string> new_action_params = new_action->parameters;
                    std::map<std::string, std::string> params_map = std::map<std::string, std::string>();
                    cout << "Mapping " << endl;
                    for(int i = 0; i < oprec->parameters.size(); i++){
                                                
                            cout << "map[" << new_action->parameters[i] << "] :" << oprec->parameters[i] << endl;
                            params_map[new_action->parameters[i]] = oprec->parameters[i];  
                            
                    }
                    
                    // replace with mapping the parameters
                    // action replace:
                    for(int i =0; i < new_action->parameters.size(); i++){
                        new_action->parameters[i] = params_map[new_action->parameters[i]];
                    }
                    
                    // preconditions replace:
                    for(State * precond : new_action->preconditions){
                        for(int i = 0; i < precond->parameters.size(); i++)
                            precond->parameters[i] = params_map[precond->parameters[i]];
                    }
                    
                    
                    // effects replace:
                    for(State * effect : new_action->effects){
                        for(int i = 0; i < effect->parameters.size(); i++)
                            effect->parameters[i] = params_map[effect->parameters[i]];
                    }
                    
                   
                                     
                    return new_action;                                                         
                }else{     
                    
                    
                    
                    
                    ////////////////////////////
                     
                    // 1 keep the mapping of original parameters
            
                    
                    // - map effect parameters with oprec parameters
                    // mapping of parameters                                        
                    std::map<std::string, std::string> mapping = std::map<std::string, std::string>();
                    for(int i = 0; i < effect->parameters.size(); i++){
                        mapping[effect->parameters[i]] = oprec->parameters[i];
                    }
                    
                    
                    for(std::string key : new_action->parameters){
                        if(mapping[key] == ""){
                            // set another parameter
                            for(std::string item : this->world->items){
                                if(!this->FindParameter(oprec->parameters, item)){
                                    mapping[key] = item;
                                }
                            }
                        }
                    }
                    
                    cout << "print map" << endl;
                    for(std::string key : new_action->parameters){
                        cout << "map[" << key << "]: " << mapping[key] << endl;                        
                    }
                                                       
                    
                    ////////////////////////////
                    cout << "PRECONDITION WITH DIFFERENT PARAMETERS CASE" << endl;
                    // replace with mapping the parameters
                    // action replace:
                    for(int i =0; i < new_action->parameters.size(); i++){
                        new_action->parameters[i] = mapping[new_action->parameters[i]];
                    }                     
                    // preconditions replace:
                    for(State * precond : new_action->preconditions){
                        for(int i = 0; i < precond->parameters.size(); i++)
                            precond->parameters[i] = mapping[precond->parameters[i]];
                    }                                        
                    // effects replace:
                    for(State * effect : new_action->effects){
                        for(int i = 0; i < effect->parameters.size(); i++)
                            effect->parameters[i] = mapping[effect->parameters[i]];
                    } 
                                       
                }              
                return  new_action;
              }
          }
      }
      
      return nullptr;
} 

void Pop::RemoveActionFromVectorByValue(std::vector<Action* > a_vector, Action * action){
    
    a_vector.erase(std::remove(a_vector.begin(), a_vector.end(), action), a_vector.end());
}

bool Pop::CheckMatchingParameters(State * A, State * B){
    for(int i = 0 ;  i < A->parameters.size(); i++){
        
        if(A->parameters[i] != B->parameters[i]){
            return false;
        }
    }
    return true;
}

bool Pop::CheckSafetyBetweenTwoSteps(Action * A, Action * B){
    for(State * a_effect :A->effects){
        for(State * b_precondition : B->preconditions){
            // check state name
            if(a_effect->name == b_precondition->name){
                // check state parameters
                if(this->CheckMatchingParameters(a_effect, b_precondition)){
                    if(a_effect->logic_op != b_precondition->logic_op)
                        return false;
                }
            }
        }
    }
    return true;
}

Edge* Pop::FindAThreat(Action * node){
    if(node->name == "FINISH")
        return nullptr;
    // find edges with node as source
    std::vector<Edge *> node_edges = std::vector<Edge *>();
    for(Edge* edge : this->plan.links){
        if(node == edge->source){
            if(!this->CheckSafetyBetweenTwoSteps(edge->source, edge->destination)){
                return edge;
            }
        }
    }
    
    return nullptr;
}  

bool Pop::ResolveAThreat(Edge * edge){
    // demotion
    cout << "Resolve a Threat - Demotion attempt" << endl;
    std::vector<Edge *> parent_new_actions = this->plan.GetEdgeByDestination(edge->source);
    std::vector<Edge *> grandparent_new_actions = this->plan.GetEdgeByDestination(edge->source);
    
    Edge * parent_e = parent_new_actions.front();
    Edge * grand_e  = grandparent_new_actions.front();
    
    // keep original
    
    Action* grand_d_dest = grand_e->destination ;    
    Action* parent_e_source = parent_e->source;
    Action* parent_e_dest = parent_e->destination;
    
    
    grand_e->destination = edge->source;
    Action * tmp = parent_e->source;
    parent_e->source = edge->source;
    parent_e->destination = tmp;
    edge->source = tmp;
    
    if(!this->CheckSafetyBetweenTwoSteps(edge->source, edge->destination) ||
       !this->CheckSafetyBetweenTwoSteps(parent_e->source, parent_e->destination)){
        // try promotion
        // recovery old status
        grand_e->destination = grand_d_dest;    
        parent_e->source = parent_e_source ;
        parent_e->destination = parent_e_dest ;
        
        std::vector<Edge *> child_es = this->plan.GetEdgeBySource(edge->destination);
        Edge * child_e = child_es.front();
        parent_e->destination = edge->source;
        tmp = edge->source;
        edge->destination = tmp;
        edge->source = child_e->source;
        child_e->source=tmp;
        
        
        if(!this->CheckSafetyBetweenTwoSteps(edge->source, edge->destination) ||
            !this->CheckSafetyBetweenTwoSteps(parent_e->source, parent_e->destination)){
            return false;
        }
        
        
    }
    
    
    // promotion
    return true;
}
bool Pop::CheckResolutionBetweenStates(State * A, State * B){
     if(A->name == B->name){
        // check state parameters
        if(this->CheckMatchingParameters(A, B)){
            if(A->logic_op == B->logic_op)
                return true;
        }
    }
    return false;
}

bool Pop::StatePresentInVector(std::vector<State*> states, State * state){
    for(State* x : states){
        if(this->CheckResolutionBetweenStates(x, state)){
            return true;
        }
    }
    
    return false;
}


bool Pop::FindStateInSet(std::set<State* > states, State* state){
    for(State * s : states){
        if(s == state){
            return true;
        }
    }
    
    return false;
}

bool Pop::FindStateInVector(std::vector<State*> states, State* state) {
    for(State * s : states){
        if(s == state){
            return true;
        }
    }
    
    return false;
}

bool Pop::CheckEffectsWithParameters(std::vector<State*> effects, State * b){
    for(State* effect : effects){
            if(this->CheckResolutionBetweenStates(effect, b)){
               return true;
            }
        }
    
    return false;
}

void Pop::UpdateOpenPreconditions( ){
    
    
    // get all effects
    // get all preconditions
    
    std::vector<State*> effects = std::vector<State*>();
    std::vector<State*> preconds = std::vector<State*>();
    std::vector<State*> preconds_x = std::vector<State*>();
    
    for(Action *  action :this->plan.actions){
        for(State * effect : action->effects){
            effects.push_back(effect);                        
        }
        
        for(State * precond : action->preconditions){
            preconds.push_back(precond);                        
        }
    }
    
    for(int i = 0; i < preconds.size(); i++){
        if(!this->CheckEffectsWithParameters(effects, preconds[i])){
            preconds_x.push_back(preconds[i]);
        }
    }
    
    this->plan.open_preconditions.clear();
    this->plan.open_preconditions = preconds_x;
    
    
}

void Pop::Algorithm(){
  do{  
    cout << "\n[POP Algorithm] - ALGORITHM STEP ----\n\n" << endl;
    if(this->plan.open_preconditions.size() > 0){
        // get the first open precondition in the vector
        cout << "[POP Algorithm] - get an open precondition" << endl;
        State * oprec = this->plan.open_preconditions.front();
        oprec->Print();
        cout << endl;
        cout << "[POP Algorithm] - the action of open precondition is :" << endl;
        Action * oprec_action = oprec->owner;
        oprec_action->Print();
        cout << endl;
        
        // find new action for open precondition
        cout << "[POP Algorithm] - Look for an action that solves the precondition" << endl;
        Action * new_action = this->FindActionForOpenPrecondition(oprec);           
        cout << "[POP Algorithm] - Found an action" << endl;
        new_action->Print();
        cout << endl;
        this->PrintAction(new_action, new_action->parameters);
        cout << endl;
        

        this->plan.actions.push_back(new_action);
        
        // find a link between oprec and its prev and update it      
        cout << "[POP Algorithm] - Update edges" << endl;
        for(int i = 0; i < this->plan.links.size(); i++){
            cout << "get the link: ";
            cout << this->plan.links[i]->source->name << " --> " << this->plan.links[i]->destination->name << endl;
            Edge * e = this->plan.links[i];
            cout << "if "; e->destination->Print();
            cout << " is equal to ";
            oprec_action->Print();
            cout << endl;
            if(e->destination == oprec_action){
                cout << "[POP Algorithm] - found an edge with the action of open precondition" << endl;
                e->Print();cout <<endl;
                cout << "!! change destination for this edge: " << endl; 
                e->destination = new_action;
                e->Print(); cout <<endl;
                // create new edge
                cout << "[POP Algorithm] - Create new edge, locating the new action between the old ones" << endl;
                Edge * new_edge = new Edge(new_action, oprec_action);                
                new_edge->Print();
                cout << endl;
                        
                this->plan.links.push_back(new_edge);
                break;                            
            }
        }
        
        
        // TODO: check threats  
        cout << "[POP Algorithm] - Resolve Threats" << endl;
        do{
          Edge * threat = FindAThreat(this->plan.start);
          if(threat == nullptr) break;
          if(!this->ResolveAThreat(threat)){
              cout << "PLANNING FAILED: cannot resolve a threat" << endl;
              exit(0); // TODO ---- the application is broken
          }

          if(threat == nullptr){
              break;
          }
        }while(true);

        std::vector<State *> effects = std::vector<State *>();
        std::vector<State *> open_prec = std::vector<State *>();
        this->UpdateOpenPreconditions(  );
          
        
        
        cout << "---STEP PLAN----" << endl;
        this->plan.PrintPlan();
        cout << "-----------------" << endl;
        
        cout << "---STEP LINKS----" << endl;
        for(Edge * edge :this->plan.links){
            edge->source->Print();
            cout << " --> " ;
            edge->destination->Print();
            cout << endl;
        }
        cout << "-----------------" << endl;
        
        cout << "--- STEP OPEN PRECONDITIONS----" << endl;
        for(State * precond: this->plan.open_preconditions){
            precond->Print();
            cout << "("; precond->owner->Print(); cout << ")";
            cout << " ";
        }
        cout << endl;
        cout << "-----------------" << endl;

    }
            
  }while(this->plan.open_preconditions.size() != 0);

  cout << " " << endl;
}

void Pop::Compute() {
    // pop algorithm
    cout << " - start computation" << endl;

    // update preconditions
    std::vector<State *> effects = std::vector<State *>();
    std::vector<State *> open_prec = std::vector<State *>();
    this->UpdateOpenPreconditions();

    
    // extract an open precondition
    this->Algorithm();
    
    cout << "[POP Algorithm] - Computation Finished" << endl;
    // print the plan
    this->plan.PrintPlan();
    cout << " [DONE]  ";

}

void Pop::PrintPlan() {

}


Pop::Pop(const Pop& orig) {
}

Pop::~Pop() {
}

void Pop::InitiatePlan() {
    this->plan.actions = std::vector<Action *>();
    
    this->plan.finish = this->world->finish;
    this->plan.start = this->world->start;
    this->plan.actions.push_back(this->plan.start);
    this->plan.actions.push_back(this->plan.finish);
    this->plan.links.push_back( new Edge(this->plan.start, this->plan.finish));
    Edge * first_edge = new  Edge(this->plan.start, this->plan.finish);
    this->plan.links.push_back(first_edge);
    for(State * precond : this->plan.finish->preconditions){
        this->plan.open_preconditions.push_back(precond);
    }
    
}


