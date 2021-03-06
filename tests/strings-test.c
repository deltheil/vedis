#include <stdlib.h>
#include <string.h>
#include <vedis.h>

#include "ct/ct.h"
#include "utils.h"

void
ctteststrings(void)
{
  int rc;
  const char *str;
  vedis *store = NULL;
  vedis_value *res = NULL;

  rc = vedis_open(&store, NULL /* in memory */);
  assert(rc == VEDIS_OK);

  EXEC_CMD("GET misc");
  assert(vedis_value_is_null(res));

  EXEC_CMD("SET misc smthg");
  assert(vedis_value_is_bool(res));
  assert(vedis_value_to_bool(res));

  EXEC_CMD("GET misc");
  assert(vedis_value_is_string(res));
  assert(str = vedis_value_to_string(res, NULL));
  assert(!strcmp(str, "smthg"));

  vedis_close(store);
}
