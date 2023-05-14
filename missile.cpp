#include "Global.h"
extern int X0, Y0;

//ミサイルインスタンスが生成されるときに呼ばれる。
Missile::Missile(string type)
{
	draw_flag = 0;//ミサイルが描画されているか否か（発射中か否か）。0であれば未発射、1なら発射中
	width = 6;//幅
	height = 10;//高さ
	missile_type = type;//ミサイルタイプ

	//ミサイルタイプに応じてダメージ量と色を設定
	//ミサイルタイプを自分で追加してみて、オリジナルのミサイルを作ってみよう。
	if (missile_type == "USER01")
	{
		power = 5;
		Cr = GetColor(255, 255, 255);//白
	}
	else if (missile_type == "USER_MACHIHE_GUN")
	{
		power = 2;
		Cr = GetColor(0, 0, 255);//青
	}
	else if (missile_type == "INVADER01")
	{
		power = 1;
		Cr = GetColor(255, 0, 0);//赤
	}
	else if (missile_type == "INVADER02_PLUNGING")
	{
		power = 2;
		Cr = GetColor(255, 255, 0);
	}
}

//ミサイルを発射する
int Missile::fire(int ix, int iy)
{
	if (!draw_flag)//未発射なら
	{
		draw_flag = 1;
		x = ix;
		y = iy;

		return 1;//発射成功
	}
	else return -1;//不発
}

//ミサイルの軌道を設定する。弾道計算。
void Missile::ballisticCalculation()//ミサイルのスピード・軌道に関係
{
	//ユーザー側
	if(missile_type == "USER01") y -= 10;//減らす量が多ければ多いほど高速なミサイルになる。
	else if(missile_type == "USER_MACHIHE_GUN") y -= 15;

	//インベーダー側
	else if (missile_type == "INVADER01") y += 5;
	else if (missile_type == "INVADER02_PLUNGING")
	{
		y += 5;
		if (GetNowCount() / 1000 % 2 == 0) x += 2;
		else x -= 2;
	}

	//x座標も上手くいじると......!!		トリッキーな起動のミサイルを作れるかも
}

//ミサイルを描画
void Missile::draw()
{
	if (draw_flag)
	{
		if (y < 0 || y > Y0 * 2) draw_flag = 0;
		else if (x<0 || x>X0 * 2) draw_flag = 0;
		else {
			ballisticCalculation();//弾道計算
			int x1 = x - width / 2, x2 = x + width / 2;
			int y1 = y - height / 2, y2 = y + height / 2;
			DrawBox(x1, y1, x2, y2, Cr, TRUE);
		}
	}	
}

//着弾したらミサイルを消して、未発射状態へ
void Missile::hit()
{
	draw_flag = 0;
}

//ミサイルの描画状態（発射状態）を取得
int Missile::getDrawFlag() { return draw_flag; };

//ミサイルのダメージ量、座標を取得
vector<int> Missile::getPosition()
{
	vector<int> position;
	position.clear();
	position.push_back(power);
	position.push_back(x);
	position.push_back(y);
	
	return position;
}