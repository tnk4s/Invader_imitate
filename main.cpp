#include "Global.h"

//��ʂ̒��S���W
int X0 = 320;
int Y0 = 240;

//��ʃT�C�Y
int win_size_x = X0 * 2;
int win_size_y = Y0 * 2;

Battery my_battery;//�C��̃C���X�^���X
vector <InvaderType01> invader_type01s;//�C���x�[�_�[�̃C���X�^���X�������i�[�����x�N�^�[�z��
int invader_line = 3, invader_num;//�C���x�[�_�[�̗񐔂ƃC���x�[�_�[�����̐������ꂽ�̂�

//�Q�[���J�n���ɃC���x�[�_�[�̃C���X�^���X�����A���ꂼ����ǂ��ɔz�u����̂��̍��W��^���Ă���֐��B
int setInvaders(int line)
{
	int counter = 0;//�C���x�[�_�[�𐔂��Ă����ϐ�
	for (int i = 0; i < line; i++)//�C���x�[�_�[������z�u���邩�����߂�Afor���̉�鐔�����C���x�[�_�[�̗񂪑�����B
	{
		for (int j = 0; j < X0 * 2 / 25; j++)//�C���x�[�_�[�����ɕ��ׂĂ����B��ʕ����C���x�[�_�[�̉����̐��B
		{
			InvaderType01 tmp_01;//�C���x�[�_�[�̉��̃C���X�^���X�𐶐�
			invader_type01s.push_back(tmp_01);//�C���x�[�_�[�������i�[����C���x�[�_�[�E�^�C�v01�̃x�N�^�[�z��ɁA�C���x�[�_�[���i�[���Ă����BC++ vector���Q�ƁB
			invader_type01s[counter].setPosition(j * 25 + 20, i * 25 + 14);//�i�[���ꂽ�C���x�[�_�[�ɑ΂��A�ǂ��ɔz�u����邩�̍��W���Z�b�g
			if (i != 0)
			{
				invader_type01s[counter].setMissleType("INVADER01");//���̃C���x�[�_�[�ɂǂ�ȃ~�T�C���^�C�v�𑕓U�����邩�����߂�B������Ԃł́uINVADER01�v�Ƃ����~�T�C�������U�����Bmissile.cpp�ɐV�����~�T�C���^�C�v��錾���Ă݂悤�B
				invader_type01s[counter].setImage("./img/Invader01.png");
			}
			else
			{
				invader_type01s[counter].setMissleType("INVADER02_PLUNGING");
				invader_type01s[counter].setImage("./img/Invader02.png");
			}
			counter++;

		}
	}
	return counter;//���ʁA���̂̃C���x�[�_�[���������ꂽ�̂���Ԃ��B
}

//�Q�[���v���O�������͂��߂Ɏ��s���鏈���������ꂽ�֐�
void myInit()
{
	//my_battery.setMissleType("USER01");
	my_battery.setMissleType("USER_MACHIHE_GUN");//���[�U�[�������삷��C��Ƀ~�T�C���^�C�v���w�肵�A���U�B������Ԃł́uUSER_MACHIHE_GUN�v�Ƃ���3�_�o�[�X�g�e�����U�����B���ɂ́uUSER01�v�Ƃ����P���̃~�T�C���������ς݁Bmissile.cpp�Q�ƁB
	invader_num = setInvaders(invader_line);//�C���x�[�_�[�����𐶐�����֐����ĂԁB
}

//�Q�[�����[�v�̂��тɌĂяo����A���s�𔻒f����֐��B
int gameJudgment()
{
	vector<int> position;//�C���x�[�_�[�����̍��W���i�[�����x�N�^�[�z��Bposition[0]��x���W�Aposition[1]��y���W�B
	int ihp, inv_counter = 0;
	//����
	for (int i = 0; i < invader_num; i++)
	{
		ihp = invader_type01s[i].getHP();
		if (ihp <= 0) inv_counter++;//HP��0�̃C���x�[�_�[�𐔂��Ă����B
	}
	if (inv_counter == invader_num) return 2;//HP0�̃C���x�[�_�[���������ꂽ�C���x�[�_�[�̐��Ɠ������Ȃ�A2��Ԃ��B�v���C���[�̏����B

	//�s�k
	if (my_battery.getHP() <= 0) return 1;//�v���C���[��HP��0�ɂȂ����B�s�k�B
	else {
		for (int i = 0; i < invader_num; i++)//�C���x�[�_�[�̐������`�F�b�N
		{
			position = invader_type01s[i].getPosition();
			if (position[1] >= Y0 * 2) return 1;//�C���x�[�_�[�̒��S������ʂɐڐG�B�s�k
		}
	}
	return 0;//���s�����Ă��Ȃ��B
}

//�Q�[���I�����ɉ摜��\������֐��B�ڍח��B
void drawGameSet(int result)
{
	int width, height;
	string img_file = "";
	if (result == 2)img_file = "./img/text_gameclear_e.png";
	else if (result == 1) img_file = "./img/text_gameover_e.png";
	WaitTimer(500);
	int img_handle = LoadGraph(img_file.c_str());
	GetGraphSize(img_handle, &width, &height);

	int x1 = X0 - width / 4, x2 = X0 + width / 4;
	int y1 = Y0 - height / 4, y2 = Y0 + height / 4;
	DrawExtendGraph(x1, y1, x2, y2, img_handle, TRUE);

	DeleteGraph(img_handle);// �ǂݍ��񂾉摜�̃O���t�B�b�N�n���h�����폜
}

//main�֐��ɑ�������B�ڍׂ͎����œǂ�ł݂悤�B�X�y���I�ɉ�������Ă���̂��q���g�ɂȂ��Ă���͂��B���Ԃ�...�B
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)// �v���O������ WinMain ����n�܂�܂�
{
	int Key;
	LONGLONG Time;
	string text = "", text_hp = "";
	vector<vector<int>> missile_positions;//�~�T�C���̈З͂��܂�
	int death_flag = 0;//�����m�F���Ɏg�p
	int result = 0;

	SetWindowText(Me);
	ChangeWindowMode(TRUE);
	SetAlwaysRunFlag(TRUE);
	SetDrawScreen(DX_SCREEN_BACK);// �`���𗠉�ʂɃZ�b�g
	SetBackgroundColor(0, 0, 0);

	SetGraphMode(win_size_x, win_size_y, 32);
	SetFontSize(20);
	ChangeFont("�l�r ����");

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}
	myInit();

	// �Q�[�����[�v�B���̃��[�v���Q�[���I���܂ŉ�葱����B����`�悷����̂��ς�邩��A�A�j���Ɠ��������œ����Č�����B
	Time = GetNowHiPerformanceCount() + 1000000 / 60;
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		{//���͎擾
			Key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

			if (Key & PAD_INPUT_RIGHT) my_battery.move(1);	// �E�������Ă�����E�ɐi��
			if (Key & PAD_INPUT_LEFT) my_battery.move(0);	// ���������Ă����獶�ɐi��
			if (Key & PAD_INPUT_UP) my_battery.attack();	//�����������U��

		}

		{//�`��
			ClearDrawScreen();// ��ʂ̏�����

			text_hp = to_string(my_battery.getHP());
			text = "HP : " + text_hp;
			DrawString(0, 0, text.c_str(), GetColor(255, 255, 255));

			//�C��`��
			my_battery.draw();
			my_battery.drawMissile();

			//�C���x�[�_�[�`��
			for (int i = 0; i < invader_num; i++)
			{
				invader_type01s[i].draw();
				invader_type01s[i].attack();//�`��Ƃقړ����^�C�~���O�ŃC���x�[�_�[�͎����ōU������B
				invader_type01s[i].drawMissile();
			}

			ScreenFlip();// ����ʂ̓��e��\��ʂɔ��f

			// ���ԑ҂�
			while (GetNowHiPerformanceCount() < Time) {}
			Time += 1000000 / 60;
		}

		if (result != 0) break;//�`��̊֌W�ケ���ɔz�u

		{//�����蔻��
			//�C�䑤
			missile_positions.clear();
			for (int i = 0; i < invader_num; i++)//�C���x�[�_�[�̐������`�F�b�N
			{
				missile_positions = invader_type01s[i].getMissilePosition();
				for (int j = 0; j < missile_positions.size(); j++)//�~�T�C���̐������`�F�b�N
				{

					death_flag = my_battery.takeDamage(missile_positions[j][0], missile_positions[j][1], missile_positions[j][2]);
					if (death_flag)
					{
						invader_type01s[i].delMissile(missile_positions[j][3]);
					}
					death_flag = 0;
				}
				missile_positions.clear();
			}

			//�C���x�[�_�[��
			missile_positions.clear();
			missile_positions = my_battery.getMissilePosition();
			for (int i = 0; i < invader_num; i++)//�C���x�[�_�[�̐������`�F�b�N
			{
				for (int j = 0; j < missile_positions.size(); j++)//�~�T�C���̐������`�F�b�N
				{

					death_flag = invader_type01s[i].takeDamage(missile_positions[j][0], missile_positions[j][1], missile_positions[j][2]);
					if (death_flag)
					{
						my_battery.delMissile(missile_positions[j][3]);
					}
					death_flag = 0;
				}
			}
			missile_positions.clear();
		}


		result = gameJudgment();
	}

	if (result != 0)
	{
		drawGameSet(result);
		ScreenFlip();

	}
	WaitKey();        // ���ʂ����邽�߂ɃL�[�҂�(�wWaitKey�x���g�p)
	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}