#include <math.h>                       /* cos */
#include <opencv2/core/core.hpp>        /* Mat*/
#include <opencv2/highgui/highgui.hpp>  /* imshow*/

#include <iostream>                     /* input and ouput*/

#define PI 3.1415926535

using namespace cv;
/**
 * Returns the value for a descrete sine Function that increases its frecuency linearly
 * It always returns a value between 0 and 1
 * @param pX value of the x pixel value
 * @param maxX number of columns to be displayed
 * @return The value of the function
 */
float discreteSine(int pX, int maxX){   
    //This causes the linear increase of the value
    pX = pX*pX * PI /(2 *maxX);
    
    //Calculates the cosine Value
    float value = cos(pX);
    
    return value;
}

/**
 * Returns the value of amplitud for a function, this value begins from 0 and goes up to 127
 * @param py value of the y pixel value
 * @param maxY number of rows to be displayed
 * @return amplitud for the function
 */
int amplitudValue(int py, int maxY){
    int value = 127*py/(maxY-1);
    return value;
}

/**
 * Returns scaled value for x when evaluating a logarithmic function
 * @param val value of pixel to be scaled
 * @param maxVal max value t obe reached
 * @return scaled value for X
 */
int scaler(int val, int maxVal){
    float alpha = log(maxVal - 1)/( maxVal - 1);
    //int value = exp(alpha * val);
    int value = log(val + 1)/alpha;
    
    return value;
}


/**
 * Displays a Campbell-Robson chart
 * @param linear boolean indicating whether to display a linear or a logarithmic chart
 * @param cols Number of colums which the image will posess
 * @param rows Number of rows which the image will posees
 */
void displayChart(bool linear, int cols = 512, int rows = 512){
    Mat chart(rows, cols, CV_8UC1);

    if(linear){
        float sine;
        for(int i = 0; i < cols; i++){
            sine = discreteSine(i, cols);
            for(int j = 0; j < rows; j++){
                float val = sine*amplitudValue(j, rows) + 128;
                
                chart.at<unsigned char>(j, i) = val;
            }
        }
    }
    else{
        float sine;
        //TODO fix exponential scale
        for(int i = 0; i < cols; i++){
            sine = discreteSine(scaler(i, cols), cols);
            for(int j = 0; j < rows; j++){
                float val = sine*amplitudValue(scaler(j, rows), rows) + 128;
                
                chart.at<unsigned char>(j, i) = val;
            }
        }
    }
    
    imshow( "Display window", chart);// Show the image inside it.
    waitKey(0);
}


/**
 * Displays a single line of a Cambell-Robson chart
 * @param cols Number of colums which the image will posess
 * @param rows Number of rows which the image will posees
 */
void displaySingleLine(bool linear, int row, int numCols = 512){
    //TODO implement display
}



int main(int ac, char* av[]){
    //TODO implement boost user interface
    displayChart(false, 600, 400);
    
    return 0;      
}
