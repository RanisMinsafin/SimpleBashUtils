#ifndef S21_GREP_H_
#define S21_GREP_H_

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
  int amountFlags;
  int amountOfFiles;
  int amountOfString;
  int amountOfMatch;
} argumentsInfo;

void haveArguments(int argc, char* argv[]);
void parser(int argc, char* argv[], argumentsInfo* info);
void patternFinder(int argc, char* argv[], argumentsInfo* info);
void flagF(int argc, char* argv[], argumentsInfo* info);
void greper(char* argv[], char* pattern[], argumentsInfo* info);
void regexProcessing(char* argv[], char* string, char* pattern[],
                     argumentsInfo* info);
void regexPlusFlags(char* argv[], char* pattern[], argumentsInfo* info);
void stringPrinter(char* argv[], char* string, argumentsInfo* info);
void flagSwitch(argumentsInfo* info);

#endif  // S21_GREP_H_
