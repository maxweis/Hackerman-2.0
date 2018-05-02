#pragma once

#include <vector>
#include "ofMain.h"
#include "font.h"
#include "panel.h"
#include "player.h"
#include "filesystem.h"
#include "enemy.h"

class Hackerman : public ofBaseApp {
    void InitPanels();
    void InitEnemyPanel();
    void InitConsolePanel();
    void InitUtilPanel();
    void InitMainPanel();
    void InitFileImages();
    void InitFilesystem();
    void startMusicLoop();

    void DrawMenu();
    void DrawPanels();
    void DrawEnemyPanel();
    void DrawConsolePanel();
    void DrawUtilPanel();
    void DrawMainPanel();
    ofRectangle DrawFile(File file, float y_ratio);
    void DrawDirectory();
    void ClearPanelFocus();
    void ClearScreen();
    void HandleUtilButtonAction(UtilButtonType button_type);
    void ProcessCommand();
    void ResizeFileImages(int columns);

    void UpdateEnemies();
    void UpdatePlayer();
    Enemy *GetFocusedEnemy();
    int EnemiesAlive();
    bool PasswordGuess(std::string guess, std::string password);
    void RestoreEnemyFirewalls();
    void DefeatEnemy(Enemy &enemy);

    void OpenEncryptInterface();
    void OpenFilesystemInterface();
    void DrawFilesystemInterface();
    void OpenStoreInterface();
    void OpenFirewallAttackInterface();
    void OpenDecryptInterface();

    std::vector<ofImage> filesystem_images;
    //root of filesystem
    File fs_root;
    //current position in filesystem
    File current_dir;

    ofRectangle DrawCenterAlign(ofImage &image, ofRectangle bound);
    ofRectangle DrawCenterAlignX(ofImage &image, ofRectangle bound, float y_ratio);

    void PrintToConsole(std::string message, bool prefix = false);
    void PrintToConsole(std::vector<std::string> messages);
	public:
    Player player;

    ofSoundPlayer music_loop;
    Font font_inconsolata14;

    ofRectangle screen;

    Panel main_panel;
    ConsolePanel console_panel;

    std::vector<EnemyPanel> enemy_panels;
    std::vector<UtilButton> util_buttons;

		void setup();
		void update();
		void draw();

    void SetResolution(int width, int height);
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
};

const int kFPS = 60;
const int kShiftKey = 3680;
