/*!
 ******************************************************************************
 *
 * \file
 *
 * \brief   Implementation file for kernel VOL3D.
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


#include "VOL3D.hpp"

#include "AppsData.hpp"
#include "common/DataUtils.hpp"

#include "RAJA/RAJA.hpp"

#include <iostream>

namespace rajaperf 
{
namespace apps
{

#define VOL3D_DATA \
  ResReal_ptr x = m_x; \
  ResReal_ptr y = m_y; \
  ResReal_ptr z = m_z; \
  ResReal_ptr vol = m_vol; \
\
  const Real_type vnormq = m_vnormq;
\
  ResReal_ptr x0,x1,x2,x3,x4,x5,x6,x7 ; \
  ResReal_ptr y0,y1,y2,y3,y4,y5,y6,y7 ; \
  ResReal_ptr z0,z1,z2,z3,z4,z5,z6,z7 ;


#define VOL3D_BODY \
  Real_type x71 = x7[i] - x1[i] ; \
  Real_type x72 = x7[i] - x2[i] ; \
  Real_type x74 = x7[i] - x4[i] ; \
  Real_type x30 = x3[i] - x0[i] ; \
  Real_type x50 = x5[i] - x0[i] ; \
  Real_type x60 = x6[i] - x0[i] ; \
 \
  Real_type y71 = y7[i] - y1[i] ; \
  Real_type y72 = y7[i] - y2[i] ; \
  Real_type y74 = y7[i] - y4[i] ; \
  Real_type y30 = y3[i] - y0[i] ; \
  Real_type y50 = y5[i] - y0[i] ; \
  Real_type y60 = y6[i] - y0[i] ; \
 \
  Real_type z71 = z7[i] - z1[i] ; \
  Real_type z72 = z7[i] - z2[i] ; \
  Real_type z74 = z7[i] - z4[i] ; \
  Real_type z30 = z3[i] - z0[i] ; \
  Real_type z50 = z5[i] - z0[i] ; \
  Real_type z60 = z6[i] - z0[i] ; \
 \
  Real_type xps = x71 + x60 ; \
  Real_type yps = y71 + y60 ; \
  Real_type zps = z71 + z60 ; \
 \
  Real_type cyz = y72 * z30 - z72 * y30 ; \
  Real_type czx = z72 * x30 - x72 * z30 ; \
  Real_type cxy = x72 * y30 - y72 * x30 ; \
  vol[i] = xps * cyz + yps * czx + zps * cxy ; \
 \
  xps = x72 + x50 ; \
  yps = y72 + y50 ; \
  zps = z72 + z50 ; \
 \
  cyz = y74 * z60 - z74 * y60 ; \
  czx = z74 * x60 - x74 * z60 ; \
  cxy = x74 * y60 - y74 * x60 ; \
  vol[i] += xps * cyz + yps * czx + zps * cxy ; \
 \
  xps = x74 + x30 ; \
  yps = y74 + y30 ; \
  zps = z74 + z30 ; \
 \
  cyz = y71 * z50 - z71 * y50 ; \
  czx = z71 * x50 - x71 * z50 ; \
  cxy = x71 * y50 - y71 * x50 ; \
  vol[i] += xps * cyz + yps * czx + zps * cxy ; \
 \
  vol[i] *= vnormq ;


#if defined(RAJA_ENABLE_CUDA)

  //
  // Define thread block size for CUDA execution
  //
  const size_t block_size = 256;


#define VOL3D_DATA_SETUP_CUDA \
  Real_ptr x; \
  Real_ptr y; \
  Real_ptr z; \
  Real_ptr vol; \
\
  const Real_type vnormq = m_vnormq; \
\
  Real_ptr x0,x1,x2,x3,x4,x5,x6,x7 ; \
  Real_ptr y0,y1,y2,y3,y4,y5,y6,y7 ; \
  Real_ptr z0,z1,z2,z3,z4,z5,z6,z7 ; \
\
  allocAndInitCudaDeviceData(x, m_x, iend); \
  allocAndInitCudaDeviceData(y, m_y, iend); \
  allocAndInitCudaDeviceData(z, m_z, iend); \
  allocAndInitCudaDeviceData(vol, m_vol, iend);

#define VOL3D_DATA_TEARDOWN_CUDA \
  getCudaDeviceData(m_vol, vol, iend); \
  deallocCudaDeviceData(x); \
  deallocCudaDeviceData(y); \
  deallocCudaDeviceData(z); \
  deallocCudaDeviceData(vol);

__global__ void vol3d(Real_ptr vol,
                      const Real_ptr x0, const Real_ptr x1,
                      const Real_ptr x2, const Real_ptr x3,
                      const Real_ptr x4, const Real_ptr x5,
                      const Real_ptr x6, const Real_ptr x7,
                      const Real_ptr y0, const Real_ptr y1,
                      const Real_ptr y2, const Real_ptr y3,
                      const Real_ptr y4, const Real_ptr y5,
                      const Real_ptr y6, const Real_ptr y7,
                      const Real_ptr z0, const Real_ptr z1,
                      const Real_ptr z2, const Real_ptr z3,
                      const Real_ptr z4, const Real_ptr z5,
                      const Real_ptr z6, const Real_ptr z7,
                      const Real_type vnormq,
                      Index_type ibegin, Index_type ilen)
{
   Index_type ii = blockIdx.x * blockDim.x + threadIdx.x;
   if (ii < ilen) {
     Index_type i = ii + ibegin; 
     VOL3D_BODY;
   }
}

#endif // if defined(RAJA_ENABLE_CUDA)


VOL3D::VOL3D(const RunParams& params)
  : KernelBase(rajaperf::Apps_VOL3D, params)
{
  setDefaultSize(64);  // See rzmax in ADomain struct
  setDefaultSamples(320);

  m_domain = new ADomain(getRunSize(), /* ndims = */ 3);
}

VOL3D::~VOL3D() 
{
  delete m_domain;
}

void VOL3D::setUp(VariantID vid)
{
  int max_loop_index = m_domain->lpn;

  allocAndInitData(m_x, max_loop_index, vid);
  allocAndInitData(m_y, max_loop_index, vid);
  allocAndInitData(m_z, max_loop_index, vid);
  allocAndInitData(m_vol, max_loop_index, vid);

  m_vnormq = 0.083333333333333333; /* vnormq = 1/12 */  
}

void VOL3D::runKernel(VariantID vid)
{
  const Index_type run_samples = getRunSamples();
  const Index_type ibegin = m_domain->fpz;
  const Index_type iend = m_domain->lpz+1;

  switch ( vid ) {

    case Baseline_Seq : {

      VOL3D_DATA;

      NDPTRSET(m_domain->jp, m_domain->kp, x,x0,x1,x2,x3,x4,x5,x6,x7) ;
      NDPTRSET(m_domain->jp, m_domain->kp, y,y0,y1,y2,y3,y4,y5,y6,y7) ;
      NDPTRSET(m_domain->jp, m_domain->kp, z,z0,z1,z2,z3,z4,z5,z6,z7) ;

      startTimer();
      for (SampIndex_type isamp = 0; isamp < run_samples; ++isamp) {

        for (Index_type i = ibegin ; i < iend ; ++i ) {
          VOL3D_BODY;
        }

      }
      stopTimer();

      break;
    } 

    case RAJA_Seq : {

      VOL3D_DATA;

      NDPTRSET(m_domain->jp, m_domain->kp, x,x0,x1,x2,x3,x4,x5,x6,x7) ;
      NDPTRSET(m_domain->jp, m_domain->kp, y,y0,y1,y2,y3,y4,y5,y6,y7) ;
      NDPTRSET(m_domain->jp, m_domain->kp, z,z0,z1,z2,z3,z4,z5,z6,z7) ;

      startTimer();
      for (SampIndex_type isamp = 0; isamp < run_samples; ++isamp) {

        RAJA::forall<RAJA::simd_exec>(ibegin, iend, [=](int i) {
          VOL3D_BODY;
        }); 

      }
      stopTimer(); 

      break;
    }

#if defined(_OPENMP)      
    case Baseline_OpenMP : {

      VOL3D_DATA;

      NDPTRSET(m_domain->jp, m_domain->kp, x,x0,x1,x2,x3,x4,x5,x6,x7) ;
      NDPTRSET(m_domain->jp, m_domain->kp, y,y0,y1,y2,y3,y4,y5,y6,y7) ;
      NDPTRSET(m_domain->jp, m_domain->kp, z,z0,z1,z2,z3,z4,z5,z6,z7) ;

      startTimer();
      for (SampIndex_type isamp = 0; isamp < run_samples; ++isamp) {

        #pragma omp parallel for 
        for (Index_type i = ibegin ; i < iend ; ++i ) {
          VOL3D_BODY;
        }

      }
      stopTimer();

      break;
    }

    case RAJALike_OpenMP : {
      // Not applicable
      break;
    }

    case RAJA_OpenMP : {

      VOL3D_DATA;

      NDPTRSET(m_domain->jp, m_domain->kp, x,x0,x1,x2,x3,x4,x5,x6,x7) ;
      NDPTRSET(m_domain->jp, m_domain->kp, y,y0,y1,y2,y3,y4,y5,y6,y7) ;
      NDPTRSET(m_domain->jp, m_domain->kp, z,z0,z1,z2,z3,z4,z5,z6,z7) ;

      startTimer();
      for (SampIndex_type isamp = 0; isamp < run_samples; ++isamp) {

        RAJA::forall<RAJA::omp_parallel_for_exec>(ibegin, iend, [=](int i) {
          VOL3D_BODY;
        });

      }
      stopTimer();

      break;
    }
#endif

#if defined(RAJA_ENABLE_CUDA)
    case Baseline_CUDA : {

      VOL3D_DATA_SETUP_CUDA;

      NDPTRSET(m_domain->jp, m_domain->kp, x,x0,x1,x2,x3,x4,x5,x6,x7) ;
      NDPTRSET(m_domain->jp, m_domain->kp, y,y0,y1,y2,y3,y4,y5,y6,y7) ;
      NDPTRSET(m_domain->jp, m_domain->kp, z,z0,z1,z2,z3,z4,z5,z6,z7) ;

      const Index_type ibegin = m_domain->fpz;
      const Index_type ilen = m_domain->lpz+1 - ibegin;

      startTimer();
      for (SampIndex_type isamp = 0; isamp < run_samples; ++isamp) {

        const size_t grid_size = RAJA_DIVIDE_CEILING_INT(iend, block_size);

        vol3d<<<grid_size, block_size>>>(vol,
                                         x0, x1, x2, x3, x4, x5, x6, x7,
                                         y0, y1, y2, y3, y4, y5, y6, y7,
                                         z0, z1, z2, z3, z4, z5, z6, z7,
                                         vnormq,
                                         ibegin, ilen);

      }
      stopTimer();

      VOL3D_DATA_TEARDOWN_CUDA;

      break;
    }

    case RAJA_CUDA : {

      VOL3D_DATA_SETUP_CUDA;

      NDPTRSET(m_domain->jp, m_domain->kp, x,x0,x1,x2,x3,x4,x5,x6,x7) ;
      NDPTRSET(m_domain->jp, m_domain->kp, y,y0,y1,y2,y3,y4,y5,y6,y7) ;
      NDPTRSET(m_domain->jp, m_domain->kp, z,z0,z1,z2,z3,z4,z5,z6,z7) ;

      startTimer();
      for (SampIndex_type isamp = 0; isamp < run_samples; ++isamp) {

        RAJA::forall< RAJA::cuda_exec<block_size, true /*async*/> >(
           ibegin, iend,
           [=] __device__ (Index_type i) {
           VOL3D_BODY;
        });

      }
      stopTimer();

      VOL3D_DATA_TEARDOWN_CUDA;

      break;
    }
#endif

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

void VOL3D::updateChecksum(VariantID vid)
{
  checksum[vid] += calcChecksum(m_vol, getRunSize());
}

void VOL3D::tearDown(VariantID vid)
{
  (void) vid;

  deallocData(m_x);
  deallocData(m_y);
  deallocData(m_z);
  deallocData(m_vol);
}

} // end namespace apps
} // end namespace rajaperf