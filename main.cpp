/*
Andy Chiang
2/20/2023
Database Management Systems
Project Assignment 1
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>

#include <sys/stat.h> 

#include "table.h"

using namespace std;

void parseInput(const string& input, vector<string>& commands);  //parse commands with delimiter
void parseCommands(vector<string>& commands, vector<table>& tables); //execute commands and modify tables
string getName(string line); //get name
string getTblName(string line); //get table name 
string getData(string line); //get data 


int main(int argc, char* argv[]){

	string input;
	vector<string> commands;
	vector<table> tables;

	
	while (input != ".EXIT"){ //main loop
		cout << "> ";
		getline(cin, input);

		parseInput(input, commands);
		parseCommands(commands, tables);
        } 
	return 0;
    }

//getData function, grabs data return line
string getData(string line){
	auto it = find(line.begin(), line.end(), '(');
	line = string(it, line.end());
	line = line.substr(1, line.size() - 2);
	replace(line.begin(), line.end(), ',', '|');

	return line;
}

//getName functionk, gets name
string getName(string line){
	stringstream ss(line);
	string token;
	while (getline(ss, token, ' ')){
    }
	return token;
}

//getTblName, gets table name
string getTblName(string line){
	stringstream ss(line);
	string token;
	int i = 0;
	while (getline(ss, token, ' ') && i < 2){
		i++;
	}
	return token;
}

//parseInput Function, gets token from data and pushes back
void parseInput(const string& input, vector<string>& commands){
	stringstream ss(input);
	string token;
	while (getline(ss, token, ';')){
		commands.push_back(token);
	}
}

//parseCommands function, handles the database systems
void parseCommands(vector<string>& commands, vector<table>& tables){
	string currDB;


	for (auto i : commands){
		if (i.find("CREATE DATABASE") != -1){
			
			string dbName = getName(i); //grabs database name
			
			const int direrr = system(("mkdir " + dbName).c_str()); //makes directory
			if (direrr == 0)
				cout << "Database " << dbName << " created." << endl;
			else //checks if successfully
				cout << "!Failed to create database " << dbName << " because it already exists." << endl;
                }
		    else if (i.find("DROP DATABASE") != -1){
			    string dbName = getName(i);
			    const int direrr = system(("rmdir " + dbName).c_str()); //remove directory
			    if (direrr == 0)
				    cout << "Database " << dbName << " deleted." << endl; //checks successful, else failed
			    else
				    cout << "!Failed to delete " << dbName << " because it does not exist." << endl;
                }
		    else if (i.find("USE") != -1){
			    string dbName = getName(i);
			    const int direrr = system(("cd " + dbName).c_str()); //changes current database
			    currDB = dbName;
			    if (direrr == 0)
				    cout << "Using datbase " << dbName << "." << endl;
			    else
				    cout << "!Failed to use " << dbName << " because it does not exist." << endl;
                }
            else if (i.find("CREATE TABLE") != -1){
			    string tbName = getTblName(i); //Get the table name
			    string data = getData(i); //parse for the data passed in
			    table tb(tbName, currDB, data);
				string dbName = getName(i);
				string folder_name = "db_1";
				int result = mkdir(folder_name.c_str());


			    auto it = find(tables.begin(), tables.end(), tb); //checks table exists
			    if (it != tables.end()){
				    cout << "!Failed to create " << tbName << " because it already exists." << endl;
			    }
			    else{
					string file_path = folder_name + "/" + tbName;
					ofstream myfile(file_path.c_str());
					if (myfile.is_open()){
						myfile << data << endl;
						tables.push_back(tb);
						myfile.close();
					}
				
					/*
				    tables.push_back(tb);
					ofstream tb("/Users/andychiang/Desktop/PA1_Database/db_1/tbl_1");
					tb << data << "\n";	
				    cout << "Table " << tbName << " created." << endl;
					*/
			    }	
		    }
			else if (i.find("DROP TABLE") != -1){
    			string tbName = getTblName(i);
    			table tb(tbName, currDB, "");
    			string folder_name = "db_1";
    			string file_path = folder_name + "/" + tbName;

    			auto it = find(tables.begin(), tables.end(), tb);
    			if (it == tables.end()) {
       				cout << "!Failed to drop " << tbName << " because it does not exist." << endl;
    			}
    			else {
        			tables.erase(it);
        			remove(file_path.c_str());
        			cout << "Table " << tbName << " dropped." << endl;
    			}
			}
		    else if (i.find("SELECT * FROM") != -1){
			    string tbName = getName(i);
			    table tb(tbName, currDB);
			    auto it = find(tables.begin(), tables.end(), tb);
			

			    size_t index = it - tables.begin(); //finds table index if it exists
			    if (it != tables.end()){
				
				    cout << tables[index].getData() << endl; //prints data from table
			    }
			    else{
				    cout << "!Failed to query " << tbName << " because it does not exist." << endl;
			    }
		    }
		    else if (i.find("ALTER TABLE") != -1){ //modifying table
			    string tbName = getTblName(i);
			    table tb(tbName, currDB);
			    auto it = find(tables.begin(), tables.end(), tb);
			    size_t index = it - tables.begin();
			    if (it != tables.end()){
				    tables[index].add(i);
				    cout << "Table " << tbName << " modified." << endl; //checks if successful

					string folder_name = "db_1";
        			string file_path = folder_name + "/" + tbName;
        			ofstream myfile(file_path.c_str());
        			if (myfile.is_open()){
           			myfile << tables[index].getData() << endl; // update file with new data
           			myfile.close();
        			}
			    }
			    else{
				    cout << "!Failed to add to " << tbName << " because it does not exist." << endl; //else fails
			    }
		    }
	    }

	commands.clear();
}
