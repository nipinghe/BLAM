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
#include <blam/adl/level3/gemm.h>

#if defined(BLAM_USE_DECAY)
//# include <blam/adl/level2/gemv.h>
#endif

namespace blam
{
namespace system
{
namespace generic
{

// Swap to remove dependence on StorageOrder
template <typename ExecutionPolicy,
          typename Alpha, typename MA, typename MB,
          typename Beta, typename MC>
void
gemm(const ExecutionPolicy& exec,
     StorageOrder order, Transpose transA, Transpose transB,
     int m, int n, int k,
     const Alpha& alpha,
     const MA* A, int ldA,
     const MB* B, int ldB,
     const Beta& beta,
     MC* C, int ldC)
{
#if defined(BLAM_USE_DECAY)
  // gemv
#else
  static_assert(sizeof(ExecutionPolicy) == 0, "BLAM UNIMPLEMENTED");
#endif
}

// Default to ColMajor
template <typename ExecutionPolicy,
          typename Alpha, typename MA, typename MB,
          typename Beta, typename MC>
void
gemm(const ExecutionPolicy& exec,
     Transpose transA, Transpose transB,
     int m, int n, int k,
     const Alpha& alpha,
     const MA* A, int ldA,
     const MB* B, int ldB,
     const Beta& beta,
     MC* C, int ldC)
{
  blam::adl::gemm(exec,
                  ColMajor, transA, transB,
                  m, n, k,
                  alpha,
                  A, ldA,
                  B, ldB,
                  beta,
                  C, ldC);
}

// Default to NoTrans
template <typename ExecutionPolicy,
          typename Alpha, typename MA, typename MB,
          typename Beta, typename MC>
void
gemm(const ExecutionPolicy& exec,
     int m, int n, int k,
     const Alpha& alpha,
     const MA* A, int ldA,
     const MB* B, int ldB,
     const Beta& beta,
     MC* C, int ldC)
{
  blam::adl::gemm(exec,
                  NoTrans, NoTrans,
                  m, n, k,
                  alpha,
                  A, ldA,
                  B, ldB,
                  beta,
                  C, ldC);
}

} // end namespace generic
} // end namespace system
} // end namespace blam
