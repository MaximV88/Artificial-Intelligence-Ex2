//
//  main.cpp
//  Ex2
//
//  Created by Maxim Vainshtein on 15/12/2015.
//  Copyright © 2015 Maxim Vainshtein. All rights reserved.
//

#include <iostream>
#include <fstream>

#include "Map.hpp"
#include "Policy.hpp"
#include "ScoreModel.hpp"
#include "Rewards.hpp"

using namespace policy;

int main(int argc, const char * argv[]) {

    //Read the file to seperate the contents of map and algorithm
    std::ifstream ifs("input2.txt");
    
    //Get the formatted map (reading from current location until end of file)
    std::string strFormattedMap((std::istreambuf_iterator<char>(ifs) ),
                                (std::istreambuf_iterator<char>()    ));
    
    Policy* cPolicy = Policy::createPolicy(
                                          
                                           //The required type is for value iteration
                                           kPolicyTypeValueIteration,
                                          
                                           //The Map the policy should be built on
                                           Map(strFormattedMap),
                                          
                                           //The transition model the policy should decide by
                                           ScoreModel(kScoreModelTypeSidewaysInnaccuracy),
                                          
                                           //The rewards the policy should consider
                                           Rewards(kRewardTypeTileValuePenalty));
    
    std::cout << *cPolicy;
    
    delete cPolicy;
    
    return 0;

}
