/* 
 * Copyright (C) 2016 HEPfit Collaboration
 *
 *
 * For the licensing terms see doc/COPYING.
 */

#include "GeneralTHDMquantities.h"

mH1_GTHDM::mH1_GTHDM(const StandardModel& SM_i)
: ThObservable(SM_i), myGTHDM(static_cast<const GeneralTHDM&> (SM_i))
{}

double mH1_GTHDM::computeThValue()
{
    if(myGTHDM.getMyGTHDMCache()->mH1_2 < 0.)
        return std::numeric_limits<double>::quiet_NaN();
    else
        return sqrt(myGTHDM.getMyGTHDMCache()->mH1_2);
}

mH2_GTHDM::mH2_GTHDM(const StandardModel& SM_i)
: ThObservable(SM_i), myGTHDM(static_cast<const GeneralTHDM&> (SM_i))
{}

double mH2_GTHDM::computeThValue()
{
    if(myGTHDM.getMyGTHDMCache()->mH2_2 < 0. || (myGTHDM.getMyGTHDMCache()->R32_GTHDM)*
            ((myGTHDM.getMyGTHDMCache()->R13_GTHDM)*(myGTHDM.getMyGTHDMCache()->R22_GTHDM) -
            (myGTHDM.getMyGTHDMCache()->R12_GTHDM)*(myGTHDM.getMyGTHDMCache()->R23_GTHDM)) < 0.00001)
        return std::numeric_limits<double>::quiet_NaN();
    else
        return sqrt(myGTHDM.getMyGTHDMCache()->mH2_2);
}

mH3_GTHDM::mH3_GTHDM(const StandardModel& SM_i)
: ThObservable(SM_i), myGTHDM(static_cast<const GeneralTHDM&> (SM_i))
{}

double mH3_GTHDM::computeThValue()
{
    if(myGTHDM.getMyGTHDMCache()->mH3_2 < 0. || (myGTHDM.getMyGTHDMCache()->R33_GTHDM)*
            ((myGTHDM.getMyGTHDMCache()->R13_GTHDM)*(myGTHDM.getMyGTHDMCache()->R22_GTHDM) -
            (myGTHDM.getMyGTHDMCache()->R12_GTHDM)*(myGTHDM.getMyGTHDMCache()->R23_GTHDM)) < 0.00001)
        return std::numeric_limits<double>::quiet_NaN();
    else
        return sqrt(myGTHDM.getMyGTHDMCache()->mH3_2);
}

mHlight_GTHDM::mHlight_GTHDM(const StandardModel& SM_i)
: ThObservable(SM_i), myGTHDM(static_cast<const GeneralTHDM&> (SM_i))
{}

double mHlight_GTHDM::computeThValue()
{
    if(myGTHDM.getMyGTHDMCache()->mHlight_2 < 0.)
        return std::numeric_limits<double>::quiet_NaN();
    else
        return sqrt(myGTHDM.getMyGTHDMCache()->mHlight_2);
}

mHmedium_GTHDM::mHmedium_GTHDM(const StandardModel& SM_i)
: ThObservable(SM_i), myGTHDM(static_cast<const GeneralTHDM&> (SM_i))
{}

double mHmedium_GTHDM::computeThValue()
{
    if(myGTHDM.getMyGTHDMCache()->mHmedium_2 < 0.)
        return std::numeric_limits<double>::quiet_NaN();
    else
        return sqrt(myGTHDM.getMyGTHDMCache()->mHmedium_2);
}

mHheavy_GTHDM::mHheavy_GTHDM(const StandardModel& SM_i)
: ThObservable(SM_i), myGTHDM(static_cast<const GeneralTHDM&> (SM_i))
{}

double mHheavy_GTHDM::computeThValue()
{
    if(myGTHDM.getMyGTHDMCache()->mHheavy_2 < 0.)
        return std::numeric_limits<double>::quiet_NaN();
    else
        return sqrt(myGTHDM.getMyGTHDMCache()->mHheavy_2);
}

mHp_GTHDM::mHp_GTHDM(const StandardModel& SM_i)
: ThObservable(SM_i), myGTHDM(static_cast<const GeneralTHDM&> (SM_i))
{}

double mHp_GTHDM::computeThValue()
{
    return sqrt(myGTHDM.getMyGTHDMCache()->mHp2_GTHDM);
}

mH3mmH2_GTHDM::mH3mmH2_GTHDM(const StandardModel& SM_i)
: ThObservable(SM_i), myGTHDM(static_cast<const GeneralTHDM&> (SM_i))
{}

double mH3mmH2_GTHDM::computeThValue()
{
    if(myGTHDM.getMyGTHDMCache()->mH3_2 < 0. || myGTHDM.getMyGTHDMCache()->mH2_2 < 0.)
        return std::numeric_limits<double>::quiet_NaN();
    else
        return sqrt(myGTHDM.getMyGTHDMCache()->mH3_2) - sqrt(myGTHDM.getMyGTHDMCache()->mH2_2);
}

mH3mmHp_GTHDM::mH3mmHp_GTHDM(const StandardModel& SM_i)
: ThObservable(SM_i), myGTHDM(static_cast<const GeneralTHDM&> (SM_i))
{}

double mH3mmHp_GTHDM::computeThValue()
{
    if(myGTHDM.getMyGTHDMCache()->mH3_2 < 0.)
        return std::numeric_limits<double>::quiet_NaN();
    else
        return sqrt(myGTHDM.getMyGTHDMCache()->mH3_2) - sqrt(myGTHDM.getMyGTHDMCache()->mHp2_GTHDM);
}

mH3mmH1_GTHDM::mH3mmH1_GTHDM(const StandardModel& SM_i)
: ThObservable(SM_i), myGTHDM(static_cast<const GeneralTHDM&> (SM_i))
{}

double mH3mmH1_GTHDM::computeThValue()
{
    if(myGTHDM.getMyGTHDMCache()->mH3_2 < 0. || myGTHDM.getMyGTHDMCache()->mH1_2 < 0.)
        return std::numeric_limits<double>::quiet_NaN();
    else
        return sqrt(myGTHDM.getMyGTHDMCache()->mH3_2) - sqrt(myGTHDM.getMyGTHDMCache()->mH1_2);
}

mH2mmHp_GTHDM::mH2mmHp_GTHDM(const StandardModel& SM_i)
: ThObservable(SM_i), myGTHDM(static_cast<const GeneralTHDM&> (SM_i))
{}

double mH2mmHp_GTHDM::computeThValue()
{
    if(myGTHDM.getMyGTHDMCache()->mH2_2 < 0.)
        return std::numeric_limits<double>::quiet_NaN();
    else
        return sqrt(myGTHDM.getMyGTHDMCache()->mH2_2) - sqrt(myGTHDM.getMyGTHDMCache()->mHp2_GTHDM);   
}

mH2mmH1_GTHDM::mH2mmH1_GTHDM(const StandardModel& SM_i)
: ThObservable(SM_i), myGTHDM(static_cast<const GeneralTHDM&> (SM_i))
{}

double mH2mmH1_GTHDM::computeThValue()
{
    if(myGTHDM.getMyGTHDMCache()->mH2_2 < 0. || myGTHDM.getMyGTHDMCache()->mH1_2 < 0.)
        return std::numeric_limits<double>::quiet_NaN();
    else
        return sqrt(myGTHDM.getMyGTHDMCache()->mH2_2) - sqrt(myGTHDM.getMyGTHDMCache()->mH1_2);
}

mHpmmH1_GTHDM::mHpmmH1_GTHDM(const StandardModel& SM_i)
: ThObservable(SM_i), myGTHDM(static_cast<const GeneralTHDM&> (SM_i))
{}

double mHpmmH1_GTHDM::computeThValue()
{
    if(myGTHDM.getMyGTHDMCache()->mH1_2 < 0.)
        return std::numeric_limits<double>::quiet_NaN();
    else
        return sqrt(myGTHDM.getMyGTHDMCache()->mHp2_GTHDM) - sqrt(myGTHDM.getMyGTHDMCache()->mH1_2);   
}


mH1sq_GTHDM::mH1sq_GTHDM(const StandardModel& SM_i)
: ThObservable(SM_i), myGTHDM(static_cast<const GeneralTHDM&> (SM_i))
{}

double mH1sq_GTHDM::computeThValue()
{
    return myGTHDM.getMyGTHDMCache()->mH1_2;
}

mH2sq_GTHDM::mH2sq_GTHDM(const StandardModel& SM_i)
: ThObservable(SM_i), myGTHDM(static_cast<const GeneralTHDM&> (SM_i))
{}

double mH2sq_GTHDM::computeThValue()
{
    return myGTHDM.getMyGTHDMCache()->mH2_2;
}

mH3sq_GTHDM::mH3sq_GTHDM(const StandardModel& SM_i)
: ThObservable(SM_i), myGTHDM(static_cast<const GeneralTHDM&> (SM_i))
{}

double mH3sq_GTHDM::computeThValue()
{
    return myGTHDM.getMyGTHDMCache()->mH3_2;
}

Msq11_GTHDM::Msq11_GTHDM(const StandardModel& SM_i)
: ThObservable(SM_i), myGTHDM(static_cast<const GeneralTHDM&> (SM_i))
{}

double Msq11_GTHDM::computeThValue()
{
    return myGTHDM.getMyGTHDMCache()->M11_2;
}

Msq12_GTHDM::Msq12_GTHDM(const StandardModel& SM_i)
: ThObservable(SM_i), myGTHDM(static_cast<const GeneralTHDM&> (SM_i))
{}

double Msq12_GTHDM::computeThValue()
{
    return myGTHDM.getMyGTHDMCache()->M12_2;
}

Msq13_GTHDM::Msq13_GTHDM(const StandardModel& SM_i)
: ThObservable(SM_i), myGTHDM(static_cast<const GeneralTHDM&> (SM_i))
{}

double Msq13_GTHDM::computeThValue()
{
    return myGTHDM.getMyGTHDMCache()->M13_2;
}

Msq22_GTHDM::Msq22_GTHDM(const StandardModel& SM_i)
: ThObservable(SM_i), myGTHDM(static_cast<const GeneralTHDM&> (SM_i))
{}

double Msq22_GTHDM::computeThValue()
{
    return myGTHDM.getMyGTHDMCache()->M22_2;
}

Msq23_GTHDM::Msq23_GTHDM(const StandardModel& SM_i)
: ThObservable(SM_i), myGTHDM(static_cast<const GeneralTHDM&> (SM_i))
{}

double Msq23_GTHDM::computeThValue()
{
    return myGTHDM.getMyGTHDMCache()->M23_2;
}

Msq33_GTHDM::Msq33_GTHDM(const StandardModel& SM_i)
: ThObservable(SM_i), myGTHDM(static_cast<const GeneralTHDM&> (SM_i))
{}

double Msq33_GTHDM::computeThValue()
{
    return myGTHDM.getMyGTHDMCache()->M33_2;
}

M2_GTHDM::M2_GTHDM(const StandardModel& SM_i)
: ThObservable(SM_i),myGTHDM(static_cast<const GeneralTHDM&> (SM_i))
{}

double M2_GTHDM::computeThValue()
{
    return myGTHDM.getMyGTHDMCache()->M2_GTHDM;
}

m11_2_GTHDM::m11_2_GTHDM(const StandardModel& SM_i)
: ThObservable(SM_i),myGTHDM(static_cast<const GeneralTHDM&> (SM_i))
{}

double m11_2_GTHDM::computeThValue()
{
    return myGTHDM.getMyGTHDMCache()->m11_2_GTHDM;
}

m22_2_GTHDM::m22_2_GTHDM(const StandardModel& SM_i)
: ThObservable(SM_i),myGTHDM(static_cast<const GeneralTHDM&> (SM_i))
{}

double m22_2_GTHDM::computeThValue()
{
    return myGTHDM.getMyGTHDMCache()->m22_2_GTHDM;
}

Imm12_2_GTHDM::Imm12_2_GTHDM(const StandardModel& SM_i)
: ThObservable(SM_i),myGTHDM(static_cast<const GeneralTHDM&> (SM_i))
{}

double Imm12_2_GTHDM::computeThValue()
{
    return myGTHDM.getMyGTHDMCache()->Imm12_2_GTHDM;
}

lambda1_GTHDM::lambda1_GTHDM(const StandardModel& SM_i)
: ThObservable(SM_i),myGTHDM(static_cast<const GeneralTHDM&> (SM_i))
{}

double lambda1_GTHDM::computeThValue()
{
    return myGTHDM.getMyGTHDMCache()->lambda1_GTHDM;
}

lambda2_GTHDM::lambda2_GTHDM(const StandardModel& SM_i)
: ThObservable(SM_i),myGTHDM(static_cast<const GeneralTHDM&> (SM_i))
{}

double lambda2_GTHDM::computeThValue()
{
    return myGTHDM.getMyGTHDMCache()->lambda2_GTHDM;
}

lambda3_GTHDM::lambda3_GTHDM(const StandardModel& SM_i)
: ThObservable(SM_i),myGTHDM(static_cast<const GeneralTHDM&> (SM_i))
{}

double lambda3_GTHDM::computeThValue()
{
    return myGTHDM.getMyGTHDMCache()->lambda3_GTHDM;
}

lambda4_GTHDM::lambda4_GTHDM(const StandardModel& SM_i)
: ThObservable(SM_i),myGTHDM(static_cast<const GeneralTHDM&> (SM_i))
{}

double lambda4_GTHDM::computeThValue()
{
    return myGTHDM.getMyGTHDMCache()->lambda4_GTHDM;
}

Relambda5_GTHDM::Relambda5_GTHDM(const StandardModel& SM_i)
: ThObservable(SM_i),myGTHDM(static_cast<const GeneralTHDM&> (SM_i))
{}

double Relambda5_GTHDM::computeThValue()
{
    return myGTHDM.getMyGTHDMCache()->Relambda5_GTHDM;
}

v1_GTHDM::v1_GTHDM(const StandardModel& SM_i)
: ThObservable(SM_i), myGTHDM(static_cast<const GeneralTHDM*> (&SM_i))
{}

double v1_GTHDM::computeThValue()
{
    double v = myGTHDM->v();
    double cosb = myGTHDM->getcosb();

    return (v*cosb);
}


v2_GTHDM::v2_GTHDM(const StandardModel& SM_i)
: ThObservable(SM_i), myGTHDM(static_cast<const GeneralTHDM*> (&SM_i))
{}

double v2_GTHDM::computeThValue()
{
    double v = myGTHDM->v();
    double sinb = myGTHDM->getsinb();

    return (v*sinb);
}

//
//Resigmau::Resigmau(const StandardModel& SM_i)
//: ThObservable(SM_i), myGTHDM(static_cast<const GeneralTHDM*> (&SM_i))
//{}
//
//double Resigmau::computeThValue()
//{
//    double v = myGTHDM->v();
//    double Ytu_33r = myGTHDM->getYtu_33r();
//    double cosb = myGTHDM->getcosb();
//    double mtop = myGTHDM->getQuarks(QCD::TOP).getMass();
//    double tanb = myGTHDM->gettanb();
//
//    return v*Ytu_33r/(sqrt(2.)*cosb*mtop)-tanb;
//}
