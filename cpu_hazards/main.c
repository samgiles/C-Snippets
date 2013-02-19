#include <stdio.h>
#include <sys/time.h>

/*
 * Function prototypes
 */
int functionA(char* value);
int functionB(char* value);

/* Demonstrates an alogorithm that can be implemented to prevent values being pushed on and popped off the stack */

int main(int argc, char* argv[]) {
  
  int value = 0x01020304;
  printf("Value = %x\n", value);
  printf("Value = %x\n", functionA((char*)&value));  
  printf("Value = %x\n", functionB((char*)&value));
  return 0;
}

int functionB(char* value) {
  return (value[0] << 24) | (value[1] << 16) | (value[2] << 8) | (value[3]);
}

int functionA(char* value) {
  int temp;
  ((char*)&temp)[0] = value[3];
  ((char*)&temp)[1] = value[2];
  ((char*)&temp)[2] = value[1];
  ((char*)&temp)[3] = value[0];

  return temp;
}
