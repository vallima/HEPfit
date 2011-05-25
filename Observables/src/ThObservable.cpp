/* 
 * File:   ThObservable.cpp
 * Author: silvest
 * 
 * Created on March 29, 2011, 12:15 PM
 */

#include "ThObservable.h"

ThObservable::ThObservable(const ThObsType& ObsType_i) : ObsType(ObsType_i), 
        SM(ObsType_i.getModel()) {
}

ThObservable::ThObservable(const ThObservable& orig) : ObsType(orig.ObsType),
        SM(orig.SM) {
}

ThObservable::~ThObservable() {
}