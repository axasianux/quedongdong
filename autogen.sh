#!/bin/sh

if [ x$1 == x"rpm" ]; then
  echo "rpm start"
  make dist
  rm -f /root/rpmbuild/SOURCES/aux-desktop-1.0.tar.gz
  mv ./aux-desktop-1.0.tar.gz  /root/rpmbuild/SOURCES/
  rm -f /root/rpmbuild/RPMS/i586/aux-desktop-1.0-*
  rm -f /root/rpmbuild/SRPMS/aux-desktop-1.0-* 
  rpmbuild -ba aux-desktop.spec
  cp /root/rpmbuild/RPMS/i586/aux-desktop-1.0-* ./
  cp /root/rpmbuild/SRPMS/aux-desktop-1.0-*  ./ 
fi

if [ ! $1 ]; then
    echo "auto make start"
libtoolize --copy --ltdl --force
aclocal
automake --add-missing
autoconf
./configure --prefix=/usr
make
fi

#autoreconf --force --install

