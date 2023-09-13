#include <stdio.h>
#include <cuda_device_runtime_api.h>
#include <cuda_runtime.h>
#include <opencv2/opencv.hpp>

#include "uni_mem_allocator.h"
#include "cuda_img.h"

#define MAX_ROTATION 355.0

namespace cv
{
}

void cu_xrotate4(CudaImg image);
void cu_insert(CudaImg bg_image, CudaImg fg_image, int2 pos);
void cu_copy3(CudaImg image, CudaImg copy);
void cu_copyAndResize(CudaImg image, CudaImg copy);
void cu_blur(CudaImg image, int kernel_size);
void cu_rotate4(CudaImg image, CudaImg copy, double degree);

int main(int t_numarg, char **t_arg)
{
    UniformAllocator allocator;
    cv::Mat::setDefaultAllocator(&allocator);

    if (t_numarg < 3)
    {
        printf("Enter picture filename!\n");
        return 1;
    }

    cv::Mat cv_bg_image = cv::imread(t_arg[1], cv::IMREAD_COLOR);
    CudaImg bg_image(cv_bg_image);

    cv::Mat cv_completed_image(cv_bg_image.size(), CV_8UC3);
    CudaImg completed_image(cv_completed_image);

    cv::Mat cv_fg_image = cv::imread(t_arg[2], cv::IMREAD_UNCHANGED);
    CudaImg fg_image(cv_fg_image);

    int2 pos = {0, 350};
    int direction = 1;
    float object_scale = 1.0;
    float rate = 0.005;
    double rotation = 0.0;
    double rotation_rate = 0.5;

    cu_xrotate4(fg_image);

    while (1)
    {
        cv::waitKey(1);

        cu_copy3(bg_image, completed_image);

        cv::Mat cv_rotated(cv_fg_image.size(), CV_8UC4);
        CudaImg rotated(cv_rotated);
        cu_rotate4(fg_image, rotated, rotation);

        cv::Size object_size = cv_fg_image.size();
        object_size.width *= object_scale;
        object_size.height *= object_scale;

        cv::Mat cv_object(object_size, CV_8UC4);
        CudaImg object(cv_object);
        cu_copyAndResize(rotated, object);
        cu_blur(object, 5);

        cu_insert(completed_image, object, pos);

        pos.x += direction;
        object_scale -= rate;
        rotation -= rotation_rate;

        if (pos.x + object.m_size.x > bg_image.m_size.x - 1 || pos.x < 0)
        {
            direction *= -1;
            cu_xrotate4(fg_image);
        }

        if (MAX_ROTATION < ((rotation > 0) ? rotation : -rotation))
            rotation_rate *= -1.0;

        if (object_scale < 0.1 || object_scale > 1)
            rate *= -1.0;

        cv::imshow("test", cv_completed_image);
    }

    cv::waitKey(0);
}
