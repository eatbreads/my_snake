#ifndef CONFIG_H
#define CONFIG_H


// 定义版本信息
#define VERSION "Snake 1.0"
// 定义窗口的属性和名称
#define WINDOW_NAME " "
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
// 定义游戏区域的尺寸和更新步长
extern int GAME_WIDTH;
extern int GAME_HEIGHT;
extern int GAME_STEP;
//这边GAME_WIDTH*GAME_STEP不可以大于WINDOW_WIDTH
//E:\\qt_project\\eat_snake\\my_snake
#endif // CONFIG_H
