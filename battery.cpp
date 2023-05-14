//�C��N���X�̃��]�b�g���L�q����Ă���

#include "Global.h"
extern int X0, Y0;

//�C���C���x�[�_�[�̃C���X�^���X���������ꂽ�Ƃ��ɌĂяo�����B
Battery::Battery()
{
	width = 25;//��
	height = 25;//����
	
	//���W
	x = X0;
	y = Y0 * 2 - height/2;
	
	hp = 10;//HP
	missile_limit = 10;//��ʂɈ�x�ɑ��݉\�ȃ~�T�C�����B�A�˃^�C�v�̃~�T�C���𑕓U�����ꍇ�A���̐��������Ƌ@�֏e�݂����ɂȂ�A���Ȃ��ƃo�[�X�g�e�̂悤�ɂȂ�B
	my_missile.clear();//�~�T�C�����i�[�i���U�j����x�N�^�[�z���������
	last_fire_time = GetNowCount();//���ݎ������~���b�œ���ƍl���ĂˁB�ڂ����� DxLib GetNowCount()�Ō����B
	Cr = GetColor(255, 255, 0);//���F
}

//�w�肳�ꂽ�^�C�v�̃~�T�C���𑕓U
void Battery::setMissleType(string type)
{
	missile_type = type;//�w�肳�ꂽ�~�T�C���̃^�C�v
	for (int i = 0; i < missile_limit; i++)//�ݒ肵�����U�����
	{
		Missile tmp(missile_type);//�~�T�C���̃C���X�^���X�𐶐��B�����̓~�T�C���^�C�v�B
		my_missile.push_back(tmp);//�x�N�^�[�z��Ɋi�[�i���U�j
	}

	//�I�񂾃~�T�C���^�C�v�ɉ����ă����[�h���ԂȂǂ��ݒ肳���B
	if(missile_type == "USER01") reload_time = 500;//[ms]
	else if (missile_type == "USER_MACHIHE_GUN")
	{
		missile_limit = 3;//�A�˖h�~�A�o�[�X�g���ɂȂ�B�����Ƌ@�֏e�B
		reload_time = 50;//[ms]
	}
	else if (missile_type == "INVADER01") reload_time = 1000 + GetRand(25000);//[ms] �����_���Ȏ��Ԃ��ݒ肳���
	else if (missile_type == "INVADER02_PLUNGING") reload_time = 3000 + GetRand(25000);
}

//�Q�[�����[�v������̖C��̈ړ�
void Battery::move(int direction)
{
	int stride = 10;

	if (direction == 0)//��
	{
		x -= stride;//x���W��stride�ɐݒ肵���l�������ɂ��炷�B
		if (x < 0) x = 0;//���[�ɗ�����A0�ɖ߂��Ă�����B		�E�ɓ����Ƃ����قړ��l�̏����B
	}
	else//�E
	{
		x += stride;
		if (x > X0 * 2) x = X0 * 2;
	}
}

//�C���`��
void Battery::draw()
{
	if (hp <= 0) return;
	int x1 = x, x2 = x - width/2, x3 = x + width / 2;
	int y1 = y - height / 2, y2 = y + height / 2;
	int y3 = y2;

	DrawTriangle(x1, y1, x2, y2, x3, y3, Cr, TRUE);
}

//�C�䂩�甭�˂��ꂽ�~�T�C����`��
void Battery::drawMissile()
{
	for (int i = 0; i < missile_limit; i++)
	{
		my_missile[i].draw();
	}
}

//�C��Ƀ~�T�C���𔭎˂�����
void Battery::attack()
{
	int flag = 0;
	if (hp <= 0) return;//�C���HP��0�Ȃ甭�˂ł��Ȃ�
	if (GetNowCount() - last_fire_time < reload_time) return;//�����[�h���@�O��̔��˂��烊���[�h���Ԍo�߂��Ă��Ȃ�

	for(int i=0;i<missile_limit;i++)
	{
		flag = my_missile[i].fire(x, y);//�w�肵���~�T�C���ɑ΂��āA���˂�����B���ː����ł����1���Ԃ��Ă���flag�Ɋi�[�B���ɔ��ˍς݂ł����0���Ԃ��Ă���B
		if (flag == 1)//���ː����ł����
		{
			last_fire_time = GetNowCount();//���˂����������L�^
			break;
		}
	}
}

//�C���HP���擾
int Battery::getHP() { return hp; }

//�C��̍��W���擾
vector<int> Battery::getPosition()
{
	vector<int> position;
	position.clear();
	position.push_back(x);
	position.push_back(y);

	return position;//positon[0] x���W�A�@positono[1] y���W
}

//�C��ɑ��U���ꂽ�~�T�C���̓��A���˒��̃~�T�C���̍��W���擾
vector<vector<int>> Battery::getMissilePosition()
{
	vector<vector<int>> positions;//�x�N�^�[�̓�d�z��
	vector<int> tmp;
	for (int i = 0; i < missile_limit; i++)
	{
		if (my_missile[i].getDrawFlag())
		{
			tmp = my_missile[i].getPosition();
			tmp.push_back(i);
			positions.push_back(tmp);
			tmp.clear();
		}
	}
	return positions;
}

//�~�T�C���̍��W�������Ă���̂ŁA���ꂪ�����̓����蔻����ł���΃_���[�W�𕉂��B
int Battery::takeDamage(int damage, int mx, int my)
{
	if (hp <= 0) return 0;//��������HP0�Ȃ̂œ����蔻��Ȃ�
	int x1 = x - width/2, x2 = x + width/2;
	int y1 = y - height/2, y2 = y + height/2;
	if (x1 <= mx && x2 >= mx)
	{
		if (y1 <= my && y2 >= my)
		{
			hp -= damage;
			if (hp <= 0)
			{
				hp = 0;
				return 1;//HP��0�ɂȂ���
			}
			else return 2;//�_���[�W�̂�
		}
	}
	return 0;//��e����
}

//�w�肵���~�T�C���������B���e���Ɏg�p�B���ꂪ�K�؂ɌĂ΂�Ȃ���΃����n���̊ђʒelv3�̂悤�ȋ����ɂȂ�B
void Battery::delMissile(int index)
{
	if (index < missile_limit) my_missile[index].hit();
}