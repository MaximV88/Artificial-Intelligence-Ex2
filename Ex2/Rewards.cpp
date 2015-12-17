//
//  Reward.cpp
//  Ex2
//
//  Created by Maxim Vainshtein on 16/12/2015.
//  Copyright © 2015 Maxim Vainshtein. All rights reserved.
//

#include "Rewards.hpp"
#include "Tile.hpp"

using namespace policy;

Rewards::Rewards(RewardType eType) :
m_eType(eType) { }

Rewards::Rewards(const Rewards& cReward) :
m_eType(cReward.m_eType) { }

float Rewards::getReward(const Policy::State& cState) const {
    
    switch(m_eType) {
        case kRewardTypeTileValuePenalty: return getRewardByTileValuePenalty(cState);
    }
    
}

float Rewards::getRewardByTileValuePenalty(const Policy::State& cState) const {
    
    //Only the final State (which is 100) is a positive reward
    if (cState.getValue() == 100) return 100;
    
    //Return the penalty of that value (multiply by -1)
    return ((-1) * (cState.getValue()));
    
}