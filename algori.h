//�������
/*
* ע�����
* 
1.��ʼ��Ⱥ�����뷽ʽ��
2.���뷽ʽ���Ը��塢����Ⱥ��

ө��������Ƚϣ��ϲ������ŵķ����ƶ�

3.flyMove�����ƶ��������ƶ���Ա������ÿ����������ʽ�����Ŷ�������ڹ����в�����С��������ô���ȡ����
4.randWalk2���������������λ��
*/
/*
void fireflyAlgor(int circle) {

	clock_t begin1, end1;
	begin1 = clock();
	srand(unsigned(time(NULL)));

	getPerm(fly);//��ʼ����Ⱥ����������
	enCode(fly);//��Ⱥ���룬�ؼ�

	int N1 = 0;//��������
	while (N1 < TMAX) {

		//����ǰ �������� ����������
		//cout<<"******�������**********"<<endl;
		//cout.width(7);
		cout << N1 <<endl;
		//cout << "\b\b\b\b\b\b\b\b"<<endl;

		int k2 = 0;	//�����м��ĸ���
		firefly nextfly[flyNum];		//�洢���Ƕ�������Ⱥ�������ź�ѡ����ǰN�����ű���,�м�洢һ���ٽ�����ʼ��Ⱥfly
		firefly temfly[2*flyNum + 1];	//�м���Ⱥ��ө����ƶ���Ľⲻȫ������Ҳֻά�ֺͳ�ʼ��Ⱥһ����С,+1��һ��β�ͣ����ֵ
		firefly temfly2;				//��ʱ�洢�µĽ�

clock_t begin2, end2;
	begin2 = clock();

		for (int i = 0; i < flyNum/2; i++) {
			//cout<<"-----"<<i<<endl;
			for (int j = i +80; j < flyNum; j++) {
				if (k2 <= 2*flyNum) {//ǰflyNum���ƶ���Ľ�ֱ�ӱ���
					if (dominate(fly[i], fly[j]) == 0)  flyMove(fly[i], fly[j], temfly[k2]);
					else if (dominate(fly[i], fly[j]) == 1)  flyMove(fly[j], fly[i], temfly[k2]);
					else randWalk2(fly[j], temfly[k2]);
					k2++;
				}
				else { //���ƶ���⹹�ɵĴ�СΪflyNum��Ⱥ�У���������Ľ�����Ⱥ�����Ľ�Ƚϣ������ƶ�����Ⱥ
					if (dominate(fly[i], fly[j]) == 0)  flyMove(fly[i], fly[j], temfly2);
					else if(dominate(fly[i], fly[j]) == 1)  flyMove(fly[j], fly[i], temfly2);
					else  randWalk2(fly[j], temfly2);
					int bad = getBad(temfly); //�����м���Ⱥ��������±�
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
		for (int i = 0; i < 2*flyNum + 1; i++) { //���м���Ⱥ���оֲ�����������ȥ�����Ż�
			if(N1<5000) opt2(temfly[i]);
			else swa(temfly[i]);
		}
*/


		//��Ӣ����,ѡ��ǰN�����ۺϱȽ� ��ʼ��Ⱥ �� �м���Ⱥ -->ѡ�����ŵ�ǰN�����������һ����Ⱥnextfly
		//����1����������Ⱥ����һ��������򣨰���Ŀ�꺯���Ĵ�С����ֱ��ȡǰN��
		//����2����������Ⱥ�ֱ���������ٷֱ��ó���һ�����жԱȣ�ֱ��ѡ��N��
		/*
clock_t begin1, end1;
	begin1 = clock();

		const int combineSize = 3*flyNum+1;
		firefly combinedPouplation[combineSize];
		memcpy(combinedPouplation, fly, flyNum * sizeof(firefly));
		memcpy(combinedPouplation + flyNum, temfly, (2*flyNum + 1) * sizeof(firefly));
		sort(combinedPouplation, combinedPouplation + combineSize,comp); //�������Ⱥ��С��������
		int capNum = flyNum;
		for (int i = 0; i < flyNum;i++) {//ѡ��ǰN����
			//�Ի����Ⱥ��������ѡȡ��ѡ�����ŵ�ǰN�����������һ����Ⱥ
			memcpy(&nextfly[i], &combinedPouplation[i], sizeof(firefly));
		}

		memcpy(fly, nextfly, flyNum * sizeof(firefly));//fly����Ϊ��һ���ĳ�ʼ��Ⱥ,nextfly����fly

		//�洢ÿһ�������Ÿ���
		//����Ҫ�洢�����м��������ڴ˴��������

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
	////����30���������Ž��
	//ofstream ocout;
	//ocout.open("G:\\VRPTW\\testOut\\VRTW_FA����ʵ��\\swa-800-1.txt", ios::app);//�ļ�������Ⱥ��С-��������
	//ocout << circle + 1 << ": " << gerationfly[TMAX - 1].carBest << " " << gerationfly[TMAX - 1].disBest <<" "<< costTime1 <<"  ";
	//ocout<< gerationfly[TMAX - 1].carBest << "-" << gerationfly[TMAX - 1].carBest_dis << "  " << gerationfly[TMAX - 1].disBest << "-" << gerationfly[TMAX - 1].disBest_car << endl;
	//ocout.close();
}
*/

void GSO(int circle) {
	ofstream out;
    out.open("out.txt");
	srand(unsigned(time(NULL)));

	getPerm(fly);//��ʼ����Ⱥ����������
	enCode(fly);//��Ⱥ���룬�ؼ�
	for (int i = 0; i < n; i++) //��λ��֮��ľ���
		for (int j = i + 1; j < n; j++) {
			dis[i][j] = sqrt(pow((cargo[i].x - cargo[j].x), 2) + pow((cargo[i].y - cargo[j].y), 2) + pow((cargo[i].z - cargo[j].z), 2));
			dis[j][i] = dis[i][j];
		}

	vector<int> Nt[flyNum];//ө����������򼯺��±�
	double rd[flyNum];//ө�������뾶
	firefly modifly[flyNum];
	int N1 = 0;//��������
	while (N1 < TMAX) {

		cout<<"**********"<<N1<<"************"<<endl;
		out<<"**********"<<N1<<"************"<<endl;
		clock_t begin1, end1;
		begin1 = clock();

		for (int i = 0; i < flyNum; i++)//����ө�������뾶
			rd[i] = min(rs, max(0.0, rd[i] + betata * (nt - Nt[i].size())));

		for (int i = 0; i < flyNum; i++) //ȷ��ө�������
			for (int j = 0; j < flyNum; j++) {
				if (i == j) break;
				if (discode(fly[i].G,fly[j].G) < rd[i] && fly[i].fluorescein > fly[j].fluorescein)
					Nt[i].push_back(j);
			}
		
		int count = 0;
		for (int i = 0; i < flyNum; i++) {//ө����������ڽ��з����ƶ�
			if (Nt[i].empty()) {//������Ϊ������б���������
				firefly temp;
				memcpy(&temp, &fly[i], sizeof(firefly));
				LocalSearch(temp);
				if (temp.fluorescein == fly[i].fluorescein)
					randCode(modifly[count++]);//ө����ظ����������һ��
				else memcpy(&modifly[count++], &temp, sizeof(firefly));
				continue;
			}
			double sum = 0,pi = 0;
			int tag = 0;//��¼piֵ�����±�
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
		memcpy(combinedPouplation + flyNum, modifly, flyNum * sizeof(firefly));//��Ӣ����
		sort(combinedPouplation, combinedPouplation + 2*flyNum, comp); //������Ӧ��ֵ����
		int capNum = flyNum;
		for (int i = 0; i < flyNum; i++) {//ѡ��ǰN����
			//�Ի����Ⱥ��������ѡȡ��ѡ�����ŵ�ǰN�����������һ����Ⱥ
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

