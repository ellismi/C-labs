// Lab 1 A - translation from cyrillic to latin

#include <ctype.h>
#include <stdio.h>
#include <string.h>

unsigned char letter[] = "abvgde2zijklmnoprstufxc2222222";
unsigned char Letter[] = "ABVGDE2ZIJKLMNOPRSTUFXC2222222";
unsigned char buf = 0;

int RUS = 0xe, LAT = 0xf, LANG = 0, TW = 0x11, TR = 0x14;

int iscyr(int c) {
  if ((c >= 192) || (c == 168) || (c == 184)) return 1;
  return 0;
}

int transl(int c, FILE *it) {
  if (c >= 224) {
    if (isalpha(letter[c - 224])) {
      fputc(letter[c - 224], it);
    } else {
      switch (c - 224) {
        case 6:
          fprintf(it, "%czh", TW);
          break;
        case 23:
          fprintf(it, "%cch", TW);
          break;
        case 24:
          fprintf(it, "%csh", TW);
          break;
        case 25:
          fprintf(it, "%cshh", TR);
          break;
        case 26:
          fprintf(it, "%c``", TW);
          break;
        case 27:
          fprintf(it, "%cy`", TW);
          break;
        case 28:
          fputc('`', it);
          break;
        case 29:
          fprintf(it, "%ce`", TW);
          break;
        case 30:
          fprintf(it, "%cyu", TW);
          break;
        case 31:
          fprintf(it, "%cya", TW);
          break;
      }
    }
    return 0;
  } else if (c >= 192) {
    if (isalpha(Letter[c - 192])) {
      fputc(Letter[c - 192], it);
      return 0;
    }

    else {
      switch (c - 192) {
        case 6:
          fprintf(it, "%cZh", TW);
          break;
        case 23:
          fprintf(it, "%cCh", TW);
          break;
        case 24:
          fprintf(it, "%cSh", TW);
          break;
        case 25:
          fprintf(it, "%cShh", TR);
          break;
        case 26:
          fprintf(it, "%c``", TW);
          break;
        case 27:
          fprintf(it, "%cY`", TW);
          break;
        case 28:
          fputc('`', it);
          break;
        case 29:
          fprintf(it, "%cE`", TW);
          break;
        case 30:
          fprintf(it, "%cYu", TW);
          break;
        case 31:
          fprintf(it, "%cYa", TW);
          break;
      }
    }
  }

  if (c == 168) {
    fprintf(it, "%cYo", TW);
  }
  if (c == 184) {
    fprintf(it, "%cyo", TW);
  }
}

int main(int argc, char *argv[]) {
  FILE *ti, *it;  // ti=INF it=OUTF
  int c;
  char outname[256];
  while (--argc) {
    ti = fopen(argv[argc], "r");
    if (ti == NULL) {
      printf("file 1 don't open !\n");
    }
    strncpy(outname, argv[argc], 252);
    strncat(outname, ".tl", 256);
    it = fopen(outname, "w");
    if (it == NULL) {
      printf("file don't open\n");
    }
    while ((c = fgetc(ti)) != EOF) {
      if (iscyr(c)) {
        if (LANG == 1) {
          LANG = 0;
          fputc(RUS, it);
        }
        transl(c, it);
      } else {
        if (isalpha(c)) {
          if (LANG == 0) {
            LANG = 1;
            fputc(LAT, it);
          }
        }
        fputc(c, it);
      }
    }
    fclose(ti);
    fclose(it);
  }
  return 0;
}
