#include "OverScene.h"

#include "Control.h"

extern Control *now;

/**
 * @brief Construct a new Over Scene object
 *
 * @param last_scene_ 上个场景（主菜单
 * @param t 关卡用时
 * @param level 关卡编号
 */
OverScene::OverScene(Scene *last_scene_, time_t t, int level)
    : last_scene{last_scene_} {
    sprintf(buff, "%4ld", t);
    sprintf(background_pic, "./Pic/endgame.png");

    /*判断是否超时*/
    tle = false;

    switch (level) {
        case 1:
            if (t > 40) {
                tle = true;
            }

        case 2:
            if (t > 60) {
                tle = true;
            }

        case 3:
            if (t > 90) {
                tle = true;
            }

        case 4:
            if (t > 130) {
                tle = true;
            }

        case 5:
            if (t > 160) {
                tle = true;
            }

        case 6:
            if (t > 200) {
                tle = true;
            }
    }

    /*如果没有超时才能解锁*/
    if (tle == false && now->level == level) {
        now->level++;
    }

    /*播放胜利音效*/
    if (tle == false) {
        now->playSound(2, "./Sound/win.mp3");
    } else {
        now->playSound(2, "./Sound/fail.mp3");
    }

    /*读取高分榜*/
    std::ifstream fin;
    std::string fname = std::string{"./Level_"} + std::to_string(level) +
                        std::string{"_Rank.dat"};

    /*高分榜不存在则创建一个*/
    if (fs::exists(fname) == false) {
        std::ofstream fout(fname);

        if (fout) {
            fout.close();
        }
    }

    fin.open(fname.c_str());
    int score;

    while (true) {
        fin >> score;

        if (fin.eof()) {
            break;
        }

        rank.push_back(score);
    }

    fin.close();

    /*没有超时则计入榜单*/
    if (tle == false) {
        rank.push_back(t);
    }

    std::sort(rank.begin(), rank.end());

    /*输出更新后的高分榜*/
    std::ofstream fout;
    fout.open(fname.c_str());
    int i = 0;

    for (auto score : rank) {
        fout << score << std::endl;

        if (++i == MAX_SCORES_NUM) {
            break;
        }
    }

    fout.close();
}

/**
 * @brief 更新画面
 *
 * 按顺序从底层到顶层逐一更新画面
 */
void OverScene::update() {
    /*动态背景*/
    now->bgnow++;

    if (now->bgnow == 49) {
        now->bgnow = 0;
    }

    char *s = new char[50];
    sprintf(s, "./Pic/bgvideo/bgvideo%02d.png", now->bgnow);
    now->putImage(s, 0, 0, 960, 640);
    delete[] s;

    now->putImage(background_pic, 0, 0, 960, 640);
    now->xyprintf(300, 300, buff, 40);

    if (tle == true) {
        now->putImage("./Pic/Over_failed.png", 0, 0, 960, 640);
    }

    /*输出高分榜 */
    int i = 0;

    for (auto score : rank) {
        now->xyprintf(700, 200 + i * 30, (std::to_string(score) + "s").c_str(),
                      40);

        if (++i == MAX_SCORES_NUM) {
            break;
        }
    }
}

/**
 * @brief 判定鼠标操作
 *
 * @param x 鼠标点击的x
 * @param y 鼠标点击的y
 */
void OverScene::onMouse(Sint32 x, Sint32 y) {
    /*判断结束菜单的按键.*/
    if (x >= 390 && x <= 580 && y >= 520 && y <= 570) {
        /*应该回到主界面.*/
        now->scene = last_scene;
        delete this;
    }
}
/**
 * @brief 鼠标移动功能
 *
 * @param x 当前鼠标的x
 * @param y 当前鼠标的y
 */
void OverScene::onMouseMotion(Sint32 x, Sint32 y) {
    if (x >= 390 && x <= 580 && y >= 520 && y <= 570) {
        sprintf(background_pic, "./Pic/endgame_stroke1.png");
    } else {
        sprintf(background_pic, "./Pic/endgame.png");
    }
}