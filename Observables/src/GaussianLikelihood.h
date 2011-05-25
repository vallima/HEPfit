/* 
 * File:   GaussianLikelihood.h
 * Author: silvest
 *
 * Created on February 22, 2011, 12:23 PM
 */

#ifndef GAUSSIANLIKELIHOOD_H
#define	GAUSSIANLIKELIHOOD_H

#include "Likelihood.h"

class GaussianLikelihood : public Likelihood {
public:
    GaussianLikelihood(const double mean, const double sigma);
    GaussianLikelihood(const GaussianLikelihood& orig);
    virtual ~GaussianLikelihood();
    double getLikelihood(const double value) const;
private:
    double mean, sigma;
};

#endif	/* GAUSSIANLIKELIHOOD_H */