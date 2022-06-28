#pragma once

#include"Scene.h"
#include"Map.h"
#include"Pic.h"
#include <ctime>
#include <list>

/**
 * @brief 游戏页面
 *
 * 游戏正式运行的所有操作
 */
class GameScene : public Scene
{
    private:

        Map *map = nullptr;/*map类对象*/
        Pic *last = nullptr;/*上一个选中的图标*/
        Scene *scene_last;/*上一个场景（开始界面）*/
        int level;/*当前游戏场景的关卡*/
        int timelimit;/*当前等级限时*/

        /*计时器相关*/

        time_t counterTime_start;
        time_t counterTime_stop;
        time_t counterTimePause_start;
        time_t counterTimePause_stop;
        time_t timer = 0;
        /*
        时间计时器状态
        0 = counter stopped
        1 = counter started
        2 = counter paused
        */
        int counterStatus = 0;
        /*开始计时*/
        void startCounter();
        /*停止计时*/
        void stopCounter();
        /*暂停计时*/
        void pauseCounter();
        /*获取时间*/
        time_t getTimer();

        /**
        *this function returns the index in map which represents the picture
        *that has benn clicked.
        *It returns **-1** if the spot that has been clicked is outside the map.
        */
        int getMousePositionOnMap(Sint32 x, Sint32 y);

        /**
         * @brief auto模式自动玩
         *
         * @return true 游戏已完成
         * @return false 游戏未完成
         */
        bool autoPlay();

    public:
        /**
         * @brief Construct a new Game Scene object
         *
         * @param scene_last_ 上一个场景（主场景
         * @param m 地图x方向图标个数
         * @param n 地图y方向图标个数
         * @param totalkind 图标种类数
         * @param level_ 当前文档
         * @param gravity 是否开启重力模式
         */
        GameScene(Scene *scene_last_, int m, int n, int totalkind, int level_, bool gravity);

        /**
         * @brief Destroy the Game Scene object
         *
         */
        ~GameScene();

        /**
         * @brief 更新画面
         *
         * 按顺序从底层到顶层逐一更新画面
         */
        void update()override;

        /**
         * @brief 判定鼠标操作
         *
         * @param x 鼠标点击的x
         * @param y 鼠标点击的y
         */
        void onMouse(Sint32 x, Sint32 y) override;
        /**
         * @brief 鼠标移动功能
         *
         * @param x 当前鼠标的x
         * @param y 当前鼠标的y
         */
        void onMouseMotion(Sint32 x, Sint32 y) override;
};
