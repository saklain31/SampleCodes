#include <bits/stdc++.h>
using namespace std;
int h,w,color;
int n,m;
string str,str2;
int input[1000][1000],output[1000][1000];


#pragma pack(push, 1)

typedef struct tagBITMAPFILEHEADER
{
    WORD bfType;  //specifies the file type
    DWORD bfSize;  //specifies the size in bytes of the bitmap file
    WORD bfReserved1;  //reserved; must be 0
    WORD bfReserved2;  //reserved; must be 0
    DWORD bfOffBits;  //species the offset in bytes from the bitmapfileheader to the bitmap bits
}BITMAPFILEHEADER;

#pragma pack(pop)

#pragma pack(push, 1)

typedef struct tagBITMAPINFOHEADER
{
    DWORD biSize;  //specifies the number of bytes required by the struct
    LONG biWidth;  //specifies width in pixels
    LONG biHeight;  //species height in pixels
    WORD biPlanes; //specifies the number of color planes, must be 1
    WORD biBitCount; //specifies the number of bit per pixel
    DWORD biCompression;//spcifies the type of compression
    DWORD biSizeImage;  //size of image in bytes
    LONG biXPelsPerMeter;  //number of pixels per meter in x axis
    LONG biYPelsPerMeter;  //number of pixels per meter in y axis
    DWORD biClrUsed;  //number of colors used by th ebitmap
    DWORD biClrImportant;  //number of colors that are important
}BITMAPINFOHEADER;

#pragma pack(pop)

unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader)
{
    FILE *filePtr; //our file pointer
    BITMAPFILEHEADER bitmapFileHeader; //our bitmap file header
    unsigned char *bitmapImage;  //store image data
    int imageIdx=0;  //image index counter
    unsigned char tempRGB;  //our swap variable

    //open filename in read binary mode
    filePtr = fopen(filename,"rb");
    if (filePtr == NULL)
        return NULL;

    //read the bitmap file header
    fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER),1,filePtr);

    //verify that this is a bmp file by check bitmap id
    if (bitmapFileHeader.bfType !=0x4D42)
    {
        fclose(filePtr);
        return NULL;
    }

    //read the bitmap info header
    fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER),1,filePtr); // small edit. forgot to add the closing bracket at sizeof

    //move file point to the begging of bitmap data
    fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);

    //allocate enough memory for the bitmap image data
    bitmapImage = (unsigned char*)malloc(bitmapInfoHeader->biSizeImage);

    //verify memory allocation
    if (!bitmapImage)
    {
        free(bitmapImage);
        fclose(filePtr);
        return NULL;
    }

    //read in the bitmap image data
    fread(bitmapImage,bitmapInfoHeader->biSizeImage,filePtr);

    //make sure bitmap image data was read
    if (bitmapImage == NULL)
    {
        fclose(filePtr);
        return NULL;
    }

    //swap the r and b values to get RGB (bitmap is BGR)
    for (imageIdx = 0;imageIdx < bitmapInfoHeader->biSizeImage;imageIdx+=3) // fixed semicolon
    {
        tempRGB = bitmapImage[imageIdx];
        bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
        bitmapImage[imageIdx + 2] = tempRGB;
    }

    //close file and return bitmap iamge data
    fclose(filePtr);
    return bitmapImage;
}


int main(int argc, char const *argv[])
{
	BITMAPINFOHEADER bitmapInfoHeader;
unsigned char *bitmapData;
bitmapData = LoadBitmapFile("im1.bmp",&bitmapInfoHeader);
//now do what you want with it, later on i will show you how to display it in a normal window
	return 0;
}
/*main()
{
	freopen("im1.bmp","r",stdin);
	char ch;
	int cnt=0;
	while(cnt<100)
	{
		scanf("%c",&ch);
		printf("%c\n",ch);
	}

}*/	
/*int main()
{
	ifstream inFile;
	ifstream::pos_type size;

	inFile.open( "im1.bmp", ios::in|ios::binary|ios::ate );
	char* oData;

	size = inFile.tellg();
	cout << "Size of file: " << size;
	inFile.seekg(0, ios::beg);

	oData = new char[ size ];

	inFile.read( oData, size );

	cout << " oData size: " << strlen(oData);
	cout << "\n";

	//print data
	for ( int i = 0; i < strlen(oData); i++ )
	{
		cout << "oData["<<i<<"] " << oData[i];
		cout << "\n";
		cout << oData[i] << " + 'a' = " << ( oData[i] + (char)'a' );
		cout << "\n\n";

	}
getchar();
return 0;
}
*/