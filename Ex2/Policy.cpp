//
//  Policy.cpp
//  Ex2
//
//  Created by Maxim Vainshtein on 16/12/2015.
//  Copyright © 2015 Maxim Vainshtein. All rights reserved.
//

#include "Policy.hpp"
#include "PolicyByValueIteration.hpp"
#include "Tile.hpp"
#include <stdexcept>

using namespace policy;

Policy* Policy::createPolicy(PolicyType eType, const Map &cMap, const ScoreModel &cScoreModel, const Rewards &cReward, float fDiscount) {
    
    switch(eType) {
        case kPolicyTypeValueIteration: return new PolicyByValueIteration(cMap, cScoreModel, cReward, fDiscount);
    }
    
}

Policy::~Policy() { }

ActionType Policy::action(const Tile &cTile) const { return action(cTile.getX(), cTile.getY()); }

std::ostream& policy::operator<<(std::ostream &out, const Policy &cPolicy) {
    return out;
}
