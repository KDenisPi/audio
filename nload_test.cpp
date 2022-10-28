#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <sys/time.h>
#include <sys/select.h>
#include "load_struct.h"
/**

*/
using namespace std;

int main (int argc, char* argv[])
{
    bool success = true, debug = true;
    int fd;
    fd_set readfds;
    ldata::fload buff;
    size_t read_bytes, count_bytes=0;
    struct timeval timeout;
    int ready = 0; //check if STDIN ready

    timeout.tv_sec = 4;
    timeout.tv_usec = 0;
    FD_ZERO(&readfds);

    std::clog << "Using: " << (argc==1 ? "STDIN" : argv[1]) << std::endl;

    fd = (argc==1 ? dup(STDIN_FILENO) : open(argv[1], O_RDONLY));
    if(fd>=0){
        FD_SET(fd, &readfds);
        do{
            if(argc==1 && ready==0){
                ready = select(fd+1, &readfds, NULL, NULL, &timeout);
                if(ready<0){
                    std::cerr << "STDIN Error: " << errno << std::endl;
                    break;
                }
                if(ready==0){
                    std::cerr << "STDIN not ready. Timeout." << std::endl;
                    break;
                }
            }

            read_bytes = read(fd, buff.ch, sizeof(buff));

            if(debug && read_bytes>0){
                printf("%lu,%f\n", (count_bytes%8000), buff.fl);
            }

            count_bytes += read_bytes;
        }while(read_bytes>0);

        if(read_bytes==0){ //EOF
            std::clog << "Read bytes: " << count_bytes << std::endl;
        }
        else if(read_bytes<0){
            std::cerr << "File read error Error: " << errno << std::endl;
        }

        close(fd);
    }
    else{
        std::cerr << "Could not open source Error: " << errno << std::endl;
        success = false;
    }

    std::clog << "Finished " << success << std::endl;
    exit( (success ? EXIT_SUCCESS : EXIT_FAILURE));
}