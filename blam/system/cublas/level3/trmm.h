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

#include <blam/detail/config.h>
#include <blam/system/cublas/execution_policy.h>

namespace blam
{
namespace cublas
{

// strmm
void
trmm(cublasHandle_t handle,
     cublasSideMode_t side, cublasFillMode_t upLo,
     cublasOperation_t transA, cublasDiagType_t diag,
     int m, int n,
     const float* alpha,
     const float* A, int ldA,
     const float* B, int ldB,
     float* C, int ldC)
{
  BLAM_DEBUG_OUT("cublasStrmm");

  cublasStrmm(handle, side, upLo, transA, diag,
              m, n,
              alpha,
              A, ldA,
              B, ldB,
              C, ldC);
}

// dtrmm
void
trmm(cublasHandle_t handle,
     cublasSideMode_t side, cublasFillMode_t upLo,
     cublasOperation_t transA, cublasDiagType_t diag,
     int m, int n,
     const double* alpha,
     const double* A, int ldA,
     const double* B, int ldB,
     double* C, int ldC)
{
  BLAM_DEBUG_OUT("cublasDtrmm");

  cublasDtrmm(handle, side, upLo, transA, diag,
              m, n,
              alpha,
              A, ldA,
              B, ldB,
              C, ldC);
}

// ctrmm
void
trmm(cublasHandle_t handle,
     cublasSideMode_t side, cublasFillMode_t upLo,
     cublasOperation_t transA, cublasDiagType_t diag,
     int m, int n,
     const ComplexFloat* alpha,
     const ComplexFloat* A, int ldA,
     const ComplexFloat* B, int ldB,
     ComplexFloat* C, int ldC)
{
  BLAM_DEBUG_OUT("cublasCtrmm");

  cublasCtrmm(handle, side, upLo, transA, diag,
              m, n,
              reinterpret_cast<const cuFloatComplex*>(alpha),
              reinterpret_cast<const cuFloatComplex*>(A), ldA,
              reinterpret_cast<const cuFloatComplex*>(B), ldB,
              reinterpret_cast<cuFloatComplex*>(C), ldC);
}

// ztrmm
void
trmm(cublasHandle_t handle,
     cublasSideMode_t side, cublasFillMode_t upLo,
     cublasOperation_t transA, cublasDiagType_t diag,
     int m, int n,
     const ComplexDouble* alpha,
     const ComplexDouble* A, int ldA,
     const ComplexDouble* B, int ldB,
     ComplexDouble* C, int ldC)
{
  BLAM_DEBUG_OUT("cublasZtrmm");

  cublasZtrmm(handle, side, upLo, transA, diag,
              m, n,
              reinterpret_cast<const cuDoubleComplex*>(alpha),
              reinterpret_cast<const cuDoubleComplex*>(A), ldA,
              reinterpret_cast<const cuDoubleComplex*>(B), ldB,
              reinterpret_cast<cuDoubleComplex*>(C), ldC);
}

// blam -> cublas
template <typename DerivedPolicy,
          typename Alpha, typename MA, typename MB, typename MC>
auto
trmm(const execution_policy<DerivedPolicy>& exec,
     Side side, StorageUpLo upLo, Transpose transA, Diag diag,
     int m, int n,
     const Alpha& alpha,
     const MA* A, int ldA,
     const MB* B, int ldB,
     MC* C, int ldC)
    -> decltype(trmm(handle(derived_cast(exec)),
                     cublas_type(side), cublas_type(upLo),
                     cublas_type(transA), cublas_type(diag),
                     m, n,
                     &alpha,
                     A, ldA,
                     B, ldB,
                     C, ldC))
{
  return trmm(handle(derived_cast(exec)),
              cublas_type(side), cublas_type(upLo),
              m, n,
              &alpha,
              A, ldA,
              B, ldB,
              C, ldC);
}

// RowMajor -> ColMajor
template <typename DerivedPolicy,
          typename Alpha, typename MA, typename MB, typename MC>
auto
trmm(const execution_policy<DerivedPolicy>& exec,
     StorageOrder order, Side side, StorageUpLo upLo, Transpose transA, Diag diag,
     int m, int n,
     const Alpha& alpha,
     const MA* A, int ldA,
     const MB* B, int ldB,
     MC* C, int ldC)
    -> decltype(trmm(exec, side, upLo, transA, diag,
                     m, n,
                     alpha,
                     A, ldA,
                     B, ldB,
                     C, ldC))
{
  if (order == ColMajor) {
    trmm(exec, side, upLo,
         transA, diag,
         m, n,
         alpha,
         A, ldA,
         B, ldB,
         C, ldC);
  } else {
    trmm(exec, (side==Left) ? Right : Left, (upLo==Upper) ? Lower : Upper,
         transA, diag,
         n, m,
         alpha,
         A, ldA,
         B, ldB,
         C, ldC);
  }
}

} // end namespace cublas
} // end namespace blam