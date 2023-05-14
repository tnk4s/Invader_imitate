#pragma once
#include<iostream>
#include<string>
#include<vector>
#include <cmath>
#include"DxLib.h"


#define Me "Prototype Invaders v0.0.2"
#define PI 3.14159			// 円周率
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
	virtual vector<int> getPosition();//ミサイルの威力を含む
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

//砲台クラスの派生クラスとしてインベーダークラスを宣言。当たり判定やミサイル発射を改めて実装せずに済む。
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

//インベーダークラスの派生クラスとしてインベーダー・タイプ01クラスを宣言
//こんな感じのを増やしてインベーダーの種類を増やす。		※改造が多いのでお勧めしない。本来、このクラスの派生でミサイルのタイプや画像の差別化をすべきだがめんどくさい
class InvaderType01 : public Invader
{
public:
	InvaderType01();
};

