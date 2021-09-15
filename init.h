//�жϻ�������
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

//������λ����
void CS_swap(){
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



//������

//���������
void get_R(int g[]){
	int j=0;
	for(int i=0;i<n;i++){
		if(g[i]<=R && j<R){//�������飬����������С��R����˵��Ϊ�ؿ����
			r_arry[j] = g[i];
			j++;
		}
	}
}
//�жϸñ���������̨�Ѷ��
int stacker(int p){
	int ddj = 0;
	if(cargo[p-1].x==1 || cargo[p-1].x==2)		//�����������Ϊ1��2����Ϊ�Ѷ��1
		ddj = 1;
	else if(cargo[p-1].x==3 || cargo[p-1].x==4)	//�����������Ϊ3��4����Ϊ�Ѷ��2
		ddj = 2;
	else if(cargo[p-1].x==5 || cargo[p-1].x==6)//�����������Ϊ5��6����Ϊ�Ѷ��3
		ddj = 3;
	else if(cargo[p-1].x==7 || cargo[p-1].x==8)//�����������Ϊ7��8����Ϊ�Ѷ��4
		ddj = 4;
	else if(cargo[p-1].x==10 || cargo[p-1].x==9)//�����������Ϊ9��10����Ϊ�Ѷ��5
		ddj = 5;
	else if(cargo[p-1].x==11 || cargo[p-1].x==12)//�����������Ϊ11��12����Ϊ�Ѷ��6
		ddj = 6;
	else{
		cout<<"ddj error!"<<endl;				//�����������λ������˵������
		ddj = 0;
	}
	return ddj;
}
//������ϻ��㵽�������ʱ��
void getT_load(int i,char type){
	//int n_load1 = R_n/fre; //���ϻ���1�����Ļ������� freΪÿ����һ��������������
	//int n_load2 = R_n - n_load1;//���ϻ���2�����Ļ������� 
		//�ж��Ƿ���ϻ���2����:
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
		if(type=='A'){//�������A���� 3���һ��
			if(temp_p==a_num){
				temp_p = 0;
				flag_R++;//����һ��
				send_t = t_R;//����ʱ��
			}
		}
		else{
			if(temp_p==b_num){//B���ͣ�5��һ��
				temp_p = 0;
				flag_R++;//����һ��
				send_t = t_R;
			}
		}
}
        
//����Ѷ������ţ����ص��öѶ����ʱ��
double getT(int ddj){
	switch(ddj){		//���ݵ���ͬ�Ѷ���ľ��룬���������Ѷ����ʱ��
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
	//write.open("Test.txt");//��ʾ��Ҫ�������������text.txt"����ļ��� ���û������ļ������Զ���������ļ�
	int p_R = 0;//�������±�
	for(int i =1;i<=R_n;i++){
		if(p_R>R)	//	��ֹ�����������Խ��
			break;
		if(an>R)	//	��ֹ�����������Խ��
			break;
        getT_load(i,'A');//�����ϻ������ı�ţ���1~R_n��ʼ�ϻ������A
        if(flag_R==2 && p_R<R){//�������� ��ʼ���㵽��Ѷ����ڵ�ʱ��
			flag_R = 0;	//����ǹ�0
            ddj = stacker(r[p_R]);//���������룬������Ѷ�����
			p_R++;
            get_t = send_t + getT(ddj);//���㵽��ʱ�� = ����ʱ��+����Ѷ����ʱ��
			//cout<<"get_t:"<<get_t<<endl;
        if(ddj==1){//�ж��Ƿ����ڶѶ��1
            //cout<<"The ddj is "<<ddj<<"\tThe num "<<p_R<<"\tstack arrive ddj time is "<<get_t<<endl;
            //write<<"The ddj is "<<ddj<<"\tThe num "<<p_R<<"\tstack arrive ddj time is "<<get_t<<endl;
				//cout<<1<<endl;
				a[an] = get_t;//д������a��
				an++;
                //write<<get_t<<endl;
                get_t = 0;//������ʱ�������0
				continue;//��߳���Ч�ʣ����ٽ���������ж�
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
	//write.close(); // �����Ϻ�ر�����ļ�
}

void randomArr(int G[],int len){    //������У�GΪ��������,lenΪ�������鳤��
    for(int i=0;i<len;i++){
        int sit = rand()%(len-1) +1;//���λ��
        int temp =G[i];		//������ǰλ�õı�������λ�õı���
        G[i] = G[sit];
        G[sit] = temp;
        //cout<<sit<<endl;
    }
}
//�춨ʱ��
void inspect(char type_inspect){//�����������
            switch(type_inspect){//���ݲ�ͬ�������ͣ����㲻ͬ�ļ춨ʱ��
                case 'a':
                    t_inspect = t_inspect_a * s_h;  //��a�ļ춨ʱ�䣨Сʱ��������� ��ֵ�� �춨ʱ��
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
//����ʱ��
double Walk_time(int y,int z){//���� y��z����
    float v1 = 2;//�Ѷ����ֱ�ƶ��ٶ�
    float v2 = 4;//�Ѷ��ˮƽ�ƶ��ٶ�
    float l = 0.5;//�� ����
    float h = 0.65;//���ܵ�һ����
    float d = 0.2;//��λ��ľ���
    int Yn = y;//y����
    int Zn = z;//z����
    float High_In = 0;//��ֱ�ƶ��ľ���
    float Long_In = 0;//ˮƽ�ƶ��ľ���
    float time_in_high = 0;//��ֱ�ƶ���ʱ��
    float time_in_long = 0;//ˮƽ�ƶ���ʱ��
    float time_in_run = 0;//�Ѷ���ƶ���ʱ��
    float time = 0;//�Ѷ���ƶ���ʱ�䣨������һ�����������ں������ԣ�
    High_In = Zn * h;//���㴹ֱ�ƶ��ľ���
    Long_In = Yn  * (l + d);//����ˮƽ�ƶ��ľ���
    time_in_high = High_In / v1;//���㴹ֱ�ƶ���ʱ��
    time_in_long = Long_In / v2;//����ˮƽ�ƶ���ʱ��
    time_in_run = max(time_in_high,time_in_long);//�Ѷ����ֱ�˶���ʱ����Ѷ��ˮƽ�ƶ���ʱ�� �������ʱ�伴Ϊ�Ѷ�����ƶ�ʱ��
    time = time_in_run;//��ֵ��time
    return time;//���ضѶ���˶���ʱ��
}
//���룬Ŀǰû���õ�
void insert_G(int G[],int sit,int value){  //���� ����ĳ�������в���һ��Ԫ�أ��������飬�����Ԫ�أ��Ͳ����λ�á�Ŀǰ�˺���û���õ�
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
//�ͼ�ǰh-k�����룬�ؿ��h-k�����룬�γ�1-1��Ӧ��ϵ��
void S_H2(int G[]){//�����������
    int j = 0,p=0;
    for(int i=0;i<n;i++){//������������
        if(cargo[G[i]-1].s1==0 && cargo[G[i]-1].s2==1 && G[i]>=R+1 && G[i]<=R+H-k){//���ձ����˳���жϱ����Ƿ����� �ͼ����,�Ҹ��ͼ��������ǰH-K
			s[j] = G[i];//���ñ���д�뵽�ͼ�������
			j++;//�ͼ������±�����1
		}
		else if(cargo[G[i]-1].s1==1 && cargo[G[i]-1].s2==0 && G[i]>=R+S+k+1 && G[i]<=R+S+H){//���ձ���˳���жϱ����Ƿ����ڻؿ���룬�һؿ�������ں�H-k
			h[p] = G[i];//���ñ���д�뵽�ؿ����
			p++;//�ؿ������±�����1
		}
    }		
}

//�ͼ�ǰh-k�����룬�ؿ��h-k�����룬�γ�1-1��Ӧ��ϵ��
void S_H(firefly f){//�ú�����S_H2�Ĺ���һ�£����������һ����Ⱥ
	int j = 0,p=0;
    for(int i=0;i<n;i++){
        if(cargo[f.G[i]-1].s1==0 && cargo[f.G[i]-1].s2==1 && f.G[i]>=R+1 && f.G[i]<=R+H-k){
			s[j] = f.G[i];
			j++;
		}
		else if(cargo[f.G[i]-1].s1==1 && cargo[f.G[i]-1].s2==0 && f.G[i]>=R+S+k+1 && f.G[i]<=R+S+H){
			h[p] = f.G[i];
			p++;
		}
    }		
}

//�ж�S�������Ӧ�Ļؿ������G[n]��ǰ���ϵ����� H����λ�ڶ�Ӧ���ͼ����֮ǰ����������λ�ã���֤S����ʼ��λ���������Ӧ��H����֮ǰ��
void check(int G[],int s[],int h[]){
    int temp = 0;
    int l = 0;//�ͼ���������±�
    for(int i=0;i<n;i++){
        if(R+1<=G[i] && R+H-k>=G[i]){//��G[]�У������Ԫ�����ڵ��ͼ�Ԫ��  
            for(;l<H-k;l++){  //��s��ȷ����Ԫ���±�
                if(s[l]==G[i]){	//��G�����������ҵ��ͼ����					
					for(int j=0;j<n;j++){   // ��G[n]�ҵ���s[l]��Ӧ��h[l]  �±��Ϊl
						if(G[j]==h[l]){
							if(i>j){        //���hλ��s֮ǰ������λ�á�
								temp = G[j];
								G[j] = G[i];
								G[i] = temp;
							}
							break;//���ҵ��ؿ���룬����ѭ��
						}
					}
					break;//�������ڶ����ͼ����
				}
			}	
        }
    }
}

double read(double TI,double TDI,int p,int nextp,int g1_H2[],int g2_H2[],int g3_H2[],int g4_H2[],int g5_H2[],int g6_H2[],int g1_th[],int g2_th[],int g3_th[],int g4_th[],int g5_th[],int g6_th[]){
    char type,next_type;//��ǰ����Ļ������ͣ���һ������Ļ�������
	int ddj=0;//�Ѷ�����
	int i=0;
    double wait_time = 0;//�ȴ�ʱ��
    double grab_time = 1.5;//ץȡʱ��
    double walk_time1 = 0;//����ʱ��1
    double place_time = 1.5;//����ʱ��
    double walk_time2 = 0;//����ʱ��2
	bool flag = false;
	//�жϵ�ǰ��ȡ�ı����������ֱ������ͣ�R��S��H��C
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
	//�ж���һ�������������ֻ�������
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
	//�����ǰ�������������ͼ����
    if(type =='S'){
        walk_time1 = Walk_time(cargo[p-1].y,cargo[p-1].z); //�Ѷ���ӵ�ǰλ���ƶ����ͼ�ڣ��˴�Ĭ���ͼ��Ϊ0,0
        if(next_type=='R'||next_type=='H')//�����һ��������������ؿ����
            walk_time2 = Walk_time(cargo[p-1].y,cargo[p-1].z);//***���޸�***�Ѷ������ƶ�����һ���������ʼλ�ã�Ҳ����0,0λ�ã��˴������ڿɸ��ݲ�ͬ�Ļؿ��ʲ���¥���öѶ���ƶ�����ͬ��λ�ã�
        else
            walk_time2 = Walk_time(abs(cargo[p-1].y-cargo[nextp-1].y),abs(cargo[p-1].z-cargo[nextp-1].z));//��������ͼ����⣬���ƶ����û���Ļ���λ��
        TI +=  grab_time + walk_time1 + place_time+ walk_time2;//��������ĶѶ���ܹ���ʱ��Ϊ �ȴ�ʱ��+��ȡʱ��+��������ʱ��+����ʱ��+���ߵ���һ�������ʱ��
		TDI =  grab_time + walk_time1 + place_time+ walk_time2 + TD[0];//�Ѷ��ʵ�ʹ���ʱ�� = �ܹ���ʱ��-�ȴ�ʱ��
		TD[0] = TDI;//��ʵ�ʹ���ʱ��д�뵽ʵ�ʹ��������У������������Ҫ�����������Ա���ÿһ̨�Ѷ����ʵ�ʹ���ʱ�䡣��ʱ��ÿ̨�Ѷ����ʵ�ʹ���ʱ����ӵ�TD[0]��
        //��ʼ���� �ͼ���� ����Ӧ�� �ؿ���� �� �ؿ�ʱ��
		for( i=0;i<H-k;i++){
            if(s[i]==p){//���ݵ�ǰ���룬�ҵ��� �ͼ�������� �е��±� i�����±�ɶ�Ӧ�� �ؿ����� �еĻؿ�����λ��
				ddj = stacker(h[i]);//�жϸûؿ����������̨�Ѷ��������
				switch (ddj)
				{
				case 1://����ǵ�һ̨�Ѷ������
					g1_H2[th1]=h[i];//���ûؿ����д�뵽�Ѷ��1�Ļؿ�������
					inspect(cargo[p-1].type);//���ݸ��ͼ����Ļ������ͣ�������ͼ�ʱ��
					g1_th[th1] = TI + t_inspect;//���ݼ춨ʱ�� �� ��ǰʱ�� ��������ؿ�ʱ�䣨�˴�����δ������
					th1++;//�Ѷ��1�� �ؿ�������� �� �ؿ�ʱ������ �±�����
					break;
				case 2:
					g2_H2[th2]=h[i];
					inspect(cargo[p-1].type);
					g2_th[th2] = TI + t_inspect;
					th2++;
					break;
				case 3:
					g3_H2[th3]=h[i];
					inspect(cargo[p-1].type);
					g3_th[th3] = TI + t_inspect;
					th3++;
					break;
				case 4:
					g4_H2[th4]=h[i];
					inspect(cargo[p-1].type);
					g4_th[th4] = TI + t_inspect;
					th4++;
					break;
				case 5:
					g5_H2[th5]=h[i];
					inspect(cargo[p-1].type);
					g5_th[th5] = TI + t_inspect;
					th5++;
					break;
				case 6:
					g6_H2[th6]=h[i];
					inspect(cargo[p-1].type);
					g6_th[th6] = TI + t_inspect;
					th6++;
					break;
				default:
					cout<<"read code ddj error!"<<endl;
					break;
				}
				//cout<<"------------"<<h[i]<<"------------"<<endl;
				hi[v2][1] = TI + t_inspect;//�ؿ�ʱ��д�뵽hi[v2][1]��
				hi[v2][0] = h[i];//�ؿ���� д�뵽hi[v2][0]��
				v2++;//v2����
                th[i] = TI + t_inspect;//�ؿ�ʱ��ͳһд�뵽һ��������
				break;
			}
        }
    }
    switch (type){
        case 'R'://�ñ���Ϊ������
            if(a[ai]<=TI)//�жϵȴ�ʱ�� ����a[ai]�д�ŵ����ʱ�������δ�С�����
                wait_time = 0;
            else
                wait_time = a[ai] - TI;
			ai++;//���� a�±�����
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
            for(i=0;i<H-k;i++){//��h[]���ҵ��±�
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
            break;
        default:
            cout<<"read error!"<<endl;
            break;
    }
    return TI;//���ضѶ����ȡ�ñ����ʱ��
}
//�ּ��������
void Storing_num(firefly f){//������Ⱥ
    int p=0;
	char g=0;
	g1_s = 0,g2_s = 0,g3_s = 0,g4_s = 0,g5_s = 0,g6_s = 0;
	g1_h = 0,g2_h = 0,g3_h = 0,g4_h = 0,g5_h = 0,g6_h = 0;
	g1_n=0;g2_n=0;g3_n=0;g4_n=0;g5_n=0;g6_n=0;
    for(int i=0;i<n;i++){//�������л�λ
        p = cargo[f.G[i]-1].x;//������Ϣ
		g = judge_type(f.G[i]-1);//������� R��S��H��C
        switch (p)//�ж�������̨�Ѷ��
        {
        case 1:
        case 2://����1�ŶѶ��
			if(g=='S')//�ͼ�
				g1_s++;
			else if(g=='H')//�ؿ�
				g1_h++;
            g1_n++;//�Ѷ��1������������
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
//�ּ����
void Storing(firefly f,int g1[],int g2[],int g3[],int g4[],int g5[],int g6[],int g1_S[],int g2_S[],int g3_S[],int g4_S[],int g5_S[],int g6_S[],int g1_H[],int g2_H[],int g3_H[],int g4_H[],int g5_H[],int g6_H[]){
	j1=0,j2=0,j3=0,j4=0,j5=0,j6=0;
	int g1s=0,g2s=0,g3s=0,g4s=0,g5s=0,g6s=0;
	int g1h=0,g2h=0,g3h=0,g4h=0,g5h=0,g6h=0;
    int p=0;
	char g=0;
    for(int i=0;i<n;i++){//������������
        p = cargo[f.G[i]-1].x;//������Ϣ
		g = judge_type(f.G[i]-1);//������� R��S��H��C
        switch (p)//�жϱ���������̨�Ѷ��
        {
        case 1:
        case 2://���ڶѶ��1
			if(g=='S'){//�����ͼ����
				g1_S[g1s] = f.G[i];//���ñ���д��Ѷ��1���ͼ�����
				g1s++;//�ͼ������±�����1
			}
			else if(g=='H'){//���ڻؿ����
				g1_H[g1h] = f.G[i];//�ñ���д��Ѷ��1�Ļؿ�����
				g1h++;//�ؿ������±�����1
			}
            g1[j1] = f.G[i];//�ñ���д�뵽�Ѷ��1�� ����������
            j1++;//�Ѷ��1�ı�����������1
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

//����� Ŀǰû���õ�
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

//�����Ӧ��ֵ���������*0.8 + �Ѷ��ʵ�ʹ���ʱ��*0.2��/60
int max2(double T[]){
	int i,j;
    double temp,G_fintess;
    for(i=0;i<5;i++)//��������Ԫ�أ��Ӵ�С����
        for(j=0;j<5-i;j++){
            if(T[j+1]>T[j]){
            temp=T[j+1];
            T[j+1]=T[j];
            T[j]=temp;
            }
        }
	//T[0] = T[0]/60.0;
	G_fintess = T[0]*0.95 + TD[0]*0.05;//��Ӧ��ֵ���㣬��Ȩ��
	//G_fintess = G_fintess/60.0;//����60 ����ת��Ϊ����
	//T[0] = T[0]/60.0;//�Ѷ��ʵ�ʹ���ʱ�� ����
	//return T[0];
    return G_fintess;
}
void read_ddj(int gi_H[],int ddj,int gi[],int g1_H2[],int g2_H2[],int g3_H2[],int g4_H2[],int g5_H2[],int g6_H2[],int g1_th[],int g2_th[],int g3_th[],int g4_th[],int g5_th[],int g6_th[]){
	switch (ddj)//�ж϶Ѷ�����
	{
	case 1:
		while(gi_H[h1]!=gi[j1]){//���϶�ȡ��ֱ����ȡ��g1�е�һ��H����Ϊֹ
			if(j1==(g1_n-1)){//�����ȡ���öѶ�������һλ���룬����һ�������뵱ǰ������ͬ
				T1 = read(T1,TD1,gi[j1],gi[j1],g1_H2,g2_H2,g3_H2,g4_H2,g5_H2,g6_H2,g1_th,g2_th,g3_th,g4_th,g5_th,g6_th);//��ȡ����
				j1++;//�Ѷ�������������1
			}
			else if(j1<(g1_n-1)){//���������һλ����
				T1 = read(T1,TD1,gi[j1],gi[j1+1],g1_H2,g2_H2,g3_H2,g4_H2,g5_H2,g6_H2,g1_th,g2_th,g3_th,g4_th,g5_th,g6_th);
				j1++;
			}
			if(j1>g1_n-1)//����öѶ���ı���ȫ����ȡ���
				break;//����ѭ��
		}
		h1++;
		break;

	case 2:
		while(gi_H[h2]!=gi[j2]){ //���϶�ȡ��ֱ����ȡ��g2�е�һ��H����Ϊֹ
			if(j2==(g2_n-1)){
				T1 = read(T2,TD2,gi[j2],gi[j2],g1_H2,g2_H2,g3_H2,g4_H2,g5_H2,g6_H2,g1_th,g2_th,g3_th,g4_th,g5_th,g6_th);
				j2++;
			}
			else if(j2<(g2_n-1)){
				T2 = read(T2,TD2,gi[j2],gi[j2+1],g1_H2,g2_H2,g3_H2,g4_H2,g5_H2,g6_H2,g1_th,g2_th,g3_th,g4_th,g5_th,g6_th);
				j2++;
			}	
			if(j2>g2_n-1)
				break;
		}
		h2++;	
		break;

	case 3:
		while(gi_H[h3]!=gi[j3]){ //���϶�ȡ��ֱ����ȡ��g3�е�һ��H����Ϊֹ
			if(j3==(g3_n-1)){
				T3 = read(T3,TD3,gi[j3],gi[j3],g1_H2,g2_H2,g3_H2,g4_H2,g5_H2,g6_H2,g1_th,g2_th,g3_th,g4_th,g5_th,g6_th);
				j3++;
			}
			else if(j3<(g3_n-1)){
				T3 = read(T3,TD3,gi[j3],gi[j3+1],g1_H2,g2_H2,g3_H2,g4_H2,g5_H2,g6_H2,g1_th,g2_th,g3_th,g4_th,g5_th,g6_th);
				j3++;
			}	
			if(j3>g3_n-1)
				break;
		}	
		h3++;
		break;

	case 4:
		while(gi_H[h4]!=gi[j4]){ //���϶�ȡ��ֱ����ȡ��g4�е�һ��H����Ϊֹ
			if(j4==(g4_n-1)){
				T4 = read(T4,TD4,gi[j4],gi[j4],g1_H2,g2_H2,g3_H2,g4_H2,g5_H2,g6_H2,g1_th,g2_th,g3_th,g4_th,g5_th,g6_th);
				j4++;
			}
			else if(j4<(g4_n-1)){
				T4 = read(T4,TD4,gi[j4],gi[j4+1],g1_H2,g2_H2,g3_H2,g4_H2,g5_H2,g6_H2,g1_th,g2_th,g3_th,g4_th,g5_th,g6_th);
				j4++;
			}	
			if(j4>g4_n-1)
				break;
		}
		h4++;
		break;

	case 5:
		while(gi_H[h5]!=gi[j5]){ //���϶�ȡ��ֱ����ȡ��g5�е�һ��S����Ϊֹ
			if(j5==(g5_n-1)){
				T5 = read(T5,TD5,gi[j5],gi[j5],g1_H2,g2_H2,g3_H2,g4_H2,g5_H2,g6_H2,g1_th,g2_th,g3_th,g4_th,g5_th,g6_th);
				j5++;
			}
			else if(j5<(g5_n-1)){
				T5 = read(T5,TD5,gi[j5],gi[j5+1],g1_H2,g2_H2,g3_H2,g4_H2,g5_H2,g6_H2,g1_th,g2_th,g3_th,g4_th,g5_th,g6_th);
				j5++;
			}	
			if(j5>g5_n-1)
				break;
		}
		h5++;
		break;

	case 6:
		while(gi_H[h6]!=gi[j6]){ //���϶�ȡ��ֱ����ȡ��g6�е�һ��S����Ϊֹ
			if(j6==(g6_n-1)){
				T6 = read(T6,TD6,gi[j6],gi[j6],g1_H2,g2_H2,g3_H2,g4_H2,g5_H2,g6_H2,g1_th,g2_th,g3_th,g4_th,g5_th,g6_th);
				j6++;
			}
			else if(j6<(g6_n-1)){
				T6 = read(T6,TD6,gi[j6],gi[j6+1],g1_H2,g2_H2,g3_H2,g4_H2,g5_H2,g6_H2,g1_th,g2_th,g3_th,g4_th,g5_th,g6_th);
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
//�ж��Ƿ��������
void decide_swap(firefly& f,int gi[],int gi_H2[],int gi_th[],int gi_H[],int thi,int p,int gi_h,int hj,int gi_n){//hj��ʾ�Ѷ����ȡ�ĵ�ǰ�ؿ��������
	int u1=0,u2=0,temp=0;//u1��u2��ʾ��Ҫ����������±�
	int p1 = 0;
	p1 = hi[v-1][0];//ʱ����̵Ļؿ����
	int ddj =  stacker(p1);//�ж����ʱ��ؿ����ĶѶ�����
	int p2=0;//Ҫ�����ı���
		for(int i=hj-1;i<thi;i++){//�Ӷ�ȡ����ǰ�ؿ�������� ��ʼ �����������ͼ����ƥ��Ļؿ��������Ϊֹ
			if(p1==gi_H2[hj-1])break;//����Ҫ����
			else{//��Ҫ����
				p2 = gi_H2[hj-1];//���һλ�Ļؿ���뽻��
				for(int j=0;j<n;j++){
					if(f.G[j]==p1){
						u1 = j;
						continue;
					}
				if(f.G[j]==p2){
					u2 = j;
					continue;
				}
				if(u1!=0 && u2!=0)
					break;
				}
				//��G�н���λ��
				temp = f.G[u1];
				f.G[u1] = f.G[u2];
				f.G[u2] = temp;
				u1=0,u2=0;
				//��gi_h�н���
				for(int j=0;j<gi_h;j++){
					if(gi_H[j]==p1){
						u1 = j;
						continue;
					}
				if(gi_H[j]==p2){
					u2 = j;
					continue;
				}
				if(u1!=0 && u2!=0)
					break;
				}
				temp = gi_H[u1];
				gi_H[u1] = gi_H[u2];
				gi_H[u2] = temp;
				u1=0,u2=0;
				
				gi_H2[hj-1] = p1;//�滻��gi_H2�еı���
				//��gi�н���
				for(int j=0;j<gi_n;j++){
					if(gi[j]==p1){
						u1 = j;
						continue;
					}
				if(gi[j]==p2){
					u2 = j;
					continue;
				}
				if(u1!=0 && u2!=0)
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
//�ҵ�ʱ����̵Ļؿ����
int min_h(){
	int Th = th1+th2+th3+th4+th5+th6;//�����Ѷ�ȡ�ͼ���������
    int i,j,p=0,sit=0;
    double temp;
	for( i=v;i<Th-1;i++){//��ʼv��0����0��ʼѭ�����������Ѷ�ȡ���ͼ�����Ϊֹ����ʾ���� �����Ѷ�ȡ�ͼ�������� �� �ؿ���� �� �ؿ�ʱ��
	//��Ҫ�������Աȣ���hi[][]������ݻؿ�ʱ��������򣬲���������ʱ�����Ӧ�Ļؿ����Ҳ���Żؿ�ʱ��������򣬱�֤hi[v][0]ʼ��Ϊ �������лؿ��������ʱ��
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
	v++;//���ζ�ȡ����̻ؿ����Ļؿ�ʱ�����ҵ����ƶ�����һλ���˺�λ��v֮ǰ�Ļؿ���벻�ٲ���Ƚ�
	return hi[v-1][0];//������̻ؿ�ʱ��Ļؿ����
}
//������Ӧ��ֵ
void Fintess(firefly& f,int g1[],int g2[],int g3[],int g4[],int g5[],int g6[],int g1_H[],int g2_H[],int g3_H[],int g4_H[],int g5_H[],int g6_H[],int g1_H2[],int g2_H2[],int g3_H2[],int g4_H2[],int g5_H2[],int g6_H2[],int g1_th[],int g2_th[],int g3_th[],int g4_th[],int g5_th[],int g6_th[]){
	T1=0,T2=0,T3=0,T4=0,T5=0,T6=0;
	TD1=0,TD2=0,TD3=0,TD4=0,TD5=0,TD6=0;
	j1=0,j2=0,j3=0,j4=0,j5=0,j6=0;
	h1=0,h2=0,h3=0,h4=0,h5=0,h6=0;
	th1=0,th2=0,th3=0,th4=0,th5=0,th6=0;
	int ddj=0,p=0;
	v = 0;v2=0;
	TD[0]=0;
		//���նѶ��˳�����ζ�ȡ���룬ֱ����ȡ���ؿ����Ϊֹ
		read_ddj(g1_H,1,g1,g1_H2,g2_H2,g3_H2,g4_H2,g5_H2,g6_H2,g1_th,g2_th,g3_th,g4_th,g5_th,g6_th);
		read_ddj(g2_H,2,g2,g1_H2,g2_H2,g3_H2,g4_H2,g5_H2,g6_H2,g1_th,g2_th,g3_th,g4_th,g5_th,g6_th);
		read_ddj(g3_H,3,g3,g1_H2,g2_H2,g3_H2,g4_H2,g5_H2,g6_H2,g1_th,g2_th,g3_th,g4_th,g5_th,g6_th);
		read_ddj(g4_H,4,g4,g1_H2,g2_H2,g3_H2,g4_H2,g5_H2,g6_H2,g1_th,g2_th,g3_th,g4_th,g5_th,g6_th);
		read_ddj(g5_H,5,g5,g1_H2,g2_H2,g3_H2,g4_H2,g5_H2,g6_H2,g1_th,g2_th,g3_th,g4_th,g5_th,g6_th);
		read_ddj(g6_H,6,g6,g1_H2,g2_H2,g3_H2,g4_H2,g5_H2,g6_H2,g1_th,g2_th,g3_th,g4_th,g5_th,g6_th);
		
		//void decide_swap(firefly& f,int gi_H2[],int gi_th[],int gi_H[],int thi,int p,int gi_h,int hi)
		for(int i=0;i<H-k-6;i++){
			p = min_h();//��̻ؿ�ʱ��Ļؿ����
			if(p==9999)
				break;
			ddj = stacker(cargo[p-1].x);//��ȡ�ñ���ĶѶ�����
		switch (ddj)//�ж� ��̻ؿ�ʱ��Ļؿ����� �Ѷ�����
		{
		case 1://�����1�ŶѶ���������ж��Ƿ���Ҫ�����ؿ�����Ϊֹ���ٶ����϶�ȡ1�ŶѶ���ı��룬ֱ����ȡ���ؿ����Ϊֹ
			decide_swap(f,g1,g1_H2,g1_th,g1_H,th1,p,g1_h,h1,g1_n);//�����ؿ����λ��
			read_ddj(g1_H,1,g1,g1_H2,g2_H2,g3_H2,g4_H2,g5_H2,g6_H2,g1_th,g2_th,g3_th,g4_th,g5_th,g6_th);//��ȡ���룬ֱ���ؿ����
			break;//���������������̻ؿ�ʱ�� 
		case 2:
			decide_swap(f,g2,g2_H2,g2_th,g2_H,th2,p,g2_h,h2,g2_n);
			read_ddj(g2_H,2,g2,g1_H2,g2_H2,g3_H2,g4_H2,g5_H2,g6_H2,g1_th,g2_th,g3_th,g4_th,g5_th,g6_th);
			break;
		case 3:
			decide_swap(f,g3,g3_H2,g3_th,g3_H,th3,p,g3_h,h3,g3_n);
			read_ddj(g3_H,3,g3,g1_H2,g2_H2,g3_H2,g4_H2,g5_H2,g6_H2,g1_th,g2_th,g3_th,g4_th,g5_th,g6_th);
			break;
		case 4:
			decide_swap(f,g4,g4_H2,g4_th,g4_H,th4,p,g4_h,h4,g4_n);
			read_ddj(g4_H,4,g4,g1_H2,g2_H2,g3_H2,g4_H2,g5_H2,g6_H2,g1_th,g2_th,g3_th,g4_th,g5_th,g6_th);
			break;
		case 5:
			decide_swap(f,g5,g5_H2,g5_th,g5_H,th5,p,g5_h,h5,g5_n);
			read_ddj(g5_H,5,g5,g1_H2,g2_H2,g3_H2,g4_H2,g5_H2,g6_H2,g1_th,g2_th,g3_th,g4_th,g5_th,g6_th);
			break;
		case 6:
			decide_swap(f,g6,g6_H2,g6_th,g6_H,th6,p,g6_h,h6,g6_n);
			read_ddj(g6_H,6,g6,g1_H2,g2_H2,g3_H2,g4_H2,g5_H2,g6_H2,g1_th,g2_th,g3_th,g4_th,g5_th,g6_th);
			break;
		default:
			cout<<"Fintess decide_swap error!"<<endl;
			break;
		}
	}
	
//�ж�6�������б����Ƿ�ȫ����ȡ���
	if(j1+j2+j3+j4+j5+j6==n){
		T[0] = T1;T[1] = T2;T[2] = T3;T[3] = T4;T[4] = T5;T[5] = T6;
		f.fitness=max2(T);
	}
	if(j1<g1_n){
		while(j1!=g1_n){
			if(j1==(g1_n-1)){
				T1 = read(T1,TD1,g1[j1],g1[j1],g1_H2,g2_H2,g3_H2,g4_H2,g5_H2,g6_H2,g1_th,g2_th,g3_th,g4_th,g5_th,g6_th);
				j1++;
			}
			else if(j1<(g1_n-1)){
				T1 = read(T1,TD1,g1[j1],g1[j1+1],g1_H2,g2_H2,g3_H2,g4_H2,g5_H2,g6_H2,g1_th,g2_th,g3_th,g4_th,g5_th,g6_th);
				j1++;
			}				
		}
	}

	if(j2<g2_n){
		while(j2!=g2_n){
			if(j2==(g2_n-1)){
				T2 = read(T2,TD2,g2[j2],g2[j2],g1_H2,g2_H2,g3_H2,g4_H2,g5_H2,g6_H2,g1_th,g2_th,g3_th,g4_th,g5_th,g6_th);
				j2++;
			}
			else if(j2<(g2_n-1)){
				T2 = read(T2,TD2,g2[j2],g2[j2+1],g1_H2,g2_H2,g3_H2,g4_H2,g5_H2,g6_H2,g1_th,g2_th,g3_th,g4_th,g5_th,g6_th);
				j2++;
			}				
		}
	}

	if(j3<g3_n){  
		while(j3!=g3_n){ 
			if(j3==(g3_n-1)){
				T3 = read(T3,TD3,g3[j3],g3[j3],g1_H2,g2_H2,g3_H2,g4_H2,g5_H2,g6_H2,g1_th,g2_th,g3_th,g4_th,g5_th,g6_th);
				j3++;
			}
			else if(j3<(g3_n-1)){
				T3 = read(T3,TD3,g3[j3],g3[j3+1],g1_H2,g2_H2,g3_H2,g4_H2,g5_H2,g6_H2,g1_th,g2_th,g3_th,g4_th,g5_th,g6_th);
				j3++;
			}	
		}	
	}

	if(j4<g4_n){  
		while(j4!=g4_n){ 
			if(j4==(g4_n-1)){
				T4 = read(T4,TD4,g4[j4],g4[j4],g1_H2,g2_H2,g3_H2,g4_H2,g5_H2,g6_H2,g1_th,g2_th,g3_th,g4_th,g5_th,g6_th);
				j4++;
			}
			else if(j4<(g4_n-1)){
				T4 = read(T4,TD4,g4[j4],g4[j4+1],g1_H2,g2_H2,g3_H2,g4_H2,g5_H2,g6_H2,g1_th,g2_th,g3_th,g4_th,g5_th,g6_th);
				j4++;
			}	
		}	
	}

	if(j5<g5_n){  
		while(j5!=g5_n){ 
			if(j5==(g5_n-1)){
				T5 = read(T5,TD5,g5[j5],g5[j5],g1_H2,g2_H2,g3_H2,g4_H2,g5_H2,g6_H2,g1_th,g2_th,g3_th,g4_th,g5_th,g6_th);
				j5++;
			}
			else if(j5<(g5_n-1)){
				T5 = read(T5,TD5,g5[j5],g5[j5+1],g1_H2,g2_H2,g3_H2,g4_H2,g5_H2,g6_H2,g1_th,g2_th,g3_th,g4_th,g5_th,g6_th);
				j5++;
			}	
		}	
	}

	if(j6<g6_n){  
		while(j6!=g6_n){ 
			if(j6==(g6_n-1)){
				T6 = read(T6,TD6,g6[j6],g6[j6],g1_H2,g2_H2,g3_H2,g4_H2,g5_H2,g6_H2,g1_th,g2_th,g3_th,g4_th,g5_th,g6_th);
				j6++;
			}
			else if(j6<(g6_n-1)){
				T6 = read(T6,TD6,g6[j6],g6[j6+1],g1_H2,g2_H2,g3_H2,g4_H2,g5_H2,g6_H2,g1_th,g2_th,g3_th,g4_th,g5_th,g6_th);
				j6++;
			}	
		}	
	}


	T[0] = T1;T[1] = T2;T[2] = T3;T[3] = T4;T[4] = T5;T[5] = T6;
	f.fitness=max2(T);
}
//
//��ʼ����Ⱥ
void getPerm(firefly fly[flyNum])//ÿһ����һ��·��  �����ü���G
{	
	//R_t(a);
	//srand(6);
	srand((double)clock());//�����������
	for(int i=0;i<flyNum;i++){
		for(int j=0;j<n;j++){
			G[j] = j+1;
		}
		randomArr(G,n);	//����˳��
		S_H2(G);
        check(G,s,h);//����
        for(int m=0;m<n;m++)//д�뵽��Ⱥ
			fly[i].G[m] =G[m];
	}
/*
	for(int i=0;i<flyNum;i++){
		for(int j=0;j<n;j++){
			cout<<fly[i].G[j]<<",";
			}cout<<endl;cout<<fly[i].fitness<<endl;}
*/
}
//��������
void enSimpleCode(firefly& f) {
	flag_R = 0;
	for(int i=0;i<R;i++)
		a[i] = 0;
	t_R = 0;
	for(int i=0;i<6;i++){
		T[i] = 0;
		TD[i] = 0;
	}
	for(int i=0;i<H-k;i++){
		th[i] = 0;
		hi[i][0]=9999;
		hi[i][1]=0;
	}
	for(int i=0;i<R;i++){
		r_arry[i] = 0;}
	int b1 = INT32_MAX;
	ai = 0;
	//��һ��������н���//G
	S_H(f);//�ͼ�ǰh-k�����룬�ؿ��h-k�����룬�γ�1-1��Ӧ��ϵ��
	get_R(f.G);
	R_Test(r_arry);
/*	
	for(int i=0;i<R;i++){
		cout<<a[i]<<endl;
	}
	cout<<"---------"<<endl;
*/	
	//cout<<endl;
	Storing_num(f);
	int g1_S[g1_s],g2_S[g2_s],g3_S[g3_s],g4_S[g4_s],g5_S[g5_s],g6_S[g6_s];//�ͼ�����ּ�6̨�Ѷ��
	int g1_H[g1_h],g2_H[g2_h],g3_H[g3_h],g4_H[g4_h],g5_H[g5_h],g6_H[g6_h];//�ؿ�����ּ�6̨�Ѷ��
	int g1_th[g1_h],g2_th[g2_h],g3_th[g3_h],g4_th[g4_h],g5_th[g5_h],g6_th[g6_h];//6̨�Ѷ���Ļؿ������ʱ��
	int g1[g1_n],g2[g2_n],g3[g3_n],g4[g4_n],g5[g5_n],g6[g6_n];//����ּ�6̨�Ѷ��
	int g1_H2[g1_h],g2_H2[g2_h],g3_H2[g3_h],g4_H2[g4_h],g5_H2[g5_h],g6_H2[g6_h];//�����ͼ����񽫻ؿ�������䵽��Ӧ�ĶѶ��
	for(int i=0;i<g1_h;i++){g1_th[i]=0;g1_H2[i]=0;}
	for(int i=0;i<g2_h;i++){g2_th[i]=0;g2_H2[i]=0;}
	for(int i=0;i<g3_h;i++){g3_th[i]=0;g3_H2[i]=0;}
	for(int i=0;i<g4_h;i++){g4_th[i]=0;g4_H2[i]=0;}
	for(int i=0;i<g5_h;i++){g5_th[i]=0;g5_H2[i]=0;}
	for(int i=0;i<g6_h;i++){g6_th[i]=0;g6_H2[i]=0;}

	Storing(f,g1,g2,g3,g4,g5,g6,g1_S,g2_S,g3_S,g4_S,g5_S,g6_S,g1_H,g2_H,g3_H,g4_H,g5_H,g6_H);
	//f.fitness=Fintess(f,g1,g2,g3,g4,g5,g6,g1_H,g2_H,g3_H,g4_H,g5_H,g6_H,g1_H2,g2_H2,g3_H2,g4_H2,g5_H2,g6_H2,g1_th,g2_th,g3_th,g4_th,g5_th,g6_th);
	Fintess(f,g1,g2,g3,g4,g5,g6,g1_H,g2_H,g3_H,g4_H,g5_H,g6_H,g1_H2,g2_H2,g3_H2,g4_H2,g5_H2,g6_H2,g1_th,g2_th,g3_th,g4_th,g5_th,g6_th);
	f.fluorescein = (1-rou)*f.fluorescein + gamma / f.fitness;

}

void enCode(firefly fly[flyNum]) {
	//�����Լ��ķ����� ��ʼ��Ⱥ �е�ÿ��������н��룬�����Ŀ�꺯��
	//��д��һ������Ľ��룬��ѭ������
		for(int i=0;i<6;i++){
			T[i] = 0;
			TD[i] = 0;
		}
		for(int i=0;i<H-k;i++){
			th[i] =0;
			hi[i][0]=9999;
			hi[i][1]=0;
		}
		
		for(int i=0;i<flyNum;i++){
			enSimpleCode(fly[i]);
			//cout<<fly[0].G[1999];
		}
}


int dominate(firefly f1, firefly f2) {
	if (f1.fitness <= f2.fitness)
		return 0;//f1֧��f2
	else 
		return 1;//f2֧��f1
}


//ө���fj��ө���fi�����ƶ�
void flyMove(firefly fi, firefly fj, firefly& temfly) {

	double beta2 = 0;//ө����������
	int count = NUMBER;//ͳ�Ʊ�������ά�ȱ仯ֵ��Ϊ0�ĸ���
	double delta[NUMBER] = { 0 };//ÿһά��֮��ı仯ֵ
	double rij2 = 0;//ө���֮��ѿ��������ƽ��
	int passCount = 0;//�̳н���ө�����λ������
	int movedfly[NUMBER] = { 0 };//�ƶ����ө���,��ʼ��Ϊ0

	for (int i = 0; i < NUMBER; i++)
		rij2 += pow(fi.G[i] - fj.G[i], 2);

	beta2 = 1 * exp(-gamma * rij2);

	for (int i = 0; i < NUMBER; i++) {//����仯ֵdelta
		//delta[i] = beta * nodeDis[fi.G[i]][fj.G[i]]; 
		//delta[i] = beta2 * fabs(fi.G[i] - fj.G[i]);
		delta[i] = beta2 * fabs(dis[fi.G[i]] - dis[fj.G[i]]);
		if (delta[i] == 0) count--;
	}

	int fjCopy[NUMBER] = { 0 };//����ө�����룬Ϊ�˲�Ӱ��ԭ����ө���
	memcpy(fjCopy, fj.G, NUMBER * sizeof(int));

	//passCount = floor(beta2* count); //����ȡ��
	passCount = step;//������������̳нڵ���Ŀ
	for (int i = 0; i < passCount; i++) {//�̳�ө���fi�н��
		int temp = 0;
		for (int j = 0; j < NUMBER; j++) {
			if (delta[j] >= delta[temp]) temp = j;
		}
		movedfly[temp] = fi.G[temp];
		delta[temp] = 0;//��Ϊ0��������һ���������

		for (int k2 = 0; k2 < NUMBER; k2++) {	//��ө���j�ĸ����У����Ѿ��̳й���ĵ���0
			if (fjCopy[k2] == movedfly[temp]) { fjCopy[k2] = 0; break; }
		}
	}

	int k2 = 0;
	int noneZero[NUMBER] = { 0 };//�洢ө���fj�����½��
	for (int i = 0; i < NUMBER; i++) {
		if (fjCopy[i] != 0) noneZero[k2++] = fjCopy[i];
	}

	//��ө���j��������㰴��˳�����������ƶ���ı�����
	int m = 0;
	for (int i = 0; i < NUMBER; i++)
		if (movedfly[i] == 0) movedfly[i] = noneZero[m++];
	firefly movefly;
	memcpy(movefly.G, movedfly, NUMBER * sizeof(int));
	S_H(movefly);
	check(movefly.G, s, h);
	enSimpleCode(movefly);
	memcpy(&temfly, &movefly,sizeof(firefly));
}



//ө����������ʱ������Ŷ�
void randWalk2(firefly ff, firefly temfly) {//����Ϊө���
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
void opt2(firefly& f) {//����
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
		check(temp.G, s, h);//����
		enSimpleCode(temp);
		if (dominate(temp,f)==0) {
			memcpy(&f, &temp,sizeof(firefly));
		}
	}
}



void rand_opt2(firefly& f) { //��ͻ��
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

void linkToList(LinkList L,int G[NUMBER]) {//��ʽ�洢ת����˳��洢
	LNode * p;
	p = L->next;
	for (int i = 0; i < NUMBER; i++) {
		G[i] = p->data;
		p = p->next;
	}
}

void listToLink(firefly f,LinkList &L) { //˳��洢ת������ʽ�洢
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
		pf->next = p; //����Ľ��������
		pf = p;
		pf->next = p->next;
	}
}

void insertAll_sub(LinkList copyL, int r, int r1, firefly &bestfly) {//r(r>=1)�����ڵ�λ��,r1(r1>=0)����λ��
	//L����ȡ�������ڵ�
	LNode* pr, * pf;
	pr = copyL;
	int i = 0;
	while (i != r - 1) {
		pr = pr->next;
		i++;
	}
	pf = pr;
	pr = pr->next;	//��ȡ���Ľڵ�
	pf->next = pr->next;	//L��ɾȥ��pr
	pr->next = NULL;

	//L�в���
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
	//linkToList(copyL, newf.G);//��ʽ-->˳��
	enSimpleCode(newf);
	if (dominate(newf, bestfly) == 0) {
		memcpy(&bestfly, &newf, sizeof(firefly));
	}
	else {
		//��ԭ
		p->next = pr->next;
		pr->next = pf->next;
		pf->next = pr;
	}
}

void releasePoint(LinkList &L) {//�ͷ�L�ڴ�ռ�
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

void insert(firefly &f) { //ȡ����������β���
	LinkList L, copyL;
	listToLink(f,L);	//˳��-->��ʽ

	firefly bestf;
	memcpy(&bestf, &f, sizeof(firefly));
	for (int i = 0; i <= 20; i++) { //[1,100]ȡ������
		srand(unsigned(rand()));
		int r = 1 + rand() % NUMBER;
		for (int j = 0; j < NUMBER; j++) { //[0,99]��β���
			if (j != i) {
				insertAll_sub(L, r, j, bestf);
			}
		}
	}
	memcpy(&f, &bestf, sizeof(firefly));
	releasePoint(L);
	//releasePoint(copyL);
	//LNode* t; //���:˳��-��ʽ�洢
	//t = copyL->next;
	//while (t != NULL) { 
	//	cout << t->data <<"--";
	//	t = t->next;
	//}
	//cout <<endl;

	//int G[NUMBER] = {};//���:��ʽ-˳��洢
	//linkToList(L,G);
	//for (int i = 0; i < NUMBER; i++)
	//	cout << G[i] << "--";
	//cout << endl;

	//LNode* p;//���Ը��ƺ���
	//p = copyL->next;
	//while (p!=NULL) {
	//	cout << p->data << "--";
	//	p = p->next;
	//}
}

void insertAll_sub_car(LinkList copyL, int r, int r1, firefly& bestfly) {//r(r>=1)�����ڵ�λ��,r1(r1>=0)����λ��
	//L����ȡ�������ڵ�
	LNode* pr, * pf;
	pr = copyL;
	int i = 0;
	while (i != r - 1) {
		pr = pr->next;
		i++;
	}
	pf = pr;
	pr = pr->next;	//��ȡ���Ľڵ�
	pf->next = pr->next;	//L��ɾȥ��pr
	pr->next = NULL;

	//L�в���
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
	//linkToList(copyL, newf.G);//��ʽ-->˳��
	//enSimpleCode(newf);
	//if (newf.carNum < bestfly.carNum) {
	//	memcpy(&bestfly, &newf, sizeof(firefly));
	//}
	//else {
	//	//��ԭ
	//	p->next = pr->next;
	//	pr->next = pf->next;
	//	pf->next = pr;
	//}
}


void decompRounte(firefly f, LinkList &rtHead) { //�ֽ�ɸ���·������ 
	LinkList L; //��ͷ
	listToLink(f, L); //˳��-->��ʽ
	LNode* Lp1,* tempLp1;
	Lp1 = L->next;

	LinkList headL, record;//·��ͷ�ڵ�
	headL = new LNode;
	headL->next = Lp1;
	headL->head = NULL;
	record = headL;
	rtHead->head = headL;
	
	int count = 1;
	int ca = 0;
	//while (Lp1 != NULL) {
	//	if (count == f.car_nodeNum[ca]) {	//�ҵ��������ٽ��
	//		ca++;
	//		count = 1;
	//		tempLp1 = Lp1->next;//ָ����һ�������׽ڵ�
	//		Lp1->next = NULL;
	//		Lp1 = tempLp1;
	//		
	//		if (ca == f.carNum) break;//������һ���սڵ�
	//		LinkList temphL;
	//		temphL = new LNode;//��һ������ͷ���
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

	while (hd != NULL) {//����ͷ�ڵ�
		Lp1 = hd->next;
		Lp2 = hd->next;
		while (Lp1!=NULL) {//���ڿͻ��ڵ�
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
		check(temp.G, s, h);//����
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
	for (int i = 0; i < NUMBER; i++) {//��i�����
		for (int j = 0; j < NUMBER; j++) {//�Ե�i�������б������������ȡ���λ��
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

void mut_swap(firefly& f) { //����������ʵ�λ��
	firefly bestf;
	memcpy(&bestf, &f, sizeof(firefly));
	firefly temp;
	int tag[101] = {};
	for (int i = 0; i < 10; i++) { //��i�����
		srand(unsigned(rand()));
		int r = rand() % NUMBER;
		for (int j = 0; j < NUMBER; j++) { //�Ե�i�������б�������������ȡ���λ��
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
	//		listToLink(f, L);//˳��-->��ʽ
	//		copyLink(L, copyL);

	//		//L����ȡ�������ڵ�
	//		int r = 1 + rand() % NUMBER; //�����ڵ�λ��[1,100]
	//		LNode* pr, * pf;
	//		pr = copyL;
	//		int i = 0;
	//		while (i != r - 1) {
	//			pr = pr->next;
	//			i++;
	//		}
	//		pf = pr;
	//		pr = pr->next;//��ȡ���Ľڵ�
	//		pf->next = pr->next; //L��ɾȥ��pr

	//		//L�в���
	//		int r1 = rand() % NUMBER;//����λ��[0,99]
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

	//		linkToList(copyL, temfly.G);//��ʽ-->˳��
	//		enSimpleCode(temfly);

	//		//�ͷ�L�ڴ�ռ�
	//		LNode* Lp1, * Lp2;
	//		Lp1 = L->next;
	//		Lp2 = L->next;
	//		free(L);
	//		while (Lp1 != NULL) {
	//			Lp1 = Lp2->next;
	//			free(Lp2);
	//			Lp2 = Lp1;
	//		}

	//		//�ͷ�copyL�ڴ�ռ�
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

double discode(int c1[],int c2[]) {//����֮���ƽ������
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
	check(newf.G, s, h);//����
	enSimpleCode(newf);
}

void randCode(firefly& fly) { //�������һ����벢����
	for (int j = 0; j < n; j++) {
		G[j] = j + 1;
	}
	randomArr(G, n);	//����˳��
	S_H2(G);
	check(G, s, h);//����
	for (int m = 0; m < n; m++)
		fly.G[m] = G[m];
	enSimpleCode(fly);
}

void gsofly(firefly fi, firefly fj, firefly& temfly) {
	//fj��fi�����ƶ�
	int count = NUMBER;//���������
	double delta[NUMBER] = { 0 };	//ÿһά��֮��ı仯ֵ
	firefly newfly;                 //�ƶ����ө���
	int fjCode[NUMBER] = { 0 };		//����fjө�����룬��Ӱ��ԭ����
	memcpy(fjCode, fj.G, NUMBER * sizeof(int));

	for (int i = 0; i < NUMBER; i++) {//����ÿ��λ�ñ仯ֵdelta
		delta[i] = fabs(dis[fi.G[i]] - dis[fj.G[i]]);
		if (delta[i] == 0) {
			count--;
			newfly.G[i] = fi.G[i];//��ͬλ����ͬ�ڵ㱣��
			fjCode[i] = 0;
		}
	}
	
	int reserve = min(step, count);	//����������̳н���ө�����λ������
	for (int i = 0; i < reserve; i++) {//�̳�ө���fi��������������
		int temp = 0;
		for (int j = 0; j < NUMBER; j++) {//Ѱ�ҵ�ǰdelta���ڵ�λ��
			if (delta[j] >= delta[temp]) temp = j;
		}
		newfly.G[temp] = fi.G[temp];
		delta[temp] = 0;//��Ϊ0��������һ�������

		fjCode[find(fjCode, fi.G[temp])] = 0;
		// for (int k2 = 0; k2 < NUMBER; k2++) {	//��ө���j�ĸ����У����Ѿ��̳й������0
			// if (fjCode[k2] == fi.G[temp]) { fjCode[k2] = 0; break; }
		// }
	}

	for (int i = 0,c = 0; i < NUMBER; i++){
		if (newfly.G[i] == 0) {
			while(fjCode[c]==0){//��˳�������ҵ�ԭө��������ڵ�
				c++;
			}
			newfly.G[i] = fjCode[c++];
		}
	}
	S_H(newfly);
	check(newfly.G, s, h);
	enSimpleCode(newfly);
	memcpy(&temfly, &newfly,sizeof(firefly));
}
