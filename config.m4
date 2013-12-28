PHP_ARG_ENABLE(mysql_async, whether to enable mysql_async support,
 [  --enable-mysql_async           Enable mysql_async support])

if test "$PHP_MYSQL_ASYNC" != "no"; then
  PHP_SUBST(MYSQL_ASYNC_SHARED_LIBADD)
  PHP_NEW_EXTENSION(mysql_async, mysql_async.c, $ext_shared)
fi
