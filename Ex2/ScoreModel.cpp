//
//  ScoreModel.cpp
//  Ex2
//
//  Created by Maxim Vainshtein on 16/12/2015.
//  Copyright © 2015 Maxim Vainshtein. All rights reserved.
//

#include "ScoreModel.hpp"

using namespace policy;

ScoreModel::ScoreModel(ScoreModelType eType) :
m_eType(eType) { }

float ScoreModel::getScore(const Policy::State &cState, ActionType eAction) const {
    
    switch (m_eType) {
        case kScoreModelTypeSidewaysInnaccuracy: return getScoreBySidewardsInnaccuracy(cState, eAction);
    }
    
}

float ScoreModel::getScoreBySidewardsInnaccuracy(const Policy::State &cState, ActionType eAction) const {
    
        
    /*
     * There is a chance of 70% to succeed, with 15% for the adjacent tiles
     * which we know exist since the sideways tile exists.
     */
    switch (eAction) {
        case kActionTypeMoveLeftDown:
            
            

        case kActionTypeMoveLeftUp:
        case kActionTypeMoveRightDown:
        case kActionTypeMoveRightUp:
            
            return 0.7;
            
        default: return 1;
    }
    
}
