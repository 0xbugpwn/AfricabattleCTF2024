#include <stdio.h>
#include <unistd.h>


void vuln(){
    char buf[50];
    read(0, buf, 256);
}
  
void main(){
    write(1,"Africa battle CTF 2024\n",23);
    printf("Write() address : %p\n",write);
    vuln();
}
