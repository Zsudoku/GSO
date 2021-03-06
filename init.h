//快速排序
//选择基准（轴）
int partition(double array[][2], int low, int high)
{
    while (low < high)
    {
        //low位置为轴点，low右边的不小于low左边的
        while (low < high&&array[low][1] <= array[high][1])
        {
            high--;
        }
        double temp = array[low][1];
        array[low][1] = array[high][1];
        array[high][1] = temp;

        temp = array[low][0];
        array[low][0] = array[high][0];
        array[high][0] = temp;
        //high位置为轴点，high左边的不大于high右边的
        while (low < high&&array[low][1] <= array[high][1])
        {
            low++;
        }
        temp = array[low][1];
        array[low][1] = array[high][1];
        array[high][1] = temp;

        temp = array[low][0];
        array[low][0] = array[high][0];
        array[high][0] = temp;
    }
    return low;
}

void quickSortHelp(double array[][2], int low, int high)
{
    if (low < high)
    {
        //找枢轴元位置
        int location = partition(array, low, high);
        //递归调用
        quickSortHelp(array, low, location - 1);
        quickSortHelp(array, location + 1, high);
    }
}

void quickSort(double array[][2], int sort_n)
{
    //以第一个数组元素为基准（轴）
    quickSortHelp(array, 0, sort_n - 1);
}
//判断货物类型
char judge_type(int p){
	if(cargo[p].s1==0 && cargo[p].s2==0)
		return 'R';
	else if(cargo[p].s1==0 && cargo[p].s2==1)
		return 'S';
	else if(cargo[p].s1==1 && cargo[p].s2==0)
		return 'H';
	else if(cargo[p].s1==1 && cargo[p].s2==1)
		return 'C';
	else{
		cout<<"judge_type error!"<<endl;
		cout<<p<<endl;
		return 'C';
	}
}

//交换货位坐标
void CS_swap(){
	srand((double)clock());
	for(int i=0;i<n/2;i++){
		int sit = rand()%(n-1);
		int temp_x=0,temp_y=0,temp_z=0;
		temp_x = cargo[i].x;
		temp_y = cargo[i].y;
		temp_z = cargo[i].z;
		cargo[i].x = cargo[sit].x;
		cargo[i].y = cargo[sit].y;
		cargo[i].z = cargo[sit].z;
		cargo[sit].x = temp_x;
		cargo[sit].y = temp_y;
		cargo[sit].z = temp_z;
	}
	ofstream out1;
	ofstream out_sit;
	out1.open("rand_2000_1.txt");
	out_sit.open("rand_2000_1_sit.txt");
	for(int i=0;i<n;i++){
		out1<<"{"<<cargo[i].x<<","<<cargo[i].y<<","<<cargo[i].z<<","<<cargo[i].s1<<","<<cargo[i].s2<<","<<cargo[i].num<<","<<"'a'"<<","<<cargo[i].model<<","<<cargo[i].time<<"}"<<",";
		out_sit<<cargo[i].x<<","<<cargo[i].y<<","<<cargo[i].z<<","<<judge_type(i)<<endl;
		if((i+1)%5==0){
			out1<<endl;	
		}
	}
	out1.close();
	out_sit.close();
}



//入库仿真

//获得入库编码
void get_R(int g[]){
	int j=0;
	for(int i=0;i<n;i++){
		if(g[i]<=R && j<R){//遍历数组，如果数组编码小于R，则说明为回库编码
			r_arry[j] = g[i];
			j++;
		}
	}
}
//判断该编码属于哪台堆垛机
int stacker(int p){
	int ddj = 0;
	if(cargo[p-1].x==1 || cargo[p-1].x==2)		//如果货架坐标为1、2，则为堆垛机1
		ddj = 1;
	else if(cargo[p-1].x==3 || cargo[p-1].x==4)	//如果货架坐标为3、4，则为堆垛机2
		ddj = 2;
	else if(cargo[p-1].x==5 || cargo[p-1].x==6)//如果货架坐标为5、6，则为堆垛机3
		ddj = 3;
	else if(cargo[p-1].x==7 || cargo[p-1].x==8)//如果货架坐标为7、8，则为堆垛机4
		ddj = 4;
	else if(cargo[p-1].x==10 || cargo[p-1].x==9)//如果货架坐标为9、10，则为堆垛机5
		ddj = 5;
	else if(cargo[p-1].x==11 || cargo[p-1].x==12)//如果货架坐标为11、12，则为堆垛机6
		ddj = 6;
	else{
		cout<<"ddj error!"<<endl;				//如果是其他货位坐标则说明错误
		ddj = 0;
	}
	return ddj;
}
//货物从上货点到叠箱机的时间
void getT_load(int i,char type){
	//int n_load1 = R_n/fre; //从上货点1发出的货物数量 fre为每秒中一共出货的总数量
	//int n_load2 = R_n - n_load1;//从上货点2发出的货物数量 
		//判断是否从上货点2发出:
		//1: fre1 + t_load1
		//2: fre2 + t_load2
		//3: fre1*2 + t_load1
		//4: fre2*2 + t_load2
		//5: fre1*3 + t_load1
		//6: fre2*3 + t_load2
		if(i%2==0){
			t_R = fre2*(i/2) + t_load2;  
		}
		else{
			t_R = fre1*((i+1)/2) + t_load1;
		}
		temp_p++;
		if(type=='A'){//如果属于A类型 3箱成一垛
			if(temp_p==a_num){
				temp_p = 0;
				flag_R++;//发送一垛
				send_t = t_R;//发送时间
			}
		}
		else{
			if(temp_p==b_num){//B类型，5箱一垛
				temp_p = 0;
				flag_R++;//发送一垛
				send_t = t_R;
			}
		}
}
        
//传入堆垛机的序号，返回到该堆垛机的时间
double getT(int ddj){
	switch(ddj){		//根据到不同堆垛机的距离，计算出到达堆垛机的时间
		case 1:
			return r_ji1/v_R;
		case 2:
			return r_ji2/v_R;
		case 3:
			return r_ji3/v_R;
		case 4:
			return r_ji4/v_R;
		case 5:
			return r_ji5/v_R;
		case 6:
			return r_ji6/v_R;
		default:return 0;
	}
}
void R_Test(int r[]){
	int an=0;
	int ddj;
	//write.open("Test.txt");//表示你要把内容输出到“text.txt"这个文件里 如果没有这个文件，会自动创建这个文件
	int p_R = 0;//入库编码下标
	for(int i =1;i<=R_n;i++){
		if(p_R>R)	//	防止出现数组访问越界
			break;
		if(an>R)	//	防止出现数组访问越界
			break;
        getT_load(i,'A');//按照上货箱数的编号，从1~R_n开始上货物，类型A
        if(flag_R==2 && p_R<R){//集齐两垛 开始计算到达堆垛机入口的时间
			flag_R = 0;	//将标记归0
            ddj = stacker(r[p_R]);//根据入库编码，计算出堆垛机序号
			p_R++;
            get_t = send_t + getT(ddj);//计算到达时间 = 发送时间+到达堆垛机的时间
			//cout<<"get_t:"<<get_t<<endl;
        if(ddj==1){//判断是否属于堆垛机1
            //cout<<"The ddj is "<<ddj<<"\tThe num "<<p_R<<"\tstack arrive ddj time is "<<get_t<<endl;
            //write<<"The ddj is "<<ddj<<"\tThe num "<<p_R<<"\tstack arrive ddj time is "<<get_t<<endl;
				//cout<<1<<endl;
				a[an] = get_t;//写入数组a中
				an++;
                //write<<get_t<<endl;
                get_t = 0;//将到达时间变量归0
				continue;//提高程序效率，不再进行下面的判断
        }
        if(ddj==2){
			a[an] = get_t;
				an++;
               // write<<get_t<<endl;
                get_t = 0;
				continue;
        }
        if(ddj==3){
			a[an] = get_t;
				an++;
                //write<<get_t<<endl;
                get_t = 0;
				continue;
        }
        if(ddj==4){
			a[an] = get_t;
				an++;
               // write<<get_t<<endl;
                get_t = 0;
				continue;
        }
        if(ddj==5){
			a[an] = get_t;
				an++;
               // write<<get_t<<endl;
                get_t = 0;
				continue;
        }
        if(ddj==6){
			a[an] = get_t;
				an++;
                //write<<get_t<<endl;
                get_t = 0;
				continue;
        }
    }
	}
	//write.close(); // 输出完毕后关闭这个文件
}

void randomArr(int G[],int len){    //随机序列，G为编码数组,len为编码数组长度
    for(int i=0;i<len;i++){
        int sit = rand()%(len-1) +1;//随机位置
        int temp =G[i];		//交换当前位置的编码和随机位置的编码
        G[i] = G[sit];
        G[sit] = temp;
        //cout<<sit<<endl;
    }
}
//检定时间
void inspect(char type_inspect){//输入货物类型
            switch(type_inspect){//根据不同货物类型，计算不同的检定时间
                case 'a':
                    t_inspect = t_inspect_a * s_h;  //将a的检定时间（小时）换算成秒 赋值给 检定时间
                    break;
                case 'b':
                    t_inspect = t_inspect_b * s_h;
                    break;
                case 'c':
                    t_inspect = t_inspect_c * s_h;
                    break;
                case 'd':
                    t_inspect = t_inspect_d * s_h;
                    break;
                case 'e': 
                    t_inspect = t_inspect_e * s_h;
                    break;
                case 'f':
                    t_inspect = t_inspect_f * s_h;
                    break;    
                default:t_inspect = 0;
                break;
            }
}
//行走时间
double Walk_time(int y,int z){//输入 y、z坐标
    float v1 = 2;//堆垛机垂直移动速度
    float v2 = 4;//堆垛机水平移动速度
    float l = 0.5;//垛 长度
    float h = 0.65;//货架的一个高
    float d = 0.2;//货位间的距离
    int Yn = y;//y坐标
    int Zn = z;//z坐标
    float High_In = 0;//垂直移动的距离
    float Long_In = 0;//水平移动的距离
    float time_in_high = 0;//垂直移动的时间
    float time_in_long = 0;//水平移动的时间
    float time_in_run = 0;//堆垛机移动的时间
    float time = 0;//堆垛机移动的时间（多设置一个变量，用于后续测试）
    High_In = Zn * h;//计算垂直移动的距离
    Long_In = Yn  * (l + d);//计算水平移动的距离
    time_in_high = High_In / v1;//计算垂直移动的时间
    time_in_long = Long_In / v2;//计算水平移动的时间
    time_in_run = max(time_in_high,time_in_long);//堆垛机垂直运动的时间与堆垛机水平移动的时间 两者最长的时间即为堆垛机的移动时间
    time = time_in_run;//赋值给time
    return time;//返回堆垛机运动的时间
}
//插入，目前没有用到
void insert_G(int G[],int sit,int value){  //插入 ，在某个数组中插入一个元素，输入数组，插入的元素，和插入的位置。目前此函数没有用到
    len++;
    int *a_n = new int[len];
    for(int i = 0;i<sit;i++)
        a_n[i] = G[i];
    a_n[sit] = value;
    for(int i = sit+1;i<len;i++)
        a_n[i] = G[i-1];
    for(int i=0;i<len;i++)
        G[i] = a_n[i];
    delete []a_n;
}
//送检前h-k个编码，回库后h-k个编码，形成1-1对应关系。
void S_H2(int G[]){//输入编码数组
    int j = 0,p=0;
    for(int i=0;i<n;i++){//遍历编码数组
        if(cargo[G[i]-1].s1==0 && cargo[G[i]-1].s2==1 && G[i]>=R+1 && G[i]<=R+H-k){//按照编码的顺序，判断编码是否属于 送检编码,且该送检编码属于前H-K
			s[j] = G[i];//将该编码写入到送检数组中
			INum[j][0] = i;
			j++;//送检数组下标自增1
		}
		else if(cargo[G[i]-1].s1==1 && cargo[G[i]-1].s2==0 && G[i]>=R+S+k+1 && G[i]<=R+S+H){//按照编码顺序，判断编码是否属于回库编码，且回库编码属于后H-k
			h[p] = G[i];//将该编码写入到回库编码
			INum[p][1] = i;
			p++;//回库数组下标自增1
		}
    }	
	for(int i=0;i<H-k;i++){
		I[i][0] = s[i];
		I[i][1] = h[i];
	}		
}

//送检前h-k个编码，回库后h-k个编码，形成1-1对应关系。
void S_H(firefly f){//该函数与S_H2的功能一致，但输入的是一个种群
	int j = 0,p=0;
    for(int i=0;i<n;i++){
        if(cargo[f.G[i]-1].s1==0 && cargo[f.G[i]-1].s2==1 && f.G[i]>=R+1 && f.G[i]<=R+H-k){
			s[j] = f.G[i];
			INum[j][0] = i;
			j++;
		}
		else if(cargo[f.G[i]-1].s1==1 && cargo[f.G[i]-1].s2==0 && f.G[i]>=R+S+k+1 && f.G[i]<=R+S+H){
			h[p] = f.G[i];
			INum[p][1] = i;
			p++;
		}
    }	
	for(int i=0;i<H-k;i++){
		I[i][0] = s[i];
		I[i][1] = h[i];
	}	
}

//判断S编码与对应的回库编码在G[n]的前后关系，如果 H编码位于对应的送检编码之前，交换两者位置，保证S编码始终位于与其相对应的H编码之前。
// void check(int G[],int s[],int h[]){
//     int temp = 0;
//     int l = 0;//送检编码数组下标
//     for(int i=0;i<n;i++){
//         if(R+1<=G[i] && R+H-k>=G[i]){//在G[]中，如果该元素属于到送检元素  
//             for(;l<H-k;l++){  //在s中确定该元素下标
//                 if(s[l]==G[i]){	//在G编码数组中找到送检编码					
// 					for(int j=0;j<n;j++){   // 在G[n]找到与s[l]对应的h[l]  下标均为l
// 						if(G[j]==h[l]){
// 							if(i>j){        //如果h位于s之前，交换位置。
// 								temp = G[j];
// 								G[j] = G[i];
// 								G[i] = temp;
// 							}
// 							break;//已找到回库编码，跳出循环
// 						}
// 					}
// 					break;//继续检测第二个送检编码
// 				}
// 			}	
//         }
//     }
// }

void check(firefly &f,int s[],int h[]){
	int i=0,temp=0;
	for(int j=0;j<H-k;j++){
		if(INum[j][0]>INum[j][1]){//需要交换
			temp = f.G[INum[j][0]];
			f.G[INum[j][0]] = f.G[INum[j][1]];
			f.G[INum[j][1]] = temp;
		}
	}	
}

void check(int G[],int s[],int h[]){
	int i=0,temp=0;
	for(int j=0;j<H-k;j++){
		if(INum[j][0]>INum[j][1]){//需要交换
			temp = G[INum[j][0]];
			G[INum[j][0]] = G[INum[j][1]];
			G[INum[j][1]] = temp;
		}
	}	
}

double read(double TI,double TDI,int p,int nextp){
    char type,next_type;//当前编码的货物类型，下一个编码的货物类型
	int ddj=0;//堆垛机序号
	int i=0;
    double wait_time = 0;//等待时间
    double grab_time = 1.5;//抓取时间
    double walk_time1 = 0;//行走时间1
    double place_time = 1.5;//放置时间
    double walk_time2 = 0;//行走时间2
	bool flag = false;
	//判断当前读取的编码属于哪种编码类型：R、S、H、C
    if(1<=p && p<=R )
        type = 'R';
    else if (R+1<=p && p<=R+S)
        type = 'S';
    else if (R+S+1<=p && p<=R+S+H)
        type = 'H';
    else if(R+S+H+1<=p && p<=R+S+H+C)
        type = 'C';
    else
        cout<<"p error!"<<endl;
	//判断下一个编码属于哪种货物类型
    if(1<=nextp && nextp<=R )
        next_type = 'R';
    else if (R+1<=nextp && nextp<=R+S)
        next_type = 'S';
    else if (R+S+1<=nextp && nextp<=R+S+H)
        next_type = 'H';
    else if(R+S+H+1<=nextp && nextp<=R+S+H+C)
        next_type = 'C';
    else
        cout<<"nextp error!"<<endl;
    switch (type){
        case 'R'://该编码为入库编码
            if(a[ai]<=TI)//判断等待时间 数组a[ai]中存放的入库时间是依次从小到大的
                wait_time = 0;
            else
                wait_time = a[ai] - TI;
			ai++;//数组 a下标自增
            walk_time1 = Walk_time(cargo[p-1].y,cargo[p-1].z);
            if(next_type=='R'||next_type=='H')
                walk_time2 = Walk_time(cargo[p-1].y,cargo[p-1].z);
            else
                walk_time2 = Walk_time(abs(cargo[p-1].y-cargo[nextp-1].y),abs(cargo[p-1].z-cargo[nextp-1].z));
            TI += wait_time + grab_time + walk_time1 + walk_time2 + place_time;
			TDI = grab_time + walk_time1 + walk_time2 + place_time + TD[0];
			TD[0] = TDI;
            break;
        case 'H':
            for(i=0;i<H-k;i++){//在h[]中找到下标
                if(hi[i][0] == p){
					flag = true;
					break;
				}
            }
            if(hi[i][1]<=TI || flag==false)
                wait_time = 0;
            else    
                wait_time = hi[i][1] - TI;
            walk_time1 = Walk_time(cargo[p-1].y,cargo[p-1].z);
            if(next_type=='R'||next_type=='H')
                walk_time2 = Walk_time(cargo[p-1].y,cargo[p-1].z);
            else
                walk_time2 = Walk_time(abs(cargo[p-1].y-cargo[nextp-1].y),abs(cargo[p-1].z-cargo[nextp-1].z));
            TI += wait_time + grab_time + walk_time1 + walk_time2 + place_time;
			TDI = grab_time + walk_time1 + walk_time2 + place_time + TD[0];
			TD[0] = TDI;
            break;
        case 'C':
            walk_time1 = Walk_time(cargo[p-1].y,cargo[p-1].z);
            if(next_type=='R'||next_type=='H')
                walk_time2 = Walk_time(cargo[p-1].y,cargo[p-1].z);
            else
                walk_time2 = Walk_time(abs(cargo[p-1].y-cargo[nextp-1].y),abs(cargo[p-1].z-cargo[nextp-1].z));
            TI += grab_time + walk_time1 + place_time + walk_time2;
			TDI = grab_time + walk_time1 + walk_time2 + place_time + TD[0];
			TD[0] = TDI;
            break;
        case 'S':
            walk_time1 = Walk_time(cargo[p-1].y,cargo[p-1].z); //堆垛机从当前位置移动到送检口，此处默认送检口为0,0
			if(next_type=='R'||next_type=='H')//如果下一个编码属于入库或回库编码
				walk_time2 = Walk_time(cargo[p-1].y,cargo[p-1].z);//***可修改***堆垛机最后移动到下一个编码的起始位置，也就是0,0位置（此处，后期可根据不同的回库资产的楼层让堆垛机移动到不同的位置）
			else
				walk_time2 = Walk_time(abs(cargo[p-1].y-cargo[nextp-1].y),abs(cargo[p-1].z-cargo[nextp-1].z));//如果属于送检或出库，则移动到该货物的货架位置
			TI +=  grab_time + walk_time1 + place_time+ walk_time2;//该条编码的堆垛机总工作时间为 等待时间+拿取时间+工作行走时间+放置时间+行走到下一条编码的时间
			TDI =  grab_time + walk_time1 + place_time+ walk_time2 + TD[0];//堆垛机实际工作时间 = 总工作时间-等待时间
			TD[0] = TDI;//将实际工作时间写入到实际工作数组中，如果后期有需要，则该数组可以保留每一台堆垛机的实际工作时间。此时将每台堆垛机的实际工作时间叠加到TD[0]中
			//开始计算 送检编码 所对应的 回库编码 的 回库时间
			for( i=0;i<H-k;i++){
				if(s[i]==p){//根据当前编码，找到在 送检编码数组 中的下标 i，此下标可对应在 回库数组 中的回库编码的位置
					ddj = stacker(h[i]);//判断该回库编码属于哪台堆垛机来服务
					switch (ddj)
					{
					case 1://如果是第一台堆垛机服务
						inspect(cargo[p-1].type);//根据该送检编码的货物类型，计算出送检时间
						g1_H2[th1]=h[i];//将该回库编码写入到堆垛机1的回库数组里
						th1++;//堆垛机1的 回库编码数组 和 回库时间数组 下标自增
						break;
					case 2:
						inspect(cargo[p-1].type);
						g2_H2[th2]=h[i];
						th2++;
						break;
					case 3:
						inspect(cargo[p-1].type);
						g3_H2[th3]=h[i];
						th3++;
						break;
					case 4:
						inspect(cargo[p-1].type);
						g4_H2[th4]=h[i];
						th4++;
						break;
					case 5:
						inspect(cargo[p-1].type);
						g5_H2[th5]=h[i];
						th5++;
						break;
					case 6:
						inspect(cargo[p-1].type);
						g6_H2[th6]=h[i];
						th6++;
						break;
					default:
						cout<<"read code ddj error!"<<endl;
						break;
					}
					//cout<<"------------"<<h[i]<<"------------"<<endl;
					hi[v2][1] = TI + t_inspect;//回库时间写入到hi[v2][1]中
					hi[v2][0] = h[i];//回库编码 写入到hi[v2][0]中
					v2++;//v2自增
					th[i] = TI + t_inspect;//回库时间统一写入到一个数组中
					break;
				}
			}
		break;
        default:
            cout<<"read error!"<<endl;
            break;
    }
    return TI;//返回堆垛机读取该编码的时间
}
//分拣编码数量
void Storing_num(firefly f){//输入种群
    int p=0;
	char g=0;
	g1_s = 0,g2_s = 0,g3_s = 0,g4_s = 0,g5_s = 0,g6_s = 0;
	g1_h = 0,g2_h = 0,g3_h = 0,g4_h = 0,g5_h = 0,g6_h = 0;
	g1_n=0;g2_n=0;g3_n=0;g4_n=0;g5_n=0;g6_n=0;
    for(int i=0;i<n;i++){//遍历所有货位
        p = cargo[f.G[i]-1].x;//货架信息
		g = judge_type(f.G[i]-1);//货物类别 R、S、H、C
        switch (p)//判断属于哪台堆垛机
        {
        case 1:
        case 2://属于1号堆垛机
			if(g=='S')//送检
				g1_s++;
			else if(g=='H')//回库
				g1_h++;
            g1_n++;//堆垛机1编码数量自增
            break;
        case 3:
        case 4:
			if(g=='S')
				g2_s++;
			else if(g=='H')
				g2_h++;
            g2_n++;
            break;
        case 5:
        case 6:
			if(g=='S')
				g3_s++;
			else if(g=='H')
				g3_h++;
            g3_n++;
            break;
        case 7:
        case 8:
			if(g=='S')
				g4_s++;
			else if(g=='H')
				g4_h++;
            g4_n++;
            break;
        case 9:
        case 10:
			if(g=='S')
				g5_s++;
			else if(g=='H')
				g5_h++;
            g5_n++;
            break;
        case 11:
        case 12:
			if(g=='S')
				g6_s++;
			else if(g=='H')
				g6_h++;
            g6_n++;
            break;
        default:
            cout<<"sort_num error!"<<endl;
            break;
        }
    }
}
//分拣编码
void Storing(firefly f,int g1[],int g2[],int g3[],int g4[],int g5[],int g6[],int g1_S[],int g2_S[],int g3_S[],int g4_S[],int g5_S[],int g6_S[],int g1_H[],int g2_H[],int g3_H[],int g4_H[],int g5_H[],int g6_H[]){
	j1=0,j2=0,j3=0,j4=0,j5=0,j6=0;
	int g1s=0,g2s=0,g3s=0,g4s=0,g5s=0,g6s=0;
	int g1h=0,g2h=0,g3h=0,g4h=0,g5h=0,g6h=0;
    int p=0;
	char g=0;
    for(int i=0;i<n;i++){//遍历编码数组
        p = cargo[f.G[i]-1].x;//货架信息
		g = judge_type(f.G[i]-1);//货物类别 R、S、H、C
        switch (p)//判断编码属于哪台堆垛机
        {
        case 1:
        case 2://属于堆垛机1
			if(g=='S'){//属于送检编码
				g1_S[g1s] = f.G[i];//将该编码写入堆垛机1的送检数组
				g1s++;//送检数组下标自增1
			}
			else if(g=='H'){//属于回库编码
				g1_H[g1h] = f.G[i];//该编码写入堆垛机1的回库数组
				g1h++;//回库数组下标自增1
			}
            g1[j1] = f.G[i];//该编码写入到堆垛机1的 编码数组中
            j1++;//堆垛机1的编码数组自增1
            break;
        case 3:
        case 4:
			if(g=='S'){
				g2_S[g2s] = f.G[i];
				g2s++;
			}
			else if(g=='H'){
				g2_H[g2h] = f.G[i];
				g2h++;
			}
            g2[j2] = f.G[i];
            j2++;
            break;
        case 5:
        case 6:
			if(g=='S'){
				g3_S[g3s] = f.G[i];
				g3s++;
			}
			else if(g=='H'){
				g3_H[g3h] = f.G[i];
				g3h++;
			}
            g3[j3] = f.G[i];
            j3++;
            break;
        case 7:
        case 8:
			if(g=='S'){
				g4_S[g4s] = f.G[i];
				g4s++;
			}
			else if(g=='H'){
				g4_H[g4h] = f.G[i];
				g4h++;
			}
            g4[j4] = f.G[i];
            j4++;
            break;
        case 9:
        case 10:
			if(g=='S'){
				g5_S[g5s] = f.G[i];
				g5s++;
			}
			else if(g=='H'){
				g5_H[g5h] = f.G[i];
				g5h++;
			}
            g5[j5] = f.G[i];
            j5++;
            break;
        case 11:
        case 12:
			if(g=='S'){
				g6_S[g6s] = f.G[i];
				g6s++;
			}
			else if(g=='H'){
				g6_H[g6h] = f.G[i];
				g6h++;
			}
            g6[j6] = f.G[i];
            j6++;
            break;
        default:
            cout<<"sort error!"<<endl;
            break;
        }
    }
}

//入库组 目前没有用到
void R_t(double a[]){
    int cnt = 0;
    double temp = 0;
    FILE *fp=fopen("Test.txt", "r");
    while(cnt<R){
        fscanf(fp, "%lf", &temp);
        a[cnt] = temp; 
        cnt++;
    }
    fclose(fp);
}

//获得适应度值，（最大工期*0.8 + 堆垛机实际工作时间*0.2）/60
int max2(double T[]){
	int i,j;
    double temp,G_fintess;
    for(i=0;i<5;i++)//按照数组元素，从大到小排序
        for(j=0;j<5-i;j++){
            if(T[j+1]>T[j]){
            temp=T[j+1];
            T[j+1]=T[j];
            T[j]=temp;
            }
        }
	//T[0] = T[0]/60.0;
	G_fintess = T[0]*0.95 + TD[0]*0.05;//适应度值计算，加权重
	//G_fintess = G_fintess/60.0;//除以60 将秒转换为分钟
	//T[0] = T[0]/60.0;//堆垛机实际工作时间 分钟
	return T[0];
    //return G_fintess;
}
void read_ddj(int gi_H[],int ddj,int gi[]){
	switch (ddj)//判断堆垛机序号
	{
	case 1:
		while(gi_H[h1]!=gi[j1]){//不断读取，直到读取到g1中第一条H编码为止

			if(j1<(g1_n-1)){//不属于最后一位编码	
				T1 = read(T1,TD1,gi[j1],gi[j1+1]);//读取编码
				j1++;//堆垛机数组编码自增1
			}
			else if(j1==(g1_n-1)){//如果读取到该堆垛机的最后一位编码，则下一条编码与当前编码相同
				T1 = read(T1,TD1,gi[j1],gi[j1]);
				j1++;
			}
			if(j1>g1_n-1)//如果该堆垛机的编码全部读取完毕
				break;//跳出循环

		}
		h1++;
		break;

	case 2:
		while(gi_H[h2]!=gi[j2]){ //不断读取，直到读取到g2中第一条H编码为止

			if(j2<(g2_n-1)){
				T2 = read(T2,TD2,gi[j2],gi[j2+1]);
				j2++;
			}
			else if(j2==(g2_n-1)){
				T2 = read(T2,TD2,gi[j2],gi[j2]);
				j2++;
			}	
			if(j2>g2_n-1)
				break;

		}
		h2++;	
		break;

	case 3:
		while(gi_H[h3]!=gi[j3]){ //不断读取，直到读取到g3中第一条H编码为止
			if(j3<(g3_n-1)){
				T3 = read(T3,TD3,gi[j3],gi[j3+1]);
				j3++;
			}
			else if(j3==(g3_n-1)){
				T3 = read(T3,TD3,gi[j3],gi[j3]);
				j3++;
			}	
			if(j3>g3_n-1)
				break;
		}	
		h3++;
		break;

	case 4:
		while(gi_H[h4]!=gi[j4]){ //不断读取，直到读取到g4中第一条H编码为止
			if(j4<(g4_n-1)){
				T4 = read(T4,TD4,gi[j4],gi[j4+1]);
				j4++;
			}
			else if(j4==(g4_n-1)){
				T4 = read(T4,TD4,gi[j4],gi[j4]);
				j4++;
			}	
			if(j4>g4_n-1)
				break;
		}
		h4++;
		break;

	case 5:
		while(gi_H[h5]!=gi[j5]){ //不断读取，直到读取到g5中第一条S编码为止
			if(j5<(g5_n-1)){
				T5 = read(T5,TD5,gi[j5],gi[j5+1]);
				j5++;
			}
			else if(j5==(g5_n-1)){
				T5 = read(T5,TD5,gi[j5],gi[j5]);
				j5++;
			}	
			if(j5>g5_n-1)
				break;
		}
		h5++;
		break;

	case 6:
		while(gi_H[h6]!=gi[j6]){ //不断读取，直到读取到g6中第一条S编码为止
			if(j6<(g6_n-1)){
				T6 = read(T6,TD6,gi[j6],gi[j6+1]);
				j6++;
			}
			else if(j6==(g6_n-1)){
				T6 = read(T6,TD6,gi[j6],gi[j6]);
				j6++;
			}	
			if(j6>g6_n-1)
				break;
		}	
		h6++;
		break;

	default:
		cout<<"read_ddj error!"<<endl;
		break;
	}
}
//判断是否产生交换
void decide_swap(int g[],int gi[],int gi_H2[],int gi_th[],int gi_H[],int thi,int p,int gi_h,int hj,int gi_n){//hj表示堆垛机读取的当前回库编码数量
	int u1=0,u2=0,temp=0;//u1，u2表示需要交换编码的下标
	int p1 = 0;
	bool flag_u1 = false,flag_u2 = false;
	p1 = hi[v-1][0];//时间最短的回库编码
	int ddj =  stacker(p1);//判断最短时间回库编码的堆垛机序号
	int p2=0;//要交换的编码
		for(int i=hj-1;i<thi;i++){//从读取到当前回库编码数量 开始 到所有已与送检编码匹配的回库编码数量为止
			if(p1==gi_H2[hj-1])break;//不需要交换
			else{//需要交换
				p2 = gi_H2[hj-1];//与第一位的回库编码交换
				for(int j=0;j<n;j++){
					if(g[j]==p1){
						u1 = j;
						flag_u1 = true;
						continue;
					}
					if(g[j]==p2){
						u2 = j;
						flag_u2 = true;
						continue;
					}
					if(flag_u1 == true && flag_u2 == true)
						break;
				}
				//在G中交换位置
				temp = g[u1];
				g[u1] = g[u2];
				g[u2] = temp;
				u1=0,u2=0;
				flag_u1 = false,flag_u2 = false;
				//在gi_h中交换
				for(int j=0;j<gi_h;j++){
					if(gi_H[j]==p1){
						u1 = j;
						continue;
					}
				if(gi_H[j]==p2){
					u2 = j;
					continue;
				}
				if(flag_u1 == true && flag_u2 == true)
					break;
				}
				temp = gi_H[u1];
				gi_H[u1] = gi_H[u2];
				gi_H[u2] = temp;
				u1=0,u2=0;
				flag_u1 = false,flag_u2 = false;
				gi_H2[hj-1] = p1;//替换在gi_H2中的编码
				//在gi中交换
				for(int j=0;j<gi_n;j++){
					if(gi[j]==p1){
						u1 = j;
						continue;
					}
				if(gi[j]==p2){
					u2 = j;
					continue;
				}
				if(flag_u1 == true && flag_u2 == true)
					break;
				}
				temp = gi[u1];
				gi[u1] = gi[u2];
				gi[u2] = temp;
				u1=0,u2=0;
				break;
			}
		}
	}
//找到时间最短的回库编码
int min_h(){
	int Th = th1+th2+th3+th4+th5+th6-v;//所有已读取送检编码的数量
    int i,j,p=0,sit=0;
    double temp;
	//冒泡排序
	for( i=v;i<Th-1;i++){//开始v是0，从0开始循环，到所有已读取的送检数量为止。表示遍历 所有已读取送检编码数量 的 回库编码 和 回库时间
	//主要是两两对比，将hi[][]数组根据回库时间进行排序，并且在排序时，其对应的回库编码也随着回库时间进行排序，保证hi[v][0]始终为 本次所有回库编码的最短时间
        for(j=v;j<Th-1-i;j++){
            if(hi[j+1][1]<hi[j][1]){
            temp=hi[j+1][1];
            hi[j+1][1]=hi[j][1];
            hi[j][1]=temp;

			sit = hi[j+1][0];
            hi[j+1][0] = hi[j][0];
            hi[j][0] = sit;
            }
        }
	}
	
	//快速排序
	//quickSortHelp(hi, v, Th-1);
	v++;//本次读取的最短回库编码的回库时间已找到，移动到下一位，此后，位于v之前的回库编码不再参与比较
	if(hi[v-1][0]==9999)
		v--;
	return hi[v-1][0];//返回最短回库时间的回库编码
}
//计算适应度值
double Fintess(firefly& f,int g1[],int g2[],int g3[],int g4[],int g5[],int g6[],int g1_H[],int g2_H[],int g3_H[],int g4_H[],int g5_H[],int g6_H[],int g1_H2[],int g2_H2[],int g3_H2[],int g4_H2[],int g5_H2[],int g6_H2[],int g1_th[],int g2_th[],int g3_th[],int g4_th[],int g5_th[],int g6_th[]){
	T1=0,T2=0,T3=0,T4=0,T5=0,T6=0;
	TD1=0,TD2=0,TD3=0,TD4=0,TD5=0,TD6=0;
	j1=0,j2=0,j3=0,j4=0,j5=0,j6=0;
	h1=0,h2=0,h3=0,h4=0,h5=0,h6=0;
	th1=0,th2=0,th3=0,th4=0,th5=0,th6=0;
	int ddj=0,p=0;
	v = 0;v2=0;
	TD[0]=0;
		//按照堆垛机顺序，依次读取编码，直到读取到回库编码为止
		read_ddj(g1_H,1,g1);
		read_ddj(g2_H,2,g2);
		read_ddj(g3_H,3,g3);
		read_ddj(g4_H,4,g4);
		read_ddj(g5_H,5,g5);
		read_ddj(g6_H,6,g6);
		
		//void decide_swap(firefly& f,int gi_H2[],int gi_th[],int gi_H[],int thi,int p,int gi_h,int hi)
		for(int i=0;i<H-k-6;i++){
			p = min_h();//最短回库时间的回库编码
			if(p==9999)
				break;
			ddj = stacker(cargo[p-1].x);//获取该编码的堆垛机序号
		switch (ddj)//判断 最短回库时间的回库编码的 堆垛机序号
		{
		case 1://如果是1号堆垛机，则先判断是否需要交换回库编码的为止，再读不断读取1号堆垛机的编码，直到读取到回库编码为止
			decide_swap(f.G,g1,g1_H2,g1_th,g1_H,th1,p,g1_h,h1,g1_n);//交换回库编码位置
			read_ddj(g1_H,1,g1);//读取编码，直到回库编码
			break;//跳出，继续获得最短回库时间 
		case 2:
			decide_swap(f.G,g2,g2_H2,g2_th,g2_H,th2,p,g2_h,h2,g2_n);
			read_ddj(g2_H,2,g2);
			break;
		case 3:
			decide_swap(f.G,g3,g3_H2,g3_th,g3_H,th3,p,g3_h,h3,g3_n);
			read_ddj(g3_H,3,g3);
			break;
		case 4:
			decide_swap(f.G,g4,g4_H2,g4_th,g4_H,th4,p,g4_h,h4,g4_n);
			read_ddj(g4_H,4,g4);
			break;
		case 5:
			decide_swap(f.G,g5,g5_H2,g5_th,g5_H,th5,p,g5_h,h5,g5_n);
			read_ddj(g5_H,5,g5);
			break;
		case 6:
			decide_swap(f.G,g6,g6_H2,g6_th,g6_H,th6,p,g6_h,h6,g6_n);
			read_ddj(g6_H,6,g6);
			break;
		default:
			cout<<"Fintess decide_swap error!"<<endl;
			break;
		}
	}
	
//判断6个子序列编码是否全部读取完毕
	if(j1+j2+j3+j4+j5+j6==n){
		T[0] = T1;T[1] = T2;T[2] = T3;T[3] = T4;T[4] = T5;T[5] = T6;
		return max2(T);
	}
	if(j1<g1_n){
		while(j1!=g1_n){
			if(j1==(g1_n-1)){
				T1 = read(T1,TD1,g1[j1],g1[j1]);
				j1++;
			}
			else if(j1<(g1_n-1)){
				T1 = read(T1,TD1,g1[j1],g1[j1+1] );
				j1++;
			}				
		}
	}

	if(j2<g2_n){
		while(j2!=g2_n){
			if(j2==(g2_n-1)){
				T2 = read(T2,TD2,g2[j2],g2[j2] );
				j2++;
			}
			else if(j2<(g2_n-1)){
				T2 = read(T2,TD2,g2[j2],g2[j2+1] );
				j2++;
			}				
		}
	}

	if(j3<g3_n){  
		while(j3!=g3_n){ 
			if(j3==(g3_n-1)){
				T3 = read(T3,TD3,g3[j3],g3[j3] );
				j3++;
			}
			else if(j3<(g3_n-1)){
				T3 = read(T3,TD3,g3[j3],g3[j3+1] );
				j3++;
			}	
		}	
	}

	if(j4<g4_n){  
		while(j4!=g4_n){ 
			if(j4==(g4_n-1)){
				T4 = read(T4,TD4,g4[j4],g4[j4] );
				j4++;
			}
			else if(j4<(g4_n-1)){
				T4 = read(T4,TD4,g4[j4],g4[j4+1] );
				j4++;
			}	
		}	
	}

	if(j5<g5_n){  
		while(j5!=g5_n){ 
			if(j5==(g5_n-1)){
				T5 = read(T5,TD5,g5[j5],g5[j5] );
				j5++;
			}
			else if(j5<(g5_n-1)){
				T5 = read(T5,TD5,g5[j5],g5[j5+1] );
				j5++;
			}	
		}	
	}

	if(j6<g6_n){  
		while(j6!=g6_n){ 
			if(j6==(g6_n-1)){
				T6 = read(T6,TD6,g6[j6],g6[j6] );
				j6++;
			}
			else if(j6<(g6_n-1)){
				T6 = read(T6,TD6,g6[j6],g6[j6+1] );
				j6++;
			}	
		}	
	}


	T[0] = T1;T[1] = T2;T[2] = T3;T[3] = T4;T[4] = T5;T[5] = T6;
	return max2(T);
}
//
//初始化种群
void getPerm(firefly fly[flyNum])//每一行是一个路径  创建好几个G
{	
	//R_t(a);
	//srand(6);
	srand((double)clock());//设置随机种子
	for(int i=0;i<flyNum;i++){
		for(int j=0;j<n;j++){
			G[j] = j+1;
		}
		randomArr(G,n);	//打乱顺序
		S_H2(G);
        check(G,s,h);//调整
        for(int m=0;m<n;m++)//写入到种群
			fly[i].G[m] =G[m];
	}

	// for(int i=0;i<flyNum;i++){
	// 	for(int j=0;j<n;j++){
	// 		cout<<fly[i].G[j]<<",";
	// 	}
	// 		cout<<endl;cout<<fly[i].fitness<<endl;
	// }
}
//单独解码
void enSimpleCode(firefly& f) {
	//初始化一些变量
	int b1 = INT32_MAX;
	ai = 0;
	flag_R = 0;
	t_R = 0;
	for(int i=0;i<R;i++){
		r_arry[i] = 0;
		a[i] = 0;
	}
	for(int i=0;i<6;i++){
		T[i] = 0;
		TD[i] = 0;
	}
	for(int i=0;i<H;i++){
		th[i] = 0;
		hi[i][0]=9999;
		hi[i][1]=999999;
		I[i][0] = 0;
		I[i][1] = 0;
		INum[i][0] = 0;
		INum[i][1] = 0;
		g1_H2[i] = 0;
		g2_H2[i] = 0;
		g3_H2[i] = 0;
		g4_H2[i] = 0;
		g5_H2[i] = 0;
		g6_H2[i] = 0;
	}
	S_H(f);//送检前h-k个编码，回库后h-k个编码，形成1-1对应关系。
	check(f,s,h);
	get_R(f.G);//分离出入库编码
	R_Test(r_arry);//计算出入库货物到达堆垛机的时间，从小到大排序
/*	
	for(int i=0;i<R;i++){
		cout<<a[i]<<endl;
	}
	cout<<"---------"<<endl;
*/	
	//cout<<endl;
	Storing_num(f);//计算出每台堆垛机的任务量、送检数量、回库数量
	int g1_S[g1_s],g2_S[g2_s],g3_S[g3_s],g4_S[g4_s],g5_S[g5_s],g6_S[g6_s];//送检任务分拣到6台堆垛机
	int g1_H[g1_h],g2_H[g2_h],g3_H[g3_h],g4_H[g4_h],g5_H[g5_h],g6_H[g6_h];//回库任务分拣到6台堆垛机
	int g1_th[g1_h],g2_th[g2_h],g3_th[g3_h],g4_th[g4_h],g5_th[g5_h],g6_th[g6_h];//6台堆垛机的回库任务的时间
	int g1[g1_n],g2[g2_n],g3[g3_n],g4[g4_n],g5[g5_n],g6[g6_n];//任务分拣到6台堆垛机
	
	for(int i=0;i<g1_h;i++){g1_th[i]=999999;g1_H2[i]=0;}
	for(int i=0;i<g2_h;i++){g2_th[i]=999999;g2_H2[i]=0;}
	for(int i=0;i<g3_h;i++){g3_th[i]=999999;g3_H2[i]=0;}
	for(int i=0;i<g4_h;i++){g4_th[i]=999999;g4_H2[i]=0;}
	for(int i=0;i<g5_h;i++){g5_th[i]=999999;g5_H2[i]=0;}
	for(int i=0;i<g6_h;i++){g6_th[i]=999999;g6_H2[i]=0;}

	Storing(f,g1,g2,g3,g4,g5,g6,g1_S,g2_S,g3_S,g4_S,g5_S,g6_S,g1_H,g2_H,g3_H,g4_H,g5_H,g6_H);//将每台堆垛机的工作和送检、回库任务分离成不同的数组。共18个数组
	//f.fitness=Fintess(f,g1,g2,g3,g4,g5,g6,g1_H,g2_H,g3_H,g4_H,g5_H,g6_H );
	f.fitness = Fintess(f,g1,g2,g3,g4,g5,g6,g1_H,g2_H,g3_H,g4_H,g5_H,g6_H,g1_H2,g2_H2,g3_H2,g4_H2,g5_H2,g6_H2,g1_th,g2_th,g3_th,g4_th,g5_th,g6_th);//计算适应度值
	f.fluorescein = (1-rou)*f.fluorescein + gamma / f.fitness;

}

void enCode(firefly fly[flyNum]) {
	//按照自己的方法对 初始种群 中的每个个体进行解码，计算出目标函数
	//先写对一条编码的解码，再循环调用
		for(int i=0;i<flyNum;i++){
			enSimpleCode(fly[i]);
			//cout<<fly[0].G[1999];
		}
		// enSimpleCode(fly[0]);
		// enSimpleCode(fly[1]);
		// enSimpleCode(fly[2]);
}


int dominate(firefly f1, firefly f2) {
	if (f1.fitness <= f2.fitness)
		return 0;//f1支配f2
	else 
		return 1;//f2支配f1
}


//萤火虫fj向萤火虫fi飞行移动
void flyMove(firefly fi, firefly fj, firefly& temfly) {

	double beta2 = 0;//萤火虫的吸引力
	int count = NUMBER;//统计编码所有维度变化值不为0的个数
	double delta[NUMBER] = { 0 };//每一维度之间的变化值
	double rij2 = 0;//萤火虫之间笛卡尔距离的平方
	int passCount = 0;//继承较亮萤火虫结点位置数量
	int movedfly[NUMBER] = { 0 };//移动后的萤火虫,初始化为0

	for (int i = 0; i < NUMBER; i++)
		rij2 += pow(fi.G[i] - fj.G[i], 2);

	beta2 = 1 * exp(-gamma * rij2);

	for (int i = 0; i < NUMBER; i++) {//计算变化值delta
		//delta[i] = beta * nodeDis[fi.G[i]][fj.G[i]]; 
		//delta[i] = beta2 * fabs(fi.G[i] - fj.G[i]);
		delta[i] = beta2 * fabs(dis[fi.G[i]] - dis[fj.G[i]]);
		if (delta[i] == 0) count--;
	}

	int fjCopy[NUMBER] = { 0 };//复制萤火虫编码，为了不影响原来的萤火虫
	memcpy(fjCopy, fj.G, NUMBER * sizeof(int));

	//passCount = floor(beta2* count); //向下取整
	passCount = step;//随机步长，即继承节点数目
	for (int i = 0; i < passCount; i++) {//继承萤火虫fi中结点
		int temp = 0;
		for (int j = 0; j < NUMBER; j++) {
			if (delta[j] >= delta[temp]) temp = j;
		}
		movedfly[temp] = fi.G[temp];
		delta[temp] = 0;//置为0便于找下一个个最大数

		for (int k2 = 0; k2 < NUMBER; k2++) {	//在萤火虫j的副本中，将已经继承过结的点置0
			if (fjCopy[k2] == movedfly[temp]) { fjCopy[k2] = 0; break; }
		}
	}

	int k2 = 0;
	int noneZero[NUMBER] = { 0 };//存储萤火虫fj中余下结点
	for (int i = 0; i < NUMBER; i++) {
		if (fjCopy[i] != 0) noneZero[k2++] = fjCopy[i];
	}

	//将萤火虫j中其他结点按照顺序依次填入移动后的编码中
	int m = 0;
	for (int i = 0; i < NUMBER; i++)
		if (movedfly[i] == 0) movedfly[i] = noneZero[m++];
	firefly movefly;
	memcpy(movefly.G, movedfly, NUMBER * sizeof(int));
	S_H(movefly);
	check(movefly, s, h);
	enSimpleCode(movefly);
	memcpy(&temfly, &movefly,sizeof(firefly));
}



//萤火虫亮度相等时的随机扰动
void randWalk2(firefly ff, firefly temfly) {//对象为萤火虫
	int walkfly[NUMBER] = { 0 };
	memcpy(walkfly, ff.G, NUMBER * sizeof(int));

	int randNum = 1+rand()%5;
	for (int i = 0; i < randNum; i++) {
		int s1 = rand() % NUMBER;
		int s2 = rand() % NUMBER;
		while (s2 == s1) {//s1!=s2
			s2 = rand() % NUMBER;
		}
		swap(walkfly[s1], walkfly[s2]);
	}
	memcpy(temfly.G, walkfly, NUMBER * sizeof(int));
	enSimpleCode(temfly);
}


int getBad(firefly f[flyNum+1]) {
	int badNum = 0;
	for (int i = 1; i < flyNum+1; i++)
		if (f[i].fitness >= f[badNum].fitness) badNum = i;
	return badNum;
}

void neibor_opt2(firefly& f) {
	int maxT = 20;
	firefly temp_;
	memcpy(&temp_, &f, sizeof(firefly));
	for (int i = 0; i < maxT; i++)
	{
		srand(unsigned(rand()));
		int bd = 1+rand() % 5;
		int r1 = rand() % NUMBER;
		int r2 = (r1+bd) % NUMBER;
		if (r1 < r2)
			reverse(temp_.G + r1, temp_.G + r2+1);
		else
			reverse(temp_.G + r2, temp_.G + r1+1);

		enSimpleCode(temp_);
		if (dominate(temp_, f) == 0) {
			memcpy(&f, &temp_, sizeof(firefly));
		}
		else {
			memcpy(&temp_, &f, sizeof(firefly));
		}
	}
}

//void opti_2opt(firefly& f) {
//	firefly walkfly;
//	memcpy(walkfly.G,f.G,NUMBER*sizeof(int));
//
//	bool tag = false;
//	//do {
//		tag = false;
//		for (int i = 0; i < NUMBER - 3; i++) {
//			int d1 = nodeDis[f.G[i]][f.G[i + 1]] + nodeDis[f.G[i + 2]][f.G[i + 3]];
//			int d2 = nodeDis[f.G[i]][f.G[i + 2]] + nodeDis[f.G[i + 1]][f.G[i + 3]];
//			if (d1 > d2) {
//				changeCount++;
//				swap(walkfly.G[i + 1], walkfly.G[i + 2]);
//				enSimpleCode(walkfly);
//				//if (dominate(walkfly, f) == 0) {
//					memcpy(&f, &walkfly, sizeof(firefly));
//					//tag = true;
//			/*	}
//				else {
//					swap(walkfly.G[i + 1], walkfly.G[i + 2]);
//					enSimpleCode(walkfly);
//				}*/
//			}
//		}
//	//} while(tag);
//}
/*
void opt2(firefly& f) {
	int maxT = 20;
	firefly temp;
	for (int i = 0; i < maxT; i++)
	{
		memcpy(&temp, &f, sizeof(firefly));
		int r1 = rand() % NUMBER;
		int r2 = rand() % NUMBER;
		while (r2 == r1) {//s1!=s2
			r2 = rand() % NUMBER;
		}
		if (r1 < r2)
			reverse(temp.G + r1, temp.G + r2);
		else
			reverse(temp.G + r2, temp.G + r1);

		enSimpleCode(temp);
		if (dominate(temp,f)==0) {
			memcpy(&f, &temp,sizeof(firefly));
		}
	}
}
*/
void opt2(firefly& f) {//逆序
	int maxT = 10;
	firefly temp;
	for (int i = 0; i < maxT; i++)
	{
		memcpy(&temp, &f, sizeof(firefly));
		int r1 = rand() % NUMBER;
		int r2 = rand() % NUMBER;
		while (r2 == r1) {//s1!=s2
			r2 = rand() % NUMBER;
		}
		if (r1 < r2)
			reverse(temp.G + r1, temp.G + r2);
		else
			reverse(temp.G + r2, temp.G + r1);
		S_H(temp);
		check(temp, s, h);//调整
		enSimpleCode(temp);
		if (dominate(temp,f)==0) {
			memcpy(&f, &temp,sizeof(firefly));
		}
	}
}



void rand_opt2(firefly& f) { //超突变
	int maxT = 10;
	for (int i = 0; i < maxT; i++)
	{
		int r1 = rand() % NUMBER;
		int r2 = rand() % NUMBER;
		while (r2 == r1) { //s1!=s2
			r2 = rand() % NUMBER;
		}
		if (r1 < r2)
			reverse(f.G + r1, f.G + r2);
		else
			reverse(f.G + r2, f.G + r1);
		enSimpleCode(f);
	}
}

void t_t(firefly& f) {
	firefly temp;
	memcpy(&temp, &f, sizeof(firefly));
	bool tag = false;

	do{
		tag = false;
		for (int i = 0; i < NUMBER - 1; i++) {
			swap(temp.G[i], temp.G[i + 1]);
			enSimpleCode(temp);
			if (dominate(temp, f) == 0) {
				memcpy(&f, &temp, sizeof(firefly));
				tag = true;
			}
			else swap(temp.G[i], temp.G[i + 1]);
		}
	} while (tag);
}

void copyLink(LinkList L,LinkList &copyL) {
	copyL = new LNode;
	copyL->next = NULL;
	LNode* pL, * pCL, * p;
	pL = L->next;
	pCL = copyL;
	while (pL != NULL) {
		p = new LNode;
		p->data = pL->data;
		p->next = pCL->next;
		pCL->next = p;
		pCL = pCL->next;
		pL = pL->next;
	}
}

void linkToList(LinkList L,int G[NUMBER]) {//链式存储转换成顺序存储
	LNode * p;
	p = L->next;
	for (int i = 0; i < NUMBER; i++) {
		G[i] = p->data;
		p = p->next;
	}
}

void listToLink(firefly f,LinkList &L) { //顺序存储转换成链式存储
	L = new LNode;
	L->next = NULL;
	LNode* pf;
	pf = L;
	pf->next = NULL;
	for (int i = 0; i < NUMBER; i++) {
		LNode* p;
		p = new LNode;
		p->data = f.G[i];
		p->next = pf->next;
		pf->next = p; //加入的结点连接上
		pf = p;
		pf->next = p->next;
	}
}

void insertAll_sub(LinkList copyL, int r, int r1, firefly &bestfly) {//r(r>=1)单个节点位置,r1(r1>=0)插入位置
	//L中提取出单个节点
	LNode* pr, * pf;
	pr = copyL;
	int i = 0;
	while (i != r - 1) {
		pr = pr->next;
		i++;
	}
	pf = pr;
	pr = pr->next;	//提取出的节点
	pf->next = pr->next;	//L中删去了pr
	pr->next = NULL;

	//L中插入
	LNode* p;
	p = copyL;
	int j = 0;
	do {
		if (j == r1) {
			pr->next = p->next;
			p->next = pr;
			break;
		}
		else {
			p = p->next;
			j++;
		}
	} while (1);
	firefly newf;
	//linkToList(copyL, newf.G);//链式-->顺序
	enSimpleCode(newf);
	if (dominate(newf, bestfly) == 0) {
		memcpy(&bestfly, &newf, sizeof(firefly));
	}
	else {
		//复原
		p->next = pr->next;
		pr->next = pf->next;
		pf->next = pr;
	}
}

void releasePoint(LinkList &L) {//释放L内存空间
	LNode* Lp1, * Lp2;
	Lp1 = L->next;
	Lp2 = L->next;
	while (Lp1 != NULL) {
		Lp1 = Lp2->next;
		delete Lp2;
		Lp2 = Lp1;
	}
	delete L;
}

void insert(firefly &f) { //取出单个，多次插入
	LinkList L, copyL;
	listToLink(f,L);	//顺序-->链式

	firefly bestf;
	memcpy(&bestf, &f, sizeof(firefly));
	for (int i = 0; i <= 20; i++) { //[1,100]取出单个
		srand(unsigned(rand()));
		int r = 1 + rand() % NUMBER;
		for (int j = 0; j < NUMBER; j++) { //[0,99]多次插入
			if (j != i) {
				insertAll_sub(L, r, j, bestf);
			}
		}
	}
	memcpy(&f, &bestf, sizeof(firefly));
	releasePoint(L);
	//releasePoint(copyL);
	//LNode* t; //输出:顺序-链式存储
	//t = copyL->next;
	//while (t != NULL) { 
	//	cout << t->data <<"--";
	//	t = t->next;
	//}
	//cout <<endl;

	//int G[NUMBER] = {};//输出:链式-顺序存储
	//linkToList(L,G);
	//for (int i = 0; i < NUMBER; i++)
	//	cout << G[i] << "--";
	//cout << endl;

	//LNode* p;//测试复制函数
	//p = copyL->next;
	//while (p!=NULL) {
	//	cout << p->data << "--";
	//	p = p->next;
	//}
}

void insertAll_sub_car(LinkList copyL, int r, int r1, firefly& bestfly) {//r(r>=1)单个节点位置,r1(r1>=0)插入位置
	//L中提取出单个节点
	LNode* pr, * pf;
	pr = copyL;
	int i = 0;
	while (i != r - 1) {
		pr = pr->next;
		i++;
	}
	pf = pr;
	pr = pr->next;	//提取出的节点
	pf->next = pr->next;	//L中删去了pr
	pr->next = NULL;

	//L中插入
	LNode* p;
	p = copyL;
	int j = 0;
	do {
		if (j == r1) {
			pr->next = p->next;
			p->next = pr;
			break;
		}
		else {
			p = p->next;
			j++;
		}
	} while (1);
	//firefly newf;
	//linkToList(copyL, newf.G);//链式-->顺序
	//enSimpleCode(newf);
	//if (newf.carNum < bestfly.carNum) {
	//	memcpy(&bestfly, &newf, sizeof(firefly));
	//}
	//else {
	//	//复原
	//	p->next = pr->next;
	//	pr->next = pf->next;
	//	pf->next = pr;
	//}
}


void decompRounte(firefly f, LinkList &rtHead) { //分解成各个路径链表 
	LinkList L; //表头
	listToLink(f, L); //顺序-->链式
	LNode* Lp1,* tempLp1;
	Lp1 = L->next;

	LinkList headL, record;//路径头节点
	headL = new LNode;
	headL->next = Lp1;
	headL->head = NULL;
	record = headL;
	rtHead->head = headL;
	
	int count = 1;
	int ca = 0;
	//while (Lp1 != NULL) {
	//	if (count == f.car_nodeNum[ca]) {	//找到车辆的临界点
	//		ca++;
	//		count = 1;
	//		tempLp1 = Lp1->next;//指向下一辆车的首节点
	//		Lp1->next = NULL;
	//		Lp1 = tempLp1;
	//		
	//		if (ca == f.carNum) break;//避免多加一个空节点
	//		LinkList temphL;
	//		temphL = new LNode;//下一辆车的头结点
	//		temphL->next = Lp1;
	//		temphL->head = NULL;

	//		record->head = temphL;
	//		record = record->head;
	//	}
	//	else {
	//		count++;
	//		Lp1 = Lp1->next;
	//	}
	//}
	delete L;
}

void releaseRouteHead(LinkList &routeHead) {
	LinkList hd,hd2;
	hd = routeHead->head;
	hd2 = hd;
	LNode* Lp1, * Lp2;

	while (hd != NULL) {//车队头节点
		Lp1 = hd->next;
		Lp2 = hd->next;
		while (Lp1!=NULL) {//队内客户节点
			Lp1 = Lp2->next;
			delete Lp2;
			Lp2 = Lp1;
		}
		hd = hd2->head;
		delete hd2;
		hd2 = hd;
	}
	delete routeHead;
}


void two_two(firefly& f) {
	firefly temp;
	memcpy(&temp, &f, sizeof(firefly));
	for (int i = 0; i < NUMBER - 1; i++) {
		swap(temp.G[i], temp.G[i + 1]);
		enSimpleCode(temp);
		if (dominate(temp, f)==0) {
			memcpy(&f, &temp,sizeof(firefly));
		}
	}
}
void neibor_swa(firefly& f) {
	int maxT = 20;
	firefly temp;
	memcpy(&temp, &f, sizeof(firefly));
	for (int i = 0; i < maxT; i++)
	{
		int r1 = rand() % NUMBER;
		swap(temp.G[r1], temp.G[(r1 + 1) % NUMBER]);

		enSimpleCode(temp);
		if (dominate(temp, f) == 0) {
			memcpy(&f, &temp, sizeof(firefly));
		}
		else {
			memcpy(&temp, &f, sizeof(firefly));
		}
	}
}


void swa_one(firefly &f) {
	firefly temp;
	memcpy(&temp, &f, sizeof(firefly));
	int randNum = 20;
	for (int i = 0; i < randNum; i++) {
		int r1 = rand() % NUMBER;
		int r2 = rand() % NUMBER;
		while (r2 == r1) {//s1!=s2
			r2 = rand() % NUMBER;
		}

		swap(temp.G[r1], temp.G[r2]);
		enSimpleCode(temp);
		if (dominate(temp, f) == 0) {
			memcpy(&f, &temp, sizeof(firefly));
		}
		else {
			swap(temp.G[r1], temp.G[r2]);
			enSimpleCode(temp);
		}
	}
}


void swa(firefly& f) {
	firefly temp;
	int randNum = 20;
	for (int i = 0; i < randNum; i++) {
		srand(unsigned(rand()));
		memcpy(&temp, &f, sizeof(firefly));
		int r1 = rand() % NUMBER;
		int r2 = rand() % NUMBER;
		int len = 2+rand() % 2;
		while (r2 == r1) {//s1!=s2
			r2 = rand() % NUMBER;
		}
		for (int j = 0; j < len; j++) {
			swap(temp.G[(r1 + j) % NUMBER], temp.G[(r2 + j) % NUMBER]);
		}	
		S_H(temp);
		check(temp.G, s, h);//调整
		enSimpleCode(temp);
		if (dominate(temp, f) == 0) {
			memcpy(&f, &temp, sizeof(firefly));
		}
	}
}

void simpleSA(firefly& f) {
	firefly tempCode;
	memcpy(&tempCode, &f, sizeof(firefly));

	int outC = 20, inC = 50, oC = 0, iC = 0;
	double T0 = 0.1, lam = 0.95;
	double T = T0;
	for (int i = 0; i < outC; i++) {
		for (int j = 0; j < inC; j++) {
			int r1 = rand() % NUMBER;
			int r2 = rand() % NUMBER;
			while (r2 == r1) {//s1!=s2
				r2 = rand() % NUMBER;
			}
			swap(tempCode.G[r1], tempCode.G[r2]);
			/*if (r1 < r2)
				reverse(tempCode.G + r1, tempCode.G + r2);
			else
				reverse(tempCode.G + r2, tempCode.G + r1);*/

			enSimpleCode(tempCode);
			int deltaf = dominate(tempCode,f);

			if (deltaf == 0) {
				memcpy(&f, &tempCode,sizeof(firefly));
			}
			else {
				double r = rand() / (double)(RAND_MAX);
				if (r < exp(-deltaf / T)) {
					memcpy(&f, &tempCode, sizeof(firefly));
				}
				else swap(tempCode.G[r1], tempCode.G[r2]);
			}
		}
		T = lam * T0;
	}
}

int hammer_dis(int h1[NUMBER],int h2[NUMBER]) {
	int dis = NUMBER;
	for (int i = 0; i < NUMBER; i++) {
		if (h1[i] == h2[i]) dis--;
	}
	return dis;
}

void mut_swap_sub(firefly f, int i, int j, firefly& temp) {
	swap(f.G[i], f.G[j]);
	enSimpleCode(f);
	memcpy(&temp, &f, sizeof(firefly));
}

void mutation(firefly &f) {

	firefly bestf;
	memcpy(&bestf, &f, sizeof(firefly));
	firefly temp;
	int tag[101] = {};
	for (int i = 0; i < NUMBER; i++) {//第i个结点
		for (int j = 0; j < NUMBER; j++) {//对第i个结点进行遍历插入操作，取最佳位置
			if (j != i) {
				mut_swap_sub(f, i, j, temp);
				if (dominate(temp, bestf) == 0) {
					memcpy(&bestf, &temp, sizeof(firefly));
				}
			}
		}
		memcpy(&f, &bestf, sizeof(firefly));
	}
}

void mut_swap(firefly& f) { //交换到最合适的位置
	firefly bestf;
	memcpy(&bestf, &f, sizeof(firefly));
	firefly temp;
	int tag[101] = {};
	for (int i = 0; i < 10; i++) { //第i个结点
		srand(unsigned(rand()));
		int r = rand() % NUMBER;
		for (int j = 0; j < NUMBER; j++) { //对第i个结点进行遍历交换操作，取最佳位置
			if (j != i) {
				mut_swap_sub(f,i,j,temp);
				if (dominate(temp, bestf) == 0) {
					//changeCount++;
					memcpy(&bestf, &temp, sizeof(firefly));
				}
			}
		}
		memcpy(&f, &bestf, sizeof(firefly));
	}
}


void LS(firefly f1, firefly f2, firefly &bestf) {
	insert(f1);
	enSimpleCode(f1);
	insert(f2);
	enSimpleCode(f2);
	if (dominate(f1, f2) == 0) {
		memcpy(&bestf,&f1,sizeof(firefly));
	}
	else {
		memcpy(&bestf, &f2, sizeof(firefly));
	}
}

void interchange_operator(firefly &f) {
	firefly temp;

	for (int i = 0; i < 20; i++) {
		memcpy(&temp, &f, sizeof(firefly));
		int pairs = 1 + rand() % 5;
		for (int j = 0; j < pairs; j++) {
			int r1 = rand() % NUMBER;
			int r2 = rand() % NUMBER;
			while (r1 == r2) {
				r2 = rand() % NUMBER;
			}
			swap(temp.G[r1], temp.G[r2]);
		}
		enSimpleCode(temp);
		if(dominate(temp,f)==0) memcpy(&f, &temp, sizeof(firefly));
	}
}

void neibor_solution(firefly f, firefly &temfly) {
	int p1 = 0.7, p2 = 0.98;
	double r = rand() / (double)(RAND_MAX);

	if (r < p1) {//interchange_operator
		int randNum = 1 + rand() % 8;
		for (int i = 0; i < randNum; i++) {
			int s1 = rand() % NUMBER;
			int s2 = rand() % NUMBER;
			while (s2 == s1) {//s1!=s2
				s2 = rand() % NUMBER;
			}
			swap(f.G[s1], f.G[s2]);
		}
		memcpy(temfly.G, f.G, NUMBER * sizeof(int));
		enSimpleCode(temfly);
	}
	else if (r < p2) {
		int r1 = rand() % NUMBER;
		int r2 = rand() % NUMBER;
		int len = 1 + rand() % 5;
		while (r2 == r1) {//s1!=s2
			r2 = rand() % NUMBER;
		}
		for (int j = 0; j < len; j++) {
			swap(f.G[(r1 + j) % NUMBER], f.G[(r2 + j) % NUMBER]);
		}
		memcpy(temfly.G, f.G, NUMBER * sizeof(int));
		enSimpleCode(temfly);
	}
	else {//inverse_operator
		int r1 = rand() % NUMBER;
		int r2 = rand() % NUMBER;
		while (r2 == r1) {//s1!=s2
			r2 = rand() % NUMBER;
		}
		if (r1 < r2)
			reverse(f.G + r1, f.G + r2);
		else
			reverse(f.G + r2, f.G + r1);
		memcpy(temfly.G, f.G, NUMBER * sizeof(int));
		enSimpleCode(temfly);
	}
	mut_swap(temfly); 
	//insertAll(temfly);
	insert(temfly);
	//else {//shift_operator
	//	for (int k = 0; k < 5; k++) {
	//		LinkList L, copyL;
	//		listToLink(f, L);//顺序-->链式
	//		copyLink(L, copyL);

	//		//L中提取出单个节点
	//		int r = 1 + rand() % NUMBER; //单个节点位置[1,100]
	//		LNode* pr, * pf;
	//		pr = copyL;
	//		int i = 0;
	//		while (i != r - 1) {
	//			pr = pr->next;
	//			i++;
	//		}
	//		pf = pr;
	//		pr = pr->next;//提取出的节点
	//		pf->next = pr->next; //L中删去了pr

	//		//L中插入
	//		int r1 = rand() % NUMBER;//插入位置[0,99]
	//		LNode* p;
	//		p = copyL;
	//		int j = 0;
	//		do {
	//			if (j == r1) {
	//				pr->next = p->next;
	//				p->next = pr;
	//				break;
	//			}
	//			else {
	//				p = p->next;
	//				j++;
	//			}
	//		} while (1);

	//		linkToList(copyL, temfly.G);//链式-->顺序
	//		enSimpleCode(temfly);

	//		//释放L内存空间
	//		LNode* Lp1, * Lp2;
	//		Lp1 = L->next;
	//		Lp2 = L->next;
	//		free(L);
	//		while (Lp1 != NULL) {
	//			Lp1 = Lp2->next;
	//			free(Lp2);
	//			Lp2 = Lp1;
	//		}

	//		//释放copyL内存空间
	//		LNode* copyLp1, * copyLp2;
	//		copyLp1 = copyL->next;
	//		copyLp2 = copyL->next;
	//		free(copyL);
	//		while (copyLp1 != NULL) {
	//			copyLp1 = copyLp2->next;
	//			free(copyLp2);
	//			copyLp2 = copyLp1;
	//		}
	//	}
	//}
}

bool comp(firefly a, firefly b) {
	return a.fitness < b.fitness;
}
//GSO
bool GSOcomp(firefly a, firefly b) {
	return a.fluorescein > b.fluorescein;
}

double discode(int c1[],int c2[]) {//编码之间的平均距离
	double sum = 0;
	for (int i = 0; i < n; i++)
		sum = sum + dis[c1[i]][c2[i]];
	return sum / n;
}

void LocalSearch(firefly& fi) {
	if (rand() % 2 == 0)
		swa(fi);
	else opt2(fi);
}

int find(int arr[], int value) {
	int tag = 0;
	for (int i = 0; i < n;i++) {
		if (arr[i] == value) {
			tag = i;
			break;
		}
	}
	return tag;
}

void GSOMove(firefly fi, firefly fj, firefly& newf) {
	memcpy(&newf, &fi, sizeof(firefly));
	int st = 0;
	for (int i = 0; i < step; i++) {
		st = rand() % n;
		while (newf.G[st] == fj.G[st]) {
			st = (st + 1)%2000;
		}
		int temp = newf.G[st];
		newf.G[st] = fj.G[st];
		newf.G[find(newf.G, temp)] = temp;
	}
	S_H(newf);
	check(newf.G, s, h);//调整
	enSimpleCode(newf);
}

void randCode(firefly& fly) { //随机产生一天编码并解码
	for (int j = 0; j < n; j++) {
		G[j] = j + 1;
	}
	randomArr(G, n);	//打乱顺序
	S_H2(G);
	check(G, s, h);//调整
	for (int m = 0; m < n; m++)
		fly.G[m] = G[m];
	enSimpleCode(fly);
}

void gsofly(firefly fi, firefly fj, firefly& temfly) {
	//fj向fi飞行移动
	int count = NUMBER;//海明码距离
	double delta[NUMBER] = { 0 };	//每一维度之间的变化值
	firefly newfly;                 //移动后的萤火虫
	int fjCode[NUMBER] = { 0 };		//复制fj萤火虫编码，不影响原编码
	memcpy(fjCode, fj.G, NUMBER * sizeof(int));

	for (int i = 0; i < NUMBER; i++) {//计算每个位置变化值delta
		delta[i] = fabs(dis[fi.G[i]] - dis[fj.G[i]]);
		if (delta[i] == 0) {
			count--;
			newfly.G[i] = fi.G[i];//相同位置相同节点保留
			fjCode[i] = 0;
		}
	}
	
	int reserve = min(step, count);	//随机步长，继承较亮萤火虫结点位置数量
	for (int i = 0; i < reserve; i++) {//继承萤火虫fi中随机步长个结点
		int temp = 0;
		for (int j = 0; j < NUMBER; j++) {//寻找当前delta最大节点位置
			if (delta[j] >= delta[temp]) temp = j;
		}
		newfly.G[temp] = fi.G[temp];
		delta[temp] = 0;//置为0便于找下一个最大数

		fjCode[find(fjCode, fi.G[temp])] = 0;
		// for (int k2 = 0; k2 < NUMBER; k2++) {	//在萤火虫j的副本中，将已经继承过结点置0
			// if (fjCode[k2] == fi.G[temp]) { fjCode[k2] = 0; break; }
		// }
	}

	for (int i = 0,c = 0; i < NUMBER; i++){
		if (newfly.G[i] == 0) {
			while(fjCode[c]==0){//按顺序依次找到原萤火虫其他节点
				c++;
			}
			newfly.G[i] = fjCode[c++];
		}
	}
	S_H(newfly);
	check(newfly, s, h);
	enSimpleCode(newfly);
	memcpy(&temfly, &newfly,sizeof(firefly));
}
