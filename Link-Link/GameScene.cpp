#include "GameScene.h"
#include "Control.h"
#include "StartScene.h"
#include "SetScene.h"
#include "OverScene.h"

static int count = 0;
static int count_auto = 0;
extern Control *now;
extern bool hasEnabledAutoMode;
extern int autoSpeed[4];
extern int autoSpeedIndicator;

/**
 * @brief Construct a new Game Scene object
 *
 * @param scene_last_ ��һ��������������
 * @param m ��ͼx����ͼ�����
 * @param n ��ͼy����ͼ�����
 * @param totalkind ͼ��������
 * @param level_ ��ǰ�ĵ�
 * @param gravity �Ƿ�������ģʽ
 */
GameScene::GameScene(Scene *scene_last_, int m, int n, int totalkind, int level_, bool gravity) : scene_last{ scene_last_ }, level{ level_ }
{
    map = new Map{ m, n, totalkind, gravity };

    // start timer
    startCounter();

    map->setConnectLine(nullptr);

    switch (level)
    {
        case 1:
            timelimit = 40;
            break;

        case 2:
            timelimit = 60;
            break;

        case 3:
            timelimit = 90;
            break;

        case 4:
            timelimit = 130;
            break;

        case 5:
            timelimit = 160;
            break;

        case 6:
            timelimit = 200;
            break;
    }
}

/**
 * @brief Destroy the Game Scene object
 *
 */
GameScene::~GameScene()
{
    delete map;
}

/**
 * @brief ���»���
 *
 * ��˳��ӵײ㵽������һ���»���
 */
void GameScene::update()
{
    /*���ƻ��汳��ͼƬ.*/
    now->putImage("./Pic/Game.png", 0, 0, 960, 640);

    /*���ƻ��水ť*/
    now->putImage("./Pic/Set/home.png", 890, 100, 50, 50);
    now->putImage("./Pic/main.png", 867, 155, 127, 37);
    now->putImage("./Pic/Set/cogwheel.png", 890, 200, 50, 50);
    now->putImage("./Pic/set.png", 883, 255, 127, 37);

    if (0 == now->pause)
    {
        now->putImage("./Pic/Set/pause.png", 890, 300, 50, 50);
        now->putImage("./Pic/pause.png", 883, 355, 127, 37);
    }

    if (1 == now->pause)
    {
        now->putImage("./Pic/Set/play.png", 890, 300, 50, 50);
        now->putImage("./Pic/play.png", 883, 355, 127, 37);
    }

    now->putImage("./Pic/Set/blub.png", 890, 400, 50, 50);
    now->putImage("./Pic/blub.png", 883, 455, 127, 37);
    now->putImage("./Pic/Set/refresh.png", 890, 500, 50, 50);
    now->putImage("./Pic/refresh.png", 883, 555, 127, 37);

    /*��ť��������*/
    /*��ť����ʱ*/
    if (count < 10 && now->click != 0)
    {
        if (5 == now->click)
        {
            now->putImage("./Pic/Set/blub_.png", 890, 400, 50, 50);
        }

        if (6 == now->click)
        {
            now->putImage("./Pic/Set/refresh_.png", 890, 500, 50, 50);
        }

        count++;
    }

    /*��ť�ָ�*/
    if (count == 10)
    {
        if (5 == now->click)
        {
            map->closeHelp();
        }

        now->click = 0;
        count = 0;
    }

    /*����ͼ�����*/
    while (map->anyMatch() == false && map->isWin() == false)
    {
        map->RandomOrder();
    }

    map->draw();

    // display timer
    now->xyprintf(870, 5, "Time", 40);
    char buff[50];
    sprintf_s(buff, 50, "%4lld", getTimer());
    now->xyprintf(850, 50, buff, 30);
    sprintf_s(buff, 50, "/%3d", timelimit);
    now->xyprintf(890, 50, buff, 30);

    // Auto mode /////
    if (map->getReady() && hasEnabledAutoMode)
    {
        if (dynamic_cast<GameScene *>(now->scene)->map->isWin())
        {
            hasEnabledAutoMode = false;
        }
        else if (count_auto < autoSpeed[autoSpeedIndicator])
        {
            count_auto++;
        }
        else
        {
            count_auto = 0;
            dynamic_cast<GameScene *>(now->scene)->autoPlay();
        }
    }

    //////////////////

    /*�������������������ҳ��*/
    if (map->isWin())
    {
        hasEnabledAutoMode = false;
        now->scene = new OverScene(this->scene_last, getTimer(), this->level);
        delete this;
    }
}

/**
 * @brief �ж�������
 *
 * @param x �������x
 * @param y �������y
 */
void GameScene::onMouse(Sint32 x, Sint32 y)
{
    /*����ͼ����ж�*/
    int linearMousePositionOnMap = getMousePositionOnMap(x, y);

    if (map->getReady() && linearMousePositionOnMap >= 0 && map->map[linearMousePositionOnMap]->getValid())
    {
        now->playSound(2, "./Sound/Touch.wav");

        if (last == nullptr)
        {
            /*���ǵ�һ�ΰ�ͼ�꣬��ͼ��ӿ�*/
            last = map->map[linearMousePositionOnMap];
            last->setIsStroke(true);
        }
        else if (map->isMatch(last, map->map[linearMousePositionOnMap]) == false)
        {
            /*����޷�ƥ�䣬���л��ӿ��ͼ��*/
            last->setIsStroke(false);
            last = map->map[linearMousePositionOnMap];
            last->setIsStroke(true);
        }
        else
        {
            /*������ƥ�䣬��ôҪ���last������������ƥ�亯���������*/
            last = nullptr;
        }

        //  printf("%d %d\n", map->map[linearMousePositionOnMap]->getX(), map->map[linearMousePositionOnMap]->getY());
    }

    /*���ܰ������ж�*/
    if (x >= 890 && x <= 940 && y >= 100 && y <= 150)
    {
        now->scene = scene_last;
        delete this;
        //���ﷵ�����˵�.
    }

    if (x >= 890 && x <= 940 && y >= 200 && y <= 250)
    {
        //����������ý���
        new SetScene(this);
        pauseCounter();
        now->pause = 1;
    }

    if (x >= 890 && x <= 940 && y >= 300 && y <= 350)
    {
        now->pause = !now->pause;
        //��������ͣ��ť.
    }

    if (x >= 890 && x <= 940 && y >= 400 && y <= 450)
    {
        now->click = 5;
        map->openHelp();
        //��������ʾ����.
    }

    if (x >= 890 && x <= 940 && y >= 500 && y <= 550)
    {
        now->click = 6;
        //���������Ź���.
        map->RandomOrder();
    }

    if (1 == now->pause)
    {
        this->pauseCounter();
        //��������ͣ����.
    }

    if (0 == now->pause)
    {
        this->startCounter();
        //������ȡ����ͣ����.
    }
}

/**
 * @brief ����ƶ�����
 *
 * @param x ��ǰ����x
 * @param y ��ǰ����y
 */
void GameScene::onMouseMotion(Sint32 x, Sint32 y)
{
    // Pass
    // by wht
}

/**
*this function returns the index in map which represents the picture
*that has benn clicked.
*It returns **-1** if the spot that has been clicked is outside the map.
*/
int GameScene::getMousePositionOnMap(Sint32 x, Sint32 y)
{
    // how many pictures are there horizontally
    const int NUM_OF_HORIZONTAL_PICTURES = map->m;
    // how many pictures are there vertically
    const int NUM_OF_VERTICAL_PICTURES = map->n;

    // consider the map as a rectangle
    // this is the coordinate of the upper left corner
    const int MAP_START_POSOTION_X = 50;
    const int MAP_START_POSOTION_Y = 50;
    // this is the coordinate of the lower right corner
    const int MAP_END_POSOTION_X = 50 * (NUM_OF_HORIZONTAL_PICTURES);
    const int MAP_END_POSOTION_Y = 50 * (NUM_OF_VERTICAL_PICTURES);

    int ln, col;
    // return value
    int ret = -1;

    if ((x >= MAP_START_POSOTION_X)
        && (y >= MAP_START_POSOTION_Y)
        && (x <= MAP_END_POSOTION_X)
        && (y <= MAP_END_POSOTION_Y))
    {
        ln = (y - MAP_START_POSOTION_Y) / Pic::height + 1; // line index
        col = (x - MAP_START_POSOTION_X) / Pic::width + 1; // column index

        // index in map to return
        ret = col * NUM_OF_VERTICAL_PICTURES + ln;
    }

    return ret;
}

/**
 * @brief autoģʽ�Զ���
 *
 * @return true ��Ϸ�����
 * @return false ��Ϸδ���
 */
bool GameScene::autoPlay()
{
    bool isWin = map->isWin();

    if (!isWin)
    {
        map->isMatch(map->getFirstMatchedPair().first, map->getFirstMatchedPair().second);
    }

    return isWin;
}

/*��ʼ��ʱ*/
void GameScene::startCounter()
{
    // if counter is stopped.
    if (counterStatus == 0)
    {
        timer = 0;
        counterStatus = 1;
        counterTime_start = time(NULL);
    }
    // if counter is paused.
    else if (counterStatus == 2)
    {
        counterStatus = 1;
        counterTimePause_stop = time(NULL);
        timer += counterTimePause_start - counterTimePause_stop;
    }

    return;
}

/*ֹͣ��ʱ*/
void GameScene::stopCounter()
{
    // if counter is started.
    if (counterStatus == 1)
    {
        counterStatus = 0;
        counterTime_stop = time(NULL);
    }
    // if counter is paused.
    else if (counterStatus == 2)
    {
        counterStatus = 0;
        counterTimePause_stop = time(NULL);
        counterTime_stop = time(NULL);
        timer += counterTimePause_start - counterTimePause_stop;
    }

    return;
}

/*��ͣ��ʱ*/
void GameScene::pauseCounter()
{
    // if counter is started.
    if (counterStatus == 1)
    {
        counterStatus = 2;
        counterTimePause_start = time(NULL);
    }

    return;
}

/*��ȡʱ��*/
time_t GameScene::getTimer()
{
    switch (counterStatus)
    {
        case 0: // counter stopped
            timer += counterTime_stop - counterTime_start;
            return timer;
            break;

        case 1: // counter started
            return timer + time(NULL) - counterTime_start;
            break;

        case 2: // counter paused
            return timer - counterTime_start + counterTimePause_start;
            break;

        default:
            break;
    }

    return 0;
}