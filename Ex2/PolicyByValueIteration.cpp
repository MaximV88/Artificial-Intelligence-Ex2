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
#include <stack>
#include <stdexcept>
#include <sstream>
#include <math.h>

#define UTILITY_INITIAL_VALUE 0

using namespace policy;

PolicyByValueIteration::PolicyByValueIteration(const Map& cMap, const ScoreModel& cScoreModel, const Rewards& cReward, float fDiscount) :
Policy(buildStates(cMap)), m_cMap(cMap) {
    
    //TODO: fix copy of vector using reference
    
    //Build the internal representation of the input map
    m_fUtilities = buildDynamicArray<float>(cMap.getTilesCount(), UTILITY_INITIAL_VALUE);
    
    while (true) {
    
        //Perform the value iteration step
        float* fTemporaryUtilities = valueIteration(cMap, cScoreModel, cReward, fDiscount);

        //Check differences via RMS for termination of iteration
        double fRMS = calculateRMS(m_fUtilities, fTemporaryUtilities);
        
        //Remove values that are no longer needed
        delete [] m_fUtilities;
        
        //Once the Utility calculation for the current state is finished, update the values
        m_fUtilities = fTemporaryUtilities;
        
        if (fRMS == 0.0)
            break;
        
    }
    
    //After finishing calculating the Utility values, decide the best actions
    m_eBestActions = bestActions(cMap, cScoreModel);
    
}

PolicyByValueIteration::~PolicyByValueIteration() {
    
    //Delete the dynamic array if found
    if (m_fUtilities)
        delete [] m_fUtilities;
    
    if (m_eBestActions)
        delete [] m_eBestActions;
    
}

float PolicyByValueIteration::calculateRMS(float *fOld, float *fNew) const {

    size_t uiTotalStates = getStates().size();
    size_t uiTotalTiles = m_cMap.getTilesCount();
    
    float fSum = 0;
    
    //Calculate the sum of the differences
    for (size_t uiIndex = 0 ; uiIndex < uiTotalTiles ; uiIndex++)
        fSum += powf(fOld[uiIndex] - fNew[uiIndex], 2);

    //Return the RMS
    return ((float)(1 / (float)uiTotalStates) * (sqrtf(fSum)));

}

float* PolicyByValueIteration::valueIteration(const Map &cMap, const policy::ScoreModel &cScoreModel, const policy::Rewards &cReward, float fDiscount) const {
    
    //The Utility array to hold temporary values
    float* fUtilities = buildDynamicArray<float>(cMap.getTilesCount(), UTILITY_INITIAL_VALUE);
    
    //Iterate over all of the states
    for (std::vector<const State*>::const_iterator iterator = m_vcStates.begin() ; iterator != m_vcStates.end() ; iterator++) {
        
        /*
         * The iteration is made towards each possible action, in which the maximum
         * value score is chosen and set in a temporary utilities array.
         */
        
        //The terminal nodes apply only the reward.
        if ((*iterator)->isTerminal()) {
            fUtilities[cMap.getIndex((*iterator)->getTile())] = cReward.getReward(**iterator);
            continue;
        }
        
        float fBestUtility = getUtility(*static_cast<const StateByValueIteration*>(*iterator));
        for (int iAction = kActionTypeNone + 1 ; iAction < kActionTypeTotalNumber ; iAction++) {
            
            try {
                
                //This might raise an exception if there is no state for the requested action
                float fScore = cScoreModel.getScore(**iterator, static_cast<ActionType>(iAction));
                
                //Assign the maximum value
                if (fScore > fBestUtility)
                    fBestUtility = fScore;
                
            } catch (...) {
                
                //A non valid action will not affect the end result if to ignore it
                
            }
            
        }
        
        //Assign the value to the temporary array to be used a future utility (once iteration is over)
        fUtilities[cMap.getIndex((*iterator)->getTile())] = cReward.getReward(**iterator) + fBestUtility * fDiscount;

    }
    
    return fUtilities;
    
}

ActionType* PolicyByValueIteration::bestActions(const Map &cMap, const policy::ScoreModel &cScoreModel) const {
    
    //Create a dynamic array filled with initalized values
    ActionType* eActions = buildDynamicArray<ActionType>(cMap.getTilesCount(), kActionTypeInvalid);
    
    //Iterate over all of the states
    for (std::vector<const State*>::const_iterator iterator = m_vcStates.begin() ; iterator != m_vcStates.end() ; iterator++) {

        //For the current state, consider the best actions from the input utility values
        float fBestUtility = static_cast<const StateByValueIteration*>(*iterator)->getUtility();
        
        //If the best utility is the starting utility dont do anything
        ActionType eBestAction = kActionTypeNone;
        
        for (int iAction = kActionTypeNone + 1 ; iAction < kActionTypeTotalNumber ; iAction++) {
            
            try {
                
                //Might throw an exception if no state exists for the action - the contained object was created originally in this class
                float fUtility = cScoreModel.getScore(**iterator, static_cast<ActionType>(iAction));

                //Assign the maximum value
                if (fUtility > fBestUtility || (fUtility == fBestUtility && eBestAction == kActionTypeNone)) {
                    
                    fBestUtility = fUtility;
                    eBestAction = static_cast<ActionType>(iAction);
   
                }
                
            } catch (...) {
        
                //There is no state for the input action, thus no action is made
                
            }
            
        }
        
        eActions[cMap.getIndex((*iterator)->getTile())] = eBestAction;
        
    }
    
    return eActions;
    
}

ActionType PolicyByValueIteration::bestAction(const Policy::State& cState) const throw() {

    //Gets the index from the Map object and returns the stored best action
    try {
        
        const Tile& cTile = cState.getTile();
        return m_eBestActions[m_cMap.getIndex(cTile.getX(), cTile.getY())];
        
    } catch (...) {
        
        //There is no such position, so there is no action
        return kActionTypeNone;
        
    }
        
}

float PolicyByValueIteration::getUtility(const StateByValueIteration &cState) const {
    
    //Gets the index from the Map object and returns the stored value
    return m_fUtilities[m_cMap.getIndex(cState.getTile())];

}

std::vector<const Policy::State*> PolicyByValueIteration::buildStates(const Map &cMap) const {
 
    std::set<const StateByValueIteration*, StateByValueIterationComparatorLessThan> scVisited;
    std::stack<const StateByValueIteration*> vcFrontier;
    
    //The algorithm needs a tile to start from
    vcFrontier.push(new StateByValueIteration(*this, cMap.getStartTile()));
    
    //Traversal order of Utility calculation does not matter
    while (!vcFrontier.empty()) {
        
        const StateByValueIteration* cState = vcFrontier.top();
        
        //The state is no longer needed to be considered in the stack
        vcFrontier.pop();
        
        //Enter the value into the visited set to avoid duplicate checking
        scVisited.insert(cState);
        
        //Enter all of the neighbors to be considered
        std::vector<const Tile*> vcNeighbors = cState->getTile().getNeighbors();
        for (size_t uiIndex = 0 ; uiIndex < vcNeighbors.size() ; uiIndex++) {
            
            //To avoid the stack allocated objects take their representation from the map
            const StateByValueIteration* cNeighborState = new StateByValueIteration(*this, *vcNeighbors[uiIndex]);
            
            //If not already visited in, push for a future iteration
            if (scVisited.find(cNeighborState) == scVisited.end())
                vcFrontier.push(cNeighborState);
            else {
                
                //Remove the duplicate
                delete cNeighborState;
                
            }
            
        }
        
    }
    
    return std::vector<const Policy::State*>(scVisited.begin(), scVisited.end());
    
}

const Policy::State* PolicyByValueIteration::getStateForPosition(size_t uiX, size_t uiY) const {
    
    //Find out if there is a valid tile in that position
    const Tile* cTile = NULL;
    
    try {
        
        cTile = m_cMap.getTile(uiX, uiY);
        
    } catch (...) {
        
        //Lack of tile means that there is no state for this, but a map exception is not an error one.
        
    }
    
    if (!cTile) throw std::runtime_error("There is no state for the given input.");
    else {
        
        //The found tile copy will be returned encapsulated in a State
        return new StateByValueIteration(*this, *cTile);
        
    }
}

std::string PolicyByValueIteration::statusByUtilities() const {
    
    std::string strDescription;
    
    for (size_t uiY = 0 ; uiY < m_cMap.getWidth() ; uiY++) {
        for (size_t uiX = 0 ; uiX < m_cMap.getHeight() ; uiX++) {
            
            std::ostringstream os;
            os<< (m_fUtilities[m_cMap.getIndex(uiX, uiY)]);
            
            strDescription += os.str();
            strDescription += "\t\t";

        }
    
        strDescription += "\n";
        
    }
    
    return strDescription;
    
}

#pragma mark - Template functions

template<typename T>
T* PolicyByValueIteration::buildDynamicArray(size_t uiSize, T tInitialValue) const {
    
    //Build a dynamic array that maps to the size of the input map
    T* tTypes = new T[uiSize];
    
    //Initialize and send back
    for (size_t uiIndex = 0 ; uiIndex < uiSize ; uiIndex++)
        tTypes[uiIndex] = tInitialValue;
    
    return tTypes;
    
}

#pragma mark - StateByValueIteration functions

PolicyByValueIteration::StateByValueIteration::StateByValueIteration(const PolicyByValueIteration& cPolicy, const Tile& cTile) :
State(cTile), m_cPolicy(cPolicy) { }

float PolicyByValueIteration::StateByValueIteration::getUtility() const {
    
    //Gets the utility value via the Policy
    return m_cPolicy.getUtility(*this);

}

float PolicyByValueIteration::StateByValueIteration::getUtility(ActionType eAction) const {
    
    //Find the tile in the requested direction and ask for it's utility (Directions and ActionType are mapped to same meaning)
    return m_cPolicy.getUtility(StateByValueIteration(m_cPolicy, m_cTile.getNeighbor(static_cast<Directions>(eAction))));
    
}

bool PolicyByValueIteration::StateByValueIteration::isTerminal() const { return getTile().eType == kEnd; }
