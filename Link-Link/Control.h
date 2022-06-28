/*****************************************************************//**
 * \file   Control.h
 * \brief  Control������
 * Control�����������ͷ�ļ�
 *
 * \author FrogDar
 * \date   June 2020
 *********************************************************************/
#pragma once
#include "Scene.h"
#include "SDL.h"
#include <map>
#include <string>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <filesystem>
namespace fs = std::filesystem;

/**
 * @brief Control����ƴ�������
 *
 * ����һ����Ϸ���ڣ����Ʊ����ڵ������߼�
 * �߼���mainloop����
 */
class Control
{
    private:
        /*private����*/

        /*������*/
        int width;
        /*����߶�*/
        int height;

        /*������ʼֵ0.5*/
        double volm1{ 0.5 }, volm2{ 0.5 };

        /*��Ҫ��Ⱦ�Ĵ���*/
        SDL_Window *window = NULL;
        /*��Ҫ��Ⱦ��render*/
        SDL_Renderer *renderer = NULL;

        /*�û��Ƿ�ѡ���˳�*/
        bool quit = false;

        /*���仯Texture��Դ*/
        std::map<std::string, SDL_Texture *>Textures;
        /*���仯������Դ*/
        std::map<int, TTF_Font * >Fonts;
        /*���仯������Դ*/
        std::map<std::string, Mix_Chunk *>Sounds;

        /*private���ܺ���*/

        /**
         * @brief ����ͼƬ��Դ
         *
         * @param strPath ����·��
         */
        void Initmypngs(fs::path strPath);
        /**
         * @brief ������Ƶ��Դ
         *
         * @param strPath ����·��
         */
        void Initmywavs(fs::path strPath);

    public:
        /*Public����*/

        /*�û�����Ĺ��ܰ������*/
        int click = 0;
        /*�����Ƿ�����ͣ��*/
        bool pause = false;
        /*Ŀǰ�Ѿ������Ĺؿ�*/
        int level = 1;
        /*��ǰˢ�µĳ���*/
        Scene *scene;
        /*��̬�����ĵ�ǰ���*/
        int bgnow;

        /*ctor&&dtor*/

        /**
         * @brief Construct a new Control object
         *
         * ����һ��width*height��С�Ĵ���
         * SDL�ĸ���׼������
         * @param _width ���ڿ��
         * @param _height ���ڸ߶�
         */
        Control(int _width, int _height);

        /**
         * @brief Destroy the Control object
         *
         * �ͷ�SDL�ĸ�����Դ
         * �ͷ�ָ����Դ
         */
        ~Control();

        /*���ܺ���*/

        /**
        * @brief ��ѭ��.

        * ��������߼������岿��
        */
        void mainLoop();

        /**
         * @brief ����һ��ͼƬ.
         *
         * ��λ��x��y �Կ�� width �߶� height�ķ�ʽ ����ͼƬpath
         * @param path ͼƬ��·��
         * @param x ���Ƶ�ĺ�����
         * @param y ���Ƶ��������
         * @param width ��Ҫ���Ƶ�ͼƬ���
         * @param height ��Ҫ���Ƶ�ͼƬ�ĸ߶�
         */
        void putImage(std::string path, int x, int y, int width, int height);

        /**
         * @brief ��ĳƵ����������path��cnt��.
         *
         * ��channelƵ����������pathһ��cnt��
         * @param channel ���ֲ��ŵ�Ƶ�� ��BGMΪƵ��1����ЧΪƵ��2
         * @param path ���ֵ�·��
         * @param cnt ���Ŵ�����0Ϊ��������(���޴�)
         */
        void playSound(int channel, std::string path, int cnt = 1);

        /**
         * @brief ����Ƶ��������
         *
         * @param channel 1��ʾbgmƵ�� 2��ʾ��ЧƵ��
         */
        void addVolume(int channel);
        /**
         * @brief ��СƵ��������
         *
         * @param channel 1��ʾbgmƵ�� 2��ʾ��ЧƵ��
         */
        void decVolume(int channel);

        /**
         * @brief ���������Ϣ.
         *
         * ��(x,y)������ֺ�Ϊsize������c
         * @param x ������
         * @param y ������
         * @param c �������
         * @param size �ֺŴ�С
         */
        void xyprintf(int x, int y, const char *c, int size);

        /*getter&&setter*/

        /**
         * @brief Get the Volm1 object
         *
         * @return double �������ֵ�����
         */
        double getVolm1() const;
        /**
         * @brief Get the Volm2 object
         *
         * @return double ��Ч������
         */
        double getVolm2() const;

        /**
         * @brief Get the Quit object
         *
         * @return true �˳���Ϸ
         * @return false ������Ϸ
         */
        bool getQuit() const;
        /**
         * @brief Set the Quit object
         *
         * @param quit_ ���ĵ��˳���־��״̬
         */
        void setQuit(bool quit_);

        /**
         * @brief Get the Renderer object
         * ��ȡ��ǰ��Renderer
         * @return SDL_Renderer*
         */
        SDL_Renderer *getRenderer();

        /**
         * @brief ��ȡһ�������
         *
         * @return int һ�������
         */
        int getRand();
};
