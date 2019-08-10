#! /bin/sh

echo "buildconf: checking installation..."

stamp=$1

# Allow the autoconf executable to be overridden by $PHP_AUTOCONF.
if test -z "$PHP_AUTOCONF"; then
  PHP_AUTOCONF='autoconf'
fi

# autoconf 2.68 or newer
ac_version=`$PHP_AUTOCONF --version 2>/dev/null|head -n 1|sed -e 's/^[^0-9]*//' -e 's/[a-z]* *$//'`
if test -z "$ac_version"; then
echo "buildconf: autoconf not found." >&2
echo "           You need autoconf version 2.68 or newer installed" >&2
echo "           to build PHP from Git." >&2
exit 1
fi
IFS=.; set $ac_version; IFS=' '
if test "$1" = "2" -a "$2" -lt "68" || test "$1" -lt "2"; then
echo "buildconf: autoconf version $ac_version found." >&2
echo "           You need autoconf version 2.68 or newer installed" >&2
echo "           to build PHP from Git." >&2
exit 1
else
echo "buildconf: autoconf version $ac_version (ok)"
fi

test -n "$stamp" && touch $stamp

exit 0
