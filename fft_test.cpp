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
#include "colors.h"

using namespace std;

int main (int argc, char* argv[])
{
    bool success = true, debug = false;
    int fd;
    int N = 2000; //50ms //800;//8000;       //Number of samples
    int Freq = 40000; //8000;    //Frequency
    int freq_interval = 20; // 1000/150
    double *in;
    fftw_complex *out;
    fftw_plan my_plan;
    ldata::fload buff;
    size_t read_bytes, count_items=0;

    int freq_sp =  (int)(Freq/N); //frequency spacing

    in = (double*) fftw_malloc(sizeof(double)*N);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*N);

    std::chrono::time_point<std::chrono::system_clock> tp_start, tp_end;

    std::cout << "Frequency: " << Freq << " N: " << N << " Freq step: " << freq_sp << std::endl;

    fd = open(argv[1], O_RDONLY);
    if(fd>=0){
        for(int loop=0; loop<1; loop++){
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

                double res = 0.0;
                int i_start = 0;
                int i;
                for(i=0; i<N/2; i++){
                    res += 70+10*log10(out[i][0]*out[i][0]+out[i][1]*out[i][1]);
                    if(i>0 && (i%freq_interval)==0){
                        printf("%d, [%d - %d], %4.2f\n", i/freq_interval, freq_sp*i_start, freq_sp*i, res/freq_interval);
                        res = 0.0;
                        i_start = i;
                    }
                }
                printf("%d, [%d - %d], %4.2f\n", i/freq_interval, freq_sp*i_start, freq_sp*i, res/freq_interval);

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