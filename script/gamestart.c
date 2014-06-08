include "script/glo.c"
//�G�������_���ɏo��
int EnemyRand()
{
	enemyrandct = (enemyrandct + 1) % 5;
	return enemyrandct;
}
void awPlayWave( int lp )
{
	loop {			// ���[�v�ł܂��܂�

		if (!IsPlayWave(lp)) break;
		// �`�����l���P��Wave�̍Đ����I�����Ă����loop���甲���܂�
		// !�́A�ے艉�Z�q�ł�

		halt;		// �������[�v���ɂ́Ahalt�������ł����ˁB
	}
}
//Background indication
void ShowBg()
{
/*	for(i=0;i<15;i++)
	for(j=0;j<15;j++)
		BltFast(104,fx[i],fy[j]);//����
		

	BltFast(99,life_x,life_y);//��

	Sea();
*/
	for(i=0;i<15*15;i++)
		BltFast(map[i]+100,fx[i%15],fy[i/15]);

	for(i=0;i<5;i++)
	for(j=0;j<15;j++)
		BltFast(100,Dx[i],Dy[j]);//�V�X�e����

}
//The initialization of the filed
void FiledInit()
{
	ReleaseMIDI();					//	MIDI�t�@�C���̉��
	LoadMIDI("midi/filed1.mid"); 	//	�t�@�C����ǂݍ���
	PlayMIDI();						//	�Đ��J�n
	
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
			PlayWave(3);	//��
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
		hero_muki = 4;	//��
	}
	else if(IsPressDownKey()){
		hero_ypos = 2;
		enct++;
		hero_muki = 3;	//��
	}
	else if(IsPressLeftKey()){	//	���ݍ��L�[��������Ă��邩�𔻒肵�܂��B
		hero_xpos = -2;
		enct++;
		hero_muki = 2;	//��
	}
	
	else if(IsPressRightKey()){	//	���݉E�L�[��������Ă��邩�𔻒肵�܂��B
		hero_xpos = 2;
		enct++;
		hero_muki = 1;	//�E
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
	if( kind == 0){		//�w�r
		enemy_HP  = 10;
		enemy_STR = 5;
		enemy_sp  = 20;
		enemy_EX  = 3;
	}
	else if( kind == 1){//�R�E����
		enemy_HP  = 10;
		enemy_STR = 7;
		enemy_sp  = 21;
		enemy_EX  = 10;
	}
	else if( kind == 2){//�X���C��
		enemy_HP  = 18;
		enemy_STR = 15;
		enemy_sp  = 22;
		enemy_EX  = 50;
	}
	else if( kind == 3){//�I�o�P
		enemy_HP  = 100;
		enemy_STR = 9;
		enemy_sp  = 23;
		enemy_EX  = 200;
	}
	else if( kind == 4){//�h���S��
		enemy_HP  = 1000;
		enemy_STR = 15;
		enemy_sp  = 24;
		enemy_EX  = 3000;
	}
	else if( kind == 5){//�{�X
		enemy_HP  = 44444;
		enemy_STR = 50;
		enemy_sp  = 25;
		enemy_EX  = 30000;
	}
	ReleaseMIDI();					//	MIDI�t�@�C���̉��
	LoadMIDI("midi/battle1.mid"); //	�t�@�C����ǂݍ���
	PlayMIDI();						//	�Đ��J�n
	
	initfiled = 0;

}
//Battle in the key
void BattleKey()
{
	if (IsPushKey(0x02)){		//�U��
		enemy_HP = enemy_HP - hero_STR;
		PlayWave(1);
		flushFlg = 1;					//�t���b�V�������邽�߂̃t���O
		if( kind == 5 )
			FlushBlt(enemy_sp,0,0,64,64);	//�t���b�V���摜�B���Ƃɖ߂�Ȃ�����A���ɖ߂��������K�v
		else FlushBlt(enemy_sp,0,0,32,32);	//�t���b�V���摜�B���Ƃɖ߂�Ȃ�����A���ɖ߂��������K�v
	}
	else if (IsPushKey(0x03)){	//������
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
			turn = 1;//�G�^�[���Ɉӌ�
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
	TextOut ( 10, "�U��   1" );

	TextLayerOn ( 11, 480, 180 );
	//sprintf(string[0],"d\n",hero_LV);
	TextOut ( 11, "������   2" );
	
	alt
	{
		case enemy_sp == 20:
		{
			TextLayerOn ( 30, 480, 280 );
			TextOut ( 30, "�w�r" );
		}
		case enemy_sp == 21:
		{
			TextLayerOn ( 30, 480, 280 );
			TextOut ( 30, "�R�E����" );
		}
		case enemy_sp == 22:
		{
			TextLayerOn ( 30, 480, 280 );
			TextOut ( 30, "�X���C��" );
		}
		case enemy_sp == 23:
		{
			TextLayerOn ( 30, 480, 280 );
			TextOut ( 30, "�I�o�P" );
		}
		case enemy_sp == 24:
		{
			TextLayerOn ( 30, 480, 280 );
			TextOut ( 30, "�h���S��" );
		}
		case enemy_sp == 25:
		{
			TextLayerOn ( 30, 480, 280 );
			TextOut ( 30, "�{�X" );
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
	ShowBg();		//�w�i�\��
	if( enct < 256 )//�t�B�[���h��
	{
		if( initfiled == 0 ){
			FiledInit();
			initfiled  =1;
		}
		kind = EnemyRand();
		ShowSpr();	//�X�v���C�g�\��
		Key();		//
		Hit();		//�����蔻��
		hero_x = hero_x + hero_xpos;
		hero_y = hero_y + hero_ypos;
		hero_xpos = 0;
		hero_ypos = 0;

		Anim();		//�X�v���C�g�A�j���[�V����
		
		//enct = enct & 0x7f;
		TextLayerOff(10);
		TextLayerOff(11);
	}
	else//�퓬
	{
		if( initbattle == 0 ){
			BattleInit();	//�퓬�O�̏�����
			initbattle = 1;
		}
		BltFast(enemy_sp,226,226);
		
		if( turn != 1 )//���^�[��
		{
			BattleKey();	//�퓬���̃L�[����
			EnemyFlush();	//�G���t���b�V����������Ɍ��ɖ߂�����
			EnemyDown();	//�G���S����
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
	LVUP();		//�k�u�t�o
	ShowText();	//�e�L�X�g�\��
}
void Sea()
{

	
	for( i = 0;i < 15; i++ ){
		BltFast(101,i*32,0);//�C
		BltFast(101,i*32,448);//�C

		BltFast(101,0,i*32);//�C
		BltFast(101,448,i*32);//�C
	}
	
}
void GameInit()
{
	for( i = 0;i < 15; i++ )
		fx[i] = i * 32;//����
	for( i = 0;i < 15; i++ ){
		fy[i] = i * 32;//����
		Dy[i] = i * 32;//�V�X�e����
	}
	for( i = 0; i < 5; i++ )
		Dx[i] = 480+(i)*32;
	

			
	LoadBitmap("tipp/��l��1.bmp",9,1);
	LoadBitmap("tipp/��l��2.bmp",10,1);
	LoadBitmap("tipp/��.bmp",99,1);
	LoadBitmap("tipp/��.bmp",100,1);
	LoadBitmap("tipp/�C.bmp",101,1);
	LoadBitmap("tipp/��.bmp",102,1);
	LoadBitmap("tipp/�R.bmp",103,1);
	LoadBitmap("tipp/����.bmp",104,1);
	
	
	LoadBitmap("tipp/�w�r.bmp",20,1);
	LoadBitmap("tipp/�R�E����.bmp",21,1);
	LoadBitmap("tipp/�X���C��.bmp",22,1);
	LoadBitmap("tipp/�I�o�P.bmp",23,1);
	LoadBitmap("tipp/�h���S��.bmp",24,1);
	LoadBitmap("tipp/�{�X.bmp",25,1);
	
	
	LoadMIDI("midi/filed1.mid"); //	�t�@�C����ǂݍ���
	PlayMIDI();						//	�Đ��J�n
	
	LoadWave("wave/Hit00.wav",1);
	LoadWave("wave/enemyhit.wav",2);
	LoadWave("wave/��.wav",3);

	
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
	
		while(1){//�Q�[�����[�o����
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
	ReleaseMIDI();					//	MIDI�t�@�C���̉��
	ReleaseWave(1);
	ReleaseWave(2);
	ReleaseWave(3);
}

