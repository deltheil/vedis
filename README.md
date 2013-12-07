# vedis

[Vedis](http://vedis.symisc.net/) is an embedded datastore C library similar in
concept to Redis but without the networking layer developed by
[Symisc Systems](http://www.symisc.net/).

## Goals

At the time of writing the official Vedis version includes around
[70 commands](http://vedis.symisc.net/commands.html). Some of them have no
equivalent in Redis, e.g [SPEEK](http://vedis.symisc.net/cmd/speek.html).

On the other hand Vedis is extensible by means of the
[vedis_register_command](http://vedis.symisc.net/c_api/vedis_register_command.html)
function which makes possible to:

* add new, user-defined, commands,
* modify built-in commands.

> Note: it's interesting to notice that built-in Vedis commands are precisely
registered via `vedis_register_command` internally.

That being said, it is (of course) not possible with `vedis_register_command` to
access the internal, private data structures such as `struct vedis_table` that
implements the hash table used for Redis Hashes or Sets.

AFAIK I would say `vedis_register_command` is handy to create specific extensions
a la [Redis Lua scripting](http://redis.io/commands/eval). But probably not enough
to extend Vedis with missing, official Redis commands.

So the main goal of this fork is to add support from other Redis commands.

Secondary goals are to provide:

* some `Makefile`-s to ease the build of a Vedis static library - especially
for mobile platforms (iOS, Android),
* some basic unit tests to cover the new commands additions.

## License

Vedis is released under the Sleepycat License: see `LICENSE`.
