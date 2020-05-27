#include <iostream>
#include <vector>
#include <bitset>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <ctime>
#include <cmath>
#include <array>
#include <cstdio>
unsigned long long int generate_the_public_key(int mode){ //mode for 1024 or 2048
//std::string generate_the_public_key(int mode){ //mode for 1024 or 2048
	unsigned long long int time = 0;
	//std::ofstream myfile;
	unsigned long long int result = 0;
	//myfile.open("Key_N_inital.txt");
	std::srand (std::time(0));
	unsigned long long int range = mode;
	while( time < range){
		result += rand();
		time += 1;
	}
	//myfile << result;
  	//myfile.close();
  	return (unsigned long long int)result;
}

unsigned long long int all_prime_num (unsigned long long int N_key){
	unsigned long long all_prime = 0;
	for( unsigned long long int i = 2; i < N_key; i++){
		if(N_key % i != 0){
			all_prime+=1;
		}
	}
	return all_prime;
}

unsigned long long int get_the_e(unsigned long long int N_size, unsigned long long int N){
	std::vector<unsigned long long int> e_list = {};
	//std::cout<<"here0"<<std::endl;
	for(unsigned long long int i = 200; i < 600; i++){
		if ((N_size % i != 0) && (N % i != 0) ){
			e_list.push_back(i);
		}

	}
	std::srand (std::time(0));
	//std::cout<<"here1"<<std::endl;
	//std::cout<<e_list.size()<<std::endl;
	//std::cout<<N_size<<std::endl;
	int temp_index = 0;
	do{
		temp_index = rand();
	}while(temp_index > e_list.size()-1);
	//std::cout<<"here2"<<std::endl;
	return e_list[temp_index];
}

unsigned long long int get_the_d(unsigned long long int e_value, unsigned long long int N_size){
	unsigned long long int k = 1;
	std::vector<unsigned long long int> d_value = {};
	//std::cout<<"here3"<<std::endl;
	while(d_value.size() < 100){
		if ((k*N_size+1) % e_value == 0){
			d_value.push_back((unsigned long long int)((k*N_size+1) / e_value));
		}
		k += 1;
	}
	//std::cout<<"here4"<<std::endl;
	std::srand (std::time(0));
	int temp_index = 0;
	do{
		temp_index = rand() % 100;
	}while(temp_index > d_value.size()-1);
	//std::cout<<"here4"<<std::endl;
	return d_value[temp_index];
}

unsigned long long int EncrypteMessage(unsigned long long int E, unsigned long long int N, char M){//http://www.cplusplus.com/forum/general/100351/
	return (unsigned long long int)(pow(int(M),E)) % N;
}

char DecrypteMessage(unsigned long long int D, unsigned long long int N, unsigned long long int M){
	return char((unsigned long long int)pow(M,D) % N);
}

void powerfunction(unsigned long long int power, unsigned long long int Mes){
	std::cout<<"pass";

	std::vector<int> temp_arr={};
	int i = 0;
	while(i < 2048){
		temp_arr.push_back(0);
		i += 1;
	}
	std::string temp_str = "" + Mes;
	std::vector<int> mes_vector = {};
	for (int i = 1; i <= temp_str.size(); i++){
		temp_arr[0-i] = (int)temp_str[0-i];
		mes_vector.push_back((int)temp_str[i]);
	}
	
	unsigned long long int time = 0;
	unsigned long long int indexing = 0;
	unsigned long long int pass_up = 0;
	while(time < power){
		for(int j = 1; j <= mes_vector.size();j++ ){
			for (int i = 1; i <= temp_arr.size(); i++){
				int result = temp_arr[0-i] * mes_vector[0-j];
				pass_up = result / (int)pow(10,i);
				int reminder = result % (int)pow(10,i);
				temp_arr[0-i] = reminder + pass_up;

			}
		}
		time += 1;
	}
	std::ofstream myfile;
	myfile.open("powerfunction.txt");
	for (int i = 0 ; i < temp_arr.size() ; i++){
		myfile << temp_arr[i];
	}
	
  	myfile.close();

}

std::string readinfile(std::string file_name){ https://www.w3schools.com/cpp/cpp_files.asp
	std::ifstream myReadFile;
	myReadFile.open(file_name);
	char output(1);
	std::string temp_string = "";
	std::string temp_str = "";
	while (getline(myReadFile,temp_str)) {
		temp_string += temp_str;	
	}
	myReadFile.close();
	return temp_string;
}

void actionE(){
	std::string EFile_Name;
	std::string PK_name;
	std::cout << "Enter message file name that want to Encrypte >>> ";
	std::cin >> EFile_Name;
	std::cout << "Enter Public key file name >>> ";
	std::cin >> PK_name;
	auto message = readinfile(EFile_Name);
	//std::cout<<message<<std::endl;
	auto key = readinfile(PK_name);
	std::string key_e = "";
	std::string key_n = "";
	bool check = false;
	for (auto i: key){
		if (i == ','){
			check = true;
			continue;
		}
		if (!check){
			key_e += i;
		}
		else{
			key_n += i;
		}
	}
	std::string::size_type sz;
	unsigned long long int e_value = std::stoull (key_e); //test case: test_for_encryted.txt
	unsigned long long int n_value = std::stoull (key_n); // Encrypte_key.txt
	//std::cout<<key_e<<" "<<key_n<<std::endl;
	std::vector<unsigned long long int>product_list = {};
	for (auto i : message){
		product_list.push_back(EncrypteMessage(e_value,n_value,char(i)));
	}
	//std::cout << product_list[0]<<std::endl;
	std::ofstream myfile;
	myfile.open("Encryted_message.txt");
	for (int i = 0 ; i < product_list.size() ; i++){
		if (i < product_list.size()-1){
			//std::cout<<"break here"<< std::endl;
			std::string temp_arr = std::to_string(product_list[i]) + ",";
			myfile << temp_arr;
		}
		myfile << product_list[i];
	}
	
  	myfile.close();
  	std::cout<<"File Stored" << std::endl;
}

void actionD(){
	std::string DFile_Name;
	std::string PrK_name;
	std::cout << "Enter message file name that want to Decrypte >>> ";
	std::cin >> DFile_Name;
	std::cout << "Enter Private key file name >>> ";
	std::cin >> PrK_name;
	auto message = readinfile(DFile_Name);
	auto key = readinfile(PrK_name);
	std::string key_d = "";
	std::string key_n = "";
	bool check = false;
	for (auto i: key){
		if (i == ','){
			check = true;
			continue;
		}
		if (!check){
			key_d += i;
		}
		else{
			key_n += i;
		}
	}
	std::vector<unsigned long long int> message_list = {};
	std::string temp_list = "";
	for (auto i: message){
		if (i == ','){
			message_list.push_back(std::stoull(temp_list));
			temp_list = "";
		}
		else{
			temp_list += i;
		}
	}
	std::string::size_type sz;
	unsigned long long int d_value = std::stoull (key_d);
	unsigned long long int n_value = std::stoull (key_n);
	std::string product_list = "";
	for (auto i : message_list){
		product_list += DecrypteMessage(d_value,n_value,i);
	}
	std::cout << product_list<<std::endl;
	std::ofstream myfile;
	myfile.open("Decryted_message.txt");
	myfile << product_list;
	myfile.close();
  	std::cout<<"File Stored" << std::endl;
}

void actionI(){
	int style;
	std::cout << "Enter an int (32 Max) for key N length >>> ";
	std::cin >> style;
	unsigned long long int temp = generate_the_public_key(style);
	//std::cout<<"pass here1"<<std::endl;
	unsigned long long int prime_list = all_prime_num(temp);
	//std::cout<<"pass here2"<<std::endl;
	auto num_e = get_the_e(prime_list, temp);
	//std::cout<<"pass here3"<<std::endl;
	auto num_d = get_the_d(num_e,prime_list);
	//std::cout<<"pass here4"<<std::endl;
	std::ofstream myfile;
	myfile.open("Encrypte_key.txt");
	std::string temp_str = std::to_string(num_e) + "," + std::to_string(temp);
	myfile << temp_str;
	myfile.close();
	std::ofstream myfile2;
	myfile2.open("Decrypte_key.txt");
	std::string temp_str2 = std::to_string(num_d) + "," + std::to_string(temp);
	myfile2 << temp_str2;
	myfile2.close();
  	std::cout<<"Files Stored" << std::endl;
}


int main(){
	std::string action;
	unsigned long long int A = 454;
	unsigned long long int B = 90;
	powerfunction(A,B);
	std::cout << "Enter 'e' for Encrypte or 'd' for Decryte or 'i' for initial >>> ";
	std::cin >> action;
	if (action == "e"){
		actionE();
	}
	else if(action == "d"){
		actionD();
	}
	else if (action == "i"){
		actionI();
	}
	else{
		std::cout<<"Invalid Action"<<std::endl;
	}
	return 0;
}