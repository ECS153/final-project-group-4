//Decryption method, Program the encryption and decryption table. Will test on toy messages. 
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <stdio.h>
#include "QrCode.hpp"  //package from https://github.com/nayuki/QR-Code-generator
#include "QrCode.cpp"
#include <fstream>
#include <cstdlib> //https://blog.csdn.net/xiangxianghehe/article/details/77351721
//https://github.com/sylnsfar/qrcode/blob/master/README-cn.md
//for storing the QR code as .png
//generate a standard library for the universal tabling 
void GenerateBoard(std::vector< std::vector<char> > &v, const std::vector<char> rule){ //generate the one time pad table
	for(int i = 0; i < rule.size(); i++){
		if (i ==0){
			v.push_back(rule);
		}
		else{
			std::vector<char> Temp; //push in as two part, from start to end, from 0 to start, since it may not always start at A
			for (int j = i; j < rule.size(); j++){
				Temp.push_back(rule[j]);
			}
			for (int j = 0; j < i; j++){
				Temp.push_back(rule[j]);
			}
			v.push_back(Temp);
		}
	}
}

//process the inputing string
std::vector<char> splitastring(std::string InputStr){
	std::vector <char> tempstr;
	for (auto i : InputStr){
		tempstr.push_back( (char) i);
	}
	return tempstr;
}
//get the element index in a list about ascii
int FindElement(char Element, const std::vector<char> library){
	for (int i = 0; i < library.size();i++){
		if (library[i] == Element){
			return i;
		}
	}
}

//function of decoding
std::string Decode(std::string One_Time, std::string CyberText, 
			const std::vector< std::vector<char> > library, 
			const std::vector<char> standard){

	std::vector<char> One_Time_list = splitastring(One_Time);//split out the input
	std::vector<char> CyberText_list = splitastring(CyberText);
	std::string decodeText = "";
	char element = ' ';
	for (int i = 0; i < CyberText_list.size(); i++){ //one time pad can be longer than the cybertext
		int temp_index = 0;
		for (auto ele : library[FindElement(One_Time_list[i],standard)]){//loop the vector to find the cyber text in the standard table
			if (ele != CyberText[i]){
				temp_index++;
			}
			else{
				element = standard[temp_index];	
			}		
		}
		decodeText += element;
	}
	return decodeText;

}
//function for encoding
std::string Encode(std::string One_Time, std::string CyberText, 
			const std::vector< std::vector<char> > library, 
			const std::vector<char> standard){

	std::vector<char> One_Time_list = splitastring(One_Time); //split out the input
	std::vector<char> CyberText_list = splitastring(CyberText);
	std::string EncodedText = "";

	//get the value from X and Y axis from the standard table
	for (int each_index = 0; each_index < CyberText_list.size(); each_index++){
		EncodedText += library[FindElement(One_Time_list[each_index],standard)][FindElement(CyberText_list[each_index],standard)];
	}
	return EncodedText;

}

int main(){

	std::vector< std::vector<char> > VECTOR;
	/*
	std::vector<char> num_char = {'\0','!','"','#',
								  '$','%','&','\'','(',')',
        						  '*','+',',','-','.','/',
        						  '0','1','2','3','4','5',
        						  '6','7','8','9',':',';',
        						  '<','=','>','?','@','A',
        						  'B','C','D','E','F','G',
        						  'H','I','J','K','L','M',
        						  'N','O','P','Q','R','S',
        						  'T','U','V','W','X','Y',
        						  'Z','[','\\',']','^','_','`',
        						  'a','b','c','d','e','f',
								  'g','h','i','j','k','l',
								  'm','n','o','p','q','r',
								  's','t','u','v','w','x',
								  'y','z','{','|','}','~'};

	*/
	
	int check_point_One_Time = 0;
	int check_point_cyber = 0;
	std::string One;
	std::string Cyber;
	std::string Options;
	std::vector<char> num_char = {};
	std::string Temp_elements;
	bool checking = false;
	//One = "W8JD7SDJFHSK";
	//Cyber = "HELLO";
	//Options = "a";
	//Cyber = "3CUOL";
	
	while (true){ //confirm the input is valid
		//take the table elements
		std::cout << "Enter the elements in the one time pad table elements (the element in the table cannot be repeat, no space for the element, if enter nothing, will use ascii number elements as standard table; For example: ABCDabcd1234)\n-> ";
		//std::cin >> Temp_elements;
		std::getline (std::cin,Temp_elements);
		//choose the mode
		std::cout << "Enter 'a' for 'Encrypted' or 'b' for 'decrypted' -> ";
		std::cin >> Options;
		//input for the one time pad key
		std::cout << "Input the One-Time Pad -> ";
		std::cin >> One;
		//input the text for encryption or decryption
		std::cout << "Input the CyberText for decrypted or Text to Encrypted (use '_' for space)-> ";
		std::cin >> Cyber;
		if (Temp_elements.size() == 0){ //standard table
			num_char = {'!','"','#',
						'$','%','&','\'','(',')',
						'*','+',',','-','.','/',
						'0','1','2','3','4','5',
						'6','7','8','9',':',';',
						'<','=','>','?','@','A',
						'B','C','D','E','F','G',
						'H','I','J','K','L','M',
						'N','O','P','Q','R','S',
						'T','U','V','W','X','Y',
						'Z','[','\\',']','^','_','`',
						'a','b','c','d','e','f',
						'g','h','i','j','k','l',
						'm','n','o','p','q','r',
						's','t','u','v','w','x',
						'y','z','{','|','}','~'};
			std::cout << "\nUsing ascii table elements into One Time Pad table\n"<<std::endl;
		}
		else{ //check if all elements in the input for table element is repreated
			for (auto i : Temp_elements){
				if (std::find(num_char.begin(), num_char.end(), i) != num_char.end()){
					checking = true;
				}
				num_char.push_back(i);
			}
		}
		for(auto i : One){//check the capitalization of the input
			if (((int) i >=32 && (int) i <= 126) || ((int) i== 0)){
				check_point_One_Time++;
			}
			if (std::find(num_char.begin(), num_char.end(), i) == num_char.end()){ //if not in one time pad table elements
				check_point_One_Time--;
			}
		}
		for(auto i : Cyber){ //same as above
			if (((int) i >=32 && (int) i <= 126) || ((int) i== 0)){
				check_point_cyber++;
			}
			if (std::find(num_char.begin(), num_char.end(), i) == num_char.end()){
				check_point_cyber--;
			}
		}
		//need to be number or full cap, one time pad can be longer than text, but not shorter, there are only two options for modes
		if (check_point_cyber != Cyber.size() || check_point_One_Time != One.size() || (Options != "a" && Options != "b") || (check_point_One_Time < check_point_cyber)){
			One = "";
			Cyber = "";
			Options = "";
			check_point_One_Time = 0;
			check_point_cyber = 0;
			Temp_elements = "";
			num_char = {};
		}
		else if(checking){ //if repeated elements, restart over
			One = "";
			Cyber = "";
			Options = "";
			check_point_One_Time = 0;
			check_point_cyber = 0;
			Temp_elements = "";
			num_char = {};
		}
		else{
			
			break;
		}
	}
	//write the information into the files
	std::ofstream myfile;
	myfile.open ("tableelement.txt"); //put down the table elements
	if (Temp_elements.size() != 0){
		myfile << Temp_elements;
	}
	else{
		std::string inputproduct;
		for (auto i : num_char){
			inputproduct += i;
		}
		myfile << inputproduct;
	}
	myfile.close();
	std::ofstream myfile1;
	myfile1.open ("inputOneTimePadkey.txt");
	myfile1 << One;
	myfile1.close();
	std::ofstream myfile2;
	myfile2.open ("InputMessage.txt");
	myfile2 << Cyber;
	myfile2.close();

	GenerateBoard(VECTOR,num_char);//board generation
	if (Options == "a"){ //different mode, encryted, and decryted
		std::string PlainText = Encode(One, Cyber, VECTOR, num_char);//enryption
		std::cout << PlainText << std::endl;
		const char* s = PlainText.c_str();//https://stackoverflow.com/questions/5638831/c-char-array
		using namespace qrcodegen;
		QrCode qr0 = QrCode::encodeText(s, QrCode::Ecc::LOW); //start the qr code generation for the html version
		std::string svg = qr0.toSvgString(100);
		std::ofstream myfile3;
		myfile3.open ("outputQRcode.html");
		myfile3 << svg;
		myfile3.close();
		std::ofstream myfile4;
		myfile4.open ("outputMessage.txt"); //save the output message
		myfile4 << PlainText;
		myfile4.close();
		std::string temp_str = "myqr "+ PlainText +" -v 10 -l H"; //this is for the png version
		const char* commandline = temp_str.c_str();
		std::system(commandline);//https://github.com/sylnsfar/qrcode/blob/master/README-cn.md
		try{//https://www.geeksforgeeks.org/exception-handling-c/
			std::system("google-chrome outputQRcode.html"); //try to use the html version
			//https://stackoverflow.com/questions/27760105/how-can-i-run-a-html-file-from-terminal/55531753
		}
		catch(...){
			std::system("xdg-open qrcode.png"); //open the file directly
		}	
	}
	else{//for decryption
		std::string PlainText = Decode(One, Cyber, VECTOR, num_char);
		std::cout << PlainText << std::endl;
		std::cout << PlainText << std::endl;
		const char* s = PlainText.c_str();//https://stackoverflow.com/questions/5638831/c-char-array
		using namespace qrcodegen;
		QrCode qr0 = QrCode::encodeText(s, QrCode::Ecc::LOW); //similar to above, about the html version qr code
		std::string svg = qr0.toSvgString(100);
		std::ofstream myfile3;
		myfile3.open ("outputQRcode.html");
		myfile3 << svg;
		myfile3.close();
		std::ofstream myfile4;
		myfile4.open ("outputMessage.txt");//save the output message
		myfile3 << PlainText;
		myfile4.close();
		std::string temp_str = "myqr "+ PlainText +" -v 10 -l H"; //save the png version qr code
		const char* commandline = temp_str.c_str();
		std::system(commandline);//https://github.com/sylnsfar/qrcode/blob/master/README-cn.md
		try{//https://www.geeksforgeeks.org/exception-handling-c/
			std::system("google-chrome outputQRcode.html"); //try to use the html version
			//https://stackoverflow.com/questions/27760105/how-can-i-run-a-html-file-from-terminal/55531753
		}
		catch(...){
			std::system("xdg-open qrcode.png"); //open the file directly
		}
	}
	return 0;
}


