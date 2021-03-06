/*
 * Copyright (C) 2014 HEPfit Collaboration
 *
 *
 * For the licensing terms see doc/COPYING.
 */

/**
 * @example libmode_config.cpp
 * This is an example of how to compute observables from the input parameters
 * defined in a model configuration file.
 *
 */

#include <iostream>
#include <ComputeObservables.h>
#include "HeffDF1.h"
#include "HeffDB1.h"
#include "EvolDB1Mll.h"
#include "EvolDB1bsg.h"
#include "EvolBsmm.h"
#include "BXqll.h"


int main(void) {

    /* Define the model configuration file.                        */
    /* Here it is passed as the first argument to the executable.  */
    /* The model configuration file provides the default values of */
    /* the mandatory model parameters.                             */
    std::string ModelConf = "StandardModel.conf";

    /* Define a map for the parameters to be varied. */
    std::map<std::string, double> DPars;

    /* Create objects of the classes ModelFactory and ThObsFactory */
    ModelFactory ModelF;
    ThObsFactory ThObsF;

    /* register user-defined model named ModelName defined in class ModelClass using the following syntax: */
    /* ModelF.addModelToFactory(ModelName, boost::factory<ModelClass*>() ) */

    /* register user-defined ThObservable named ThObsName defined in class ThObsClass using the following syntax: */
    /* ThObsF.addObsToFactory(ThObsName, boost::factory<ThObsClass*>() )*/

    /* Create an object of the class ComputeObservables. */
    ComputeObservables CO(ModelF, ThObsF, ModelConf);
    StandardModel& mySM = *CO.getModel();

    HeffDF1 Heff("CPM", mySM, NNLO, NO_QED);
    HeffDB1 HDB1(mySM);
//    CO.AddObservable("Rlow_BXsee");
//    /* Get the map of observables if necessary. */
//    std::map<std::string, double> DObs = CO.getObservables();
//
//    DObs = CO.compute(DPars);
//    
//    std::cout << DObs.at("Rlow_BXsee") << std::endl;

    std::cout << "%SUITE_STARTING% Evolutor" << std::endl;
    std::cout << "%SUITE_STARTED% **é***" << std::endl;
    gslpp::vector<gslpp::complex> ** allcoeff, **allcoeff1;

    gslpp::matrix<gslpp::complex> myVCKM(mySM.getVCKM());
    double sw = sqrt( (M_PI * mySM.getAle() ) / ( sqrt(2.) * mySM.getGF() * mySM.Mw() * mySM.Mw() ) );
//    double sw = sqrt(mySM.sW2());
    double as5 =  mySM.Alstilde5(5.);
    double ae5 = mySM.getAle() / 4. / M_PI;

    std::cout << "%SUITE_STARTED% **é***" << std::endl;

    allcoeff = Heff.ComputeCoeff(5.);
    allcoeff1 = HDB1.ComputeCoeffsgamma(5.);

    std::cout << "LO:" << std::endl;
    std::cout << (*(allcoeff[LO])) <<  std::endl;
    std::cout << (*(allcoeff[LO])) - *(allcoeff1[LO]) <<  std::endl;
   
    std::cout << "NLO:" << std::endl;
    std::cout << (*(allcoeff[NLO])) <<  std::endl;
    std::cout << (*(allcoeff[NLO])) - (*(allcoeff1[NLO])) <<  std::endl;

    std::cout << "NNLO:" << std::endl;
    std::cout << (*(allcoeff[NNLO]))  <<  std::endl;    
    std::cout << (*(allcoeff[NNLO])) - (*(allcoeff1[NNLO])) <<  std::endl;

// test di CPL   
    std::cout << "studente: " << as5*4.*M_PI << ", grande unificazione: " << mySM.Als(3, FULLNNNLO, true) << " -- "  << mySM.Als(3, FULLNNNLO, true, false) << std::endl;
//    std::cout << "LO:" << std::endl;
//    std::cout << sw*sw*(myVCKM(2,2).conjugate() * myVCKM(2,1))*(*(allcoeff[LO])) - *(allcoeff1[LO]) <<  std::endl;
//    
//    std::cout << "NLO:" << std::endl;
//    std::cout << sw*sw*(myVCKM(2,2).conjugate() * myVCKM(2,1))*(*(allcoeff[NLO])) - as5*(*(allcoeff1[NLO])) <<  std::endl;
//
//    std::cout << "NNLO:" << std::endl;
//    std::cout << sw*sw*(myVCKM(2,2).conjugate() * myVCKM(2,1))*(*(allcoeff[NNLO])) - as5*as5*(*(allcoeff1[NNLO])) <<  std::endl;
//
//    std::cout << "LO_QED:" << std::endl;
//    std::cout << sw*sw*(myVCKM(2,2).conjugate() * myVCKM(2,1))*(*(allcoeff[LO_QED])) - ae5/as5*(*(allcoeff1[LO_QED])) <<  std::endl;
//
//    std::cout << "NLO_QED11:" << std::endl;
//    std::cout << sw*sw*(myVCKM(2,2).conjugate() * myVCKM(2,1))*(*(allcoeff[NLO_QED11])) - ae5*(*(allcoeff1[NLO_QED11])) <<  std::endl;
//
//    std::cout << "NLO_QED02:" << std::endl;
//    std::cout << sw*sw*(myVCKM(2,2).conjugate() * myVCKM(2,1))*(*(allcoeff[NLO_QED02])) - ae5*ae5/as5/as5*(*(allcoeff1[NLO_QED02])) <<  std::endl;
//
//    std::cout << "NLO_QED12:" << std::endl;
//    std::cout << sw*sw*(myVCKM(2,2).conjugate() * myVCKM(2,1))*(*(allcoeff[NLO_QED12]))- ae5*ae5/as5*(*(allcoeff1[NLO_QED12])) <<  std::endl;
//
//    std::cout << "NLO_QED21:" << std::endl;
//    std::cout << sw*sw*(myVCKM(2,2).conjugate() * myVCKM(2,1))*(*(allcoeff[NLO_QED21]))- ae5*as5*(*(allcoeff1[NLO_QED21])) <<  std::endl;
//
//    std::cout << "NLO_QED11+22:" << std::endl;
//    std::cout << myVCKM(2,2).conjugate() * myVCKM(2,1) * (*(allcoeff[NLO_QED11]) +
//            *(allcoeff[NLO_QED22])) - mySM.getGF() / sqrt(8.) * mySM.Mw() * mySM.Mw() / M_PI /M_PI *
//            (*(allcoeff1[NLO_QED11]) +  ae5 * (*(allcoeff1[NLO_QED22]))) <<  std::endl;
    
//   std::cout << *(allcoeff[NLO]) <<  std::endl;
//    std::cout << *(allcoeff[NNLO]) <<  std::endl;
//    std::cout << *(allcoeff[LO_QED]) <<  std::endl;    
//    std::cout << Heff.LowScaleCoeff(22) <<  std::endl;    
    
//    std::cout << *(mySM.getMatching().CMDF1("C",2)[0].getCoeff(LO)) <<  std::endl;    
//    std::cout << *(mySM.getMatching().CMDF1("C",2)[0].getCoeff(NLO)) <<  std::endl;    
//    std::cout << *(mySM.getMatching().CMDF1("C",2)[0].getCoeff(NNLO)) <<  std::endl;    

//    gslpp::matrix<gslpp::complex> myVCKM(mySM.getVCKM());
//    double sw = sqrt( (M_PI * mySM.getAle() ) / ( sqrt(2.) * mySM.getGF() * mySM.Mw() * mySM.Mw() ) );
////    double sw = sqrt(mySM.sW2());
//    double as5 =  mySM.Alstilde5(mySM.getMuw());
//    double ae5 = mySM.getAle() / 4. / M_PI;
//    std::cout << sw*sw*(myVCKM(2,2).conjugate() * myVCKM(2,1))*(*(mySM.getMatching().CMDF1("CPML",10)[0].getCoeff(LO_QED))) <<  std::endl;    
//    std::cout << *(mySM.getMatching().CMbsmm()[0].getCoeff(LO_QED)) << std::endl;
//    std::cout << std::endl;
//    std::cout << sw*sw*(myVCKM(2,2).conjugate() * myVCKM(2,1))*(*(mySM.getMatching().CMDF1("CPML",10)[0].getCoeff(NLO_QED11))) <<  std::endl;    
//    std::cout << ae5*(*(mySM.getMatching().CMbsmm()[0].getCoeff(NLO_QED11))) << std::endl;
//    std::cout << std::endl;
//    std::cout << sw*sw*(myVCKM(2,2).conjugate() * myVCKM(2,1))*(*(mySM.getMatching().CMDF1("CPML",10)[0].getCoeff(NLO_QED02))) <<  std::endl;    
//    std::cout << ae5*ae5/as5/as5*(*(mySM.getMatching().CMbsmm()[0].getCoeff(NLO_QED02))) << std::endl;
//    std::cout << std::endl;
//    std::cout << sw*sw*(myVCKM(2,2).conjugate() * myVCKM(2,1))*(*(mySM.getMatching().CMDF1("CPML",10)[0].getCoeff(NLO_QED21))) <<  std::endl;    
//    std::cout << as5*ae5*(*(mySM.getMatching().CMbsmm()[0].getCoeff(NLO_QED21))) << std::endl;
//    std::cout << std::endl;
//    std::cout << sw*sw*(myVCKM(2,2).conjugate() * myVCKM(2,1))*(*(mySM.getMatching().CMDF1("CPML",10)[0].getCoeff(NLO_QED12))) <<  std::endl;    
//    std::cout << ae5*ae5/as5*(*(mySM.getMatching().CMbsmm()[0].getCoeff(NLO_QED12))) << std::endl;
//    std::cout << std::endl;
//    std::cout << sw*sw*(myVCKM(2,2).conjugate() * myVCKM(2,1))*(*(mySM.getMatching().CMDF1("CPML",10)[0].getCoeff(NLO_QED22))) <<  std::endl;    
//    std::cout << ae5*ae5*(*(mySM.getMatching().CMbsmm()[0].getCoeff(NLO_QED22))) << std::endl;    

//test OK  (up to 10-14)
//    std::cout << Heff.getEvol().AnomalousDimension(10, 2, 3) - HDB1.getUBsmm().AnomalousDimension(10, 2, 3) << std::endl;
//    std::cout << Heff.getEvol().AnomalousDimension(20, 2, 3) - HDB1.getUBsmm().AnomalousDimension(20, 2, 3) << std::endl;
//    std::cout << Heff.getEvol().AnomalousDimension(30, 2, 3) - HDB1.getUBsmm().AnomalousDimension(30, 2, 3) << std::endl;          
//    std::cout << Heff.getEvol().AnomalousDimension(01, 2, 3) - HDB1.getUBsmm().AnomalousDimension(01,2,3) <<  std::endl;
//    std::cout << Heff.getEvol().AnomalousDimension(02, 2, 3) - HDB1.getUBsmm().AnomalousDimension(02,2,3) <<  std::endl;
//    std::cout << Heff.getEvol().AnomalousDimension(11, 2, 3) - HDB1.getUBsmm().AnomalousDimension(11,2,3) <<  std::endl;
//    std::cout << Heff.getEvol().AnomalousDimension(21, 2, 3) - HDB1.getUBsmm().AnomalousDimension(21,2,3) <<  std::endl;

//
//      std::cout << Heff.getEvol().DF1Evol(5., 90., LO) << std::endl;
////    std::cout << HDB1.getUDF1BMll().Df1EvolMll(5., 90., LO) << std::endl;
//      std::cout << HDB1.getUDB1bsg().Df1Evolbsg(5., 90., LO) << std::endl;
//
//    std::cout << Heff.getEvol().DF1Evol(5., 90., NLO, NO_QED) << std::endl;
////    std::cout << HDB1.getUDF1BMll().Df1EvolMll(5., 90., NLO) << std::endl;
//    std::cout << HDB1.getUDB1bsg().Df1Evolbsg(5., 90., NLO) << std::endl;
//    
//    std::cout << Heff.getEvol().DF1Evol(5., 90., NNLO, NO_QED) << std::endl;
////    std::cout << HDB1.getUDF1BMll().Df1EvolMll(5., 90., NLO) << std::endl;
//    std::cout << HDB1.getUDB1bsg().Df1Evolbsg(5., 90., NNLO) << std::endl;
//
////    std::cout << Heff.getEvol().DF1Evol(2., 90., LO, NO_QED) << std::endl;
////    std::cout << HDB1.getUDF1BMll().Df1EvolMll(2., 90., LO) << std::endl;
////    std::cout << HDB1.getUDB1bsg().Df1Evolbsg(5., 90., LO) << std::endl;
////    std::cout << Heff.getEvol().DF1Evol(2., 90., NLO, NO_QED) << std::endl;
////    std::cout << HDB1.getUDF1BMll().Df1EvolMll(2., 90., NLO) << std::endl;
//    
////    std::cout << Heff.getEvol().DF1Evol(1., 90., LO, NO_QED) << std::endl;
////    std::cout << HDB1.getUDF1BMll().Df1EvolMll(1., 90., LO) << std::endl;
////    std::cout << HDB1.getUDB1bsg().Df1Evolbsg(5., 90., LO) << std::endl;
////    std::cout << Heff.getEvol().DF1Evol(1., 90., NLO, NO_QED) << std::endl;
////    std::cout << HDB1.getUDF1BMll().Df1EvolMll(1., 90., NLO) << std::endl;
}