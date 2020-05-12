//Decryption method, Program the encryption and decryption table. Will test on toy messages. 
#include <vector>
#include <iostream>
#include <string>

void GenerateBoard(std::vector< std::vector<char> > &v, const std::vector<char> rule){
	for(int i = 0; i < rule.size(); i++){
		if (i ==0){
			v.push_back(rule);
		}
		else{
			std::vector<char> Temp;
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

std::vector<char> splitastring(std::string InputStr){
	std::vector <char> tempstr;
	for (auto i : InputStr){
		tempstr.push_back( (char) i);
	}
	return tempstr;
}

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

std::string Decode(std::string One_Time, std::string CyberText, 
			const std::vector< std::vector<char> > library, 
			const std::vector<char> standard){

	std::vector<char> One_Time_list = splitastring(One_Time);
	std::vector<char> CyberText_list = splitastring(CyberText);
	std::string decodeText = "";
	char element = ' ';
	for (int i = 0; i < One_Time_list.size(); i++){
		int temp_index = 0;
		for (auto ele : library[FindElement(One_Time_list[i])]){
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

int main(){

	std::vector< std::vector<char> > VECTOR;
	std::vector<char> num_char = {'A','B','C','D','E','F',
								  'G','H','I','J','K','L',
								  'M','N','O','P','Q','R',
								  'S','T','U','V','W','X',
								  'Y','Z','0','1','2','3',
								  '4','5','6','7','8','9'};
	GenerateBoard(VECTOR,num_char);
	int check_point_One_Time = 0;
	int check_point_cyber = 0;
	std::string One;
	std::string Cyber;
	while (true){
		std::cout << "Input the One-Time Pad -> ";
		std::cin >> One;
		std::cout << "Input the CyberText -> ";
		std::cin >> Cyber;
		for(auto i : One){
			if (((int) i >=48 && (int) i <= 57) || ((int) i >=65 && (int) i <= 90)){
				check_point_One_Time++;
			}
		}
		for(auto i : Cyber){
			if (((int) i >=48 && (int) i <= 57) || ((int) i >=65 && (int) i <= 90)){
				check_point_cyber++;
			}
		}
		if (check_point_cyber != Cyber.size() || check_point_One_Time != One.size()){
			One = "";
			Cyber = "";
			check_point_One_Time = 0;
			check_point_cyber = 0;
		}
		else{
			break;
		}
	}
	//std::string One = "W8JD7";
	//std::string Cyber = "3CUOL";
	std::string PlainText = Decode(One, Cyber, VECTOR, num_char);
	std::cout << PlainText << std::endl;
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


