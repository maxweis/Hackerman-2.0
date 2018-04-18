#pragma once

#include <vector>
#include "ofMain.h"
#include "font.h"
#include "panel.h"

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
    void ClearScreen();

	public:
    Font font_inconsolata14;

    ofRectangle screen;

    Panel main_panel;
    ConsolePanel console_panel;

    std::vector<EnemyPanel> enemy_panels;
    std::vector<UtilButton> util_buttons;

		void setup();
		void update();
		void draw();

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
