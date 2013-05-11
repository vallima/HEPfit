/* 
 * Copyright (C) 2012-2013 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#ifndef EPSILON1_H
#define	EPSILON1_H

#include <ThObservable.h>
#include "EW.h"

/**
 * @class epsilon1
 * @ingroup EW 
 * @brief A class for the electroweak precision parameter @f$\epsilon_1@f$
 * @author SusyFit Collaboration
 * @copyright GNU General Public License
 * @details This class is used to compute the electroweak precision parameter @f$\epsilon_1@f$. 
 */
class epsilon1 : public ThObservable {
public:

    /**
     * A constructor.
     * @param[in] EW_i A reference to an object of EW class, which is the base class of 
     * the electroweak precision observables.
     */
    epsilon1(const EW& EW_i) 
    : ThObservable(EW_i)//, myEW(EW_i)
    {
    };

    /**
     * @return The electroweak precision parameter @f$\epsilon_1@f$. 
     */
    double getThValue();


private:

    /**
     * A reference to an object of EW class, which is the base class of the electroweak 
     * precision observables.
     */
    //const EW& myEW;
};

#endif	/* EPSILON1_H */

