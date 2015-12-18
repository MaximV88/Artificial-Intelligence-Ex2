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
#include "Map.hpp"
#include <stdexcept>
#include <sstream>

using namespace policy;

/**
 * The sorting predicate for the printing of the policy.
 */
struct StateSortingPredicate {
    bool operator()(const Policy::State* lhs, const Policy::State* rhs) {
        
        //Sort by Y and then by X
        const Tile& cTilel = lhs->getTile();
        const Tile& cTiler = rhs->getTile();
        
        return ((cTilel.getY() < cTiler.getY()) || ((cTilel.getY() == cTiler.getY()) && cTilel.getX() < cTiler.getX()));

    }
};

Policy* Policy::createPolicy(PolicyType eType, const Map &cMap, const ScoreModel &cScoreModel, const Rewards &cReward, float fDiscount) {
    
    switch(eType) {
        case kPolicyTypeValueIteration: return new PolicyByValueIteration(cMap, cScoreModel, cReward, fDiscount);
    }
    
}

Policy::Policy(std::vector<const State*> vcStates) :
m_vcStates(vcStates) { }

Policy::~Policy() {

    //Delete all of the stored states
    for (std::vector<const State*>::const_iterator iterator = m_vcStates.begin() ; iterator != m_vcStates.end() ; iterator++)
        delete (*iterator);

}

std::vector<const Policy::State*> Policy::getStates() const { return m_vcStates; }

std::ostream& policy::operator<<(std::ostream &out, const Policy &cPolicy) {
    
    /*
     * The format to print is: <line>,<row>,<action> by printing
     * every row completly before going to the next one.
     */
    
    std::vector<const Policy::State*> vcStates = cPolicy.getStates();

    //Sort the states according to the required order
    std::sort(vcStates.begin(), vcStates.end(), StateSortingPredicate());
    
    for (std::vector<const Policy::State*>::const_iterator iterator = vcStates.begin() ; iterator != vcStates.end() ; iterator++) {
        
        ActionType eBestAction = cPolicy.bestAction(**iterator);
        
        //Instructions dont want to print the end tile
        if ((*iterator)->getTile().eType == kEnd) continue;

        //Print only when not in the first row
        if (iterator != vcStates.begin())
            out << "\n";
        
        out << **iterator << ",";

        //Stores the string to be printed
        std::string strDescription;
        
        switch (eBestAction) {
            case kActionTypeMoveDown:       out << "D";     break;
            case kActionTypeMoveUp:         out << "U";     break;
            case kActionTypeMoveLeft:       out << "L";     break;
            case kActionTypeMoveRight:      out << "R";     break;
            case kActionTypeMoveLeftDown:   out << "LD";    break;
            case kActionTypeMoveLeftUp:     out << "LU";    break;
            case kActionTypeMoveRightDown:  out << "RD";    break;
            case kActionTypeMoveRightUp:    out << "RU";    break;
            case kActionTypeNone:           out << "C";     break;
            default: break;
        }
        
    }
    
    return out;
    
}

#pragma mark - State functions

Policy::State::State(const Tile& cTile) :
m_cTile(cTile) { }

Policy::State::State(const State& cState) :
m_cTile(cState.m_cTile) { }

Policy::State::~State() { }

const Tile& Policy::State::getTile() const {
    
    //Returns the internally stored pointer
    return m_cTile;
    
}

std::ostream& policy::operator<<(std::ostream &out, const Policy::State &cState) {

    const Tile& cTile = cState.getTile();

    //Print the required format
    out << cTile.getY() << "," << cTile.getX();

    return out;
}
