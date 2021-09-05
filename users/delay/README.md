# @delay's userspace

## `COMPOSE`

Provides a generic composition implementation. Used to add support for accented
characters. Requires the host system to use the US layout with Mac variant, eg.

```sh
$ setxkbmap -layout us -variant mac
```

(or the default US layout on macOS.)
