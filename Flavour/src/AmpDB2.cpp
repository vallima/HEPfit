/* 
 * File:   AmpDB2.cpp
 * Author: marco
 * 
 * Created on June 14, 2011, 2:40 PM
 */

#include "AmpDB2.h"

AmpDB2::AmpDB2(Flavour& Flavour) : myFlavour(Flavour) {
}

complex AmpDB2::Amp(orders order) {
    if (myFlavour.getHDF2().getCoeff().getOrder() < order)
        throw "DmBd::getThValue(): requires cofficient of order not computed";

    vector<complex> ** allcoeff = myFlavour.ComputeCoeff(
            myFlavour.getModel().getBBd().getMu(),
            myFlavour.getModel().getBBd().getScheme());

    vector<double> me(myFlavour.getModel().getBBd().getBpars());
    double MBd = myFlavour.getModel().getMesons(QCD::B_D).getMass();
    double Mb = myFlavour.getModel().getQuarks(QCD::BOTTOM).getMass();
    double Md = myFlavour.getModel().getQuarks(QCD::DOWN).getMass();
    double KBd = MBd/(Mb+Md)*MBd/(Mb+Md);
    double Fb = myFlavour.getModel().getMesons(QCD::B_D).getDecayconst();
    me(0) *= 1./3.*MBd*Fb*Fb;
    me(1) *= -5./24.*KBd*MBd*Fb*Fb;
    me(2) *= 1./24.*KBd*MBd*Fb*Fb;
    me(3) *= 1./4.*KBd*MBd*Fb*Fb;
    me(4) *= 1./12.*KBd*MBd*Fb*Fb;

    complex res(0.);
    switch(order) {
        case NLO:
            return((*(allcoeff[LO]) + *(allcoeff[NLO])) * me / HCUT);
        case LO:
            return((*(allcoeff[LO])) * me / HCUT);
        default:
            throw "AmpDB2::Amp(): order not implemented";
    }
}