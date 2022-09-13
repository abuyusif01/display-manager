# Contributor: Abubakar Abubakar Yusif <abubakaryusuf951@gmail.com>
# Maintainer: Abubakar Abubakar Yusif <abubakaryusuf951@gmail.com>

pkgname=display-manager
pkgver=r44.ca3dc5b
pkgrel=1
pkgdesc="A light weight display manager for linux"
arch=('any')
url="https://github.com/abuyusif01/display-manager"
license=('GPL')
depends=('pam' 'ncurses' 'python3' 'make' 'gcc' 'git')
source=("display-manager::git+${url}.git")
md5sums=('SKIP')

package() {
    cd "${srcdir}/${pkgname}"
    install -Dm755 bin/release/dm "${pkgdir}/usr/bin/dm"
    install -Dm644 config/pam.d/display-manager "${pkgdir}/etc/pam.d/display-manager"
    install -Dm644 config/systemd/dm.service "${pkgdir}/usr/lib/systemd/system/dm.service"
}

build() {
    cd "${srcdir}/${pkgname}"
    make release # todo: fix make release to copy file to bin/release
}

pkgver() {
    cd "${srcdir}/${pkgname}"
    printf "r%s.%s" "$(git rev-list --count HEAD)" "$(git rev-parse --short HEAD)"

}
