//
//  Reward.hpp
//  Ex2
//
//  Created by Maxim Vainshtein on 16/12/2015.
//  Copyright © 2015 Maxim Vainshtein. All rights reserved.
//

#ifndef Reward_hpp
#define Reward_hpp
#include "Policy.hpp"
POLICY_NAMESPACE_BEGIN


enum RewardType {
    kRewardTypeTileValuePenalty = 0
};

/**
 *  Responsible for returning the rewards for given Tiles.
 */
class Rewards {
public:
    
    /** Constructor */
    Rewards(RewardType eType);
    
    /** Copy Constructor */
    Rewards(const Rewards& cReward);
    
    /** Returns the reward for the given state */
    float getReward(const Policy::State& cState) const;
    
private:
    
    const RewardType m_eType;
    
    float getRewardByTileValuePenalty(const Policy::State& cState) const;
    
};


POLICY_NAMESPACE_END
#endif /* Reward_hpp */
