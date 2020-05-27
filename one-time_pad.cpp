//Decryption method, Program the encryption and decryption table. Will test on toy messages. 
#include <vector>
#include <iostream>
#include <string>

//generate a standard library for the universal tabling 
void GenerateBoard(std::vector< std::vector<char> > &v, const std::vector<char> rule){
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
//get the element index in a list [A to Z and 0 to 9] with binary search
int FindElement(char Element){
	double ascii_num = (double) Element;
	int char_beg = 65;
	int char_end = 90;
	int int_beg = 48;
	int int_end = 57;
	double Balence_char = (char_end-char_beg)/2;
	double Balence_int = (int_end-int_beg)/2;
	bool check = true;
	if (ascii_num <= char_end && ascii_num >= char_beg){
		while(Balence_char != ascii_num){
			if (Balence_char > ascii_num){
				char_end = Balence_char;
			}
			else{
				char_beg = Balence_char;
			}
			Balence_char = (char_end - char_beg)/2 + char_beg;
			Balence_char = (int) Balence_char;
		}
	}
	else{
		check = false;
		while(Balence_int != ascii_num){
			if (Balence_int > ascii_num){
				int_end = Balence_int;
			}
			else{
				int_beg = Balence_int;
			}
			Balence_int = (int_end - int_beg)/2 + int_beg;
			Balence_int = (int) Balence_int;
		}
	}

	if (check){
		return Balence_char-65;	
	}
	return Balence_int-48+26;
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
		for (auto ele : library[FindElement(One_Time_list[i])]){//loop the vector to find the cyber text in the standard table
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
		EncodedText += library[FindElement(One_Time_list[each_index])][FindElement(CyberText_list[each_index])];
	}
	return EncodedText;

}

int main(){

	std::vector< std::vector<char> > VECTOR;
	std::vector<char> num_char = {'A','B','C','D','E','F',
								  'G','H','I','J','K','L',
								  'M','N','O','P','Q','R',
								  'S','T','U','V','W','X',
								  'Y','Z','0','1','2','3',
								  '4','5','6','7','8','9',
								  'a','b','c','d','e','f',
								  'g','h','i','j','k','l',
								  'm','n','o','p','q','r',
								  's','t','u','v','w','x',
								  'y','z',' ','!','"','#',
								  '$','%','&','\'','(',')',
        						  '*','+','-','.','/',':',
        						  ';','<','=','>','?','@',
        						  '[','\\',']','^','_','`',
        						  '{','|','}','~','\0'};
	GenerateBoard(VECTOR,num_char);
	int check_point_One_Time = 0;
	int check_point_cyber = 0;
	std::string One;
	std::string Cyber;
	std::string Options;
	//One = "W8JD7SDJFHSK";
	//Cyber = "HELLO";
	//Options = "a";
	//Cyber = "3CUOL";
	
	while (true){ //confirm the input is valid
		std::cout << "Enter 'a' for 'Encrypted' or 'b' for 'decrypted' -> ";
		std::cin >> Options;
		std::cout << "Input the One-Time Pad -> ";
		std::cin >> One;
		std::cout << "Input the CyberText for decrypted or Text to Encrypted -> ";
		std::cin >> Cyber;
		for(auto i : One){//check the capitalization of the input
			if (((int) i >=32 && (int) i <= 126) || ((int) i== 0)){
				check_point_One_Time++;
			}
		}
		for(auto i : Cyber){
			if (((int) i >=32 && (int) i <= 126) || ((int) i== 0)){
				check_point_cyber++;
			}
		}
		//need to be number or full cap, one time pad can be longer than text, but not shorter, there are only two options for modes
		if (check_point_cyber != Cyber.size() || check_point_One_Time != One.size() || (Options != "a" && Options != "b") || (check_point_One_Time < check_point_cyber)){
			One = "";
			Cyber = "";
			Options = "";
			check_point_One_Time = 0;
			check_point_cyber = 0;
		}
		else{
			break;
		}
	}
	
	if (Options == "a"){ //different mode, encryted, and decryted
		std::string PlainText = Encode(One, Cyber, VECTOR, num_char);
		std::cout << PlainText << std::endl;
	}
	else{
		std::string PlainText = Decode(One, Cyber, VECTOR, num_char);
		std::cout << PlainText << std::endl;
	}
	/*
	for (int each_element = 0; each_element < VECTOR.size(); each_element++){
		std::string Text;
		for(int i = 0; i < VECTOR.size(); i++){
			Text.push_back(VECTOR[each_element][i]);
		}
		std::cout << Text << std::endl;
	}*/
	return 0;
}


