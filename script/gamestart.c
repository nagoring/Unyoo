include "script/glo.c"
//敵をランダムに出す
int EnemyRand()
{
	enemyrandct = (enemyrandct + 1) % 5;
	return enemyrandct;
}
void awPlayWave( int lp )
{
	loop {			// ループでまわります

		if (!IsPlayWave(lp)) break;
		// チャンネル１のWaveの再生が終了していればloopから抜けます
		// !は、否定演算子です

		halt;		// 長いループ中には、haltを入れるんでしたね。
	}
}
//Background indication
void ShowBg()
{
/*	for(i=0;i<15;i++)
	for(j=0;j<15;j++)
		BltFast(104,fx[i],fy[j]);//草原
		

	BltFast(99,life_x,life_y);//回復

	Sea();
*/
	for(i=0;i<15*15;i++)
		BltFast(map[i]+100,fx[i%15],fy[i/15]);

	for(i=0;i<5;i++)
	for(j=0;j<15;j++)
		BltFast(100,Dx[i],Dy[j]);//システム黒

}
//The initialization of the filed
void FiledInit()
{
	ReleaseMIDI();					//	MIDIファイルの解放
	LoadMIDI("midi/filed1.mid"); 	//	ファイルを読み込む
	PlayMIDI();						//	再生開始
	
	initbattle = 0;
}
//sprit is indicated
void ShowSpr()
{
	Blt(hero_sp,hero_x,hero_y);
}
void Hit()
{

	ho2 = hero_y/32;
	ho3 = ((hero_x+hero_xpos+16)/32) + ((hero_y+hero_ypos+16)/32)*15;
	ho  = map[ho3];
	if(map[ho3] == 1)
	{
		if(hero_muki == 1)
			hero_xpos = -2;
		else if(hero_muki == 2)
			hero_xpos =  2;
		else if(hero_muki == 3)
			hero_ypos = -2;
		else if(hero_muki == 4)
			hero_ypos =  2;
	}
	if(map[ho3] == -1)
	{
		if( hero_HP != hero_MAXHP )
		{
			hero_HP = hero_MAXHP;
			PlayWave(3);	//回復
		}
	}
	if(map[ho3] == 3)
	{
		enct = 256;
		hero_x = hero_x-2;
		hero_y = hero_y-2;
		kind = 5;
	}	
}
//Key in the filed
void Key()
{
	if(IsPressUpKey()){
		hero_ypos = -2;
		enct++;
		hero_muki = 4;	//上
	}
	else if(IsPressDownKey()){
		hero_ypos = 2;
		enct++;
		hero_muki = 3;	//下
	}
	else if(IsPressLeftKey()){	//	現在左キーが押されているかを判定します。
		hero_xpos = -2;
		enct++;
		hero_muki = 2;	//左
	}
	
	else if(IsPressRightKey()){	//	現在右キーが押されているかを判定します。
		hero_xpos = 2;
		enct++;
		hero_muki = 1;	//右
	}
	
}

//Animetion
void Anim()
{
	ct++;
	if( ct < 10 )
		hero_sp = 9;
	else if( ct < 20 )
		hero_sp = 10;
	else if( ct < 30 )
		ct = 0;
}
//The initilzation of the battle
void BattleInit()
{
	if( kind == 0){		//ヘビ
		enemy_HP  = 10;
		enemy_STR = 5;
		enemy_sp  = 20;
		enemy_EX  = 3;
	}
	else if( kind == 1){//コウモリ
		enemy_HP  = 10;
		enemy_STR = 7;
		enemy_sp  = 21;
		enemy_EX  = 10;
	}
	else if( kind == 2){//スライム
		enemy_HP  = 18;
		enemy_STR = 15;
		enemy_sp  = 22;
		enemy_EX  = 50;
	}
	else if( kind == 3){//オバケ
		enemy_HP  = 100;
		enemy_STR = 9;
		enemy_sp  = 23;
		enemy_EX  = 200;
	}
	else if( kind == 4){//ドラゴン
		enemy_HP  = 1000;
		enemy_STR = 15;
		enemy_sp  = 24;
		enemy_EX  = 3000;
	}
	else if( kind == 5){//ボス
		enemy_HP  = 44444;
		enemy_STR = 50;
		enemy_sp  = 25;
		enemy_EX  = 30000;
	}
	ReleaseMIDI();					//	MIDIファイルの解放
	LoadMIDI("midi/battle1.mid"); //	ファイルを読み込む
	PlayMIDI();						//	再生開始
	
	initfiled = 0;

}
//Battle in the key
void BattleKey()
{
	if (IsPushKey(0x02)){		//攻撃
		enemy_HP = enemy_HP - hero_STR;
		PlayWave(1);
		flushFlg = 1;					//フラッシュさせるためのフラグ
		if( kind == 5 )
			FlushBlt(enemy_sp,0,0,64,64);	//フラッシュ画像。もとに戻らないから、元に戻す処理が必要
		else FlushBlt(enemy_sp,0,0,32,32);	//フラッシュ画像。もとに戻らないから、元に戻す処理が必要
	}
	else if (IsPushKey(0x03)){	//逃げる
		enct = 0;		//
	}
}
void EnemyFlush()
{
	if(flushFlg == 1)
	{
		flushct++;
		if(flushct > 5)
		{
			flushFlg = 0;
			flushct = 0;
			if(kind == 5)
				FlushBlt(enemy_sp,0,0,64,64);
			else FlushBlt(enemy_sp,0,0,32,32);
			turn = 1;//敵ターンに意向
		}
	}
}
void EnemyDown()
{
	if(flushct == 0)
	if(enemy_HP <= 0)
	{
		enct = 0;
		turn = 0;
		hero_EX = hero_EX + enemy_EX;
	}
}
//A character in the battle
void BattleText()
{
	TextLayerOn ( 10, 480, 160 );
	//sprintf(string[0],"d\n",hero_LV);
	TextOut ( 10, "攻撃   1" );

	TextLayerOn ( 11, 480, 180 );
	//sprintf(string[0],"d\n",hero_LV);
	TextOut ( 11, "逃げる   2" );
	
	alt
	{
		case enemy_sp == 20:
		{
			TextLayerOn ( 30, 480, 280 );
			TextOut ( 30, "ヘビ" );
		}
		case enemy_sp == 21:
		{
			TextLayerOn ( 30, 480, 280 );
			TextOut ( 30, "コウモリ" );
		}
		case enemy_sp == 22:
		{
			TextLayerOn ( 30, 480, 280 );
			TextOut ( 30, "スライム" );
		}
		case enemy_sp == 23:
		{
			TextLayerOn ( 30, 480, 280 );
			TextOut ( 30, "オバケ" );
		}
		case enemy_sp == 24:
		{
			TextLayerOn ( 30, 480, 280 );
			TextOut ( 30, "ドラゴン" );
		}
		case enemy_sp == 25:
		{
			TextLayerOn ( 30, 480, 280 );
			TextOut ( 30, "ボス" );
		}
	}
}
//A character in the normal
void ShowText()
{
	TextLayerOn ( 1, 480, 0 );
	sprintf(string[0],"LV      %d\n",hero_LV);
	TextOut ( 1, string[0] );
	
	TextLayerOn ( 2, 480, 20 );
	sprintf(string[0],"MAXHP   %d\n",hero_MAXHP);
	TextOut ( 2, string[0] );

	TextLayerOn ( 3, 480, 80 );
	sprintf(string[0],"HP      %d\n",hero_HP);
	TextOut ( 3, string[0] );
	
	TextLayerOn ( 4, 480, 100 );
	sprintf(string[0],"STR     %d\n",hero_STR);
	TextOut ( 4, string[0] );

	TextLayerOn ( 5, 480, 120 );
	sprintf(string[0],"EX      %d\n",hero_EX);
	TextOut ( 5, string[0] );

	TextLayerOn ( 6, 480, 140 );
	sprintf(string[0],"NEXT    %d\n",hero_LV * 10 * 2);
	TextOut ( 6, string[0] );
	
	TextLayerOn ( 7, 480, 340 );
	sprintf(string[0],"X    %d\n",ho);
	TextOut ( 7, string[0] );

	TextLayerOn ( 8, 480, 360 );
	sprintf(string[0],"Y    %d\n",ho2);
	TextOut ( 8, string[0] );

	TextLayerOn ( 9, 480, 380 );
	sprintf(string[0],"XY    %d\n",ho3);
	TextOut ( 9, string[0] );
	
}
void LVUP()
{
	if( hero_EX > hero_LV * 10*2+hero_LV )
	{
		hero_LV++;
		hero_MAXHP = hero_MAXHP + 5;
		hero_STR   = hero_STR + 2;
	}
}
//GameMain
void GameMain()
{
	KeyInput();
	ShowBg();		//背景表示
	if( enct < 256 )//フィールド時
	{
		if( initfiled == 0 ){
			FiledInit();
			initfiled  =1;
		}
		kind = EnemyRand();
		ShowSpr();	//スプライト表示
		Key();		//
		Hit();		//あたり判定
		hero_x = hero_x + hero_xpos;
		hero_y = hero_y + hero_ypos;
		hero_xpos = 0;
		hero_ypos = 0;

		Anim();		//スプライトアニメーション
		
		//enct = enct & 0x7f;
		TextLayerOff(10);
		TextLayerOff(11);
	}
	else//戦闘
	{
		if( initbattle == 0 ){
			BattleInit();	//戦闘前の初期化
			initbattle = 1;
		}
		BltFast(enemy_sp,226,226);
		
		if( turn != 1 )//自ターン
		{
			BattleKey();	//戦闘時のキー処理
			EnemyFlush();	//敵をフラッシュさせた後に元に戻す処理
			EnemyDown();	//敵死亡処理
		}
		else//Enemy turn
		{
			PlayWave(2);
			hero_HP = hero_HP - enemy_STR;
			turn = 0;
		}
		
		BattleText();
		if(IsPushSpaceKey())
			enct = 0;
	}
	LVUP();		//ＬＶＵＰ
	ShowText();	//テキスト表示
}
void Sea()
{

	
	for( i = 0;i < 15; i++ ){
		BltFast(101,i*32,0);//海
		BltFast(101,i*32,448);//海

		BltFast(101,0,i*32);//海
		BltFast(101,448,i*32);//海
	}
	
}
void GameInit()
{
	for( i = 0;i < 15; i++ )
		fx[i] = i * 32;//草原
	for( i = 0;i < 15; i++ ){
		fy[i] = i * 32;//草原
		Dy[i] = i * 32;//システム黒
	}
	for( i = 0; i < 5; i++ )
		Dx[i] = 480+(i)*32;
	

			
	LoadBitmap("tipp/主人公1.bmp",9,1);
	LoadBitmap("tipp/主人公2.bmp",10,1);
	LoadBitmap("tipp/回復.bmp",99,1);
	LoadBitmap("tipp/黒.bmp",100,1);
	LoadBitmap("tipp/海.bmp",101,1);
	LoadBitmap("tipp/木.bmp",102,1);
	LoadBitmap("tipp/山.bmp",103,1);
	LoadBitmap("tipp/草原.bmp",104,1);
	
	
	LoadBitmap("tipp/ヘビ.bmp",20,1);
	LoadBitmap("tipp/コウモリ.bmp",21,1);
	LoadBitmap("tipp/スライム.bmp",22,1);
	LoadBitmap("tipp/オバケ.bmp",23,1);
	LoadBitmap("tipp/ドラゴン.bmp",24,1);
	LoadBitmap("tipp/ボス.bmp",25,1);
	
	
	LoadMIDI("midi/filed1.mid"); //	ファイルを読み込む
	PlayMIDI();						//	再生開始
	
	LoadWave("wave/Hit00.wav",1);
	LoadWave("wave/enemyhit.wav",2);
	LoadWave("wave/回復.wav",3);

	
	hero_LV = 1;
	hero_MAXHP = 60;
	hero_HP = hero_MAXHP;
	hero_STR = 6;
	hero_x   = 150;
	hero_y   = 150;
}
void main()
{
	GameInit();
	loop
	{
		halt;
		if(IsPushKey(0x3b))
			SetWindow(0,640,480,16);	
		if(IsPushKey(0x3c))
			SetWindow(1,640,480,16);	
		GameMain();
		if (IsPushEscKey()) break;
			if( hero_HP <= 0 )
	
		while(1){//ゲーム尾ーバ処理
			KeyInput();
			TextLayerOn ( 50, 120, 80 );
			TextOut ( 50, "GAME OVER" );
			halt;
			if (IsPushEscKey()) goto END;
		}
	}
	END:
	
	GameRelease();
}
void GameRelease()
{
	TextLayerOff(1);
	TextLayerOff(2);
	TextLayerOff(3);
	TextLayerOff(4);
	TextLayerOff(10);
	TextLayerOff(11);
	ReleaseMIDI();					//	MIDIファイルの解放
	ReleaseWave(1);
	ReleaseWave(2);
	ReleaseWave(3);
}

