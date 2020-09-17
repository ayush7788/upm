#include <iostream>
#include <fstream>
using namespace std;

string os_name, package_manager;

//package manager functions
string install, rem, look, sync, upgrade, update;

void parse(string line){
	int count = 0;
	int suc = 0;
	string str, tok;
	for(int i = 0; i<line.length(); i++){
		tok += line[i];
		if(tok == "NAME="){
			tok = "";
			suc = 1;
		}
		else if(tok == "\""){
			if(suc == 1){
				if(count == 0){
					count = 1;
					tok = "";
				}
				else if(count == 1){
					count = 0;
					os_name = str;
					str = "";
					tok = "";
				}
			}
		}
		else if(count == 1){
			str += tok;
			tok = "";
		}
	}
}

void check_os(){
	string line;
	ifstream obj;
	obj.open("/etc/os-release");
	while(getline(obj, line)){
		parse(line);
	}
}

void set_manager(string distro){
	if(distro == "Arch Linux"){
		package_manager = "pacman";
		install = "-S";
		rem = "-R";
		look = "-Ss";
		sync = "-Syy";
		upgrade = "-Syu";
	}
	else if(distro == "Ubuntu"){
		package_manager = "apt";
		install = "install";
		rem = "remove";
		look = "search";
		rem = "remove";
		sync = "update";
		upgrade = "upgrade";
	}
}

void ins(string pkg){
	string cmd;
	cmd = package_manager + " " + install + " " + pkg;
	const char *c = cmd.c_str();
	system(c);
}

void remo(string pkg){
	string cmd;
	cmd = package_manager + " " + rem + " " + pkg;
	const char *c = cmd.c_str();
	system(c);
}

void look_for(string pkg){
	string cmd;
	cmd = package_manager + " " + look + " " + pkg;
	const char *c = cmd.c_str();
	system(c);
}

void upgrade_func(){
	string cmd;
	cmd = package_manager + " " + upgrade;
	const char *c = cmd.c_str();
	system(c);
}

void sync_func(){
	string cmd;
	cmd = package_manager + " " + sync;
	const char *c = cmd.c_str();
	system(c);
}

int main(int argc, char **argv){
	string arg = argv[1];
	check_os();
	set_manager(os_name);
	if(arg == "install"){
		ins(argv[2]);
	}
	else if(arg == "remove"){
		remo(argv[2]);
	}
	else if(arg == "look"){
		look_for(argv[2]);
	}
	else if(arg == "sync"){
		sync_func();
	}
	else if(arg == "upgrade"){
		upgrade_func();
	}
	else if(arg == "--version"){
		cout << "Universal Package Manger \"Wrapper\"\nver- 1.0\nMode: " << package_manager << "\nBuilt by Ayush Yadav\n";
	}
	return 0;
}