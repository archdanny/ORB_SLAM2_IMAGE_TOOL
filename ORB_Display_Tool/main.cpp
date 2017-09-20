//
//  main.cpp
//  ORB_Display_Tool
//
//  Created by Daniello on 19/09/2017.
//  Copyright © 2017 DDdesigns. All rights reserved.
//



#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <string>
#include <fstream>


//using namespace cv;
using namespace std;


int main(int argc, const char * argv[])
{

    cv::Mat image;
    image = cv::imread( "/Users/Danny/Documents/Urbinn/Foto_2/data/0000000005.png", CV_LOAD_IMAGE_COLOR);   // Read the file
    
    if(! image.data )                              // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }
    cv::namedWindow( "Display window", cv::WINDOW_AUTOSIZE );// Create a window for display.
    
    
    //loop text file
    float pointOne;
    float pointTwo;
    string STRING;
    ifstream inFile;
    inFile.open("/Users/Danny/Documents/Urbinn/Foto_2/mapText.txt");
    if (!inFile) {
        cerr << "Unable to open file mapText";
        exit(1);   // call system to stop
    }
    
    bool didFindKeyFrame = false;
    while(!inFile.eof()) // To get you all the lines.
    {
        getline(inFile,STRING); // Saves the line in STRING.
        if (STRING.find("KeyframeId : ") != std::string::npos) {
            if (STRING.find(": 5 :") != std::string::npos) {
                didFindKeyFrame = true;
            } else {
                didFindKeyFrame = false;
            }
           
        }
        
        if (STRING.find("Key point X:") != std::string::npos && didFindKeyFrame) {
            std::cout << "found!" << '\n';
            
            pointOne = strtof(( STRING.substr (13,21)).c_str(),0)  ;
            pointTwo = strtof(( STRING.substr (30,39)).c_str(),0)  ;
            
            //point
            cv::Point2f pt1,pt2;
            float radius = 5;
            pt1.x=pointOne - radius;
            pt1.y=pointTwo - radius;
            
            pt2.x = pointOne + radius;
            pt2.y = pointTwo + radius;;
            
            cv::rectangle(image,pt1,pt2,cv::Scalar(255,255,0));
        }
        cout<<STRING; // Prints our STRING.
    }
    inFile.close();
    
    imshow( "Frame 5", image );                   // Show our image inside it.
    
    
    cv::waitKey(0);
    // Wait for a keystroke in the window
    return 0;
}

