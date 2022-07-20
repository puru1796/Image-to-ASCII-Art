#include<iostream>
#include<fstream>
using namespace std;

//Variable declaration
int bmp_w;
int bmp_h;
char bmp_ASCII[500][500];
int i = 0, j = 0;
double max_grayScale = 0.3*(255.0 / 256.0) + 0.6*(255.0 / 256.0) + 0.11*(255.0 / 256.0);

//Function intialization
void print_bmp();
int get_padding(int width);
void setArray(double gray_scale);

int main(){
	char bmp[200];
	cin >> bmp;
	cout << endl;
	ifstream fin;
	fin.open(bmp, ios::binary);
	unsigned char* bmp_info;
	bmp_info = new unsigned char[54];
	fin.read((char*)bmp_info, 54);
	bmp_w = *(int*)&bmp_info[18];
	bmp_h = *(int*)&bmp_info[22];

	int padding = get_padding(bmp_w);
	unsigned char* pixelInfo = new unsigned char[padding];
	char temp;
	while (i < bmp_h)
	{
		fin.read((char*)pixelInfo, padding);

		for (j = 0; j < bmp_w * 3; j += 3)
		{
			temp = pixelInfo[j];

			pixelInfo[j] = pixelInfo[j + 2];

			pixelInfo[j + 2] = temp;

			double grayScale = 0.3*((int)pixelInfo[j] / 256.0) + 0.6*((int)pixelInfo[j + 1] / 256.0) + 0.11*((int)pixelInfo[j + 2] / 256.0);

			setArray(grayScale);
		}
		i++;
	}
	fin.close();
	print_bmp();

	return 0;
}


//Functions
int get_padding(int width){
	return (((width * 3 + 3) / 4) * 4);
}

void setArray(double gray_scale){
	if (gray_scale > 0.6){
		bmp_ASCII[i][j] = 65 + (gray_scale - 0.6)*(1 * 26 / (max_grayScale - 0.6));
	}

	else if (gray_scale >= 0.3){
		bmp_ASCII[i][j] = 97 + (gray_scale - 0.3)*(1 * 26 / 0.3);
	}

	else{
		bmp_ASCII[i][j] = 32 + (gray_scale * (1 * 16 / 0.3));
	}
}

void print_bmp(){
	for (int i = bmp_h - 1; i >= 0; i--){
		for (int j = 0; j < bmp_w * 3; j = j + 3){
			if (bmp_ASCII[i][j] == '['){
				bmp_ASCII[i][j] = 'z';
			}
			cout << bmp_ASCII[i][j];
		}
		cout << endl;
	}
}