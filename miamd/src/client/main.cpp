#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

int main(int argc,char** argv) {
  int shm = shm_open("/playershm-1000",O_CREAT|O_RDWR,ACCESSPERMS);
  void *shmem = mmap(NULL, (size_t)1, PROT_READ|PROT_WRITE, MAP_SHARED, shm, 0);
  char* message = argv[1];
  memcpy(shmem, message, 1);
}
