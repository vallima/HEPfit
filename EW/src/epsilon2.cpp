/* 
 * File:   epsilon2.cpp
 * Author: mishima
 */

#include "epsilon2.h"


double epsilon2::getThValue() {  
    double DeltaRhoPrime = 2.0*( sqrt(SM.rhoZ_l(SM.ELECTRON).abs()) - 1.0 );
    double DeltaKappaPrime = myEW.sin2thetaEff(SM.ELECTRON)/SM.s02() - 1.0;
    double DeltaRW = 1.0 - M_PI*SM.alphaMz()
                /(sqrt(2.0)*SM.getGF()*SM.getMz()*SM.getMz()*SM.sW2()*SM.cW2());
    
    return ( SM.c02()*DeltaRhoPrime + SM.s02()*DeltaRW/(SM.c02() - SM.s02()) 
             - 2.0*SM.s02()*DeltaKappaPrime ); 
}
 

