#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

  const int SIZE = 1024;

  int lineNum = 0, numshift = 0, reverseShift = 0, args = argc, num = 1,
      eolFlag = 0, numRead = 0, j = 0, fd;

  char buf[SIZE];
  char c;
  int shifted = 0;

  // CHECK FOR NO ARGS

  if (argc == 1) {
    printf("Usage: %s -nsr file.txt\n", argv[0]);
    exit(0);
  }

  // PARSE ARGS FOR SWITCHES

  while (args--) {
    if (argv[args][0] == '-') {
      int switchLen = (int)strlen(argv[args]);
      while (switchLen--) {
        if (argv[args][switchLen] == 'n')
          lineNum = 1;
        if (argv[args][switchLen] == 's')
          numshift = 1;
        if (argv[args][switchLen] == 'r')
          reverseShift = 1;
      }
    }

    if (isdigit((unsigned char)argv[args][0])) {
      shifted = atoi(argv[args]);
    }
  }

  // OPEN FILE FOR READING

  fd = open(argv[argc - 1], O_RDONLY);
  if (fd == -1) {
    perror(argv[argc - 1]);
    exit(1);
  }

  // READ FILE AND PRINT TO CONSOLE (FOR -n OPTION)

  if (lineNum && !numshift && !reverseShift) {
    while ((numRead = read(fd, buf, SIZE)) > 0) {
      for (j = 0; j < numRead; j++) {
        c = buf[j];

        if (eolFlag || num == 1) {
          printf("     %d  ", num++);
          eolFlag = 0;
        }

        printf("%c", c);

        if (c == '\n') {
          eolFlag = 1;
        }
      }
    }
    close(fd);
    return 0;
  }

  // READ FILE, PROCESS CONTENT (SHIFT OR REVERSE SHIFT), AND WRITE TO FILE

  char output[SIZE * 10]; // Buffer to store the processed content
  int outputIndex = 0;

  while ((numRead = read(fd, buf, SIZE)) > 0) {
    for (j = 0; j < numRead; j++) {
      c = buf[j];

      if (numshift && isalpha((unsigned char)c) && shifted != 0) {
        char ccipher = (c - 'a' + shifted) % 26 + 'a';
        output[outputIndex++] = ccipher;
      } else if (reverseShift && isalpha((unsigned char)c) && shifted != 0) {
        char ccipher = ((c - 'a' - shifted + 26) % 26) + 'a';
        output[outputIndex++] = ccipher;
      } else {
        output[outputIndex++] = c;
      }
    }
  }

  // CLOSE FILE AFTER READING
  close(fd);

  // OPEN FILE FOR WRITING (overwrite original content)
  fd = open(argv[argc - 1], O_WRONLY | O_TRUNC);
  if (fd == -1) {
    perror("Error opening file for writing");
    exit(1);
  }

  // WRITE THE PROCESSED CONTENT TO THE FILE
  if (write(fd, output, outputIndex) != outputIndex) {
    perror("Error writing to file");
    close(fd);
    exit(1);
  }

  // CLOSE FILE AFTER WRITING
  close(fd);

  printf("The file has been successfully processed and written.\n");

  return 0;
}