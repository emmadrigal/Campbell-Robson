#include <math.h>                       /* sin */
#include <opencv2/core/core.hpp>        /* Mat*/
#include <opencv2/highgui/highgui.hpp>  /* imshow*/

#include <iostream>                     /* input and ouput*/

#include <boost/program_options.hpp>    /* user interacion and parameters*/

#define PI 3.1415926535

using namespace cv;
using namespace std;
namespace po = boost::program_options;


/**
 * Returns the value for a descrete sine Function that increases its frecuency linearly
 * It always returns a value between 0 and 1
 * @param pX value of the x pixel value
 * @param maxX number of columns to be displayed
 * @return The value of the function
 */
double discreteSine(double pX, int maxX){       
    //This causes the linear increase of the value
    pX = pX*pX/(2*maxX);
    
    //Calculates the cosine Value
    return sin(pX);
}

/**
 * Returns the value of amplitud for a function, this value begins from 0 and goes up to 127
 * @param py value of the y pixel value
 * @param maxY number of rows to be displayed
 * @return amplitud for the function
 */
double amplitudValue(double py, int maxY){
    return 127*py/(maxY-1);
}

/**
 * Returns scaled value for x when evaluating a logarithmic function
 * @param val value of pixel to be scaled
 * @param maxVal max value t obe reached
 * @return scaled value for X
 */
double scaler(int val, int maxVal){
    double alpha = log(maxVal)/( maxVal - 1); 
    
    return (maxVal+1)/(maxVal)*exp(val*alpha);
    
}


/**
 * Displays a Campbell-Robson chart
 * @param linear boolean indicating whether to display a linear or a logarithmic chart
 * @param cols Number of colums which the image will posess
 * @param rows Number of rows which the image will posees
 */
void displayChart(bool linear, int cols, int rows){
    Mat chart(rows, cols, CV_8UC1);


    if(linear){
        double sine;
        for(int i = 0; i < cols; i++){
            sine = discreteSine(i, cols);
            for(int j = 0; j < rows; j++){
                double val = sine*amplitudValue(j, rows) + 128;
                
                chart.at<unsigned char>(j, i) = val;
            }
        }
    }
    else{
        double sine;
        for(int i = 0; i < cols; i++){
            sine = discreteSine(scaler(i, cols), cols);
            for(int j = 0; j < rows; j++){
                double val = sine*amplitudValue(scaler(j, rows), rows) + 128;
                //double val = amplitudValue(scaler(j, rows), rows) + 128;
                //double val = sine*127 + 128;
                
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
void displaySingleLine(bool linear, int row, int maxRows, int cols){
    Mat chart(100, cols, CV_8UC1);
    
    if(row > maxRows){
        maxRows = row + 1;
    }

    if(linear){
        float amp = amplitudValue(row, maxRows);
        float sine;
        for(int i = 0; i < cols; i++){
            sine = discreteSine(i, cols);
            for(int j = 0; j < 100; j++){
            chart.at<unsigned char>(j, i) = sine*amp + 128;
            }
        }
    }
    else{
        float amp = amplitudValue(scaler(row, maxRows), maxRows);
        float sine;
        for(int i = 0; i < cols; i++){
            sine = discreteSine(scaler(i, cols), cols);
            for(int j = 0; j < 100; j++){
                chart.at<unsigned char>(j, i) = sine*amp + 128;
            }
        }
    }
    
    imshow( "Display window", chart);// Show the image inside it.
    waitKey(0);
}



int main(int ac, char* av[]){
    try{
        po::options_description desc("Allowed Options");
        desc.add_options()
                ("help", "Produce help message")
                ("display", "Shows a Cambell-Robson chart")
                ("rows,r", po::value<int>()->default_value(512), "Number of rows to display, default is 512")
                ("cols,c", po::value<int>()->default_value(512), "Number of columns to display, default is 512")
                ("linear,l", "Indicates if a linear chart is to be shown, defualt is logarithmic")
                ("singleRow,x", po::value<int>(), "Shows a single row indicated by argument")
        ;

        po::variables_map vm;
        po::store(po::parse_command_line(ac, av, desc), vm);
        po::notify(vm);

        if(vm.count("help")){
            cout << desc << "\n";
            return 0;
        }
        else if(vm.count("display")){
            int rows =  vm["rows"].as<int>();
            int cols =  vm["cols"].as<int>();
            if(vm.count("singleRow")){
                displaySingleLine(vm.count("linear"), vm["singleRow"].as<int>(), rows, cols);
            }
            else{
                displayChart(vm.count("linear"), cols, rows);
            }
        }
        else {
            cout << desc << "\n";
            return 0;
        }

    }
    catch(exception& e) {
        cerr << "error: " << e.what() << "\n";
        return 1;
    }
    catch(...) {
        cerr << "Exception of unknown type!\n";
    }

    return 0;     
}
