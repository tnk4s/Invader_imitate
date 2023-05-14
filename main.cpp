#include "Global.h"

//画面の中心座標
int X0 = 320;
int Y0 = 240;

//画面サイズ
int win_size_x = X0 * 2;
int win_size_y = Y0 * 2;

Battery my_battery;//砲台のインスタンス
vector <InvaderType01> invader_type01s;//インベーダーのインスタンスたちが格納されるベクター配列
int invader_line = 3, invader_num;//インベーダーの列数とインベーダーが何体生成されたのか

//ゲーム開始時にインベーダーのインスタンスを作り、それぞれをどこに配置するのかの座標を与えている関数。
int setInvaders(int line)
{
	int counter = 0;//インベーダーを数えていく変数
	for (int i = 0; i < line; i++)//インベーダーを何列配置するかを決める、for文の回る数だけインベーダーの列が増える。
	{
		for (int j = 0; j < X0 * 2 / 25; j++)//インベーダーを横に並べていく。画面幅÷インベーダーの横幅の数。
		{
			InvaderType01 tmp_01;//インベーダーの仮のインスタンスを生成
			invader_type01s.push_back(tmp_01);//インベーダーたちを格納するインベーダー・タイプ01のベクター配列に、インベーダーを格納していく。C++ vectorを参照。
			invader_type01s[counter].setPosition(j * 25 + 20, i * 25 + 14);//格納されたインベーダーに対し、どこに配置されるかの座標をセット
			if (i != 0)
			{
				invader_type01s[counter].setMissleType("INVADER01");//そのインベーダーにどんなミサイルタイプを装填させるかを決める。初期状態では「INVADER01」というミサイルが装填される。missile.cppに新しいミサイルタイプを宣言してみよう。
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
	return counter;//結果、何体のインベーダーが生成されたのかを返す。
}

//ゲームプログラムがはじめに実行する処理が書かれた関数
void myInit()
{
	//my_battery.setMissleType("USER01");
	my_battery.setMissleType("USER_MACHIHE_GUN");//ユーザー側が操作する砲台にミサイルタイプを指定し、装填。初期状態では「USER_MACHIHE_GUN」という3点バースト弾が装填される。他には「USER01」という単発のミサイルが実装済み。missile.cpp参照。
	invader_num = setInvaders(invader_line);//インベーダーたちを生成する関数を呼ぶ。
}

//ゲームループのたびに呼び出され、勝敗を判断する関数。
int gameJudgment()
{
	vector<int> position;//インベーダーたちの座標が格納されるベクター配列。position[0]がx座標、position[1]がy座標。
	int ihp, inv_counter = 0;
	//勝利
	for (int i = 0; i < invader_num; i++)
	{
		ihp = invader_type01s[i].getHP();
		if (ihp <= 0) inv_counter++;//HPが0のインベーダーを数えていく。
	}
	if (inv_counter == invader_num) return 2;//HP0のインベーダーが生成されたインベーダーの数と等しいなら、2を返す。プレイヤーの勝利。

	//敗北
	if (my_battery.getHP() <= 0) return 1;//プレイヤーのHPが0になった。敗北。
	else {
		for (int i = 0; i < invader_num; i++)//インベーダーの数だけチェック
		{
			position = invader_type01s[i].getPosition();
			if (position[1] >= Y0 * 2) return 1;//インベーダーの中心部が底面に接触。敗北
		}
	}
	return 0;//勝敗がついていない。
}

//ゲーム終了時に画像を表示する関数。詳細略。
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

	DeleteGraph(img_handle);// 読み込んだ画像のグラフィックハンドルを削除
}

//main関数に相当する。詳細は自分で読んでみよう。スペル的に何をやっているのかヒントになっているはず。たぶん...。
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)// プログラムは WinMain から始まります
{
	int Key;
	LONGLONG Time;
	string text = "", text_hp = "";
	vector<vector<int>> missile_positions;//ミサイルの威力を含む
	int death_flag = 0;//生存確認時に使用
	int result = 0;

	SetWindowText(Me);
	ChangeWindowMode(TRUE);
	SetAlwaysRunFlag(TRUE);
	SetDrawScreen(DX_SCREEN_BACK);// 描画先を裏画面にセット
	SetBackgroundColor(0, 0, 0);

	SetGraphMode(win_size_x, win_size_y, 32);
	SetFontSize(20);
	ChangeFont("ＭＳ 明朝");

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}
	myInit();

	// ゲームループ。このループがゲーム終了まで回り続ける。毎回描画するものが変わるから、アニメと同じ原理で動いて見える。
	Time = GetNowHiPerformanceCount() + 1000000 / 60;
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		{//入力取得
			Key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

			if (Key & PAD_INPUT_RIGHT) my_battery.move(1);	// 右を押していたら右に進む
			if (Key & PAD_INPUT_LEFT) my_battery.move(0);	// 左を押していたら左に進む
			if (Key & PAD_INPUT_UP) my_battery.attack();	//上を押したら攻撃

		}

		{//描画
			ClearDrawScreen();// 画面の初期化

			text_hp = to_string(my_battery.getHP());
			text = "HP : " + text_hp;
			DrawString(0, 0, text.c_str(), GetColor(255, 255, 255));

			//砲台描画
			my_battery.draw();
			my_battery.drawMissile();

			//インベーダー描画
			for (int i = 0; i < invader_num; i++)
			{
				invader_type01s[i].draw();
				invader_type01s[i].attack();//描画とほぼ同じタイミングでインベーダーは自動で攻撃する。
				invader_type01s[i].drawMissile();
			}

			ScreenFlip();// 裏画面の内容を表画面に反映

			// 時間待ち
			while (GetNowHiPerformanceCount() < Time) {}
			Time += 1000000 / 60;
		}

		if (result != 0) break;//描画の関係上ここに配置

		{//当たり判定
			//砲台側
			missile_positions.clear();
			for (int i = 0; i < invader_num; i++)//インベーダーの数だけチェック
			{
				missile_positions = invader_type01s[i].getMissilePosition();
				for (int j = 0; j < missile_positions.size(); j++)//ミサイルの数だけチェック
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

			//インベーダー側
			missile_positions.clear();
			missile_positions = my_battery.getMissilePosition();
			for (int i = 0; i < invader_num; i++)//インベーダーの数だけチェック
			{
				for (int j = 0; j < missile_positions.size(); j++)//ミサイルの数だけチェック
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
	WaitKey();        // 結果を見るためにキー待ち(『WaitKey』を使用)
	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}