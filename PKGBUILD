# Contributor: Abubakar Abubakar Yusif <abubakaryusuf951@gmail.com>
# Maintainer: Abubakar Abubakar Yusif <abubakaryusuf951@gmail.com>

pkgname=dm
pkgver=r44.ca3dc5b
pkgrel=1
pkgdesc="A light weight display manager for linux"
arch=('any')
url="https://github.com/abuyusif01/display-manager"
license=('GPL')
depends=('pam' 'ncurses' 'python3' 'make' 'gcc' 'git')
source=("${pkgname}::git+${url}.git")
md5sums=('SKIP')

package() {
    cd "${srcdir}/${pkgname}"
    install -Dm755 bin/release/* "${pkgdir}/usr/bin/" # incase by any chance there are more than one file in the release folder
    install -Dm644 config/pam.d/* "${pkgdir}/etc/pam.d/"
    install -Dm644 config/systemd/* "${pkgdir}/usr/lib/systemd/system/"
}

build() {
    cd "${srcdir}/${pkgname}"
    make release
}

pkgver() {
    cd "${srcdir}/${pkgname}"
    printf "r%s.%s" "$(git rev-list --count HEAD)" "$(git rev-parse --short HEAD)"
}
