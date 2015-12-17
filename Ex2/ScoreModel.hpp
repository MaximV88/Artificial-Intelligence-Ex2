//
//  ScoreModel.hpp
//  Ex2
//
//  Created by Maxim Vainshtein on 16/12/2015.
//  Copyright © 2015 Maxim Vainshtein. All rights reserved.
//

#ifndef ScoreModel_hpp
#define ScoreModel_hpp
#include "Policy.hpp"

POLICY_NAMESPACE_BEGIN

enum ScoreModelType {
    kScoreModelTypeSidewaysInnaccuracy = 0
};

class ScoreModel {
public:
    
    ScoreModel(ScoreModelType eType);
    
    float getScore(const Policy::State& cState, ActionType eAction) const throw(...);
    
private:
    
    const ScoreModelType m_eType;
    
    float getScoreBySidewardsInnaccuracy(const Policy::State& cState, ActionType eAction) const throw(...);
    
    
};


POLICY_NAMESPACE_END
#endif /* ScoreModel_hpp */
