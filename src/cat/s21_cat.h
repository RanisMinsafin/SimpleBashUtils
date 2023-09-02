#ifndef S21_CAT_H_
#define S21_CAT_H_

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int numberEmpty;   // b
  int showEnd;       // e
  int showEndE;      // E
  int numberAll;     // n
  int squeezeBlank;  // s
  int showTabs;      // t
  int showTabsT;     // T
  int showUnsigned;  // v
} argumentsInfo;

void haveArguments(int argc, char* argv[]);
void noArguments();
int parser(int argc, argumentsInfo* info, char* argv[]);
void flagB(char prev, int* countEmptyLine, char ch);
void flagE(char ch);
int flagN(int start, int* countLines, char ch);
int flagS(char prev, char next, char ch);
int flagT(char ch);
int flagV(char* ch);
void reader(int argc, char* argv[], argumentsInfo* info);

#endif  // S21_CAT_H_
