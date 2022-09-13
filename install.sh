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

    # disable display-manager.service
    echo "[+] Disabling display-manager.service"
    sudo systemctl disable display-manager.service

    # enable dm.service
    echo "[+] Enabling dm.service"
    sudo systemctl enable dm.service

}

function compile() {
    # compile the project
    echo "[+] Compiling the project"
    make
    cp main bin/debug/dm_debug
    cp main bin/release/dm
    rm main
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
