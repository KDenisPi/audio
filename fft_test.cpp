/**
 * @file fft_test.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-10-26
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <math.h>
#include <time.h>
#include <chrono>
#include <ctime>


#include<fftw3.h>
#include "load_struct.h"

using namespace std;

int main (int argc, char* argv[])
{
    bool success = true, debug = false;
    int fd;
    int N = 800;//8000;       //Number of samples
    int Freq = 8000;    //Frequency
    double *in;
    fftw_complex *out;
    fftw_plan my_plan;
    ldata::fload buff;
    size_t read_bytes, count_items=0;

    int freq_sp =  (int)(Freq/N); //frequency spacing

    in = (double*) fftw_malloc(sizeof(double)*N);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*N);

    std::chrono::time_point<std::chrono::system_clock> tp_start, tp_end;
    //std::time_t time_now = std::chrono::system_clock::to_time_t(tp);

    fd = open(argv[1], O_RDONLY);
    if(fd>=0){
        for(int loop=0; loop<40; loop++){
            tp_start = std::chrono::system_clock::now();
            for(int i=0; i<N; i++){
                read_bytes = read(fd, buff.ch, sizeof(buff));
                in[i] = buff.fl;

                if(read_bytes==0){ //EOF
                    std::clog << "Unexpected EOF" << std::endl;
                    success = false;
                    break;
                }
                else if(read_bytes<0){
                    std::cerr << "File read error Error: " << errno << std::endl;
                    success = false;
                    break;
                }
            }

            if(success){
                my_plan = fftw_plan_dft_r2c_1d(N, in, out, FFTW_ESTIMATE);
                fftw_execute(my_plan);

                for(int i =0; i<N/2; i++){
                    double res = 70+10*log10(out[i][0]*out[i][0]+out[i][1]*out[i][1]);
                    //printf("%d,%4.2f\n", freq_sp*i, 70+10*log10(out[i][0]*out[i][0]+out[i][1]*out[i][1]));
                }

                fftw_destroy_plan(my_plan);
            }

            tp_end = std::chrono::system_clock::now();
            std::cout << "Milliseconds: " << std::chrono::duration_cast<std::chrono::milliseconds>(tp_end - tp_start).count() << std::endl;
        }

        close(fd);
    }

    fftw_free(in);
    fftw_free(out);

    std::clog << "Finished " << success << std::endl;
    exit( (success ? EXIT_SUCCESS : EXIT_FAILURE));
}