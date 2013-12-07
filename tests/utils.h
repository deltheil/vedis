#ifndef _VEDIS_TEST_UTILS
#define _VEDIS_TEST_UTILS

#define EXEC_CMD(vds_CMD) \
  do { \
    rc = vedis_exec(store, (vds_CMD), -1); \
    assert(rc == VEDIS_OK); \
    rc = vedis_exec_result(store, &res); \
    assert(rc == VEDIS_OK); \
  } while (0)

#endif
