#pragma once

#include"Scene.h"

/**
 * @brief 开始页面
 *
 * 进入游戏的入口
 */
class StartScene : public Scene
{
    private:
        /*暂存UI按钮图片路径的字符数组.*/
        char *background_pic = new char[50];
    public:
        /**
         * @brief Construct a new Start Scene object
         *
         */
        StartScene();
        /**
         * @brief Destroy the Start Scene object
         *
         */
        ~StartScene() = default;

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
