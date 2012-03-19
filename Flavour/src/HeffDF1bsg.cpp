/* 
 * File:   HeffDF1bsg.cpp
 * Author: stefano
 *
 * Created on 15 settembre 2011, 15.36
 */
    
#include "HeffDF1bsg.h"

using namespace gslpp;

HeffDF1bsg::HeffDF1bsg(const StandardModel & SM, StandardModelMatching & SM_Matching) :
        model(SM), modelmatching(SM_Matching), coeffbsg(10, NDR, NLO), 
        u(10, NDR, NLO, SM) {
}

HeffDF1bsg::~HeffDF1bsg() {
}

/*******************************************************************************
 * evoulution Wilson Coefficien b-> s gamma                                    * 
 * Misiak base                                                                 *
 ******************************************************************************/
vector<complex>** HeffDF1bsg::ComputeCoeffBsg(double mu, schemes scheme) {
    
    const std::vector<WilsonCoefficient>& mc = modelmatching.CMbsg();
    
    coeffbsg.setMu(mu); 
    
    orders ordDF1 = coeffbsg.getOrder();
    for (int i = 0; i < mc.size(); i++){
        for (int j = LO; j <= ordDF1; j++){
            for (int k = LO; k <= j; k++){
                coeffbsg.setCoeff(*coeffbsg.getCoeff(orders(j)) +
                    u.Df1Evolbsg(mu, mc[i].getMu(), orders(k), mc[i].getScheme()) *
                    (*(mc[i].getCoeff(orders(j - k)))), orders(j));
            }
        }
    }
    
    coeffbsg.setScheme(scheme);
   
    return coeffbsg.getCoeff();
}
