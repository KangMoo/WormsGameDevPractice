#include "stdafx.h"
#include "BattleScene.h"

BattleScene::BattleScene()
{
}


BattleScene::~BattleScene()
{

}

HRESULT BattleScene::init()
{
	SOUNDMANAGER->init();
	addImg();
	addSound();
	_map = new Map;
	_pm = new PlayerManager;
	_ui = new UI;
	_wm = new WeaponManager;


	_pm->setMapAdressLink(_map);
	_pm->setUIAdressLink(_ui);
	_pm->setWMAddressLing(_wm);

	_map->setUIAddressLink(_ui);

	_ui->setMapAddressLink(_map);
	_ui->setPMAddressLink(_pm);

	_wm->setMapAddressLink(_map);
	_wm->setPMAddressLink(_pm);
	_wm->setUIAddressLink(_ui);

	_map->init();
	_pm->init();
	_ui->init();
	_wm->init();
	SOUNDMANAGER->play("04_bgm_4", 0.5);
	int a = 0;
	return S_OK;
}
void BattleScene::release()
{

}
void BattleScene::update()
{
	_map->update();
	_pm->update();
	_wm->update();
	EFFECTMANAGER->update();
	_ui->update();
	SOUNDMANAGER->update();

	gameOverChk();
}
void BattleScene::render()
{
	_map->render();
	_pm->render();
	_wm->render();
	EFFECTMANAGER->render(_ui->getCamera());
	_ui->render();
	TIMEMANAGER->render(getMemDC());
}

void BattleScene::addImg()
{
	//맵 이미지
	IMAGEMANAGER->addImage(TEXT("Map_1"), TEXT("Img\\Map\\map2_1.bmp"), 4500, 2000, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage(TEXT("Map_2"), TEXT("Img\\Map\\map2_2.bmp"), 4500, 2000, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage(TEXT("Map_3"), TEXT("Img\\Map\\map2_3.bmp"), 4500, 2000, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage(TEXT("bg"), TEXT("Img\\Map\\bg_ns.bmp"), 5000, 2436, true, RGB(255, 0, 255));

	//지렁이 이미지
	IMAGEMANAGER->addFrameImage("WORMSTATE_BACKFLIP", "Img\\Worm\\wbackflp.bmp", 120, 1320, 2, 22, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("WORMSTATE_SLIDING", "Img\\Worm\\wslide.bmp", 120, 180, 2, 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("WORMSTATE_MOVING", "Img\\Worm\\wwalk.bmp", 120, 900, 2, 15, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("WORMSTATE_FALLING", "Img\\Worm\\wfall.bmp", 120, 120, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("WORMSTATE_IDLE", "Img\\Worm\\wbrth1.bmp", 120, 2400, 2, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("WORMSTATE_FLYING", "Img\\Worm\\wfly1.bmp", 120, 1920, 2, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("WORMSTATE_JUMPING", "Img\\Worm\\wflyup.bmp", 120, 120, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("WORMSTATE_DROWNING", "Img\\Worm\\wdrown.bmp", 120, 540, 2, 9, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("W_Win", "Img\\Worm\\wwinner.bmp", 120, 840, 2, 14, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("WORMSTATE_DYING", "Img\\Worm\\wdie.bmp", 120, 3600, 2, 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("W_Fist", "Img\\Worm\\wfist.bmp", 120, 4080, 2, 68, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("W_brth2", "Img\\Worm\\wbrth2.bmp", 120, 1560, 2, 1560 / 60, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("W_SlideToIdle", "Img\\Worm\\wsldlk1.bmp", 120, 1320, 2, 22, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("NI_1", "Img\\Worm\\NI\\waccuse.bmp", 120, 2160, 2, 2160 / 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("NI_2", "Img\\Worm\\NI\\wbghead.bmp", 120, 1200, 2, 1200 / 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("NI_3", "Img\\Worm\\NI\\wblink1.bmp", 120, 720, 2, 720 / 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("NI_4", "Img\\Worm\\NI\\wblink2.bmp", 120, 1920, 2, 1920 / 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("NI_5", "Img\\Worm\\NI\\wkambmr.bmp", 120, 2400, 2, 2400 / 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("NI_6", "Img\\Worm\\NI\\wmunch.bmp", 120, 5880, 2, 5880 / 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("NI_7", "Img\\Worm\\NI\\wolook.bmp", 120, 1800, 2, 1800 / 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("NI_8", "Img\\Worm\\NI\\wpeek.bmp", 120, 2040, 2, 2040 / 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("NI_9", "Img\\Worm\\NI\\wscarey.bmp", 120, 2400, 2, 2400 / 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("NI_10", "Img\\Worm\\NI\\wscrtch.bmp", 120, 3240, 2, 3240 / 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("NI_11", "Img\\Worm\\NI\\wselbak.bmp", 120, 720, 2, 720 / 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("NI_12", "Img\\Worm\\NI\\wtache.bmp", 120, 3600, 2, 3600 / 60, true, RGB(255, 0, 255));
	//무기 장착 이미지
	IMAGEMANAGER->addFrameImage("W_airStrike", "Img\\Worm\\wwinner.bmp", 120, 840, 2, 14, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("baz_S", "Img\\Worm\\Weapon\\baz_S.bmp", 120, 420, 2, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("baz_A", "Img\\Worm\\Weapon\\baz_A.bmp", 120, 1920, 2, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("grn_S", "Img\\Worm\\Weapon\\grn_S.bmp", 120, 600, 2, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("grn_A", "Img\\Worm\\Weapon\\grn_A.bmp", 120, 1920, 2, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("dyn_S", "Img\\Worm\\Weapon\\dyn_S.bmp", 120, 600, 2, 10, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("ban_S", "Img\\Worm\\Weapon\\ban_S.bmp", 120, 600, 2, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ban_A", "Img\\Worm\\Weapon\\ban_A.bmp", 120, 1920, 2, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bat_A", "Img\\Worm\\Weapon\\bat_A.bmp", 120, 1920, 2, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bat_A2", "Img\\Worm\\Weapon\\bat_A2.bmp", 120, 1920, 2, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bat_S", "Img\\Worm\\Weapon\\bat_S.bmp", 120, 600, 2, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("baz2_A", "Img\\Worm\\Weapon\\baz2_A.bmp", 120, 1920, 2, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("baz2_S", "Img\\Worm\\Weapon\\baz2_S.bmp", 120, 420, 2, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("gri_S", "Img\\Worm\\Weapon\\gri_S.bmp", 120, 900, 2, 15, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("holy_A", "Img\\Worm\\Weapon\\holy_A.bmp", 120, 1920, 2, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("holy_S", "Img\\Worm\\Weapon\\holy_S.bmp", 120, 600, 2, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mine_S", "Img\\Worm\\Weapon\\mine_S.bmp", 120, 600, 2, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("rope_H", "Img\\Worm\\Weapon\\rope_H.bmp", 120, 3840, 2, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("rope_I_1", "Img\\Worm\\Weapon\\rope_I_1.bmp", 120, 1920, 2, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("rope_I_2", "Img\\Worm\\Weapon\\rope_I_2.bmp", 120, 1920, 2, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("rope_S", "Img\\Worm\\Weapon\\rope_S.bmp", 120, 600, 2, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("skip_S", "Img\\Worm\\Weapon\\skip_S.bmp", 120, 540, 2, 9, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("tel_A", "Img\\Worm\\Weapon\\tel_A.bmp", 120, 2880, 2, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("tel_S", "Img\\Worm\\Weapon\\tel_S.bmp", 120, 600, 2, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("aircall_I", "Img\\Worm\\Weapon\\airStrike_I.bmp", 120, 600, 2, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("aircall_S", "Img\\Worm\\Weapon\\airStrike_S.bmp", 120, 600, 2, 10, true, RGB(255, 0, 255));


	//무기 이미지
	IMAGEMANAGER->addFrameImage("WP_mis", "Img\\Weapon\\airmisl.bmp", 60, 1920, 1, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("WP_ban", "Img\\Weapon\\banana.bmp", 60, 1920, 1, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("WP_ban2", "Img\\Weapon\\banana2.bmp", 30, 960, 1, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("WP_baz", "Img\\Weapon\\bazoka.bmp", 60, 1920, 1, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("WP_drill", "Img\\Weapon\\drill.bmp", 60, 300, 1, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("WP_dyn", "Img\\Weapon\\dynamite1.bmp", 60, 1800, 1, 1800 / 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("WP_dyn2", "Img\\Weapon\\dynamite2.bmp", 60, 7740, 1, 7740 / 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("WP_grn", "Img\\Weapon\\grenade.bmp", 60, 1920, 1, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("WP_holy", "Img\\Weapon\\hgrenade.bmp", 60, 1920, 1, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("WP_homing", "Img\\Weapon\\hmissil.bmp", 60, 1920, 1, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("WP_ropecuff", "Img\\Weapon\\ropecuff.bmp", 60, 7680, 1, 128, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("WP_ropetip", "Img\\Weapon\\ropetip.bmp", 60, 3840, 1, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("WP_spsheep", "Img\\Weapon\\spsheep.bmp", 120, 1920, 1, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("WP_mine", "Img\\Weapon\\mine.bmp", 120, 1920, 2, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("plane", "Img\\Weapon\\airjetb.bmp", 120, 60, 2, 1, true, RGB(255, 0, 255));
	//기타 이미지

	IMAGEMANAGER->addFrameImage("grave_0", "Img\\Worm\\grave\\grave1.bmp", 60, 2400, 1, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("grave_1", "Img\\Worm\\grave\\grave2.bmp", 60, 2400, 1, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("grave_2", "Img\\Worm\\grave\\grave3.bmp", 60, 2400, 1, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("grave_3", "Img\\Worm\\grave\\grave4.bmp", 60, 2400, 1, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("grave_4", "Img\\Worm\\grave\\grave5.bmp", 60, 2400, 1, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("grave_5", "Img\\Worm\\grave\\grave6.bmp", 60, 2400, 1, 40, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("arrow_0", "Img\\Misc\\arrow\\arrowdnb.bmp", 60, 1800, 1, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("arrow_1", "Img\\Misc\\arrow\\arrowdnc.bmp", 60, 1800, 1, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("arrow_2", "Img\\Misc\\arrow\\arrowdng.bmp", 60, 1800, 1, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("arrow_3", "Img\\Misc\\arrow\\arrowdnp.bmp", 60, 1800, 1, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("arrow_4", "Img\\Misc\\arrow\\arrowdnr.bmp", 60, 1800, 1, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("arrow_5", "Img\\Misc\\arrow\\arrowdny.bmp", 60, 1800, 1, 30, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("num_0", "Img\\Misc\\num\\stdnumb.bmp", 8, 160, 1, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("num_1", "Img\\Misc\\num\\stdnumc.bmp", 8, 160, 1, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("num_2", "Img\\Misc\\num\\stdnumg.bmp", 8, 160, 1, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("num_3", "Img\\Misc\\num\\stdnump.bmp", 8, 160, 1, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("num_4", "Img\\Misc\\num\\stdnumr.bmp", 8, 160, 1, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("num_5", "Img\\Misc\\num\\stdnumy.bmp", 8, 160, 1, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("num88", "Img\\Misc\\num\\stdnumw.bmp", 8, 160, 1, 10, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("frame4020", "Img\\Misc\\ButtonBorders\\4020.bmp", 40, 20, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("CRH", "Img\\Misc\\crshair.bmp", 60, 3840, 1, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mark", "Img\\Misc\\markerb.bmp", 60, 1200, 1, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("icon", "Img\\Misc\\icon.bmp", 138, 234, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("windl", "Img\\Misc\\windl.bmp", 96, 13, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("windr", "Img\\Misc\\windr.bmp", 96, 13, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("windlf", "Img\\Misc\\windlf.bmp", 96, 104,1,8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("windrf", "Img\\Misc\\windrf.bmp", 96, 104,1,8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("blackline", "Img\\Misc\\ButtonBorders\\blackdot.bmp", 2, 13,true,RGB(255,0,255));
	IMAGEMANAGER->addFrameImage("num60", "Img\\Misc\\num\\num60600.bmp", 60, 600, 1, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("num30", "Img\\Misc\\num\\num30300.bmp", 30, 300, 1, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("num24", "Img\\Misc\\num\\num24240.bmp", 24, 240, 1, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("frame3636", "Img\\Misc\\ButtonBorders\\3636.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("windframe", "Img\\Misc\\ButtonBorders\\windframe.bmp", 200, 21, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("waterwave", "Img\\Map\\waterb.bmp", 6114, 288, 1, 12, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("blue", "Img\\Map\\blue.bmp", 4500, 2250, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("fire1", "Img\\Effect\\petrol1.bmp", 60, 1200, 1, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("fire2", "Img\\Effect\\petrol2.bmp", 50, 1000, 1, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("fire3", "Img\\Effect\\petrol3.bmp", 40, 800, 1, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("fire4", "Img\\Effect\\petrol4.bmp", 30, 600, 1, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("fire5", "Img\\Effect\\petrol5.bmp", 20, 400, 1, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("fire6", "Img\\Effect\\petrol6.bmp", 10, 200, 1, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("circl100", "Img\\Effect\\circl100.bmp", 200, 800, 1, 800 / 200, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("circle25", "Img\\Effect\\circle25.bmp", 50, 400, 1, 400 / 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("circle50", "Img\\Effect\\circle50.bmp", 100, 800, 1, 800 / 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("circle75", "Img\\Effect\\circle75.bmp", 150, 600, 1, 600 / 150, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("elips100", "Img\\Effect\\elips100.bmp", 300, 3000, 1, 3000 / 300, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("elipse25", "Img\\Effect\\elipse25.bmp", 74, 1480, 1, 1480 / 74, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("elipse50", "Img\\Effect\\elipse50.bmp", 150, 3000, 1, 3000 / 150, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("elipse75", "Img\\Effect\\elipse75.bmp", 224, 2240, 1, 2240 / 224, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("exbiff", "Img\\Effect\\exbiff.bmp", 60, 720, 1, 720 / 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("exfoom", "Img\\Effect\\exfoom.bmp", 100, 2000, 1, 2000 / 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("expoot", "Img\\Effect\\expoot.bmp", 70, 1260, 1, 1260 / 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("expow", "Img\\Effect\\expow.bmp", 60, 720, 1, 720 / 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("feather", "Img\\Effect\\feather.bmp", 60, 4440, 1, 4440 / 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("firehit", "Img\\Effect\\firehit.bmp", 50, 450, 1, 450 / 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("hexhaust", "Img\\Effect\\hexhaust.bmp", 60, 1680, 1, 1680 / 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("skdsmoke", "Img\\Effect\\skdsmoke.bmp", 60, 3840, 1, 3840 / 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("smkdrk20", "Img\\Effect\\smkdrk20.bmp", 20, 560, 1, 560 / 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("smkdrk30", "Img\\Effect\\smkdrk30.bmp", 30, 840, 1, 840 / 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("smkdrk40", "Img\\Effect\\smkdrk40.bmp", 40, 1120, 1, 1120 / 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("smklt25", "Img\\Effect\\smklt25.bmp", 44, 1232, 1, 1232 / 44, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("smklt50", "Img\\Effect\\smklt50.bmp", 60, 1680, 1, 1680 / 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("smklt75", "Img\\Effect\\smklt75.bmp", 90, 2520, 1, 2520 / 90, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("smklt100", "Img\\Effect\\smklt100.bmp", 134, 3752, 1, 3752 / 134, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("wexhaust", "Img\\Effect\\wexhaust.bmp", 60, 1200, 1, 1200 / 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("flame1", "Img\\Effect\\flame1.bmp", 60, 1920, 1, 1920 / 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("flame2", "Img\\Effect\\flame2.bmp", 60, 1920, 1, 1920 / 60, true, RGB(255, 0, 255));

	image* tmp;
	tmp = IMAGEMANAGER->findImage("circl100");
	EFFECTMANAGER->addEffect("circl100", "circl100", tmp->getWidth(), tmp->getHeight(), tmp->getFrameWidth(), tmp->getFrameHeight(), 60, 0.005, 50);
	tmp = IMAGEMANAGER->findImage("circle25");
	EFFECTMANAGER->addEffect("circle25", "circle25", tmp->getWidth(), tmp->getHeight(), tmp->getFrameWidth(), tmp->getFrameHeight(), 60, 0.005, 50);
	tmp = IMAGEMANAGER->findImage("circle50");
	EFFECTMANAGER->addEffect("circle50", "circle50", tmp->getWidth(), tmp->getHeight(), tmp->getFrameWidth(), tmp->getFrameHeight(), 60, 0.005, 50);
	tmp = IMAGEMANAGER->findImage("circle75");
	EFFECTMANAGER->addEffect("circle75", "circle75", tmp->getWidth(), tmp->getHeight(), tmp->getFrameWidth(), tmp->getFrameHeight(), 60, 0.005, 50);
	tmp = IMAGEMANAGER->findImage("elips100");
	EFFECTMANAGER->addEffect("elips100", "elips100", tmp->getWidth(), tmp->getHeight(), tmp->getFrameWidth(), tmp->getFrameHeight(), 60, 0.005, 50);
	tmp = IMAGEMANAGER->findImage("elipse25");
	EFFECTMANAGER->addEffect("elipse25", "elipse25", tmp->getWidth(), tmp->getHeight(), tmp->getFrameWidth(), tmp->getFrameHeight(), 60, 0.005, 50);
	tmp = IMAGEMANAGER->findImage("elipse50");
	EFFECTMANAGER->addEffect("elipse50", "elipse50", tmp->getWidth(), tmp->getHeight(), tmp->getFrameWidth(), tmp->getFrameHeight(), 60, 0.005, 50);
	tmp = IMAGEMANAGER->findImage("elipse75");
	EFFECTMANAGER->addEffect("elipse75", "elipse75", tmp->getWidth(), tmp->getHeight(), tmp->getFrameWidth(), tmp->getFrameHeight(), 60, 0.005, 50);
	tmp = IMAGEMANAGER->findImage("exbiff");
	EFFECTMANAGER->addEffect("exbiff", "exbiff", tmp->getWidth(), tmp->getHeight(), tmp->getFrameWidth(), tmp->getFrameHeight(), 60, 0.005, 50);
	tmp = IMAGEMANAGER->findImage("exfoom");
	EFFECTMANAGER->addEffect("exfoom", "exfoom", tmp->getWidth(), tmp->getHeight(), tmp->getFrameWidth(), tmp->getFrameHeight(), 60, 0.005, 50);
	tmp = IMAGEMANAGER->findImage("expow");
	EFFECTMANAGER->addEffect("expow", "expow", tmp->getWidth(), tmp->getHeight(), tmp->getFrameWidth(), tmp->getFrameHeight(), 60, 0.005, 50);
	tmp = IMAGEMANAGER->findImage("feather");
	EFFECTMANAGER->addEffect("feather", "feather", tmp->getWidth(), tmp->getHeight(), tmp->getFrameWidth(), tmp->getFrameHeight(), 60, 0.005, 50);
	tmp = IMAGEMANAGER->findImage("firehit");
	EFFECTMANAGER->addEffect("firehit", "firehit", tmp->getWidth(), tmp->getHeight(), tmp->getFrameWidth(), tmp->getFrameHeight(), 60, 0.005, 50);
	tmp = IMAGEMANAGER->findImage("hexhaust");
	EFFECTMANAGER->addEffect("hexhaust", "hexhaust", tmp->getWidth(), tmp->getHeight(), tmp->getFrameWidth(), tmp->getFrameHeight(), 60, 0.005, 50);
	tmp = IMAGEMANAGER->findImage("skdsmoke");
	EFFECTMANAGER->addEffect("skdsmoke", "skdsmoke", tmp->getWidth(), tmp->getHeight(), tmp->getFrameWidth(), tmp->getFrameHeight(), 60, 0.005, 50);
	tmp = IMAGEMANAGER->findImage("smkdrk20");
	EFFECTMANAGER->addEffect("smkdrk20", "smkdrk20", tmp->getWidth(), tmp->getHeight(), tmp->getFrameWidth(), tmp->getFrameHeight(), 60, 0.005, 50);
	tmp = IMAGEMANAGER->findImage("smkdrk30");
	EFFECTMANAGER->addEffect("smkdrk30", "smkdrk30", tmp->getWidth(), tmp->getHeight(), tmp->getFrameWidth(), tmp->getFrameHeight(), 60, 0.005, 50);
	tmp = IMAGEMANAGER->findImage("smkdrk40");
	EFFECTMANAGER->addEffect("smkdrk40", "smkdrk40", tmp->getWidth(), tmp->getHeight(), tmp->getFrameWidth(), tmp->getFrameHeight(), 60, 0.005, 50);
	tmp = IMAGEMANAGER->findImage("smklt25");
	EFFECTMANAGER->addEffect("smklt25", "smklt25", tmp->getWidth(), tmp->getHeight(), tmp->getFrameWidth(), tmp->getFrameHeight(), 60, 0.005, 50);
	tmp = IMAGEMANAGER->findImage("smklt50");
	EFFECTMANAGER->addEffect("smklt50", "smklt50", tmp->getWidth(), tmp->getHeight(), tmp->getFrameWidth(), tmp->getFrameHeight(), 60, 0.005, 50);
	tmp = IMAGEMANAGER->findImage("smklt75");
	EFFECTMANAGER->addEffect("smklt75", "smklt75", tmp->getWidth(), tmp->getHeight(), tmp->getFrameWidth(), tmp->getFrameHeight(), 60, 0.005, 50);
	tmp = IMAGEMANAGER->findImage("smklt100");
	EFFECTMANAGER->addEffect("smklt100", "smklt100", tmp->getWidth(), tmp->getHeight(), tmp->getFrameWidth(), tmp->getFrameHeight(), 60, 0.005, 50);
	tmp = IMAGEMANAGER->findImage("wexhaust");
	EFFECTMANAGER->addEffect("wexhaust", "wexhaust", tmp->getWidth(), tmp->getHeight(), tmp->getFrameWidth(), tmp->getFrameHeight(), 60, 0.005, 50);
	tmp = IMAGEMANAGER->findImage("flame1");
	EFFECTMANAGER->addEffect("flame1", "flame1", tmp->getWidth(), tmp->getHeight(), tmp->getFrameWidth(), tmp->getFrameHeight(), 60, 0.005, 50);
	tmp = IMAGEMANAGER->findImage("flame2");
	EFFECTMANAGER->addEffect("flame2", "flame2", tmp->getWidth(), tmp->getHeight(), tmp->getFrameWidth(), tmp->getFrameHeight(), 60, 0.005, 50);
	tmp = IMAGEMANAGER->findImage("exbiff");
	EFFECTMANAGER->addEffect("exbiff", "exbiff", tmp->getWidth(), tmp->getHeight(), tmp->getFrameWidth(), tmp->getFrameHeight(), 60, 0.005, 50);
	tmp = IMAGEMANAGER->findImage("exfoom");
	EFFECTMANAGER->addEffect("exfoom", "exfoom", tmp->getWidth(), tmp->getHeight(), tmp->getFrameWidth(), tmp->getFrameHeight(), 60, 0.005, 50);
	tmp = IMAGEMANAGER->findImage("expoot");
	EFFECTMANAGER->addEffect("expoot", "expoot", tmp->getWidth(), tmp->getHeight(), tmp->getFrameWidth(), tmp->getFrameHeight(), 60, 0.005, 50);
	tmp = IMAGEMANAGER->findImage("expow");
	EFFECTMANAGER->addEffect("expow", "expow", tmp->getWidth(), tmp->getHeight(), tmp->getFrameWidth(), tmp->getFrameHeight(), 60, 0.005, 50);
}

void BattleScene::addSound()
{
	SOUNDMANAGER->addSound("01_bgm_1", "Sound\\bgm\\ingame-04-battlezone.wav", false, true);
	SOUNDMANAGER->addSound("02_bgm_2", "Sound\\bgm\\ingame-08-desert.wav", false, true);
	SOUNDMANAGER->addSound("03_bgm_3", "Sound\\bgm\\ingame-09-hell.wav", false, true);
	SOUNDMANAGER->addSound("04_bgm_4", "Sound\\bgm\\ingame-11-rain&surf.wav", false, true);
	SOUNDMANAGER->addSound("05_bgm_5", "Sound\\bgm\\title.wav", false, true);

	SOUNDMANAGER->addSound("06_Airstrike", "Sound\\Effect\\Airstrike.wav", false, false);
	SOUNDMANAGER->addSound("07_BananaImpact", "Sound\\Effect\\BananaImpact.wav", false, false);
	SOUNDMANAGER->addSound("08_Explosion1", "Sound\\Effect\\Explosion1.wav", false, false);
	SOUNDMANAGER->addSound("09_Explosion2", "Sound\\Effect\\Explosion2.wav", false, false);
	SOUNDMANAGER->addSound("10_Explosion3", "Sound\\Effect\\Explosion3.wav", false, false);
	SOUNDMANAGER->addSound("11_HOLYGRENADE", "Sound\\Effect\\HOLYGRENADE.wav", false, false);
	SOUNDMANAGER->addSound("12_HOLYGRENADEIMP", "Sound\\Effect\\HOLYGRENADEIMPACT.wav", false, false);
	SOUNDMANAGER->addSound("13_ROCKETRELEASE", "Sound\\Effect\\ROCKETRELEASE.wav", false, false);
	SOUNDMANAGER->addSound("14_Splash", "Sound\\Effect\\Splash.wav", false, false);
	SOUNDMANAGER->addSound("15_TELEPORT", "Sound\\Effect\\TELEPORT.wav", false, false);
	SOUNDMANAGER->addSound("16_THROWPOWERUP", "Sound\\Effect\\THROWPOWERUP.wav", false, false);
	SOUNDMANAGER->addSound("17_THROWRELEASE", "Sound\\Effect\\THROWRELEASE.wav", false, false);

	SOUNDMANAGER->addSound("18_CLICK", "Sound\\ui\\CLICK(2).wav", false, false);

	SOUNDMANAGER->addSound("19_AMAZING", "Sound\\worm\\AMAZING.wav", false, false);
	SOUNDMANAGER->addSound("20_BORING", "Sound\\worm\\BORING.wav", false, false);
	SOUNDMANAGER->addSound("21_BUMMER", "Sound\\worm\\BUMMER.wav", false, false);
	SOUNDMANAGER->addSound("22_FIRE", "Sound\\worm\\FIRE.wav", false, false);
	SOUNDMANAGER->addSound("23_GRENADE", "Sound\\worm\\GRENADE.wav", false, false);
	SOUNDMANAGER->addSound("24_HELLO", "Sound\\worm\\HELLO.wav", false, false);
	SOUNDMANAGER->addSound("25_ILLGETYOU", "Sound\\worm\\ILLGETYOU.wav", false, false);
	SOUNDMANAGER->addSound("26_INCOMING", "Sound\\worm\\INCOMING.wav", false, false);
	SOUNDMANAGER->addSound("27_JUMP1", "Sound\\worm\\JUMP1.wav", false, false);
	SOUNDMANAGER->addSound("28_JUMP2", "Sound\\worm\\JUMP2.wav", false, false);
	SOUNDMANAGER->addSound("29_JUSTYOUWAIT", "Sound\\worm\\JUSTYOUWAIT.wav", false, false);
	SOUNDMANAGER->addSound("30_LAUGH", "Sound\\worm\\LAUGH.wav", false, false);
	SOUNDMANAGER->addSound("31_MISSED", "Sound\\worm\\MISSED.wav", false, false);
	SOUNDMANAGER->addSound("32_OINUTTER", "Sound\\worm\\OINUTTER.wav", false, false);
	SOUNDMANAGER->addSound("33_OOFF1", "Sound\\worm\\OOFF1.wav", false, false);
	SOUNDMANAGER->addSound("34_OOFF2", "Sound\\worm\\OOFF2.wav", false, false);
	SOUNDMANAGER->addSound("35_OOFF3", "Sound\\worm\\OOFF3.wav", false, false);
	SOUNDMANAGER->addSound("36_ORDERS", "Sound\\worm\\ORDERS.wav", false, false);
	SOUNDMANAGER->addSound("37_OW1", "Sound\\worm\\OW1.wav", false, false);
	SOUNDMANAGER->addSound("38_OW2", "Sound\\worm\\OW2.wav", false, false);
	SOUNDMANAGER->addSound("39_OW3", "Sound\\worm\\OW3.wav", false, false);
	SOUNDMANAGER->addSound("40_STUPID", "Sound\\worm\\STUPID.wav", false, false);
	SOUNDMANAGER->addSound("41_walk-compress", "Sound\\worm\\walk-compress.wav", false, false);
	SOUNDMANAGER->addSound("42_YESSIR", "Sound\\worm\\YESSIR.wav", false, false);
	SOUNDMANAGER->addSound("43_YOULLREGRETTHAT", "Sound\\worm\\YOULLREGRETTHAT.wav", false, false);
	//
	SOUNDMANAGER->addSound("44_GRENADEIMPACT", "Sound\\Effect\\GRENADEIMPACT.wav", false, false);
	
	SOUNDMANAGER->addSound("45_BYEBYE", "Sound\\worm\\BYEBYE.wav", false, false);
	SOUNDMANAGER->addSound("46_OOPS", "Sound\\worm\\OOPS.wav", false, false);
	SOUNDMANAGER->addSound("47_RUNAWAY", "Sound\\worm\\RUNAWAY.wav", false, false);
	SOUNDMANAGER->addSound("48_TAKECOVER", "Sound\\worm\\TAKECOVER.wav", false, false);
	SOUNDMANAGER->addSound("49_VICTORY", "Sound\\worm\\VICTORY.wav", false, false);
	SOUNDMANAGER->addSound("50_WATCHTHIS", "Sound\\worm\\WATCHTHIS.wav", false, false);
	SOUNDMANAGER->addSound("51_OHDEAR", "Sound\\worm\\OHDEAR.wav", false, false);
	SOUNDMANAGER->addSound("52_FUSE", "Sound\\Effect\\FUSE.wav", false, false);
	SOUNDMANAGER->addSound("53_CrowdPart1", "Sound\\Effect\\CrowdPart1.wav", false, false);
	SOUNDMANAGER->addSound("54_CrowdPart2", "Sound\\Effect\\CrowdPart2.wav", false, false);
	SOUNDMANAGER->addSound("55_MINEDUD", "Sound\\Effect\\MINEDUD.wav", false, false);
}

void BattleScene::gameOverChk()
{

}