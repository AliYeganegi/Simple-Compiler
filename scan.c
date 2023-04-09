#include "token.h"
#include "data.h"
#include "deceleration.h"

// Return the position of character c
static int chrpos(char *s, int c) {
  char *p;

  p = strchr(s, c);
  return (p ? p - s : -1);
}

// Get the next character from file
static int next(void) {
  int c;

  if (Putback) {
    c = Putback;
    Putback = 0;
    return c;
  }

  c = fgetc(Infile);
  if ('\n' == c)
    Line++;			
  return c;
}

// Put back an unwanted character
static void putback(int c) {
  Putback = c;
}

// character we dont need
static int skip(void) {
  int c;

  c = next();
  while (' ' == c || '\t' == c || '\n' == c || '\r' == c || '\f' == c) {
    c = next();
  }
  return (c);
}

// Scanan integer literal
static int scanint(int c) {
  int k, val = 0;

  while ((k = chrpos("0123456789", c)) >= 0) {
    val = val * 10 + k;
    c = next();
  }

  putback(c);
  return val;
}

// Scan and return the next token
int scan(struct token *t) {
  int c;

  // Skip " ", "\n", "\t", "\f", "\r"
  c = skip();

  // Which token?
  switch (c) {
  case EOF:
    return (0);
  case '+':
    t->token = T_PLUS;
    break;
  case '-':
    t->token = T_MINUS;
    break;
  case '*':
    t->token = T_STAR;
    break;
  case '/':
    t->token = T_SLASH;
    break;
  default:

    // Scan int value
    if (isdigit(c)) {
      t->intvalue = scanint(c);
      t->token = T_INTLIT;
      break;
    }

    printf("undefined character '%c' in line %d\n", c, Line);
    exit(1);
  }

  // a token was found
  return (1);
}