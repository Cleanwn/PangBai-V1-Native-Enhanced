#pragma once
#include <types/script/types.hpp>

enum SubMenus
{
	NOMENU,
	mainmenu,
	self,
	Misc,
	World,
	settings,
	exitgta,
};

extern enum SubMenus;

namespace MdayS::widgets
{
	namespace Draw {
		void text(const char* text, rgbaf rgbaf, Vector2 position, Vector_2 size, bool center);
		void rect(rgba rgba, Vector2 position, Vector_2 size);
		void spriter(std::string Streamedtexture, std::string textureName, float x, float y, float width, float height, float rotation, int r, int g, int b, int a);
	}

	namespace MenuLevelHandler {
		void MoveMenu(SubMenus menu);
		void BackMenu();
	}

	namespace Checks {
		void controlls();
	}
	namespace Tools {
		char* string_to_char(std::string string);
	}

	namespace Settings {
		extern bool selectPressed;
		extern bool leftPressed;
		extern bool rightPressed;
		extern bool center;
		extern bool controllerinput;

		extern int maxVisOptions;
		extern int currentOption;
		extern int optionCount;

		extern SubMenus currentMenu;
		extern int menuLevel;
		extern int optionsArray[1000];
		extern SubMenus menusArray[1000];

		extern float menuX;
		extern rgbaf count;
		extern rgbaf titleText;
		extern rgba titleRect;
		extern rgbaf breakText;
		extern rgbaf optionText;
		extern rgba selectedText;
		extern rgbaf arrow;
		extern rgbaf integre;
		extern rgba optionRect;
		extern rgba scroller;
		extern rgba line;
		extern rgba primary;
		extern rgba secondary;

		extern int keyPressDelay;
		extern int keyPressPreviousTick;
		extern int keyPressDelay2;
		extern int keyPressPreviousTick2;
		extern int keyPressDelay3;
		extern int keyPressPreviousTick3;
		extern int openKey;
		extern int backKey;
		extern int upKey;
		extern int downKey;
		extern int leftKey;
		extern int rightKey;
		extern int selectKey;
		extern int arrowupKey;
		extern int arrowdownKey;
		extern int arrowleftKey;
		extern int arrowrightKey;
		extern int enterKey;
		extern int deleteKey;
		extern int openpress;
		extern int downpress;
		extern int uppress;
		extern int backpress;
		extern int click;
		extern int leftpress;
		extern int rightpress;
	}

	void add_title(const char* title);
	void add_vehicle(std::string texture1, std::string texture2);
	void add_speedometer(char* text);
	void add_fps(char* text);
	void add_name(char* text);
	void add_smalltitle(char* text);
	void AddSmallInfo(char* text, short line);
	void AddSmallTitle2(char* text);
	void AddSmallInfo2(char* text, short line);
	void AddSmallTitle3(char* text);
	void AddSmallInfo3(char* text, short line);
	bool add_break(const char* option);
	bool add_button(const char* option);
	bool add_button(const char* option, std::function<void()> function);
	bool add_submenus(const char* option, SubMenus newSub);
	bool add_submenus(const char* option, SubMenus newSub, std::function<void()> function);
	bool add_toggle(const char* option, bool& b00l);
	bool add_int(const char* option, int& _int, int min, int max);
	bool add_int(const char* option, int& _int, int min, int max, int step);
	bool add_int(const char* option, int& _int, int min, int max, std::function<void()> function);
	bool add_int(const char* option, int& _int, int min, int max, int step, std::function<void()> function);
	bool add_float(const char* option, float& _float, int min, int max);
	bool add_float(const char* option, float& _float, int min, int max, int step);
	bool add_float(const char* option, float& _float, int min, int max, std::function<void()> function);
	bool add_float(const char* option, float& _float, int min, int max, int step, std::function<void()> function);
	bool add_int_vector(const char* option, std::vector<int> Vector, int& position);
	bool add_int_vector(const char* option, std::vector<int> Vector, int& position, std::function<void()> function);
	bool add_float_vector(const char* option, std::vector<float> Vector, int& position);
	bool add_float_vector(const char* option, std::vector<float> Vector, int& position, std::function<void()> function);
	bool add_string_vector(const char* option, std::vector<std::string> Vector, int& position);
	bool add_string_vector(const char* option, std::vector<std::string> Vector, int& position, std::function<void()> function);
	bool add_string_vector(const char* option, std::vector<char*> Vector, int& position);
	bool add_string_vector(const char* option, std::vector<char*> Vector, int& position, std::function<void()> function);
	bool add_teleport(const char* option, Vector3 coords);
	bool add_teleport(const char* option, Vector3 coords, std::function<void()> function);
	void end();
}
