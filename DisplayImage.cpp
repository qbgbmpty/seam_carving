#include <stdio.h>
#include <opencv2/opencv.hpp>


//git flow test

using namespace cv;

int main(int argc, char* argv[]) {

	Mat img = imread(argv[1]);
	Mat img_backup = img.clone();
	Mat energyMat(img.rows,img.cols,CV_8U,cv::Scalar(0));
	
	if (3 == img.channels())
		cvtColor(img, img, cv::COLOR_BGR2GRAY);


	for (int i = 0; i < img.rows; ++i)
		for (int j = 0; j < img.cols; ++j)
		{
			if (i==0)
			{
				if (j==0)
				{
					*(energyMat.data + energyMat.step[0] * i + energyMat.step[1] * j)=(abs((*(img.data + img.step[0] * (i+1) + img.step[1] * j)*2)+(*(img.data + img.step[0] * (i+1) + img.step[1] * (j+1))))+abs((*(img.data + img.step[0] * i + img.step[1] * (j+1))*2)))/9;
				}

				else if (j==img.cols-1)
				{
					*(energyMat.data + energyMat.step[0] * i + energyMat.step[1] * j)=(abs((*(img.data + img.step[0] * (i+1 )+ img.step[1] * j)*2)+(*(img.data + img.step[0] * (i+1) + img.step[1] * (j-1))))+abs((*(img.data + img.step[0] * i + img.step[1] * (j-1))*2)))/9;
				}

				else
				{
					*(energyMat.data + energyMat.step[0] * i + energyMat.step[1] * j)=(abs((0+0+0)-(*(img.data + img.step[0] * (i+1) + img.step[1] * (j-1))+*(img.data + img.step[0] * (i+1) + img.step[1] * j)*2+*(img.data + img.step[0] * (i+1) + img.step[1] * (j+1))))+abs((0+*(img.data + img.step[0] * i + img.step[1] * (j-1))*2+*(img.data + img.step[0] * (i+1) + img.step[1] * (j-1)))-(0+*(img.data + img.step[0] * i + img.step[1] * (j+1))*2+*(img.data + img.step[0] * (i+1) + img.step[1] * (j+1)))))/9;
				}
			}

			else if (i==img.rows-1)
			{
				if (j==0)
				{
					*(energyMat.data + energyMat.step[0] * i + energyMat.step[1] * j)=(abs((0+*(img.data + img.step[0] * (i-1) + img.step[1] * j)*2+*(img.data + img.step[0] * (i-1 )+ img.step[1] * (j+1))))+abs((*(img.data + img.step[0] * (i-1) + img.step[1] * (j+1))+*(img.data + img.step[0] * i + img.step[1] * (j+1))*2+0)))/9;
				}

				else if (j==img.cols-1)
				{
					*(energyMat.data + energyMat.step[0] * i + energyMat.step[1] * j)=(abs((*(img.data + img.step[0] * (i-1) + img.step[1] * (j-1))+*(img.data + img.step[0] * (i-1) + img.step[1] * j)*2+0))+abs(*(img.data + img.step[0] * (i-1) + img.step[1] * (j-1))+*(img.data + img.step[0] * i + img.step[1] * (j-1))*2+0))/9;
				}

				else
				{
					*(energyMat.data + energyMat.step[0] * i + energyMat.step[1] * j)=(abs(*(img.data + img.step[0] * (i-1) + img.step[1] * (j-1))+*(img.data + img.step[0] * (i-1) + img.step[1] * j)*2+*(img.data + img.step[0] * (i-1) + img.step[1] * (j+1)))+abs((*(img.data + img.step[0] * (i-1) + img.step[1] * (j+1))+*(img.data + img.step[0] * i + img.step[1] * (j+1))*2+0)-(*(img.data + img.step[0] * (i-1) + img.step[1] * (j-1))+*(img.data + img.step[0] * i + img.step[1] * (j-1))*2+0)))/9;
				}
			}

			else
			{
				*(energyMat.data + energyMat.step[0] * i + energyMat.step[1] * j)=(abs((*(img.data + img.step[0] * (i-1) + img.step[1] * (j-1))+*(img.data + img.step[0] * (i-1) + img.step[1] * j)*2+*(img.data + img.step[0] * (i-1) + img.step[1] * (j+1)))-(*(img.data + img.step[0] * (i+1) + img.step[1] * (j-1))+*(img.data + img.step[0] * (i+1) + img.step[1] * j)*2+*(img.data + img.step[0] * (i+1) + img.step[1] * (j+1))))+abs((*(img.data + img.step[0] * (i-1) + img.step[1] * (j+1))+*(img.data + img.step[0] * i + img.step[1] * (j+1))*2+*(img.data + img.step[0] *( i+1) + img.step[1] * (j+1)))-(*(img.data + img.step[0] * (i-1) + img.step[1] * (j-1))+*(img.data + img.step[0] * i + img.step[1] * (j-1))*2+*(img.data + img.step[0] * (i+1) + img.step[1] * (j-1)))))/9;
			}      
		}
		
	imshow("img_energy", energyMat);
	
	imwrite("out.jpg",energyMat);	

  
  
	for (int i = 1; i < energyMat.rows; ++i)
		for (int j = 0; j < energyMat.cols; ++j)
		{
			if (j==0)
			{
				if (*(energyMat.data + energyMat.step[0] * (i-1) + energyMat.step[1] * j)<=*(energyMat.data + energyMat.step[0] * (i-1) + energyMat.step[1] * (j+1)))
				{          
				  *(energyMat.data + energyMat.step[0] * i + energyMat.step[1] * j)=*(energyMat.data + energyMat.step[0] * i + energyMat.step[1] * j)+*(energyMat.data + energyMat.step[0] * (i-1) + energyMat.step[1] * j);
				}
				else
				{          
					*(energyMat.data + energyMat.step[0] * i + energyMat.step[1] * j)=*(energyMat.data + energyMat.step[0] * i + energyMat.step[1] * j)+*(energyMat.data + energyMat.step[0] * (i-1) + energyMat.step[1] * (j+1));          
				}
				
			}
			
			else if (j==img.cols-1)
			{
				if (*(energyMat.data + energyMat.step[0] * (i-1) + energyMat.step[1] * j)<=*(energyMat.data + energyMat.step[0] * (i-1) + energyMat.step[1] * (j-1)))
				{
				  *(energyMat.data + energyMat.step[0] * i + energyMat.step[1] * j)=*(energyMat.data + energyMat.step[0] * i + energyMat.step[1] * j)+*(energyMat.data + energyMat.step[0] * (i-1) + energyMat.step[1] * j);
				}
				else
				{
				  *(energyMat.data + energyMat.step[0] * i + energyMat.step[1] * j)=*(energyMat.data + energyMat.step[0] * i + energyMat.step[1] * j)+*(energyMat.data + energyMat.step[0] * (i-1) + energyMat.step[1] * (j-1));
				}
			}
			
			else
			{
				if (*(energyMat.data + energyMat.step[0] * (i-1) + energyMat.step[1] * j)<=*(energyMat.data + energyMat.step[0] * (i-1) + energyMat.step[1] * (j-1)))
				{
					if (*(energyMat.data + energyMat.step[0] * (i-1) + energyMat.step[1] * j)<=*(energyMat.data + energyMat.step[0] * (i-1) + energyMat.step[1] * (j+1)))
					{
						*(energyMat.data + energyMat.step[0] * i + energyMat.step[1] * j)=*(energyMat.data + energyMat.step[0] * i + energyMat.step[1] * j)+*(energyMat.data + energyMat.step[0] * (i-1) + energyMat.step[1] * j);
					}
					else
					{
					*(energyMat.data + energyMat.step[0] * i + energyMat.step[1] * j)=*(energyMat.data + energyMat.step[0] * i + energyMat.step[1] * j)+*(energyMat.data + energyMat.step[0] * (i-1) + energyMat.step[1] * (j+1));
					}
				}
				else
				{
					if (*(energyMat.data + energyMat.step[0] * (i-1) + energyMat.step[1] * (j-1))<=*(energyMat.data + energyMat.step[0] * (i-1) + energyMat.step[1] * (j+1)))
					{
						*(energyMat.data + energyMat.step[0] * i + energyMat.step[1] * j)=*(energyMat.data + energyMat.step[0] * i + energyMat.step[1] * j)+*(energyMat.data + energyMat.step[0] * (i-1) + energyMat.step[1] * (j-1));
					}
					else
					{
						*(energyMat.data + energyMat.step[0] * i + energyMat.step[1] * j)=*(energyMat.data + energyMat.step[0] * i + energyMat.step[1] * j)+*(energyMat.data + energyMat.step[0] * (i-1) + energyMat.step[1] * j+1);
					}
				}
			}
		}

  
	
  /*
	int min=9999,min_pos=0;
	for (int j = 0; j < img.cols; ++j)
		if (min>*(energyMat.data + energyMat.step[0] * (img.rows-1) + energyMat.step[1] * j))
    {
      min=*(energyMat.data + energyMat.step[0] * (img.rows-1) + energyMat.step[1] * j);
      min_pos=j;
    }

	*(img.data + img.step[0] * (energyMat.rows-1) + img.step[1] * min_pos + img.elemSize1() * 0) = 0;
	*(img.data + img.step[0] * (energyMat.rows-1) + img.step[1] * min_pos + img.elemSize1() * 1) = 0;
	*(img.data + img.step[0] * (energyMat.rows-1) + img.step[1] * min_pos + img.elemSize1() * 2) = 255;
	
	for (int i = energyMat.rows-2; i >=0 ; --i)
	{
		if (min_pos==0)
			if (*(energyMat.data + energyMat.step[0] * i + energyMat.step[1] * min_pos)>=*(energyMat.data + energyMat.step[0] * i + energyMat.step[1] * (min_pos+1)))
				min_pos=min_pos+1;
			
		
		else if (min_pos==img.cols-1)
			if (*(energyMat.data + energyMat.step[0] * i + energyMat.step[1] * min_pos)>=*(energyMat.data + energyMat.step[0] * i + energyMat.step[1] * (min_pos-1)))
				min_pos=min_pos-1;
		
		
		else
		{
			if (*(energyMat.data + energyMat.step[0] * i + energyMat.step[1] * min_pos)>=*(energyMat.data + energyMat.step[0] * i + energyMat.step[1] * (min_pos-1)))
			{
				if (*(energyMat.data + energyMat.step[0] * i + energyMat.step[1] * min_pos)>=*(energyMat.data + energyMat.step[0] * i + energyMat.step[1] * (min_pos+1)))
					min_pos=min_pos+1;
				else
					min_pos=min_pos-1;
			}
			else
			{
				if (*(energyMat.data + energyMat.step[0] * i + energyMat.step[1] * (min_pos-1))<=*(energyMat.data + energyMat.step[0] * i + energyMat.step[1] * (min_pos+1)))
					min_pos=min_pos-1;
				else
					min_pos=min_pos+1;
			}
		}
		
		
		
		
		*(img_backup.data + img_backup.step[0] * i + img_backup.step[1] * min_pos + img_backup.elemSize1() * 0) = 0;
		*(img_backup.data + img_backup.step[0] * i + img_backup.step[1] * min_pos + img_backup.elemSize1() * 1) = 0;
		*(img_backup.data + img_backup.step[0] * i + img_backup.step[1] * min_pos + img_backup.elemSize1() * 2) = 255;

	}
	
	imshow("img_rst", img_backup);
	*/
    
 
	
	waitKey();

}
