##Description
This is a simple mysql extension which provide a function `mysql_async_get_socket` to get a database connection's socket file descriptor, the file descriptor can be used in some stream based function such as event_set etc.

#Install
This is a php extension, you could install it just like any other ext.
```
/usr/local/php/bin/phpize
./configure --with-php-config=/usr/local/php/bin/php-config --enable-mysqlasync
make
```

#Usage
```php
<?php
$db = new mysqli('localhost', 'root', '');
$handle = mysql_async_get_socket($db);
$db->query("SELECT SLEEP(4)", MYSQLI_ASYNC);
$callback = function() use ($db) {
    $read[] = $error[] = $reject[] = $db;
    if (mysqli::poll($read, $error, $reject, 1)) {
        if (!empty($read)) {
            foreach ($read as $hd) {
                $res = $hd->reap_async_query();
                print_r($res->fetch_row());
            }
        }
        if (!empty($error)) {
            foreach ($error as $hd) {
                print_r($hd->error_list);
            }
        }
    }
};

$base = event_base_new();
$event = event_new();
event_set($event, $handle, EV_READ, $callback);
event_base_set($event, $base);
event_add($event);
event_base_loop($base);
```
