int i,j;		//LoopCounter
int fx[20];		//草原X
int fy[15];		//草原Y
int Dx[5];		//システム	
int Dy[15];		//
int hero_x;		//主人公X
int hero_y;		//主人公Y
int hero_xpos;
int hero_ypos;
int hero_sp;	//主人公SP
int hero_LV;	//主人公ＬＶ
int hero_HP;	//主人公ＨＰ
int hero_MAXHP;	//主人公ＭＡＸＨＰ
int hero_STR;	//主人公ＳＴＲ
int hero_EX;	//主人公の経験値
int hero_muki;	//向き

long ct;
int enct;		//敵出現率
int turn;		//戦闘ターンフラグ
int enemyrandct;//敵種類出現ランダム
int kind;		//敵の種類保存
int enemy_HP;
int enemy_STR;
int enemy_sp;	//
int enemy_EX;
int initbattle;	//バトル時初期化
int initfiled;	//フィールド時初期化
int flushFlg;	//フラッシュさせるためのフラグ
int flushct;	//フラッシュさせるためのカウンター
int ho;
int ho2;
int ho3;

int map[225]={
		1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1,
		1,4,4,4,4, 4,4,4,4,4, 4,4,4,4,1,
		1,4,4,4,4, 4,4,4,4,4, 4,4,4,4,1,
		1,4,4,4,4, 4,4,4,4,4, 4,4,4,4,1,
		1,4,4,4,4, 4,4,4,4,4, 4,4,4,4,1,

		1,4,4,4,4, 4,4,4,4,4, 4,4,4,4,1,
		1,4,4,4,4, 4,4,4,4,4, 4,4,4,4,1,
		1,4,4,4,4, 4,4,4,4,4, 4,4,4,4,1,
		1,4,4,4,4, 4,4,4,4,4, 4,4,4,4,1,
		1,4,4,4,4, 4,4,4,4,4, 4,4,4,4,1,

		1,4,4,-1,4, 4,4,4,4,2, 2,2,2,2,1,
		1,4,4,4,4, 4,4,4,4,2, 2,2,2,2,1,
		1,4,4,4,4, 4,4,4,4,2, 2,2,2,2,1,
		1,4,4,4,4, 4,4,4,4,2, 2,2,2,3,1,
		1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1
	};
