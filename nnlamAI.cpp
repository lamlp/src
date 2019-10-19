#include <bits/stdc++.h>
using namespace std;

struct Point
{
    int x;
    int y;
};

int MAT[20][30];
int mang[10][10];
int row, col, mybot, soplayer, m;
int xMinSta, yMinSta, xDatGan, yDatGan, xKhoangTrong, yKhoangTrong, dichuyen=-1;
int DEMkt,DEMunst,DEMst;
struct queueNode
{
    Point pt;
    int dist;
};

int rowNum[] = {-1, 0, 0, 1};
int colNum[] = {0, -1, 1, 0};

//Check khong dung tuong
bool isValid(int x, int y)
{
    return (x >= 0) && (x < 30) &&
           (y >= 0) && (y < 30);
}

//Check my Stable
bool checkMyStable(int x, int y)
{
	if (MAT[x][y] == mybot)
	return 1;
	else
	return 0;
}

//Giai thuat BFS
int BFS(int mat[20][30], Point src, Point dest)
{
	queueNode curr;
    bool visited[20][30];
    memset(visited, false, sizeof visited);
    visited[src.x][src.y] = true;
    queue<queueNode> q;
    queueNode s = {src, 0};
    q.push(s);
    while (!q.empty())
    {
        curr = q.front();
        Point pt = curr.pt;
		if (pt.x == dest.x && pt.y == dest.y)
        {
            return curr.dist;
 		}
        q.pop();
 
        for (int i = 0; i < 4; i++)
        {
            int rowTam = pt.x + rowNum[i];
            int colTam = pt.y + colNum[i];
            if (isValid(rowTam, colTam) && mat[rowTam][colTam]!= mybot+1 && 
               !visited[rowTam][colTam])
            {
                visited[rowTam][colTam] = true;
                queueNode Adjcell = { {rowTam, colTam},
                                      curr.dist + 1 };
                q.push(Adjcell);
            }
        }
    }
    return INT_MAX;
}

//Khoang cach 2 diem
int KhoangCach(int x1,int y1,int x2, int y2)
{
    Point source = {x1, y1};
    Point dest = {x2, y2};
    return BFS(MAT, source, dest);
}

void myViTri()
{
	for(int i=0; i < soplayer ;i++)
	{
		for (int j=0; j<2; j++)
		cin>> mang[i][j];
	}
	int b= mybot/2;
	row= mang[b][0], col= mang[b][1], m=b;
}

//Reset gia tri
void capnhat()
{
	DEMkt=0,DEMunst=0,DEMst=0;
	int tam;
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			cin>>s;
			tam = MAT[i][j]=s-'0';
			//cout<<" "<<tam<<" ";
			if (MAT[i][j] == 0)
				{
				mangKhoangTrong[DEMkt]=i;
				mangKhoangTrong[DEMkt+1]=j;
				DEMkt+=2;
				}
				else if (tam == 1 || tam == 3 || tam == 5 || tam == 7)
					{
					mangUnStable[DEMst]=i;
					mangUnStable[DEMst+1]=j;
					DEMst+=2;
					}
					else if (tam == 2 || tam == 4 || tam == 6 || tam == 8)
						{
						mangUnStable[DEMunst]=i;
						mangUnStable[DEMunst+1]=j;
						DEMunst+=2;
						}
			/*switch(tam)
			{
				case 0:	{	mangKhoangTrong[DEMkt]=i,mangKhoangTrong[DEMkt+1]=j,DEMkt+=2;
					break;
				}
				case 1:{	mangUnStable[DEMst]=i,mangStable[DEMst+1]=j,DEMst+=2;
					break;
				}
				case 2:{	mangUnStable[DEMunst]=i,mangUnStable[DEMunst+1]=j,DEMunst+=2;
					break;
				}
				case 3:{	mangUnStable[DEMst]=i,mangStable[DEMst+1]=j,DEMst+=2;
					break;
				}
				case 4:{	mangUnStable[DEMunst]=i,mangUnStable[DEMunst+1]=j,DEMunst+=2;
					break;
				}
				case 5:{	mangUnStable[DEMst]=i,mangStable[DEMst+1]=j,DEMst+=2;
					break;
				}
				case 6:{	mangUnStable[DEMunst]=i,mangUnStable[DEMunst+1]=j,DEMunst+=2;
					break;
				}
				case 7:{	mangUnStable[DEMst]=i, mangStable[DEMst+1]=j, DEMst+=2;
					break;
				}
				case 8:{	mangUnStable[DEMunst]=i,mangUnStable[DEMunst+1]=j,DEMunst+=2;
					break;
				}
				default:{
					break;
				}
			}*/
		}
	}
	myViTri();
}

bool sangtrai()
{
	if (dichuyen!=2 && KhoangCach(row,col-1, xMinSta, yMinSta)!=INT_MAX)
	{
	cout<<"LEFT"<<endl;
	dichuyen= 1;
	return 1;
	}
	else return 0;
}

bool sangphai()
{
	if (dichuyen!=1 && KhoangCach(row,col+1, xMinSta, yMinSta)!=INT_MAX)
	{
	cout<<"RIGHT"<<endl;
	dichuyen= 2;
	return 1;
	}
	else return 0;
}

bool dilen()
{
	if (dichuyen!=3 && KhoangCach(row-1,col, xMinSta, yMinSta)!=INT_MAX)
	{
	cout<<"UP"<<std::endl;
	dichuyen= 0;
	return 1;
	}
	else return 0;
}

bool dixuong()
{
	if (dichuyen!=0 && KhoangCach(row+1,col, xMinSta, yMinSta)!=INT_MAX)
	{
	cout<<"DOWN"<<endl;
	dichuyen= 3;
	return 1;
	}
	else return 0;
}

void dichuyenDen(int x, int y)
{
	int min = 100, giatri =0, bien=0, rowDen,colDen;
	for (int i = 0; i < 4; i++)
    {
    		rowDen=row,colDen=col;
            rowDen += rowNum[i];
            colDen += colNum[i];
            if (isValid(rowDen, colDen) && MAT[rowDen][colDen] == (mybot+1))
            {
            	giatri = KhoangCach(rowDen, colDen, x, y);
				if (giatri < min)
				{
				if (i==0 && dichuyen!=3)
				{
				min = giatri;
				bien =i;
				}
				else if (i==1 && dichuyen!=2)
				{
				min = giatri;
				bien =i;
				}
				else if (i==2 && dichuyen!=1)
				{
				min = giatri;
				bien =i;
				}
				else if (i==3 && dichuyen!=0)
				{
				min = giatri;
				bien =i;
				}
				}
			}
	}
	switch (bien)
	{
	case 0: {
	if (!dilen())
	if (!sangtrai())
	if (!sangphai())
	dixuong(); break;}
  	case 1: {
	if (!sangtrai())
	if (!dixuong())
	if (!dilen())
	sangphai(); break;}
	case 2: {
	if (!sangphai())
	if (!dilen())
	if (!dixuong())
	sangtrai(); break;}
	case 3: {
	if (!dixuong())
	if (!sangphai())
	if (!sangtrai())
	dilen(); break;}
	default: {
	if (!dilen())
	if (!sangtrai())
	if (!sangphai())
	dixuong(); break;}
	}
}

//Khoang cach tu vi tri Enemy den my Unstable gan nhat
int khoangcachEnemyToMyUnStable()
{
	int min = 100;
	int giatri = 0;
	for (int i = 0; i <= DEMunst; i+2)
	{	
			if (MAT[mangUnStable[i]][mangUnStable[i+1]]==mybot+1)
			for (int l = 0; l<soplayer; l++)
			{
				if (l!=m)
				{
				giatri = KhoangCach( mangUnStable[i], mangUnStable[i+1], mang[l][0], mang[l][1]);
				if (giatri < min)
				min = giatri;
				}
			}
	}
	return min;
}

//Khoang cach tu vi tri den My Stable
int khoangcachMyStable()
{
	int min=100;
	int giatri;
	for (int i=0;i<=DEMst;i+2)
	{
		if (checkMyStable(mangStable[i],mangStable[i+1]))
			{
			giatri=KhoangCach(row, col, mangStable[i], mangStable[i+1]);
			if (giatri < min && giatri != INT_MAX)
			{
			xMinSta=mangStable[i],yMinSta=mangStable[i+1];
			min = giatri;
			}
			}
	}
	return min;
}

//Khoang cach tu toi den Enemy
int khoangcachEnemy()
{
	int min=100;
	int giatri=0;
	for(int i=0;i<soplayer;i++)
	{
		if (i!=m)
		{
		giatri=KhoangCach(row, col, mang[i][0], mang[i][1]);
		if (giatri < min && giatri != INT_MAX)
		min = giatri;
		}
	}
	return min;
}

void quayVe()
{
	dichuyenDen(xMinSta, yMinSta);
}

bool KhoangTrong(int x, int y)
{
	if (MAT[x][y]==0)
	return 1;
	else return 0;
}

int khoangTrongMin()
{
	int min=100;
	int giatri=0;
	for (int i = 0; i <= DEMkt; i+2)
	{
			if (KhoangTrong(mangKhoangTrong[i],mangKhoangTrong[i+1]))
			{
			giatri=KhoangCach(row, col, mangKhoangTrong[i], mangKhoangTrong[i+1]);
			if (giatri < min && giatri != SHRT_MAX)
			{
			min = giatri;
			xKhoangTrong = mangKhoangTrong[i], yKhoangTrong = mangKhoangTrong[i+1];
			}
			}
	}
	return min;
}

int datGanNhat()
{
	int min=100;
	int giatri=0;
	int rowDat,colDat;
	for (int i = 0; i < 4; i++)
    {
    		rowDat=row,colDat=col;
            rowDat += rowNum[i];
            colDat += colNum[i];
            
			if (isValid(rowDat,colDat) && MAT[rowDat][colDat]!=mybot+1 && MAT[rowDat][colDat]!=mybot)
			{
			giatri=KhoangCach(rowDat, colDat, xMinSta, yMinSta);
			if (giatri < min)
			{
			min = giatri;
			xDatGan = rowDat, yDatGan = colDat;
			}
			}
	}
	return min;
}

void Farm()
{
	//10, 15
	//Goc tren tay trai
	
	if ((row<=10 && col<=15) && MAT[0][0]==0)
	dichuyenDen(0, 0);
	
	//Goc tren tay phai
	else if ((row<=10 && col>15) && MAT[0][29]==0)
	dichuyenDen(0, 29);
	
	//Goc duoi tay trai
	else if ((row>10 && col<=15) && MAT[19][0]==0)
	dichuyenDen(19, 0);
	
	//Goc duoi tay phai
	else if ((row>10 && col>15) && MAT[19][29]==0)
	dichuyenDen(19, 29);
	
	//Di tu do
	else
	{
	int dat=datGanNhat(), ktrong=khoangTrongMin();
	if (dat + 2 < ktrong)
		dichuyenDen(xDatGan,yDatGan);
		else
		{
		dichuyenDen(xKhoangTrong,yKhoangTrong);
		}
	}
}

int main()
{
	cin>>soplayer;
	cin>>mybot;
	int EneGoMyUns, IGoMySta, IvsEnemy;
	while(true)
	{
    capnhat();
    EneGoMyUns = khoangcachEnemyToMyUnStable(), IGoMySta = khoangcachMyStable() + 3, IvsEnemy = khoangcachEnemy();
	if ( EneGoMyUns <= IGoMySta || IvsEnemy < 4 )
	quayVe();
	else
    Farm();
	}
}
