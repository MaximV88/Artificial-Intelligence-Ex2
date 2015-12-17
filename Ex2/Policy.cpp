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

using namespace policy;

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
    
    
    
    
    return out;
}

#pragma mark - State functions

Policy::State::State(const Tile* cTile) :
m_cTile(cTile) { }

Policy::State::State(const State& cState) :
m_cTile(new Tile(*cState.m_cTile)) { }

Policy::State::~State() {

    if (m_cTile) delete m_cTile;

}

const Tile* Policy::State::getTile() const {
    
    //Returns the internally stored pointer
    return m_cTile;
    
}