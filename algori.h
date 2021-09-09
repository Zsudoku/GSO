//程序入口
/*
* 注意事项：
* 
1.初始种群（编码方式）
2.解码方式（对个体、对种群）

萤火虫两两比较，较差的向较优的飞行移动

3.flyMove飞行移动：飞行移动针对编码里的每个参数按公式进行扰动，如果在过程中产生了小数点坐标得处理（取整）
4.randWalk2：编码内随机交换位置
*/
/*
void fireflyAlgor(int circle) {

	clock_t begin1, end1;
	begin1 = clock();
	srand(unsigned(time(NULL)));

	getPerm(fly);//初始化种群，产生编码
	enCode(fly);//种群解码，关键

	int N1 = 0;//迭代次数
	while (N1 < TMAX) {

		//将当前 迭代次数 输出到命令窗口
		//cout<<"******进入迭代**********"<<endl;
		//cout.width(7);
		cout << N1 <<endl;
		//cout << "\b\b\b\b\b\b\b\b"<<endl;

		int k2 = 0;	//计数中间解的个数
		firefly nextfly[flyNum];		//存储的是对两个种群进行择优后选出的前N个最优编码,中间存储一下再交给初始种群fly
		firefly temfly[2*flyNum + 1];	//中间种群：萤火虫移动后的解不全保留，也只维持和初始种群一样大小,+1是一个尾巴，最差值
		firefly temfly2;				//临时存储新的解

clock_t begin2, end2;
	begin2 = clock();

		for (int i = 0; i < flyNum/2; i++) {
			//cout<<"-----"<<i<<endl;
			for (int j = i +80; j < flyNum; j++) {
				if (k2 <= 2*flyNum) {//前flyNum个移动后的解直接保存
					if (dominate(fly[i], fly[j]) == 0)  flyMove(fly[i], fly[j], temfly[k2]);
					else if (dominate(fly[i], fly[j]) == 1)  flyMove(fly[j], fly[i], temfly[k2]);
					else randWalk2(fly[j], temfly[k2]);
					k2++;
				}
				else { //在移动后解构成的大小为flyNum种群中，后面产生的解与种群中最差的解比较，更新移动后种群
					if (dominate(fly[i], fly[j]) == 0)  flyMove(fly[i], fly[j], temfly2);
					else if(dominate(fly[i], fly[j]) == 1)  flyMove(fly[j], fly[i], temfly2);
					else  randWalk2(fly[j], temfly2);
					int bad = getBad(temfly); //计算中间种群中最差解的下标
					memcpy(&temfly[bad], &temfly2, sizeof(firefly));
				}
			}
		}
		
		end2 = clock();
	double costTime2 = (double)(end2 - begin2) / 1000.0;
cout << endl << "time:" << costTime2 << endl;

		/*
		cout<<N1<<"@@@@@@@@@@@@@@@@@@"<<endl;
		for(int i=0;i<flyNum;i++){
		for(int j=0;j<n;j++){
			cout<<fly[i].G[j]<<",";
			}cout<<endl;cout<<fly[i].fitness<<endl;}
		*/
		
/*
		for (int i = 0; i < 2*flyNum + 1; i++) { //对中间种群进行局部搜索，即再去进行优化
			if(N1<5000) opt2(temfly[i]);
			else swa(temfly[i]);
		}
*/


		//精英机制,选择前N个：综合比较 初始种群 和 中间种群 -->选出最优的前N个个体组成下一代种群nextfly
		//方法1：把两个种群放在一起进行排序（按照目标函数的大小），直接取前N个
		//方法2：对两个种群分别进行排序，再分别拿出第一个进行对比，直到选出N个
		/*
clock_t begin1, end1;
	begin1 = clock();

		const int combineSize = 3*flyNum+1;
		firefly combinedPouplation[combineSize];
		memcpy(combinedPouplation, fly, flyNum * sizeof(firefly));
		memcpy(combinedPouplation + flyNum, temfly, (2*flyNum + 1) * sizeof(firefly));
		sort(combinedPouplation, combinedPouplation + combineSize,comp); //对组合种群按小到大排序
		int capNum = flyNum;
		for (int i = 0; i < flyNum;i++) {//选出前N个解
			//对混合种群进行排序选取，选出最优的前N个编码组成下一代种群
			memcpy(&nextfly[i], &combinedPouplation[i], sizeof(firefly));
		}

		memcpy(fly, nextfly, flyNum * sizeof(firefly));//fly更新为下一代的初始种群,nextfly传给fly

		//存储每一代的最优个体
		//若需要存储其他中间量，可在此处单独编程

		N1++;

		end1 = clock();
	double costTime1 = (double)(end1 - begin1) / 1000.0;
cout << endl << "time:" << costTime1 << endl;
for(int i=0;i<3;i++){
		for(int j=0;j<n;j++){
			cout<<fly[i].G[j]<<",";
			}cout<<endl;cout<<fly[i].fitness<<endl;}

	}

	end1 = clock();
	double costTime1 = (double)(end1 - begin1) / 1000.0;
	for(int i=0;i<3;i++){
		for(int j=0;j<n;j++){
			cout<<fly[i].G[j]<<",";
			}cout<<endl;cout<<fly[i].fitness<<endl;}
	////保存30次所有最优结果
	//ofstream ocout;
	//ocout.open("G:\\VRPTW\\testOut\\VRTW_FA调试实验\\swa-800-1.txt", ios::app);//文件名：种群大小-迭代次数
	//ocout << circle + 1 << ": " << gerationfly[TMAX - 1].carBest << " " << gerationfly[TMAX - 1].disBest <<" "<< costTime1 <<"  ";
	//ocout<< gerationfly[TMAX - 1].carBest << "-" << gerationfly[TMAX - 1].carBest_dis << "  " << gerationfly[TMAX - 1].disBest << "-" << gerationfly[TMAX - 1].disBest_car << endl;
	//ocout.close();
}
*/

void GSO(int circle) {
	ofstream out;
    out.open("out.txt");
	srand(unsigned(time(NULL)));

	getPerm(fly);//初始化种群，产生编码
	enCode(fly);//种群解码，关键
	for (int i = 0; i < n; i++) //货位号之间的距离
		for (int j = i + 1; j < n; j++) {
			dis[i][j] = sqrt(pow((cargo[i].x - cargo[j].x), 2) + pow((cargo[i].y - cargo[j].y), 2) + pow((cargo[i].z - cargo[j].z), 2));
			dis[j][i] = dis[i][j];
		}

	vector<int> Nt[flyNum];//萤火虫个体的邻域集合下标
	double rd[flyNum];//萤火虫邻域半径
	firefly modifly[flyNum];
	int N1 = 0;//迭代次数
	while (N1 < TMAX) {

		cout<<"**********"<<N1<<"************"<<endl;
		out<<"**********"<<N1<<"************"<<endl;
		clock_t begin1, end1;
		begin1 = clock();

		for (int i = 0; i < flyNum; i++)//更新萤火虫邻域半径
			rd[i] = min(rs, max(0.0, rd[i] + betata * (nt - Nt[i].size())));

		for (int i = 0; i < flyNum; i++) //确定萤火虫邻域集
			for (int j = 0; j < flyNum; j++) {
				if (i == j) break;
				if (discode(fly[i].G,fly[j].G) < rd[i] && fly[i].fluorescein > fly[j].fluorescein)
					Nt[i].push_back(j);
			}
		
		int count = 0;
		for (int i = 0; i < flyNum; i++) {//萤火虫在邻域内进行飞行移动
			if (Nt[i].empty()) {//邻域内为空则进行变领域搜索
				firefly temp;
				memcpy(&temp, &fly[i], sizeof(firefly));
				LocalSearch(temp);
				if (temp.fluorescein == fly[i].fluorescein)
					randCode(modifly[count++]);//萤火虫重复则随机产生一条
				else memcpy(&modifly[count++], &temp, sizeof(firefly));
				continue;
			}
			double sum = 0,pi = 0;
			int tag = 0;//记录pi值最大的下标
			for (int j = 0; j < Nt[i].size(); j++) {
				sum = sum + fly[Nt[i][j]].fluorescein - fly[i].fluorescein;
			}
			for (int j = 0; j < Nt[i].size(); j++) {
				double tempi = (fly[Nt[i][j]].fluorescein - fly[i].fluorescein) / sum;
				if (tempi > pi) { pi = tempi; tag = j; }
			}
			flyMove(fly[Nt[i][tag]], fly[i], modifly[count]);
			//GSOMove(fly[i],fly[Nt[i][tag]], modifly[count]);
			//enSimpleCode(modifly[count]);
			//gsofly(fly[Nt[i][tag]], fly[i], modifly[count]);
			LocalSearch(modifly[count++]);

			vector<int>().swap(Nt[i]);
		}

		//const int combineSize = 2 * flyNum;
		//firefly combinedPouplation[combineSize];
		memcpy(combinedPouplation, fly, flyNum * sizeof(firefly));
		memcpy(combinedPouplation + flyNum, modifly, flyNum * sizeof(firefly));//精英策略
		sort(combinedPouplation, combinedPouplation + 2*flyNum, comp); //按照适应度值排序
		int capNum = flyNum;
		for (int i = 0; i < flyNum; i++) {//选出前N个解
			//对混合种群进行排序选取，选出最优的前N个编码组成下一代种群
			memcpy(&fly[i], &combinedPouplation[i], sizeof(firefly));
		}
		
		N1++;
		end1 = clock();
		double costTime1 = (double)(end1 - begin1) / 1000.0;
		cout << endl << "time:" << costTime1 << endl;
		out<< endl << "time:" << costTime1 << endl;
		for(int i=0;i<1;i++){
			for(int j=0;j<n;j++){
				//cout<<fly[i].G[j]<<",";
				out<<fly[i].G[j]<<",";
				}
			cout<<fly[i].fitness<<endl;
			out<<endl<<fly[i].fitness<<endl;
		}
	}

	for(int i=0;i<1;i++){
		for(int j=0;j<n;j++){
			cout<<fly[i].G[j]<<",";
			}cout<<endl;cout<<fly[i].fitness<<endl;}
	out.close();
}

