#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// The sleep(ms) function
#ifdef _WIN32
#include <windows.h>
#define sleep(ms) Sleep(ms)
#elif __unix
#define sleep(ms)                       \
  do                                    \
  {                                     \
    struct timespec ts;                 \
    ts.tv_sec = ms / 1000;              \
    ts.tv_nsec = (ms % 1000) * 1000000; \
    nanosleep(&ts, NULL);               \
  } while (0);
#else
#error "Unknown platform"
#endif

// colors
#define RED "\033[91m"
#define YELLOW "\033[93m"
#define PURPLE "\033[95m"
#define WHITE "\033[97m"
#define RESET "\033[0m"

typedef enum
{
  false,
  true
} bool;
int random_int(int min, int max)
{
  return rand() % (max - min + 1) + min;
}
typedef enum
{
  print,
  help,
  version
} Command;

void cyprint(char *text, int speed, bool newline, bool random_speed)
{
  for (int i = 0; i < strlen(text); i++)
  {
    printf("%c", text[i]);
    fflush(stdout);

    if (random_speed)
    {
      sleep(random_int(20, speed));
    }
    else
    {
      sleep(speed);
    }
  }
  if (newline)
  {
    printf("\n");
  }
}

int main(int argc, char *argv[])
{
  srand((int)clock() + (int)time(NULL));
  // the text to print
  char *text = NULL;
  // the timout in milliseconds between each character
  int speed = 50;
  // whether to print a newline after the text
  bool newline = true;
  bool random_speed = true;
  // the action to execute
  Command command = print;

  // Parse arguments
  while (--argc > 0)
  {
    char *arg = *++argv;
    if (strcmp(arg, "--help") == 0 || strcmp(arg, "-h") == 0)
    {
      command = help;
    }
    else if (strcmp(arg, "--version") == 0 || strcmp(arg, "-v") == 0)
    {
      command = version;
    }
    else if (strcmp(arg, "-s") == 0 || strcmp(arg, "--speed") == 0)
    {
      if (argc <= 1)
      {
        printf("%sError:%s -s/--speed requires an argument\n", RED, RESET);
        exit(1);
      }
      arg = *++argv;
      argc--;
      speed = atoi(arg);
      if (speed <= 0)
      {
        printf("%sError:%s Invalid speed.\n", RED, RESET);
        exit(1);
      }
    }
    else if (strcmp(arg, "--no-random-speed") == 0 || strcmp(arg, "-r") == 0)
    {
      random_speed = false;
    }
    else if (text == NULL)
    {
      text = arg;
    }
    else
    {
      printf("Unknown argument: %s\n", arg);
      return 1;
    }
  }

  // Execute the command
  switch (command)
  {
  case print:
    if (text == NULL)
    {
      printf("%sError:%s No text to print.\n", RED, RESET);
      return 1;
    }
    cyprint(text, speed, newline, random_speed);
    break;
  case help:
    printf("Cyprint\n");
    printf("%s━━━━━━━━━━━━━━━━━%s\n", PURPLE, RESET);
    printf("Author: %sSkwalExe%s\n", PURPLE, RESET);
    printf("Github: %shttps://github.com/SkwalExe/%s\n", PURPLE, RESET);
    printf("%s━━━━━━━━━━━━━━━━━%s\n", PURPLE, RESET);
    cyprint("Print text with a typing effect.", 50, true, false);
    printf("%s━━━━━━━━━━━━━━━━━%s\n", PURPLE, RESET);
    printf("Options :\n");
    printf("\t%s-v, --version: %sPrints the version of the program and exit%s\n", PURPLE, YELLOW, RESET);
    printf("\t%s-h, --help: %sPrints this message and exit%s\n", PURPLE, YELLOW, RESET);
    printf("\t%s-s, --speed: %sSets the delay between each chars (in ms)%s\n", PURPLE, YELLOW, RESET);
    printf("\t%s-r, --no-random-speed: %sDisable random delay between each char randomly generated from 20 to speed%s\n", PURPLE, YELLOW, RESET);
    printf("\t%s[text]: %sThe text to print%s\n", PURPLE, YELLOW, RESET);
    break;
  case version:
    printf("Cyprint 0.1.0\n");
    break;
  }
  return 0;
}
