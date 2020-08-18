/*
 * This file is part of the saf_tracker module.
 * Copyright (c) 2020 - Leo McCormack
 *
 * The saf_tracker module is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * The saf_tracker module is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * See <http://www.gnu.org/licenses/> for a copy of the GNU General Public
 * License.
 */

/**
 * @file saf_tracker_internal.h
 * @brief Particle filtering based tracker
 *
 * Based on the RBMCDA Matlab toolbox (GPLv2 license) by Simo Särkkä and Jouni
 * Hartikainen (Copyright (C) 2003-2008):
 *     https://users.aalto.fi/~ssarkka/#softaudio
 *
 * And also inspired by the work of Sharath Adavanne, Archontis Politis, Joonas
 * Nikunen, and Tuomas Virtanen (GPLv2 license):
 *     https://github.com/sharathadavanne/multiple-target-tracking
 *
 * @author Leo McCormack
 * @date 04.07.2020
 */

#ifndef __SAF_TRACKER_INTERNAL_H_INCLUDED__
#define __SAF_TRACKER_INTERNAL_H_INCLUDED__

#include <stdio.h>
#include <math.h>
#include <string.h>
#include "saf_tracker.h"
#include "saf.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */ 
    
/* ========================================================================== */
/*                            Internal Parameters                             */
/* ========================================================================== */



/* ========================================================================== */
/*                            Internal Structures                             */
/* ========================================================================== */

/** Monte Carlo Sample (particle) structure */
typedef struct _MCS{
    float W;        /**< Importance weight */
    int nTargets;   /**< Number of targets being tracked */
    int nActive;    /**< Number of active targets */
    int B;          /**< Birth indicator (non-zero indicates new birth with
                     *   index of the value of 'B') */
    int D;          /**< Death indicator (non-zero indicates new death with
                     *   index of the value of 'D') */
    float dt;       /**< Elapsed time inbetween each observation/measurment */
    float* M[6];    /**< Current target means; nTargets x ([6]) */
    float* P[6][6]; /**< Current target variances; nTargets x ([6][6]) */
    float M0[6];    /**< 0,1,2: Position of sound source PRIORs (x,y,z), 3,4,5:
                     *   Mean velocity PRIORs (x,y,z) */
    float P0[6][6]; /**< Diagonal matrix, 0,1,2: Variance PRIORs of estimates
                     *   along the x,y,z axes; 3,4,5 Velocity PRIORs of
                     *   estimates along the x,y,z axes */
    int* targetIDs; /**< Unique ID assigned to each target; nTargets x 1 */
    int* activeIDs; /**< IDs of targets currently active; nActive x 1 */
    int* Tcount;    /**< Time elapsed since birth of target: Tcount * dt;
                     *   nTargets x 1 */

} MCS_data;

/** Main structure for tracker3d */
typedef struct _tracker3dlib
{
    /** User parameters struct */
    tracker3d_config tpars;

    /* Internal */
    MCS_data* S;    /**< The particles; tpars.Np x 1 */ 
    float R[3][3];  /**< Diagonal matrix, measurement noise PRIORs along the
                     *   x,y,z axes */
    float A[6][6];  /**< Transition matrix */
    float H[3][6];  /**< Measurement matrix */

    
} tracker3dlib_data;
     

/* ========================================================================== */
/*                             Internal Functions                             */
/* ========================================================================== */



#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* __SAF_TRACKER_INTERNAL_H_INCLUDED__ */