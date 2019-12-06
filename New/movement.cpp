#include "movement.h"

#include <opencv2/features2d/features2d.hpp>
#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/video/background_segm.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <QDebug>
#include <QtWidgets/QMessageBox>


using namespace std;
using namespace cv;

movement::movement()
{
    connect(this,SIGNAL(sendText(const QString &)), ma, SLOT(updateText(const QString &)));


   string file = "D:/QtProjet/test3.avi";
   string method = "mog2";    //knn or mog2 背景建模方法
   VideoCapture cap;

   //VideoCapture cap(0);

   cap.open(file.c_str());

   if( !cap.isOpened() )
   {
       printf("can not open camera or video file\n");
       //return -1;
   }

   namedWindow("image", WINDOW_NORMAL);
   namedWindow("foreground mask", WINDOW_NORMAL);
   namedWindow("SimpleBlobDetector");

   Ptr<BackgroundSubtractor> bg_model = method == "knn" ?
           createBackgroundSubtractorKNN().dynamicCast<BackgroundSubtractor>() :
           createBackgroundSubtractorMOG2().dynamicCast<BackgroundSubtractor>();

   Mat img0, img, fgmask, fgimg;

   for(;;)
   {
       cap >> img0;
       if( img0.empty() )
           break;

       resize(img0, img, Size(600, 600*img0.rows/img0.cols), INTER_LINEAR);

       if( fgimg.empty() )
         fgimg.create(img.size(), img.type());

       //更新模型 update the model
       bg_model->apply(img, fgmask,-1);

       // 腐蚀   //两个一起去噪点
       erode(fgmask, fgmask, Mat());
       // 膨胀
       dilate(fgmask, fgmask, Mat());

       fgimg = Scalar::all(0);
       img.copyTo(fgimg, fgmask);

       Mat bgimg;
       bg_model->getBackgroundImage(bgimg);

       imshow("image", img);
       detect(fgmask,img);
       imshow("foreground mask", fgmask);


       /*一帧到下一帧25毫秒
       // c ：为按键的ASCⅡ码值，常用ASCⅡ码值
       //ESC：ASCⅡ码27
       // 回车：ASCⅡ码13
       //换行（Ctrl + Enter）：ASCⅡ码10
       //空格：ASCⅡ码32*/

       char k = (char)waitKey(25);
       if( k == 27 ) break;
   }
}

void movement::detect(Mat mask,Mat img)
{
   SimpleBlobDetector::Params params;

   params.minThreshold = 20;//二值化的起始阈值
   params.maxThreshold = 180;//二值化的终止阈值
   params.thresholdStep = 10;//二值化的阈值步长

   params.minConvexity = 0.5f;//斑点的最小凸度 默认0.95f
   params.minInertiaRatio = 0.03f;//斑点的最小惯性率 默认0.1f
   params.minArea = 20;//斑点的最小面积
   params.maxArea = 5000;//斑点的最大面积
   params.blobColor = 255;//检测白色

    //重复的最小次数，只有属于灰度图像斑点的那些二值图像斑点数量大于该值时，该灰度图像斑点才被认为是特征点
   params.minRepeatability = 2;
    //最小的斑点距离，不同二值图像的斑点间距离小于该值时，被认为是同一个位置的斑点，否则是不同位置上的斑点
   params.minDistBetweenBlobs = 10;

   Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params);

   vector<KeyPoint> key_points;

   detector->detect(mask,key_points);

   if(key_points.size()>0)
   {
       //qDebug()<<key_points.size();
       emit sendText( "Find aaaa robot" );
   }

   Mat output_img;

   drawKeypoints( img, key_points, output_img, Scalar(0,0,255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS );

   imshow("SimpleBlobDetector", output_img);
}

