/* 
 * Copyright (C) 2016 HEPfit Collaboration
 *
 *
 * For the licensing terms see doc/COPYING.
 */

#ifndef BXQLL_H
#define	BXQLL_H

class StandardModel;
class F_1;
class F_2;
#include "QCD.h"
#include "ThObservable.h"
//#include "Particle.h"
#include "gslpp.h"
#include <gsl/gsl_integration.h>

/**
* @enum q2regions
* @ingroup BXqll
* @brief An enum type for \f$ q^2 \f$ regions in @f$B \to X_q l^+ l^-@f$.
*/
enum q2regions
{
    LOWQ2 = 0, /**< Dilepton invariant mass region \f$ 1 < q^2 < 6 \mathrm{GeV}^2 \f$ */
    HIGHQ2, /**< Dilepton invariant mass region \f$ q^2 > 14.4 \mathrm{GeV}^2 \f$  */
};

/**
 * @class BXqll
 * @ingroup Flavour
 * @brief A class for the @f$B \to X_q l^+ l^-@f$ decay.  
 * @author HEPfit Collaboration
 * @copyright GNU General Public License
 * @details This class is used to compute all the functions needed in order to 
 * build the observables relative to the @f$B \to X_q l^+ l^-@f$ decays, where
 * @f$X_q@f$ is an inclusive hadronic state containing a @f$q@f$ quark.
 * Formulae for the effective Hamiltonian are taken from Bobeth et al., hep-ph/9910220.
 * Formulae for the matrix elements are taken from Greub et al., arXiv:0810.4077
 */
class BXqll {
public:
    
    /**
     * @brief Constructor.
     * @param[in] SM_i a reference to an object of type StandardModel
     * @param[in] quark_i quark defining the inclusive final hadronic state @f$X_q@f$ of the decay
     * @param[in] lep_i final leptons of the decay
     */
    BXqll(const StandardModel& SM_i, QCD::quark quark_i, QCD::lepton lep_i);
    
    /**
     * @brief Destructor.
     */
    virtual ~BXqll();  

    class Expanded {
    public:
        Expanded() {
            lo = nlo = nnlo = 0.;
        };
        
        Expanded(gslpp::complex x_LO, gslpp::complex x_NLO = 0., gslpp::complex x_NNLO = 0.) {
            lo = x_LO;
            nlo = x_NLO;
            nnlo = x_NNLO;
            };
 
        Expanded operator*(const Expanded& z) const
        {
          return Expanded(lo * z.lo, lo * z.nlo + nlo * z.lo,
                  nnlo * z.lo + nlo * z.nlo + lo * z.nnlo);
        };

        Expanded operator*(const double& x) const
        {
          return Expanded(lo * x, nlo * x, nnlo * x);
        };

        Expanded operator+(const Expanded& z) const
        {
          return Expanded(lo + z.lo, nlo + z.nlo, nnlo + z.nnlo);
        };

        Expanded operator-(const Expanded& z) const
        {
          return Expanded(lo - z.lo, nlo - z.nlo, nnlo - z.nnlo);
        };

        Expanded conjugate() const
        {
            return Expanded(lo.conjugate(), nlo.conjugate(), nnlo.conjugate());
        };

        Expanded real() const
        {
            return Expanded(lo.real(), nlo.real(), nnlo.real());
        };

        Expanded abs2() const
        {
            return Expanded(lo.abs2(), 2.* (lo * nlo.conjugate()).real(),
                    nlo.abs2() + 2.* (lo * nnlo.conjugate()).real());
        };
        
        friend Expanded operator*(const double& x1, const Expanded& z2) {
            return(z2 * x1);
        }
        
        gslpp::complex lo, nlo, nnlo;
    };

    /**
    * @brief A method for initializing the parameters necessary for BXqll.
    * @return the vector of BXqll specific parameters
    */
    std::vector<std::string> initializeBXqllParameters();
    
    /**
     * @brief dGamma/ds for @f$B \to X_q l^+ l^-@f$ in the low dilepton invariant mass region.
     * @param[in] sh normalized dilepton invariant mass @f$q^2/m_b^2@f$
      */    
    double getR_LOWQ2(double sh);
    
    /**
     * @brief dGamma/ds for @f$B \to X_q l^+ l^-@f$ in the high dilepton invariant mass region.
     * @param[in] sh normalized dilepton invariant mass @f$q^2/m_b^2@f$
      */    
    double getR_HIGHQ2(double sh);
    
    /**
    * @brief The integral of dGamma/ds for @f$B \to X_q l^+ l^-@f$ from \f$s_{min}\f$ to \f$s_{max}\f$
    * @param[in] sh_min minimum \f$q^2/m_b^2\f$ of the integral
    * @param[in] sh_max maximum \f$q^2/m_b^2\f$ of the integral
    */
    double integrate_Rquark(double sh_min, double sh_max, q2regions q2region);
    
    const StandardModel& mySM;/**< Model type */

private:
//    const StandardModel& mySM;/**< Model type */
    F_1& myF_1;
    F_2& myF_2;
    QCD::lepton lep;/**< Final leptons type */
    QCD::quark quark;/**< Initial meson type */
    double CF, GF, ale, alsmu, alsmuc, alstilde, aletilde, kappa;
    double Mlep, mu_b, mu_c, Mb, Mc, Mtau, Mb_pole, Mc_pole, Ms, MW;
    double abslambdat_over_Vcb, Vts_over_Vcb, z, muh, lambda_1, lambda_2, Lbl, phi1, phi2;

    std::vector<std::string> BXqllParameters;/**< The string of mandatory MVgamma parameters */

    gslpp::vector<gslpp::complex> ** allcoeff;/**<Vector that contains the Wilson coeffients */
//    gslpp::vector<gslpp::complex> ** allcoeffh;/**<Vector that contains the Wilson coeffients at scale @f$\mu_h@f$ */
    gslpp::vector<gslpp::complex> ** allcoeffprime;/**<Vector that contains the primed Wilson coeffients */
    
    gslpp::complex C_1[4];/**<Wilson coeffients @f$C_1@f$*/
    gslpp::complex C_1L_bar[4];/**<Wilson coeffients @f$C_1@f$*/
    gslpp::complex C_2[4];/**<Wilson coeffients @f$C_2@f$*/
    gslpp::complex C_2L_bar[4];/**<Leading order Wilson coeffients @f$C_2@f$*/
    gslpp::complex C_3[4];/**<Wilson coeffients @f$C_3@f$*/
    gslpp::complex C_4[4];/**<Wilson coeffients @f$C_4@f$*/
    gslpp::complex C_5[4];/**<Wilson coeffients @f$C_5@f$*/
    gslpp::complex C_6[4];/**<Wilson coeffients @f$C_6@f$*/
    gslpp::complex C_7[4];/**<Wilson coeffients @f$C_7@f$*/
    gslpp::complex C_8L[4];/**<Leading order Wilson coeffients @f$C_8@f$*/
    gslpp::complex C_9[4];/**<Wilson coeffients @f$C_9@f$*/
    gslpp::complex C_10[4];/**<Wilson coeffients @f$C_{10}@f$*/
    gslpp::complex C_S[4];/**<Wilson coeffients @f$C_S@f$*/
    gslpp::complex C_P[4];/**<Wilson coeffients @f$C_P@f$*/
    
    gslpp::complex C_7p[4];/**<Wilson coeffients @f$C_7'@f$*/
    gslpp::complex C_9p[4];/**<Wilson coeffients @f$C_9'@f$*/
    gslpp::complex C_10p[4];/**<Wilson coeffients @f$C_{10}'@f$*/
    gslpp::complex C_Sp[4];/**<Wilson coeffients @f$C_S'@f$*/
    gslpp::complex C_Pp[4];/**<Wilson coeffients @f$C_P'@f$*/
    gslpp::complex T_9[4], U_9[4], W_9[4];
    
    double avaRquark;/**< Gsl integral variable */
    double errRquark;/**< Gsl integral variable */
    
    gsl_function FR;/**< Gsl integral variable */
    
    gsl_integration_cquad_workspace * w_Rquark;/**< Gsl integral variable */
    
    gsl_error_handler_t * old_handler; /**< GSL error handler store */
    
    /**
     * @brief The update parameter method for BXqll.
     */
    void updateParameters();

    double F_17re(double muh, double z, double sh, int maxpow=20);
    double F_17im(double muh, double z, double sh, int maxpow=20);
    double F_19re(double muh, double z, double sh, int maxpow=20);
    double F_19im(double muh, double z, double sh, int maxpow=20);
    double F_27re(double muh, double z, double sh, int maxpow=20);
    double F_27im(double muh, double z, double sh, int maxpow=20);
    double F_29re(double muh, double z, double sh, int maxpow=20);
    double F_29im(double muh, double z, double sh, int maxpow=20);
    
    double DeltaF_19re(double muh, double z, double sh, int maxpow=20);
    double DeltaF_19im(double muh, double z, double sh, int maxpow=20);
    double DeltaF_29re(double muh, double z, double sh, int maxpow=20);
    double DeltaF_29im(double muh, double z, double sh, int maxpow=20);
    /**
    * @brief The correction \f$ F_{17} \f$ from @cite Greub:2008cy.
    * @param[in] sh \f$q^2/m_b^2\f$ of the decay
    * @return \f$ F_{17} \f$
    */
    gslpp::complex F17(double sh);

    /**
    * @brief The correction \f$ F_{27} \f$ from @cite Greub:2008cy.
    * @param[in] sh \f$q^2/m_b^2\f$ of the decay
    * @return \f$ F_{27} \f$
    */
    gslpp::complex F27(double sh);

    /**
    * @brief The correction \f$ F_{19} \f$ from @cite Greub:2008cy.
    * @param[in] sh \f$q^2/m_b^2\f$ of the decay
    * @return \f$ F_{19} \f$
    */
    gslpp::complex F19(double sh);

    /**
    * @brief The correction \f$ F_{29} \f$ from @cite Greub:2008cy.
    * @param[in] sh \f$q^2/m_b^2\f$ of the decay
    * @return \f$ F_{29} \f$
    */
    gslpp::complex F29(double sh);

    /**
    * @brief The correction \f$ F_{87} \f$ from @cite Greub:2008cy.
    * @param[in] sh \f$q^2/m_b^2\f$ of the decay
    * @return \f$ F_{87} \f$
    */
    gslpp::complex F87(double sh);

    /**
    * @brief The correction \f$ F_{89} \f$ from @cite Asatrian:2001de.
    * @param[in] sh \f$q^2/m_b^2\f$ of the decay
    * @return \f$ F_{89} \f$
    */
    double F89(double sh);

    /**
    * @brief The effective coefficient \f${\tilde C}_7^\mathrm{eff}\f$ from @cite Asatrian:2001zw.
    * @param[in] sh \f$q^2/m_b^2\f$ of the decay
    * @return \f${\tilde C}_7^\mathrm{eff}\f$
    */
    gslpp::complex C7eff(double sh, orders order);

    /**
    * @brief The effective coefficient \f${\tilde C}_9^\mathrm{eff}\f$ from @cite Asatrian:2001zw.
    * @param[in] sh \f$q^2/m_b^2\f$ of the decay
    * @return \f${\tilde C}_9^\mathrm{eff}\f$
    */
    gslpp::complex C9eff(double sh, orders order);

    /**
    * @brief The effective coefficient \f${\tilde C}_{10}^\mathrm{eff}\f$ from @cite Asatrian:2001zw.
    * @param[in] sh \f$q^2/m_b^2\f$ of the decay
    * @return \f${\tilde C}_{10}^\mathrm{eff}\f$
    */
    gslpp::complex C10eff(double sh, orders order);

    /**
    * @brief The bremsstrahlung correction \f$omega_7(\hat s)\f$ from @cite Asatrian:2001zw.
    * @param[in] sh \f$q^2/m_b^2\f$ of the decay
    * @return \f$omega_7(\hat s)\f$
    */
    double omega7(double sh);

    /**
    * @brief The bremsstrahlung correction \f$omega_9(\hat s)\f$ from @cite Asatrian:2001zw.
    * @param[in] sh \f$q^2/m_b^2\f$ of the decay
    * @return \f$omega_9(\hat s)\f$
    */
    double omega9(double sh);

    /**
    * @brief The bremsstrahlung correction \f$omega_{79}(\hat s)\f$ from @cite Asatrian:2001zw.
    * @param[in] sh \f$q^2/m_b^2\f$ of the decay
    * @return \f$omega_{79}(\hat s)\f$
    */
    double omega79(double sh);

    /**
    * @brief Auxiliary function ATUW from @cite Asatrian:2001zw.
    * @param[in] sh \f$q^2/m_b^2\f$ of the decay
    * @param[in] order LO or NLO
    * @return ATUW(sh, order)
    */
    gslpp::complex ATUW(double sh, orders order);
    
    /**
    * @brief Auxiliary function \f$h(z,sh)\f$ from @cite Asatrian:2001zw.
    * @param[in] sh \f$q^2/m_b^2\f$ of the decay
    * @param[in] z \f$m_c^2/m_b^2\f$
    * @return \f$h(z,sh)\f$
    */
    gslpp::complex h_z(double zed, double sh);
 
    
    /**
    * @brief Auxiliary function \f$g(z)\f$ from @cite Asatrian:2001zw.
    * @param[in] z \f$m_c^2/m_b^2\f$
    * @return \f$g(z)\f$
    */
    double g(double z);
    
    /**
    * @brief Auxiliary function \f$f_{sl}(z) = g(z) K(z)\f$ from @cite Asatrian:2001zw.
    * @param[in] z \f$m_c^2/m_b^2\f$
    * @return \f$g(z)\f$
    */
    double f_sl(double z);
    
    /**
    * @brief The finite bremsstrahlung correction \f$tau_{78}(\hat s)\f$ from @cite Asatryan:2002iy.
    * @param[in] sh \f$q^2/m_b^2\f$ of the decay
    * @return \f$tau_{78}(\hat s)\f$
    */
    double tau78(double sh);
    
    /**
    * @brief The finite bremsstrahlung correction \f$tau_{89}(\hat s)\f$ from @cite Asatryan:2002iy.
    * @param[in] sh \f$q^2/m_b^2\f$ of the decay
    * @return \f$tau_{89}(\hat s)\f$
    */
    double tau89(double sh);
    
    /**
    * @brief The finite bremsstrahlung correction \f$tau_{88}(\hat s)\f$ from @cite Asatryan:2002iy.
    * @param[in] sh \f$q^2/m_b^2\f$ of the decay
    * @return \f$tau_{88}(\hat s)\f$
    */
    double tau88(double sh);
    
    /**
    * @brief The fit of the finite bremsstrahlung correction \f$tau_{22}(\hat s)\f$ from @cite Asatryan:2002iy.
    * @param[in] sh \f$q^2/m_b^2\f$ of the decay
    * @return \f$tau_{22}(\hat s)\f$
    */
    double tau22fit(double sh, q2regions q2region);
    
    /**
    * @brief The fit of the real part of finite bremsstrahlung correction \f$tau_{27}(\hat s)\f$ from @cite Asatryan:2002iy.
    * @param[in] sh \f$q^2/m_b^2\f$ of the decay
    * @return \f$tau_{27}(\hat s)\f$
    */
    double tau27fit_Re(double sh, q2regions q2region);
    
    /**
    * @brief The fit of the imaginary part of finite bremsstrahlung correction \f$tau_{27}(\hat s)\f$ from @cite Asatryan:2002iy.
    * @param[in] sh \f$q^2/m_b^2\f$ of the decay
    * @return \f$tau_{27}(\hat s)\f$
    */
    double tau27fit_Im(double sh, q2regions q2region);
    
    /**
    * @brief The fit of the real part of finite bremsstrahlung correction \f$tau_{28}(\hat s)\f$ from @cite Asatryan:2002iy.
    * @param[in] sh \f$q^2/m_b^2\f$ of the decay
    * @return \f$tau_{28}(\hat s)\f$
    */
    double tau28fit_Re(double sh, q2regions q2region);
    
    /**
    * @brief The fit of the imaginary part of finite bremsstrahlung correction \f$tau_{28}(\hat s)\f$ from @cite Asatryan:2002iy.
    * @param[in] sh \f$q^2/m_b^2\f$ of the decay
    * @return \f$tau_{28}(\hat s)\f$
    */
    double tau28fit_Im(double sh, q2regions q2region);
    
    /**
    * @brief The fit of the real part of finite bremsstrahlung correction \f$tau_{29}(\hat s)\f$ from @cite Asatryan:2002iy.
    * @param[in] sh \f$q^2/m_b^2\f$ of the decay
    * @return \f$tau_{29}(\hat s)\f$
    */
    double tau29fit_Re(double sh, q2regions q2region);
    
    /**
    * @brief The fit of the imaginary part of finite bremsstrahlung correction \f$tau_{29}(\hat s)\f$ from @cite Asatryan:2002iy.
    * @param[in] sh \f$q^2/m_b^2\f$ of the decay
    * @return \f$tau_{29}(\hat s)\f$
    */
    double tau29fit_Im(double sh, q2regions q2region);
    
    /**
    * @brief The finite bremsstrahlung corrections to dGamma/ds for @f$B \to X_q l^+ l^-@f$ from @cite Asatryan:2002iy
    * @param[in] sh normalized dilepton invariant mass \f$q^2/m_b^2\f$
    * @param[in] q2region allowed region of dilepton invariant mass @f$q^2@f$
    */
    double R_bremsstrahlung(double sh, q2regions q2region);
    
    /**
     * @brief dGamma/ds for @f$B \to X_q l^+ l^-@f$.
     * @param[in] sh normalized dilepton invariant mass @f$q^2/m_b^2@f$
     * @param[in] q2region allowed regions of dilepton invariant mass @f$q^2@f$
      */    
    double R_quark(double sh, q2regions q2region);
    
    /**
    * @brief Auxiliary function \f$g_lambda(z)\f$ from @cite Buchalla:1998mt
    * @param[in] z \f$m_c^2/m_b^2\f$
    * @return \f$g_lambda(z)\f$
    */
    double g_lambda(double z);
    
    /**
    * @brief The \f$1/m_b^2\f$ correction to dGamma/ds for @f$B \to X_q l^+ l^-@f$ from @cite Buchalla:1998mt
    * @param[in] sh normalized dilepton invariant mass \f$q^2/m_b^2\f$
    * @param[in] q2region allowed region of dilepton invariant mass @f$q^2@f$
    */
    double deltaMb2_Rquark(double sh, q2regions q2region);
  
    
    /**
    * @brief Auxiliary functions \f$S_{NM}^T\f$ from @cite Huber:2015sra
    * @param[in] sh normalized dilepton invariant mass \f$q^2/m_b^2\f$
    * @param[in] order LO or NLO
    */
    double S77_T(double sh, orders order);
    double S79_T(double sh, orders order);
    double S99_T(double sh, orders order);
    double S1010_T(double sh, orders order);
    
    /**
    * @brief Auxiliary functions \f$S_{NM}^L\f$ from @cite Huber:2015sra
    * @param[in] sh normalized dilepton invariant mass \f$q^2/m_b^2\f$
    * @param[in] order LO or NLO
    */
    double S77_L(double sh, orders order);
    double S79_L(double sh, orders order);
    double S99_L(double sh, orders order);
    double S1010_L(double sh, orders order);
    
    /**
    * @brief Auxiliary functions \f$S_{NM}^A\f$ from @cite Huber:2015sra
    * @param[in] sh normalized dilepton invariant mass \f$q^2/m_b^2\f$
    * @param[in] order LO or NLO
    */
    double S710_A(double sh, orders order);
    double S910_A(double sh, orders order);
    
    /**
    * @brief \f$\mathcal{O}(\Lambda_{QCD}^2/m_c^2)\f$ contributions \f$c_{ij}^I\f$ as defined in @cite Huber:2015sra
    * @param[in] sh normalized dilepton invariant mass \f$q^2/m_b^2\f$
    * @param[in] i,j indices in eq. (4.10) in @cite Huber:2015sra
    */
    gslpp::complex cij_T(unsigned int i, unsigned int j, double sh, orders order);
    gslpp::complex cij_L(unsigned int i, unsigned int j, double sh, orders order);
    gslpp::complex cij_A(unsigned int i, unsigned int j, double sh, orders order);
    
    /**
    * @brief Log-enhanced electromagnetic corrections \f$e_{ij}^I\f$ as defined in @cite Huber:2015sra
    * @param[in] sh normalized dilepton invariant mass \f$q^2/m_b^2\f$
    * @param[in] i,j indices in eq. (4.10) in @cite Huber:2015sra
    */
    gslpp::complex eij_T(unsigned int i, unsigned int j, double sh);
    gslpp::complex eij_L(unsigned int i, unsigned int j, double sh);
    gslpp::complex eij_A(unsigned int i, unsigned int j, double sh);
    
    /**
    * @brief Auxiliary functions \f$omega_{NM}^T\f$ from @cite Huber:2015sra
    * @param[in] sh normalized dilepton invariant mass \f$q^2/m_b^2\f$
    */
    double omega77_T(double sh);
    double omega79_T(double sh);
    double omega99_T(double sh);
    
    /**
    * @brief Auxiliary functions \f$omega_{NM}^L\f$ from @cite Huber:2015sra
    * @param[in] sh normalized dilepton invariant mass \f$q^2/m_b^2\f$
    */
    double omega77_L(double sh);
    double omega79_L(double sh);
    double omega99_L(double sh);
    
    /**
    * @brief Auxiliary functions \f$omega_{NM}^A\f$ from @cite Huber:2015sra
    * @param[in] sh normalized dilepton invariant mass \f$q^2/m_b^2\f$
    */
    double omega710_A(double sh);
    double omega910_A(double sh);
    
    /**
    * @brief Auxiliary functions \f$omega_{NM,T}^{(em)}\f$ from @cite Huber:2015sra
    * @param[in] sh normalized dilepton invariant mass \f$q^2/m_b^2\f$
    */
    double omega77em_T(double sh);
    double omega79em_T(double sh);
    double omega99em_T(double sh);
    double omega22em_T(double sh);
    gslpp::complex omega27em_T(double sh);
    gslpp::complex omega29em_T(double sh);
    
    /**
    * @brief Auxiliary functions \f$omega_{NM,L}^{(em)}\f$ from @cite Huber:2015sra
    * @param[in] sh normalized dilepton invariant mass \f$q^2/m_b^2\f$
    */
    double omega77em_L(double sh);
    double omega79em_L(double sh);
    double omega99em_L(double sh);
    double omega22em_L(double sh);
    gslpp::complex omega27em_L(double sh);
    gslpp::complex omega29em_L(double sh);
    
    /**
    * @brief Auxiliary functions \f$omega_{NM}^A\f$ from @cite Huber:2015sra
    * @param[in] sh normalized dilepton invariant mass \f$q^2/m_b^2\f$
    */
    double omega710em_A(double sh);
    double omega910em_A(double sh);
    gslpp::complex omega210em_A(double sh);
    
    /**
    * @brief Auxiliary function \f$f_{i}\f$ from @cite Huber:2005ig
    * @param[in] sh normalized dilepton invariant mass \f$q^2/m_b^2\f$
    * @param[in] gamma_9 anomalous dimension matrix \f$gamma_{i9^{(01)}}\f$
    * @param[in] rho_c,b,0,num numbers from Table 7 of @cite Huber:2005ig
    */
    gslpp::complex f_Huber(double sh, double gamma_9, double rho_c, double rho_b, double rho_0, double rho_num);
    
    /**
    * @brief Auxiliary function \f$f_{9}^{pen}\f$ from @cite Huber:2005ig
    * @param[in] sh normalized dilepton invariant mass \f$q^2/m_b^2\f$
    */
    gslpp::complex f9pen_Huber(double sh);
    
    /**
    * @brief Auxiliary function \f$g(y)\f$ from @cite Huber:2005ig
    * @param[in] y fraction of z over sh
    */
    gslpp::complex g_Huber(double y);
    
    /**
    * @brief Auxiliary function \f$F(r)\f$ from @cite Buchalla:1997ky
    * @param[in] r normalized dilepton invariant mass \f$q^2/{4 m_c^2}\f$
    */
    gslpp::complex F_BIR(double r);
    
    /**
    * @brief Vector of auxiliary functions \f$M_i^7(sh)\f$ from Table 6 of @cite Huber:2005ig
    * @param[in] sh normalized dilepton invariant mass \f$q^2/m_b^2\f$
    * @param[in] order LO or NLO
    */
    gslpp::vector<gslpp::complex> Mi7(double sh, orders order);
    
    /**
    * @brief Vector of auxiliary functions \f$M_i^9(sh)\f$ from Table 6 of @cite Huber:2005ig
    * @param[in] sh normalized dilepton invariant mass \f$q^2/m_b^2\f$
    * @param[in] order LO or NLO
    */
    gslpp::vector<gslpp::complex> Mi9(double sh, orders order);
    
    /**
    * @brief Vector of auxiliary functions \f$M_i^10(sh)\f$ from Table 6 of @cite Huber:2005ig
    * @param[in] sh normalized dilepton invariant mass \f$q^2/m_b^2\f$
    */
    gslpp::vector<double> Mi10(double sh);
    
    /**
    * @brief Matrix of auxiliary functions \f$H_{ij}^{T}\f$ from @cite Huber:2015sra
    * @param[in] sh normalized dilepton invariant mass \f$q^2/m_b^2\f$
    * @param[in] order LO or NLO
    */
    std::vector< std::vector<Expanded> > matH_T(double sh);
    
    /**
    * @brief Matrix of auxiliary functions \f$H_{ij}^{L}\f$ from @cite Huber:2015sra
    * @param[in] sh normalized dilepton invariant mass \f$q^2/m_b^2\f$
    * @param[in] order LO or NLO
    */
    gslpp::matrix<gslpp::complex> matH_L(double sh, orders order);
    
    /**
    * @brief Angular observable \f$H_T\f$ as defined in @cite Huber:2015sra
    * @param[in] sh normalized dilepton invariant mass \f$q^2/m_b^2\f$
    */
    double H_T (double sh);
    
    /**
    * @brief Angular observable \f$H_L\f$ as defined in @cite Huber:2015sra
    * @param[in] sh normalized dilepton invariant mass \f$q^2/m_b^2\f$
    */
    double H_L (double sh);

    /**
    * @brief Normalization function for \f$B\to X_s\ell\ell\f$ from eq. (4.8) of 1503.04849
    * @param[in] ord/ord_qed order to be returned
    */
    double Phi_u(orders ord);
    double Phi_u(orders_qed ord_qed);
};
#endif	/* BXqLL_H */
