/*****************************************************************/ /**
                                                                     * \file
                                                                     *Control.cpp
                                                                     * \brief
                                                                     *Control��Ķ���
                                                                     * Control��ĺ�������
                                                                     * \author
                                                                     *FrogDar
                                                                     * \date
                                                                     *June 2020
                                                                     *********************************************************************/

#include "Control.h"

#include <cstdlib>
#include <ctime>
#include <deque>
#include <random>

#include "StartScene.h"

namespace fs = std::filesystem;
extern Control *now;
/**
 * @brief �Ƿ����Զ�ģʽ
 */
bool hasEnabledAutoMode = false;
/**
 * @brief �Զ�ģʽ���ٶ�ѡ������.
 */
int autoSpeed[] = {20, 10, 5, 2};
/**
 * @brief �Զ�ģʽ���ٶ�ѡ���±�.
 */
int autoSpeedIndicator = 0;

/**
 * @brief Construct a new Control object
 *
 * ����һ��width*height��С�Ĵ���
 * SDL�ĸ���׼������
 * @param _width ���ڿ��
 * @param _height ���ڸ߶�
 */
Control::Control(int _width, int _height)
    : width{_width}, height{_height}, scene{nullptr} {
    /*��ʼ��SDL����*/
    SDL_Init(SDL_INIT_EVERYTHING);
    /*��ʼ������*/
    window = SDL_CreateWindow("Link-Link", 100, 100, width, height,
                              SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Surface *surface = IMG_Load("./Pic/icon.png");
    SDL_SetWindowIcon(window, surface);
    SDL_FreeSurface(surface);

    /*��ʼ��SDL����Ƶ��չ*/
    Mix_Init(127);
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_CHANNELS,
                  2048);
    /*��ʼ��SDL��������չ*/
    TTF_Init();

    /*��ʼ�����������*/
    std::srand((int)time(NULL));
    bgnow = 0;
}

/**
 * @brief Destroy the Control object
 *
 * �ͷ�SDL�ĸ�����Դ
 * �ͷ�ָ����Դ
 */
Control::~Control() {
    for (auto i : Textures) {
        SDL_DestroyTexture(i.second);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    Mix_CloseAudio();
    Mix_Quit();
    SDL_Quit();

    delete scene;
    scene = nullptr;
}

/**
 * @brief ��ѭ��.
 *
 * ��������߼������岿��
 */
void Control::mainLoop() {
    /*��ʾ��������Դ�С�*/
    SDL_RenderClear(renderer);
    this->putImage("./Pic/pre.png", 0, 0, width, height);
    SDL_RenderPresent(renderer);

    /*���س�����Դ�ļ�����Ƶ*/
    Initmywavs(fs::path{"./Sound"});

    /*���ű�������*/
    this->playSound(1, "./Sound/bgm.mp3", 0);

    /*���س�����Դ�ļ���ͼƬ*/
    Initmypngs(fs::path{"./Pic"});

    /*��ʼ����ΪStartScene*/
    this->scene = new StartScene();

    /*�û��������¼�*/
    SDL_Event e;

    /*���̰����������*/
    std::deque<SDL_Keycode> keyCodeBuffer;

    /*����ˢ�»��������*/
    int cnt;

    while (!quit) {
        /*��¼��ǰʱ�䣨Ϊ�˿���֡��*/
        Uint64 start = SDL_GetPerformanceCounter();

        /*����ˢ�����ִ��20���¼�*/
        cnt = 20;

        while (SDL_PollEvent(&e) != 0 && --cnt) {
            //�û�ѡ���˳�
            if (e.type == SDL_QUIT) {
                quit = true;
            }

            /*�û��������*/
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                scene->onMouse(e.button.x, e.button.y);
            }

            /*�û��ƶ����*/
            if (e.type == SDL_MOUSEMOTION) {
                scene->onMouseMotion(e.motion.x, e.motion.y);
            }

            /*�û����¼���*/
            if (e.type == SDL_KEYDOWN) {
                // Auto mode /////

                /*����ǰ�������뻺����в�ֻ�����ĸ�����*/
                keyCodeBuffer.push_back(e.key.keysym.sym);

                if (keyCodeBuffer.size() > 4) {
                    keyCodeBuffer.pop_front();
                }

                /*������µ���auto����ת�Զ�ģʽ*/
                if (keyCodeBuffer.size() == 4 && keyCodeBuffer[0] == SDLK_a &&
                    keyCodeBuffer[1] == SDLK_u && keyCodeBuffer[2] == SDLK_t &&
                    keyCodeBuffer[3] == SDLK_o) {
                    hasEnabledAutoMode = !hasEnabledAutoMode;
                }

                /*������µ���s�������Զ�ģʽ���ٶ�*/
                if (keyCodeBuffer.size() > 3 && keyCodeBuffer[3] == SDLK_s) {
                    if ((++autoSpeedIndicator) >=
                        sizeof(autoSpeed) / sizeof(int)) {
                        autoSpeedIndicator = 0;
                    }
                }
            }
        }

        /*���»��Ƶ�ǰ����*/
        SDL_RenderClear(renderer);
        scene->update();
        SDL_RenderPresent(renderer);

        /*Ϊ����֡��Ϊ60���ֶ�delayʣ���ʱ��*/
        Uint64 end = SDL_GetPerformanceCounter();
        float elapsedMS =
            (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;

        /*16.666fԼ����60fps*/
        if (elapsedMS < 16.666f) {
            SDL_Delay(static_cast<int>(floor(16.666f - elapsedMS)));
        }
    }
}

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
void Control::putImage(std::string path, int x, int y, int width, int height) {
    /*���û�л�������ͼƬ������ز����仯*/
    if (Textures[path] == nullptr) {
        SDL_Surface *surface = IMG_Load(path.c_str());
        Textures[path] = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }

    auto &texture = Textures[path];
    SDL_Rect box = {x, y, width, height};
    SDL_RenderCopy(renderer, texture, NULL, &box);
}

/**
 * @brief ��ĳƵ����������path��cnt��.
 *
 * ��channelƵ����������pathһ��cnt��
 * @param channel ���ֲ��ŵ�Ƶ�� ��BGMΪƵ��1����ЧΪƵ��2
 * @param path ���ֵ�·��
 * @param cnt ���Ŵ�����0Ϊ��������(���޴�)
 */
void Control::playSound(int channel, std::string path, int cnt) {
    Mix_PlayChannel(channel, Sounds[path], cnt - 1);
}

/**
 * @brief ����Ƶ��������
 *
 * @param channel 1��ʾbgmƵ�� 2��ʾ��ЧƵ��
 */
void Control::addVolume(int channel) {
    if (1 == channel) {
        volm1 += 0.25;

        if (volm1 > 1) {
            volm1 = 1;
        }

        Mix_Volume(channel, (int)(volm1 * MIX_MAX_VOLUME));
    }

    if (2 == channel) {
        volm2 += 0.25;

        if (volm2 > 1) {
            volm2 = 1;
        }

        Mix_Volume(channel, (int)(volm2 * MIX_MAX_VOLUME));
    }
}

/**
 * @brief ��СƵ��������
 *
 * @param channel 1��ʾbgmƵ�� 2��ʾ��ЧƵ��
 */
void Control::decVolume(int channel) {
    if (1 == channel) {
        volm1 -= 0.25;

        if (volm1 < 0) {
            volm1 = 0;
        }

        Mix_Volume(channel, (int)(volm1 * MIX_MAX_VOLUME));
    }

    if (2 == channel) {
        volm2 -= 0.25;

        if (volm2 < 0) {
            volm2 = 0;
        }

        Mix_Volume(channel, (int)(volm2 * MIX_MAX_VOLUME));
    }
}

/**
 * @brief ��ȡControl�൱ǰ��Renderer.
 *
 * @return SDL_Renderer* Renderer��ָ��
 */
SDL_Renderer *Control::getRenderer() { return renderer; }

/**
 * @brief Get the Volm1 object
 *
 * @return double �������ֵ�����
 */
double Control::getVolm1() const { return volm1; }

/**
 * @brief Get the Volm2 object
 *
 * @return double ��Ч������
 */
double Control::getVolm2() const { return volm2; }

/**
 * @brief Get the Quit object
 *
 * @return true �˳���Ϸ
 * @return false ������Ϸ
 */
bool Control::getQuit() const { return quit; }
/**
 * @brief Set the Quit object
 *
 * @param quit_ ���ĵ��˳���־��״̬
 */
void Control::setQuit(bool quit_) { quit = quit_; }

/**
 * @brief ��ȡ�����
 *
 * @return int ����һ�������
 */
int Control::getRand() { return std::rand(); }

/**
 * @brief ���������Ϣ.
 * ��(x,y)������ֺ�Ϊsize������c
 * @param x ������
 * @param y ������
 * @param c �������
 * @param size �ֺŴ�С
 */
void Control::xyprintf(int x, int y, const char *c, int size = 20) {
    if (Fonts.find(size) == Fonts.end()) {
        Fonts[size] = TTF_OpenFont("./MyFont.ttf", size);
    }

    auto &font = Fonts[size];
    SDL_Color color = {2, 2, 2, 255};
    SDL_Surface *surface = TTF_RenderText_Blended(font, c, color);
    SDL_Rect box = {x, y, surface->w, surface->h};
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(renderer, texture, NULL, &box);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

/**
* @brief ����ͼƬ��Դ

* ����cpp17��׼���ݹ����
* @param strPath ����·��
*/
void Control::Initmypngs(fs::path strPath) {
    for (auto &fe : fs::directory_iterator(strPath)) {
        auto fp = fe.path();
        auto fFiename = fp.filename();

        if (fs::is_directory(fe)) {
            if (fFiename != "." && fFiename != "..") {
                Initmypngs(fp);
            }
        } else if (fs::is_regular_file(fp)) {
            now->putImage(fp.generic_string().c_str(), 0, 0, 100, 100);
        }
    }
}

/**
 * @brief ������Ƶ��Դ
 *
 * ����cpp17��׼���ݹ����
 * @param strPath ����·��
 */
void Control::Initmywavs(fs::path strPath) {
    for (auto &fe : fs::directory_iterator(strPath)) {
        auto fp = fe.path();
        auto fFiename = fp.filename();

        if (fs::is_directory(fe)) {
            if (fFiename != "." && fFiename != "..") {
                Initmywavs(fp);
            }
        } else if (fs::is_regular_file(fp)) {
            Sounds[fp.generic_string()] =
                Mix_LoadWAV(fp.generic_string().c_str());
        }
    }
}