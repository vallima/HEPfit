/* 
 * Copyright (C) 2017 HEPfit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#include "gslpp.h"
#include "GMcache.h"

GMcache::GMcache(const StandardModel& SM_i)
        : unitarityeigenvalues(4, 0.), myGM(static_cast<const GeorgiMachacek*> (&SM_i))
{
//    myRunnerGM=new RunnerGM(SM_i);
}

GMcache::~GMcache()
{
//  delete myRunnerGM;
}
//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
int GMcache::CacheCheck(const gslpp::complex cache[][CacheSize], 
                          const int NumPar, const double params[]) const {
    bool bCache;
    for(int i=0; i<CacheSize; i++) {
        bCache = true;
        for(int j=0; j<NumPar; j++)
            bCache &= (params[j] == cache[j][i].real());
        if (bCache) return i;
    }
    return -1;
}
//
//int GMcache::CacheCheckReal(const double cache[][CacheSize], 
//                          const int NumPar, const double params[]) const {
//    bool bCache;
//    for(int i=0; i<CacheSize; i++) {
//        bCache = true;
//        for(int j=0; j<NumPar; j++)
//            bCache &= (params[j] == cache[j][i]);
//        if (bCache) return i;
//    }
//    return -1;
//}

void GMcache::CacheShift(gslpp::complex cache[][CacheSize], const int NumPar, 
                           const double params[], const gslpp::complex newResult) const {
    // shift old parameters and result
    for(int i=CacheSize-1; i>0; i--)
        for(int j=0; j<NumPar+1; j++)
            cache[j][i] = cache[j][i-1];

    // store new parameters and result
    for(int j=0; j<NumPar; j++) {
        cache[j][0] = gslpp::complex(params[j], 0.0, false);
        cache[NumPar][0] = newResult;
    }
}

gslpp::complex GMcache::I_h_U(const double mHl2, const double Mu, const double Mc, const double Mt) const {
    int NumPar = 4;
    double params[] = {mHl2, Mu, Mc, Mt};

    int i = CacheCheck(I_h_U_cache, NumPar, params);
    if (i>=0) {
        return ( I_h_U_cache[NumPar][i] );
    } else {
    	double TAUu=4.0*Mu*Mu/mHl2;
    	double TAUc=4.0*Mc*Mc/mHl2;
    	double TAUt=4.0*Mt*Mt/mHl2;
        gslpp::complex newResult = -(8./3.)*(TAUu*(1.0+(1.0-TAUu)*f_func(TAUu))
                         +TAUc*(1.0+(1.0-TAUc)*f_func(TAUc))+TAUt*(1.0+(1.0-TAUt)*f_func(TAUt)));
        CacheShift(I_h_U_cache, NumPar, params, newResult);
        return newResult;
    }
}

gslpp::complex GMcache::I_HH_U(const double mHh2, const double Mc, const double Mt) const {
    int NumPar = 3;
    double params[] = {mHh2, Mc, Mt};

    int i = CacheCheck(I_HH_U_cache, NumPar, params);
    if (i>=0) {
        return ( I_HH_U_cache[NumPar][i] );
    } else {
    	double TAUc=4.0*Mc*Mc/mHh2;
    	double TAUt=4.0*Mt*Mt/mHh2;
        gslpp::complex newResult = -(8./3.)*(TAUc*(1.0+(1.0-TAUc)*f_func(TAUc))
                      +TAUt*(1.0+(1.0-TAUt)*f_func(TAUt)));
        CacheShift(I_HH_U_cache, NumPar, params, newResult);
        return newResult;
    }
}

gslpp::complex GMcache::I_A_U(const double mA2, const double Mc, const double Mt) const {
    int NumPar = 3;
    double params[] = {mA2, Mc, Mt};

    int i = CacheCheck(I_A_U_cache, NumPar, params);
    if (i>=0) {
        return ( I_A_U_cache[NumPar][i] );
    } else {
    	double TAUc=4.0*Mc*Mc/mA2;
    	double TAUt=4.0*Mt*Mt/mA2;
        gslpp::complex newResult = -(8./3.)*(TAUc*f_func(TAUc)+TAUt*f_func(TAUt));
        CacheShift(I_A_U_cache, NumPar, params, newResult);
        return newResult;
    }
}

gslpp::complex GMcache::I_h_D(const double mHl2, const double Md, const double Ms, const double Mb) const {
    int NumPar = 4;
    double params[] = {mHl2, Md, Ms, Mb};

    int i = CacheCheck(I_h_D_cache, NumPar, params);
    if (i>=0) {
        return ( I_h_D_cache[NumPar][i] );
    } else {
    	double TAUd=4.0*Md*Md/mHl2;
    	double TAUs=4.0*Ms*Ms/mHl2;
    	double TAUb=4.0*Mb*Mb/mHl2;
        gslpp::complex newResult = -(2./3.)*(TAUd*(1.0+(1.0-TAUd)*f_func(TAUd))
                         +TAUs*(1.0+(1.0-TAUs)*f_func(TAUs))+TAUb*(1.0+(1.0-TAUb)*f_func(TAUb)));
        CacheShift(I_h_D_cache, NumPar, params, newResult);
        return newResult;
    }
}

gslpp::complex GMcache::I_HH_D(const double mHh2, const double Ms, const double Mb) const {
    int NumPar = 3;
    double params[] = {mHh2, Ms, Mb};

    int i = CacheCheck(I_HH_D_cache, NumPar, params);
    if (i>=0) {
        return ( I_HH_D_cache[NumPar][i] );
    } else {
    	double TAUs=4.0*Ms*Ms/mHh2;
    	double TAUb=4.0*Mb*Mb/mHh2;
        gslpp::complex newResult = -(2./3.)*(TAUs*(1.0+(1.0-TAUs)*f_func(TAUs))
                      +TAUb*(1.0+(1.0-TAUb)*f_func(TAUb)));
        CacheShift(I_HH_D_cache, NumPar, params, newResult);
        return newResult;
    }
}

gslpp::complex GMcache::I_A_D(const double mA2, const double Ms, const double Mb) const {
    int NumPar = 3;
    double params[] = {mA2, Ms, Mb};

    int i = CacheCheck(I_A_D_cache, NumPar, params);
    if (i>=0) {
        return ( I_A_D_cache[NumPar][i] );
    } else {
    	double TAUs=4.0*Ms*Ms/mA2;
    	double TAUb=4.0*Mb*Mb/mA2;
        gslpp::complex newResult = -(2./3.)*(TAUs*f_func(TAUs)+TAUb*f_func(TAUb));
        CacheShift(I_A_D_cache, NumPar, params, newResult);
        return newResult;
    }
}

gslpp::complex GMcache::I_h_L(const double mHl2, const double Me, const double Mmu, const double Mtau) const {
    int NumPar = 4;
    double params[] = {mHl2, Me, Mmu, Mtau};

    int i = CacheCheck(I_h_L_cache, NumPar, params);
    if (i>=0) {
        return ( I_h_L_cache[NumPar][i] );
    } else {
    	double TAUe=4.0*Me*Me/mHl2;
    	double TAUmu=4.0*Mmu*Mmu/mHl2;
    	double TAUtau=4.0*Mtau*Mtau/mHl2;
        gslpp::complex newResult = -2.0*(TAUe*(1.0+(1.0-TAUe)*f_func(TAUe))
                         +TAUmu*(1.0+(1.0-TAUmu)*f_func(TAUmu))
                         +TAUtau*(1.0+(1.0-TAUtau)*f_func(TAUtau)));
        CacheShift(I_h_L_cache, NumPar, params, newResult);
        return newResult;
    }
}

gslpp::complex GMcache::I_HH_L(const double mHh2, const double Mmu, const double Mtau) const {
    int NumPar = 3;
    double params[] = {mHh2, Mmu, Mtau};

    int i = CacheCheck(I_HH_L_cache, NumPar, params);
    if (i>=0) {
        return ( I_HH_L_cache[NumPar][i] );
    } else {
    	double TAUmu=4.0*Mmu*Mmu/mHh2;
    	double TAUtau=4.0*Mtau*Mtau/mHh2;
        gslpp::complex newResult = -2.0*(TAUmu*(1.0+(1.0-TAUmu)*f_func(TAUmu))+
                           TAUtau*(1.0+(1.0-TAUtau)*f_func(TAUtau)));
        CacheShift(I_HH_L_cache, NumPar, params, newResult);
        return newResult;
    }
}

gslpp::complex GMcache::I_A_L(const double mA2, const double Mmu, const double Mtau) const {
    int NumPar = 3;
    double params[] = {mA2, Mmu, Mtau};

    int i = CacheCheck(I_A_L_cache, NumPar, params);
    if (i>=0) {
        return ( I_A_L_cache[NumPar][i] );
    } else {
    	double TAUmu=4.0*Mmu*Mmu/mA2;
    	double TAUtau=4.0*Mtau*Mtau/mA2;
        gslpp::complex newResult = -2.0*(TAUmu*f_func(TAUmu)+TAUtau*f_func(TAUtau));
        CacheShift(I_A_L_cache, NumPar, params, newResult);
        return newResult;
    }
}

gslpp::complex GMcache::I_H_W(const double mH, const double MW) const {
    int NumPar = 2;
    double params[] = {mH, MW};

    int i = CacheCheck(I_H_W_cache, NumPar, params);
    if (i>=0) {
        return ( I_H_W_cache[NumPar][i] );
    } else {
        double TAUw=4.0*MW*MW/(mH*mH);
        gslpp::complex newResult = 2.0 + 3.0*TAUw + 3.0*TAUw*(2.0-TAUw)*f_func(TAUw);
        CacheShift(I_H_W_cache, NumPar, params, newResult);
        return newResult;
    }
}

gslpp::complex GMcache::I_H_Hp(const double mHp2, const double mH) const {
    int NumPar = 2;
    double params[] = {mHp2, mH};

    int i = CacheCheck(I_H_Hp_cache, NumPar, params);
    if (i>=0) {
        return ( I_H_Hp_cache[NumPar][i] );
    } else {
        double TAUhp=4.0*mHp2/(mH*mH);
        gslpp::complex newResult = -TAUhp*(1.0-TAUhp*f_func(TAUhp));
        CacheShift(I_H_Hp_cache, NumPar, params, newResult);
        return newResult;
    }
}

gslpp::complex GMcache::A_h_U(const double mHl2, const double cW2, const double Mu, const double Mc, const double Mt, const double MZ) const {
    int NumPar = 6;
    double params[] = {mHl2, cW2, Mu, Mc, Mt, MZ};

    int i = CacheCheck(A_h_U_cache, NumPar, params);
    if (i>=0) {
        return ( A_h_U_cache[NumPar][i] );
    } else {
    	double TAUu=4.0*Mu*Mu/mHl2;
    	double TAUc=4.0*Mc*Mc/mHl2;
    	double TAUt=4.0*Mt*Mt/mHl2;
    	double LAMu=4.0*Mu*Mu/(MZ*MZ);
    	double LAMc=4.0*Mc*Mc/(MZ*MZ);
    	double LAMt=4.0*Mt*Mt/(MZ*MZ);
	double sW2=1.0-cW2;
        gslpp::complex newResult = -4.0*(1.0/2.0-4.0/3.0*sW2)*(Int1(TAUu,LAMu)+Int1(TAUc,LAMc)
                           +Int1(TAUt,LAMt)-Int2(TAUu,LAMu)-Int2(TAUc,LAMc)-Int2(TAUt,LAMt));
        CacheShift(A_h_U_cache, NumPar, params, newResult);
        return newResult;
    }
}

gslpp::complex GMcache::A_HH_U(const double mHh2, const double cW2, const double Mc, const double Mt, const double MZ) const {
    int NumPar = 5;
    double params[] = {mHh2, cW2, Mc, Mt, MZ};

    int i = CacheCheck(A_HH_U_cache, NumPar, params);
    if (i>=0) {
        return ( A_HH_U_cache[NumPar][i] );
    } else {
    	double TAUc=4.0*Mc*Mc/mHh2;
    	double TAUt=4.0*Mt*Mt/mHh2;
    	double LAMc=4.0*Mc*Mc/(MZ*MZ);
    	double LAMt=4.0*Mt*Mt/(MZ*MZ);
	double sW2=1.0-cW2;
        gslpp::complex newResult = -4.0*(1.0/2.0-4.0/3.0*sW2)*(Int1(TAUc,LAMc)-Int2(TAUc,LAMc)
                                         +Int1(TAUt,LAMt)-Int2(TAUt,LAMt));
        CacheShift(A_HH_U_cache, NumPar, params, newResult);
        return newResult;
    }
}

gslpp::complex GMcache::A_A_U(const double mA2, const double cW2, const double Mc, const double Mt, const double MZ) const {
    int NumPar = 5;
    double params[] = {mA2, cW2, Mc, Mt, MZ};

    int i = CacheCheck(A_A_U_cache, NumPar, params);
    if (i>=0) {
        return ( A_A_U_cache[NumPar][i] );
    } else {
    	double TAUc=4.0*Mc*Mc/mA2;
    	double TAUt=4.0*Mt*Mt/mA2;
    	double LAMc=4.0*Mc*Mc/(MZ*MZ);
    	double LAMt=4.0*Mt*Mt/(MZ*MZ);
	double sW2=1.0-cW2;
        gslpp::complex newResult = -4.0*(1.0/2.0-4.0/3.0*sW2)*(-Int2(TAUc,LAMc)-Int2(TAUt,LAMt))/sqrt(sW2*cW2);
        CacheShift(A_A_U_cache, NumPar, params, newResult);
        return newResult;
    }
}

gslpp::complex GMcache::A_h_D(const double mHl2, const double cW2, const double Md, const double Ms, const double Mb, const double MZ) const {
    int NumPar = 6;
    double params[] = {mHl2, cW2, Md, Ms, Mb, MZ};

    int i = CacheCheck(A_h_D_cache, NumPar, params);
    if (i>=0) {
        return ( A_h_D_cache[NumPar][i] );
    } else {
    	double TAUd=4.0*Md*Md/mHl2;
    	double TAUs=4.0*Ms*Ms/mHl2;
    	double TAUb=4.0*Mb*Mb/mHl2;
    	double LAMd=4.0*Md*Md/(MZ*MZ);
    	double LAMs=4.0*Ms*Ms/(MZ*MZ);
	double LAMb=4.0*Mb*Mb/(MZ*MZ);
	double sW2=1.0-cW2;
        gslpp::complex newResult = 2.0*(-1.0/2.0+2.0/3.0*sW2)*(Int1(TAUd,LAMd)+Int1(TAUs,LAMs)
                           +Int1(TAUb,LAMb)-Int2(TAUd,LAMd)-Int2(TAUs,LAMs)-Int2(TAUb,LAMb));
        CacheShift(A_h_D_cache, NumPar, params, newResult);
        return newResult;
    }
}

gslpp::complex GMcache::A_HH_D(const double mHh2, const double cW2, const double Ms, const double Mb, const double MZ) const {
    int NumPar = 5;
    double params[] = {mHh2, cW2, Ms, Mb, MZ};

    int i = CacheCheck(A_HH_D_cache, NumPar, params);
    if (i>=0) {
        return ( A_HH_D_cache[NumPar][i] );
    } else {
    	double TAUs=4.0*Ms*Ms/mHh2;
    	double TAUb=4.0*Mb*Mb/mHh2;
    	double LAMs=4.0*Ms*Ms/(MZ*MZ);
	double LAMb=4.0*Mb*Mb/(MZ*MZ);
	double sW2=1.0-cW2;
        gslpp::complex newResult = 2.0*(-1.0/2.0+2.0/3.0*sW2)*(Int1(TAUs,LAMs)-Int2(TAUs,LAMs)
                                          +Int1(TAUb,LAMb)-Int2(TAUb,LAMb));
        CacheShift(A_HH_D_cache, NumPar, params, newResult);
        return newResult;
    }
}

gslpp::complex GMcache::A_A_D(const double mA2, const double cW2, const double Ms, const double Mb, const double MZ) const {
    int NumPar = 5;
    double params[] = {mA2, cW2, Ms, Mb, MZ};

    int i = CacheCheck(A_A_D_cache, NumPar, params);
    if (i>=0) {
        return ( A_A_D_cache[NumPar][i] );
    } else {
    	double TAUs=4.0*Ms*Ms/mA2;
    	double TAUb=4.0*Mb*Mb/mA2;
    	double LAMs=4.0*Ms*Ms/(MZ*MZ);
	double LAMb=4.0*Mb*Mb/(MZ*MZ);
	double sW2=1.0-cW2;
        gslpp::complex newResult = 2.0*(-1.0/2.0+2.0/3.0*sW2)*(-Int2(TAUs,LAMs)-Int2(TAUb,LAMb))/sqrt(sW2*cW2);
        CacheShift(A_A_D_cache, NumPar, params, newResult);
        return newResult;
    }
}

gslpp::complex GMcache::A_h_L(const double mHl2, const double cW2, const double Me, const double Mmu, const double Mtau, const double MZ) const {
    int NumPar = 6;
    double params[] = {mHl2, cW2, Me, Mmu, Mtau, MZ};

    int i = CacheCheck(A_h_L_cache, NumPar, params);
    if (i>=0) {
        return ( A_h_L_cache[NumPar][i] );
    } else {
    	double TAUe=4.0*Me*Me/mHl2;
    	double TAUmu=4.0*Mmu*Mmu/mHl2;
    	double TAUtau=4.0*Mtau*Mtau/mHl2;
    	double LAMe=4.0*Me*Me/(MZ*MZ);
    	double LAMmu=4.0*Mmu*Mmu/(MZ*MZ);
	double LAMtau=4.0*Mtau*Mtau/(MZ*MZ);
	double sW2=1.0-cW2;
        gslpp::complex newResult = 2.0*(-1.0/2.0+2.0*sW2)*(Int1(TAUe,LAMe)+Int1(TAUmu,LAMmu)
                            +Int1(TAUtau,LAMtau)-Int2(TAUe,LAMe)-Int2(TAUmu,LAMmu)
                            -Int2(TAUtau,LAMtau));
        CacheShift(A_h_L_cache, NumPar, params, newResult);
        return newResult;
    }
}

gslpp::complex GMcache::A_HH_L(const double mHh2, const double cW2, const double Mmu, const double Mtau, const double MZ) const {
    int NumPar = 5;
    double params[] = {mHh2, cW2, Mmu, Mtau, MZ};

    int i = CacheCheck(A_HH_L_cache, NumPar, params);
    if (i>=0) {
        return ( A_HH_L_cache[NumPar][i] );
    } else {
    	double TAUmu=4.0*Mmu*Mmu/mHh2;
    	double TAUtau=4.0*Mtau*Mtau/mHh2;
    	double LAMmu=4.0*Mmu*Mmu/(MZ*MZ);
	double LAMtau=4.0*Mtau*Mtau/(MZ*MZ);
	double sW2=1.0-cW2;
        gslpp::complex newResult = 2.0*(-1.0/2.0+2.0*sW2)*(Int1(TAUmu,LAMmu)-Int2(TAUmu,LAMmu)
                                      +Int1(TAUtau,LAMtau)-Int2(TAUtau,LAMtau));
        CacheShift(A_HH_L_cache, NumPar, params, newResult);
        return newResult;
    }
}

gslpp::complex GMcache::A_A_L(const double mA2, const double cW2, const double Mmu, const double Mtau, const double MZ) const {
    int NumPar = 5;
    double params[] = {mA2, cW2, Mmu, Mtau, MZ};

    int i = CacheCheck(A_A_L_cache, NumPar, params);
    if (i>=0) {
        return ( A_A_L_cache[NumPar][i] );
    } else {
    	double TAUmu=4.0*Mmu*Mmu/mA2;
    	double TAUtau=4.0*Mtau*Mtau/mA2;
    	double LAMmu=4.0*Mmu*Mmu/(MZ*MZ);
	double LAMtau=4.0*Mtau*Mtau/(MZ*MZ);
	double sW2=1.0-cW2;
        gslpp::complex newResult = 2.0*(-1.0/2.0+2.0*sW2)*(-Int2(TAUmu,LAMmu)-Int2(TAUtau,LAMtau))/sqrt(sW2*cW2);
        CacheShift(A_A_L_cache, NumPar, params, newResult);
        return newResult;
    }
}

gslpp::complex GMcache::A_H_W(const double mH, const double cW2, const double MW, const double MZ) const {
    int NumPar = 4;
    double params[] = {mH, cW2, MW, MZ};

    int i = CacheCheck(A_H_W_cache, NumPar, params);
    if (i>=0) {
        return ( A_H_W_cache[NumPar][i] );
    } else {
        double TAUw=4.0*MW*MW/(mH*mH);
        double LAMw=4.0*MW*MW/(MZ*MZ);
	double sW2=1.0-cW2;
        gslpp::complex newResult = -sqrt(cW2/sW2)*(4.0*(3.0-sW2/cW2)*Int2(TAUw,LAMw)
                            +((1.0+2.0/TAUw)*sW2/cW2-(5.0+2.0/TAUw))*Int1(TAUw,LAMw));
        CacheShift(A_H_W_cache, NumPar, params, newResult);
        return newResult;
    }
}

gslpp::complex GMcache::A_H_Hp(const double mHp2, const double mH, const double cW2, const double MZ) const {
    int NumPar = 4;
    double params[] = {mHp2, mH, cW2, MZ};

    int i = CacheCheck(A_H_Hp_cache, NumPar, params);
    if (i>=0) {
        return ( A_H_Hp_cache[NumPar][i] );
    } else {
        double TAUhp=4.0*mHp2/(mH*mH);
        double LAMhp=4.0*mHp2/(MZ*MZ);
	double sW2=1.0-cW2;
        gslpp::complex newResult = (1.0-2.0*sW2)/sqrt(cW2*sW2)*Int1(TAUhp,LAMhp);
        CacheShift(A_H_Hp_cache, NumPar, params, newResult);
        return newResult;
    }
}

gslpp::complex GMcache::f_func(const double x) const{
    if(x<1) {
    gslpp::complex z = -gslpp::complex::i()*M_PI;
    return -pow(log((1.0+sqrt(1.0-x))/(1.0-sqrt(1.0-x)))+z,2)/4.0;
    }
    else {
        return pow(asin(sqrt(1.0/x)),2);
    }
}

gslpp::complex GMcache::g_func(const double x) const{
    if(x<1) {
    gslpp::complex z = -gslpp::complex::i()*M_PI;
    gslpp::complex gs1 = sqrt(1.0-x)*(log((1.0+sqrt(1.0-x))/(1.0-sqrt(1.0-x)))+z)/2.0;
    return gs1;
    }
    else {
        gslpp::complex gg1 = sqrt(x-1.0)*asin(sqrt(1.0/x));
        return gg1;
    }
}

gslpp::complex GMcache::Int1(const double tau, const double lambda) const{
    return tau*lambda/(tau-lambda)/2.0+tau*tau*lambda*lambda/((tau-lambda)
           *(tau-lambda))/2.0*(f_func(tau)-f_func(lambda))+tau*tau*lambda/((tau-lambda)
           *(tau-lambda))*(g_func(tau)-g_func(lambda));
}

gslpp::complex GMcache::Int2(const double tau, const double lambda) const{
    return -tau*lambda/(tau-lambda)/2.0*(f_func(tau)-f_func(lambda));
}

void GMcache::computeSignalStrengthQuantities()
{
    double Mt = myGM->getQuarks(QCD::TOP).getMass();
    double Mb = myGM->getQuarks(QCD::BOTTOM).getMass();
    double Mc = myGM->getQuarks(QCD::CHARM).getMass();
    double Ms = myGM->getQuarks(QCD::STRANGE).getMass();
    double Mu = myGM->getQuarks(QCD::UP).getMass();
    double Md = myGM->getQuarks(QCD::DOWN).getMass();
    double Mtau = myGM->getLeptons(StandardModel::TAU).getMass();
    double Mmu = myGM->getLeptons(StandardModel::MU).getMass();
    double Me = myGM->getLeptons(StandardModel::ELECTRON).getMass();
    double MW = myGM->Mw_tree();
    double cW2 = myGM->c02();
    double sW2=1.0-cW2;

    double BrSM_htobb = 5.77e-1;
    double BrSM_htotautau = 6.32e-2;
    double BrSM_htogaga = 2.28e-3;
    double BrSM_htoWW = 2.15e-1;
    double BrSM_htoZZ = 2.64e-2;
    double BrSM_htogg = 8.57e-2;
    double BrSM_htoZga = 1.54e-3;
    double BrSM_htocc = 2.91e-2;

    rh_QuQu = cosa*cosa/(sinb*sinb);
    rh_VV = sin(bma)*sin(bma);
    rh_QdQd = 0.0;
    rh_ll = 0.0;
    rh_gg = 0.0;
    double ghHpHm = 0.0;

    //rh_gaga formula = fabs(I_h_F+I_h_W+I_h_Hp)^2 / fabs(I_hSM_F+I_hSM_W)^2

    gslpp::complex I_h_F = 0.0;
    gslpp::complex fermU = I_h_U(mhsq,Mu,Mc,Mt);
    gslpp::complex fermD = I_h_D(mhsq,Md,Ms,Mb);
    gslpp::complex fermL = I_h_L(mhsq,Me,Mmu,Mtau);
    gslpp::complex I_hSM_W = I_H_W(mhsq,MW);
    gslpp::complex I_h_W = sin(bma)*I_hSM_W;

    double ABSgagaGM=0.0;
    double ABSgagaSM=0.0;

    //rh_Zga formula = fabs(A_h_F+A_h_W+A_h_Hp)^2 / fabs(A_hSM_F+A_hSM_W)^2

    gslpp::complex A_h_F = 0.0;
    gslpp::complex A_h_Ux = A_h_U(mhsq,cW2,Mu,Mc,Mt,MZ);
    gslpp::complex A_h_Dx = A_h_D(mhsq,cW2,Md,Ms,Mb,MZ);
    gslpp::complex A_h_Lx  = A_h_L(mhsq,cW2,Me,Mmu,Mtau,MZ);
    gslpp::complex A_hSM_W = A_H_W(mhsq,cW2,MW,MZ);
    gslpp::complex A_h_W = sin(bma)*A_hSM_W;

    double ABSZgaGM=0.0;
    double ABSZgaSM=0.0;

//    if( GMmodel == "custodial1" ) {
        rh_QdQd=cosa/sinb*cosa/sinb;
        rh_ll=cosa/sinb*cosa/sinb;
        ghHpHm = vev*vev/mAsq * (-lambda1*sina*sinb*sinb*cosb+lambda2*cosa*sinb*cosb*cosb
                                 +lambda3*(cosa*sinb*sinb*sinb-sina*cosb*cosb*cosb)
                                 -2.0*lambda4*(cosa*cosb-sina*sinb)*sinb*cosb);
        I_h_F=cosa/sinb*(fermU+fermD+fermL);
        A_h_F = cosa/sinb*(A_h_Ux+A_h_Dx+A_h_Lx)/sqrt(sW2*cW2);
//    }
//    else {
//        throw std::runtime_error("GMmodel can be only \"custodial1\"");
//    }

    double ch_p=0.0;
    double ch_r=0.0;
    gslpp::complex I_h_Sp = 1.5*ch_p*(3.0*I_H_Hp(mSpsq,mhsq));   //Factor 3 to normalize Higgs Hunters Guide to 1606.01298
    gslpp::complex I_h_SR = 1.5*ch_r*(3.0*I_H_Hp(mSRsq,mhsq));   //Factor 3 to normalize Higgs Hunters Guide to 1606.01298
    gslpp::complex I_h_SI = 1.5*ch_p*(3.0*I_H_Hp(mSIsq,mhsq));   //Factor 3 to normalize Higgs Hunters Guide to 1606.01298
//    double ABSggGM=(9.0/32.0*I_h_F+I_h_Sp+I_h_SR+I_h_SI).abs2();   //Factor 9/32 to normalize Higgs Hunters Guide to 1606.01298
//    double ABSggSM=(9.0/32.0*(fermU+fermD)).abs2();   //Factor 9/32 to normalize Higgs Hunters Guide to 1606.01298
    rh_gg=cosa/sinb*cosa/sinb;

    gslpp::complex I_h_Hp = 16.0*ghHpHm*I_H_Hp(mHpsq,mhsq);
    gslpp::complex A_h_Hp = 16.0*ghHpHm*A_H_Hp(mHpsq,mhsq,cW2,MZ);
    gslpp::complex I_h_S = 0.0;
    gslpp::complex A_h_S = 0.0;

    ABSgagaGM=(I_h_F+I_h_W+I_h_Hp+I_h_S).abs2();
    ABSgagaSM=(fermU+fermL+fermD+I_hSM_W).abs2();
    rh_gaga=ABSgagaGM/ABSgagaSM;
//
    ABSZgaGM=(A_h_F+A_h_W+A_h_Hp+A_h_S).abs2();
    ABSZgaSM=((A_h_Ux+A_h_Lx+A_h_Dx)/sqrt(sW2*cW2)+A_hSM_W).abs2();
    rh_Zga=ABSZgaGM/ABSZgaSM;

    sumModBRs = rh_QdQd*BrSM_htobb + rh_VV*(BrSM_htoWW+BrSM_htoZZ) + rh_ll*BrSM_htotautau +
          rh_gaga*BrSM_htogaga + rh_gg*BrSM_htogg + rh_Zga*BrSM_htoZga + rh_QuQu*BrSM_htocc;

    Gamma_h = sumModBRs*myGM->computeGammaHTotal();
    
    GM_BR_h_bb = rh_QdQd*BrSM_htobb/sumModBRs;
    GM_BR_h_gaga = rh_gaga*BrSM_htogaga/sumModBRs;
    GM_BR_h_tautau = rh_ll*BrSM_htotautau/sumModBRs;
    GM_BR_h_WW = rh_VV*BrSM_htoWW/sumModBRs;
    GM_BR_h_ZZ = rh_VV*BrSM_htoZZ/sumModBRs;
}

//void GMcache::runGMparameters()
//{
////    vev=myGM->v();
////    double cosb=myGM->getcosb();
//
//    std::string RGEorder=myGM->getRGEorderflag();
//    //flag will be used to transport information about model and RGEorder to the Runner:
//    //flag=0 for LO, 1 for approxNLO (and 2 for NLO - not implemented yet)
//    int flag;
//    if( RGEorder == "LO" ) flag=0;
//    else if( RGEorder == "approxNLO" ) flag=1;
////    else if( RGEorder == "NLO" ) flag=2;
//    else {
//        throw std::runtime_error("RGEorder can be only any of \"LO\", \"approxNLO\" or \"NLO\"");
//    }
//
//    double lambda1_at_MZ=lambda1;
//    double lambda2_at_MZ=lambda2;
//    double lambda3_at_MZ=lambda3;
//    double lambda4_at_MZ=lambda4;
//    double mu1_at_MZ=mu1;
//    double mu3_at_MZ=mu3;
//    double mu4_at_MZ=mu4;
//    double nu1_at_MZ=nu1;
//    double omega1_at_MZ=omega1;
//    double kappa1_at_MZ=kappa1;
//    double nu2_at_MZ=nu2;
//    double omega2_at_MZ=omega2;
//    double kappa2_at_MZ=kappa2;
//    double nu4_at_MZ=nu4;
//    double omega4_at_MZ=omega4;
//    double NLOuniscale=myGM->getNLOuniscaleGM();
//
//    if(fabs(Q_GM-log10(MZ))<0.005)   //at MZ scale
//    {
//        Q_cutoff=log10(MZ);
//
//        lambda1_at_Q = lambda1_at_MZ;
//        lambda2_at_Q = lambda2_at_MZ;
//        lambda3_at_Q = lambda3_at_MZ;
//        lambda4_at_Q = lambda4_at_MZ;
//        mu1_at_Q = mu1_at_MZ;
//        mu3_at_Q = mu3_at_MZ;
//        mu4_at_Q = mu4_at_MZ;
//        nu1_at_Q = nu1_at_MZ;
//        omega1_at_Q = omega1_at_MZ;
//        kappa1_at_Q = kappa1_at_MZ;
//        nu2_at_Q = nu2_at_MZ;
//        omega2_at_Q = omega2_at_MZ;
//        kappa2_at_Q = kappa2_at_MZ;
//        nu4_at_Q = nu4_at_MZ;
//        omega4_at_Q = omega4_at_MZ;
//    }
//    else   //at some other scale
//    {
//        double InitVals[15];
//        InitVals[0]=lambda1_at_MZ;
//        InitVals[1]=lambda2_at_MZ;
//        InitVals[2]=lambda3_at_MZ;
//        InitVals[3]=lambda4_at_MZ;
//        InitVals[4]=mu1_at_MZ;
//        InitVals[5]=mu3_at_MZ;
//        InitVals[6]=mu4_at_MZ;
//        InitVals[7]=nu1_at_MZ;
//        InitVals[8]=omega1_at_MZ;
//        InitVals[9]=kappa1_at_MZ;
//        InitVals[10]=nu2_at_MZ;
//        InitVals[11]=omega2_at_MZ;
//        InitVals[12]=kappa2_at_MZ;
//        InitVals[13]=nu4_at_MZ;
//        InitVals[14]=omega4_at_MZ;
//
//        Q_cutoff=myRunnerGM->RGERunnerGM(InitVals, 15, log10(MZ), Q_GM, flag, RpepsGM, NLOuniscale);  //Running up to Q_cutoff<=Q_GM
//
//        lambda1_at_Q = InitVals[0];
//        lambda2_at_Q = InitVals[1];
//        lambda3_at_Q = InitVals[2];
//        lambda4_at_Q = InitVals[3];
//        mu1_at_Q=InitVals[4];
//        mu3_at_Q=InitVals[5];
//        mu4_at_Q = InitVals[6];
//        nu1_at_Q = InitVals[7];
//        omega1_at_Q = InitVals[8];
//        kappa1_at_Q = InitVals[9];
//        nu2_at_Q = InitVals[10];
//        omega2_at_Q = InitVals[11];
//        kappa2_at_Q = InitVals[12];
//        nu4_at_Q = InitVals[13];
//        omega4_at_Q = InitVals[14];
//    }
//
//}

void GMcache::computeUnitarity()
{
//    std::string ModelType=myGM->getModelTypeGMflag();
//    if( ModelType != "custodial1" )
//    {
//        throw std::runtime_error("GM unitarity constraints are only implemented for the \"custodial1\" model.");
//    }
//
    double pi=M_PI;
//    /*
//    *******   LO part   *************
//    */

    unitarityeigenvalues.assign(0, (fabs(6.0*lambda1+11.0*lambda2+7.0*lambda3)+sqrt((6.0*lambda1-11.0*lambda2-7.0*lambda3)*(6.0*lambda1-11.0*lambda2-7.0*lambda3)+36.0*lambda4*lambda4))/(4.0*pi));
    unitarityeigenvalues.assign(1, fabs(lambda4-lambda5)/(2.0*pi));
    unitarityeigenvalues.assign(2, fabs(lambda2+2.0*lambda3)/pi);
    unitarityeigenvalues.assign(3, (fabs(2.0*lambda1+2.0*lambda2-lambda3)+sqrt((2.0*lambda1-2.0*lambda2+lambda3)*(2.0*lambda1-2.0*lambda2+lambda3)+lambda5*lambda5))/(4.0*pi));

//    
//    
//    /*
//    *******   NLO part   *************
//    */
//
//    double blambda1=(12.0*lambda1*lambda1 + 4.0*lambda3*lambda3 + 4.0*lambda3*lambda4 + 4.0*lambda4*lambda4 
//                     + 8.0*nu1*nu1 + 8.0*nu1*nu2 + 8.0*nu2*nu2)/(16.0*pi*pi);
//    double blambda2=(12.0*lambda2*lambda2 + 4.0*lambda3*lambda3 + 4.0*lambda3*lambda4 + 4.0*lambda4*lambda4
//                     + 8.0*omega1*omega1 + 8.0*omega1*omega2 + 8.0*omega2*omega2)/(16.0*pi*pi);
//    double blambda3=(4.0*lambda3*lambda3 + 4.0*lambda4*lambda4 + (lambda1+lambda2)*(6.0*lambda3+2.0*lambda4) 
//                     + 8.0*kappa2*kappa2 + 8.0*nu1*omega1 + 4.0*nu2*omega1 + 4.0*nu1*omega2)/(16.0*pi*pi);
//    double blambda4=(lambda1*lambda4 + lambda2*lambda4 + 4.0*lambda3*lambda4 + 6.0*lambda4*lambda4
//                     + 4.0*kappa1*kappa1 + 4.0*kappa1*kappa2 + 2.0*kappa2*kappa2 + 2.0*nu2*omega2)/(8.0*pi*pi);
//    double bmu1=(11.0*mu1*mu1 + 3.0*mu1*mu4 + mu1*(2.0*mu1+6.0*mu3+3.0*mu4)
//               + 3.0*nu4*nu4 + 3.0*omega4*omega4)/(16.0*pi*pi);
//    double bmu3=(18.0*kappa1*kappa1 + 18.0*kappa1*kappa2 + 134.0*mu1*mu1 + 6.0*mu1*(39.0*mu3 + 22.0*mu4)
//               + 3.0*(30.0*mu3*mu3 + 39.0*mu3*mu4 + 9.0*mu4*mu4 
//                      + 3.0*nu1*nu1 + 3.0*nu1*nu2 - 5.0*nu4*nu4
//                      + 3.0*omega1*omega1 + 3.0*omega1*omega2 - 5.0*omega4*omega4))/(72.0*pi*pi);
//    double bmu4=(18.0*kappa2*kappa2 + 4.0*mu1*mu1 + 156.0*mu1*mu4 + 54.0*mu3*mu4 + 144.0*mu4*mu4
//               + 9.0*nu2*nu2 + 6.0*nu4*nu4 + 9.0*omega2*omega2 + 6.0*omega4*omega4)/(144.0*pi*pi);
//    double bnu1=(6.0*kappa1*kappa1 + 6.0*kappa2*kappa2 + 18.0*lambda1*nu1
//               + 78.0*mu1*nu1 + 51.0*mu3*nu1 + 39.0*mu4*nu1 + 6.0*nu1*nu1
//               + 6.0*lambda1*nu2 + 32.0*mu1*nu2 + 24.0*mu3*nu2 + 6.0*mu4*nu2
//               + 6.0*nu2*nu2 + 10.0*nu4*nu4
//               + 12.0*lambda3*omega1 + 6.0*lambda4*omega1 + 6.0*lambda3*omega2)/(48.0*pi*pi);
//    double bomega1=(6.0*kappa1*kappa1 + 6.0*kappa2*kappa2 
//               + 12.0*lambda3*nu1 + 6.0*lambda4*nu1 + 6.0*lambda3*nu2
//               + 18.0*lambda2*omega1 + 78.0*mu1*omega1 + 51.0*mu3*omega1 + 39.0*mu4*omega1 + 6.0*omega1*omega1
//               + 6.0*lambda2*omega2 + 32.0*mu1*omega2 + 24.0*mu3*omega2 + 6.0*mu4*omega2 + 6.0*omega2*omega2
//               + 10.0*omega4*omega4)/(48.0*pi*pi);
//    double bkappa1=(6.0*kappa1*(2.0*lambda3 + 10.0*lambda4 + 18.0*mu1 + 17.0*mu3 + 13.0*mu4 + 2.0*nu1 + 2.0*omega1)
//               + kappa2*(24.0*lambda4 + 64.0*mu1 + 48.0*mu3 + 24.0*mu4 + 9.0*nu2 + 9.0*omega2)
//               + 20.0*nu4*omega4)/(96.0*pi*pi);
//    double bnu2=(4.0*kappa1*kappa2 + 6.0*kappa2*kappa2 + 2.0*lambda1*nu2 + ((14.0*mu1)/3.0 + mu3 + 9.0*mu4)*nu2 
//                + 4.0*nu1*nu2 + 6.0*nu2*nu2 + (25.0*nu4*nu4)/3.0 + 2.0*lambda4*omega2)/(16.0*pi*pi);
//    double bomega2=(4.0*kappa1*kappa2 + 6.0*kappa2*kappa2 + 2.0*lambda4*nu2 + 2.0*lambda2*omega2 
//                + ((14.0*mu1)/3.0 + mu3 + 9.0*mu4)*omega2 + 4.0*omega1*omega2 + 6.0*omega2*omega2 
//                + (25.0*omega4*omega4)/3.0)/(16.0*pi*pi);
//    double bkappa2=(kappa2*(6.0*lambda3 + 6.0*lambda4 + 14.0*mu1 + 3.0*mu3 + 27.0*mu4
//                     + 6.0*nu1 + 12.0*nu2 + 6.0*omega1 + 12.0*omega2)
//                + 6.0*kappa1*(nu2 + omega2) + 42.0*nu4*omega4)/(48.0*pi*pi);
//    double bnu4=(11.0*mu1*nu4 + 3.0*mu3*nu4 + 9.0*mu4*nu4 + 3.0*nu1*nu4 + 9.0*nu2*nu4 
//                + 3.0*kappa1*omega4 + 9.0*kappa2*omega4)/(16.0*pi*pi);
//    double bomega4=(3.0*kappa1*nu4 + 9.0*kappa2*nu4 
//                + (11.0*mu1 + 3.0*(mu3 + 3.0*mu4 + omega1 + 3.0*omega2))*omega4)/(16.0*pi*pi);
//
//    Sbmatrix1.assign(0,0, 3.0*blambda1/(16.0*pi));
//    Sbmatrix1.assign(0,1, (2.0*blambda3+blambda4)/(16.0*pi));
//    Sbmatrix1.assign(1,0, Sbmatrix1(0,1));
//    Sbmatrix1.assign(0,3, (2.0*bnu1+bnu2)/(8.0*sqrt(2.0)*pi));
//    Sbmatrix1.assign(3,0, Sbmatrix1(0,3));
//    Sbmatrix1.assign(1,1, 3.0*blambda2/(16.0*pi));
//    Sbmatrix1.assign(1,3, (2.0*bomega1+bomega2)/(8.0*sqrt(2.0)*pi));
//    Sbmatrix1.assign(3,1, Sbmatrix1(1,3));
//    Sbmatrix1.assign(2,2, (blambda3+5.0*blambda4)/(16.0*pi));
//    Sbmatrix1.assign(2,3, (4.0*bkappa1+2.0*bkappa2)/(16.0*pi));
//    Sbmatrix1.assign(3,2, Sbmatrix1(2,3));
//    Sbmatrix1.assign(3,3, (26.0*bmu1+17.0*bmu3+13.0*bmu4)/(32.0*pi));
//
//    Sbmatrix2.assign(0,0, blambda1/(16.0*pi));
//    Sbmatrix2.assign(0,1, blambda4/(16.0*pi));
//    Sbmatrix2.assign(1,0, Sbmatrix2(0,1));
//    Sbmatrix2.assign(0,3, bnu2/(8.0*sqrt(2.0)*pi));
//    Sbmatrix2.assign(3,0, Sbmatrix2(0,3));
//    Sbmatrix2.assign(1,1, blambda2/(16.0*pi));
//    Sbmatrix2.assign(1,3, bomega2/(8.0*sqrt(2.0)*pi));
//    Sbmatrix2.assign(3,1, Sbmatrix2(1,3));
//    Sbmatrix2.assign(2,2, (blambda3+blambda4)/(16.0*pi));
//    Sbmatrix2.assign(2,3, bkappa2/(8.0*pi));
//    Sbmatrix2.assign(3,2, Sbmatrix2(2,3));
//    Sbmatrix2.assign(3,3, (14.0*bmu1+3.0*bmu3+27.0*bmu4)/(96.0*pi));
//
//    Seigenvectors1T=Seigenvectors1.hconjugate();
//    Seigenvectors2T=Seigenvectors2.hconjugate();
//
//    for (int i=0; i < 4; i++) {
//        for (int k=0; k < 4; k++) {
//            for (int l=0; l < 4; l++) {
//                Sbeigenvalues1.assign(i, Sbeigenvalues1(i) + Seigenvectors1T(i,k) * Sbmatrix1(k,l) * Seigenvectors1(l,i) );
//                Sbeigenvalues2.assign(i, Sbeigenvalues2(i) + Seigenvectors2T(i,k) * Sbmatrix2(k,l) * Seigenvectors2(l,i) );
//            }                
//        }
//        betaeigenvalues.assign(i, -1.5 * Sbeigenvalues1(i));
//        betaeigenvalues.assign(i+4, -1.5 * Sbeigenvalues2(i));
//    }
//
//    betaeigenvalues.assign(8, -1.5 * (blambda3-blambda4)/(16.0*pi));
//    betaeigenvalues.assign(9, -1.5 * sqrt(15.0)*bnu4/(16.0*pi));
//    betaeigenvalues.assign(10, -1.5 * sqrt(15.0)*bomega4/(16.0*pi));
//
//    for (int i=0; i < 11; i++) {
//        NLOunitarityeigenvalues.assign(i, -(gslpp::complex::i()-1.0/pi)*unitarityeigenvalues(i)*unitarityeigenvalues(i) + betaeigenvalues(i) );
//    }
}

void GMcache::setOtherParameters()
{

}

double GMcache::updateCache()
{
//    GMmodel=myGM->getModelTypeGMflag();
    Q_GM=myGM->getQ_GM();
    vev=myGM->v();
    mHl=myGM->getMHl();
    mHl2=mHl*mHl;
    MZ=myGM->getMz();
    tanb=0.0;
    bma=0.0;
    sina=0.0;
    cosa=0.0;
    mhsq=0.0;
    mHsq=0.0;
    mAsq=0.0;
    mSRsq=0.0;
    mSIsq=0.0;
    mHpsq=0.0;
    mSpsq=0.0;
    lambda1=0.0;
    lambda2=0.0;
    lambda3=0.0;
    lambda4=0.0;
    lambda5=0.0;
    mSsq=0.0;
    mu1=0.0;
    mu3=0.0;
    mu4=0.0;
    nu1=0.0;
    omega1=0.0;
    kappa1=0.0;
    nu2=0.0;
    omega2=0.0;
    kappa2=0.0;
    nu3=0.0;
    omega3=0.0;
    kappa3=0.0;
    nu4=0.0;
    omega4=0.0;

    setOtherParameters();
//    runGMparameters();
//    computeUnitarity();
    return mHl2;
}



//double GeorgiMachacek::computelambda1() const
//{
//    return (mHh*mHh+mHl*mHl
//            +(mHh*mHh-mHl*mHl)*sign(mHh-mHl)*(cos(alpha)*cos(alpha)-sin(alpha)*sin(alpha)))/
//           (16.*v()*v()*costheta*costheta);
//}
//
//double GeorgiMachacek::computelambda2() const
//{
//    return (mH3*mH3 -M1*v()/(2.*sqrt(2.)*sintheta)
//            +((mHh*mHh-mHl*mHl)*sign(mHh-mHl)*cos(alpha)*sin(alpha))/(sqrt(6.)*costheta*sintheta))/
//           (v()*v());
//}
//
//double GeorgiMachacek::computelambda3() const
//{
//    return (mH5*mH5 -3.*sqrt(2.)*M2*v()*sintheta
//            +(-3.*mH3*mH3 + sqrt(2.)*M1*v()/sintheta)*costheta*costheta)/
//           (v()*v()*sintheta*sintheta);
//}
//
//double GeorgiMachacek::computelambda4() const
//{
//    return (-2.*mH5*mH5 +9.*sqrt(2.)*M2*sintheta*v()
//            +(6.*mH3*mH3 -(3.*sqrt(2.)*M1*v())/sintheta)*costheta*costheta
//            +mHh*mHh+mHl*mHl
//            -(mHh*mHh-mHl*mHl)*sign(mHh-mHl)*(cos(alpha)*cos(alpha)-sin(alpha)*sin(alpha)))/
//           (6.*v()*v()*sintheta*sintheta);
//}
//
//double GeorgiMachacek::computelambda5() const
//{
//    return (2.*mH3*mH3-sqrt(2.)*M1*v()/sintheta)/(v()*v());
//}
//
//double GeorgiMachacek::computemu2sq() const
//{
//    return (3.*sqrt(2.)*M1*v()*sintheta
//            -4.*(mHh*mHh+mHl*mHl)
//            -2.*(mHh*mHh-mHl*mHl)*sign(mHh-mHl)*(2.*cos(alpha)*cos(alpha) -2.*sin(alpha)*sin(alpha)
//                                                 +sqrt(6.)*cos(alpha)*sin(alpha)*sintheta/costheta))/16.;
//}
//
//double GeorgiMachacek::computemu3sq() const
//{
//    return (M1*v()*costheta*costheta +3.*M2*v()*sintheta*sintheta
//            -((mHh*mHh+mHl*mHl)*sintheta)/sqrt(2.)
//            -((mHh*mHh-mHl*mHl)*sign(mHh-mHl)*(3.*sqrt(2.)*(sin(alpha)*sin(alpha)-cos(alpha)*cos(alpha))*sintheta
//                                               +8.*sqrt(3.)*cos(alpha)*sin(alpha)*costheta))/6.)/
//           (2.*sqrt(2.)*sintheta);
//}
