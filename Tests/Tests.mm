//
//  Tests.m
//  Tests
//
//  Created by Maxim Vainshtein on 18/12/2015.
//  Copyright © 2015 Maxim Vainshtein. All rights reserved.
//

#import <XCTest/XCTest.h>
#import <iostream>
#import <fstream>
#import <sstream>

#import "Map.hpp"
#import "Policy.hpp"
#import "ScoreModel.hpp"
#import "Rewards.hpp"

using namespace policy;

@interface Tests : XCTestCase

@end

@implementation Tests

- (void)testInputs {
   
    XCTAssertTrue(compare("input.txt", "output.txt"));
    XCTAssertTrue(compare("input2.txt", "output2.txt"));
    XCTAssertTrue(compare("input3.txt", "output3.txt"));
    XCTAssertTrue(compare("input4.txt", "output4.txt"));
    XCTAssertTrue(compare("input5.txt", "output5.txt"));
    XCTAssertTrue(compare("input6.txt", "output6.txt"));
    XCTAssertTrue(compare("input7.txt", "output7.txt"));

}

bool compare(const std::string& strInput, const std::string& stdOutput) {
    
    std::string strResult = getResult(strInput);
    std::string strOutput = getContents(stdOutput);

    //Conform by removing redundant characters
    strOutput.erase(std::remove(strOutput.begin(), strOutput.end(), '\r'), strOutput.end());
    strOutput.erase(std::remove(strOutput.begin(), strOutput.end(), '\n'), strOutput.end());
    strResult.erase(std::remove(strResult.begin(), strResult.end(), '\n'), strResult.end());

    bool bResult = strResult == strOutput;
    
    if (!bResult) {

        std::cout << "Result:\n" << strResult << std::endl;
        std::cout << "\nOutput:\n" << strOutput << std::endl;
        
        for (size_t uiIndex = 0 ; uiIndex < strResult.size() ; uiIndex++)
            if (strResult[uiIndex] != strOutput[uiIndex])
                std::cout << "Difference at index " << uiIndex << " with character: " << strResult[uiIndex] << "\n";
        
    }
    
    return bResult;
    
}

std::string getResult(const std::string& strFileName) {
    
    //Read the file to seperate the contents of map and algorithm
    std::ifstream ifs(strFileName.c_str());
    
    //Get the formatted map (reading from current location until end of file)
    std::string strFormattedMap((std::istreambuf_iterator<char>(ifs) ),
                                (std::istreambuf_iterator<char>()    ));
    
    
    Policy* cPolicy = Policy::createPolicy(
                                
                                //The required type is for value iteration
                                kPolicyTypeValueIteration,
                                
                                //The Map the policy should be built on
                                Map(strFormattedMap),
                                
                                //The transition model the policy should decide by
                                ScoreModel(kScoreModelTypeSidewaysInnaccuracy),
                                
                                //The rewards the policy should consider
                                Rewards(kRewardTypeTileValuePenalty));
    
    std::stringstream test;
    test << *cPolicy;
    delete cPolicy;
    
    return test.str();
    
}

std::string getContents(const std::string& strFileName) {
    
    //Read the file to seperate the contents of map and algorithm
    std::ifstream ifs(strFileName.c_str());
    
    //Get the formatted map (reading from current location until end of file)
    return std::string((std::istreambuf_iterator<char>(ifs) ),
                       (std::istreambuf_iterator<char>()    ));
    
    
}

@end
