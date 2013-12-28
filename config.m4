PHP_ARG_ENABLE(mysqlasync, whether to enable mysqlasync support,
 [  --enable-mysqlasync           Enable mysqlasync support])

if test "$PHP_MYSQLASYNC" != "no"; then
  PHP_SUBST(MYSQLASYNC_SHARED_LIBADD)
  PHP_NEW_EXTENSION(mysqlasync, mysqlasync.c, $ext_shared)
fi
