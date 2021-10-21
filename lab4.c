// Lab 4 - counting words from text with help tree

#include <ctype.h>
#include <iconv.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
  int count;
  char *word;
  struct node *left;
  struct node *right;
} NODE;

NODE *root = NULL;
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

char issp(char t) { return (t == '-') || (t == '`') || (t == '\''); }

char iscyr(int i) {
  if (i >= 192 || i == 168 || i == 184) {
    return 1;
  }
  return 0;
}

int strcyrcmp(char a, char b) {
  if (a == b) return 0;
  if (a == '\xb8') return (unsigned char)b > 229 ? -1 : 1;
  if (b == '\xb8') return (unsigned char)a > 229 ? 1 : -1;
  // cyrilic
  if (((unsigned char)a > 192 && b == '\0') ||
      ((unsigned char)b > 192 && a == '\0')) {
    return (a - b) * -1;
  }
  return (a - b);
}

int stralh(char *w1, char *w2) {
  char *p1 = w1, *p2 = w2;
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

char *getword(FILE *in) {
  char *w = (char *)malloc(255 * sizeof(char)), *p = w;
  int c;
  char state = 0;
  while (1) {
    c = fgetc(in);
    if (c == EOF) {
      if (state == 0)
        return NULL;
      else {
        *p++ = '\0';
        return w;
      }
    }
    if (!state && (isalpha(c) || iscyr(c))) {
      state = 1;
    }
    if (state && (isalpha(c) || iscyr(c) || issp(c) || isalnum(c))) {
      if (isalpha(c))
        c = tolower(c);
      else if (iscyr(c))
        c = tolowcyr(c);
      else if (c == '-') {
        c = fgetc(in);
        if (isalpha(c) || iscyr(c)) {
          fseek(in, -1, SEEK_CUR);
          *p++ = '-';
        }
        c = '\0';
        c = fgetc(in);
        if (c == '\n' || c == '\r') {
          c = '\0';
          c = fgetc(in);
        }
        *p = c;
      }
      *p++ = c;
    } else if (state) {
      *p++ = '\0';
      return w;
    }
  }
  return NULL;
}

int strnalh(const char *w1, const char *w2, int n) {
  if (!n) return 0;
  if (strlen(w1) < n) {
    n = strlen(w1);
  }
  while (--n && *w1 == *w2) {
    w1++;
    w2++;
  }
  return *(unsigned char *)w1 - *(unsigned char *)w2;
}

struct node *tree_insert(NODE *tree, char *val) {
  if (tree == NULL) {
    tree = (struct node *)malloc(sizeof(struct node));
    tree->word = val;
    tree->left = tree->right = NULL;
    tree->count = 1;
    total++;
    return tree;
  }

  if (stralh(val, tree->word) < 0) {
    tree->left = tree_insert(tree->left, val);
    return tree;
  }
  if (stralh(val, tree->word) > 0) {
    tree->right = tree_insert(tree->right, val);
    return tree;
  }
  tree->count++;
  return tree;
}

void treeprint(NODE *tree, FILE *out) {
  if (tree != NULL) {
    treeprint(tree->left, out);
    fprintf(out, "%s - %d\n", tree->word, tree->count);
    treeprint(tree->right, out);
  }
}

// in 1251 && utf 8
void to_u8(char *in, char *out) {
  iconv_t i = iconv_open("UTF-8", "CP1251");
  size_t len = 256;
  iconv(i, &in, &len, &out, &len);
  iconv_close(i);
}
void to1251(char *in, char *out) {
  iconv_t i = iconv_open("CP1251", "UTF-8");
  size_t len = 256;
  iconv(i, &in, &len, &out, &len);
  iconv_close(i);
}

void tree_find(NODE *tree, char *val) {
  if (tree != NULL) {
    if (strnalh(val, tree->word, 5) == 0) {
      char buf[256];
      to_u8(tree->word, buf);

      printf("%s -> %d\n", buf, tree->count);
    }
  }
  if (tree->left != NULL) tree_find(tree->left, val);
  if (tree->right != NULL) tree_find(tree->right, val);
}

void tree_clear(NODE *tree) {
  if (tree != NULL) {
    if (tree->left != NULL) tree_clear(tree->left);
    if (tree->right != NULL) tree_clear(tree->right);
    free(tree);
  }
}

int main(int argc, char *argv[]) {
  FILE *in, *out;
  char *val;
  char cp[256], utf[256];
  if (argc < 2) {
    printf("Вы забыли указать список файлов!\n");
    exit(0);
  }
  while (--argc) {
    char outname[256];
    in = fopen(argv[argc], "r");
    if (in == NULL) {
      printf("file 1 don't open !\n");
    }
    strncpy(outname, argv[argc], 247);
    strncat(outname, "__.txt", 255);

    out = fopen(outname, "w");
    if (out == NULL) {
      printf("file don't open\n");
    }
    while ((val = getword(in)) != NULL) {
      root = tree_insert(root, val);
    }
    fprintf(out, "Total words: %d\n", total);
    treeprint(root, out);
    fclose(out);
    fclose(in);

    while (1) {
      char i;
      printf("search:");
      scanf("%s", utf);
      while (getchar() != '\n') continue;
      to1251(utf, cp);
      tree_find(root, cp);
      printf("go on? (y/n)\n");
      scanf("%c", &i);
      while (getchar() != '\n') continue;
      if (i == 'n') break;
    }
  }
  tree_clear(root);
  return 0;
}
