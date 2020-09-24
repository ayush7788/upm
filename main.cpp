#include <iostream>
#include <fstream>
using namespace std;

//package manager flags
string pkgmgr, ins, rem, look, update, sync;

//identify which user is running this
string user;

void parse(string line){
	int count = 0;
	int suc = 0;
    int pkger = 0;
    int inser = 0;
    int remer = 0;
    int syncer = 0;
    int upgrader = 0;
    int looker = 0;
	string str, tok;
	for(int i = 0; i<line.length(); i++){
		tok += line[i];
		if(tok == "PKGMGR="){
			tok = "";
            pkger = 1;
		}
        else if(tok == "INSTALL="){
            tok = "";
            inser = 1;
        }
        else if(tok == "REMOVE="){
            tok = "";
            remer = 1;
        }
        else if(tok == "SYNC="){
            tok = "";
            syncer = 1;
        }
        else if(tok == "UPDATE="){
            tok = "";
            upgrader = 1;
        }
        else if(tok == "SYNC="){
            tok = "";
            syncer = 1;
        }
		else if(tok == "\""){
			if(count == 0){
				count = 1;
				tok = "";
			}
			else if(count == 1){
				count = 0;
                if(pkger == 1){
                    pkgmgr = str;
                    pkger = 0;
                }
                else if(inser == 1){
                    ins = str;
                    inser = 0;
                }
                else if(remer == 1){
                    rem = str;
                    remer = 0;
                }
                else if(looker == 1){
                    look = str;
                    looker = 0;
                }
                else if(syncer == 1){
                    sync = str;
                    syncer = 0;
                }
                else if(upgrader == 1){
                    update = str;
                    upgrader = 0;
                }
				str = "";
				tok = "";
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
    string line;
    string cfg = "/usr/share/upm/config";
    cout << "Generating UPM config in - " << cfg << endl;
    if(system("pacman --version >>/dev/null 2>>/dev/null") == 0){
        pkgmgr = "pacman";
        ins = "-S";
        rem = "-R";
        look = "-Ss";
        update = "-Syu";
        sync = "-Sy";
        if(system("mkdir /usr/share/upm >>/dev/null 2>>/dev/null") == 0){
            obj.open(cfg);
            obj << "[UPM Config]\nPKGMGR=\"pacman\"\nINSTALL=\"-S\"\nREMOVE=\"-R\"\nLOOK=\"-Ss\"\nUPDATE=\"-Syu\"\nSYNC=\"-Sy\"\n";
            obj.close();
        }
        else{
            obj.open(cfg);
            obj << "[UPM Config]\nPKGMGR=\"pacman\"\nINSTALL=\"-S\"\nREMOVE=\"-R\"\nLOOK=\"-Ss\"\nUPDATE=\"-Syu\"\nSYNC=\"-Sy\"\n";
            obj.close(); 
        }
    }
    else if(system("apt list --installed >>/dev/null 2>>/dev/null") == 0){
        pkgmgr = "apt";
        ins = "install";
        rem = "remove";
        look = "search";
        update = "update";
        sync = "update";
        if(system("mkdir /usr/share/upm >>/dev/null 2>>/dev/null") == 0){
            obj.open(cfg);
            obj << "[UPM Config]\nPKGMGR=\"apt\"\nINSTALL=\"install\"\nREMOVE=\"remove\"\nLOOK=\"search\"\nUPDATE=\"upgrade\"\nSYNC=\"update\"\n";
            obj.close();
        }
        else{
            obj.open(cfg);
            obj << "[UPM Config]\nPKGMGR=\"apt\"\nINSTALL=\"install\"\nREMOVE=\"remove\"\nLOOK=\"search\"\nUPDATE=\"upgrade\"\nSYNC=\"update\"\n";
            obj.close(); 
        }
    }
    else if(system("dnf info >>/dev/null 2>>/dev/null") == 0){
        ins = "install";
        rem = "remove";
        sync = "check-update";
        update = "update";
        look = "search";
        if(system("mkdir /usr/share/upm >>/dev/null 2>>/dev/null") == 0){
            obj.open(cfg);
            obj << "[UPM Config]\nPKGMGR=\"dnf\"\nINSTALL=\"install\"\nREMOVE=\"remove\"\nLOOK=\"search\"\nUPDATE=\"update\"\nSYNC=\"check-update\"\n";
            obj.close();
        }
        else{
            obj.open(cfg);
            obj << "[UPM Config]\nPKGMGR=\"dnf\"\nINSTALL=\"install\"\nREMOVE=\"remove\"\nLOOK=\"search\"\nUPDATE=\"update\"\nSYNC=\"check-update\"\n";
            obj.close(); 
        }
    }
    else{
        cout << "Unknown package manager!\n";
        obj.open(cfg);
        obj << "[UPM Config]\nPKGMGR=\"unknown\"\nINSTALL=\"unknown\"\nREMOVE=\"unknown\"\nLOOK=\"unknown\"\nUPDATE=\"unknown\"\nSYNC=\"unknown\"\n";
        pkgmgr = "unknown";
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

void exec_flags(string flags){
    string cmd;
	cmd = pkgmgr + " " + flags;
	const char *c = cmd.c_str();
	system(c);
}

int main(int argc, char **argv){
    user = getenv("USER");
    ifstream obj;
    string line;
    string cfg = "/usr/share/upm/config";
    obj.open(cfg);
    if(!obj){
        if(user == "root"){
            check_pkgmgr();
        }
        else{
            cout << "You are running the program without config file!\nplease run \"upm --configure\" as root\n";
        }
    }
    else if(obj){
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
        else if(arg == "--configure"){
            if(user == "root"){
                check_pkgmgr();
            }
            else{
                cout << "you must be root to perform this action!\n";
            }
        }
	    else{
            for(int i = 1;i < argc; i++){
                arguments += argv[i];
                arguments += " ";
            }
		    exec_flags(arguments);
	    }
    }
    return 0;
}