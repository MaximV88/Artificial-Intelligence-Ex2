//
//  PolicyByValueIteration.hpp
//  Ex2
//
//  Created by Maxim Vainshtein on 16/12/2015.
//  Copyright © 2015 Maxim Vainshtein. All rights reserved.
//

#ifndef PolicyByValueIteration_hpp
#define PolicyByValueIteration_hpp
#include "Policy.hpp"
#include "Tile.hpp"

POLICY_NAMESPACE_BEGIN

/**
 * Finds the policy by Value Iteration method.
 */
class PolicyByValueIteration : public Policy {
public:
    
    /**
     * Constructor.
     *
     * @param cMap The map that the Policy should calculate from.
     * @param cScoreModel The model that is to calculate the scores for a pair of states.
     * @param cReward The reward system.
     * @param cDiscount The discount value for policy calculations
     */
    PolicyByValueIteration(const Map& cMap, const ScoreModel& cScoreModel, const Rewards& cReward, float fDiscount);
    
    /**
     * Returns the actions the policy decided for the tile at the input coordinate
     *
     * @param uiX The X coordinate for a requested query.
     * @param uiY The Y coordinate for a requested query.
     * @return Direction that is considered best to go to by the policy (best action to perform)
     */
    virtual ActionType action(size_t uiX, size_t uiY) const;
    
    /**
     * Desctructor.
     */
    virtual ~PolicyByValueIteration();
    
private:
    
    /*
     * The internal State representation needs
     * access for the private Utility methods.
     */
    friend class StateByValueIteration;
    
    class StateByValueIteration : public State {
    public:
        
        StateByValueIteration(const PolicyByValueIteration& cPolicy, const Tile& cTile);
        
        virtual float getValue() const;
        virtual float getUtility() const;
        virtual float getUtility(ActionType eAction) const throw(...);
        
        const Tile& getTile() const;
        
    private:
        
        const PolicyByValueIteration& m_cPolicy;
        const Tile& m_cTile;
        
    };
    
    struct StateByValueIterationComparatorLessThan {
        bool operator() (const StateByValueIteration lhs, const StateByValueIteration rhs) {
            return lhs.getTile() < rhs.getTile();
        }
    };
    
    /**
     * Returns the Utility value for the input state.
     *
     * @param cState The state which the utility is required for.
     * @return Utility value for the input state.
     */
    float getUtility(const StateByValueIteration& cState) const;
    
    /**
     * Sets the Utility value for that state to the input parameter.
     *
     * @param fUtility The Utility value for the associated state.
     * @param cState The state which the Utility value is to be set unto.
     */
    void setUtility(float fUtility, const StateByValueIteration& cState);
    
    /**
     * Allocates a dynamic array to hold the Utility values for the states.
     *
     * @param The map that the utilities will be mapped to.
     * @return A dynamic array with size of the input map.
     */
    float* buildDefaultUtilities(const Map& cMap) const;
    
    ///The utilities are stored in a dynamic array with indexes that map to coordinates of tiles (which they hold values for).
    float* m_fUtilities = NULL;
    
    ///The map object that the policy is constructed for
    const Map& m_cMap;
    
};


POLICY_NAMESPACE_END
#endif /* PolicyByValueIteration_hpp */
