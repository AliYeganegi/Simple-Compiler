#include "token.h"
#define extern_
#include "data.h"
#include "deceleration.h"
#include <errno.h>

static void init() {
  Line = 1;
  Putback = '\n';
}

// List of printable tokens
char *tokstr[] = { "+", "-", "*", "/", "intlit" };

// Scan all the tokens
static void scanfile() {
  struct token T;

  while (scan(&T)) {
    printf("Token %s", tokstr[T.token]);
    if (T.token == T_INTLIT)
      printf(", value %d", T.intvalue);
    printf("\n");
  }
}

void main(int argc, char *argv[]) {
  init();

  if ((Infile = fopen(argv[1], "r")) == NULL) {
    fprintf(stderr, "Unable to open %s: %s\n", argv[1], strerror(errno));
    exit(1);
  }

  scanfile();
  exit(0);
}