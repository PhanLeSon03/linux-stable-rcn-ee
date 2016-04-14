#!/bin/bash
CHROOT_DIR=/tmp/arm-chroot
VERSION=jessie
CHROOT_ARCH=armhf
MIRROR=http://httpredir.debian.org/debian
GUEST_DEPENDENCIES="build-essential git sudo lzop"
DEBOOT="1.0.80"

function run_build {
	cd ${CHROOT_DIR}/${TRAVIS_BUILD_DIR}
	make bb.org_defconfig
	make -s -j4 CROSS_COMPILE="ccache arm-linux-gnueabihf-"
}

function run_package {
	make KBUILD_DEBARCH=armhf KDEB_SOURCENAME=linux KDEB_CHANGELOG_DIST=unstable
}

function setup_arm_chroot {
	wget -c https://rcn-ee.net/mirror/debootstrap/debootstrap_${DEBOOT}_all.deb
	if [ -f debootstrap_${DEBOOT}_all.deb ] ; then
		sudo dpkg -i debootstrap_${DEBOOT}_all.deb
		rm -rf debootstrap_${DEBOOT}_all.deb
	fi
	sudo mkdir ${CHROOT_DIR}
	sudo debootstrap --foreign --no-check-gpg --include=fakeroot,build-essential \
		--arch=${CHROOT_ARCH} ${VERSION} ${CHROOT_DIR} ${MIRROR}
	sudo cp /usr/bin/qemu-arm-static ${CHROOT_DIR}/usr/bin/
	sudo chroot ${CHROOT_DIR} ./debootstrap/debootstrap --second-stage
	sudo sbuild-createchroot --arch=${CHROOT_ARCH} --foreign --setup-only \
	        ${VERSION} ${CHROOT_DIR} ${MIRROR}

	echo "export ARCH=${ARCH}" > envvars.sh
	echo "export TRAVIS_BUILD_DIR=${TRAVIS_BUILD_DIR}" >> envvars.sh
	chmod a+x envvars.sh

	sudo chroot ${CHROOT_DIR} apt-get update
	sudo chroot ${CHROOT_DIR} apt-get --allow-unauthenticated install \
		-qq -y ${GUEST_DEPENDENCIES}
	sudo mkdir -p ${CHROOT_DIR}/${TRAVIS_BUILD_DIR}
	sudo rsync -a ${TRAVIS_BUILD_DIR}/ ${CHROOT_DIR}/${TRAVIS_BUILD_DIR}/

	sudo touch ${CHROOT_DIR}/.chroot_is_done
}

if [ -e "/.chroot_is_done" ]; then
	. ./envvars.sh
	run_package
else
	echo "Setting up chrooted ARM environment"
	setup_arm_chroot
	run_build
	sudo chroot ${CHROOT_DIR} bash -c "cd ${TRAVIS_BUILD_DIR} && bash -ex build_deb_in_arm_chroot.sh"
fi
