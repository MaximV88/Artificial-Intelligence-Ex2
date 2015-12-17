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
     * There is a chance of 70% to succeed for sideways, with 15% for the adjacent tiles
     * which we know exist since the sideways tile exists.
     */
    switch (eAction) {
        case kActionTypeMoveLeftDown:
            
        {
            
            float fLeftUtility = cState.getUtility(kActionTypeMoveLeft);
            float fDownUtility = cState.getUtility(kActionTypeMoveDown);
            
            //Return the probability values as specified in instructions
            return 0.7 * cState.getUtility(kActionTypeMoveLeftDown) + 0.15 * fLeftUtility + 0.15 * fDownUtility;

        }
            
            break;
            
        case kActionTypeMoveLeftUp:
            
        {
            
            float fLeftUtility  = cState.getUtility(kActionTypeMoveLeft);
            float fUpUtility    = cState.getUtility(kActionTypeMoveUp);
            return 0.7 * cState.getUtility(kActionTypeMoveLeftUp) + 0.15 * fLeftUtility + 0.15 * fUpUtility;
            
        }
            
            break;
            
        case kActionTypeMoveRightDown:
            
        {
            
            float fRightUtility = cState.getUtility(kActionTypeMoveRight);
            float fDownUtility  = cState.getUtility(kActionTypeMoveDown);
            return 0.7 * cState.getUtility(kActionTypeMoveRightDown) + 0.15 * fRightUtility + 0.15 * fDownUtility;
            
        }
            
            break;
            
            
        case kActionTypeMoveRightUp:
            
        {
            
            float fRightUtility = cState.getUtility(kActionTypeMoveRight);
            float fUpUtility    = cState.getUtility(kActionTypeMoveUp);
            return 0.7 * cState.getUtility(kActionTypeMoveRightUp) + 0.15 * fRightUtility + 0.15 * fUpUtility;
            
        }
            
            break;
            
        //Return the Utility values for the direct movements
        default: return 1 * cState.getUtility(eAction);
            
    }
    
}
