#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

const int  WARRIOR_NUM = 5;

/*
string Warrior::names[WARRIOR_NUM] = { "dragon","ninja","iceman","lion","wolf" };
红方司令部按照 iceman、lion、wolf、ninja、dragon 的顺序制造武士。
蓝方司令部按照 lion、dragon、ninja、iceman、wolf 的顺序制造武士。
*/

class Headquarter;

//class City;

//class Weapon:public Worrior;
//class sword:public Weapon;
//class arrow:public Weapon;
//class bomb:public Weapon;

class Warrior
{
	private:
		Headquarter * pHeadquarter;
		//Weapon * pWeapon;//擁有的武器
		int kindNo; //武士的种类编号 0 dragon 1 ninja 2 iceman 3 lion 4 wolf
		//float morale; //士氣
		//float loyalty; //忠誠度
		int no;
		int step; //前進步數
	public:
		static string names[WARRIOR_NUM];
		static int initialLifeValue [WARRIOR_NUM];
		Warrior( Headquarter * p,int no_,int kindNo_ );
		void PrintResult(int nTime);
                //void Forward(City &c); //前進到下一個城市(每小時十分)
                //bool TwoStep(); //武士是否前近兩城市
                //void fight(City &c); //武士攻擊
                //void fightBack(City &c); //武士反擊
                //void hurted(int n); //武士受傷
                //void GetLife(int n); //武士得到司令部生命元獎勵
                //void TakeLife(int n); //武士取走城市生命元(每小時30分)
                //bool dead(); //武士是否死亡
                //void roar(); //歡呼
                //void PowerUp(); //攻擊力上升
                //void MoraleUp(); //士氣上升
                //void LoyaltyDrop(); //忠誠度下降
                //bool escape(); //lion是否逃離(每小時第5分)
                //void GetWeapon(); //得到敵人武器
                //void shoot(); //武士放箭(每小時35分)
                //void explode(); //武士引爆炸彈(每小時38分)
};

/*class City
{
       public:
                int num; //城市編號
                void CreateCityNum(); //製造city編號
                char flag; //旗幟顏色
                void ChangeFlag(); //更換旗幟
                bool continuous(); //判斷戰鬥是否連續
                void LifeProduce(); //城市產出10生命元(每小時20分)
};
*/

/*class Weapon:public Worrior
{
       public:
                virtual int num;//武器編號
                virtual int strength;//武器攻擊力
};
*/ //用多態
/*class sword:public Weapon
{
       public:
                virtual int num;//武器編號
                virtual int strength;//武器攻擊力
                void blunt();//劍變鈍
}*/
/*class arrow:public Weapon{
       public:
                virtual int num;//武器編號
                virtual int strength;//武器攻擊力
                void wear();//弓箭用完
}*/
/*class bomb:public Weapon{
       public:
                virtual int num;//武器編號
                virtual int strength;//武器攻擊力
                bool kill();//判斷會不會被殺死(每小時38分)
}*/

class Headquarter
{
	private:
		int totalLifeValue;
		bool stopped;
		int totalWarriorNum;
		int color;
		int curMakingSeqIdx; //当前要制造的武士是制造序列中的第几个
		int warriorNum[WARRIOR_NUM]; //存放每种武士的数量
		Warrior * pWarriors[1000];
	public:
		//int CityNum; //城市編號
                //void CreateCityNum(); //製造headquater編號
		//void getLife; //司令部得到武士生命元(每小時30分)
                friend class Warrior;
		static int makingSeq[2][WARRIOR_NUM]; //武士的制作顺序序列
		void Init(int color_, int lv);
		~Headquarter () ;
		int Produce(int nTime);
		string GetColor();

};
Warrior::Warrior( Headquarter * p,int no_,int kindNo_ ) {
	no = no_;
	kindNo = kindNo_;
	pHeadquarter = p;
}
void Warrior::PrintResult(int nTime)
{
		string color =  pHeadquarter->GetColor();
		printf("%03d00 %s %s %d born with strength %d,%d %s in %s headquarter\n"	,
				nTime, color.c_str(), names[kindNo].c_str(), no, initialLifeValue[kindNo],
				pHeadquarter->warriorNum[kindNo],names[kindNo].c_str(),color.c_str());
}
void Headquarter::Init(int color_, int lv)
{
	color = color_;
	totalLifeValue = lv;
	totalWarriorNum = 0;
	stopped = false;
	curMakingSeqIdx = 0;
	for( int i = 0;i < WARRIOR_NUM;i ++ )
		warriorNum[i] = 0;
}
Headquarter::~Headquarter () {
	for( int i = 0;i < totalWarriorNum;i ++ )
		delete pWarriors[i];
}
int Headquarter::Produce(int nTime)
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
			printf("%03d00 red headquarter stops making warriors\n",nTime);
		else
			printf("%03d00 blue headquarter stops making warriors\n",nTime);
		return 0;
	}
	totalLifeValue -= Warrior::initialLifeValue[kindNo];
	curMakingSeqIdx = ( curMakingSeqIdx + 1 ) % WARRIOR_NUM ;
	pWarriors[totalWarriorNum] = new Warrior( this,totalWarriorNum+1,kindNo);
	warriorNum[kindNo]++;
	pWarriors[totalWarriorNum]->PrintResult(nTime);
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
int Headquarter::makingSeq[2][WARRIOR_NUM] = { { 2,3,4,1,0 },{3,0,1,2,4} }; //两个司令部武士的制作顺序序列

int main()
{
	int t;
	int m;
	Headquarter RedHead,BlueHead;
	scanf("%d",&t);
	int nCaseNo = 1;
	while ( t -- ) {
		printf("Case:%d\n",nCaseNo++);
		scanf("%d",&m);
		for( int i = 0;i < WARRIOR_NUM;i ++ )
			scanf("%d", & Warrior::initialLifeValue[i]);
		RedHead.Init(0,m);
		BlueHead.Init(1,m);
		int nTime = 0;
		while( true) {
			int tmp1 = RedHead.Produce(nTime);
			int tmp2 = BlueHead.Produce(nTime);
			if( tmp1 == 0 && tmp2 == 0)
				break;
			nTime ++;
		}
	}
	return 0;
}

/*
以下是不同时间会发生的不同事件：

在每个整点，即每个小时的第0分， 双方的司令部中各有一个武士降生。

红方司令部按照 iceman、lion、wolf、ninja、dragon 的顺序制造武士。

蓝方司令部按照 lion、dragon、ninja、iceman、wolf 的顺序制造武士。

制造武士需要生命元。

制造一个初始生命值为 m 的武士，司令部中的生命元就要减少 m 个。

如果司令部中的生命元不足以制造某武士，那么司令部就等待，直到获得足够生命元后的第一个整点，才制造该武士。

例如，在2:00，红方司令部本该制造一个 wolf ，如果此时生命元不足，那么就会等待，直到生命元足够后的下一个整点，才制造一个 wolf。

在每个小时的第5分，该逃跑的lion就在这一时刻逃跑了。

在每个小时的第10分：所有的武士朝敌人司令部方向前进一步。即从己方司令部走到相邻城市，或从一个城市走到下一个城市。
                    
                    或从和敌军司令部相邻的城市到达敌军司令部。

在每个小时的第20分：每个城市产出10个生命元。生命元留在城市，直到被武士取走。

在每个小时的第30分：如果某个城市中只有一个武士，那么该武士取走该城市中的所有生命元，并立即将这些生命元传送到其所属的司令部。

在每个小时的第35分，拥有arrow的武士放箭，对敌人造成伤害。放箭事件应算发生在箭发出的城市。
                 
                    注意，放箭不算是战斗，因此放箭的武士不会得到任何好处。

                    武士在没有敌人的城市被箭射死也不影响其所在城市的旗帜更换情况。

在每个小时的第38分，拥有bomb的武士评估是否应该使用bomb。如果是，就用bomb和敌人同归于尽。

在每个小时的第40分：在有两个武士的城市，会发生战斗。 如果敌人在5分钟前已经被飞来的arrow射死，那么仍然视为发生了一场战斗，而且存活者视为获得了战斗的胜利。此情况下不会有“武士主动攻击”，“武士反击”，“武士战死”的事件发生，但战斗胜利后应该发生的事情都会发生。如Wolf一样能缴获武器，旗帜也可能更换，等等。在此情况下,Dragon同样会通过判断是否应该轮到自己主动攻击来决定是否欢呼。

在每个小时的第50分，司令部报告它拥有的生命元数量。

在每个小时的第55分，每个武士报告其拥有的武器情况。

武士到达对方司令部后就算完成任务了，从此就呆在那里无所事事。

任何一方的司令部里若是出现了2个敌人，则认为该司令部已被敌人占领。

任何一方的司令部被敌人占领，则战争结束。战争结束之后就不会发生任何事情了。
*/

/*
不同的武士有不同的特点。

dragon可以拥有一件武器。编号为n的dragon降生时即获得编号为 n%3 的武器。

dragon还有“士气”这个属性，是个浮点数，其值为它降生后其司令部剩余生命元的数量除以造dragon所需的生命元数量。

dragon 在一次在它主动进攻的战斗结束后，如果还没有战死，而且士气值大于0.8，就会欢呼。

dragon每取得一次战斗的胜利(敌人被杀死)，士气就会增加0.2，每经历一次未能获胜的战斗，士气值就会减少0.2。

士气增减发生在欢呼之前。


ninjia可以拥有两件武器。编号为n的ninjia降生时即获得编号为 n%3 和 (n+1)%3的武器。ninja 挨打了也从不反击敌人。


iceman有一件武器。编号为n的iceman降生时即获得编号为 n%3 的武器。

iceman 每前进两步，在第2步完成的时候，生命值会减少9，攻击力会增加20。

但是若生命值减9后会小于等于0，则生命值不减9,而是变为1。即iceman不会因走多了而死。


lion 有“忠诚度”这个属性，其初始值等于它降生之后其司令部剩余生命元的数目。

每经过一场未能杀死敌人的战斗，忠诚度就降低K。忠诚度降至0或0以下，则该lion逃离战场,永远消失。

但是已经到达敌人司令部的lion不会逃跑。Lion在己方司令部可能逃跑。lion 若是战死，则其战斗前的生命值就会转移到对手身上。

所谓“战斗前”，就是每个小时的40分前的一瞬间。


wolf降生时没有武器，但是在战斗中如果获胜（杀死敌人），就会缴获敌人的武器，但自己已有的武器就不缴获了。

被缴获的武器当然不能算新的，已经被用到什么样了，就是什么样的。
*/

/*

各种武器有其特点：

sword武器的初始攻击力为拥有它的武士的攻击力的20%（去尾取整）。

但是sword每经过一次战斗(不论是主动攻击还是反击)，就会变钝，攻击力变为本次战斗前的80% (去尾取整)。

sword攻击力变为0时，视为武士失去了sword。如果武士降生时得到了一个初始攻击力为0的sword，则视为武士没有sword.


arrow有一个攻击力值R。如果下一步要走到的城市有敌人，那么拥有arrow的武士就会放箭攻击下一个城市的敌人

（不能攻击对方司令部里的敌人）而不被还击。arrow使敌人的生命值减少R，若减至小于等于0，则敌人被杀死。

arrow使用3次后即被耗尽，武士失去arrow。两个相邻的武士可能同时放箭把对方射死。


拥有bomb的武士，在战斗开始前如果判断自己将被杀死（不论主动攻击敌人，或者被敌人主动攻击都可能导致自己被杀死，

而且假设武士可以知道敌人的攻击力和生命值），那么就会使用bomb和敌人同归于尽。武士不预测对方是否会使用bomb。

武士使用bomb和敌人同归于尽的情况下，不算是一场战斗，双方都不能拿走城市的生命元，也不影响城市的旗帜。

*/

/*

描述

魔兽世界的西面是红魔军的司令部，东面是蓝魔军的司令部。两个司令部之间是依次排列的若干城市，城市从西向东依次编号为1,2,3 .... N 

( N <= 20 )。红魔军的司令部算作编号为0的城市，蓝魔军的司令部算作编号为N+1的城市。司令部有生命元，用于制造武士。


两军的司令部都会制造武士。武士一共有 dragon 、ninja、iceman、lion、wolf 五种。每种武士都有编号、生命值、攻击力这三种属性。

双方的武士编号都是从1开始计算。红方制造出来的第 n 个武士，编号就是n。同样，蓝方制造出来的第 n 个武士，编号也是n。

武士在刚降生的时候有一个初始的生命值，生命值在战斗中会发生变化，如果生命值减少到0（生命值变为负数时应当做变为0处理），

则武士死亡（消失）。


有的武士可以拥有武器。武器有三种，sword, bomb,和arrow，编号分别为0,1,2。


武士降生后就朝对方司令部走，在经过的城市如果遇到敌人（同一时刻每个城市最多只可能有1个蓝武士和一个红武士），就会发生战斗。

每次战斗只有一方发起主动进攻一次。被攻击者生命值会减去进攻者的攻击力值和进攻者手中sword的攻击力值。

被进攻者若没死，就会发起反击，被反击者的生命值要减去反击者攻击力值的一半(去尾取整)和反击者手中sword的攻击力值。

反击可能致敌人于死地。



如果武士在战斗中杀死敌人（不论是主动进攻杀死还是反击杀死），则其司令部会立即向其发送8个生命元作为奖励，使其生命值增加8。

当然前提是司令部得有8个生命元。如果司令部的生命元不足以奖励所有的武士，则优先奖励距离敌方司令部近的武士。

如果某武士在某城市的战斗中杀死了敌人，则该武士的司令部立即取得该城市中所有的生命元。

注意，司令部总是先完成全部奖励工作，然后才开始从各个打了胜仗的城市回收生命元。

对于因司令部生命元不足而领不到奖励的武士，司令部也不会在取得战利品生命元后为其补发奖励。

如果一次战斗的结果是双方都幸存(平局)，则双方都不能拿走发生战斗的城市的生命元。


城市可以插旗子，一开始所有城市都没有旗子。在插红旗的城市，以及编号为奇数的无旗城市，由红武士主动发起进攻。

在插蓝旗的城市，以及编号为偶数的无旗城市，由蓝武士主动发起进攻。

当某个城市有连续两场战斗都是同一方的武士杀死敌人(两场战斗之间如果有若干个战斗时刻并没有发生战斗，则这两场战斗仍然算是连续的；

但如果中间有平局的战斗，就不算连续了) ，那么该城市就会插上胜方的旗帜，若原来插着败方的旗帜，则败方旗帜落下。

旗帜一旦插上，就一直插着，直到被敌人更换。一个城市最多只能插一面旗帜，旗帜没被敌人更换前，也不会再次插同颜色的旗。

*/
