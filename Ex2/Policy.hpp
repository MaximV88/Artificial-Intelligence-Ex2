//
//  Policy.hpp
//  Ex2
//
//  Created by Maxim Vainshtein on 16/12/2015.
//  Copyright © 2015 Maxim Vainshtein. All rights reserved.
//

#ifndef Policy_hpp
#define Policy_hpp
#include <stdio.h>
#include <iostream>

#define POLICY_NAMESPACE_BEGIN namespace policy {
#define POLICY_NAMESPACE_END }

class Map;
class Tile;

enum ActionType {
    kActionTypeNone = -1,
    kActionTypeMoveRight,
    kActionTypeMoveLeft,
    kActionTypeMoveUp,
    kActionTypeMoveDown,
    kActionTypeMoveRightDown,
    kActionTypeMoveRightUp,
    kActionTypeMoveLeftDown,
    kActionTypeMoveLeftUp,
    kActionTypeTotalNumber
};

POLICY_NAMESPACE_BEGIN

class Rewards;
class ScoreModel;

enum PolicyType {
    kPolicyTypeValueIteration = 0
};

/**
 * The Policy class has defined action
 * toward every position that is given to it.
 */
class Policy {
public:
    
    /**
     * Returns the action the policy decided for the input tile
     *
     * @param eType The wanted action type the policy should follow.
     * @param cMap The map the policy is to act on.
     * @param cScoreModel The scoring model for consideration of the policy (calculates score per each possible action).
     * @param cReward The reward system the Policy follows by.
     * @param fDiscount The discount value the policy consideres.
     *
     * @return Policy object that describes the best actions that can be made on given parameters.
     */
    static Policy* createPolicy(PolicyType eType,
                                const Map& cMap,
                                const ScoreModel& cScoreModel,
                                const Rewards& cReward,
                                float fDiscount);
    
    /**
     * Returns the action the policy decided for the input tile
     *
     * @param cTile The tile that the action is considered for.
     * @return Direction that is considered best to go to by the policy (best action to perform)
     */
    ActionType action(const Tile& cTile) const throw(...);
    
    /**
     * Returns the actions the policy decided for the tile at the input coordinate
     *
     * @param uiX The X coordinate for a requested query.
     * @param uiY The Y coordinate for a requested query.
     * @return Direction that is considered best to go to by the policy (best action to perform)
     */
    virtual ActionType action(size_t uiX, size_t uiY) const throw(...) = 0;
    
    /**
     * Prints the Policy, including the internal action layout of the input map.
     *
     * @param out The osteam object that can print.
     * @param cPolicy The policy object that is to be printed.
     *
     * @return ostream object that was given in parameter (this made to allow for chaining another print).
     */
    friend std::ostream& operator<<(std::ostream &out, const Policy &cPolicy);
    
    /**
     * Desctructor.
     */
    virtual ~Policy();
    
protected:
    
    /*
     * The ScoreModel class has outsourced functionality that is performed by Policy subclasses,
     * therefore it needs access to the State class to complete these calculations.
     */
    friend class ScoreModel;
    friend class Rewards;
    
    class State {
    public:
        
        virtual float getValue() const = 0;
        virtual float getUtility() const = 0;
        virtual float getUtility(ActionType eAction) const throw(...) = 0;
        
    };
    
};

POLICY_NAMESPACE_END
#endif /* Policy_hpp */
