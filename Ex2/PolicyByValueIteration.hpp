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
     * @param cState The state that the action is considered for.
     * @return Action that is considered best to go to by the policy (best action to perform)
     */
    virtual ActionType bestAction(const Policy::State& cState) const throw();
    
    /**
     * Desctructor.
     */
    virtual ~PolicyByValueIteration();
    
protected:
    
    virtual const State* getStateForPosition(size_t uiX, size_t uiY) const throw(...);
    
private:
    
    /*
     * The internal State representation needs
     * access for the private Utility methods.
     */
    friend class StateByValueIteration;
    
    /**
     * The class is responsible for the implementation of 
     * State functionality so that it conforms to the operation
     * of the PolicyByValueIteration class.
     */
    class StateByValueIteration : public State {
    public:
        
        StateByValueIteration(const PolicyByValueIteration& cPolicy, const Tile& cTile);
        
        /**
         * Returns the utility value for the state.
         *
         * @return A utility value.
         */
        virtual float getUtility() const;
        
        /**
         * Returns the utility value that results from performing the input action.
         *
         * @param eAction The utility that results in performing the input action.
         * @return A utility value.
         */
        virtual float getUtility(ActionType eAction) const throw(...);
        
        /**
         * Returns true if terminal state, false otherwise.
         *
         * @return True if the State is terminal, false otherwise.
         */
        virtual bool isTerminal() const;
        
    private:
        
        ///Holds a pointer to the policy owner
        const PolicyByValueIteration& m_cPolicy;
        
    };
    
    /**
     * Responsible for ordering of States based on their internal representation
     * that results from the Tile object.
     */
    struct StateByValueIterationComparatorLessThan {
        bool operator() (const StateByValueIteration* lhs, const StateByValueIteration* rhs) {
            return lhs->getTile() < rhs->getTile();
        }
    };

    /**
     * Perform a Value Iteration algorithm with the current Utility values, Returns the resulting Utility values.
     *
     * @param cMap The map that the Policy should calculate from.
     * @param cScoreModel The model that is to calculate the scores for a pair of states.
     * @param cReward The reward system.
     * @param cDiscount The discount value for policy calculations
     * @return A float dynamic array that holds the value per state in it's index mapped to map coordinates.
     */
    float* valueIteration(const Map& cMap, const ScoreModel& cScoreModel, const Rewards& cReward, float fDiscount) const;
    
    /**
     * Returns the best actions that can be made based on the input Utility values.
     *
     * @param cMap The map that the actions should be mapped to (via index).
     * @param cScoreModel The model that is to calculate the scores for a pair of states.
     * @return A dynamic array that contains the best actions mapped to the map coordinates.
     */
    ActionType* bestActions(const Map& cMap, const policy::ScoreModel &cScoreModel) const;
    
    /**
     * Returns the Utility value for the input state.
     *
     * @param cState The state which the utility is required for.
     * @return Utility value for the input state.
     */
    float getUtility(const StateByValueIteration& cState) const;
        
    /**
     * Builds the states that represent the map.
     *
     * @param cMap The map that the states should represent.
     */
    std::vector<const State*> buildStates(const Map& cMap) const;
    
    /**
     * Calculates the RMS value based on the input float arrays.
     *
     * @param fOld First array
     * @param fNew Second array
     * @return the RMS value from the comparison of the input arrays.
     */
    float calculateRMS(float* fOld, float* fNew) const;
    
    /**
     * A debug function that returns the state description of the utilities as map.
     *
     * @return A string describing a map with utility values.
     */
    std::string statusByUtilities() const;
    
    /**
     * Allocates a dynamic array of a given type.
     *
     * @param The map that the actions will be mapped to.
     * @param The initial value the array will be assigned to.
     * @return A dynamic array with size of the input map.
     */
    template<class T>
    T* buildDynamicArray(size_t uiSize, T tInitialValue) const;
    
    ///The Uilities are stored in a dynamic array with indexes that map to coordinates of tiles (which they hold values for).
    float* m_fUtilities = NULL;
    
    ///Stores the best actions that should be performed based on coordinates
    ActionType* m_eBestActions = NULL;
    
    ///The map object that the policy is constructed for
    const Map& m_cMap;
    
};


POLICY_NAMESPACE_END
#endif /* PolicyByValueIteration_hpp */
