/**
 * @file color_matrix.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-10-31
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

using namespace std;

int main (int argc, char* argv[])
{
    int freq_block[3] = {6,8,6};
    int freq_step = 30;
    int amp_step = 5;

    //printf("%06X", (0xff<<(8*1)));


    for(int i=0;i<3;i++){
        uint32_t color = 0xff;
        for(int hz=0;hz<freq_block[i];hz++){
            printf("<tr>\n");
            for(int amp=0; amp<6; amp++){
                printf("<td class=\"td\" style=\"background:#%06X\">&nbsp;</td>\n",(color<<(8*i)));
                //printf("%06X", (color<<(8*i)));
                color -= amp_step;
            }
            printf("</tr>\n");
            color -= amp_step;
        }
    }


    exit(EXIT_SUCCESS);
}