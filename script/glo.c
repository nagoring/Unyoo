int i,j;		//LoopCounter
int fx[20];		//����X
int fy[15];		//����Y
int Dx[5];		//�V�X�e��	
int Dy[15];		//
int hero_x;		//��l��X
int hero_y;		//��l��Y
int hero_xpos;
int hero_ypos;
int hero_sp;	//��l��SP
int hero_LV;	//��l���k�u
int hero_HP;	//��l���g�o
int hero_MAXHP;	//��l���l�`�w�g�o
int hero_STR;	//��l���r�s�q
int hero_EX;	//��l���̌o���l
int hero_muki;	//����

long ct;
int enct;		//�G�o����
int turn;		//�퓬�^�[���t���O
int enemyrandct;//�G��ޏo�������_��
int kind;		//�G�̎�ޕۑ�
int enemy_HP;
int enemy_STR;
int enemy_sp;	//
int enemy_EX;
int initbattle;	//�o�g����������
int initfiled;	//�t�B�[���h��������
int flushFlg;	//�t���b�V�������邽�߂̃t���O
int flushct;	//�t���b�V�������邽�߂̃J�E���^�[
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
