#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
#include <getopt.h>

#define VERSION "1.0"
#define AUTHOR  "Seth Buchanan"

void encryptChar(char, char*, char*, char*);
void makeMap(char*, int);
void makeUpperMap(char*, int);
void makeNumMap(char*, int);
void oneKey(int key, bool printKeys, FILE* file);
void allKeysFile(bool printKeys, FILE* file);
void allKeysMemory(bool printKeys, char* file);
void bufferInput(bool printKeys);
void fileTime(bool printKeys, char* buff);
void printUsage(char* program_name);
int  isDir(char*);
int  convertKey(char* keyString);


int main(int argc, char** argv) {
  bool printKeys, runOneKey, runAllKeys;

  printKeys = runOneKey = runAllKeys = false;

  int c, i, key;
  char* fileName = "";
  char* program_name = argv[0];
  FILE* file;

  while (true) {
    int option_index = 0;
    static struct option long_options[] = {
      {"encrypt",  required_argument, 0,  'e'},
      {"decrypt",  required_argument, 0,  'd'},
      {"allkeys",  no_argument,       0,  'a'},
      {"showkeys", no_argument,       0,  's'},
      {"help",     no_argument,       0,  'h'},
      {"version",  no_argument,       0,  'v'},
      {0,          0,                 0,   0 }
    };

    c = getopt_long(argc, argv, "shave:d:",
		    long_options, &option_index);
    if (c == -1)
      break;

    switch (c) {
    case 's':			/* --showkeys */
      printKeys = true;
      break;
      
    case 'a':			/* --allkeys */
      runAllKeys = true;
      break;

    case 'e':			/* --encrypt */
      key += convertKey(optarg);
      runAllKeys = false;
      runOneKey = true;
      break;

    case 'd':			/* --decrypt */
      key -= convertKey(optarg);
      runAllKeys = false;
      runOneKey = true;
      break;

    case 'h':			/* --help */
      printUsage(program_name);
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
      printf("Try '%s --help' for more information.\n", program_name);
      exit(EXIT_FAILURE);
      break;
      
    default:
      fprintf(stderr,"?? getopt returned character code 0%o ??\n", c);
    }

  }
  if (!(runOneKey || runAllKeys)) {
    printUsage(program_name);
    exit(EXIT_SUCCESS);
  }

  if(optind == argc) {		/* Run from stdin */
    if (runAllKeys) {
      bufferInput(printKeys);
      exit(EXIT_SUCCESS);
    }
    if (runOneKey) {
      oneKey(key, printKeys, stdin);
      exit(EXIT_SUCCESS);
    }
  }

  for (i = optind; i < argc; i++) {
    fileName = argv[i];
    if (isDir(fileName)) {
      fprintf(stderr,"\"%s\" is a directory\n", fileName);
      continue;
    } 

    file = fopen(fileName, "r");
    if (file == NULL) {
      if (fileName[0] == '\0') {
	fputs("invalid zero-length file name\n", stderr);
	continue;
      }
      fprintf(stderr,"file \"%s\" could not be opened\n", fileName);
      continue;
    }

    if (runAllKeys) {
      allKeysFile(printKeys, file);
      continue;
    }

    if (runOneKey) {
      oneKey(key, printKeys, file);
      continue;
    }

  }

  exit(EXIT_SUCCESS);
}


void oneKey(int key, bool printKeys, FILE* file) {
  char *map      = (char*) malloc(26*sizeof(char));
  char *upperMap = (char*) malloc(26*sizeof(char));
  char *numMap   = (char*) malloc(10*sizeof(char));
  char c;

  makeMap(map, key);
  makeUpperMap(upperMap, key);
  makeNumMap(numMap, key);
  if (printKeys) {
    printf("Key: %d\t", abs(key));
  }

  while ((c = fgetc(file)) != EOF) {
    if (islower(c)) {
      putchar(map[c - 'a']);
    } else if (isupper(c)) {
      putchar(upperMap[c - 'A']);
    } else if (isdigit(c)) {
      putchar(numMap[c - '0']);
    } else {
      putchar(c);
    }
  }
  free(map);
  free(upperMap);
  free(numMap);

  fclose(file);
}


void allKeysFile(bool printKeys, FILE* file) {
  char *map      = (char*) malloc(26*sizeof(char));
  char *upperMap = (char*) malloc(26*sizeof(char));
  char *numMap   = (char*) malloc(10*sizeof(char));
  char c;
  int key;

  for (key = -1; key > -26; key--) {
    makeMap(map, key);
    makeUpperMap(upperMap, key);
    makeNumMap(numMap, key);

    if (printKeys) {
      printf("Key: %d\t", abs(key));
    }

    while ((c = fgetc(file)) != EOF) {
      if (islower(c)) {
	putchar(map[c - 'a']);
      } else if (isupper(c)) {
	putchar(upperMap[c - 'A']);
      } else if (isdigit(c)) {
	putchar(numMap[c - '0']);
      } else {
	putchar(c);
      }
    }

    rewind(file);
  }
  free(map);
  free(upperMap);
  free(numMap);
  fclose(file);
}


void allKeysMemory(bool printKeys, char* buff) {
  char *map      = (char*) malloc(26*sizeof(char));
  char *upperMap = (char*) malloc(26*sizeof(char));
  char *numMap   = (char*) malloc(10*sizeof(char));
  int key, i;  

  for (key = -1; key > -26; key--) {
    makeMap(map, key);
    makeUpperMap(upperMap, key);
    makeNumMap(numMap, key);

    if (printKeys)
      printf("Key: %d\t", abs(key));

    for (i = 0; buff[i] != '\0'; i++)
      if (islower(buff[i])) {
	putchar(map[buff[i] - 'a']);
      } else if (isupper(buff[i])) {
	putchar(upperMap[buff[i] - 'A']);
      } else if (isdigit(buff[i])) {
	putchar(numMap[buff[i] - '0']);
      } else {
	putchar(buff[i]);
      }


    if (buff[i-1] != '\n')
      putchar('\n');
  }
  free(map);
  free(upperMap);
  free(numMap);
}


void makeMap(char* map, int key) {
  int i;

  if (key < 0) {
    key %= 26;
    key += 26;
  }
  for (i = 0; i < 26; i++) {
    map[i] = 'a' + ((i + key) % 26);
  }
}


void makeUpperMap(char* upperMap, int key) {
  int i;

  if (key < 0) {
    key %= 26;
    key += 26;
  }
  for (i = 0; i < 26; i++) {
    upperMap[i] = 'A' + ((i + key) % 26);
  }
}


void makeNumMap(char* numMap, int key) {
  int i;

  if (key < 0) {
    key %= 10;
    key += 10;
  }
  for (i = 0; i < 10; i++) {
    numMap[i] = '0' + ((i + key) % 10);
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
  if (buff[0] != '\0') {
    allKeysMemory(printKeys, buff);
  }
  return;
}


void fileTime(bool printKeys, char* buff) {
  FILE * temp = tmpfile();
  char ch = EOF;

  if (temp != NULL) {
    fputs(buff, temp);
  } else {
    fprintf(stderr, "Couldn't make temporary file");
    return;
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


int convertKey(char* keyString) {
  char *end;
  int key = strtol(keyString, &end, 10);
 
  if (end == keyString || *end != '\0') {
    fprintf(stderr,"\"%s\" could not be converted into an integer\n", keyString);
    exit(EXIT_FAILURE);
  }
  return key;
}


int isDir(char* fileName) {
  struct stat path;

  stat(fileName, &path);
  return S_ISDIR(path.st_mode);
}


void printUsage(char* program_name) {
  printf("Usage: %s [OPTION]... [FILE]... \n", program_name);
  fputs("\
Specify a cesar cipher encryption or decryption key \n\
or decrypt given text with all 26 keys.\n\n\
By default, print help and exit.\n\n\
Without a FILE, input is taken through standard in.\n\
  -e      --encrypt       encrypt text with specified key \n\
  -d      --decrypt       decrypt text with specified key \n\
  -a      --allkeys       decrypt text with all keys \n\
  -s      --showkeys      print encryption key \n\
  -h      --help          print this page and exit\n\
  -v      --version       print program information\n\
", stdout);
}
