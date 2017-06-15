/* 
 * Copyright (C) 2012 HEPfit Collaboration
 *
 *
 * For the licensing terms see doc/COPYING.
 */

#ifndef STANDARDMODELMATCHING_H
#define	STANDARDMODELMATCHING_H

#include "ModelMatching.h"
#include <gslpp.h>

#define LEPS 1.e-5 // tolerance in the limit of S(x,y) to S(x)

class StandardModel;

/**
 * @class StandardModelMatching
 * @ingroup StandardModel
 * @brief A class for the matching in the Standard Model. 
 * @author HEPfit Collaboration
 * @copyright GNU General Public License
 * @details 
 */
class StandardModelMatching : public ModelMatching {
public:

    StandardModelMatching(const StandardModel & SM_i);
    
    /**
     *
     * @brief Updates to new Standard Model parameter sets.
     */
    
    void updateSMParameters();
    
    /**
     * 
     * @brief \f$ \Delta B = 2 \f$, \f$ B_{d} \f$ 
     * @return return the vector of SM Wilson coefficients
     */
    virtual  std::vector<WilsonCoefficient>& CMdbd2() ;
    
    /**
     * 
     * @brief \f$ \Delta B = 2 \f$, \f$ B_{s} \f$ 
     * @return return the vector of SM Wilson coefficients
     */
    virtual   std::vector<WilsonCoefficient>& CMdbs2() ;
    
    /**
     * 
     * @brief \f$ \Delta C = 2 \f$,
     * @return return the vector of SM Wilson coefficients
     */
    virtual   std::vector<WilsonCoefficient>& CMdd2() ;
    
    /**
     * 
     * @brief \f$ \Delta S = 2 \f$ 
     * @return return the vector of SM Wilson coefficients
     */
    virtual   std::vector<WilsonCoefficient>& CMdk2() ;
        
    /**
     * 
     * @return Wilson coefficients for \f$ K_{L} \rightarrow \pi \nu \nu \f$
     */
    virtual  std::vector<WilsonCoefficient>& CMkpnn() ;
    
    /**
     * 
     * @return Wilson coefficient for \f$ B \rightarrow \tau \nu \f$
     */
    virtual  std::vector<WilsonCoefficient>& CMbtaunu() ;
    
    /**
     * 
     * @return Wilson coefficients for \f$ B_{s} \rightarrow X_{s} \nu \nu \f$
     */
    virtual  std::vector<WilsonCoefficient>& CMBXsnn() ;
    
    /**
     * 
     * @return Wilson coefficients for \f$ B_{d} \rightarrow X_{d} \nu \nu \f$
     */
    virtual   std::vector<WilsonCoefficient>& CMBXdnn() ;
    
     /**
     * 
     * @return Wilson coefficients for \f$ \ell_i \to \ell_j\f$
     */
    virtual  std::vector<WilsonCoefficient>& CMDLij(int li_lj) ;

     /**
     * 
     * @return Wilson coefficients for \f$ \ell_i \to \ell_j\ell_j\ell_j\f$
     */
    virtual  std::vector<WilsonCoefficient>& CMDLi3j(int li_lj) ;

     /**
     * 
     * @return Wilson coefficients for \f$ \mu \to e\f$ conversion in nuclei
     */
    virtual  std::vector<WilsonCoefficient>& CMmueconv() ;

     /**
     * 
     * @return Wilson coefficients for \f$ (g-2)_\mu \f$
     */
    virtual  std::vector<WilsonCoefficient>& CMgminus2mu() ;

    double x_c(const double mu, const orders order = FULLNNLO) const;
    double x_t(const double mu, const orders order = FULLNNLO) const;
    double mt2omh2(const double mu, const orders order = FULLNNLO) const;
    
    /**
     * 
     * @brief loop function which appear in the Wilson coefficient for the magnetic operator
     * in the non-effective Misiak basis, Bobeth et al hep-ph/9910220 
     * @param[in] x the square of the ratio between top mass and W mass
     */
    double A0t(double x)const;
    
    /**
     * 
     * @brief loop function which appear in the Wilson coefficient for the semileptonic operator
     * in the non-effective Misiak basis, Bobeth et al hep-ph/9910220 
     * @param[in] x the square of the ratio between top mass and W mass
     */
    double B0t(double x)const;
    
    /**
     * 
     * @brief loop function which appear in the Wilson coefficient for the magnetic operator
     * in the non-effective Misiak basis, Bobeth et al hep-ph/9910220 
     * @param[in] x the square of the ratio between top mass and W mass
     */
    double C0t(double x)const;
    
    /**
     * 
     * @brief loop function which appear in the Wilson coefficient for the magnetic operator
     * in the non-effective Misiak basis, Bobeth et al hep-ph/9910220 
     * @param[in] x the square of the ratio between top mass and W mass
     */
    double D0t(double x)const;
    
    /**
     * 
     * @brief loop function which appear in the Wilson coefficient for the chromomagnetic operator
     * in the non-effective Misiak basis, Bobeth et al hep-ph/9910220 
     * @param[in] x the square of the ratio between top mass and W mass
     */
    double F0t(double x)const;
    
    /**
     * 
     * @brief loop function which appear in the Wilson coefficient for the chromomagnetic operator
     * in the Misiak basis, Chetyrkin et al hep-ph/9612313 
     * @param[in] x the square of the ratio between top mass and W mass
     */
    double E0t(double x)const;
    
    /**
     * 
     * @brief loop function which appear in the Wilson coefficient for the semileptonic operator
     * in the non-effective Misiak basis, Misiak and Urban hep-ph/9901278v1
     * @param[in] x the square of the ratio between top mass and W mass
     * @param[in] mu the matching scale of the Wilson coefficients
     */
    double A1t(double x, double mu) const;
    
    /**
     * 
     * @brief loop function which appear in the Wilson coefficient for the semileptonic operator
     * in the non-effective Misiak basis, Misiak and Urban hep-ph/9901278v1
     * @param[in] x the square of the ratio between top mass and W mass
     * @param[in] mu the matching scale of the Wilson coefficients
     */
    double B1t(double x, double mu)const;
    
    /**
     * 
     * @brief loop function which appear in the Wilson coefficient for the magnetic operator
     * in the non-effective Misiak basis, Misiak and Urban hep-ph/9901278v1
     * @param[in] x the square of the ratio between top mass and W mass
     * @param[in] mu the matching scale of the Wilson coefficients
     */
    double C1t(double x, double mu)const;
    
    /**
     * 
     * @brief loop function which appear in the Wilson coefficient for the magnetic operator
     * in the non-effective Misiak basis, Misiak and Urban hep-ph/9901278v1
     * @param[in] x the square of the ratio between top mass and W mass
     * @param[in] mu the matching scale of the Wilson coefficients
     */
    double D1t(double x, double mu)const;
    
    /**
     * 
     * @brief loop function which appear in the Wilson coefficient for the semileptonic operator
     * in the non-effective Misiak basis, Misiak and Urban hep-ph/9901278v1
     * @param[in] x the square of the ratio between top mass and W mass
     * @param[in] mu the matching scale of the Wilson coefficients
     */
    double F1t(double x, double mu) const;
    
    /**
     * 
     * @brief loop function which appear in the Wilson coefficient
     * in the non-effective Misiak basis, Misiak and Urban hep-ph/9910220
     * @param[in] x the square of the ratio between top mass and W mass
     * @param[in] mu the matching scale of the Wilson coefficients
     */
    double E1t(double x, double mu) const;
    
    /**
     * 
     * @brief loop function which appear in the Wilson coefficient
     * in the non-effective Misiak basis, Misiak and Urban hep-ph/9910220
     * @param[in] x the square of the ratio between top mass and W mass
     * @param[in] mu the matching scale of the Wilson coefficients
     */
    double G1t(double x, double mu) const;
    
     /**
     * 
     * @brief power expansion appearing in the Wilson coefficient 
     * C7 at NNLO, see Misiak and Steinhauser hep-ph/0401041
     * @param[in] x the square of the ratio between top mass and W mass
     * @param[in] mu the matching scale of the Wilson coefficients
     */
    double C7c_3L_at_mW(double x) const;
    
     /**
     * 
     * @brief power expansion appearing in the Wilson coefficient 
     * C7 at NNLO, see Misiak and Steinhauser hep-ph/0401041
     * @param[in] x the square of the ratio between top mass and W mass
     * @param[in] mu the matching scale of the Wilson coefficients
     */
    double C7t_3L_at_mt(double x) const;
    
     /**
     * 
     * @brief loop function which appear in the Wilson coefficient 
     * C7 at NNLO, see Misiak and Steinhauser hep-ph/0401041
     * @param[in] x the square of the ratio between top mass and W mass
     * @param[in] mu the matching scale of the Wilson coefficients
     */
    double C7t_3L_func(double x, double mu) const;
    
     /**
     * 
     * @brief power expansion appearing in the Wilson coefficient 
     * C8 at NNLO, see Misiak and Steinhauser hep-ph/0401041
     * @param[in] x the square of the ratio between top mass and W mass
     * @param[in] mu the matching scale of the Wilson coefficients
     */
    double C8c_3L_at_mW(double x) const;
    
     /**
     * 
     * @brief power expansion appearing in the Wilson coefficient 
     * C8 at NNLO, see Misiak and Steinhauser hep-ph/0401041
     * @param[in] x the square of the ratio between top mass and W mass
     * @param[in] mu the matching scale of the Wilson coefficients
     */
    double C8t_3L_at_mt(double x) const;
    
     /**
     * 
     * @brief loop function which appear in the Wilson coefficient 
     * C8 at NNLO, see Misiak and Steinhauser hep-ph/0401041
     * @param[in] x the square of the ratio between top mass and W mass
     * @param[in] mu the matching scale of the Wilson coefficients
     */
    double C8t_3L_func(double x, double mu) const;

    /**
     * 
     * @brief loop function which appear in the Wilson coefficient
     * in the non-effective Misiak basis, Misiak and Urban hep-ph/9910220
     * @param[in] x the square of the ratio between top mass and W mass
     * @param[in] mu the matching scale of the Wilson coefficients
     */
    double Tt(double x) const;
    
    /**
     * 
     * @brief loop function which appear in the Wilson coefficient
     * in the non-effective Misiak basis, Misiak and Urban hep-ph/0512066
     * @param[in] x the square of the ratio between top mass and W mass
     * @param[in] mu the matching scale of the Wilson coefficients
     */
    double Wt(double x) const;
    
    /**
     * 
     * @brief loop function which appear in the Wilson coefficient
     * in the non-effective Misiak basis, Misiak and Urban hep-ph/0512066
     * @param[in] x the square of the ratio between top mass and W mass
     * @param[in] mu the matching scale of the Wilson coefficients
     */
    double Eet(double x) const;
    
    /**
     * 
     * @brief approximation of two-loops EW correction for Q_10 operator
     * in the non-effective Misiak basis, Misiak and Urban hep-ph/1311.1348
     * @param[in] x the square of the ratio between top mass and W mass
     * @param[in] mu the matching scale of the Wilson coefficients
     */
    double Rest(double x, double mu) const;
    
    /**
     *
     * @param[in] x the square of the ratio between top mass and W mass
     * @return 0th order loop function for the top contribution to K_L -> mu mu decays
     */
    double Y0(double x)const;
    
    /**
     *
     * @param[in] x the square of the ratio between top mass and W mass
     * @param[in] mu the matching scale of the Wilson coefficients
     * @return first order in QCD loop function for the top contribution to K_L -> mu mu decays
     */
    double Y1(double x, double mu)const;
    
    /**
     * 
     * @brief loop function which appear in the Wilson coefficient for the magnetic operator
     * in the effective Misiak basis, LO term, Chetyrkin et al hep-ph/9612313 
     * @param[in] x the square of the ratio between top mass and W mass
     */
    double C7LOeff(double x)const;
    
    /**
     * 
     * @brief loop function which appear in the Wilson coefficient for the magnetic operator
     * in the effective Misiak basis, NLO term, Chetyrkin et al hep-ph/9612313 
     * @param[in] x the square of the ratio between top mass and W mass
     */
    double C7NLOeff(double x)const;
    
    /**
     * 
     * @brief loop function which appear in the Wilson coefficient for the chromomagnetic operator
     * in the effective Misiak basis, LO term, Chetyrkin et al hep-ph/9612313 
     * @param[in] x the square of the ratio between top mass and W mass
     */
    double C8LOeff(double x)const;
    
    /**
     * 
     * @brief loop function which appear in the Wilson coefficient for the chromomagnetic operator
     * in the effective Misiak basis, LO term, Chetyrkin et al hep-ph/9612313 
     * @param[in] x the square of the ratio between top mass and W mass
     */
    double C8NLOeff(double x)const;

    /**
     * 
     * @brief loop functions for non-leptonic B decays, Buiras Basis
     * Buras et al, hep-ph/9512380v1
     * @param[in] x the square of the ratio between top mass and W mass
     */
    double B0b(double x)const;
    
    /**
     * 
     * @brief loop functions for non-leptonic B decays, Buiras Basis
     * Buras et al, hep-ph/9512380v1
     * @param[in] x the square of the ratio between top mass and W mass
     */
    double C0b(double x)const;
    
    /**
     * 
     * @brief loop functions for non-leptonic B decays, Buiras Basis
     * Buras et al, hep-ph/9512380v1
     * @param[in] x the square of the ratio between top mass and W mass
     */
    double D0b(double x)const;
    
    /**
     * 
     * @brief loop functions for non-leptonic B decays, Buras Basis
     * Buras et al, hep-ph/9512380
     * @param[in] x the square of the ratio between top mass and W mass
     */
    double D0b_tilde(double x)const;
    
    /**
     * 
     * @brief loop functions for non-leptonic B decays, Buiras Basis
     * Buras et al, hep-ph/9512380v1
     * @param[in] x the square of the ratio between top mass and W mass
     */
    double E0b(double x)const;
    
    /**
     * 
     * @brief loop functions for QED corrections of Delta F = 1 decays
     * Buras, Gambino, Haisch, hep-ph/9911250
     * @param[in] x the square of the ratio between top mass and W mass
     * @param[in] mu the matching scale of the Wilson coefficients
     */
    double B1d(double x, double mu)const;
    
    /**
     * 
     * @brief loop functions for QED corrections of Delta F = 1 decays
     * Buras, Gambino, Haisch, hep-ph/9911250
     * @param[in] x the square of the ratio between top mass and W mass
     * @param[in] mu the matching scale of the Wilson coefficients
     */
    double B1d_tilde(double x, double mu)const;
    
    /**
     * 
     * @brief loop functions for QED corrections of Delta F = 1 decays
     * Buras, Gambino, Haisch, hep-ph/9911250
     * @param[in] x the square of the ratio between top mass and W mass
     * @param[in] mu the matching scale of the Wilson coefficients
     */
    double B1u(double x, double mu)const;
    
    /**
     * 
     * @brief loop functions for QED corrections of Delta F = 1 decays
     * Buras, Gambino, Haisch, hep-ph/9911250
     * @param[in] x the square of the ratio between top mass and W mass
     * @param[in] mu the matching scale of the Wilson coefficients
     */
    double B1u_tilde(double x, double mu)const;
    
    /**
     * 
     * @brief loop functions for QED corrections of Delta F = 1 decays
     * Buras, Gambino, Haisch, hep-ph/9911250
     * @param[in] x the square of the ratio between top mass and W mass
     */
    double C1ew(double x)const;
    
    /**
     * 
     * @brief auxiliary loop function for QED corrections of Delta F = 1 decays
     * Buras, Gambino, Haisch, hep-ph/9911250
     * @param[in] xt the square of the ratio between top mass and W mass
     * @param[in] xz the square of the ratio between Z mass and W mass
     */
    double Zew(double xt, double xz)const;
        
    /**
     * 
     * @brief loop functions for QED corrections of Delta F = 1 decays
     * Buras, Gambino, Haisch, hep-ph/9911250
     * @param[in] xt the square of the ratio between top mass and W mass
     * @param[in] xz the square of the ratio between Z mass and W mass
     * @param[in] mu the matching scale of the Wilson coefficients
     */
    double Gew(double xt, double xz, double mu)const;
    
    /**
     * 
     * @brief loop functions for QED corrections of Delta F = 1 decays
     * Buras, Gambino, Haisch, hep-ph/9911250
     * @param[in] xt the square of the ratio between top mass and W mass
     * @param[in] xz the square of the ratio between Z mass and W mass
     * @param[in] mu the matching scale of the Wilson coefficients
     */
    double Hew(double xt, double xz, double mu)const;
    
    /**
     *  
     * @brief hep-ph/9512380
     * @return the loop function for the charm-charm contribution to the Delta S = 2 effective hamiltonian multiplied by the CKM element 
     */
    gslpp::complex S0c() const;
    
    /**
     *  
     * @brief hep-ph/9512380
     * @return the loop function for the charm-top contribution to the Delta S = 2 effective hamiltonian multiplied by the CKM element 
     */
    gslpp::complex S0ct() const;
    
    /**
     *  
     * @brief hep-ph/9512380v1
     * @return the loop function for the top-top contribution to the Delta S = 2 effective hamiltonian
     */
    gslpp::complex S0tt() const;
    
    /**
     *
     * @brief hep-ph/9512380v1
     * @param[in] x the square of the ratio between top mass and W mass
     * @return 0th order loop function for the top contribution to K -> pi nu nu decays
     */
    double X0t(double x)const;
    
    /**
     *
     * @brief hep-ph/1009.0947v2
     * @param[in] x the square of the ratio between top mass and W mass
     * @return first order in QCD loop function for the top contribution to K -> pi nu nu decays
     */
    double X1t(double x)const;
    
    /**
     *
     * @brief hep-ph/1009.0947v2
     * @param[in] x the square of the ratio between top mass and W mass
     * @param[in] a
     * @param[in] mu
     * @return two loop EW loop function for the top contribution to K -> pi nu nu decays
     * in the limit of small theta_W
     */
    double Xewt(double x, double a, double mu)const;

    /**
     *
     * @param[in] x the square of the ratio between top mass and W mass
     * @return
     */

    double S1(double x) const;

    virtual double S0(double, double) const;

    /*
     * Wilson coefficients Misiak basis
     * Operator block: L (2)
     * Normalization: 4 G_F / sqrt(2) x CKM
     */
    virtual std::vector<WilsonCoefficient> CMDF1s(std::string blocks, unsigned int nops, schemes scheme, orders order);

     
protected:
    std::vector<WilsonCoefficient> vmcDF1s;
    std::vector<WilsonCoefficient> vmcdb, vmcds, vmcd2, vmck2;
    std::vector<WilsonCoefficient> vmckpnn, vmcbsnn, vmcbdnn, vmcbtaunu;
    std::vector<WilsonCoefficient> vmcDLij, vmcDLi3j, vmcmueconv, vmcgminus2mu;
    std::vector<WilsonCoefficient> vmcCs, vmcPs, vmcMs, vmcLs, vmcQs, vmcBs;
    std::vector<WilsonCoefficient> vmcCe, vmcPe, vmcMe, vmcLe, vmcQe, vmcBe;
    
private:
    unsigned int setCMDF1(WilsonCoefficient& CMDF1, WilsonCoefficient& DF1block, unsigned int nops, unsigned int tot, schemes scheme, orders order);

    /*
     * Wilson coefficients Misiak basis
     * Operator block: C (2)
     * Normalization: 4 G_F / sqrt(2) x CKM
     */
    std::vector<WilsonCoefficient>& mc_Cs();

    /*
     * Wilson coefficients Misiak basis
     * Operator block: P (4)
     * Normalization: 4 G_F / sqrt(2) x CKM
     */
    std::vector<WilsonCoefficient>& mc_Ps();

    /*
     * Wilson coefficients Misiak basis
     * Operator block: M (2)
     * Normalization: 4 G_F / sqrt(2) x CKM
     */
    std::vector<WilsonCoefficient>& mc_Ms();

    /*
     * Wilson coefficients Misiak basis
     * Operator block: L (2)
     * Normalization: 4 G_F / sqrt(2) x CKM
     */
    std::vector<WilsonCoefficient>& mc_Ls();

    /*
     * Wilson coefficients Misiak basis
     * Operator block: Q (4)
     * Normalization: 4 G_F / sqrt(2) x CKM
     */
    std::vector<WilsonCoefficient>& mc_Qs();

    /*
     * Wilson coefficients Misiak basis
     * Operator block: B (1)
     * Normalization: 4 G_F / sqrt(2) x CKM
     */
    std::vector<WilsonCoefficient>& mc_Bs();

    /*
     * Wilson coefficients Misiak basis
     * Operator block: C (2)
     * QED corrections
     * Normalization: 4 G_F / sqrt(2) x CKM
     */
    std::vector<WilsonCoefficient>& mc_Ce();

    /*
     * Wilson coefficients Misiak basis
     * Operator block: P (4)
     * QED corrections
     * Normalization: 4 G_F / sqrt(2) x CKM
     */
    std::vector<WilsonCoefficient>& mc_Pe();

    /*
     * Wilson coefficients Misiak basis, effective basis
     * Operator block: M (2)
     * QED corrections
     * Normalization: 4 G_F / sqrt(2) x CKM
     * Only available at NLO and in approximate formulas
     * ref.: Gambino, Haisch, JHEP 0110, 020, hep-ph/0109058
     */
    std::vector<WilsonCoefficient>& mc_Me();

    /*
     * Wilson coefficients Misiak basis, effective basis
     * Operator block: L (2)
     * QED corrections
     * Normalization: 4 G_F / sqrt(2) x CKM
     */
    std::vector<WilsonCoefficient>& mc_Le();

    /*
     * Wilson coefficients Misiak basis
     * Operator block: Q (4)
     * QED corrections
     * Normalization: 4 G_F / sqrt(2) x CKM
     */
    std::vector<WilsonCoefficient>& mc_Qe();

    /*
     * Wilson coefficients Misiak basis
     * Operator block: B (1)
     * QED corrections
     * Normalization: 4 G_F / sqrt(2) x CKM
     */
    std::vector<WilsonCoefficient>& mc_Be();
        
    /**
     * 
     * @param z
     * @return two loop EW loop functions for K-> P nu nu, hep-ph/1009.0947v2 
     */
    double phi1(double z) const;
    
    /**
     * 
     * @param x
     * @param y
     * @return two loop EW loop functions for K-> P nu nu, hep-ph/1009.0947v2 
     */
    double phi2 (double x, double y) const;
    
    /**
     * 
     * @param z
     * @return two loop EW loop functions, hep-ph/9911250 
     */
    double phi_z(double z) const;
    
    /**
     * 
     * @param x
     * @param y
     * @return two loop EW loop functions, hep-ph/9911250 
     */
    double phi_xy (double x, double y) const;
    
    /**
     * 
     * @param x \f$ \frac{m_t^2}{M_W^2} \f$
     * @return function appearing in the matching condition for \f$ C_3 \f$ 
     */
    double C3funNNLO(double x);
    
    /**
     * 
     * @param x \f$ \frac{m_t^2}{M_W^2} \f$
     * @param ord NLO or NNLO
     * @return function appearing in the matching condition for \f$ C_4 \f$ 
     */
    double C4fun(double x, orders ord);

    /**
     * 
     * @param x \f$ \frac{m_t^2}{M_W^2} \f$
     * @return function appearing in the matching condition for \f$ C_5 \f$ 
     */
    double C5funNNLO(double x);

    /**
     * 
     * @param x \f$ \frac{m_t^2}{M_W^2} \f$
     * @return function appearing in the matching condition for \f$ C_6 \f$ 
     */
    double C6funNNLO(double x);
    
    /**
     * 
     * @param x \f$ \frac{m_t^2}{M_W^2} \f$
     * @return function appearing in the matching condition for \f$ C_7 \f$ 
     */
    double C7funLO(double x);
    
    /**
     * 
     * @param x \f$ \frac{m_t^2}{M_W^2} \f$
     * @return function appearing in the matching condition for \f$ C_8 \f$ 
     */
    double C8funLO(double x);
    
    friend double gslpp_special_functions::dilog(double x);
    friend double gslpp_special_functions::clausen(double x);
    friend double gslpp_special_functions::zeta(int i);
    
    const StandardModel & SM;
    double S0(double) const;
    double S0p(double x) const;
    double S11(double x) const;
    double S18(double x) const;

    WilsonCoefficient mcdbd2, mcdbs2, mcdd2, mcdk2;
    WilsonCoefficient mckpnn, mcbsnn, mcbdnn, mcbtaunu;
    WilsonCoefficient mcDLij,mcDLi3j,mcmueconv,mcgminus2mu;
    WilsonCoefficient mcCs, mcPs, mcMs, mcLs, mcQs, mcBs;
    WilsonCoefficient mcCe, mcPe, mcMe, mcLe, mcQe, mcBe;
    
    double Mut, Muw, Ale, GF, Mw_tree, Nc, CF, Mt_muw, Mt_mut;
    double gamma0, J5, BtNDR, Mw, sW2, mu_b;
    double L, sw, Lz;
    double alstilde, aletilde;
    

    gslpp::complex lam_t;
    const gslpp::matrix<gslpp::complex>& Vckm;
};

#endif	/* STANDARDMODELMATCHING_H */
