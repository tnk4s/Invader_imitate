#include "Global.h"
extern int X0, Y0;

//�~�T�C���C���X�^���X�����������Ƃ��ɌĂ΂��B
Missile::Missile(string type)
{
	draw_flag = 0;//�~�T�C�����`�悳��Ă��邩�ۂ��i���˒����ۂ��j�B0�ł���Ζ����ˁA1�Ȃ甭�˒�
	width = 6;//��
	height = 10;//����
	missile_type = type;//�~�T�C���^�C�v

	//�~�T�C���^�C�v�ɉ����ă_���[�W�ʂƐF��ݒ�
	//�~�T�C���^�C�v�������Œǉ����Ă݂āA�I���W�i���̃~�T�C��������Ă݂悤�B
	if (missile_type == "USER01")
	{
		power = 5;
		Cr = GetColor(255, 255, 255);//��
	}
	else if (missile_type == "USER_MACHIHE_GUN")
	{
		power = 2;
		Cr = GetColor(0, 0, 255);//��
	}
	else if (missile_type == "INVADER01")
	{
		power = 1;
		Cr = GetColor(255, 0, 0);//��
	}
	else if (missile_type == "INVADER02_PLUNGING")
	{
		power = 2;
		Cr = GetColor(255, 255, 0);
	}
}

//�~�T�C���𔭎˂���
int Missile::fire(int ix, int iy)
{
	if (!draw_flag)//�����˂Ȃ�
	{
		draw_flag = 1;
		x = ix;
		y = iy;

		return 1;//���ː���
	}
	else return -1;//�s��
}

//�~�T�C���̋O����ݒ肷��B�e���v�Z�B
void Missile::ballisticCalculation()//�~�T�C���̃X�s�[�h�E�O���Ɋ֌W
{
	//���[�U�[��
	if(missile_type == "USER01") y -= 10;//���炷�ʂ�������Α����قǍ����ȃ~�T�C���ɂȂ�B
	else if(missile_type == "USER_MACHIHE_GUN") y -= 15;

	//�C���x�[�_�[��
	else if (missile_type == "INVADER01") y += 5;
	else if (missile_type == "INVADER02_PLUNGING")
	{
		y += 5;
		if (GetNowCount() / 1000 % 2 == 0) x += 2;
		else x -= 2;
	}

	//x���W����肭�������......!!		�g���b�L�[�ȋN���̃~�T�C�������邩��
}

//�~�T�C����`��
void Missile::draw()
{
	if (draw_flag)
	{
		if (y < 0 || y > Y0 * 2) draw_flag = 0;
		else if (x<0 || x>X0 * 2) draw_flag = 0;
		else {
			ballisticCalculation();//�e���v�Z
			int x1 = x - width / 2, x2 = x + width / 2;
			int y1 = y - height / 2, y2 = y + height / 2;
			DrawBox(x1, y1, x2, y2, Cr, TRUE);
		}
	}	
}

//���e������~�T�C���������āA�����ˏ�Ԃ�
void Missile::hit()
{
	draw_flag = 0;
}

//�~�T�C���̕`���ԁi���ˏ�ԁj���擾
int Missile::getDrawFlag() { return draw_flag; };

//�~�T�C���̃_���[�W�ʁA���W���擾
vector<int> Missile::getPosition()
{
	vector<int> position;
	position.clear();
	position.push_back(power);
	position.push_back(x);
	position.push_back(y);
	
	return position;
}