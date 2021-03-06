/*
 * Copyright (C) 2017 HEPfit Collaboration
 *
 *
 * For the licensing terms see doc/COPYING.
 */

#ifndef THDMWPOSITIVITY_H
#define	THDMWPOSITIVITY_H

#include "ThObservable.h"
#include "THDMW.h"

/**
 * @class THDMWpositivity
 * @ingroup THDMW 
 * @brief Base class for "boundedness-from-below" constraints
 * @author HEPfit Collaboration
 * @copyright GNU General Public License
 * @details Formulae taken from @cite Deshpande:1977rw.
 */

/**
 * @class THDMWpositivity1
 * @brief Controls that the scalar %THDMW potential is bounded from below.
 * @details @f$\lambda_3>-\sqrt{\lambda_1 \lambda_2}@f$.
 * @author HEPfit Collaboration
 * @copyright GNU General Public License
 */
class THDMWpositivity1: public ThObservable {
public:

    /**
     * @brief THDMWpositivity1 constructor.
     */
    THDMWpositivity1(const StandardModel& SM_i);

    /**
     * @return @f$\lambda_3+\sqrt{\lambda_1 \lambda_2}@f$
     */
    double computeThValue();
private:
    const THDMW& myTHDMW;
};

/**
 * @class THDMWpositivity2
 * @brief Controls that the scalar %THDMW potential is bounded from below.
 * @details @f$\lambda_3+\lambda_4-|\lambda_5|>-\sqrt{\lambda_1 \lambda_2}@f$.
 * @author HEPfit Collaboration
 * @copyright GNU General Public License
 */
class THDMWpositivity2: public ThObservable {
public:

    /**
     * @brief THDMWpositivity2 constructor.
     */
    THDMWpositivity2(const StandardModel& SM_i);

    /**
     * @return @f$\lambda_3+\lambda_4-|\lambda_5|+\sqrt{\lambda_1 \lambda_2}@f$
     */
    double computeThValue();
private:
    const THDMW& myTHDMW;
};

#endif	/* THDMWPOSITIVITY_H */
