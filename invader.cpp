//インベーダークラスのメゾット関数が記述されている
//インベーダークラスは砲台クラスから派生したものなので、インベーダークラスは事実上、砲台クラスのメゾット関数も使える。つまり砲台と同じ挙動をするところは実装しなくてよい！！

#include "Global.h"
extern int X0, Y0;

//インベーダーの座標を設定
void Invader::setPosition(int ix, int iy)
{
	x = ix;
	y = iy;
	dy = (double)iy;
}

//インベーダーの座標を動かす。
void Invader::move()
{
	double stride = 0.1;//移動量[px]
	dy += stride;
	y = (int)dy;
}

//インベーダーを描画、砲台と違い画像を描画する
void Invader::draw()
{
	if (hp <= 0) return;
	move();//移動させる
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

//インベーダークラスから派生したインベーダー・タイプ01クラスが生成されたときに呼ばれる
//ここで設定する値を変えることでインベーダーの大きさやHP、画像、装弾数を決める。	※ミサイルタイプは別
InvaderType01::InvaderType01()
{
	hp = 5;
	width = 25;
	height = 25;

	missile_limit = 1;
}

