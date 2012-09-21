/* 
 * File:   EW.cpp
 * Author: mishima
 */

#include "EW.h"
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <gsl/gsl_sf_zeta.h>
#include <stdexcept>


EW::EW(const StandardModel& SM_i, bool bDebug_i) : ThObsType(SM_i), SM(SM_i) {
    bDebug = bDebug_i;
}


////////////////////////////////////////////////////////////////////////

bool EW::checkModelForSTU() const {
    std::string Model = SM.ModelName();
    if (Model=="StandardModel" || Model=="SUSY")
        return false;
    else if (Model=="NewPhysicsSTU" || Model=="THDM")
        return true;
    else 
        throw std::runtime_error("Error in EW::checkModelForSTU()");  
}


double EW::Ql(const StandardModel::lepton l) const {
    return ( SM.getLeptons(l).getCharge() );
}        
 

double EW::Qq(const StandardModel::quark q) const {
    return ( SM.getQuarks(q).getCharge() );
}


double EW::s2() const {
    return ( SM.s02() );
}


double EW::c2() const {
    return ( SM.c02() );
}


////////////////////////////////////////////////////////////////////////

double EW::sin2thetaEff(const StandardModel::lepton l) const {
    complex gV_over_gA = SM.gVl(l)/SM.gAl(l);
    double absQf = fabs(Ql(l));
    return ( 1.0/4.0/absQf*(1.0 - gV_over_gA.real()) );
}


double EW::sin2thetaEff(const StandardModel::quark q) const {
    complex gV_over_gA = SM.gVq(q)/SM.gAq(q);
    double absQf = fabs(Qq(q));
    return ( 1.0/4.0/absQf*(1.0 - gV_over_gA.real()) );
}


double EW::Gamma_l(const StandardModel::lepton l) const {
    complex rhoZ_l = SM.rhoZ_l(l);
    complex gV_over_gA = SM.gVl(l)/SM.gAl(l);
    double alphaMz = SM.alphaMz();
    double Q = Ql(l);
    double xl = pow(SM.getLeptons(l).getMass()/SM.getMz(), 2.0);
    double G0 = SM.getGF()*pow(SM.getMz(),3.0)/24.0/sqrt(2.0)/M_PI;
    double Gamma = G0*rhoZ_l.abs()*sqrt(1.0 - 4.0*xl)
                   * ( (1.0 + 2.0*xl)*(gV_over_gA.abs2() + 1.0) - 6.0*xl )
                   * ( 1.0 + 3.0/4.0*alphaMz/M_PI*pow(Q,2.0) );
    return Gamma;
}


double EW::Gamma_q(const StandardModel::quark q) const {
    complex rhoZ_q = SM.rhoZ_q(q);
    complex gV_over_gA = SM.gVq(q)/SM.gAq(q);
    double alphaMz = SM.alphaMz();
    
    double mcMz, mbMz;
    if (!bDebug) {
        mcMz = SM.Mrun(SM.getMz(), SM.getQuarks(SM.CHARM).getMass(), FULLNNLO);
        mbMz = SM.Mrun(SM.getMz(), SM.getQuarks(SM.BOTTOM).getMass(), FULLNNLO);  
    } else {
        mcMz = 0.56381685; 
        mbMz = 2.8194352;
    }

    /* Radiator functions from the final-state QED and QCD corrections
     * to the vector and axial-vector currents */
    double RVf, RAf;
    /* non-factorizable EW-QCD corrections in GeV*/
    double Delta_EWQCD;
    /* z-component of isospin */
    double I3q;
    /* electric charge squared */
    double Qf2 = pow(Qq(q),2.0);

    switch(q) {
        case StandardModel::UP:
        case StandardModel::CHARM:
            Delta_EWQCD = -0.000113;
            I3q = 1.0/2.0;
            break;
        case StandardModel::TOP:
            return 0.0;
        case StandardModel::DOWN:
        case StandardModel::STRANGE:
            Delta_EWQCD = -0.000160;
            I3q = -1.0/2.0;
            break;
        case StandardModel::BOTTOM:
            Delta_EWQCD = -0.000040;
            I3q = -1.0/2.0;
            break;
        default:
            throw std::runtime_error("Error in EW::Gamma_q()");   
    }

    /* s = Mz^2 */
    double s = SM.getMz()*SM.getMz();

    /* products of the charm and bottom masses at Mz */
    double mcMz2 = mcMz*mcMz;
    double mbMz2 = mbMz*mbMz;
    double mqMz2, mqdash4;
    switch(q) {
        case StandardModel::CHARM:
            mqMz2 = mcMz*mcMz;
            mqdash4 = mbMz2*mbMz2;
            break;
        case StandardModel::BOTTOM:
            mqMz2 = mbMz*mbMz;
            mqdash4 = mcMz2*mcMz2;
            break;
        default:
            mqMz2 = 0.0;
            mqdash4 = 0.0;
            break;
    }

    /* Logarithms */
    double log_t = log(pow(SM.getQuarks(SM.TOP).getMass(),2.0)/s);
    double log_c = log(mcMz2/s);
    double log_b = log(mbMz2/s);
    double log_q;
    switch(q) {
        case StandardModel::CHARM:
        case StandardModel::BOTTOM:
            log_q = log(mqMz2/s);
            break;
        default:
            log_q = 0.0;
            break;
    }    
    
    /* the active number of flavour */
    double nf = 5.0;

    /* zeta functions */
    double zeta2 = gsl_sf_zeta_int(2);
    double zeta3 = gsl_sf_zeta_int(3);
    double zeta4 = gsl_sf_zeta_int(4);
    double zeta5 = gsl_sf_zeta_int(5);

    /* massless non-singlet corrections */
    double C02 = 365.0/24.0 - 11.0*zeta3 + (-11.0/12.0 + 2.0/3.0*zeta3)*nf;
    double C03 = 87029.0/288.0 - 121.0/8.0*zeta2 - 1103.0/4.0*zeta3
                 + 275.0/6.0*zeta5 
                 + (-7847.0/216.0 + 11.0/6.0*zeta2 + 262.0/9.0*zeta3
                    - 25.0/9.0*zeta5)*nf
                 + (151.0/162.0 - zeta2/18.0 - 19.0/27.0*zeta3)*nf*nf;
    double C04 = -156.61 + 18.77*nf - 0.7974*nf*nf + 0.0215*nf*nf*nf;
    //std::cout << "TEST: C02 = " << C02 << std::endl;// TEST (should be 1.40923)
    //std::cout << "TEST: C03 = " << C03 << std::endl;// TEST (should be -12.7671)
    //std::cout << "TEST: C04 = " << C04 << std::endl;// TEST (should be -80.0075)

    /* quadratic massive corrections */
    double C23  = -80.0 + 60.0*zeta3 + (32.0/9.0 - 8.0/3.0*zeta3)*nf;
    double C21V = 12.0;
    double C22V = 253.0/2.0 - 13.0/3.0*nf;
    double C23V = 2522.0 - 855.0/2.0*zeta2 + 310.0/3.0*zeta3 - 5225.0/6.0*zeta5
                  + (-4942.0/27.0 + 34.0*zeta2 - 394.0/27.0*zeta3
                     + 1045.0/27.0*zeta5)*nf
                  + (125.0/54.0 - 2.0/3.0*zeta2)*nf*nf;
    double C20A = -6.0;
    double C21A = -22.0;
    double C22A = -8221.0/24.0 + 57.0*zeta2 + 117.0*zeta3
                  + (151.0/12.0 - 2.0*zeta2 - 4.0*zeta3)*nf;
    double C23A = -4544045.0/864.0 + 1340.0*zeta2 + 118915.0/36.0*zeta3
                  - 127.0*zeta5
                  + (71621.0/162.0 - 209.0/2.0*zeta2 - 216.0*zeta3
                     + 5.0*zeta4 + 55.0*zeta5)*nf
                  + (-13171.0/1944.0 + 16.0/9.0*zeta2 + 26.0/9.0*zeta3)*nf*nf;

    /* quartic massive corrections */
    double C42  = 13.0/3.0 - 4.0*zeta3;
    //double C40V = -6.0; /* not used */
    double C41V = -22.0;
    double C42V = -3029.0/12.0 + 162.0*zeta2 + 112.0*zeta3
                  + (143.0/18.0 - 4.0*zeta2 - 8.0/3.0*zeta3)*nf;
    double C42VL= -11.0/2.0 + nf/3.0;
    double C40A = 6.0;
    double C41A = 10.0;
    double C42A = 3389.0/12.0 - 162.0*zeta2 - 220.0*zeta3
                  + (-41.0/6.0 + 4.0*zeta2 + 16.0/3.0*zeta3)*nf;
    double C42AL= 77.0/2.0 - 7.0/3.0*nf;

    /* power suppressed top-mass correction */
    double xt = s/pow(SM.getQuarks(SM.TOP).getMass(),2.0);
    double C2t = xt*(44.0/675.0 - 2.0/135.0*(-log_t));

    /* singlet axial-vector corrections */
    double I2 = -37.0/12.0 + (-log_t) + 7.0/81.0*xt + 0.0132*xt*xt;
    double I3 = -5075.0/216.0 + 23.0/6.0*zeta2 + zeta3 + 67.0/18.0*(-log_t)
                + 23.0/12.0*log_t*log_t;
    double I4 = 49.0309 - 17.6637*(-log_t) + 14.6597*log_t*log_t 
                + 3.6736*(-log_t*log_t*log_t);
    
    /* singlet vector corrections */
    //double RVh; /* not used */
    
    /* rescaled strong coupling constant */
    double AlsMzPi  = SM.getAlsMz()/M_PI;
    double AlsMzPi2 = AlsMzPi*AlsMzPi;
    double AlsMzPi3 = AlsMzPi2*AlsMzPi;
    double AlsMzPi4 = AlsMzPi3*AlsMzPi;

    /* radiator function to the vector current */
    RVf = 1.0 + 3.0/4.0*Qf2*alphaMz/M_PI + AlsMzPi - Qf2/4.0*alphaMz/M_PI*AlsMzPi
            + (C02 + C2t)*AlsMzPi2 + C03*AlsMzPi3 + C04*AlsMzPi4
            + (mcMz2 + mbMz2)/s*C23*AlsMzPi3
            + mqMz2/s*(C21V*AlsMzPi + C22V*AlsMzPi2 + C23V*AlsMzPi3)
            + mcMz2*mcMz2/s/s*(C42 - log_c)*AlsMzPi2
            + mbMz2*mbMz2/s/s*(C42 - log_b)*AlsMzPi2
            + mqMz2*mqMz2/s/s*(C41V*AlsMzPi + (C42V + C42VL*log_q)*AlsMzPi2)
            + 12.0*mqdash4/s/s*AlsMzPi2
            - mqMz2*mqMz2*mqMz2/s/s/s
              *(8.0+16.0/27.0*(155.0 + 6.0*log_q)*AlsMzPi);

    /* radiator function to the axial-vector current */
    RAf = 1.0 + 3.0/4.0*Qf2*alphaMz/M_PI + AlsMzPi - Qf2/4.0*alphaMz/M_PI*AlsMzPi
            + (C02 + C2t - 2.0*I3q*I2)*AlsMzPi2
            + (C03 - 2.0*I3q*I3)*AlsMzPi3
            + (C04 - 2.0*I3q*I4)*AlsMzPi4
            + (mcMz2 + mbMz2)/s*C23*AlsMzPi3
            + mqMz2/s*(C20A + C21A*AlsMzPi + C22A*AlsMzPi2
                       + 6.0*(3.0 + log_t)*AlsMzPi2 + C23A*AlsMzPi3)
            - 10.0*mqMz2/pow(SM.getQuarks(SM.TOP).getMass(),2.0)
              *(8.0/81.0 + log_t/54.0)*AlsMzPi2
            + mcMz2*mcMz2/s/s*(C42 - log_c)*AlsMzPi2
            + mbMz2*mbMz2/s/s*(C42 - log_b)*AlsMzPi2
            + mqMz2*mqMz2/s/s*(C40A + C41A*AlsMzPi
                               + (C42A + C42AL*log_q)*AlsMzPi2)
            - 12.0*mqdash4/s/s*AlsMzPi2 ;    
    
    double G0 = SM.getGF()*pow(SM.getMz(),3.0)/24.0/sqrt(2.0)/M_PI;    
    double Gamma = 3.0* G0*rhoZ_q.abs()
                   * ( gV_over_gA.abs2()*RVf + RAf ) + Delta_EWQCD;
    return Gamma;
}


double EW::Gamma_inv() const {
    return ( Gamma_l(SM.NEUTRINO_1) + Gamma_l(SM.NEUTRINO_2) 
             + Gamma_l(SM.NEUTRINO_3) );
}


double EW::Gamma_had() const {
    double Gamma_had_tmp = Gamma_q(SM.UP) + Gamma_q(SM.DOWN) + Gamma_q(SM.CHARM)
                           + Gamma_q(SM.STRANGE) + Gamma_q(SM.BOTTOM);

    /* rescaled strong coupling constant */
    double AlsMzPi  = SM.getAlsMz()/M_PI;
    double AlsMzPi2 = AlsMzPi*AlsMzPi;
    double AlsMzPi3 = AlsMzPi2*AlsMzPi;
    double AlsMzPi4 = AlsMzPi3*AlsMzPi;

    complex gV_sum(0.0, 0.0); 
    complex gV_q;
    std::string Model = getSM().ModelName();
    for (int q=0; q<6; q++) {
        gV_q = SM.gVq((StandardModel::quark)q);
        if (q==(int)(StandardModel::TOP)) 
            gV_q = 0.0;
        gV_sum += gV_q;
    }
    
    // singlet vector corrections
    double G0 = SM.getGF()*pow(SM.getMz(),3.0)/24.0/sqrt(2.0)/M_PI; 
    double RVh = gV_sum.abs2()*(-0.4132*AlsMzPi3 - 4.9841*AlsMzPi4);
    Gamma_had_tmp += 4.0*3.0*G0*RVh;

    return Gamma_had_tmp;    
}


double EW::Gamma_Z() const {
    return ( Gamma_l(SM.ELECTRON) + Gamma_l(SM.MU) + Gamma_l(SM.TAU) 
             + Gamma_inv() + Gamma_had() );
}


double EW::sigma0_l(const StandardModel::lepton l) const {
    return ( 12.0*M_PI*Gamma_l(SM.ELECTRON)*Gamma_l(l)
             /SM.getMz()/SM.getMz()/Gamma_Z()/Gamma_Z() );
}


double EW::sigma0_had() const {
     return (12.0*M_PI*Gamma_l(SM.ELECTRON)*Gamma_had()
            /SM.getMz()/SM.getMz()/Gamma_Z()/Gamma_Z());
}


double EW::A_l(const StandardModel::lepton l) const {
    double Re_gV_over_gA = (SM.gVl(l)/SM.gAl(l)).real();
    return ( 2.0*Re_gV_over_gA/(1.0+pow(Re_gV_over_gA,2.0)) );
}


double EW::A_q(const StandardModel::quark q) const {
    double Re_gV_over_gA = (SM.gVq(q)/SM.gAq(q)).real();    
    return ( 2.0*Re_gV_over_gA/(1.0+pow(Re_gV_over_gA,2.0)) );
}


////////////////////////////////////////////////////////////////////////

double EW::dsigma_lLEP2(const StandardModel::lepton l, const double s, 
                        const double W, const double X, const double Y, 
                        const double cos_theta) const {
    return ( SM.DsigmaLEP2_l(l, s, cos_theta, W, X, Y, Gamma_Z()) );
}


double EW::dsigma_qLEP2(const StandardModel::quark q, const double s,
                        const double W, const double X, const double Y, 
                        const double cos_theta) const {
    return ( SM.DsigmaLEP2_q(q, s, cos_theta, W, X, Y, Gamma_Z()) );
}


////////////////////////////////////////////////////////////////////////

double EW::sigma_l_Born_LEP2(const StandardModel::lepton l, const double s) const {
    double mf = SM.getLeptons(l).getMass();
    double Qf = SM.getLeptons(l).getCharge();
    double I3f = SM.getLeptons(l).getIsospin();
    return sigma_f_Born_LEP2(s, mf, Qf, I3f, 1.0);
}


double EW::sigma_q_Born_LEP2(const StandardModel::quark q, const double s) const {
    double mf;
    switch(q) {
        case StandardModel::UP:
        case StandardModel::DOWN:
        case StandardModel::STRANGE:
            mf = SM.Mrun(SM.getMz(), 2.0, SM.getQuarks(q).getMass(), FULLNNLO);
            break;
        case StandardModel::CHARM:
        case StandardModel::BOTTOM:
            mf = SM.Mrun(SM.getMz(), SM.getQuarks(q).getMass(), FULLNNLO);
            break;
        default:
            throw std::runtime_error("Error in EW::sigma_q_Born_LEP2()");   
    }
    double Qf = SM.getQuarks(q).getCharge();
    double I3f = SM.getQuarks(q).getIsospin();
    return sigma_f_Born_LEP2(s, mf, Qf, I3f, 3.0);
}


double EW::sigma_f_Born_LEP2(const double s, const double mf, const double Qf, 
                             const double I3f, const double Ncf) const {
    double betaf = sqrt(1.0 - 4.0*mf*mf/s);
    double Qe = SM.getLeptons(SM.ELECTRON).getCharge();
    double I3e = SM.getLeptons(SM.ELECTRON).getIsospin();
    double sW2 = SM.sW2();
    double sW = sqrt(sW2);
    double cW = sqrt(SM.cW2());
    double ve = (I3e - 2.0*Qe*sW2)/(2.0*sW*cW);
    double ae = I3e/(2.0*sW*cW);
    double vf = (I3f - 2.0*Qf*sW2)/(2.0*sW*cW);
    double af = I3f/(2.0*sW*cW);
    double Mz = SM.getMz();
    double GammaZ = Gamma_Z();
    double Qe2 = Qe*Qe, Qf2 = Qf*Qf, betaf2 = betaf*betaf;
    double ve2 = ve*ve, ae2 = ae*ae, vf2 = vf*vf, af2 = af*af;
    
    complex chi_gamma = complex(1.0, 0.0, false);
    complex i = complex::i();
    complex chi_Z = s/(s - Mz*Mz + i*Mz*GammaZ);
    //complex chi_Z = s/(s - Mz*Mz);
    complex chi_gammaZ = complex(0.0, 0.0, false);
    
    double G1 = Qe2*Qf2*chi_gamma.abs2()
                + 2.0*ve*vf*Qe*Qf*(chi_Z*chi_gamma.conjugate()).real()
                + (ve2 + ae2)*(vf2 + betaf2*af2)*chi_Z.abs2()
                + (Qe2*(vf2 + af2) + 2.0*ve*vf*Qe*Qf + (ve2 + ae2)*Qf2)*chi_gammaZ.abs2()
                + 2.0*(vf*Qe2*Qf + ve*Qe*Qf2)*(chi_gamma*chi_gammaZ.conjugate()).real()
                + 2.0*(ve*(vf2 + af2)*Qe + (ve2 + ae2)*vf*Qf)*(chi_Z*chi_gammaZ.conjugate()).real();
    double G2 = Qe2*Qf2*chi_gamma.abs2()
                + 2.0*ve*vf*Qe*Qf*(chi_Z*chi_gamma.conjugate()).real()
                + (ve2 + ae2)*vf2*chi_Z.abs2();
    
    return ( 4.0*M_PI*SM.getAle()*SM.getAle()/(3.0*s)*Ncf*betaf*(G1 + 2.0*mf*mf/s*G2) );
}

