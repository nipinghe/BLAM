/******************************************************************************
 * Copyright (C) 2016-2017, Cris Cecka.  All rights reserved.
 * Copyright (C) 2016-2017, NVIDIA CORPORATION.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the NVIDIA CORPORATION nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NVIDIA CORPORATION BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ******************************************************************************/

#pragma once

#include <blam/system/cublas/config.h>
#include <blam/system/cublas/execution_policy.h>

#include <blam/system/cublas/level2/syr2.h>  // Real-valued her2

namespace blam
{
namespace cublas
{

// sher2
inline cublasStatus_t
her2(cublasHandle_t handle, cublasFillMode_t uplo,
     int n,
     const float* alpha,
     const float* x, int incX,
     const float* y, int incY,
     float* A, int ldA)
{
  return syr2(handle, uplo,
              n,
              alpha,
              x, incX,
              y, incY,
              A, ldA);
}

// dher2
inline cublasStatus_t
her2(cublasHandle_t handle, cublasFillMode_t uplo,
     int n,
     const double* alpha,
     const double* x, int incX,
     const double* y, int incY,
     double* A, int ldA)
{
  return syr2(handle, uplo,
              n,
              alpha,
              x, incX,
              y, incY,
              A, ldA);
}

// cher2
inline cublasStatus_t
her2(cublasHandle_t handle, cublasFillMode_t uplo,
     int n,
     const ComplexFloat* alpha,
     const ComplexFloat* x, int incX,
     const ComplexFloat* y, int incY,
     ComplexFloat* A, int ldA)
{
  BLAM_DEBUG_OUT("cublasCher2");

  return cublasCher2(handle, uplo,
                     n,
                     reinterpret_cast<const cuFloatComplex*>(alpha),
                     reinterpret_cast<const cuFloatComplex*>(x), incX,
                     reinterpret_cast<const cuFloatComplex*>(y), incY,
                     reinterpret_cast<cuFloatComplex*>(A), ldA);
}

// zher2
inline cublasStatus_t
her2(cublasHandle_t handle, cublasFillMode_t uplo,
     int n,
     const ComplexDouble* alpha,
     const ComplexDouble* x, int incX,
     const ComplexDouble* y, int incY,
     ComplexDouble* A, int ldA)
{
  BLAM_DEBUG_OUT("cublasZher2");

  return cublasZher2(handle, uplo,
                     n,
                     reinterpret_cast<const cuDoubleComplex*>(alpha),
                     reinterpret_cast<const cuDoubleComplex*>(x), incX,
                     reinterpret_cast<const cuDoubleComplex*>(y), incY,
                     reinterpret_cast<cuDoubleComplex*>(A), ldA);
}

// blam -> cublas
template <typename DerivedPolicy,
          typename Alpha,
          typename VX, typename VY, typename MA>
inline auto
her2(const execution_policy<DerivedPolicy>& exec,
     Uplo uplo,
     int n,
     const Alpha& alpha,
     const VX* x, int incX,
     const VY* y, int incY,
     MA* A, int ldA)
    -> decltype(her2(handle(derived_cast(exec)), cublas_type(uplo),
                     n, &alpha,
                     x, incX,
                     y, incY,
                     A, ldA))
{
  return her2(handle(derived_cast(exec)), cublas_type(uplo),
              n, &alpha,
              x, incX,
              y, incY,
              A, ldA);
}


// RowMajor -> ColMajor
template <typename DerivedPolicy,
          typename Alpha,
          typename VX, typename VY, typename MA>
inline auto
her2(const execution_policy<DerivedPolicy>& exec,
     Layout order, Uplo uplo,
     int n,
     const Alpha& alpha,
     const VX* x, int incX,
     const VY* y, int incY,
     MA* A, int ldA)
    -> decltype(her2(exec, uplo,
                     n, alpha,
                     x, incX,
                     y, incY,
                     A, ldA))
{
  if (order == RowMajor) {
    // Swap upper <=> lower
    uplo = (uplo == Uplo::Lower ? Uplo::Upper : Uplo::Lower);
  }

  return her2(exec, uplo,
              n, alpha,
              x, incX,
              y, incY,
              A, ldA);
}

} // end namespace cublas
} // end namespace blam
