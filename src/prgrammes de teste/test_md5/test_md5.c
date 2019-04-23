#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#if defined(__APPLE__)
#  define COMMON_DIGEST_FOR_OPENSSL
#  include <CommonCrypto/CommonDigest.h>
#  define SHA1 CC_SHA1
#else
#  include <openssl/md5.h>
#endif

char *str2md5(const char * str, int length) {
    int n;
    MD5_CTX c;
    unsigned char digest[16];
    char *out = (char*)malloc(33);

    MD5_Init(&c);

    while (length > 0) {
        if (length > 512) {
            MD5_Update(&c, str, 512);
        } else {
            MD5_Update(&c, str, length);
        }
        length -= 512;
        str += 512;
    }

    MD5_Final(digest, &c);

    for (n = 0; n < 16; ++n) {
        snprintf(&(out[n*2]), 16*2, "%02x", (unsigned int)digest[n]);
    }

    return out;
}

char * f2s(const char * file_name) {
    
    char * file_contents;    // fichier chargé
    long input_file_size=1000; //c'est zéro mais bon...
    FILE * input_file = fopen(file_name, "rb");
    printf("->%s\n", file_name);
    fseek(input_file, 0, SEEK_END);
    input_file_size = ftell(input_file);
    rewind(input_file);
    file_contents = malloc(input_file_size * (sizeof(char)));
    fread(file_contents, sizeof(char), input_file_size, input_file);
    printf("%s\n",file_contents );
    fclose(input_file);
    return(file_contents);
}


int main(int argc, char **argv){
  int optS=0,option=0;
  char * file_name;
  while ((option = getopt (argc, argv, "s")) != -1){
    if (option == 's'){
      optS = 1;
      break;
    }
  }
  if (optS && argc>2){
    printf("opt OK\n");
    strncpy(file_name, argv[2], strlen(argv[2])+1);
  }
  else
    strncpy(file_name, "p_save.txt", strlen("p-save.txt")+1);
    
  /*printf("%s\n", file_name);
  printf("%s\n", file_name);*/

  char * file_contents = f2s(file_name);

  char * output = str2md5(file_contents, strlen(file_contents));
  printf("%s\n", output);
  free(output);
  free(file_contents);
  


  return(0);
  
}

// apt-get install libssl-dev

// gcc -o test_md5 test_md5.c -lcrypto