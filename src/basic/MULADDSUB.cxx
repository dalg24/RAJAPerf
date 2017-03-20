/*!
 ******************************************************************************
 *
 * \file
 *
 * \brief   Implementation file for Basic kernel MULADDSUB.
 *
 ******************************************************************************
 */

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Copyright (c) 2017, Lawrence Livermore National Security, LLC.
//
// Produced at the Lawrence Livermore National Laboratory
//
// LLNL-CODE-xxxxxx
//
// All rights reserved.
//
// This file is part of the RAJA Performance Suite.
//
// For additional details, please read the file LICENSE.
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//


#include "MULADDSUB.hxx"

#include "common/DataUtils.hxx"

#include <iostream>

namespace rajaperf 
{
namespace basic
{

#define MULADDSUB_DATA 

#define MULADDSUB_BODY(i) 


MULADDSUB::MULADDSUB(const RunParams& params)
  : KernelBase(rajaperf::Basic_MULADDSUB, params)
{
   setDefaultSize(100000);
   setDefaultSamples(10000);
}

MULADDSUB::~MULADDSUB() 
{
}

void MULADDSUB::setUp(VariantID vid)
{
}

void MULADDSUB::runKernel(VariantID vid)
{
  int run_size = getRunSize();
  int run_samples = getRunSamples();

  switch ( vid ) {

    case Baseline_Seq : {

      MULADDSUB_DATA;

      startTimer();
#if 0
      for (SampIndex_type isamp = 0; isamp < run_samples; ++isamp) {

        for (RAJA::Index_type i = 0; i < run_size; ++i ) {
          MULADDSUB_BODY(i);
        }

      }
#endif
      stopTimer();

      break;
    }

    case RAJA_Seq : {

      MULADDSUB_DATA;

      startTimer();
#if 0
      for (SampIndex_type isamp = 0; isamp < run_samples; ++isamp) {

        RAJA::forall<RAJA::simd_exec>(0, run_size, [=](int i) {
          MULADDSUB_BODY(i);
        });

      }
#endif
      stopTimer();

      break;
    }

    case Baseline_OpenMP : {

      MULADDSUB_DATA;

      startTimer();
#if 0
      for (SampIndex_type isamp = 0; isamp < run_samples; ++isamp) {

        #pragma omp for schedule(static)
        for (RAJA::Index_type i = 0; i < run_size; ++i ) {
          MULADDSUB_BODY(i);
        }

      }
#endif
      stopTimer();

      break;
    }

    case RAJALike_OpenMP : {
      // case is not defined...
      break;
    }

    case RAJA_OpenMP : {

      MULADDSUB_DATA;

      startTimer();
#if 0
      for (SampIndex_type isamp = 0; isamp < run_samples; ++isamp) {

        RAJA::forall<RAJA::omp_parallel_for_exec>(0, run_size, [=](int i) {
          MULADDSUB_BODY(i);
        });

      }
#endif
      stopTimer();

      break;
    }

    case Baseline_CUDA : {

      MULADDSUB_DATA;

      startTimer();
#if 0
      for (SampIndex_type isamp = 0; isamp < run_samples; ++isamp) {

      }
#endif
      stopTimer();

      break;
    }

    case RAJA_CUDA : {

      MULADDSUB_DATA;

      startTimer();
#if 0
      for (SampIndex_type isamp = 0; isamp < run_samples; ++isamp) {

      }
#endif
      stopTimer();

      break;
    }

#if 0
    case Baseline_OpenMP4x :
    case RAJA_OpenMP4x : {
      // Fill these in later...you get the idea...
      break;
    }
#endif

    default : {
      std::cout << "\n  Unknown variant id = " << vid << std::endl;
    }

  }

}

void MULADDSUB::updateChecksum(VariantID vid)
{
#if 0
  checksum[vid] += calcChecksum(m_p_new, getRunSize());
#endif
}

void MULADDSUB::tearDown(VariantID vid)
{
  switch ( vid ) {

    case Baseline_Seq :
    case RAJA_Seq :
    case Baseline_OpenMP :
    case RAJA_OpenMP :
    case Baseline_CUDA :
    case RAJA_CUDA : {
      // De-allocate host memory here.
      break;
    }

#if 0
    case Baseline_OpenMP4x :
    case RAJA_OpenMP4x : {
      // De-allocate host and device memory here.
      break;
    }
#endif

    default : {
      std::cout << "\n  Unknown variant id = " << vid << std::endl;
    }

  }

  if (vid == Baseline_CUDA || vid == RAJA_CUDA) {
    // De-allocate device memory here.
  }
}

} // end namespace basic
} // end namespace rajaperf
