/* 
 * Copyright (C) 2012-2013 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#ifndef __MONTECARLOENGINE__H
#define __MONTECARLOENGINE__H

#include <BAT/BCModel.h>
#include <BAT/BCH1D.h>
#include <BAT/BCH2D.h>
#include <BAT/BCModelOutput.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TFile.h>
#include <TRandom3.h>
#include <Observable.h>
#include <Observable2D.h>
#include <CorrelatedGaussianObservables.h>
#include <ModelParaVsObs.h>
#include <ModelParameter.h>
#include <Model.h>
#include <map>
#include <string>
#include <sstream>

#define NBINSMODELPARS 100
#define NBINS1D 100
#define NBINS2D 100

/**
 * @class MonteCarloEngine
 * @ingroup MonteCarlo 
 * @brief An engine class for Monte Carlo. 
 * @author SusyFit Collaboration
 * @copyright GNU General Public License
 * @details  
 */
class MonteCarloEngine : public BCModel {
public:

    // Constructors and destructor
    MonteCarloEngine(const std::vector<ModelParameter>& ModPars_i,
                     std::vector<Observable>& Obs_i,
                     std::vector<Observable2D>& Obs2D_i,
                     std::vector<CorrelatedGaussianObservables>& CGO_i,
                     std::vector<ModelParaVsObs>& ParaObs_i,
                     const bool checkHistRange_i=false);
    ~MonteCarloEngine();

    void Initialize(Model* Mod_i);
    
    // Methods to overload, see file MonteCarloEngine.cxx
    void DefineParameters();
    double LogLikelihood(const std::vector <double>& parameters);
    void CheckHistogram(const TH1D& hist, const std::string name);
    void CheckHistogram(const TH2D& hist, const std::string name);
    void PrintHistogram(BCModelOutput & out, std::vector<Observable>::iterator it,
                        const std::string OutputDir);
    void PrintHistogram(BCModelOutput& out, const std::string OutputDir);
    void MCMCIterationInterface();
    void setNChains(unsigned int i);
    void AddChains();
    double Weight(const Observable& obs, const double& th);
    double Weight(const Observable2D& obs, const double& th1, const double& th2);    
    double Weight(const CorrelatedGaussianObservables& obs);
    void generateRandomEvent(Model* Mod_i, int iterationNo);
    Model* getMod() const
    {
        return Mod;
    }

    void setMod(Model* Mod)
    {
        this->Mod = Mod;
    }
    
    std::string getHistoLog() const 
    {
        return HistoLog.str().c_str();
    }

    void PrintCorrelationMatrix(const std::string filename);

    int getNumOfDiscardedEvents() const
    {
        return NumOfDiscardedEvents;
    }

    int getNumOfUsedEvents() const
    {
        return NumOfUsedEvents;
    }

private:
    const std::vector<ModelParameter>& ModPars;
    std::vector<Observable> Obs_MCMC;
    std::vector<Observable>& Obs_ALL; 
    std::vector<Observable2D> Obs2D_MCMC;
    std::vector<Observable2D>& Obs2D_ALL;
    std::vector<CorrelatedGaussianObservables>& CGO;
    std::vector<ModelParaVsObs>& ParaObs;
    Model* Mod;
    std::map<std::string, double> DPars;
    std::map<std::string, BCH1D * > Histo1D;
    std::map<std::string, TH1D * > InHisto1D;
    std::map<std::string, BCH2D * > Histo2D;
    std::map<std::string, TH2D * > InHisto2D;
    std::map<std::string, double> thMin;
    std::map<std::string, double> thMax;
    double *obval, *obweight;
    unsigned int kwmax, kmax;
    std::ostringstream HistoLog;
    int NumOfUsedEvents;
    int NumOfDiscardedEvents;
    bool checkTheoryRange;
    
};

#endif

