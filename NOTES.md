## Data Structures Backends

### Overview

Strings are backed by an internal K/V store `vedis_kv_engine`, e.g the `SET` and
`GET` commands use resp.:

* `VedisStoreValue` -> `vedis_context_kv_store`
* `vedisFetchValue` -> `vedis_context_kv_fetch_callback`

> Note: the `EXISTS` command also uses the `vedis_kv_engine` via
`vedis_context_kv_fetch_callback`!

Lists, hashes and sets are backed by an internal hash table `struct vedis_table`.
There is one `vedis_table` per Redis key. Each table carries its own type via
its `iTableType` field:

```C
#define VEDIS_TABLE_HASH 1
#define VEDIS_TABLE_SET  2
#define VEDIS_TABLE_LIST 3
```

Zsets are not yet implemented.

### Limitations

#### `EXISTS` only checks strings

At the time of writing `EXISTS` only scans the `vedis_kv_engine`. If there is no
entry within the K/V engine, it should check if there is a given `vedis_table`
for the given key.

So far `EXISTS` is broken:

```
vedis> HSET test scm git
true
vedis> EXISTS test
false
```

#### No wrong type detection

For all non-string commands Vedis first performs a lookup to retrieve the
`vedis_table` associated with the input key. This lookup is done via the
`vedisFetchTable` function:

```C
vedis_table * vedisFetchTable(vedis *pDb,vedis_value *pName,int create_new,int iType);
```

If `create_new = 1` Vedis automatically creates a new table for the given type.

The problem is for write operations Vedis *does* create a new table even though
there is one that already exists for a different data structure, e.g:

```
vedis> HSET test scm git
true
vedis> LPUSH test xyz
1
```

`LPUSH` should not work here since `test` already holds a hash.
