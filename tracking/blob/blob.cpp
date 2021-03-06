#include "blob.hpp"

//methods of blob class
cv::Point blob::point()
{
   return cv::Point((x.end+x.start)/2,(y.end+y.start)/2);
}
//calculates the area
int blob::area()
{
   return (x.end-x.start)*(y.end-y.start);
}
//marks object in image
//returns a negative number if fails or positive if succeeded
int blob::mark(cv::Mat& img,const cv::Scalar& color)
{
   if(x.end > img.cols || y.end > img.rows || img.type() != CV_8UC3)
      return -1;

   cv::Mat part          = img(y,x);
   part.col(0)           = color;
   part.col(part.cols-1) = color;
   part.row(0)           = color;
   part.row(part.rows-1) = color;
   cv::circle(img,point(),3,color,-1);

   return 1;
}
//operator overload
std::ostream& operator<<(std::ostream& os,blob& bl)
{
   os << "([" << bl.x.start << "," << bl.x.end << "],[" << bl.y.start << "," << bl.y.end << "])";
   return os; 
}

//bubble sort in ascending order
void orderBlob(blob bl[],const int& n)
{
   int i,j;
   blob aux;

   for(j=0;j<n;j++)
      for(i=1;i<n;i++)
         if(bl[i].area() > bl[i-1].area())
         {
            aux     = bl[i];
            bl[i]   = bl[i-1];
            bl[i-1] = aux;
         }

   return;
}


