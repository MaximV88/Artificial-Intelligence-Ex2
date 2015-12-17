//
//  PolicyByValueIteration.cpp
//  Ex2
//
//  Created by Maxim Vainshtein on 16/12/2015.
//  Copyright © 2015 Maxim Vainshtein. All rights reserved.
//

#include "PolicyByValueIteration.hpp"
#include "Map.hpp"
#include "Rewards.hpp"
#include "ScoreModel.hpp"
#include <set>

#define UTILITY_INITIAL_VALUE 0

using namespace policy;

PolicyByValueIteration::PolicyByValueIteration(const Map& cMap, const ScoreModel& cScoreModel, const Rewards& cReward, float fDiscount) :
m_cMap(cMap) {
    
    //Build the internal representation of the input map
    m_fUtilities = buildDefaultUtilities(cMap);
    
    while (1) {
    
        //The algorithm needs a tile to start from
        StateByValueIteration cState = StateByValueIteration(*this, cMap.getStartTile());
        std::set<const StateByValueIteration, StateByValueIterationComparatorLessThan> scVisited;
        
        float* fTemporaryUtilities = buildDefaultUtilities(cMap);
        
        /*
         * The iteration is made towards each possible action, in which the maximum
         * value score is chosen and set in a temporary utilities array.
         */
        float fBestUtility = getUtility(cState);
        for (int iAction = kActionTypeNone ; iAction < kActionTypeTotalNumber ; iAction++) {
            
            float fScore = cScoreModel.getScore(cState, static_cast<ActionType>(iAction));
            
            //Enter the value into the visited set to avoid duplicate checking
            scVisited.insert(cState);
            
        }
        
        
    }
    
    
}

PolicyByValueIteration::~PolicyByValueIteration() {
    
    //Delete the dynamic array if found
    if (m_fUtilities)
        delete [] m_fUtilities;
    
}

float* PolicyByValueIteration::buildDefaultUtilities(const Map &cMap) const {
    
    //Build a dynamic array that maps to the size of the input map
    size_t uiTotalStates = cMap.getTilesCount();
    float* fUtilities = new float[uiTotalStates];
    
    //Initialize and send back
    for (size_t uiIndex = 0 ; uiIndex < uiTotalStates ; uiIndex++)
        fUtilities = UTILITY_INITIAL_VALUE;
    
    return fUtilities;
    
}

ActionType PolicyByValueIteration::action(size_t uiX, size_t uiY) const {
    return kActionTypeMoveDown;
}

float PolicyByValueIteration::getUtility(const StateByValueIteration &cState) const {
    
    //Gets the index from the Map object and returns the stored value
    return m_fUtilities[m_cMap.getIndex(cState.getTile())];

}

void PolicyByValueIteration::setUtility(float fUtility, const StateByValueIteration &cState) {
    
    //Gets the index from the Map object and assigns it the value
    m_fUtilities[m_cMap.getIndex(cState.getTile())] = fUtility;

}

#pragma mark - StateByValueIteration methods

PolicyByValueIteration::StateByValueIteration::StateByValueIteration(const PolicyByValueIteration& cPolicy, const Tile& cTile) :
m_cPolicy(cPolicy), m_cTile(cTile) { }

const Tile& PolicyByValueIteration::StateByValueIteration::getTile() const {
    
    //Returns the internally stored pointer
    return m_cTile;

}

float PolicyByValueIteration::StateByValueIteration::getValue() const {
    
    //The value is determined by the tile type
    return m_cTile.eType;

}

float PolicyByValueIteration::StateByValueIteration::getUtility() const {
    
    //Gets the utility value via the Policy
    return m_cPolicy.getUtility(*this);

}

float PolicyByValueIteration::StateByValueIteration::getUtility(ActionType eAction) const {
    
    //Find the tile in the requested direction and ask for it's utility (Directions and ActionType are mapped to same meaning)
    return m_cPolicy.getUtility(StateByValueIteration(m_cPolicy, m_cTile.getNeighbor(static_cast<Directions>(eAction))));
    
}
