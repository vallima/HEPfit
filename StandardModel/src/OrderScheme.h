/* 
 * Copyright (C) 2012 HEPfit Collaboration
 *
 *
 * For the licensing terms see doc/COPYING.
 */

#ifndef ORDERSCHEME_H
#define	ORDERSCHEME_H

#define MAXORDER FULLNNNLO
#define MAXORDER_QED FULLNLO_QED

/**
 * @enum schemes
 * @ingroup StandardModel
 * @brief An enum type for regularization schemes.
 */
enum schemes
{
    NDR = 0, /**< Naive dimensional regularization (NDR) scheme */
    HV, /**< 't Hooft-Veltman (HV) scheme */
    LRI /**< Regularization-Independent (RI) renormalization schemes with the Landau gauge */
};

/**
 * @enum orders
 * @ingroup StandardModel
 * @brief An enum type for orders in %QCD.
 */
enum orders
{
    LO = 0, /**< Leading order */
    NLO, /**< Next-to-leading order */
    NNLO, /**< Next-to-next-to-leading order */
    NNNLO, /**< Next-to-next-to-next-to-leading order */
    FULLNLO, /**< Full NLO = LO + NLO */
    FULLNNLO, /**< Full NNLO = LO + NLO + NNLO */
    FULLNNNLO /**< Full NNLO = LO + NLO + NNLO + NNNLO */        
};

/**
 * @enum orders_qed
 * @ingroup StandardModel
 * @brief An enum type for orders in electroweak.
 */
enum orders_qed
{
    NO_QED = orders(MAXORDER) + 1, /**< An auxiliary enumerator */
    LO_QED, /**< Leading order e/s */
    NLO_QED11, /**< Next-to-leading order e */
    NLO_QED02,   /* e^2/s^2 */
    NLO_QED21,     /* e*s */
    NLO_QED12,    /* e^2/s */
    NLO_QED22,     /* e^2 */
    FULLNLO_QED /**< Full NLO_QED = LO + NLO + LO_QED + NLO_QED +...+ NLO_QED22 */
};

#endif	/* ORDERSCHEME_H */