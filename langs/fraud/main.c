#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include "types.h"
#include "values.h"
#include "runtime.h"

FILE* in;
FILE* out;
void (*error_handler)();

void print_result(val_t);
void print_char(val_char_t);

void error_exit()
{
  printf("err\n");
  exit(1);
}

void raise_error()
{
  return error_handler();
}

int main(int argc, char** argv)
{
  in = stdin;
  out = stdout;
  error_handler = &error_exit;
  
  val_t result;

  result = entry();
  print_result(result);
  if (val_typeof(result) != T_VOID)
    putchar('\n');

  return 0;
}

void print_result(val_t x)
{
  switch (val_typeof(x)) {
  case T_INT:
    printf("%" PRId64, val_unwrap_int(x));
    break;
  case T_BOOL:    
    printf(val_unwrap_bool(x) ? "#t" : "#f");
    break;
  case T_CHAR:
    print_char(val_unwrap_char(x));    
    break;
  case T_EOF:
    printf("#<eof>");
    break;
  case T_VOID:
    break;    
  case T_INVALID:
  default:
    printf("internal error");
  }
}
