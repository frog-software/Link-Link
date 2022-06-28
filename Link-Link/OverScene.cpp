#include "OverScene.h"
#include "Control.h"

extern Control *now;

/**
 * @brief Construct a new Over Scene object
 *
 * @param last_scene_ �ϸ����������˵�
 * @param t �ؿ���ʱ
 * @param level �ؿ����
 */
OverScene::OverScene(Scene *last_scene_, time_t t, int level) : last_scene{ last_scene_ }
{
    sprintf_s(buff, 50, "%4llds", t);
    sprintf_s(background_pic, 50, "./Pic/endgame.png");

    /*�ж��Ƿ�ʱ*/
    tle = false;

    switch (level)
    {
        case 1:
            if (t > 40)
            {
                tle = true;
            }

        case 2:
            if (t > 60)
            {
                tle = true;
            }

        case 3:
            if (t > 90)
            {
                tle = true;
            }

        case 4:
            if (t > 130)
            {
                tle = true;
            }

        case 5:
            if (t > 160)
            {
                tle = true;
            }

        case 6:
            if (t > 200)
            {
                tle = true;
            }
    }

    /*���û�г�ʱ���ܽ���*/
    if (tle == false && now->level == level)
    {
        now->level++;
    }

    /*����ʤ����Ч*/
    if (tle == false)
    {
        now->playSound(2, "./Sound/win.mp3");
    }
    else
    {
        now->playSound(2, "./Sound/fail.mp3");
    }

    /*��ȡ�߷ְ�*/
    std::ifstream fin;
    std::string fname = std::string{ "./Level_" } +std::to_string(level) + std::string{ "_Rank.dat" };

    /*�߷ְ񲻴����򴴽�һ��*/
    if (fs::exists(fname) == false)
    {
        std::ofstream fout(fname);

        if (fout)
        {
            fout.close();
        }
    }

    fin.open(fname.c_str());
    int score;

    while (true)
    {
        fin >> score;

        if (fin.eof())
        {
            break;
        }

        rank.push_back(score);
    }

    fin.close();

    /*û�г�ʱ������*/
    if (tle == false)
    {
        rank.push_back(t);
    }

    std::sort(rank.begin(), rank.end());

    /*������º�ĸ߷ְ�*/
    std::ofstream fout;
    fout.open(fname.c_str());
    int i = 0;

    for (auto score : rank)
    {
        fout << score << std::endl;

        if (++i == MAX_SCORES_NUM)
        {
            break;
        }
    }

    fout.close();
}

/**
 * @brief ���»���
 *
 * ��˳��ӵײ㵽������һ���»���
 */
void OverScene::update()
{
    /*��̬����*/
    now->bgnow++;

    if (now->bgnow == 49)
    {
        now->bgnow = 0;
    }

    char *s = new char[50];
    sprintf_s(s, 50, "./Pic/bgvideo/bgvideo%02d.png", now->bgnow);
    now->putImage(s, 0, 0, 960, 640);
    delete[] s;

    now->putImage(background_pic, 0, 0, 960, 640);
    now->xyprintf(300, 300, buff, 40);

    if (tle == true)
    {
        now->putImage("./Pic/Over_failed.png", 0, 0, 960, 640);
    }

    /*����߷ְ� */
    int i = 0;

    for (auto score : rank)
    {
        now->xyprintf(700, 200 + i * 30, (std::to_string(score) + "s").c_str(), 40);

        if (++i == MAX_SCORES_NUM)
        {
            break;
        }
    }
}

/**
 * @brief �ж�������
 *
 * @param x �������x
 * @param y �������y
 */
void OverScene::onMouse(Sint32 x, Sint32 y)
{
    /*�жϽ����˵��İ���.*/
    if (x >= 390 && x <= 580 && y >= 520 && y <= 570)
    {
        /*Ӧ�ûص�������.*/
        now->scene = last_scene;
        delete this;
    }
}
/**
 * @brief ����ƶ�����
 *
 * @param x ��ǰ����x
 * @param y ��ǰ����y
 */
void OverScene::onMouseMotion(Sint32 x, Sint32 y)
{
    if (x >= 390 && x <= 580 && y >= 520 && y <= 570)
    {
        sprintf_s(background_pic, 50, "./Pic/endgame_stroke1.png");
    }
    else
    {
        sprintf_s(background_pic, 50, "./Pic/endgame.png");
    }
}