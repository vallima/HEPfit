/*
 * Copyright (C) 2017 HEPfit Collaboration
 *
 *
 * For the licensing terms see doc/COPYING.
 */

#ifndef HIGGSCHIRAL_H
#define	HIGGSCHIRAL_H
#include "NPbase.h"

/**
 * @class HiggsChiral
 * @ingroup HiggsExtensions
 * @brief A model class extending the %StandardModel Higgs sector with 
 * @author HEPfit Collaboration
 * @copyright GNU General Public License
 * @details 

 * @anchor HiggsChiralParameters
 * <h3>%Model parameters</h3>
 *
 * The model parameters of %HiggsChiral (in addition to the %StandardModel ones) are summarized below:
 * <table class="model">
 * <tr>
 *   <th>Label</th>
 *   <th>LaTeX symbol</th>
 *   <th>Description</th>
 * </tr>
 * <tr>
 *   <td class="mod_name">%cv</td>
 *   <td class="mod_symb">@f$c_V@f$</td>
 *   <td class="mod_desc"></td>
 * </tr>
 * <tr>
 *   <td class="mod_name">%ct</td>
 *   <td class="mod_symb">@f$c_t@f$</td>
 *   <td class="mod_desc"></td>
 * </tr>
 * <tr>
 *   <td class="mod_name">%cb</td>
 *   <td class="mod_symb">@f$c_b@f$</td>
 *   <td class="mod_desc"></td>
 * </tr>
 * <tr>
 *   <td class="mod_name">%ctau</td>
 *   <td class="mod_symb">@f$c_\tau@f$</td>
 *   <td class="mod_desc"></td>
 * </tr>
 * <tr>
 *   <td class="mod_name">%cmu</td>
 *   <td class="mod_symb">@f$c_\mu@f$</td>
 *   <td class="mod_desc"></td>
 * </tr>
 * <tr>
 *   <td class="mod_name">%cg</td>
 *   <td class="mod_symb">@f$c_g@f$</td>
 *   <td class="mod_desc"></td>
 * </tr>
 * <tr>
 *   <td class="mod_name">%cga</td>
 *   <td class="mod_symb">@f$c_\gamma@f$</td>
 *   <td class="mod_desc"></td>
 * </tr>
 * <tr>
 *   <td class="mod_name">%cZga</td>
 *   <td class="mod_symb">@f$c_{Z\gamma}@f$</td>
 *   <td class="mod_desc"></td>
 * </tr>
 * </table>
 * 
 */
class HiggsChiral : public NPbase {
public:

    static const int NHChiralvars = 8; ///< The number of the model parameters.

    /**
     * @brief A string array containing the labels of the model parameters in %HiggsKvKf.
     */
    static const std::string HChiralvars[NHChiralvars];

    /**
     * @brief The default constructor.
     */
    HiggsChiral();

    /**
     * @brief The default destructor.
     */
    virtual ~HiggsChiral()
    {
    };

    /**
     * @brief .
     * @return @f$c_V@f$
     */
    double getcv() const
    {
        return cv;
    }

    /**
     * @brief .
     * @return @f$c_t@f$
     */
    double getct() const
    {
        return ct;
    }

    /**
     * @brief .
     * @return @f$c_b@f$
     */
    double getcb() const
    {
        return cb;
    }

    /**
     * @brief .
     * @return @f$c_\tau@f$
     */
    double getctau() const
    {
        return ctau;
    }

    /**
     * @brief .
     * @return @f$c_\mu@f$
     */
    double getcmu() const
    {
        return cmu;
    }

    /**
     * @brief .
     * @return @f$c_g@f$
     */
    double getcg() const
    {
        return cg;
    }

    /**
     * @brief .
     * @return @f$c_\gamma@f$
     */
    double getcga() const
    {
        return cga;
    }

    /**
     * @brief .
     * @return @f$c_{Z\gamma}@f$
     */
    double getcZga() const
    {
        return cZga;
    }

    /**
     * @brief A method to check if all the mandatory parameters for %HiggsChiral
     * have been provided in model initialization.
     * @param[in] DPars a map of the parameters that are being updated in the Monte Carlo run
     * (including parameters that are varied and those that are held constant)
     * @return a boolean that is true if the execution is successful
     */
    virtual bool CheckParameters(const std::map<std::string, double>& DPars);

    ////////////////////////////////////////////////////////////////////////

    /**
     * @brief The ratio @f$\mu_{ggH}@f$ between the gluon-gluon fusion Higgs
     * production cross-section in the current model and in the Standard Model.
     * @param[in] sqrt_s the center-of-mass energy in TeV
     * @return @f$\mu_{ggH}@f$
     */
    virtual double muggH(const double sqrt_s) const;
    /**
     * @brief The ratio @f$\mu_{VBF}@f$ between the vector-boson fusion Higgs
     * production cross-section in the current model and in the Standard Model. 
     * @param[in] sqrt_s the center-of-mass energy in TeV
     * @return @f$\mu_{VBF}@f$
     */
    virtual double muVBF(const double sqrt_s) const;
    /**
     * @brief The ratio @f$\mu_{eeWBF}@f$ between the 
     * @f$ e^{+}e^{-}\to \nu\bar{\nu} H @f$ production
     * cross-section in the current model and in the Standard Model.
     * @param[in] sqrt_s the center-of-mass energy in TeV
     * @return @f$\mu_{eeWBF}@f$
     */
    virtual double mueeWBF(const double sqrt_s) const;
    /**
     * @brief The ratio @f$\mu_{WH}@f$ between the W-Higgs associated production
     * cross-section in the current model and in the Standard Model. 
     * @param[in] sqrt_s the center-of-mass energy in TeV
     * @return @f$\mu_{WH}@f$
     */
    virtual double muWH(const double sqrt_s) const;
    /**
     * @brief The ratio @f$\mu_{ZH}@f$ between the Z-Higgs associated production
     * cross-section in the current model and in the Standard Model.
     * @param[in] sqrt_s the center-of-mass energy in TeV
     * @return @f$\mu_{ZH}@f$
     */
    virtual double muZH(const double sqrt_s) const;
    /**
     * @brief The ratio @f$\mu_{eeZH}@f$ between the 
     * @f$e^{+}e^{-}\to ZH@f$ associated production
     * cross-section in the current model and in the Standard Model.
     * @param[in] sqrt_s the center-of-mass energy in TeV
     * @return @f$\mu_{eeZH}@f$
     */
    virtual double mueeZH(const double sqrt_s) const;
    /**
     * @brief The ratio @f$\mu_{VH}@f$ between the WH+ZH associated production
     * cross-section in the current model and in the Standard Model.
     * @param[in] sqrt_s the center-of-mass energy in TeV
     * @return @f$\mu_{VH}@f$
     */
    virtual double muVH(const double sqrt_s) const;
    /**
     * @brief The ratio @f$\mu_{VBF+VH}@f$ between the sum of VBF and WH+ZH associated production
     * cross-section in the current model and in the Standard Model.
     * @param[in] sqrt_s the center-of-mass energy in TeV
     * @return @f$\mu_{VBF+VH}@f$
     */
    virtual double muVBFpVH(const double sqrt_s) const;
    /**
     * @brief The ratio @f$\mu_{ttH}@f$ between the t-tbar-Higgs associated 
     * production cross-section in the current model and in the Standard Model.
     * @param[in] sqrt_s the center-of-mass energy in TeV
     * @return @f$\mu_{ttH}@f$
     */
    virtual double muttH(const double sqrt_s) const;
    /**
     * @brief The ratio @f$\mu_{ggH+ttH}@f$ between the sum of gluon-gluon fusion
     * and t-tbar-Higgs associated 
     * production cross-section in the current model and in the Standard Model.
     * @param[in] sqrt_s the center-of-mass energy in TeV
     * @return @f$\mu_{ggH+ttH}@f$
     */
    virtual double muggHpttH(const double sqrt_s) const;
    /**
     * @brief The ratio @f$\mu_{eettH}@f$ between the 
     * @f$ e^{+}e^{-}\to t\bar{t} H @f$ production
     * cross-section in the current model and in the Standard Model.
     * @param[in] sqrt_s the center-of-mass energy in TeV
     * @return @f$\mu_{eettH}@f$
     */
    virtual double mueettH(const double sqrt_s) const;
    /**
     * @brief The ratio of the Br@f$(H\to gg)@f$ in the current model
     * and in the Standard Model.
     * @return Br@f$(H\to gg)@f$/Br@f$(H\to gg)_{\mathrm{SM}}@f$
     */
    virtual double BrHggRatio() const;
    /**
     * @brief The ratio of the Br@f$(H\to WW)@f$ in the current model
     * and in the Standard Model.
     * @return Br@f$(H\to WW)@f$/Br@f$(H\to WW)_{\mathrm{SM}}@f$
     */
    virtual double BrHWWRatio() const;
    /**
     * @brief The ratio of the Br@f$(H\to ZZ)@f$ in the current model
     * and in the Standard Model.
     * @return Br@f$(H\to ZZ)@f$/Br@f$(H\to ZZ)_{\mathrm{SM}}@f$
     */
    virtual double BrHZZRatio() const;
    /**
     * @brief The ratio of the Br@f$(H\to Z\gamma)@f$ in the current model
     * and in the Standard Model.
     * @return Br@f$(H\to Z\gamma)@f$/Br@f$(H\to Z\gamma)_{\mathrm{SM}}@f$
     */
    virtual double BrHZgaRatio() const;
    /**
     * @brief The ratio of the Br@f$(H\to \gamma\gamma)@f$ in the current model
     * and in the Standard Model.
     * @return Br@f$(H\to \gamma\gamma)@f$/Br@f$(H\to \gamma\gamma)_{\mathrm{SM}}@f$
     */
    virtual double BrHgagaRatio() const;
    /**
     * @brief The ratio of the Br@f$(H\to \mu^+\mu^-)@f$ in the current model
     * and in the Standard Model.
     * @return Br@f$(H\to \mu^+\mu^-)@f$/Br@f$(H\to \mu^+\mu^-)_{\mathrm{SM}}@f$
     */
    virtual double BrHmumuRatio() const;
    /**
     * @brief The ratio of the Br@f$(H\to \tau^+\tau^-)@f$ in the current model
     * and in the Standard Model.
     * @return Br@f$(H\to \tau^+\tau^-)@f$/Br@f$(H\to \tau^+\tau^-)_{\mathrm{SM}}@f$
     */
    virtual double BrHtautauRatio() const;
    /**
     * @brief The ratio of the Br@f$(H\to c\bar{c})@f$ in the current model
     * and in the Standard Model.
     * @return Br@f$(H\to c\bar{c})@f$/Br@f$(H\to c\bar{c})_{\mathrm{SM}}@f$
     */
    virtual double BrHccRatio() const;
    /**
     * @brief The ratio of the Br@f$(H\to b\bar{b})@f$ in the current model
     * and in the Standard Model.
     * @return Br@f$(H\to b\bar{b})@f$/Br@f$(H\to b\bar{b})_{\mathrm{SM}}@f$
     */
    virtual double BrHbbRatio() const;
    /**
     * @brief The ratio of the @f$\Gamma(H)@f$ in the current model
     * and in the Standard Model.
     * @return @f$\Gamma(H)@f$/@f$\Gamma(H)_{\mathrm{SM}}@f$
     */
    virtual double computeGammaTotalRatio() const;

    ////////////////////////////////////////////////////////////////////////
protected:

    /**
     * @brief A method to set the value of a parameter of %HiggsChiral.
     * @param[in] name name of a model parameter
     * @param[in] value the value to be assigned to the parameter specified by name
     */
    virtual void setParameter(const std::string name, const double& value);

    /**
     * @brief A method to compute the ratio of the @f$Hgg@f$ coupling in the current model and in the SM.
     * @return the ratio of the @f$Hgg@f$ coupling in the current model and in the SM
     */
    virtual double computeKg(const double sqrt_s) const;

    /**
     * @brief A method to compute the ratio of the @f$HWW@f$ coupling in the current model and in the SM.
     * @return the ratio of the @f$HWW@f$ coupling in the current model and in the SM
     */
    virtual double computeKW() const;

    /**
     * @brief A method to compute the ratio of the @f$HZZ@f$ coupling in the current model and in the SM.
     * @return the ratio of the @f$HZZ@f$ coupling in the current model and in the SM
     */
    virtual double computeKZ() const;

    /**
     * @brief A method to compute the ratio of the @f$HZ\gamma@f$ coupling in the current model and in the SM.
     * @return the ratio of the @f$HZ\gamma@f$ coupling in the current model and in the SM
     */
    virtual double computeKZga() const;

    /**
     * @brief A method to compute the ratio of the @f$H\gamma\gamma@f$ coupling in the current model and in the SM.
     * @return the ratio of the @f$H\gamma\gamma@f$ coupling in the current model and in the SM
     */
    virtual double computeKgaga() const;
    
    /**
     * @brief A method to compute the ratio of the @f$H\mu\mu@f$ coupling in the current model and in the SM.
     * @return the ratio of the @f$H\mu\mu@f$ coupling in the current model and in the SM
     */
    virtual double computeKmu() const;

    /**
     * @brief A method to compute the ratio of the @f$H\tau\tau@f$ coupling in the current model and in the SM.
     * @return the ratio of the @f$H\tau\tau@f$ coupling in the current model and in the SM
     */
    virtual double computeKtau() const;

    /**
     * @brief A method to compute the ratio of the @f$Hcc@f$ coupling in the current model and in the SM.
     * @return the ratio of the @f$Hcc@f$ coupling in the current model and in the SM
     */
    virtual double computeKc() const;

    /**
     * @brief A method to compute the ratio of the @f$Htt@f$ coupling in the current model and in the SM.
     * @return the ratio of the @f$Htt@f$ coupling in the current model and in the SM
     */
    virtual double computeKt() const;

    /**
     * @brief A method to compute the ratio of the @f$Hbb@f$ coupling in the current model and in the SM.
     * @return the ratio of the @f$Hbb@f$ coupling in the current model and in the SM
     */
    virtual double computeKb() const;

    ////////////////////////////////////////////////////////////////////////
private:
    double cv; ///< 
    double ct; ///< 
    double cb; ///< 
    double ctau; ///< 
    double cmu; ///< 
    double cg; ///< 
    double cga; ///< 
    double cZga; ///< 
};

#endif	/* HIGGSCHIRAL_H */