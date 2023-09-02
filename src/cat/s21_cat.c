#include "s21_cat.h"

int main(int argc, char** argv) {
  if (argc > 1)
    haveArguments(argc, argv);
  else
    noArguments();
  return 0;
}

void haveArguments(int argc, char* argv[]) {
  argumentsInfo info = {0, 0, 0, 0, 0, 0, 0, 0};
  int flag = parser(argc, &info, argv);
  if (flag == 0) reader(argc, argv, &info);
}

void noArguments() {
  int c = -1;
  while (1) {
    c = getchar();
    printf("%c", c);
  }
}

int parser(int argc, argumentsInfo* info, char* argv[]) {
  int result = 0, option_index = 0, flag = 0;
  static struct option long_options[] = {
      {"number-nonblank", no_argument, NULL, 'b'},
      {"squeeze", no_argument, NULL, 's'},
      {"number-blank", no_argument, NULL, 'n'},
      {NULL, 0, NULL, 0}};
  while ((result = getopt_long(argc, argv, "+benstvET", long_options,
                               &option_index)) != -1) {
    switch (result) {
      case 'b':
        info->numberEmpty = 1;
        break;
      case 'e':
        info->showEnd = 1;
        break;
      case 'n':
        info->numberAll = 1;
        break;
      case 's':
        info->squeezeBlank = 1;
        break;
      case 't':
        info->showTabs = 1;
        break;
      case 'v':
        info->showUnsigned = 1;
        break;
      case 'E':
        info->showEndE = 1;
        break;
      case 'T':
        info->showTabsT = 1;
        break;
      default:
        fprintf(stderr, "usage: cat [-benstuv] [file ...]\n");
        flag = 1;
    }
  }
  return flag;
}

void reader(int argc, char* argv[], argumentsInfo* info) {
  FILE* fp = NULL;
  int n = 0;
  while ((argc > optind + n) &&
         (((fp = fopen(argv[optind + n], "r")) != NULL))) {
    int start = 1, countEmptyLine = 1, countLines = 1;
    char prev = '\n', next = ' ';
    char ch[2] = {'\0'};
    while ((*ch = getc(fp)) != EOF) {
      if (info->squeezeBlank && flagS(prev, next, *ch)) continue;
      if (info->numberAll && !(info->numberEmpty))
        start = flagN(start, &countLines, *ch);
      if (info->numberEmpty) flagB(prev, &countEmptyLine, *ch);
      if (info->showEnd || info->showEndE) flagE(*ch);
      if (info->showEnd || info->showTabs || info->showUnsigned) flagV(ch);
      next = prev;
      prev = *ch;
      if ((info->showTabs || info->showTabsT) && flagT(*ch)) continue;
      if (*ch == '\0')
        fputc(*ch, stdout);
      else
        fputs(ch, stdout);
      memset(ch, '\0', 2);
    }
    n++;
    fclose(fp);
  }
  if (n == 0 && fp == NULL) {
    fprintf(stderr, "Cannot open file.\n");
  }
}

void flagB(char prev, int* countEmptyLine, char ch) {
  if (prev == '\n' && ch != '\n') printf("%6d\t", (*countEmptyLine)++);
}

void flagE(char ch) {
  if (ch == '\n') printf("$");
}

int flagN(int start, int* countLines, char ch) {
  if (start) printf("%6d\t", (*countLines)++);
  return ch == '\n';
}

int flagS(char prev, char next, char ch) {
  return prev == '\n' && next == '\n' && ch == '\n';
}

int flagV(char* ch) {
  if (((*ch <= 31) && *ch != 10 && *ch != 9)) {
    printf("^");
    *ch += 64;
  } else if (*ch == 127) {
    printf("^");
    *ch -= 64;
  }
  return *ch;
}

int flagT(char ch) {
  int tab = 0;
  if (ch == '\t') tab = printf("^I");
  return tab;
}
