#!/bin/bash

function prepare() { # no args, Just default shit
    # install dependencies
    pwd # print working directory

    # make sure the user have python 3.6 or higher installed
    if ! command -v python3 &>/dev/null; then
        echo "python3 could not be found"
        exit
    else
        echo "[+] python3 found"
        echo "[+] Installing dependecy packages"
        cd build/utils
        python3 utils.py # install dependencies
        cd ../..         # go back to the root directory
    fi

    # copy from config to /etc/pam.d
    echo "[+] Copying pam.d files"
    sudo cp config/pam.d/* /etc/pam.d/

    # copy to /etc/systemd/system
    echo "[+] Copying systemd files"
    sudo cp config/systemd/* /etc/systemd/system/

    # if distro == ubuntu
    if [ -f /etc/os-release ]; then
        . /etc/os-release
        if [ "$ID" == "ubuntu" ]; then
            echo "[+] Github environment detected"
            # disable display-manager.service
            echo "[+] Disabling display-manager.service"
            sudo systemctl disable display-manager.service 2>/dev/null
            echo "[+] Enabling dm.service"
            sudo systemctl enable dm.service 2>/dev/null

        elif [[ "$ID" != "ubuntu" ]]; then
            echo "[+] Normal environment detected"
            echo "[+] Would you like to enable dm at startup"
            read -p "[+] (y/n): " choice
            if [[ $choice == "y" ]]; then
                # enable dm.service
                echo "[+] Enabling dm.service"
                sudo systemctl enable dm.service 2>/dev/null
            fi
            echo "[+] Not enabling dm at startup"
        fi
    fi

    # ask the user if they wanna disable and enale dm

}

function compile() {
    # compile the project
    echo "[+] Compiling the project"
    make clean
    make debug
    cp main bin/debug/dm_debug
    rm -rf main
    make release
    cp main bin/release/dm
    rm -rf main
}

function install() {
    # install the project
    echo "[+] Installing the project"
    cd bin/release
    sudo cp dm /usr/bin
    cd ../..
}

prepare # call the prepare function
compile # call the compile function
