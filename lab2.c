// Lab 2 - count words from text

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct word {
  char *w;
  int count;
} WORD;

WORD *words[100000];
char *cw;
int total = 0;

int tolowcyr(int i) {
	if (i > 191 && i < 224) {
		return i | 32;
	}
	else if (i == 168) {
		return i | 16;
	}
	else {
		return i;
	}
}

char iscyr(int i) {
  if (i >= 192 || i == 168 || i == 184) {
    return 1;
  }
  return 0;
}

char issp(char t) { return (t == '-') || (t == '`') || (t == '\''); }

char *getword(FILE *in) {
  char *w = (char *)malloc(255 * sizeof(char));
  char *p = w;     // word
  int c;           // alpha
  char state = 0;  // Y/n

  while (1) {
    c = fgetc(in);
    if (c == EOF) {
      if (state == 0) {
        return NULL;
      } else {
        *p++ = '\0';
        return w;
      }
    }
    if (!state && isalpha(c) || iscyr(c)) {
      state = 1;
    }
    if (state && (isalnum(c)) || issp(c) || iscyr(c)) {
      if (isalpha(c)) {
        c = tolower(c);
      } else if (iscyr(c)) {
        c = tolowcyr(c);
        *p++ = c;
        printf("%c ",c);
        printf("%d\n",c);
      } else if (c == '-') {
        c = fgetc(in);
        if (c == '\n' || c == '\r') {
          c = fgetc(in);
        } else if (isalpha(c) || iscyr(c)) {
          fseek(in, -1, SEEK_CUR);
          *p++ = '-';
        }
        *p = c;
      }
    } else if (state) {
      *p++ = '\0';
      return w;
    }
  }
  return NULL;
}

int strnum(WORD **a, WORD **b) { return ((*a)->count - (*b)->count) * (-1); }

int strcyrcmp(char a, char b) {
  if (a == b) return 0;
  // �
  if (a == '\xb8') return (unsigned char)b > 229 ? -1 : 1;
  if (b == '\xb8') return (unsigned char)a > 229 ? 1 : -1;
  // ��� ���������
  if (((unsigned char)a > 192 && b == '\0') ||
      ((unsigned char)b > 192 && a == '\0')) {
    return (a - b) * -1;
  }
  return (a - b);
}

int stralh(WORD **w1, WORD **w2) {
  char *p1 = (*w1)->w, *p2 = (*w2)->w;
  int cmp = 0;
  while (*p1 != '\0' && *p2 != '\0') {
    cmp = strcyrcmp(*p1, *p2);
    if (!cmp) {
      p1++;
      p2++;
      continue;
    }
    return cmp;
  }
  return strcyrcmp(*p1, *p2);
}

int main(int argc, char *argv[]) {
  FILE *in, *out_alh, *out_num;

  if (argc < 2) {
    printf("�� ������ ������� ������ ������!\n");
    exit(0);
  }

  while (--argc) {
    char outname[256];

    in = fopen(argv[argc], "r");
    if (in == NULL) {
      printf("file 1 don't open !\n");
    }
    strncpy(outname, argv[argc], 248);
    strncat(outname, "_alh.txt", 256);

    out_alh = fopen(outname, "w");
    if (out_alh == NULL) {
      printf("file don't open\n");
    }
    strncpy(outname, argv[argc], 248);
    strncat(outname, "_num.txt", 256);

    out_num = fopen(outname, "w");
    if (out_num == NULL) {
      printf("file don't open\n");
    }

    while ((cw = getword(in)) != NULL) {
      printf("%s\n",cw);
      int found = 0;
      for (int i = 0; i < total; i++) {
        if (strcmp(cw, words[i]->w) == 0) {
          words[i]->count++;
          found = 1;
          break;
        }
      }
      //printf("%s",cw);
      if (found) continue;
      words[total] = malloc(sizeof(WORD));
      words[total]->count = 1;
      words[total]->w = malloc(strlen(cw) + 1);
      words[total]->w = cw;
      total++;
    }
    fclose(in);
  }
  printf("1");

  qsort(words, total, sizeof(WORD *),
        (int (*)(const void *, const void *))strnum);

  fprintf(out_num, "total words: %d\n", total);
  for (int i = 0; i < total; i++) {
    fprintf(out_num, "%s  %d\n", words[i]->w, words[i]->count);
  }

  qsort(words, total, sizeof(WORD *),
        (int (*)(const void *, const void *))stralh);
  fprintf(out_alh, "total words: %d\n", total);
  for (int i = 0; i < total; i++) {
    fprintf(out_alh, "%s  %d\n", words[i]->w, words[i]->count);
  }
  fclose(out_alh);
  fclose(out_num);
  return 0;
}
