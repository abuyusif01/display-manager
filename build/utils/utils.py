import os


class Utils:
    def __init__(self):
        self.distro = get_distro()
        self.arch = get_arch()

    def install_packages(self, packages):
        if self.distro == "ubuntu" or command_exists("apt"):
            for package in packages:
                install_packages_debain(package)

        if self.distro == "arch" or command_exists("pacman"):
            for package in packages:
                install_packages_arch(package)

    def get_distro(self):
        return self.distro

    def get_arch(self):
        return self.arch


def command_exists(command):
    return os.system("command -v {} > /dev/null".format(command)) == 0


def install_packages_arch(name):
    print("Installing packages: {}".format(name))
    os.system("sudo pacman -S {}".format(name))


def install_packages_debain(name):
    print("Installing packages: {}".format(name))
    os.system("sudo apt-get install -y {}".format(name))


def get_distro():
    with open("/etc/os-release") as f:
        for line in f:
            if line.startswith("ID="):
                return line.split("=")[1].strip().lower()


def get_arch():
    return os.uname().machine


Utils = Utils()

arch_dependencies = open("../arch_dependencies.txt").read().splitlines()
deb_dependencies = open("../deb_dependencies.txt").read().splitlines()


def install_dependencies():
    if Utils.get_distro() == "arch" or command_exists("pacman"):
        Utils.install_packages(arch_dependencies)
    else:
        Utils.install_packages(deb_dependencies)


install_dependencies()
