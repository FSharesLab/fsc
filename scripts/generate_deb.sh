#! /bin/bash

PREFIX="usr"
SPREFIX=${PREFIX}
SUBPREFIX="opt/${PROJECT}/${VERSION_TAG}/${VERSION}"
SSUBPREFIX="opt\/${PROJECT}\/${VERSION_TAG}\/${VERSION}"
RELEASE="${VERSION_SUFFIX}"

# default release to "1" if there is no suffix
if [[ -z $RELEASE ]]; then
  RELEASE="1"
fi

NAME="${PROJECT}-${VERSION_TAG}-${VERSION_NO_SUFFIX}-${RELEASE}_amd64"

mkdir -p ${PROJECT}-${VERSION_TAG}/DEBIAN
chmod 0755 ${PROJECT}-${VERSION_TAG}/DEBIAN

echo "Package: ${PROJECT}-${VERSION_TAG}
Version: ${VERSION_NO_SUFFIX}-${RELEASE}
Section: devel
Priority: optional
Depends: libbz2-dev (>= 1.0), libssl-dev (>= 1.0), libgmp3-dev, build-essential, libicu-dev, zlib1g-dev, libtinfo5
Architecture: amd64
Homepage: ${URL}
Maintainer: ${EMAIL}
Description: ${DESC}" &> ${PROJECT}-${VERSION_TAG}/DEBIAN/control

export PREFIX
export SUBPREFIX
export SPREFIX
export SSUBPREFIX

bash generate_tarball.sh ${NAME}.tar.gz

tar -xvzf ${NAME}.tar.gz -C ${PROJECT}-${VERSION_TAG}
dpkg-deb --build ${PROJECT}-${VERSION_TAG}
BUILDSTATUS=$?
mv -f ${PROJECT}-${VERSION_TAG}.deb ${NAME}.deb
rm -r ${PROJECT}-${VERSION_TAG}

exit $BUILDSTATUS
