//�C���x�[�_�[�N���X�̃��]�b�g�֐����L�q����Ă���
//�C���x�[�_�[�N���X�͖C��N���X����h���������̂Ȃ̂ŁA�C���x�[�_�[�N���X�͎�����A�C��N���X�̃��]�b�g�֐����g����B�܂�C��Ɠ�������������Ƃ���͎������Ȃ��Ă悢�I�I

#include "Global.h"
extern int X0, Y0;

//�C���x�[�_�[�̍��W��ݒ�
void Invader::setPosition(int ix, int iy)
{
	x = ix;
	y = iy;
	dy = (double)iy;
}

//�C���x�[�_�[�̍��W�𓮂����B
void Invader::move()
{
	double stride = 0.1;//�ړ���[px]
	dy += stride;
	y = (int)dy;
}

//�C���x�[�_�[��`��A�C��ƈႢ�摜��`�悷��
void Invader::draw()
{
	if (hp <= 0) return;
	move();//�ړ�������
	int x1 = x - width/2, x2 = x + width/2;
	int y1 = y - height/2, y2 = y + height/2;

	DrawExtendGraph(x1, y1, x2, y2, img_handle, TRUE);
	//DrawBox(x1, y1, x2, y2, Cr, TRUE);
}

void Invader::setImage(string imgfile)
{
	img_file = imgfile;
	img_handle = LoadGraph(img_file.c_str());
}

//�C���x�[�_�[�N���X����h�������C���x�[�_�[�E�^�C�v01�N���X���������ꂽ�Ƃ��ɌĂ΂��
//�����Őݒ肷��l��ς��邱�ƂŃC���x�[�_�[�̑傫����HP�A�摜�A���e�������߂�B	���~�T�C���^�C�v�͕�
InvaderType01::InvaderType01()
{
	hp = 5;
	width = 25;
	height = 25;

	missile_limit = 1;
}

