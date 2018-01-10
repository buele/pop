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
 * File:   Pop.h
 * Author: buele
 *
 * Created on December 3, 2017, 10:56 PM
 */

#ifndef POP_H
#define POP_H

class Pop {
public:

    Pop(World * world);
    Pop(const Pop& orig);

    void Compute();
    void PrintPlan();
    void InitiatePlan();
    virtual ~Pop();

    World * world;
    Plan plan;
private:
    void PrintState(State * state);
    void PrintAction(Action * action,std::vector<std::string>parameters);
    void CheckFinishPrecodsWithStartEffects();
    void Algorithm();
    Action * FindActionForOpenPrecondition(State * oprec);
    void RemoveActionFromVectorByValue(std::vector<Action* > a_vector, Action * action);
    bool CheckSafetyBetweenTwoSteps(Action * A, Action * B);
    Edge* FindAThreat(Action * node);
    bool ResolveAThreat(Edge * edge);
    bool CheckMatchingParameters(State * A, State * B);
    void UpdateOpenPreconditions();
    bool CheckResolutionBetweenStates(State * A, State * B);
    bool StatePresentInVector(std::vector<State*> states, State * state);
    bool FindParameter(std::vector<std::string> parameters, std::string parameter);
    bool FindStateInSet(std::set<State* > states, State* state);
    bool FindStateInVector(std::vector<State* > states, State* state);
    bool CheckEffectsWithParameters(std::vector<State*> effects, State * b);


};

#endif /* POP_H */

