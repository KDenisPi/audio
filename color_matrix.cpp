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
    uint32_t confs[3][5] = {{0, 16, 8, 0x70, 3}, {8, 0, 16, 0x60, 2}, {16, 8, 0, 0x70, 3}};

    //std::cout << "<html>\n   <head>\n    </head>\n    <body>\n        <table>" << std::endl;

    // 20 frequence * 6 for amp
    std::cout << "#include <stdint.h>\n namespace ldata {\n uint32_t colors[120] = {" << std::endl;

    int idx=0;
    for(int i=0;i<3;i++){
        uint32_t color = confs[i][3];;
        for(int hz=0;hz<freq_block[i];hz++){
            uint32_t a_color_1 = 0x10;
            uint32_t a_color_2 = 0x50;
            //printf("<tr>\n");
            for(int amp=0; amp<6; amp++){
                uint32_t rgb = (color<<confs[i][0]) | (a_color_1<<confs[i][1]) | (a_color_2<<confs[i][2]);

                //printf("<td class=\"td\" style=\"background:#%06X\">&nbsp;</td>\n",rgb);
                printf("0x%06X%c", rgb, (idx==119 ? ' ' : ','));

                color += confs[i][4];
                a_color_1 += 2;
                a_color_2 += 4;
                idx++;
            }
            //printf("</tr>\n");
            printf("\n");
            color += confs[i][4];
        }
    }

    //std::cout << "</table>\n     </body>\n </html>" << std::endl;
    std::cout << "\n};\n }" << std::endl;

    exit(EXIT_SUCCESS);
}