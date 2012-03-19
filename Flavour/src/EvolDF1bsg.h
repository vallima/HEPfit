/* 
 * File:   EvolDF1bsg.h
 * Author: Mauro_87
 *
 * Created on 11 ottobre 2011, 15.48
 */

#ifndef EVOLDF1BSG_H
#define	EVOLDF1BSG_H


#include <RGEvolutor.h>
#include <StandardModel.h>
#include <sstream>

using namespace gslpp;

class EvolDF1bsg : public RGEvolutor {
/**
 * @class EvolDC1Buras
 * @brief \f$ |\Delta F = 1 | \f$ Evolutor Class
 * @details This evolutor is properly written to study \f$ |\Delta F = 1 | \f$ 
 * processes such as radiative and semileptonic weak decays of the B meson; 
 * it is implemented for the evolution of the 10 Wilson coefficients (related to the 
 * 2 current x current + 4 QCD penguins + em & chromo penguins + 2 semilptonic ones)
 * in the Chetyrkin, Misiak and Munz basis at the NLO in \f$ \alpha_{strong} \f$;
 * principal reference: hep-ph/0612329 
 */
    public:
    /**
     * @brief EvolDF1bsg constructor
     * @param dim an unsigned integer  for the dimension of the evolutor 
     * @param scheme an enum "schemes" for the regularization scheme of the evolutor
     * @param order an enum "orders" for the order of perturbation theory of the evolutor
     * @param model an object of StandardModel class
     */
    EvolDF1bsg(unsigned int dim,  schemes scheme, orders order, const StandardModel& model);
    /**
     * @brief EvolDF1bsg destructor
     */
    virtual ~EvolDF1bsg();
    /**
     * @brief a method returning the anomalous dimension matrix given in the Misiak basis
     * @param order an enum "orders" for the order of perturbation theory of the ADM
     * @param n_u an unsigned integer for the up-type number of d.o.f.
     * @param n_d an unsigned integer for the down-type number of d.o.f.
     * @return the ADM at the order LO/NLO in the Misiak basis
     */
    matrix<double> AnomalousDimension_M(orders order, unsigned int n_u, unsigned int n_d) const;
    /**
     * @brief a method returning the evolutor related to the high scale \f$ M \f$ and the low scale \f$ \mu \f$
     * @param mu a double for the low scale of the evolution
     * @param M a double for the high scale of the evolution
     * @param order an enum "orders" for the order of perturbation theory of the evolutor
     * @param scheme an enum "schemes" for the regularization scheme of the evolutor
     * @return the evolutor \f$ U (\mu , M) \f$
     */
    matrix<double>& Df1Evolbsg(double mu, double M, orders order,  schemes scheme = NDR);
    /**
     * @brief a method returning the anomalous dimension in the Chetyrkin, Misiak and Munz operator basis 
     * @param order an enum "orders" for the order of perturbation theory of the evolutor
     * @param n_u an unsigned integer for the up-type number of d.o.f.
     * @param n_d an unsigned integer for the down-type number of d.o.f.
     * @return the ADM at the order LO/NLO in the Chetyrkin, Misiak and Munz basis
     */
    matrix<double> ToRescaleBasis(orders order, unsigned int n_u, unsigned int n_d) const;
    /**
     * @brief a method returning the anomalous dimension for the evolution of the effective Wilson coefficients
     * @param mat a temporary variable of gslpp::matrix type
     * @return the ADM at the order LO/NLO for the effective Wilson coefficients
     */
    matrix<double> ToEffectiveBasis(matrix<double> mat)const;
    
    private:
    /**
     * @param nu an unsigned integer for the up-type number of d.o.f.
     * @param nu an unsigned integer for the down-type number of d.o.f.
     */
    int nu,nd;
    /**
     * @param a array of double for the magic numbers of the evolutor ( LO evolution )
     * @param b array of double for the magic numbers of the evolutor ( LO evolution ) 
     * @param c array of double for the magic numbers of the evolutor ( NLO evolution, associated to \f$ \alpha_{strong}(\mu) \f$ )
     * @param d array of double for the magic numbers of the evolutor ( NLO evolution, associated to \f$ \alpha_{strong}(M) \f$ )
     */
    double a[3][10], b[3][10][10][10], c[3][10][10][10], d[3][10][10][10];
    const StandardModel& model;
    /**
     * @brief a void type method storing properly the magic numbers for the implementation of the evolutor
     * @param mu a double for the low scale of the evolution
     * @param M a double for the high scale of the evolution
     * @param nf a double for the active number of flavors
     * @param scheme an enum "schemes" for the regularization scheme of the evolutor
     */
    void Df1Evolbsg(double mu, double M, double nf, schemes scheme);
    gslpp::matrix<complex> v, vi, gg, js, h, jv, vij, s_s, jss, jssv;
    gslpp::vector<complex> e;
    
 };


#endif	/* EVOLDF1BSG_H */
