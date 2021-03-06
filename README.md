# upm
An universal package manager wrapper!
One of the biggest headaches when disto hopping is learning, the commands to install or remove a program!
You can easily search for those commands on the internet, but to help you a bit Universal Package Manager "Wrapper" is here!
It can be installed on any linux distro using supported package managers.
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

# Supported Package Managers
At this time only three package managers are supported!
1. pacman
2. apt
3. dnf

# Installation
To install upm, just clone the repo and run install.sh as root.

On a typical linux install, you should do 
```
sudo sh install.sh
```
In terminal in the directory where you cloned the repo.

If you want to install using sch(available at https://github.com/ayush7788/sch), a codefile is included for help!

If you are running UPM for first time, make sure you are running it as root! So that it can generate some config files.

# Usage
When you will run "upm", it will identify your package manager and generate a config in /usr/share/upm/config
1. To install a package
```
upm install "pkg-name"
```
2. To uninstall a package
```
upm remove "pkg-name"
```
3. To sync the repositories
```
upm sync
```
4. To do full system upgrade 
```
upm upgrade
```
5. To search for a package in repo
```
upm look "pkg-name"
```
6. Pass any non-defined flag to package manager
```
upm "any other param"
```
If sometime you played up with config a bit more and now UPM cannot identify your package manager, you can always run(as root)
```
upm --configure
```
to re-generate config file

# TO-do list
- [x] Do first release
- [x] Support Ubuntu
- [x] Support Arch Linux
- [x] Change Identification system of package manager
- [x] Support pacman
- [x] Support apt
- [x] support dnf
- [x] Make better flags support
- [x] Do second release
- [ ] Add more default functions
- [ ] Make native packages for various distros
- [ ] Play Minecraft ^_^
