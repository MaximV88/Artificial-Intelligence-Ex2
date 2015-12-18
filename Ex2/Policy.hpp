//
//  Policy.hpp
//  Ex2
//
//  Created by Maxim Vainshtein on 16/12/2015.
//  Copyright © 2015 Maxim Vainshtein. All rights reserved.
//

#ifndef Policy_hpp
#define Policy_hpp
#include "Tile.hpp"
#include <stdio.h>
#include <iostream>
#include <vector>
#define POLICY_NAMESPACE_BEGIN namespace policy {
#define POLICY_NAMESPACE_END }

class Map;
class Tile;

enum ActionType {
    kActionTypeInvalid = -1,
    kActionTypeNone,
    kActionTypeMoveRightUp,
    kActionTypeMoveUp,
    kActionTypeMoveLeftUp,
    kActionTypeMoveLeft,
    kActionTypeMoveLeftDown,
    kActionTypeMoveDown,
    kActionTypeMoveRightDown,
    kActionTypeMoveRight,
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
     * Describes the state with which the policy can decide the best actions for.
     */
    class State {
    public:
        
        /**
         * Constructor.
         *
         * @param cTile A tile that the state's position represents. Must not be nil.
         */
        State(const Tile& cTile);
        
        /**
         * Copy Constructor.
         *
         * @param The state to copy.
         */
        State(const State& cState);
        
        /**
         * Returns the position (tile) that the state represents.
         *
         * @return A tile that the state represents.
         */
        const Tile& getTile() const;
        
        /**
         * Returns true if terminal state, false otherwise.
         *
         * @return True if the State is terminal, false otherwise.
         */
        virtual bool isTerminal() const = 0;
        
        /**
         * Prints the State.
         *
         * @param out The osteam object that can print.
         * @param cPolicy The State object that is to be printed.
         *
         * @return ostream object that was given in parameter (this made to allow for chaining another print).
         */
        friend std::ostream& operator<<(std::ostream &out, const Policy::State &cState);
        
        /**
         * Destructor.
         */
        virtual ~State();
        
    protected:
        
        /* 
         * ScoreModel needs access to Utility values to perform it's task.
         * It is a logical seperation of Policy to allow multiple implementations
         * of ScoreModels without changing the Policy implementation.
         */
        friend class ScoreModel;
        
        /**
         * Returns the utility value for the state.
         * 
         * @return A utility value.
         */
        virtual float getUtility() const = 0;
        
        /**
         * Returns the utility value that results from performing the input action.
         * 
         * @param eAction The utility that results in performing the input action.
         * @return A utility value.
         */
        virtual float getUtility(ActionType eAction) const throw(...) = 0;
                
        ///Holds the position that the state represents.
        const Tile m_cTile;
        
    };
    
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
                                float fDiscount = 1);
    
    /**
     * Constructor.
     *
     * @param vcStates The states that the policy should be performed on. 
     */
    Policy(std::vector<const Policy::State*> vcStates);
    
    /**
     * Returns the action the policy decided for the input tile
     *
     * @param cState The state that the action is considered for.
     * @return Action that is considered best to go to by the policy (best action to perform)
     */
    virtual ActionType bestAction(const Policy::State& cState) const throw() = 0;
    
    /**
     * Prints the Policy.
     *
     * @param out The osteam object that can print.
     * @param cPolicy The policy object that is to be printed.
     *
     * @return ostream object that was given in parameter (this made to allow for chaining another print).
     */
    friend std::ostream& operator<<(std::ostream &out, const Policy &cPolicy);
    
    /**
     * Returns the states that are used in the policy.
     *
     * @return Vector containing all states.
     */
    std::vector<const State*> getStates() const;
    
    /**
     * Desctructor.
     */
    virtual ~Policy();
    
protected:
    
    ///Stores the states that are contained in the policy.
    const std::vector<const State*> m_vcStates;

};

POLICY_NAMESPACE_END
#endif /* Policy_hpp */
