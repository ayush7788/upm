# upm
An universal package manager wrapper!
One of the biggest headaches when disto hopping is learning, the commands to install or remove a program!
You can easily search for those commands on the internet, but to help you a bit Universal Package Manager "Wrapper" is here!
It can be installed on any linux distro using systemd as init system.
It has simple command-line options, to install and remove packages, which are all same across all the distros that are supported till now.
So, you don't need to memorize every package manager commands to do somehing, learn once and all your distros can do packager manager stuff with same commands!

# What actually is UPM
UPM isn't some different package manager! Its just simply a wrapper for pre-built package managers!

# Commanline options
UPM supports these commands till now-
1. install (to install a given package)
2. remove (to uninstall a package manager)
3. sync (to sync the repo)
4. upgrade (to perform full system upgrade)
5. look (search for a package in repo)

# Supported Distributions
At this time only two distros are supported!
1. Arch Linux (pacman)
2. Ubuntu (apt)

# Installation
To install upm, just clone the repo and run install.sh.

If you want to install using sch(available at https://github.com/ayush7788/sch), a codefile is included for help!

# Usage
When you will install "upm", it will read a file "/etc/os-release" to identify the distribution.
1. To install a package
> upm install "pkg-name"
2. To uninstall a package
> upm remove "pkg-name"
3. To sync the repositories
> upm sync
4. To do full system upgrade 
> upm upgrade
5. To search for a package in repo
> upm look "pkg-name"

# TO-do list
- [x] Do first release
- [x] Support Ubuntu
- [x] Support Arch Linux
- [ ] Support Debian
- [ ] Support Void Linux
