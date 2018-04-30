#pragma once

#include <vector>
#include "ofMain.h"
#include "font.h"
#include "panel.h"
#include "player.h"

class Hackerman : public ofBaseApp {
    void InitPanels();
    void InitEnemyPanel();
    void InitConsolePanel();
    void InitUtilPanel();
    void InitMainPanel();

    void DrawMenu();
    void DrawPanels();
    void DrawEnemyPanel();
    void DrawConsolePanel();
    void DrawUtilPanel();
    void DrawMainPanel();
    void ClearPanelFocus();
    void ClearScreen();
    void HandleUtilButtonAction(UtilButtonType button_type);
    void ProcessCommand();

    void OpenEncryptInterface();
    void OpenFilesystemInterface();
    void OpenStoreInterface();
    void OpenFirewallAttackInterface();
    void OpenDecryptInterface();

    ofRectangle RenderCenterAlign(ofImage &image, ofRectangle bound);

    void PrintToConsole(std::string message, bool prefix = false);
    void PrintToConsole(std::vector<std::string> messages);
    void startMusicLoop();

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

const int kShiftKey = 3680;
