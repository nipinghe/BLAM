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

#include <blam/system/cblas/config.h>
#include <blam/system/cblas/execution_policy.h>

namespace blam
{
namespace cblas
{

// saxpy
inline void
axpy(int n, const float& alpha, const float* x, int incX,
     float* y, int incY)
{
  BLAM_DEBUG_OUT("cblas_saxpy");

  cblas_saxpy(n, alpha, x, incX, y, incY);
}

// daxpy
inline void
axpy(int n, const double& alpha, const double* x, int incX,
     double* y, int incY)
{
  BLAM_DEBUG_OUT("cblas_daxpy");

  cblas_daxpy(n, alpha, x, incX, y, incY);
}

// caxpy
inline void
axpy(int n, const ComplexFloat& alpha,
     const ComplexFloat* x, int incX,
     ComplexFloat* y, int incY)
{
  BLAM_DEBUG_OUT("cblas_caxpy");

  cblas_caxpy(n, reinterpret_cast<const float*>(&alpha),
              reinterpret_cast<const float*>(x), incX,
              reinterpret_cast<float*>(y), incY);
}

// zaxpy
inline void
axpy(int n, const ComplexDouble& alpha,
     const ComplexDouble* x, int incX,
     ComplexDouble* y, int incY)
{
  BLAM_DEBUG_OUT("cblas_zaxpy");

  cblas_zaxpy(n, reinterpret_cast<const double*>(&alpha),
              reinterpret_cast<const double*>(x), incX,
              reinterpret_cast<double*>(y), incY);
}

// blam -> cblas
template <typename DerivedPolicy,
          typename Alpha, typename VX, typename VY>
inline auto
axpy(const execution_policy<DerivedPolicy>& /*exec*/,
     int n, const Alpha& alpha,
     const VX* x, int incX,
     VY* y, int incY)
    -> decltype(axpy(n, alpha, x, incX, y, incY))
{
  return axpy(n, alpha, x, incX, y, incY);
}

} // end namespace cblas
} // end namespace blam
