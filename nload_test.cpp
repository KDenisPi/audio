#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

#include "load_struct.h"
/**

*/
using namespace std;


int main (int argc, char* argv[])
{
    bool success = true, debug = true;
    int fd;
    ldata::fload buff;
    size_t read_bytes, count_bytes=0;

    fd = open(argv[1], O_RDONLY);
    if(fd>=0){
        do{
            read_bytes = read(fd, buff.ch, sizeof(buff));
            count_bytes += read_bytes;

            if(debug && read_bytes>0){
                printf("%ld %f", read_bytes, buff.fl);
            }

        }while(read_bytes>0);

        if(read_bytes==0){ //EOF
            std::cout << "Read bytes: " << count_bytes << std::endl;
        }
        else if(read_bytes<0){
            std::cout << "File read error Error: " << errno << std::endl;
        }

        close(fd);
    }
    else{
        std::cout << "Could not open source Error: " << errno << std::endl;
        success = false;
    }

    std::cout << "Finished " << success << std::endl;
    exit( (success ? EXIT_SUCCESS : EXIT_FAILURE));
}