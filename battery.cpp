//砲台クラスのメゾットが記述されている

#include "Global.h"
extern int X0, Y0;

//砲台やインベーダーのインスタンスが生成されたときに呼び出される。
Battery::Battery()
{
	width = 25;//幅
	height = 25;//高さ
	
	//座標
	x = X0;
	y = Y0 * 2 - height/2;
	
	hp = 10;//HP
	missile_limit = 10;//画面に一度に存在可能なミサイル数。連射タイプのミサイルを装填した場合、この数が多いと機関銃みたいになり、少ないとバースト銃のようになる。
	my_missile.clear();//ミサイルを格納（装填）するベクター配列を初期化
	last_fire_time = GetNowCount();//現在時刻がミリ秒で入ると考えてね。詳しくは DxLib GetNowCount()で検索。
	Cr = GetColor(255, 255, 0);//黄色
}

//指定されたタイプのミサイルを装填
void Battery::setMissleType(string type)
{
	missile_type = type;//指定されたミサイルのタイプ
	for (int i = 0; i < missile_limit; i++)//設定した装填数回る
	{
		Missile tmp(missile_type);//ミサイルのインスタンスを生成。引数はミサイルタイプ。
		my_missile.push_back(tmp);//ベクター配列に格納（装填）
	}

	//選んだミサイルタイプに応じてリロード時間などが設定される。
	if(missile_type == "USER01") reload_time = 500;//[ms]
	else if (missile_type == "USER_MACHIHE_GUN")
	{
		missile_limit = 3;//連射防止、バースト式になる。多いと機関銃。
		reload_time = 50;//[ms]
	}
	else if (missile_type == "INVADER01") reload_time = 1000 + GetRand(25000);//[ms] ランダムな時間が設定される
	else if (missile_type == "INVADER02_PLUNGING") reload_time = 3000 + GetRand(25000);
}

//ゲームループあたりの砲台の移動
void Battery::move(int direction)
{
	int stride = 10;

	if (direction == 0)//左
	{
		x -= stride;//x座標をstrideに設定した値だけ左にずらす。
		if (x < 0) x = 0;//左端に来たら、0に戻してあげる。		右に動くときもほぼ同様の処理。
	}
	else//右
	{
		x += stride;
		if (x > X0 * 2) x = X0 * 2;
	}
}

//砲台を描画
void Battery::draw()
{
	if (hp <= 0) return;
	int x1 = x, x2 = x - width/2, x3 = x + width / 2;
	int y1 = y - height / 2, y2 = y + height / 2;
	int y3 = y2;

	DrawTriangle(x1, y1, x2, y2, x3, y3, Cr, TRUE);
}

//砲台から発射されたミサイルを描画
void Battery::drawMissile()
{
	for (int i = 0; i < missile_limit; i++)
	{
		my_missile[i].draw();
	}
}

//砲台にミサイルを発射させる
void Battery::attack()
{
	int flag = 0;
	if (hp <= 0) return;//砲台のHPが0なら発射できない
	if (GetNowCount() - last_fire_time < reload_time) return;//リロード中　前回の発射からリロード時間経過していない

	for(int i=0;i<missile_limit;i++)
	{
		flag = my_missile[i].fire(x, y);//指定したミサイルに対して、発射させる。発射成功であれば1が返ってきてflagに格納。既に発射済みであれば0が返ってくる。
		if (flag == 1)//発射成功であれば
		{
			last_fire_time = GetNowCount();//発射した時刻を記録
			break;
		}
	}
}

//砲台のHPを取得
int Battery::getHP() { return hp; }

//砲台の座標を取得
vector<int> Battery::getPosition()
{
	vector<int> position;
	position.clear();
	position.push_back(x);
	position.push_back(y);

	return position;//positon[0] x座標、　positono[1] y座標
}

//砲台に装填されたミサイルの内、発射中のミサイルの座標を取得
vector<vector<int>> Battery::getMissilePosition()
{
	vector<vector<int>> positions;//ベクターの二重配列
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

//ミサイルの座標が送られてくるので、それが自分の当たり判定内であればダメージを負う。
int Battery::takeDamage(int damage, int mx, int my)
{
	if (hp <= 0) return 0;//そもそもHP0なので当たり判定なし
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
				return 1;//HPが0になった
			}
			else return 2;//ダメージのみ
		}
	}
	return 0;//被弾せず
}

//指定したミサイルを消す。着弾時に使用。これが適切に呼ばれなければモンハンの貫通弾lv3のような挙動になる。
void Battery::delMissile(int index)
{
	if (index < missile_limit) my_missile[index].hit();
}