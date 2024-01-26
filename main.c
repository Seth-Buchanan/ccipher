#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <stdbool.h>
#include <getopt.h>

#define VERSION "1.0"
#define AUTHOR  "Seth Buchanan"

void encryptChar(char input, int key);
void decryptChar(char input, int key);
void oneKey(char* optarg, bool printKeys, FILE* file, void (*rotateChar)(char, int));
void allKeysFile(bool printKeys, FILE* file);
void allKeysMemory(bool printKeys, char* file);
void bufferInput(bool printKeys);
void fileTime(bool printKeys, char* buff);


int main(int argc, char *argv[]) {
  bool printKeys, runOneKey, runAllKeys, decryptInput;
  printKeys = runOneKey = runAllKeys = decryptInput = false;
  
  int c, i;
  char* fileName = "";
  char* key;
  char* program_name = argv[0];
  FILE* file;

  while (true) {
    int option_index = 0;
    static struct option long_options[] = {
      {"encryptkey", required_argument, 0,  'e'},
      {"decryptkey", required_argument, 0,  'd'},
      {"crack",      no_argument,       0,  'c'},
      {"showkeys",   no_argument,       0,  's'},
      {"help",       no_argument,       0,  'h'},
      {"version",    no_argument,       0,  'v'},
      {0,            0,                 0,   0 }
    };

    c = getopt_long(argc, argv, "shcvd:e:",
		    long_options, &option_index);
    if (c == -1)
      break;

    switch (c) {
    case 's':			/* --showkeys */
      printKeys = true;
      break;

    case 'e':			/* --encrypt */
      key = optarg;
      runOneKey = true;
      break;
      
    case 'd':			/* --decryptkey */
      key = optarg;
      decryptInput = true;
      runOneKey = true;
      break;

    case 'c':			/* --crack */
      runAllKeys = true;
      break;

    case 'h':			/* --help */
      printf("Usage: %s [OPTION]... [FILE]... \n", program_name);
      fputs("\
By default, the command prints all rotations of the input file.\n\
\nThe command options allow for specifying a key or \n\
printing the key on the line.\n\
  -s      --showkeys      print encryption key \n\
  -k n    --key n         specify one encryption key n\n\
  -h      --help          print this page and exit\n\
  -v      --version       print program information\n\
", stdout);
      exit(EXIT_SUCCESS);
      break;

    case 'v':			/* --version */
      printf("%s %s \n", program_name, VERSION);
      fputs("\
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>.\n\
This is free software: you are free to change and redistribute it.\n\
There is NO WARRANTY, to the extent permitted by law.\n\
\n", stdout);
      printf("Written by %s.\n", AUTHOR);
      exit(EXIT_SUCCESS);
      break;

    case '?':
    fprintf(stderr, " \
Usage: %s \t[-edcshv] [--showkeys] [--encryptkey] \n\
          \t[--decryptkey] [--crack] <file> ... \n\
       %s [--help] \n", program_name, program_name);
      exit(EXIT_FAILURE);
	break;
      
    default:
      fprintf(stderr,"?? getopt returned character code 0%o ??\n", c);
    }

  }

  if (!(runAllKeys || runOneKey)){
    fprintf(stderr, " \
Usage: %s \t[-edcshv] [--showkeys] [--encryptkey] \n\
          \t[--decryptkey] [--crack] <file> ... \n\
       %s [--help] \n", program_name, program_name);
  } else if (runAllKeys && runOneKey){
    fputs("--decryptkey and --encryptkey cannot both be specified", stderr);
    exit(EXIT_FAILURE);
  }

  if(optind == argc) {
    if (runAllKeys) {
      bufferInput(printKeys);
      exit(EXIT_SUCCESS);
    }
    if (runOneKey) {
      if(decryptInput) {
	oneKey(key, printKeys, stdin, decryptChar);
      } else {
	oneKey(key, printKeys, stdin, encryptChar);
      }
    }
  }

  for (i = optind; i < argc; i++) {
    fileName = argv[i];
    file = fopen(fileName, "r");

    if (file == NULL) {
      if (fileName[0] == '\0') {
	fputs("invalid zero-length file name\n", stderr);
	exit(EXIT_FAILURE);
      }
      fprintf(stderr,"file \"%s\" could not be opened\n", fileName);
      exit(EXIT_FAILURE);
    }

    if (runAllKeys) {
      allKeysFile(printKeys, file);
    }

    if (runOneKey) {
      if(decryptInput) {
	oneKey(key, printKeys, file, decryptChar);
      } else {
	oneKey(key, printKeys, file, encryptChar);
      }
    }
  }
  exit(EXIT_SUCCESS);
}
  


void oneKey(char* keyString, bool printKeys, FILE* file, void (rotateChar)(char, int)) {
  char *end;
  int key = strtol(keyString, &end, 10);
  char c;

  if (end == keyString || *end != '\0') {
    fprintf(stderr,"\"%s\" could not be converted to a number\n", keyString);
    exit(EXIT_FAILURE);
  }

  if (printKeys) {
    printf("Key: %d\t", key);
  }

  while ((c = fgetc(file)) != EOF) {
    rotateChar(c, key);
  }
  fclose(file);
}


void allKeysFile(bool printKeys, FILE* file) {
  int key;
  char c;
  for (key = 1; key < 26; key++) {

    if (printKeys) {
      printf("Key: %d\t", key);
    }

    while ((c = fgetc(file)) != EOF) {
      decryptChar(c, key);
    }

    rewind(file);
  }
  fclose(file);
}


void allKeysMemory(bool printKeys, char* buff) {
  if (buff[0] == '\0')		/* prevents 26 newlines when no input */
    exit(EXIT_SUCCESS);

  int size = strlen(buff), i, key;
  for (key = 1; key < 26; key++) {

    if (printKeys)
      printf("Key: %d\t", key);

    for (i = 0; i < size; i++)
      decryptChar(buff[i], key);

    if (buff[i-1] != '\n')
      putchar('\n');
  }
}


void encryptChar(char input, int key) {
  if (isupper(input)) {
    putchar((((input - 'A') + key) % 26) + 'A');
  } else if (islower(input)) {
    putchar((((input - 'a') + key) % 26) + 'a');
  } else if (isdigit(input)) {
    putchar((((input - '0') + key) % 10) + '0');
  } else {
    putchar(input);
  }
}

void decryptChar(char input, int key) {
  if (isupper(input)) {
    putchar((((input - 'A'))));
  } else if (islower(input)) {
    putchar((((input - 'a') - key) % 26) + 'a');
  } else if (isdigit(input)) {
    putchar((((input - '0') - key) % 10) + '0');
  } else {
    putchar(input);
  }
}


void bufferInput(bool printKeys) {
    char *buff = NULL, *tmp = NULL;
    size_t size = 4096, index = 0, count = 0;
    int ch = EOF;

    buff = (char*) malloc(size*sizeof(char));
    
    while (ch) {
        ch = getc(stdin);

        /* Check if we need to stop. */
        if (ch == EOF)
            ch = 0;

        /* Check if we need to expand. */
        if (size <= index) {
	  if (count >= 16) {	/* ~256M. For tuning, use the following calculation:
				   $ echo $((4096 * $((2**count)))) | numfmt --to iec  */
	    fileTime(printKeys, buff); /* it's file time bb */
	    return;
	  }
            size *= 2;		/* buff size will be 4096, 8192, 16384 etc. */
	    count++;

            tmp = realloc(buff, size);
            if (!tmp) {
                free(buff);
                buff = NULL;
                break;
            }
            buff = tmp;
        }

        /* Actually store the thing. */
        buff[index++] = ch;
    }
    allKeysMemory(printKeys, buff);
    return;
}


void fileTime(bool printKeys, char* buff) {

  FILE * temp = tmpfile();
  char ch = EOF;

  if (temp != NULL) {
    fputs(buff, temp);
  } else {
    fprintf(stderr, "Couldn't make temporary file");
    exit(EXIT_FAILURE);
  }

  while (ch) {
    ch = getc(stdin);
    
    if (ch == EOF)
      ch = 0;
    
    fputc(ch, temp);
  }

  rewind(temp);			/* gotta reel back the VHS for the next guy  */
  allKeysFile(printKeys, temp);
  return;
}
