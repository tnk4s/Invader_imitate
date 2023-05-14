#pragma once
#include<iostream>
#include<string>
#include<vector>
#include <cmath>
#include"DxLib.h"


#define Me "Prototype Invaders v0.0.2"
#define PI 3.14159			// �~����
using namespace std;

class Missile
{
protected:
	int draw_flag;
	int width, height;
	int x, y;
	int power;
	string missile_type;
	unsigned int Cr;

	virtual void ballisticCalculation();
public:
	Missile(string type);
	virtual int getDrawFlag();
	virtual vector<int> getPosition();//�~�T�C���̈З͂��܂�
	int fire(int ix, int iy);
	virtual void draw();
	virtual void hit();
};

class Battery
{
protected:
	int width, height;
	int x, y;
	int hp;
	int missile_limit, reload_time;
	int last_fire_time;
	string missile_type;
	vector <Missile> my_missile;
	unsigned int Cr;

public:
	Battery();
	virtual vector<int> getPosition();
	virtual vector<vector<int>> getMissilePosition();
	virtual int getHP();
	virtual void draw();
	virtual void move(int direction);
	virtual void attack();
	virtual void drawMissile();
	virtual void setMissleType(string type);
	virtual int takeDamage(int damage, int mx, int my);
	virtual void delMissile(int index);
};

//�C��N���X�̔h���N���X�Ƃ��ăC���x�[�_�[�N���X��錾�B�����蔻���~�T�C�����˂����߂Ď��������ɍςށB
class Invader :public Battery 
{
protected:
	double dy;
	int img_handle;
	string img_file;
public:
	void draw();
	void move();
	void setPosition(int ix, int iy);
	void setImage(string imgfile);
};

//�C���x�[�_�[�N���X�̔h���N���X�Ƃ��ăC���x�[�_�[�E�^�C�v01�N���X��錾
//����Ȋ����̂𑝂₵�ăC���x�[�_�[�̎�ނ𑝂₷�B		�������������̂ł����߂��Ȃ��B�{���A���̃N���X�̔h���Ń~�T�C���̃^�C�v��摜�̍��ʉ������ׂ������߂�ǂ�����
class InvaderType01 : public Invader
{
public:
	InvaderType01();
};

