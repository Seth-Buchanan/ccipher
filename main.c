#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <stdbool.h>
#include <getopt.h>

#define VERSION "1.0"
#define AUTHOR  "Seth Buchanan"

void rotateChar(char input, long key);
void oneKey(char* optarg, bool printKeys, FILE** file);
void allKeys(bool printKeys, FILE** file);
char *scan();

int main(int argc, char *argv[]) {
  bool printKeys = false;
  bool runOneKey = false;
  bool runAllKeys = true;
  int c;
  char* fileName = "";
  char* key;
  char* program_name = argv[0];
  FILE* file;

  while (true) {
    int option_index = 0;
    static struct option long_options[] = {
      {"key",      required_argument, 0,  'k'},
      {"showkeys", no_argument,       0,  's'},
      {"help",     no_argument,       0,  'h'},
      {"version",  no_argument,       0,  'v'},
      {"input",    required_argument, 0,  'i'},
      {0,          0,                 0,   0 }
    };

    c = getopt_long(argc, argv, "k:i:shv",
		    long_options, &option_index);
    if (c == -1)
      break;

    switch (c) {

    case 'i':			/* --input */
      fileName = optarg;

      break;

    case 's':			/* --showkeys */
      printKeys = true;
      break;
      
    case 'k':			/* --key */
      key = optarg;
      runAllKeys = false;
      runOneKey = true;
      break;

    case 'h':			/* --help */
      printf("Usage: %s --input file [OPTION]... \n", program_name);
      fputs("\
By default, the command prints all rotations of the input file.\n\
\nThe command options allow for specifying a key or \n\
printing the key on the line.\n\
  -i file --input file    specify input file \n\
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

    default:
      fprintf(stderr,"?? getopt returned character code 0%o ??\n", c);
    }
  }
  
  if (*fileName == '\0') {
    printf("Usage: %s --input file [OPTION]... \nUse --help to access help page", program_name);
    exit(EXIT_FAILURE);
  } else {
    file = fopen(fileName, "r");
  }
  
  if (file == NULL) {
    fprintf(stderr,"File \"%s\" could not be opened\n", optarg);
    exit(EXIT_FAILURE);
  }
  if (runAllKeys) {
      allKeys(printKeys, &file);
      exit(EXIT_SUCCESS);
  }

  if (runOneKey) {
      oneKey(key, printKeys, &file);
      exit(EXIT_SUCCESS);
  }
  
}

void oneKey(char* optarg, bool printKeys, FILE** file) {
  char *end;
  long key = strtol(optarg, &end, 10);
  char c;

  if (end == optarg || *end != '\0') {
    fprintf(stderr,"\"%s\" could not be converted to a number\n", optarg);
    exit(EXIT_FAILURE);
  }

  if (printKeys) {
    printf("KEY: %lu\t", key);
  }

  while ((c = fgetc(*file)) != EOF) {
    rotateChar((char)c, key);
  }
  fclose(*file);

}

void allKeys(bool printKeys, FILE** file) {
  long key;
  char c;

  for (key = 1; key < 26; key++) {

    if (printKeys) {
      printf("KEY: %lu\t", key);
    }

    while ((c = fgetc(*file)) != EOF) {
      rotateChar((char)c, key);
    }

    rewind(*file);
  }
  fclose(*file);
}


void rotateChar(char input, long key) {
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

  
