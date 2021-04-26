#include "test.h"

#include <stdio.h>
#include <stdlib.h>
//#include <stddef.h>
#include <math.h>
#include <time.h>
#include <windows.h> 

#define WIDTH 4
#define HEIGHT 4

typedef struct {
	int x;
	int y;
	int dir; //方向：0 上，1 右，2 下， 3左 
} Info;

int arrInit[WIDTH][HEIGHT] = 
{
	{
		-1,0,0,-1
	},
	{
		0,0,0,0
	},
	{
		0,0,0,0
	},
	{
		0,0,0,0
	}
};

int arr[WIDTH][HEIGHT];

int count = 0;

Info turn(Info info) {
//	show();
	if(info.dir!=-1){
		count++;
		info.dir = (info.dir+1)%4;
	}
	arr[info.x][info.y] = info.dir;
	switch(info.dir){
		case 0:
			info.x--;
			break;
		case 1:
			info.y++;
			break;
		case 2:
			info.x++;
			break;
		case 3:
			info.y--;
			break;
	}
	if(info.x < 0 || info.x >= WIDTH || info.y < 0 || info.y >= HEIGHT || arr[info.x][info.y]==-1) {
		info.dir = -1;
	}else {
		info.dir = arr[info.x][info.y];
	}
//	show();
	return info;
}

void show(){
	int i,j;
	printf("------\n");
	for(i=0;i<WIDTH;i++){
		for(j=0;j<HEIGHT;j++){
			char c;
			switch(arr[i][j]){
				case 0:
					c = '^';
					break;
				case 1:
					c = '>';
					break;
				case 2:
					c = '_';
					break;
				case 3:
					c = '<';
					break;
				default:
					c = ' ';
					break;
			}
			printf("%c ",c);
		}
		printf("\n");
	}
	printf("------\n");
}

void clearArr(){
	int i,j;
	for(i=0;i<WIDTH;i++){
		for(j=0;j<HEIGHT;j++){
			arr[i][j] = arrInit[i][j];
		}
	}
}

void click(int x, int y) {
//	printf("click [%d][%d] .................\n",x,y);
	Info info = {x,y,arr[x][y]};
	while(turn(info).dir!=-1) {
		int x = turn(info).x;
		count--;
		int y = turn(info).y;
		count--;
		int dir = turn(info).dir;
		count--;
		info.x = x;
		info.y = y;
		info.dir = dir;
	}
}

typedef struct {
	int second;
	int minute;
	int hour;
	int day;
} TimeFormat;

TimeFormat getTimeFormat(double time){
	long long t = (long long)time;
	TimeFormat tF = {0,0,0,0};
	tF.second = t%60;
	t /= 60;
	if(t!=0){
		tF.minute = t%60;
		t /= 60;
		if(t!=0){
			tF.hour = t%24;
			t /= 24;
			if(t!=0){
				tF.day = t;
			}
		}
	}
	return tF;
}

void findBestWay(){
	time_t start_time;
	time_t end_time;
	time(&start_time);
	double percent;
	double percentTmp;
	
	int x,y;
	long long totalLen = WIDTH*HEIGHT;
	long long totalLenPrem = totalLen*totalLen*totalLen*totalLen*totalLen*totalLen*totalLen*totalLen*totalLen*totalLen;
	int pathtmp[10] = {0};
	int path[10] = {0};
	int max = 0;
	long long i,j;
	for(i=0;i<totalLenPrem;i++){
		int n = 10;
		count = 0;
		clearArr();
		long long index = i;
		while(n--){
//			printf("---------------- i = %d -------------------\n",i);
			pathtmp[n] = index%totalLen;
			x = (index%totalLen)/HEIGHT;
			y = (index%totalLen)%HEIGHT;
//			printf("arr[%d][%d]\n",arr[x][y]);
			click(x,y);
//			show();
			index /= totalLen;
		}
		if(count>max){
			max = count;
			int k;
			for(k=0;k<10;k++){
				path[k] = pathtmp[10-k-1];
			}
		}
		percent = ((double)i*100)/totalLenPrem; 
		if(i%10000000==0){
			time(&end_time);
			percentTmp = percent;
		}
		if(i%100000==0 || i==totalLenPrem-1){
			printf("\r%f%%(%.0fs)",percent,(end_time-start_time)*100/percentTmp);
		}
//		printf("count = %d\n",count*90);
	}
	
	printf("\narr[%d][%d]",path[0]/HEIGHT,path[0]%HEIGHT);
	for(i=1;i<10;i++){
		printf(" -> arr[%d][%d]",path[i]/HEIGHT,path[i]%HEIGHT);
	}
	printf("\n");
	printf("max = %d\n",max*90);
}

int main(){
	time_t start_time;
	time_t end_time;
	time(&start_time);
	findBestWay();
	time(&end_time);
	printf("\nend_time - start_time = %lld\n", end_time - start_time);

//	clearArr();
//	click(3,1);
//	click(2,2);
//	click(1,1);
//	click(1,1);
//	click(1,1);
//	click(0,2);
//	click(3,1);
//	click(3,2);
//	click(3,2);
//	click(3,2);
//	show();

//	time_t tmpcal_ptr;
//	struct tm *tmp_ptr = NULL;
//	time(&tmpcal_ptr);
//	printf("tmpcal_ptr=%d\n", tmpcal_ptr);
//	tmp_ptr = gmtime(&tmpcal_ptr);
//	printf("after gmtime, the time is:%d:%d:%d\n", tmp_ptr->tm_hour, tmp_ptr->tm_min, tmp_ptr->tm_sec);
//	tmp_ptr = localtime(&tmpcal_ptr);
//	printf ("after localtime, the time is:%d.%d.%d ", (1900+tmp_ptr->tm_year), (1+tmp_ptr->tm_mon), tmp_ptr->tm_mday);
//	printf("%d:%d:%d\n", tmp_ptr->tm_hour, tmp_ptr->tm_min, tmp_ptr->tm_sec);


	return 0;
}
