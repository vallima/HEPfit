/* 
 * File:   InputParser.h
 * Author: silvest
 *
 * Created on March 15, 2011, 2:36 PM
 */

#ifndef INPUTPARSER_H
#define	INPUTPARSER_H

#include "ThFactory.h"
#include <Observable.h>
#include <Observable2D.h>
#include <ThObservable.h>
#include <ModelParameter.h>
#include <StandardModel.h>
#include <Flavour.h>
#include <iostream>
#include <fstream>
#include <istream>
#include <boost/tokenizer.hpp>
#include <string>

class InputParser {
public:
    InputParser();
    InputParser(const InputParser& orig);
    virtual ~InputParser();
    std::string ReadParameters(const std::string filename,
            std::vector<ModelParameter>& ModelPars,
            std::vector<Observable>& Observables,
            std::vector<Observable2D>& Observables2D);

    StandardModel* GetMyModel() const {
        return myModel;
    }
private:
    StandardModel* myModel; 
    Flavour* myFlavour;
    ThFactory* thf;
};

#endif	/* INPUTPARSER_H */