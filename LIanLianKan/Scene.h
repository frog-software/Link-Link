#pragma once
#include <SDL_stdinc.h>
/**
 * @brief 页面类的抽象类
 *
 * 所有的Scene都继承于此
 */
class Scene
{
    public:
        /**
         * @brief Construct a new Scene object
         *
         */
        Scene() = default;
        /**
         * @brief 更新画面
         *
         * 按顺序从底层到顶层逐一更新画面
         */
        virtual void update() = 0;
        /**
         * @brief 判定鼠标操作
         *
         * @param x 鼠标点击的x
         * @param y 鼠标点击的y
         */
        virtual void onMouse(Sint32 x, Sint32 y) = 0;
        /**
         * @brief 鼠标移动功能
         *
         * @param x 当前鼠标的x
         * @param y 当前鼠标的y
         */
        virtual void onMouseMotion(Sint32 x, Sint32 y) = 0;
};
