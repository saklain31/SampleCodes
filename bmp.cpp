#include <bits/stdc++.h>
using namespace std;
int h,w,color;
int n,m;
string str,str2;
int input[1000][1000],output[1000][1000],inp[1000][1000],height,width;

void halftoning(int i,int j,int val)
{
    
    val=val/9;
    //printf("%d\n",val);
    if(val>=25)
    {
        output[i+1][j+1] = 255;
    }
    if(val>=50)
    {
        output[i+1][j+2] = 255;
    }
    if(val>=80)
    {
        output[i+1][j] = 255;
    }
    if(val>=105)
    {
        output[i][j+1] = 255;
    }
    if(val>=130)
    {
        output[i+2][j+2] = 255;
    }
    if(val>=160)
    {
        output[i][j] = 255;
    }
    if(val>=180)
    {
        output[i+2][j] = 255;
    }
    if(val>=210)
    {
        output[i+2][j+1] = 255;
    }
    if(val>=235)
    {
        output[i][j+2] = 255;
    }
}

void takeInput()
{
    freopen("output.ascii.pgm","r",stdin);
    freopen("output1.ascii.pgm","w",stdout);
    getline(cin,str); 
    getline(cin,str2);

    cin>>w>>h>>color;
    n=h%3;
    m=w%3;
    for(int i=0;i<h+n;i++)
    {
        for(int j=0;j<w+m;j++)
        {
            if(i>=h)
            {
                inp[i][j]=0;
                continue;
            }
            else if(j>=w)
            {
                inp[i][j]=0;
                continue;   
            }
            scanf("%d",&inp[i][j]);
        }
    }
    int i,j;
    for(i=0;i<h+n;i+=3)
    {
        
        for(j=0;j<w+m;j+=3)
        {
            int val=0;
            val+=inp[i][j];
            //printf("%d\n",inp[i][j] );
            val+=inp[i][j+1];
            //printf("%d\n", inp[i][j+1]);
            val+=inp[i][j+2];
            //printf("%d\n",inp[i][j+2] );
            val+=inp[i+1][j];
            //printf("%d\n", inp[i+1][j]);
            val+=inp[i+1][j+1];
            //printf("%d\n", inp[i+1][j+1]);
            val+=inp[i+1][j+2];
            //printf("%d\n", inp[i+1][j+2]);
            val+=inp[i+2][j];
            //printf("%d\n", inp[i+2][j]);
            val+=inp[i+2][j+1];
            //printf("%d\n",inp[i+2][j+1] );
            val+=inp[i+2][j+2];
            //printf("%d\n",inp[i+2][j+2] );

            halftoning(i,j,val);
        }
        
        
    }   
}

unsigned char* ReadBMP(char* filename)
{
    int i;
    FILE* f = fopen(filename, "rb");
    FILE* fp = fopen("output.ascii.pgm","w");



    if(f == NULL)
        throw "Argument Exception";

    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

    // extract image height and width from header
    width = *(int*)&info[18];
    height = *(int*)&info[22];

    int maxcol=255;
    
    fprintf(fp, "P2\n");
    fprintf(fp, "# im1.pgma created by PGMA_IO::PGMA_WRITE.\n");
    fprintf(fp, "%d %d\n",width,height);
    fprintf(fp, "%d\n",maxcol);

    int cc=0;
    int row_padded = (width*3 + 3) & (~3);
    unsigned char* data = new unsigned char[row_padded];
    unsigned char tmp;

    int cnt;

    for(int i = 0; i < height; i++)
    {
        fread(data, sizeof(unsigned char), row_padded, f);
        cnt=0;
        for(int j = 0; j < width*3; j += 3)
        {
            // Convert (B, G, R) to (R, G, B)
            tmp = data[j];
            data[j] = data[j+2];
            data[j+2] = tmp;

            //cout << "R: "<< (int)data[j] << " G: " << (int)data[j+1]<< " B: " << (int)data[j+2]<< endl;
            int col = (int)data[j]+(int)data[j+1]+(int)data[j+2];
            col=col/3;
            //cout<<col<<" ";
            input[i][j/3]=col;
            //fprintf(fp, "%d ",col );
            cnt++;
            //cc++;
            //if(cc>12) return data;
            
        }
    }

    for (int i=height-1;i>=0;i--)
    {
        for(int j=0;j<width;j++)
        {
            fprintf(fp, "%d ",input[i][j]);
        }
    }

    printf("%d\n",cc );
    fclose(f);
    fclose(fp);
    return data;
}
main()
{
	unsigned char* data = ReadBMP("Lion.bmp");
    takeInput();
    cout<<str<<endl;
    cout<<str2<<endl;
    cout<<w<<" "<<h<<endl;
    cout<<color<<endl;
    for(int i=0;i<h;i++) 
    {
        for(int j=0;j<w;j++) 
        {
            cout<<output[i][j]<<" ";
        }
    }
}	
