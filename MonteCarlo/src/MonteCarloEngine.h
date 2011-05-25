/* 
 * File:   MonteCarloEngine.h
 * Author: silvest
 *
 * Created on March 8, 2011, 3:18 PM
 */

#ifndef __MONTECARLOENGINE__H
#define __MONTECARLOENGINE__H

#include <BAT/BCModel.h>
#include <BAT/BCH1D.h>
#include <BAT/BCH2D.h>
#include <BAT/BCModelOutput.h>
#include <root/TH1D.h>
#include <root/TH2D.h>
#include <root/TFile.h>
#include <root/TRandom3.h>
#include <Observable.h>
#include <Observable2D.h>
#include <ModelParameter.h>
#include <Model.h>
#include <map>

#define NBINS1D 100
#define NBINS2D 100

class MonteCarloEngine : public BCModel {
public:

    // Constructors and destructor
    MonteCarloEngine(const std::vector<ModelParameter>& ModPars,
            std::vector<Observable>& Obs, 
            std::vector<Observable2D>& Obs2D);
    ~MonteCarloEngine();

    void Initialize(Model* Mod_i);
    
    // Methods to overload, see file MonteCarloEngine.cxx
    void DefineParameters();
    double LogLikelihood(std::vector <double> parameters);
    void PrintHistogram(BCModelOutput& out);
    void MCMCIterationInterface();
    void AddChains();
    double Weight(const Observable& obs, const double& th);
    double Weight(const Observable2D& obs, const double& th1, const double& th2); 

private:
    const std::vector<ModelParameter>& ModPars;
    std::vector<Observable> Obs_MCMC;
    std::vector<Observable>& Obs_ALL; 
    std::vector<Observable2D> Obs2D_MCMC;
    std::vector<Observable2D>& Obs2D_ALL;
    Model* Mod;
    std::map<std::string, double> DPars;
    std::map<std::string, BCH1D * > Histo1D;
    std::map<std::string, TH1D * > InHisto1D;
    std::map<std::string, BCH2D * > Histo2D;
    std::map<std::string, TH2D * > InHisto2D;
    double *obval, *obweight;
};
// ---------------------------------------------------------

#endif