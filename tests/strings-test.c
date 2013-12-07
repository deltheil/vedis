#include <stdlib.h>
#include <string.h>
#include <vedis.h>

#include "ct/ct.h"

#define EXEC_CMD(vds_CMD) \
  do { \
    rc = vedis_exec(store, (vds_CMD), -1); \
    assert(rc == VEDIS_OK); \
    rc = vedis_exec_result(store, &res); \
    assert(rc == VEDIS_OK); \
  } while (0)

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
