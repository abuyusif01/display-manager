import sys
import os


"""
    Function to install packages on arch linux based distros    
"""


def install_packages_arch(name):
    print("Installing packages: {}".format(name))
    os.system("sudo pacman -S {}".format(name))


"""
    Function to install packages on debian based distros
"""


def install_packages_debain(name):
    print("Installing packages: {}".format(name))
    os.system("sudo apt-get install {}".format(name))


"""
    if get_distro() == "ubuntu": install dependencies for ubuntu
    if get_distro() == "arch": install dependencies for arch
"""


def get_distro():
    with open("/etc/os-release") as f:
        for line in f:
            if line.startswith("ID="):
                return line.split("=")[1].strip().lower()


"""
    if get_arch() == "x86_64": install dependencies for x86_64
    if get_arch() == "aarch64": install dependencies for aarch64
"""


def get_arch():
    return os.uname().machine


"""
    main() function
"""


def main():
    if len(sys.argv) < 2:
        print("Usage: build.py <path to build>")
        sys.exit(1)

    build_path = sys.argv[1]
    if not os.path.exists(build_path):
        print("Build path does not exist")
        sys.exit(1)

    if not os.path.isdir(build_path):
        print("Build path is not a directory")
        sys.exit(1)


# This is a common pattern in Python to check if the file is being run directly or imported
__name__ == "__main__" and main()
