// ***********************************************************************
//
// Demo program for education in subject
// Computer Architectures and Parallel Systems.
// Petr Olivka, dep. of Computer Science, FEI, VSB-TU Ostrava, 2020/11
// email:petr.olivka@vsb.cz
//
// Example of CUDA Technology Usage.
//
// Image interface for CUDA
//
// ***********************************************************************

#pragma once

#include <opencv2/core/mat.hpp>

// Structure definition for exchanging data between Host and Device
struct CudaImg
{
  uint3 m_size; // size of picture
  union
  {
    void *m_p_void;     // data of picture
    uchar1 *m_p_uchar1; // data of picture
    uchar3 *m_p_uchar3; // data of picture
    uchar4 *m_p_uchar4; // data of picture
  };

  CudaImg(cv::Mat image)
  {
    this->m_size.x = image.size().width;
    this->m_size.y = image.size().height;
    this->m_p_void = (void *)image.data;
  }

  template <typename T>
  __device__ T &at(int x, int y)
  {
    return *((T *)this->m_p_void + (x + y * this->m_size.x));
  }
};