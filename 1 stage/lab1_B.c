// Lab 1 B - translation from latin to cyrillic

#include <ctype.h>
#include <stdio.h>
#include <string.h>

unsigned char letter[] = "������� �������� ����� � �";
unsigned char Letter[] = "������� �������� ����� � �";
int RUS = 0xe, LAT = 0xf, LANG = 0;
char buf = 0;

int exclude(int c, FILE *it, FILE *ti) {
  char u, a, t = 0;
  switch (c) {
    case 20:
      a = fgetc(ti);
      if (a < 91) {
        t = 1;
      }
      u = '�';
      fseek(ti, 1, SEEK_CUR);
      break;
    case 17:
      a = fgetc(ti);
      if (a < 91) {  // big symbols
        t = 1;
      }
      switch (tolower(a)) {
        case 'c':
          u = '�';
          break;
        case 's':
          u = '�';
          break;
        case 'z':
          u = '�';
          break;
        case '`':
          u = '�';
          fseek(ti, 1, SEEK_CUR);
          break;
        case 'e':
          u = '�';
          fseek(ti, 1, SEEK_CUR);
          break;
        case 'y':
          c = 0;
          c = fgetc(ti);
          switch (c) {
            case 'o':
              u = '�';
              break;
            case '`':
              u = '�';
              break;
            case 'u':
              u = '�';
              break;
            case 'a':
              u = '�';
              break;
            default:
              break;
          }
        default:
          break;
      }
    default:
      break;
  }
  if (t == 1 && u == '�') {
    fputc('�', it);
    buf = 1;
  } else if (buf == 1 && u == '�') {
    fputc('�', it);
    buf = 1;
  } else if (t == 1) {
    u = u & 0xdf;
    fputc(u, it);
    buf = 1;
  } else {
    fputc(u, it);
    buf = 0;
  }
  return 0;
}

void retra(int c, FILE *it) {
  //small sym
  if (c < 123 && c > 96) {
    if (letter[c - 97] != ' ') {
      fputc(letter[c - 97], it);
      buf = 0;
    }
  }
  //big sym
  if ((c > 64) && (c < 91)) {
    if (Letter[c - 65] != ' ') {
      fputc(Letter[c - 65], it);
      buf = 1;
    }
  }
  //b
  if (c == '`' && buf == 1) {
    fputc('�', it);
    buf = 1;
  } else if (c == '`' && buf == 0) {
    fputc('�', it);
    buf = 0;
  }
}

int main(int argc, char *argv[]) {
  FILE *ti, *it; // ti=INF it=OUTF
  int c;
  char outname[256];
  while (--argc) {
    ti = fopen(argv[argc], "r");
    if (ti == NULL) {
      printf("file don't open\n");
    }
    strncpy(outname, argv[argc], 251);
    strncat(outname, ".txt", 255);
    it = fopen(outname, "w");
    if (it == NULL) {
      printf("file don't open\n");
    }

    while ((c = fgetc(ti)) != EOF) {
      //selector language
      if (c == RUS) {
        LANG = 0;
        c = fgetc(ti);
      } else if (c == LAT) {
        LANG = 1;
        c = fgetc(ti);
      }
      //syblo or b or 2-symb
      if (isalpha(c) || c == '`' || c == 17 || c == 20) {
        if (LANG == 1) {
          fputc(c, it);
        } else {
          if (c == 17 || c == 20) {
            exclude(c, it, ti);
          } else {
            retra(c, it);
          }
        }
      } else {
        fputc(c, it);
      }
    }
    fclose(ti);
    fclose(it);
  }

  return 0;
}