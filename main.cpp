#include <iostream> 
#include <fstream> 
#include <cstdio> 
#include <string.h> 
#include <math.h> 
#include <cstdlib> 
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "Winmm.lib")
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
struct playerInfo{
	 char fName[65]="";
	 char lName[65]="";
	 char uName[65]="";
	 char age[65]="";
	 char gender[65]="";
}p1info;
struct matches{
	char result[65]="";
	char date[65]="";
	char time[65]="";
	int winRatio = 0;
}matHistory[10];
struct numCard{
	const char type[10] = "Number";
	char color[10] = "";
	int value;
}numDeck[76];
struct actionCard{
	const char type[10] = "Action";
	char color[10] = "";
	char value[10]="";
}actDeck[20];
struct drawCard{
	const char type[10] = "Draw";
	char color[10] = "";
	int value;
}drawDeck[12];
struct playerDeck{
	char type[10] = "";
	char color[10] = "";
	int value;
}p1deck[7], compDeck[7];
void mainScreen(int*);
void startGame(int* );
void showStats(char file[50]);
void editInfo(char file[50]);
void launchApp(int*);
bool newPlayer(char*);
bool oldPlayer(char*);
void loadPlayer();
void setDifficulty(int*);
void giveCards(numCard(&numDeck)[76], actionCard(&actDeck)[20], drawCard(&drawDeck)[12], playerDeck(&p1deck)[7], playerDeck(&compDeck)[7]);
int main(int argc, char** argv) {
	bool token = true;
	bool valid = false;
	int choice;
	int decision;
	int difficulty;
	char newFileName[50]="";
	char oldFileName[50]="";
	char userFile[50]="";
	do{
		launchApp(&decision);
		switch(decision){
			case 1:
				system("pause");
				valid = newPlayer(&newFileName[50]);
				strncpy(userFile, newFileName, strlen(newFileName));
				break;
			case 2:
				system("pause");
				valid = oldPlayer(&oldFileName[50]);
				strncpy(userFile, oldFileName, strlen(oldFileName));
				break;
			default:
				cout << "\n\nThe input you have entered is invalid!\n\n";
				system("pause");
				system("cls");
		}
	}while(valid == false);
	do{
		system("cls");
		mainScreen(&choice);
		//PlaySound("C:\\Users\\OWNER\\Desktop\\DEV C++ Files\\Uno Game\\bgm.wav", GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC | SND_LOOP);
		switch(choice){
			case 1:
				if (difficulty < 1 || difficulty > 3){
					setDifficulty(&difficulty);
				}
				startGame(difficulty);
				break;
			case 2:
				showStats(userFile);
				break;
			case 3:
				editInfo(userFile);
				break;
			case 4:
				setDifficulty(&difficulty);
				break;
			case 5:
				token = false;
				break;
			default:
				cout << "\n\nThe input you have entered is invalid please choose an input between 1-4!\n\n";
				system("pause");
				system("cls");
		}
	}while (token == true);
	
	return 0;
}
void launchApp(int *decision){
	system("cls");
	cout << "\n\n\t\t\t   Let's Play Uno!\n\n";
	cout << "\t****************************************************\n";
	cout << "\t***\t**      **   ***    **    **********     ***\n";
	cout << "\t***\t**      **   ** *   **    **      **     ***\n";
	cout << "\t***\t**      **   **  *  **    **      **     ***\n";
	cout << "\t***\t**      **   **   * **    **      **     ***\n";
	cout << "\t***\t**      **   **    ***    **      **     ***\n";
	cout << "\t***\t  ******     **     **    **********     ***\n";
	cout << "\t****************************************************\n\n\n";
	cout << "\t\t[1] New Player\t\t[2] Old User";
	cout << "\n\n\tYour Choice: ";
	cin >> *decision;
	cin.ignore();
}
void mainScreen(int *choice){
	cout << "\n\n\t\t\t   Let's Play Uno!\n\n";
	cout << "\t****************************************************\n";
	cout << "\t***\t**      **   ***    **    **********     ***\n";
	cout << "\t***\t**      **   ** *   **    **      **     ***\n";
	cout << "\t***\t**      **   **  *  **    **      **     ***\n";
	cout << "\t***\t**      **   **   * **    **      **     ***\n";
	cout << "\t***\t**      **   **    ***    **      **     ***\n";
	cout << "\t***\t  ******     **     **    **********     ***\n";
	cout << "\t****************************************************\n\n\n";
	cout << "[1] Start Game\t\t[2] Show Player Stats\t\t[5] Exit\n";
	cout << "[3] Edit Player Info\t[4] Set Difficulty\n";
	cout << "Your Choice: ";
	cin >> *choice;
	cin.ignore();
}
bool newPlayer(char *newFileName){
	bool valid = false;
	bool exist = true;
	char info[100] = "--------------------------- Player's Information ----------------------------------------\n\n\n\n\n\n\n";
	char stat[100] = "------------------------------- Statistics ----------------------------------------------\n";
	char ans[2]="";
	do{
		system("cls");
		cout << "Welcome, new player!\nPlease input the name for your file\n(No longer than 40 characters and use underscore to indicate spaces. Enter 'B' to go back): ";
		cin >> newFileName;
		if (strcmp(newFileName, "B") == 0){
			return false;
		}
		if (strlen(newFileName) > 40){
			cout << "\n\nPlease choose a name not longer than 40 characters!\n";
			system("pause");
			newPlayer(&newFileName[50]);
			break;
		}
		cout << "\nThe file name you have entered is: [" << newFileName << "]. Are you sure with this? [Y/N]: ";
		cin >> ans;
		if(strcmp(ans, "Y") == 0 || strcmp(ans, "y") == 0){
			strcat(newFileName, ".txt");
			ifstream file(newFileName);
			if(file.is_open()){
				exist = true;
				valid = false;
				file.close();
				cout << "\n\nERROR: The file name you have entered already exists! Please choose a new one.\n";
				system("pause");
				break;
			}else{
				ofstream file(newFileName);
				file << info << stat;
				file.close();
				exist = false;
				valid = true;
			}
		}
	}while(valid == false && exist == true);
	return true;
}
bool oldPlayer(char*oldFileName){
	bool valid = false;
	bool exist = false;
	char ans[2]="";
	do{
		system("cls");
		cout << "Welcome! Please enter the user file name to load (Not including the .txt file extension. Enter 'B' to go back): ";
		cin.getline(oldFileName, sizeof(oldFileName));
		if (strcmp(oldFileName, "B") == 0){
			return false;
		}
		strcat(oldFileName, ".txt");
		ifstream file(oldFileName);
		if(file.is_open()){
			exist = true;
			valid = true;
			file.close();
		}else{
			cout << "\n\nERROR: The file name you have entered does not exist! Please enter a new one.\n";
			system("pause");
			exist = false;
			valid = false;
		}
	}while(valid == false && exist == false);
	return true;	
}
void setDifficulty(int* difficulty){
	system("cls");
	char confirm[2]="";
	if (difficulty == 0){
		cout << "Oooof! Looks like you haven't set a difficulty for your game yet. Please choose a difficulty for your game.\n";
		system("pause");
		system("cls");
	}
	do{
		cout << "Choose your desired difficulty:\n";
		cout << "\t[1] Easy\n\t[2] Average\n\t[3] Unfair\n";
		cout << "Your Choice: ";
		cin >> *difficulty;
		cout << "\nAre you sure about this? [Y/N]: ";
		cin >> confirm;
	}while(strcmp(confirm, "Y") != 0);
}
void startGame(int difficulty){
	system("cls");
	for (int i = 0; i <= 76; i++){
		int colorCnt = 0;
		if (colorCnt){
			
		}
	}
	
}
void giveCards(numCard(&numDeck)[76], actionCard(&actDeck)[20], drawCard(&drawDeck)[12], playerDeck(&p1deck)[7], playerDeck(&compDeck)[7]){
	
}
void showStats(char file[50]){
	system("cls");
	ifstream readFile;
	cout << "Opening User Info File... Please Wait...\n";
	readFile.open(file);
	if (!(readFile.is_open())){
		cout << "\nUnfortunately, there's an error while opening the file...";
		system("pause");
	}else{
		cout << "\nFile Opened Succesfully!\n";
		system("pause");
		system("cls");
		string line;
		do{
			getline(readFile, line);
			cout << line << "\n";
		}while(!readFile.eof());
		system("pause");
	}
	readFile.close();
}
void editInfo(char file[50]){
	char confirm[2]="";
	int tru;
	do{
		system("cls");
		cout << "Please enter your first name: ";
		cin.getline(p1info.fName, sizeof(p1info.fName));
		cout << "Please enter your last name: ";
		cin.getline(p1info.lName, sizeof(p1info.lName));
		cout << "Please enter your username: ";
		cin.getline(p1info.uName, sizeof(p1info.uName));
		cout << "Please enter your age: ";
		cin.getline(p1info.age, sizeof(p1info.age));
		cout << "Please enter your gender: ";
		cin.getline(p1info.gender, sizeof(p1info.gender));
		system("cls");
		cout << "Here are the details you entered:\n";
		cout << "First Name: " << p1info.fName << "\n";
		cout << "Last Name: " << p1info.lName << "\n";
		cout << "Username: " << p1info.uName << "\n";
		cout << "Age: " << p1info.age << "\n";
		cout << "Gender: " << p1info.gender << "\n";
		cout << "Do you want to save these changes? [Y/N]: ";
		cin >> confirm;
		tru = strcmp(confirm, "Y");
		cin.ignore(); 
	}while (tru != 0);
	
	fstream useFile;
	cout << "Saving User Info File... Please Wait...\n";
	useFile.open(file, ios::in | ios::out | ios::ate);
	if (!useFile.is_open()){
		cout << "\nUnfortunately, there's an error while opening the file...";
		system("pause");
	}else{
		useFile.seekp(0, ios::beg);
		string line;
		string fname = "  \tFirst name: ";
		string lname = "\tLast name: ";
		string uname = "\tUsername: ";
		string age = "\tAge: ";
		string gender = "\tGender: ";
		int loc, count=1;
		do{
			loc = useFile.tellp();
			getline(useFile, line);
				if (count == 3){
					for (int i = strlen(p1info.fName); i != sizeof(p1info.fName)-1; i++){
						strcat(p1info.fName, " ");
					}
					useFile.seekp(loc);
					useFile << fname << p1info.fName;	
					break;
				}
				count++;
		} while (!useFile.eof());
		do{
			loc = useFile.tellp();
			getline(useFile, line);
				if (count == 4){
					for (int i = strlen(p1info.lName); i != sizeof(p1info.lName)-1; i++){
						strcat(p1info.lName, " ");
					}
					useFile.seekp(loc);
					useFile << lname << p1info.lName;	
					break;
				}
				count++;
		} while (!useFile.eof());
		do{
			loc = useFile.tellp();
			getline(useFile, line);
				if (count == 5){
					for (int i = strlen(p1info.uName); i != sizeof(p1info.uName)-1; i++){
						strcat(p1info.uName, " ");
					}
					useFile.seekp(loc);
					useFile << uname << p1info.uName;	
					break;
				}
				count++;
		} while (!useFile.eof());
		do{
			loc = useFile.tellp();
			getline(useFile, line);
				if (count == 6){
					for (int i = strlen(p1info.age); i != sizeof(p1info.age)-1; i++){
						strcat(p1info.age, " ");
					}
					useFile.seekp(loc);
					useFile << age << p1info.age;	
					break;
				}
				count++;
		} while (!useFile.eof());
		do{
			loc = useFile.tellp();
			getline(useFile, line);
				if (count == 7){
					for (int i = strlen(p1info.gender); i != sizeof(p1info.gender)-1; i++){
						strcat(p1info.gender, " ");
					}
					useFile.seekp(loc);
					useFile << gender << p1info.gender;	
					break;
				}
				count++;
		} while (!useFile.eof());
		cout << "\nChanges Saved Succesfully!\n";
		system("pause");
		system("cls");
	}
	useFile.close();
}
