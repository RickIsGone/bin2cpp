# Mantainer: Riccardo Tedeschi <https://github.com/rickisgone>

pkgname=bin2cpp
pkgver=1.0.2
pkgrel=1
pkgdesc="A cli tool to embed binary files into C++ headers"
arch=('i686' 'pentium4' 'x86_64' 'arm' 'armv7h' 'armv6h' 'aarch64' 'riscv64')
url="https://github.com/rickisgone/bin2cpp"
license=('MIT')
makedepends=('cmake')
source=("${pkgname}-${pkgver}.tar.gz::https://github.com/rickisgone/bin2cpp/archive/v${pkgver}.tar.gz")
md5sums=('SKIP')

build() {
  cd "${pkgname}-${pkgver}"
  cmake . -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=Release
  make
}

package() {
  cd "${pkgname}-${pkgver}"
  install -Dm755 bin2cpp "$pkgdir/usr/bin/bin2cpp"
  install -Dm644 LICENSE "$pkgdir/usr/share/licenses/${pkgname}/LICENSE"
}