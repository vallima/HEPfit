/* 
 * File:   OneLoopEW.h
 * Author: mishima
 */

#ifndef ONELOOPEW_H
#define	ONELOOPEW_H

#include <StandardModel.h>
#include "EWSMcommon.h"

using namespace gslpp;


class OneLoopEW : public EWSMcommon {
    
public:

    /**
     * @brief OneLoopEW constructor
     * @param[in] EWSMC_i reference to an EWSMcommon object
     */
    OneLoopEW(const EWSMcommon& EWSMC_i);

    /**
     * @brief OneLoopEW copy constructor
     * @param[in] orig reference to a OneLoopEW object
     */
    //OneLoopEW(const OneLoopEW& orig);

    /**
     * @brief OneLoopEW destructor
     */
    virtual ~OneLoopEW();


    ////////////////////////////////////////////////////////////////////////

    /**
     * @brief leptonic contribution to alpha
     * @return Delta alpha_{lept}^{alpha}
     */
    double DeltaAlpha_l() const;

    /**
     * @brief top-quark contribution to alpha
     * @return Delta alpha_{top}^{alpha}
     */
    double DeltaAlpha_t() const;

    /**
     * @brief leading contribution to Delta r
     * @return Delta rho^{G}
     */
    double DeltaRho() const;

    /**
     * @brief remainder contribution to Delta r
     * @return Delta r_{rem}^{alpha}
     */
    double DeltaR_rem() const;

    /**
     * @brief remainder contribution for rho_Z^f and kappa_Z^f
     * @return Delta rbar_{rem}^{G}
     */
    double DeltaRbar_rem() const;

    /**
     * @brief remainder contribution to rho_Z^l
     * @param[in] l name of a lepton 
     * @return delta rho_{rem}^{l, G}
     */
    complex deltaRho_rem_l(const StandardModel::lepton l) const;

    /**
     * @brief remainder contribution to rho_Z^q
     * @param[in] q name of a quark 
     * @return delta rho_{rem}^{q, G}
     */
    complex deltaRho_rem_q(const StandardModel::quark q) const;

    /**
     * @brief remainder contribution to kappa_Z^l
     * @param[in] l name of a lepton 
     * @return delta kappa_{rem}^{l, G}
     */
    complex deltaKappa_rem_l(const StandardModel::lepton l) const;

    /**
     * @brief remainder contribution to kappa_Z^q
     * @param[in] q name of a quark 
     * @return delta kappa_{rem}^{q, G}
     */
    complex deltaKappa_rem_q(const StandardModel::quark q) const;
    
    
    ////////////////////////////////////////////////////////////////////////    
    
private:


    ////////////////////////////////////////////////////////////////////////    
       

    
};

#endif	/* ONELOOPEW_H */
