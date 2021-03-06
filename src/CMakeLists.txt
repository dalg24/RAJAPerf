###############################################################################
# Copyright (c) 2017-19, Lawrence Livermore National Security, LLC
# and RAJA Performance Suite project contributors.
# See the RAJAPerf/COPYRIGHT file for details.
#
# SPDX-License-Identifier: (BSD-3-Clause)
###############################################################################

include_directories(.)

add_subdirectory(common)
add_subdirectory(apps)
add_subdirectory(basic)
add_subdirectory(lcals)
add_subdirectory(polybench)
add_subdirectory(stream)

set(RAJA_PERFSUITE_EXECUTABLE_DEPENDS
    common
    apps
    basic
    lcals
    polybench
    stream)
list(APPEND RAJA_PERFSUITE_EXECUTABLE_DEPENDS ${RAJA_PERFSUITE_DEPENDS}) 

if(ENABLE_TARGET_OPENMP)
  remove_definitions(-DRUN_RAJA_SEQ -DRUN_OPENMP )

blt_add_executable(
  NAME raja-perf-omptarget.exe
  SOURCES RAJAPerfSuiteDriver.cpp
  apps/AppsData.cpp
  apps/DEL_DOT_VEC_2D.cpp
  apps/DEL_DOT_VEC_2D-Cuda.cpp
  apps/DEL_DOT_VEC_2D-OMPTarget.cpp
  apps/ENERGY.cpp
  apps/ENERGY-Cuda.cpp
  apps/ENERGY-OMPTarget.cpp
  apps/FIR.cpp
  apps/FIR-Cuda.cpp
  apps/FIR-OMPTarget.cpp
  apps/PRESSURE.cpp
  apps/PRESSURE-Cuda.cpp
  apps/PRESSURE-OMPTarget.cpp
  apps/LTIMES.cpp
  apps/LTIMES-Cuda.cpp
  apps/LTIMES-OMPTarget.cpp
  apps/LTIMES_NOVIEW.cpp
  apps/LTIMES_NOVIEW-Cuda.cpp
  apps/LTIMES_NOVIEW-OMPTarget.cpp
  apps/WIP-COUPLE.cpp
  apps/VOL3D.cpp
  apps/VOL3D-Cuda.cpp
  apps/VOL3D-OMPTarget.cpp
  basic/DAXPY.cpp
  basic/DAXPY-Cuda.cpp
  basic/DAXPY-OMPTarget.cpp
  basic/IF_QUAD.cpp
  basic/IF_QUAD-Cuda.cpp
  basic/IF_QUAD-OMPTarget.cpp
  basic/INIT3.cpp
  basic/INIT3-Cuda.cpp
  basic/INIT3-OMPTarget.cpp
  basic/INIT_VIEW1D.cpp
  basic/INIT_VIEW1D-Cuda.cpp
  basic/INIT_VIEW1D-OMPTarget.cpp
  basic/INIT_VIEW1D_OFFSET.cpp
  basic/INIT_VIEW1D_OFFSET-Cuda.cpp
  basic/INIT_VIEW1D_OFFSET-OMPTarget.cpp
  basic/MULADDSUB.cpp
  basic/MULADDSUB-Cuda.cpp
  basic/MULADDSUB-OMPTarget.cpp
  basic/NESTED_INIT.cpp
  basic/NESTED_INIT-Cuda.cpp
  basic/NESTED_INIT-OMPTarget.cpp
  basic/REDUCE3_INT.cpp
  basic/REDUCE3_INT-Cuda.cpp
  basic/REDUCE3_INT-OMPTarget.cpp
  basic/TRAP_INT.cpp
  basic/TRAP_INT-Cuda.cpp
  basic/TRAP_INT-OMPTarget.cpp
  lcals/DIFF_PREDICT.cpp
  lcals/DIFF_PREDICT-Cuda.cpp
  lcals/DIFF_PREDICT-OMPTarget.cpp
  lcals/EOS.cpp
  lcals/EOS-Cuda.cpp
  lcals/EOS-OMPTarget.cpp
  lcals/FIRST_DIFF.cpp
  lcals/FIRST_DIFF-Cuda.cpp
  lcals/FIRST_DIFF-OMPTarget.cpp
  lcals/HYDRO_1D.cpp
  lcals/HYDRO_1D-Cuda.cpp
  lcals/HYDRO_1D-OMPTarget.cpp
  lcals/HYDRO_2D.cpp
  lcals/HYDRO_2D-Cuda.cpp
  lcals/HYDRO_2D-OMPTarget.cpp
  lcals/INT_PREDICT.cpp
  lcals/INT_PREDICT-Cuda.cpp
  lcals/INT_PREDICT-OMPTarget.cpp
  lcals/PLANCKIAN.cpp
  lcals/PLANCKIAN-Cuda.cpp
  lcals/PLANCKIAN-OMPTarget.cpp
  polybench/POLYBENCH_2MM.cpp
  polybench/POLYBENCH_2MM-Cuda.cpp
  polybench/POLYBENCH_2MM-OMPTarget.cpp
  polybench/POLYBENCH_3MM.cpp
  polybench/POLYBENCH_3MM-Cuda.cpp
  polybench/POLYBENCH_3MM-OMPTarget.cpp
  polybench/POLYBENCH_ADI.cpp
  polybench/POLYBENCH_ADI-Cuda.cpp
  polybench/POLYBENCH_ADI-OMPTarget.cpp
  polybench/POLYBENCH_ATAX.cpp
  polybench/POLYBENCH_ATAX-Cuda.cpp
  polybench/POLYBENCH_ATAX-OMPTarget.cpp
  polybench/POLYBENCH_FDTD_2D.cpp
  polybench/POLYBENCH_FDTD_2D-Cuda.cpp
  polybench/POLYBENCH_FDTD_2D-OMPTarget.cpp
  polybench/POLYBENCH_FLOYD_WARSHALL.cpp
  polybench/POLYBENCH_FLOYD_WARSHALL-Cuda.cpp
  polybench/POLYBENCH_FLOYD_WARSHALL-OMPTarget.cpp
  polybench/POLYBENCH_GEMM.cpp
  polybench/POLYBENCH_GEMM-Cuda.cpp
  polybench/POLYBENCH_GEMM-OMPTarget.cpp
  polybench/POLYBENCH_GEMVER.cpp
  polybench/POLYBENCH_GEMVER-Cuda.cpp
  polybench/POLYBENCH_GEMVER-OMPTarget.cpp
  polybench/POLYBENCH_GESUMMV.cpp
  polybench/POLYBENCH_GESUMMV-Cuda.cpp
  polybench/POLYBENCH_GESUMMV-OMPTarget.cpp
  polybench/POLYBENCH_HEAT_3D.cpp
  polybench/POLYBENCH_HEAT_3D-Cuda.cpp
  polybench/POLYBENCH_HEAT_3D-OMPTarget.cpp
  polybench/POLYBENCH_JACOBI_1D.cpp
  polybench/POLYBENCH_JACOBI_1D-Cuda.cpp
  polybench/POLYBENCH_JACOBI_1D-OMPTarget.cpp
  polybench/POLYBENCH_JACOBI_2D.cpp
  polybench/POLYBENCH_JACOBI_2D-Cuda.cpp
  polybench/POLYBENCH_JACOBI_2D-OMPTarget.cpp
  polybench/POLYBENCH_MVT.cpp
  polybench/POLYBENCH_MVT-Cuda.cpp
  polybench/POLYBENCH_MVT-OMPTarget.cpp
  stream/ADD.cpp
  stream/ADD-Cuda.cpp
  stream/ADD-OMPTarget.cpp
  stream/COPY.cpp
  stream/COPY-Cuda.cpp
  stream/COPY-OMPTarget.cpp
  stream/DOT.cpp
  stream/DOT-Cuda.cpp
  stream/DOT-OMPTarget.cpp
  stream/MUL.cpp
  stream/MUL-Cuda.cpp
  stream/MUL-OMPTarget.cpp
  stream/TRIAD.cpp
  stream/TRIAD-Cuda.cpp
  stream/TRIAD-OMPTarget.cpp
  common/DataUtils.cpp
  common/Executor.cpp
  common/KernelBase.cpp
  common/OutputUtils.cpp
  common/RAJAPerfSuite.cpp
  common/RPTypes.hpp
  common/RunParams.cpp
  DEPENDS_ON ${RAJA_PERFSUITE_DEPENDS}
)

else()
blt_add_executable(
  NAME raja-perf.exe
  SOURCES RAJAPerfSuiteDriver.cpp
  DEPENDS_ON ${RAJA_PERFSUITE_EXECUTABLE_DEPENDS}
  )
endif()
