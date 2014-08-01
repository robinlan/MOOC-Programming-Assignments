#include <iostream>
#include <cstdio>
#include <string>
#include <stdlib.h>
#include <cstring>
using namespace std;

const int  WARRIOR_NUM = 5;

class Headquarter;
class Sword; 
class Arrow;
class Bomb;
class City;
class Warrior
{
	public:
		Headquarter * pHeadquarter;
		Sword * pSword;
		Arrow * pArrow;
        int ArrowStrength;
        int ArrowTimes; 
		Bomb * pBomb; 
		int BombStrength; //���u���ˤO     
		City * pCity; 
		int kindNo;
		int no;
		int force;//�Z�h�����O 
		int weapon1; //�Z�h�Z���s�� 
		int weapon2; //�Z�h�Z���s�� 
		int CurCityNum; //�Z�h�Ҧb���� 
		int RedArrived; //���Z�h��F
        int BlueArrived; //�ŪZ�h��F 
        int ToGiveHq; //��ͩR���e�ٰ}��
		float morale; //�h��
        float loyalty; //���۫� 
		static string names[WARRIOR_NUM];
		static int initialLifeValue [WARRIOR_NUM];
		Warrior( Headquarter * p,int no_,int kindNo_ );
		void PrintResult(int nTime,int R);
		void RedForward(City c,int N); //���Z�h�e�i 
		void BlueForward(City c); //�ŪZ�h�e�i 
        void GetLife(); //�Z�h�o��q�O���ͩR�����y
        void TakeLife(int n); //�Z�h���������ͩR��(�C�p��30��),��City->winner
        void GiveHqLife(int n/*�����ͩR��*/); //��ͩR���e�ٰ}�� 
        void LionEscape(int nTime); //��l�k�] 
        string GetWeapon1(); //��^�Z���W�� 
        string GetWeapon2(); //��^�Z���W�� 
};
class City
{
            public:
                Warrior * pWarriors[5];
                ~City(){} ; //����Warrior�O����

                int num; //�����s�� 
                int flag; //���ݺX�m
                int LifeValue; //�����ͩR��
	 
                void Init(int flag_,int N); //�c�y��ƪ�l��

                int CurRedWarriorNo;
                int CurRedWarriorKindNo; //�ثe�Z�h�ƶq(�C�p��40��),���Z�h+2,�ŪZ�h-1
                int CurBlueWarriorNo;
                int CurBlueWarriorKindNo;
                int CurWarrior; 
                bool StartFight(); //�P�_�԰��O�_�}�l(�C�p��40��)
                void FightBegin(); //��City�t�d�D���԰�,��Warrior->fight(Warrior *p)�BStartFight()
                void FightBackBegin(); //��City�t�d�D������,��Warrior->FightBack(Warrior *p)
                void HurtBegin(int n); //��City�t�d�D������,n=���˫���,��Warrior->hurted(int n)

                bool ToExplode(); //�P�_�n���n�z��(�C�p��38��) 
                void Explode(); //���Z�h�h�z��,��warrior->explode(Warrior *p);

                int winner; //�Ӥ�,��=1,�L=0,��=-1
                bool WinSide(); //�P�_�Ӥ� 

                bool continuous(); //�P�_�԰��O�_�s��(��F�N�k�s)
                void ChangeFlag(int n); //�󴫺X�m,n=continuous()
                void LifeProduce(); //�������X10�ͩR��(�C�p��20��)
                string GetFlag(); //��^�X�m�C�� 
};
void City::LifeProduce(){
     LifeValue = LifeValue + 10; 
} 
bool City::StartFight(){
     if(CurWarrior==2)return true;
     else
     return false; 
} 
string City::GetFlag(){
     if(flag == 0)return "red";
     else if (flag == 1)return "blue";
     else 
     return "no!!";  
} 
void City::Init(int flag_,int N){
     flag = flag_;
     num = N; 
     CurWarrior = 0; 
     LifeValue = 0; 
     CurRedWarriorNo = 0;
     CurRedWarriorKindNo = -1; //�ثe�Z�h�ƶq(�C�p��40��),���Z�h+2,�ŪZ�h-1
     CurBlueWarriorNo = 0;
     CurBlueWarriorKindNo = -1;
} 
class Headquarter
{
	public:
		int totalLifeValue; 
		bool stopped;
		int totalWarriorNum;
		int color;
		int curMakingSeqIdx;
		int warriorNum[WARRIOR_NUM];
		int CityNum; 
		Warrior * pWarriors[1000];
        int EnermyNum; //�ĤH�ƶq 
		static int makingSeq[2][WARRIOR_NUM];
		void Init(int color_, int lv, int N);
		~Headquarter () ;
		int Produce(int nTime,int R);
		string GetColor();
		int occupied(); //�}��O�_�Q�e��,��EnermyNum
		void totalLifeValueUp(int n); 

};
class Sword
{
	    public:
                static string sName;
                Warrior * pWarrior;//�Z��������

                int num;//�Z���s��
                double strength;//�Z�������O

                Sword(); //��l�ƪZ�������O

                void blunt();
                
                string GetWeapon1();
                string GetWeapon2(); 
};
class Arrow
{
	    public:
                static string aName;
                Warrior * pWarrior;//�Z��������
                int num;//�Z���s��
                int strength;//�Z�������O
                int times;//�}�b�ϥΦ��� 
                Arrow(); 
                bool wear();//�}�b�Χ�,�g�X�ɭn�ˬd(�C�p��35��) 
                string GetWeapon1();
                string GetWeapon2();
};
class Bomb
{
	    public:
                static string bName;
                Warrior * pWarrior;//�Z��������
                int num;//�Z���s��
                Bomb(); 
                string GetWeapon1();
                string GetWeapon2();
};
Bomb::Bomb(){
        num = 1;     
} 
string Bomb::GetWeapon1(){
       return "Bomb"; 
} 
string Bomb::GetWeapon2(){
       return "Bomb"; 
} 
bool Arrow::wear(){
     if(times>=3)return true;
     else
     return false;
} 
Arrow::Arrow(){
        strength = pWarrior->ArrowStrength; 
        num = 2; 
}  
string Arrow::GetWeapon1(){
       return "Arrow"; 
} 
string Arrow::GetWeapon2(){
       return "Arrow"; 
} 
void Sword::blunt(){
        strength = strength * 0.8;
} 
string Sword::GetWeapon1(){
       return "Sword"; 
} 
string Sword::GetWeapon2(){
       return "Sword"; 
} 
Sword::Sword(){
                strength = pWarrior -> force * 0.2;
                num = 0; 
}
void Warrior::LionEscape(int nTime){
       if(loyalty<=0 && kindNo == 1 && pHeadquarter -> color == 0){
            printf("%03d:05 ",nTime);
            cout<<pHeadquarter->GetColor()<<" lion "<<no<<" "<<"ran away"<<endl;
            loyalty = 1; 
       } 
       else if(loyalty<=0 && kindNo == 0 && pHeadquarter -> color == 1){
            printf("%03d:05 ",nTime);
            cout<<pHeadquarter->GetColor()<<" lion "<<no<<" "<<"ran away"<<endl;
            loyalty = 1; 
       } 
} 
string Warrior::GetWeapon1(){
       if(weapon1==0)return "sword";
       else if(weapon1==2)return "arrow";
       else if(weapon1==1)return "bomb";
}
string Warrior::GetWeapon2(){
       if(weapon2==0)return "sword";
       else if(weapon2==2)return "arrow";
       else if(weapon2==1)return "bomb";
}
void Warrior::GiveHqLife(int n/*�����ͩR��*/){
        initialLifeValue[kindNo] = initialLifeValue[kindNo] - n;
        pHeadquarter -> totalLifeValue = pHeadquarter -> totalLifeValue + n; 
}
void Warrior::GetLife(){
        initialLifeValue[kindNo] = initialLifeValue[kindNo] + 8;
        pHeadquarter -> totalLifeValue =  pHeadquarter -> totalLifeValue - 8; 
}
void Warrior::TakeLife(int n /*�����ͩR��*/){
        initialLifeValue[kindNo] = initialLifeValue[kindNo] + n;
} 
void Warrior::RedForward(City c,int N){
    CurCityNum = CurCityNum + 1;
    pCity = & c; 
    pCity -> CurWarrior ++;
    if(CurCityNum==N+1)RedArrived = 1;
    else 
    RedArrived = 0; 
} 
void Warrior::BlueForward(City c){
    CurCityNum = CurCityNum - 1;
    pCity = & c;
    pCity -> CurWarrior ++;
    if(CurCityNum==0)BlueArrived = 1;
    else 
    BlueArrived = 0;
} 
Warrior::Warrior( Headquarter * p,int no_,int kindNo_ ) {
	no = no_;
	kindNo = kindNo_;
	pHeadquarter = p; 
	force = 0; 
	morale = (float)pHeadquarter->totalLifeValue / initialLifeValue[kindNo];
	loyalty = (float)pHeadquarter->totalLifeValue; 
	CurCityNum = pHeadquarter->CityNum;
    ToGiveHq = 0; 
    ArrowStrength = 0; 
    ArrowTimes = 0; 
}
void Warrior::PrintResult(int nTime,int R)
{
		string color =  pHeadquarter->GetColor();
        ArrowStrength = R;
		printf("%03d:00 %s %s %d born with strength %d,%d %s in %s headquarter\n"	,
				nTime, color.c_str(), names[kindNo].c_str(), no, initialLifeValue[kindNo],
				pHeadquarter->warriorNum[kindNo],names[kindNo].c_str(),color.c_str());
//		cout<<"The warrior is now in City "<<CurCityNum<<" !"<<endl; 
		if(pHeadquarter->curMakingSeqIdx == 4 && color=="red"){weapon1 =  no % 3;}//cout<<"It has a "<<GetWeapon1();printf(",and it's morale is %.2f\n",morale);}
        else if(pHeadquarter->curMakingSeqIdx == 1 && color=="blue"){weapon1 =  no % 3;}//cout<<"It has a "<<GetWeapon1();printf(",and it's morale is %.2f\n",morale);} 
        else if(pHeadquarter->curMakingSeqIdx == 3 && color=="red"){weapon1 =  no % 3;weapon2 =  (no+1) % 3;}//cout<<"It has a "<<GetWeapon1()<<" and a "<<GetWeapon2()<<endl;} 
        else if(pHeadquarter->curMakingSeqIdx == 2 && color=="blue"){weapon1 =  no % 3;weapon2 =  (no+1) % 3;}//cout<<"It has a "<<GetWeapon1()<<" and a "<<GetWeapon2()<<endl;} 
        else if(pHeadquarter->curMakingSeqIdx == 0 && color=="red"){weapon1 =  no % 3;}//cout<<"It has a "<<GetWeapon1()<<endl;} 
        else if(pHeadquarter->curMakingSeqIdx == 3 && color=="blue"){weapon1 =  no % 3;}//cout<<"It has a "<<GetWeapon1()<<endl;} 
        else if(pHeadquarter->curMakingSeqIdx == 1 && color=="red"){}//cout<<"It's loyalty is "<<loyalty<<endl;}
        else if(pHeadquarter->curMakingSeqIdx == 0 && color=="blue"){}//cout<<"It's loyalty is "<<loyalty<<endl;}
        else {}
}
int Headquarter::occupied(){
        if(EnermyNum>2||EnermyNum==2)
        return 1;
        else
        return 0; 
} 
void Headquarter::totalLifeValueUp(int n){
    totalLifeValue = totalLifeValue + n; 
} 
void Headquarter::Init(int color_, int lv, int N)
{
	color = color_;
	totalLifeValue = lv;
	totalWarriorNum = 0;
	stopped = false;
	curMakingSeqIdx = 0;
	for( int i = 0;i < WARRIOR_NUM;i ++ )
		warriorNum[i] = 0;
	if(color==0)CityNum = 0; 
    else if(color==1)CityNum = N+1; 
}
Headquarter::~Headquarter () {
	for( int i = 0;i < totalWarriorNum;i ++ )
		delete pWarriors[i];
}
int Headquarter::Produce(int nTime,int R)
{

	if( stopped )
		return 0;
	int searchingTimes = 0;
	while( Warrior::initialLifeValue[makingSeq[color][curMakingSeqIdx]] > totalLifeValue &&
		searchingTimes < WARRIOR_NUM ) {
		curMakingSeqIdx = ( curMakingSeqIdx + 1 ) % WARRIOR_NUM ;
		searchingTimes ++;
	}
	int kindNo = makingSeq[color][curMakingSeqIdx];
	if( Warrior::initialLifeValue[kindNo] > totalLifeValue ) {
		stopped = true;
		if( color == 0)
			printf("%03d:00 red headquarter stops making warriors\n",nTime);
		else
			printf("%03d:00 blue headquarter stops making warriors\n",nTime);
		return 0;
	}
	totalLifeValue -= Warrior::initialLifeValue[kindNo];
	pWarriors[totalWarriorNum] = new Warrior( this,totalWarriorNum+1,kindNo);
	warriorNum[kindNo]++;
	pWarriors[totalWarriorNum]->PrintResult(nTime,R);
	curMakingSeqIdx = ( curMakingSeqIdx + 1 ) % WARRIOR_NUM ;
	totalWarriorNum ++;
	return 1;
}
string Headquarter::GetColor()
{
	if( color == 0)
		return "red";
	else
		return "blue";
}

string Warrior::names[WARRIOR_NUM] = { "dragon","ninja","iceman","lion","wolf" };
int Warrior::initialLifeValue [WARRIOR_NUM];
int Headquarter::makingSeq[2][WARRIOR_NUM] = { { 2,3,4,1,0 },{3,0,1,2,4} };

int main()
{
	int t;
	int m;
	int R = 2; 
	int N;
	int cRValue = 0;
    int cBValue = 0; 
	int end = 0; 
	Headquarter RedHead,BlueHead; 
	cout<<"��J������:"<<endl; 
    cin>>N; 
	City cities[N];
	for(int j = 1;j <= N;j ++){
            cities[j].Init(-1,j);
            cout<<cities[j].GetFlag()<<endl; 
    } 
	scanf("%d",&t);
	int nCaseNo = 1;
	while ( t -- ) {
		printf("Case:%d\n",nCaseNo++);
		scanf("%d",&m);
		for( int i = 0;i < WARRIOR_NUM;i ++ )
			scanf("%d", & Warrior::initialLifeValue[i]);
		RedHead.Init(0,m,N);
		BlueHead.Init(1,m,N);
		int nTime = 0;
		while( end == 0 ) {
			int tmp1 = RedHead.Produce(nTime,R);
			int tmp2 = BlueHead.Produce(nTime,R);
			if( tmp1 == 0 && tmp2 == 0)
				break;
//*****************************lion�k�]********************************** 
            for(int p1=0;p1<RedHead.totalWarriorNum;p1++){
                    RedHead.pWarriors[p1]->LionEscape(nTime);      
            } 
            for(int p2=0;p2<BlueHead.totalWarriorNum;p2++){
                    BlueHead.pWarriors[p2]->LionEscape(nTime);          
            } 
//*****************************�Z�h�e�i**********************************
			for(int l=0;l<RedHead.totalWarriorNum;l++){
                    RedHead.pWarriors[l]->RedForward(cities[RedHead.pWarriors[l]->CurCityNum],N);
                    cities[RedHead.pWarriors[l]->CurCityNum].CurRedWarriorNo = RedHead.pWarriors[l]->no; 
                    cities[RedHead.pWarriors[l]->CurCityNum].CurRedWarriorKindNo = RedHead.pWarriors[l]->kindNo;
                    printf("%03d:10 ",nTime);cout<<RedHead.pWarriors[l]->pHeadquarter->GetColor()<<" "<<RedHead.pWarriors[l]->names[RedHead.pWarriors[l]->kindNo]<<" "<<RedHead.pWarriors[l]->no<<" marched to city "<<cities[RedHead.pWarriors[l]->CurCityNum].num<<" with "<<RedHead.pWarriors[l]->initialLifeValue[RedHead.pWarriors[l]->kindNo]<<" elements and force "<<RedHead.pWarriors[l]->force<<endl;
//                    cout<<"City "<<cities[RedHead.pWarriors[l]->CurCityNum].num<<" are now the red "<<cities[RedHead.pWarriors[l]->CurCityNum].CurRedWarriorKindNo<<" "<<cities[RedHead.pWarriors[l]->CurCityNum].CurRedWarriorNo<<" !"<<endl; 
                    cities[cities[RedHead.pWarriors[l]->CurCityNum].num].CurWarrior++; 
                    cities[cities[RedHead.pWarriors[l]->CurCityNum].num-1].CurWarrior--;
                    if(RedHead.pWarriors[l]->RedArrived == 1){
                         RedHead.EnermyNum++;
                         printf("%03d:10 ",nTime);cout<<RedHead.pWarriors[l]->pHeadquarter->GetColor()<<" "<<RedHead.pWarriors[l]->names[RedHead.pWarriors[l]->kindNo]<<" "<<RedHead.pWarriors[l]->no<<" reached blue headquarter with "<<RedHead.pWarriors[l]->initialLifeValue[RedHead.pWarriors[l]->kindNo]<<" elements and force "<<RedHead.pWarriors[l]->force<<endl;
                         if(RedHead.occupied()==1){printf("%03d:10 ",nTime);cout<<"blue headquarter was taken"<<endl;end = 1;} 
                    } 
//                    cout<<"There are "<<cities[cities[RedHead.pWarriors[l]->CurCityNum].num].CurWarrior<<" warriors in city "<<cities[RedHead.pWarriors[l]->CurCityNum].num<<endl; 
            } 
            for(int n=0;n<BlueHead.totalWarriorNum;n++){
                    BlueHead.pWarriors[n]->BlueForward(cities[BlueHead.pWarriors[n]->CurCityNum]);
                    cities[BlueHead.pWarriors[n]->CurCityNum].CurBlueWarriorNo = BlueHead.pWarriors[n]->no;
                    cities[BlueHead.pWarriors[n]->CurCityNum].CurBlueWarriorKindNo = BlueHead.pWarriors[n]->kindNo;
                    printf("%03d:10 ",nTime);cout<<BlueHead.pWarriors[n]->pHeadquarter->GetColor()<<" "<<BlueHead.pWarriors[n]->names[BlueHead.pWarriors[n]->kindNo]<<" "<<BlueHead.pWarriors[n]->no<<" marched to city "<<cities[BlueHead.pWarriors[n]->CurCityNum].num<<" with "<<BlueHead.pWarriors[n]->initialLifeValue[BlueHead.pWarriors[n]->kindNo]<<" elements and force "<<BlueHead.pWarriors[n]->force<<endl; 
//                    cout<<"City "<<cities[BlueHead.pWarriors[n]->CurCityNum].num<<" are now the blue "<<cities[BlueHead.pWarriors[n]->CurCityNum].CurBlueWarriorKindNo<<" "<<cities[BlueHead.pWarriors[n]->CurCityNum].CurBlueWarriorNo<<" !"<<endl; 
                    cities[cities[BlueHead.pWarriors[n]->CurCityNum].num].CurWarrior++; 
                    cities[cities[BlueHead.pWarriors[n]->CurCityNum].num+1].CurWarrior--;
                    if(BlueHead.pWarriors[n]->BlueArrived == 1){
                         BlueHead.EnermyNum++;
                         printf("%03d:10 ",nTime);cout<<BlueHead.pWarriors[n]->pHeadquarter->GetColor()<<" "<<BlueHead.pWarriors[n]->names[BlueHead.pWarriors[n]->kindNo]<<" "<<BlueHead.pWarriors[n]->no<<" reached blue headquarter with "<<BlueHead.pWarriors[n]->initialLifeValue[BlueHead.pWarriors[n]->kindNo]<<" elements and force "<<BlueHead.pWarriors[n]->force<<endl;
                         if(BlueHead.occupied()==1){printf("%03d:10 ",nTime);cout<<"red headquarter was taken"<<endl;end = 1;} 
                    } 
//                    cout<<"There are "<<cities[cities[BlueHead.pWarriors[n]->CurCityNum].num].CurWarrior<<" warriors in city "<<cities[BlueHead.pWarriors[n]->CurCityNum].num<<endl; 
            } 
//            for(int o=0;o<N;o++)if(cities[o].CurWarrior==2){cities[o].filled = 1;cout<<"Fight in city "<<cities[o].num<<endl;} 
//*****************************���X�ͩR��**********************************
            for(int n2=1;n2<=N;n2++){cities[n2].LifeProduce();}//cout<<"City "<<cities[n2].num<<" has "<<cities[n2].LifeValue<<" lifevalue!"<<endl;} 
//*****************************�����ͩR��(Trouble)**********************************
            for(int o2=1;o2<=N;o2++){
                    if(cities[o2].CurWarrior == 1){
                         if(cities[o2].CurRedWarriorNo != 0 && cities[o2].CurBlueWarriorNo == 0){RedHead.totalLifeValue = RedHead.totalLifeValue + cities[o2].LifeValue;}//cout<<"value up"<<endl;} 
                         else if(cities[o2].CurRedWarriorNo == 0 && cities[o2].CurBlueWarriorNo != 0){BlueHead.totalLifeValue = BlueHead.totalLifeValue + cities[o2].LifeValue;}//cout<<"value up"<<endl;} 
                    } 
            } 
//*****************************arrow�Z�h��b**********************************
            for(int l=0;l<RedHead.totalWarriorNum;l++){
                    if(RedHead.pWarriors[l]->weapon1==2){
                         if(cities[RedHead.pWarriors[l]->CurCityNum+1].CurBlueWarriorNo != 0){
                               printf("%03d:35 ",nTime);cout<<RedHead.pWarriors[l]->pHeadquarter->GetColor()<<" "<<RedHead.pWarriors[l]->names[RedHead.pWarriors[l]->kindNo]<<" "<<RedHead.pWarriors[l]->no<<" shot"<<endl; 
                               BlueHead.pWarriors[cities[RedHead.pWarriors[l]->CurCityNum+1].CurBlueWarriorNo]->initialLifeValue[cities[RedHead.pWarriors[l]->CurCityNum+1].CurBlueWarriorKindNo] = BlueHead.pWarriors[cities[RedHead.pWarriors[l]->CurCityNum+1].CurBlueWarriorNo]->initialLifeValue[cities[RedHead.pWarriors[l]->CurCityNum+1].CurBlueWarriorKindNo] - R; 
                               if(BlueHead.pWarriors[cities[RedHead.pWarriors[l]->CurCityNum+1].CurBlueWarriorNo]->initialLifeValue[cities[RedHead.pWarriors[l]->CurCityNum+1].CurBlueWarriorKindNo]<=0){
                                     printf("%03d:35 ",nTime);cout<<RedHead.pWarriors[l]->pHeadquarter->GetColor()<<" "<<RedHead.pWarriors[l]->names[RedHead.pWarriors[l]->kindNo]<<" "<<RedHead.pWarriors[l]->no<<" shot and killed "<<BlueHead.pWarriors[cities[RedHead.pWarriors[l]->CurCityNum+1].CurBlueWarriorNo]->pHeadquarter->GetColor()<<" "<<BlueHead.pWarriors[cities[RedHead.pWarriors[l]->CurCityNum+1].CurBlueWarriorNo]->names[BlueHead.pWarriors[cities[RedHead.pWarriors[l]->CurCityNum+1].CurBlueWarriorNo]->kindNo]<<" "<<BlueHead.pWarriors[cities[RedHead.pWarriors[l]->CurCityNum+1].CurBlueWarriorNo]->no<<endl; 
                               } 
//                               cout<<"He's hurted!His life is "<<BlueHead.pWarriors[cities[RedHead.pWarriors[l]->CurCityNum+1].CurBlueWarriorNo]->initialLifeValue[cities[RedHead.pWarriors[l]->CurCityNum+1].CurBlueWarriorKindNo]<<endl; 
                               RedHead.pWarriors[l]->ArrowTimes++;
                               if(RedHead.pWarriors[l]->ArrowTimes==3)RedHead.pWarriors[l]->weapon1=-1; 
//                               cout<<"arrow broke!"<<endl;  
                         }  
//                         cout<<RedHead.pWarriors[l]->names[RedHead.pWarriors[l]->kindNo]<<"'s arrowstrength is "<<RedHead.pWarriors[l]->ArrowStrength<<endl; 
                    }
                    else if(RedHead.pWarriors[l]->weapon2==2){
                         if(cities[RedHead.pWarriors[l]->CurCityNum+1].CurBlueWarriorNo != 0){
                               printf("%03d:35 ",nTime);cout<<RedHead.pWarriors[l]->pHeadquarter->GetColor()<<" "<<RedHead.pWarriors[l]->names[RedHead.pWarriors[l]->kindNo]<<" "<<RedHead.pWarriors[l]->no<<" shot"<<endl; 
                               BlueHead.pWarriors[cities[RedHead.pWarriors[l]->CurCityNum+1].CurBlueWarriorNo]->initialLifeValue[cities[RedHead.pWarriors[l]->CurCityNum+1].CurBlueWarriorKindNo] = BlueHead.pWarriors[cities[RedHead.pWarriors[l]->CurCityNum+1].CurBlueWarriorNo]->initialLifeValue[cities[RedHead.pWarriors[l]->CurCityNum+1].CurBlueWarriorKindNo] - R; 
                               if(BlueHead.pWarriors[cities[RedHead.pWarriors[l]->CurCityNum+1].CurBlueWarriorNo]->initialLifeValue[cities[RedHead.pWarriors[l]->CurCityNum+1].CurBlueWarriorKindNo]<=0){
                                     printf("%03d:35 ",nTime);cout<<RedHead.pWarriors[l]->pHeadquarter->GetColor()<<" "<<RedHead.pWarriors[l]->names[RedHead.pWarriors[l]->kindNo]<<" "<<RedHead.pWarriors[l]->no<<" shot and killed "<<BlueHead.pWarriors[cities[RedHead.pWarriors[l]->CurCityNum+1].CurBlueWarriorNo]->pHeadquarter->GetColor()<<" "<<BlueHead.pWarriors[cities[RedHead.pWarriors[l]->CurCityNum+1].CurBlueWarriorNo]->names[BlueHead.pWarriors[cities[RedHead.pWarriors[l]->CurCityNum+1].CurBlueWarriorNo]->kindNo]<<" "<<BlueHead.pWarriors[cities[RedHead.pWarriors[l]->CurCityNum+1].CurBlueWarriorNo]->no<<endl; 
                               } 
//                               cout<<"He's hurted!His life is "<<BlueHead.pWarriors[cities[RedHead.pWarriors[l]->CurCityNum+1].CurBlueWarriorNo]->initialLifeValue[cities[RedHead.pWarriors[l]->CurCityNum+1].CurBlueWarriorKindNo]<<endl; 
                               RedHead.pWarriors[l]->ArrowTimes++;
                               if(RedHead.pWarriors[l]->ArrowTimes==3)RedHead.pWarriors[l]->weapon2=-1; 
//                               cout<<"arrow broke!"<<endl;  
                         }
//                         cout<<RedHead.pWarriors[l]->names[RedHead.pWarriors[l]->kindNo]<<"'s arrowstrength is "<<RedHead.pWarriors[l]->ArrowStrength<<endl;
                    } 
            } 
            for(int n=0;n<BlueHead.totalWarriorNum;n++){
                    if(BlueHead.pWarriors[n]->weapon1==2){ 
                         if(cities[BlueHead.pWarriors[n]->CurCityNum+1].CurRedWarriorNo != 0){
                               printf("%03d:35 ",nTime);cout<<BlueHead.pWarriors[n]->pHeadquarter->GetColor()<<" "<<BlueHead.pWarriors[n]->names[BlueHead.pWarriors[n]->kindNo]<<" "<<BlueHead.pWarriors[n]->no<<" shot"<<endl; 
                               RedHead.pWarriors[cities[BlueHead.pWarriors[n]->CurCityNum+1].CurRedWarriorNo]->initialLifeValue[cities[BlueHead.pWarriors[n]->CurCityNum+1].CurRedWarriorKindNo] = RedHead.pWarriors[cities[BlueHead.pWarriors[n]->CurCityNum+1].CurRedWarriorNo]->initialLifeValue[cities[BlueHead.pWarriors[n]->CurCityNum+1].CurRedWarriorKindNo] - R; 
                               if(RedHead.pWarriors[cities[BlueHead.pWarriors[n]->CurCityNum+1].CurRedWarriorNo]->initialLifeValue[cities[BlueHead.pWarriors[n]->CurCityNum+1].CurRedWarriorKindNo]<=0){
                                     printf("%03d:35 ",nTime);cout<<BlueHead.pWarriors[n]->pHeadquarter->GetColor()<<" "<<BlueHead.pWarriors[n]->names[BlueHead.pWarriors[n]->kindNo]<<" "<<BlueHead.pWarriors[n]->no<<" shot and killed "<<RedHead.pWarriors[cities[BlueHead.pWarriors[n]->CurCityNum+1].CurRedWarriorNo]->pHeadquarter->GetColor()<<" "<<RedHead.pWarriors[cities[BlueHead.pWarriors[n]->CurCityNum+1].CurRedWarriorNo]->names[RedHead.pWarriors[cities[BlueHead.pWarriors[n]->CurCityNum+1].CurRedWarriorNo]->kindNo]<<" "<<RedHead.pWarriors[cities[BlueHead.pWarriors[n]->CurCityNum+1].CurRedWarriorNo]->no<<endl; 
                               } 
//                               cout<<"He's hurted!His life is "<<RedHead.pWarriors[cities[BlueHead.pWarriors[n]->CurCityNum+1].CurRedWarriorNo]->initialLifeValue[cities[BlueHead.pWarriors[n]->CurCityNum+1].CurRedWarriorKindNo]<<endl;  
                               BlueHead.pWarriors[n]->ArrowTimes++;
                               if(BlueHead.pWarriors[n]->ArrowTimes==3)BlueHead.pWarriors[n]->weapon1=-1; 
//                               cout<<"arrow broke!"<<endl;  
                         } 
//                         cout<<BlueHead.pWarriors[n]->names[BlueHead.pWarriors[n]->kindNo]<<"'s arrowstrength is "<<BlueHead.pWarriors[n]->ArrowStrength<<endl;
                    }
                    else if(BlueHead.pWarriors[n]->weapon2==2){
                         if(cities[BlueHead.pWarriors[n]->CurCityNum+1].CurRedWarriorNo != 0){
                               printf("%03d:35 ",nTime);cout<<BlueHead.pWarriors[n]->pHeadquarter->GetColor()<<" "<<BlueHead.pWarriors[n]->names[BlueHead.pWarriors[n]->kindNo]<<" "<<BlueHead.pWarriors[n]->no<<" shot"<<endl;  
                               RedHead.pWarriors[cities[BlueHead.pWarriors[n]->CurCityNum+1].CurRedWarriorNo]->initialLifeValue[cities[BlueHead.pWarriors[n]->CurCityNum+1].CurRedWarriorKindNo] = RedHead.pWarriors[cities[BlueHead.pWarriors[n]->CurCityNum+1].CurRedWarriorNo]->initialLifeValue[cities[BlueHead.pWarriors[n]->CurCityNum+1].CurRedWarriorKindNo] - R; 
                               if(RedHead.pWarriors[cities[BlueHead.pWarriors[n]->CurCityNum+1].CurRedWarriorNo]->initialLifeValue[cities[BlueHead.pWarriors[n]->CurCityNum+1].CurRedWarriorKindNo]<=0){
                                     printf("%03d:35 ",nTime);cout<<BlueHead.pWarriors[n]->pHeadquarter->GetColor()<<" "<<BlueHead.pWarriors[n]->names[BlueHead.pWarriors[n]->kindNo]<<" "<<BlueHead.pWarriors[n]->no<<" shot and killed "<<RedHead.pWarriors[cities[BlueHead.pWarriors[n]->CurCityNum+1].CurRedWarriorNo]->pHeadquarter->GetColor()<<" "<<RedHead.pWarriors[cities[BlueHead.pWarriors[n]->CurCityNum+1].CurRedWarriorNo]->names[RedHead.pWarriors[cities[BlueHead.pWarriors[n]->CurCityNum+1].CurRedWarriorNo]->kindNo]<<" "<<RedHead.pWarriors[cities[BlueHead.pWarriors[n]->CurCityNum+1].CurRedWarriorNo]->no<<endl; 
                               } 
//                               cout<<"He's hurted!His life is "<<RedHead.pWarriors[cities[BlueHead.pWarriors[n]->CurCityNum+1].CurRedWarriorNo]->initialLifeValue[cities[BlueHead.pWarriors[n]->CurCityNum+1].CurRedWarriorKindNo]<<endl;   
                               BlueHead.pWarriors[n]->ArrowTimes++;
                               if(BlueHead.pWarriors[n]->ArrowTimes==3)BlueHead.pWarriors[n]->weapon2=-1;
//                               cout<<"arrow broke!"<<endl;  
                         } 
//                         cout<<BlueHead.pWarriors[n]->names[BlueHead.pWarriors[n]->kindNo]<<"'s arrowstrength is "<<BlueHead.pWarriors[n]->ArrowStrength<<endl;
                    } 
            } 
//*****************************bomb�ϥ�**********************************//��ĤH�����O�j��ۤv�ͩR�� 
            for(int l=0;l<RedHead.totalWarriorNum;l++){
                    if(RedHead.pWarriors[l]->weapon1==1){
                          if(BlueHead.pWarriors[cities[RedHead.pWarriors[l]->CurCityNum].CurBlueWarriorNo]->force > RedHead.pWarriors[l]->initialLifeValue[RedHead.pWarriors[l]->kindNo]){
//runtime error                                  printf("%03d:38 ",nTime);cout<<RedHead.pWarriors[l]->pHeadquarter->GetColor()<<" "<<RedHead.pWarriors[l]->names[RedHead.pWarriors[l]->kindNo]<<" "<<RedHead.pWarriors[l]->no<<" used a bomb and killed "<<BlueHead.pWarriors[cities[RedHead.pWarriors[l]->CurCityNum].CurBlueWarriorNo]->pHeadquarter->GetColor()<<" "<<BlueHead.pWarriors[cities[RedHead.pWarriors[l]->CurCityNum].CurBlueWarriorNo]->names[BlueHead.pWarriors[cities[RedHead.pWarriors[l]->CurCityNum].CurBlueWarriorNo]->kindNo]<<" "<<BlueHead.pWarriors[cities[RedHead.pWarriors[l]->CurCityNum].CurBlueWarriorNo]->no<<endl; 
                          }                             
                    }
                    else if(RedHead.pWarriors[l]->weapon2==1){
                          if(BlueHead.pWarriors[cities[RedHead.pWarriors[l]->CurCityNum].CurBlueWarriorNo]->force > RedHead.pWarriors[l]->initialLifeValue[RedHead.pWarriors[l]->kindNo]){
//runtime error                                   printf("%03d:38 ",nTime);cout<<RedHead.pWarriors[l]->pHeadquarter->GetColor()<<" "<<RedHead.pWarriors[l]->names[RedHead.pWarriors[l]->kindNo]<<" "<<RedHead.pWarriors[l]->no<<" used a bomb and killed "<<BlueHead.pWarriors[cities[RedHead.pWarriors[l]->CurCityNum].CurBlueWarriorNo]->pHeadquarter->GetColor()<<" "<<BlueHead.pWarriors[cities[RedHead.pWarriors[l]->CurCityNum].CurBlueWarriorNo]->names[BlueHead.pWarriors[cities[RedHead.pWarriors[l]->CurCityNum].CurBlueWarriorNo]->kindNo]<<" "<<BlueHead.pWarriors[cities[RedHead.pWarriors[l]->CurCityNum].CurBlueWarriorNo]->no<<endl; 
                          }  
                    } 
            } 
            for(int n=0;n<BlueHead.totalWarriorNum;n++){
                    if(BlueHead.pWarriors[n]->weapon1==1){ 
                          if(RedHead.pWarriors[cities[BlueHead.pWarriors[n]->CurCityNum].CurRedWarriorNo]->force > BlueHead.pWarriors[n]->initialLifeValue[BlueHead.pWarriors[n]->kindNo]){
//runtime error                                   printf("%03d:38 ",nTime);cout<<BlueHead.pWarriors[n]->pHeadquarter->GetColor()<<" "<<BlueHead.pWarriors[n]->names[BlueHead.pWarriors[n]->kindNo]<<" "<<BlueHead.pWarriors[n]->no<<" used a bomb and killed "<<RedHead.pWarriors[cities[BlueHead.pWarriors[n]->CurCityNum].CurRedWarriorNo]->pHeadquarter->GetColor()<<" "<<RedHead.pWarriors[cities[BlueHead.pWarriors[n]->CurCityNum].CurRedWarriorNo]->names[RedHead.pWarriors[cities[BlueHead.pWarriors[n]->CurCityNum].CurRedWarriorNo]->kindNo]<<" "<<RedHead.pWarriors[cities[BlueHead.pWarriors[n]->CurCityNum].CurRedWarriorNo]->no<<endl; 
                          }  
                    }
                    else if(BlueHead.pWarriors[n]->weapon2==1){
                          if(RedHead.pWarriors[cities[BlueHead.pWarriors[n]->CurCityNum].CurRedWarriorNo]->force > BlueHead.pWarriors[n]->initialLifeValue[BlueHead.pWarriors[n]->kindNo]){
//runtime error                                   printf("%03d:38 ",nTime);cout<<BlueHead.pWarriors[n]->pHeadquarter->GetColor()<<" "<<BlueHead.pWarriors[n]->names[BlueHead.pWarriors[n]->kindNo]<<" "<<BlueHead.pWarriors[n]->no<<" used a bomb and killed "<<RedHead.pWarriors[cities[BlueHead.pWarriors[n]->CurCityNum].CurRedWarriorNo]->pHeadquarter->GetColor()<<" "<<RedHead.pWarriors[cities[BlueHead.pWarriors[n]->CurCityNum].CurRedWarriorNo]->names[RedHead.pWarriors[cities[BlueHead.pWarriors[n]->CurCityNum].CurRedWarriorNo]->kindNo]<<" "<<RedHead.pWarriors[cities[BlueHead.pWarriors[n]->CurCityNum].CurRedWarriorNo]->no<<endl; 
                          }   
                    } 
            } 
            nTime ++;
		} 
	} 
    system("pause");
	return 0;
}

//*****************************�����ͩR��(Trouble)**********************************
/*            for(int o2=1;o2<=N;o2++){
                    if(cities[o2].CurWarrior == 1){ 
                         for(int o3=0;o3<RedHead.totalWarriorNum;o3++){ 
                              if(RedHead.pWarriors[o3]->CurCityNum==o2){
//                                   RedHead.pWarriors[o3]->TakeLife(cities[o2].LifeValue); 
//                                     cout<<"Life return 0!"<<endl;
                                   
//                                   RedHead.pWarriors[o3]->initialLifeValue[RedHead.pWarriors[o3]->kindNo] = RedHead.pWarriors[o3]->initialLifeValue[RedHead.pWarriors[o3]->kindNo] - cities[o2].LifeValue;    
//                                   RedHead.pWarriors[o3]->GiveHqLife(cities[o2].LifeValue); 
//                                   RedHead.totalLifeValueUp(cities[o2].LifeValue); 
// �@��runtime error�L�k�[�^hq                                  RedHead.totalLifeValue = RedHead.totalLifeValue + cities[o2].LifeValue;
//                                   cout<<"Life back to headquarter!"<<endl; 
                                   cities[o2].LifeValue = 0;   
                              } 
                         }
                          
                         for(int o4=0;o4<BlueHead.totalWarriorNum;o4++){ 
                              if(BlueHead.pWarriors[o4]->CurCityNum==o2){
//                                   BlueHead.pWarriors[o4]->TakeLife(cities[o2].LifeValue);
//                                   cout<<"Life return 0!"<<endl;
//                                   BlueHead.pWarriors[o4]->initialLifeValue[BlueHead.pWarriors[o4]->kindNo] = BlueHead.pWarriors[o4]->initialLifeValue[BlueHead.pWarriors[o4]->kindNo] - cities[o2].LifeValue; 
//                                   BlueHead.pWarriors[o4]->GiveHqLife(cities[o2].LifeValue); 
//                                   BlueHead.totalLifeValueUp(cities[o2].LifeValue);
// �@��runtime error�L�k�[�^hq       BlueHead.totalLifeValue = BlueHead.totalLifeValue + cities[o2].LifeValue; 
//                                   cout<<"Life back to headquarter!"<<endl;  
                                   cities[o2].LifeValue = 0;
                              } 
                         }
                          
                    }  
            }*/ 
