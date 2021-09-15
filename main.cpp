//#pragma comment(linker,"/STACK:1024000000,1024000000")
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <sstream>
#include <algorithm>
#include <time.h>
#include <memory.h>
#include <string>
#include <random>
#include <functional>
#include <list>
#include<windows.h>
#include<bits/stdc++.h>//提示音
using namespace std;
#include"head.h"
#include"init.h"
//#include"newInit.h"
#include"algori.h"
//#include"test.h"
 
int main() {

	clock_t begin, end;
	begin = clock();
	
	//for (int i = 0; i < 20; i++)
	
		//fireflyAlgor(0);
		GSO(0);
	end = clock();
	double costTime = (double)(end - begin) / 1000.0;
	cout << endl << "time:" << costTime << endl;
	
	printf("\a");//提示音
	system("pause");
	return 0;
}