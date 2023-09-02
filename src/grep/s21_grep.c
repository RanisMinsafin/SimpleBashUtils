#include "s21_grep.h"

int main(int argc, char* argv[]) {
  if (argc > 3)
    haveArguments(argc, argv);
  else
    fprintf(stderr, "usage: grep [-eivclnhsfo]\n");
  return 0;
}

void haveArguments(int argc, char* argv[]) {
  argumentsInfo info = {0};
  parser(argc, argv, &info);
}

void parser(int argc, char* argv[], argumentsInfo* info) {
  for (int result = 0;
       (result = getopt_long(argc, argv, "eivclnhsfo", NULL, NULL)) != -1;) {
    switch (result) {
      case 'e':
        info->e = 1;
        break;
      case 'i':
        info->i = 1;
        break;
      case 'v':
        info->v = 1;
        break;
      case 'c':
        info->c = 1;
        break;
      case 'l':
        info->l = 1;
        break;
      case 'n':
        info->n = 1;
        break;
      case 'h':
        info->h = 1;
        break;
      case 's':
        info->s = 1;
        break;
      case 'f':
        info->f = 1;
        break;
      case 'o':
        info->o = 1;
        break;
      default:
        if (info->e == 0 && info->i == 0 && info->v == 0 && info->c == 0 &&
            info->l == 0 && info->n == 0 && info->h == 0 && info->s == 0 &&
            info->f == 0 && info->o == 0)
          fprintf(stderr, "usage: grep [-eivclnhsfo]\n");
    }
  }
  if ((info->e + info->i + info->v + info->c + info->l + info->n + info->h +
       info->s + info->f + info->o) != 0)
    patternFinder(argc, argv, info);
}

void patternFinder(int argc, char* argv[], argumentsInfo* info) {
  char c = '-';
  for (int i = 0; i < argc; i++) {
    if (strchr(argv[i], c) != NULL) {
      info->amountFlags++;
    }
  }
  if (info->f != 1) {
    info->amountOfFiles = (argc - info->amountFlags - 2);
    for (int amountOfPrints = info->amountFlags + 2; amountOfPrints < argc;
         amountOfPrints++) {
      greper(&argv[amountOfPrints], &argv[info->amountFlags + 1], info);
      info->amountOfString = 0;
      info->amountOfMatch = 0;
    }
  } else {
    flagF(argc, argv, info);
  }
}

void flagF(int argc, char* argv[], argumentsInfo* info) {
  FILE* file = NULL;
  if ((file = fopen(argv[info->amountFlags + 1], "r")) != NULL) {
    for (int amountOfPrints = info->amountFlags + 2; amountOfPrints < argc;
         amountOfPrints++) {
      char pattern[1024] = {'\0'};
      while ((fgets(pattern, 1024, file)) != NULL) {
        char* patternPointer = pattern;
        greper(&argv[amountOfPrints], &patternPointer, info);
      }
    }
  } else {
    fprintf(stderr, "s21_grep: %s: No such file or directory\n",
            argv[info->amountFlags + 1]);
  }
}

void greper(char* argv[], char* pattern[], argumentsInfo* info) {
  FILE* file = NULL;
  file = fopen(*argv, "r");
  if (file == NULL) {
    if (info->s == 0) {
      fprintf(stderr, "s21_grep: %s: No such file or directory\n", *argv);
    }
  } else {
    char string[1024] = {'\0'};
    while ((fgets(string, 1024, file)) != NULL) {
      if (info->n) info->amountOfString++;
      regexProcessing(argv, string, pattern, info);
    }
    regexPlusFlags(argv, pattern, info);
    fclose(file);
  }
}

void regexProcessing(char* argv[], char* string, char* pattern[],
                     argumentsInfo* info) {
  regex_t regex;
  flagSwitch(info);
  if (info->i)
    regcomp(&regex, *pattern, REG_ICASE | REG_NEWLINE);
  else
    regcomp(&regex, *pattern, REG_EXTENDED | REG_NEWLINE);
  if (info->c || info->l || info->o) {
    if (info->v == 1) {
      if (regexec(&regex, string, 0, NULL, 0) != 0) {
        info->amountOfMatch++;
      }
    } else {
      if (regexec(&regex, string, 0, NULL, 0) == 0) {
        info->amountOfMatch++;
      }
    }
  } else {
    if (info->v == 1) {
      if (regexec(&regex, string, 0, NULL, 0) != 0) {
        stringPrinter(argv, string, info);
      }
    } else {
      if (regexec(&regex, string, 0, NULL, 0) == 0) {
        stringPrinter(argv, string, info);
      }
    }
  }
  regfree(&regex);
}

void regexPlusFlags(char* argv[], char* pattern[], argumentsInfo* info) {
  if ((info->c == 1 && info->l != 1) || info->o == 1) {
    if (info->amountOfFiles > 1) {
      if (info->c == 1) {
        if (info->h == 1) {
          fprintf(stdout, "%d\n", info->amountOfMatch);
        } else {
          fprintf(stdout, "%s:%d\n", *argv, info->amountOfMatch);
        }
      } else if (info->o == 1) {
        while (info->amountOfMatch != 0) {
          if (info->h == 1) {
            fprintf(stdout, "%s\n", *pattern);
            info->amountOfMatch--;
          } else {
            fprintf(stdout, "%s:%s\n", *argv, *pattern);
            info->amountOfMatch--;
          }
        }
      }
    } else {
      if (info->c == 1) {
        fprintf(stdout, "%d\n", info->amountOfMatch);
      } else if (info->o == 1) {
        while (info->amountOfMatch != 0) {
          if (info->n != 0) {
            fprintf(stdout, "%d:%s\n", info->amountOfString, *pattern);
            info->amountOfMatch--;
          } else {
            fprintf(stdout, "%s\n", *pattern);
            info->amountOfMatch--;
          }
        }
      }
    }
  } else if (info->c == 1 && info->l == 1 && info->amountOfFiles > 1) {
    fprintf(stdout, "%s:%d\n", *argv, info->amountOfMatch);
    fprintf(stdout, "%s\n", *argv);
  } else if (info->c == 1 && info->l == 1 && info->amountOfFiles == 1) {
    fprintf(stdout, "%d\n", info->amountOfMatch);
    fprintf(stdout, "%s\n", *argv);
  } else if (info->l == 1 && info->amountOfMatch > 0) {
    fprintf(stdout, "%s\n", *argv);
  }
}

void stringPrinter(char* argv[], char* string, argumentsInfo* info) {
  if (info->amountOfFiles > 1) {
    if (info->n == 1) {
      if (info->h == 1) {
        fprintf(stdout, "%d:%s", info->amountOfString, string);
      } else {
        fprintf(stdout, "%s:%d:%s", *argv, info->amountOfString, string);
      }
    } else {
      if (info->h == 1) {
        fprintf(stdout, "%s", string);
      } else {
        fprintf(stdout, "%s:%s", *argv, string);
      }
    }
  } else {
    if (info->n == 1) {
      fprintf(stdout, "%d:%s", info->amountOfString, string);
    } else {
      fprintf(stdout, "%s", string);
    }
  }
}

void flagSwitch(argumentsInfo* info) {
  if (info->c) {
    info->o = 0;
  } else if (info->v) {
    info->o = 0;
  } else if (info->l) {
    info->v = 0;
    info->n = 0;
    info->h = 0;
    info->o = 0;
  }
}
