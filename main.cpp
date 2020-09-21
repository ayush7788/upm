#include <iostream>
#include <fstream>
using namespace std;
string pkgmgr, ins, rem, look, update, sync;
string homedir;

void parse(string line){
	int count = 0;
	int suc = 0;
    int pkger = 0;
    int inser = 0;
    int remer = 0;
    int syncer=0;
    int upgrader=0;
    int looker = 0;
	string str, tok;
	for(int i = 0; i<line.length(); i++){
		tok += line[i];
		if(tok == "PKGMGR="){
			tok = "";
			suc = 1;
            pkger = 1;
		}
        else if(tok == "INSTALL="){
            tok = "";
			suc = 1;
            inser = 0;
        }
        else if(tok == "REMOVE="){
            tok = "";
			suc = 1;
            remer = 0;
        }
        else if(tok == "SYNC="){
            tok = "";
			suc = 1;
            syncer = 0;
        }
        else if(tok == "UPDATE="){
            tok = "";
			suc = 1;
            upgrader = 0;
        }
        else if(tok == "SYNC="){
            tok = "";
			suc = 1;
            syncer = 0;
        }
		else if(tok == "\""){
			if(suc == 1){
				if(count == 0){
					count = 1;
					tok = "";
				}
				else if(count == 1){
					count = 0;
                    if(pkger == 1){
                        pkgmgr = str;
                    }
                    else if(inser == 1){
                        ins = str;
                    }
                    else if(remer == 1){
                        rem = str;
                    }
                    else if(looker == 1){
                        look = str;
                    }
                    else if(syncer == 1){
                        sync = str;
                    }
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

void check_pkgmgr(){
    ofstream obj;
    ifstream check;
    string line;
    string cfg = homedir + "/.config/upm/config";
    check.open(cfg);
    if(!check){
        if(system("pacman --version >>/dev/null 2>>/dev/null") == 0){
            pkgmgr = "pacman";
            ins = "-S";
            rem = "-R";
            look = "-Ss";
            update = "-Syu";
            sync = "-Sy";
            if(system("mkdir ~/.config/upm >>/dev/null 2>>/dev/null") == 0){
                obj.open(cfg);
                cout << "creating file\n";
                obj << "[UPM Config]\nPKGMGR=\"pacman\"\nINSTALL=\"-S\"\nREMOVE=\"-R\"\nLOOK=\"-Ss\"\nUPDATE=\"-Syu\"\nSYNC=\"-Sy\"\n";
                obj.close();
            }
            else{
                ifstream exist;
                exist.open(cfg);
                if(!exist){
                    obj.open(cfg);
                    obj << "pacman";
                    obj.close(); 
                }
                exist.close();
            }
        }
        else if(system("apt list --installed >>/dev/null 2>>/dev/null") == 0){
            pkgmgr = "apt";
            ins = "install";
            rem = "remove";
            look = "search";
            update = "update";
            sync = "update";
            if(system("mkdir ~/.config/upm >>/dev/null 2>>/dev/null") == 0){
                obj.open(cfg);
                obj << "apt";
                obj.close();
            }
            else{
                ifstream exist;
                exist.open(cfg);
                if(!exist){
                    obj.open(cfg);
                    obj << "apt";
                    obj.close(); 
                }
                exist.close();
            }
        }
        else if(system("dnf info >>/dev/null 2>>/dev/null") == 0){
            pkgmgr = "dnf";
            ins = "install";
            rem = "remove";
            sync = "check-update";
            update = "update";
            look = "search";
            if(system("mkdir ~/.config/upm >>/dev/null 2>>/dev/null") == 0){
                obj.open(cfg);
                obj << "dnf";
                obj.close();
            }
            else{
                ifstream exist;
                exist.open(cfg);
                if(!exist){
                    obj.open(cfg);
                    obj << "dnf";
                    obj.close(); 
                }
                exist.close();
            }
        }
        else{
            cout << "Unknown package manager!\n";
            pkgmgr = "unknown";
        }
        check.close();
    }
    else{
        getline(check, pkgmgr);
        if(pkgmgr == "pacman"){
            ins = "-S";
            rem = "-R";
            look = "-Ss";
            update = "-Syu";
            sync = "-Sy";
        }
        else if(pkgmgr == "apt"){
            ins = "install";
            rem = "remove";
            look = "search";
            update = "update";
            sync = "update";
        }
        else if(pkgmgr == "dnf"){
            ins = "install";
            rem = "remove";
            sync = "check-update";
            update = "update";
            look = "search";
        }
        else{
            cout << "unsupported package manager defined in ~/.config/upm/config file\n";
        }
    }
}

void install(string pkg){
	string cmd;
	cmd = pkgmgr + " " + ins + " " + pkg;
	const char *c = cmd.c_str();
	system(c);
}

void remo(string pkg){
	string cmd;
	cmd = pkgmgr + " " + rem + " " + pkg;
	const char *c = cmd.c_str();
	system(c);
}

void look_for(string pkg){
	string cmd;
	cmd = pkgmgr + " " + look + " " + pkg;
	const char *c = cmd.c_str();
	system(c);
}

void update_func(){
	string cmd;
	cmd = pkgmgr + " " + update;
	const char *c = cmd.c_str();
	system(c);
}

void sync_func(){
	string cmd;
	cmd = pkgmgr + " " + sync;
	const char *c = cmd.c_str();
	system(c);
}

int main(int argc, char **argv){
    homedir = getenv("HOME");
    ifstream obj;
    string line;
    obj.open(homedir + "/.config/upm/config");
    if(!obj){
        check_pkgmgr();
    }
    else{
        while(getline(obj, line)){
            parse(line);
        }
    }
    obj.close();
    string arguments;
    if(argc > 1){
        string arg = argv[1];
        for(int i = 2;i < argc; i++){
            arguments += argv[i];
            arguments += " ";
        }
        if(arg == "install"){
		    install(arguments);
	    }
	    else if(arg == "remove"){
		    remo(arguments);
	    }
	    else if(arg == "look"){
		    look_for(arguments);
	    }
	    else if(arg == "sync"){
		    sync_func();
	    }
	    else if(arg == "update"){
		    update_func();
	    }
	    else if(arg == "--version"){
		    cout << "Universal Package Manger \"Wrapper\"\nver- 2.1\nMode: " << pkgmgr << "\nBuilt by Ayush Yadav\n";
	    }
	    else{
		    cout << "upm:" << " invalid option:" << "\'" << arg << "\'" << endl;
	    }
    }
    return 0;
}