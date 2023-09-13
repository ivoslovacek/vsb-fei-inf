#include <stdio.h>
#include <cuda_device_runtime_api.h>
#include <cuda_runtime.h>

#include "cuda_img.h"

__global__ void kernel_xrotate4(CudaImg image)
{
    int x = threadIdx.x + blockIdx.x * blockDim.x;
    int y = threadIdx.y + blockIdx.y * blockDim.y;

    if (x >= image.m_size.x)
        return;

    if (y >= image.m_size.y)
        return;

    image.at<uchar4>(x, y) = image.at<uchar4>((image.m_size.x - 1 - x), y);
}

void cu_xrotate4(CudaImg image)
{
    cudaError_t l_cerr;

    int thread_count = 32;
    dim3 block_size(thread_count, thread_count);
    dim3 block_count((image.m_size.x + thread_count) / thread_count, (image.m_size.y + thread_count) / thread_count);

    kernel_xrotate4<<<block_count, block_size>>>(image);

    if ((l_cerr = cudaGetLastError()) != cudaSuccess)
        printf("CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString(l_cerr));

    cudaDeviceSynchronize();
}

__global__ void kernel_insert(CudaImg bg_image, CudaImg fg_image, int2 pos)
{
    int x = threadIdx.x + blockIdx.x * blockDim.x;
    int y = threadIdx.y + blockIdx.y * blockDim.y;

    if (x >= fg_image.m_size.x)
        return;

    if (y >= fg_image.m_size.y)
        return;

    if (pos.x + x < 0 || pos.x + x >= bg_image.m_size.x)
        return;

    if (pos.y + y < 0 || pos.y + y >= bg_image.m_size.y)
        return;

    bg_image.at<uchar3>(pos.x + x, pos.y + y).x = (fg_image.at<uchar4>(x, y).x * fg_image.at<uchar4>(x, y).w / 255.0) + bg_image.at<uchar3>(pos.x + x, pos.y + y).x * (255 - fg_image.at<uchar4>(x, y).w) / 255.0;
    bg_image.at<uchar3>(pos.x + x, pos.y + y).y = (fg_image.at<uchar4>(x, y).y * fg_image.at<uchar4>(x, y).w / 255.0) + bg_image.at<uchar3>(pos.x + x, pos.y + y).y * (255 - fg_image.at<uchar4>(x, y).w) / 255.0;
    bg_image.at<uchar3>(pos.x + x, pos.y + y).z = (fg_image.at<uchar4>(x, y).z * fg_image.at<uchar4>(x, y).w / 255.0) + bg_image.at<uchar3>(pos.x + x, pos.y + y).z * (255 - fg_image.at<uchar4>(x, y).w) / 255.0;
}

void cu_insert(CudaImg bg_image, CudaImg fg_image, int2 pos)
{
    cudaError_t l_cerr;

    int thread_count = 32;
    dim3 block_size(thread_count, thread_count);
    dim3 block_count((fg_image.m_size.x + thread_count) / thread_count, (fg_image.m_size.y + thread_count) / thread_count);

    kernel_insert<<<block_count, block_size>>>(bg_image, fg_image, pos);

    if ((l_cerr = cudaGetLastError()) != cudaSuccess)
        printf("CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString(l_cerr));

    cudaDeviceSynchronize();
}

template <typename T>
__global__ void kernel_copy(CudaImg image, CudaImg copy)
{
    int x = threadIdx.x + blockIdx.x * blockDim.x;
    int y = threadIdx.y + blockIdx.y * blockDim.y;

    if (x >= image.m_size.x)
        return;

    if (y >= image.m_size.y)
        return;

    copy.at<T>(x, y) = image.at<T>(x, y);
}

void cu_copy3(CudaImg image, CudaImg copy)
{
    cudaError_t l_cerr;

    int thread_count = 32;
    dim3 block_size(thread_count, thread_count);
    dim3 block_count((image.m_size.x + thread_count) / thread_count, (image.m_size.y + thread_count) / thread_count);

    kernel_copy<uchar3><<<block_count, block_size>>>(image, copy);

    if ((l_cerr = cudaGetLastError()) != cudaSuccess)
        printf("CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString(l_cerr));

    cudaDeviceSynchronize();
}

__global__ void kernel_copyAndResize(CudaImg image, CudaImg copy)
{
    int x = threadIdx.x + blockIdx.x * blockDim.x;
    int y = threadIdx.y + blockIdx.y * blockDim.y;

    if (x >= image.m_size.x)
        return;

    if (y >= image.m_size.y)
        return;

    float2 ratio = {(float)image.m_size.x / (float)copy.m_size.x, (float)image.m_size.y / (float)copy.m_size.y};

    copy.at<uchar4>(x, y) = image.at<uchar4>(x * ratio.x, y * ratio.y);
}

void cu_copyAndResize(CudaImg image, CudaImg copy)
{
    cudaError_t l_cerr;

    int thread_count = 32;
    dim3 block_size(thread_count, thread_count);
    dim3 block_count((copy.m_size.x + thread_count) / thread_count, (copy.m_size.y + thread_count) / thread_count);

    kernel_copyAndResize<<<block_count, block_size>>>(image, copy);

    if ((l_cerr = cudaGetLastError()) != cudaSuccess)
        printf("CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString(l_cerr));

    cudaDeviceSynchronize();
}

__global__ void kernel_blur(CudaImg image, int kernel_size)
{
    int x = threadIdx.x + blockIdx.x * blockDim.x;
    int y = threadIdx.y + blockIdx.y * blockDim.y;

    if (x >= image.m_size.x)
        return;

    if (y >= image.m_size.y)
        return;

    int border = kernel_size / 2;
    float kernel_area = (float)(kernel_size * kernel_size);
    float3 sum = make_float3(0.0f, 0.0f, 0.0f);

    for (int ky = -border; ky <= border; ky++)
    {
        for (int kx = -border; kx <= border; kx++)
        {
            int px = min(max(x + kx, 0), image.m_size.x - 1);
            int py = min(max(y + ky, 0), image.m_size.y - 1);
            sum.y += image.at<uchar4>(px, py).y;
            sum.x += image.at<uchar4>(px, py).x;
            sum.z += image.at<uchar4>(px, py).z;
        }
    }

    image.at<uchar4>(x, y).x = sum.x / kernel_area;
    image.at<uchar4>(x, y).y = sum.y / kernel_area;
    image.at<uchar4>(x, y).z = sum.z / kernel_area;
}

void cu_blur(CudaImg image, int kernel_size)
{
    cudaError_t l_cerr;

    int thread_count = 32;
    dim3 block_size(thread_count, thread_count);
    dim3 block_count((image.m_size.x + thread_count) / thread_count, (image.m_size.y + thread_count) / thread_count);

    kernel_blur<<<block_count, block_size>>>(image, kernel_size);

    if ((l_cerr = cudaGetLastError()) != cudaSuccess)
        printf("CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString(l_cerr));

    cudaDeviceSynchronize();
}

__global__ void kernel_rotate4(CudaImg image, CudaImg copy, double degree)
{
    int x = threadIdx.x + blockIdx.x * blockDim.x;
    int y = threadIdx.y + blockIdx.y * blockDim.y;

    if (x >= image.m_size.x)
        return;

    if (y >= image.m_size.y)
        return;

    double2 center = {image.m_size.x / 2.0, image.m_size.y / 2.0};

    double2 rotation[] = {{cos(degree), -sin(degree)},
                          {sin(degree), cos(degree)}};

    double2 new_pos = {0, 0};

    new_pos.x = (x - center.x) * rotation[0].x + (y - center.y) * rotation[0].y;
    new_pos.y = (x - center.x) * rotation[1].x + (y - center.y) * rotation[1].y;
    int new_x = (int)(new_pos.x + center.x + 0.5);
    int new_y = (int)(new_pos.y + center.y + 0.5);

    if (new_x < 0 || new_x >= image.m_size.x)
        return;

    if (new_y < 0 || new_y >= image.m_size.y)
        return;

    copy.at<uchar4>((int)x, (int)y) = image.at<uchar4>(new_x, new_y);
}

void cu_rotate4(CudaImg image, CudaImg copy, double degree)
{
    cudaError_t l_cerr;

    int thread_count = 32;
    dim3 block_size(thread_count, thread_count);
    dim3 block_count((image.m_size.x + thread_count) / thread_count, (image.m_size.y + thread_count) / thread_count);

    double rad = (degree * M_PI) / 180;

    kernel_rotate4<<<block_count, block_size>>>(image, copy, rad);

    if ((l_cerr = cudaGetLastError()) != cudaSuccess)
        printf("CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString(l_cerr));

    cudaDeviceSynchronize();
}