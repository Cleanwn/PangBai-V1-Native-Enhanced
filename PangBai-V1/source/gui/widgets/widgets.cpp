#include "pch.h"
#include "widgets.hpp"
#include "native/natives.hpp"
#include "keyboard.hpp"

#include <gta/enums.hpp>

namespace MdayS
{
	float widgets::Settings::menuX = 0.17f;
	bool widgets::Settings::selectPressed = false;
	bool widgets::Settings::leftPressed = false;
	bool widgets::Settings::rightPressed = false;
	bool firstopen = true;
	int widgets::Settings::maxVisOptions = 16;
	int widgets::Settings::currentOption = 0;
	int widgets::Settings::optionCount = 0;
	SubMenus widgets::Settings::currentMenu;
	int widgets::Settings::menuLevel = 0;
	int widgets::Settings::optionsArray[1000];
	SubMenus widgets::Settings::menusArray[1000];

	rgbaf widgets::Settings::count{ 255, 255, 255, 255, 6 };
	rgbaf widgets::Settings::titleText{ 255, 255, 255, 255, 7 };
	rgba widgets::Settings::titleRect{ 100, 0, 0, 255 };
	rgbaf widgets::Settings::optionText{ 255, 255, 255, 255, 6 };
	rgbaf widgets::Settings::breakText{ 255, 255, 255, 255, 1 };
	rgbaf widgets::Settings::arrow{ 255, 255, 255, 255, 3 };
	rgba widgets::Settings::optionRect{ 0, 0, 0, 110 };
	rgba widgets::Settings::scroller{ 100, 0, 0, 150 };
	rgbaf widgets::Settings::integre{ 255, 255, 255, 255, 2 };
	rgba widgets::Settings::line{ 255, 255, 255, 255 };
	rgba widgets::Settings::primary{ 255, 0, 0 };
	rgba widgets::Settings::secondary{ 0, 255, 0 };

	void novoid()
	{
	}

	void widgets::Draw::text(const char* text, rgbaf rgbaf, Vector2 position, Vector_2 size, bool center)
	{
		HUD::SET_TEXT_CENTRE(center);
		HUD::SET_TEXT_COLOUR(rgbaf.r, rgbaf.g, rgbaf.b, rgbaf.a);
		HUD::SET_TEXT_FONT(rgbaf.f);
		HUD::SET_TEXT_SCALE(size.w, size.h);
		HUD::SET_TEXT_DROPSHADOW(1, 0, 0, 0, 0);
		HUD::SET_TEXT_EDGE(1, 0, 0, 0, 0);
		HUD::SET_TEXT_OUTLINE();
		HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME((char*)text);
		HUD::END_TEXT_COMMAND_DISPLAY_TEXT(position.x, position.y, 0);
	}

	void widgets::Draw::spriter(std::string Streamedtexture, std::string textureName, float x, float y, float width, float height, float rotation, int r, int g, int b, int a)
	{
		if (!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED((char*)Streamedtexture.c_str()))
		{
			GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT((char*)Streamedtexture.c_str(), false);
		}
		else
		{
			GRAPHICS::DRAW_SPRITE((char*)Streamedtexture.c_str(), (char*)textureName.c_str(), x, y, width, height, rotation, r, g, b, a, 0, 0);
		}
	}

	void widgets::Draw::rect(rgba rgba, Vector2 position, Vector_2 size)
	{
		GRAPHICS::DRAW_RECT(position.x, position.y, size.w, size.h, rgba.r, rgba.g, rgba.b, rgba.a, 0);
	}


	void widgets::add_title(const char* title)
	{
		Draw::text(title, Settings::titleText, { Settings::menuX, 0.095f }, { 0.85f, 0.85f }, true);
		Draw::rect(Settings::titleRect, { Settings::menuX, 0.1175f }, { 0.21f, 0.085f });

		HUD::HIDE_HELP_TEXT_THIS_FRAME();
		CAM::SET_CINEMATIC_BUTTON_ACTIVE(0);
		HUD::HIDE_HUD_COMPONENT_THIS_FRAME(10);
		HUD::HIDE_HUD_COMPONENT_THIS_FRAME(6);
		HUD::HIDE_HUD_COMPONENT_THIS_FRAME(7);
		HUD::HIDE_HUD_COMPONENT_THIS_FRAME(9);
		HUD::HIDE_HUD_COMPONENT_THIS_FRAME(8);
		PAD::DISABLE_CONTROL_ACTION(2, INPUT_NEXT_CAMERA, true);
		PAD::DISABLE_CONTROL_ACTION(2, INPUT_CHARACTER_WHEEL, true);
		PAD::DISABLE_CONTROL_ACTION(2, INPUT_MELEE_ATTACK_LIGHT, true);
		PAD::DISABLE_CONTROL_ACTION(2, INPUT_MELEE_ATTACK_HEAVY, true);
		PAD::DISABLE_CONTROL_ACTION(2, INPUT_MULTIPLAYER_INFO, true);
		PAD::DISABLE_CONTROL_ACTION(2, INPUT_PHONE, true);
		PAD::DISABLE_CONTROL_ACTION(2, INPUT_MELEE_ATTACK_ALTERNATE, true);
		PAD::DISABLE_CONTROL_ACTION(2, INPUT_VEH_CIN_CAM, true);
		PAD::DISABLE_CONTROL_ACTION(2, INPUT_MAP_POI, true);
		PAD::DISABLE_CONTROL_ACTION(2, INPUT_PHONE, true);
		PAD::DISABLE_CONTROL_ACTION(2, INPUT_VEH_RADIO_WHEEL, true);
		PAD::DISABLE_CONTROL_ACTION(2, INPUT_VEH_HEADLIGHT, true);
	}

	bool widgets::add_break(const char* option)
	{
		Settings::optionCount++;
		bool onThis = Settings::currentOption == Settings::optionCount ? true : false;
		if (Settings::currentOption <= 16 && Settings::optionCount <= 16)
		{
			Draw::text(option, Settings::breakText, { Settings::menuX, (Settings::optionCount) * 0.035f + 0.125f }, { 0.45f, 0.45f }, true);
			Draw::rect(Settings::optionRect, { Settings::menuX, (Settings::optionCount) * 0.035f + 0.1415f }, { 0.21f, 0.035f });
		}
		else if (Settings::optionCount > (Settings::currentOption - 16) && Settings::optionCount <= Settings::currentOption)
		{
			Draw::text(option, Settings::breakText, { Settings::menuX, (Settings::optionCount - (Settings::currentOption - 16)) * 0.035f + 0.125f }, { 0.45f, 0.45f }, true);
			Draw::rect(Settings::optionRect, { Settings::menuX,  (Settings::optionCount - (Settings::currentOption - 16)) * 0.035f + 0.1415f }, { 0.21f, 0.035f });
		}
		return false;
	}

	bool widgets::add_button(const char* option)
	{
		Settings::optionCount++;
		bool onThis = Settings::currentOption == Settings::optionCount ? true : false;
		if (Settings::currentOption <= 16 && Settings::optionCount <= 16)
		{
			Draw::text(option, Settings::optionText, { Settings::menuX - 0.100f, (Settings::optionCount) * 0.035f + 0.125f }, { 0.45f, 0.45f }, false);
			Draw::rect(Settings::optionRect, { Settings::menuX, (Settings::optionCount) * 0.035f + 0.1415f }, { 0.21f, 0.035f });
			onThis ? Draw::rect(Settings::scroller, { Settings::menuX, (Settings::optionCount) * 0.035f + 0.1415f }, { 0.21f, 0.035f }) : novoid();
		}
		else if (Settings::optionCount > (Settings::currentOption - 16) && Settings::optionCount <= Settings::currentOption)
		{
			Draw::text(option, Settings::optionText, { Settings::menuX - 0.100f, (Settings::optionCount - (Settings::currentOption - 16)) * 0.035f + 0.125f }, { 0.45f, 0.45f }, false);
			Draw::rect(Settings::optionRect, { Settings::menuX,  (Settings::optionCount - (Settings::currentOption - 16)) * 0.035f + 0.1415f }, { 0.21f, 0.035f });
			onThis ? Draw::rect(Settings::scroller, { Settings::menuX,  (Settings::optionCount - (Settings::currentOption - 16)) * 0.035f + 0.1415f }, { 0.21f, 0.035f }) : novoid();
		}
		if (Settings::currentOption == Settings::optionCount)
		{
			if (Settings::selectPressed)
			{
				return true;
			}
		}
		return false;
	}

	bool widgets::add_submenus(const char* option, SubMenus newSub)
	{
		add_button(option);

		if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
			Draw::text("", Settings::titleText, { Settings::menuX + 0.099f, Settings::optionCount * 0.035f + 0.125f }, { 0.35f, 0.35f }, true);
		else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
			Draw::text("", Settings::titleText, { Settings::menuX + 0.099f, (Settings::optionCount - (Settings::currentOption - 16)) * 0.035f + 0.12f }, { 0.35f, 0.35f }, true);

		if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
			MenuLevelHandler::MoveMenu(newSub);
			return true;
		}
		return false;
	}

	bool widgets::add_toggle(const char* option, bool& b00l)
	{
		add_button(option);
		if (b00l)
		{
			if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
				Draw::text(b00l ? "~g~ON" : "~r~OFF", Settings::optionText, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.128f }, { 0.40f, 0.40f }, true); // 0.35 // 0.125 // 0.45
			else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
				Draw::text(b00l ? "~g~ON" : "~r~OFF", Settings::optionText, { Settings::menuX + 0.069f, Settings::optionCount * 0.035f + 0.128f }, { 0.40f, 0.40f }, true);
		}
		else
		{
			if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
				Draw::text(b00l ? "~g~ON" : "~r~OFF", Settings::optionText, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.128f }, { 0.40f, 0.40f }, true);
			else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
				Draw::text(b00l ? "~g~ON" : "~r~OFF", Settings::optionText, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.128f }, { 0.40f, 0.40f }, true);
		}
		if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
			b00l ^= 1;
			return true;
		}
		return false;
	}

	bool widgets::add_int(const char* option, int& _int, int min, int max)
	{
		add_button(option);

		if (Settings::optionCount == Settings::currentOption) {
			if (Settings::leftPressed) {
				_int < max ? _int++ : _int = min;
			}
			if (Settings::rightPressed) {
				_int >= min ? _int-- : _int = max;
			}
		}

		if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
			Draw::text(Tools::string_to_char("< " + std::to_string(_int) + " >"), Settings::integre, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.128f }, { 0.32f, 0.32f }, true);
		else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
			Draw::text(Tools::string_to_char("< " + std::to_string(_int) + " >"), Settings::integre, { Settings::menuX + 0.068f, (Settings::optionCount - (Settings::currentOption - 16)) * 0.035f + 0.12f }, { 0.32f, 0.32f }, true);

		if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
		else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
		else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
		return false;
	}
	bool widgets::add_int(const char* option, int& _int, int min, int max, int step)
	{
		add_button(option);

		if (Settings::optionCount == Settings::currentOption) {
			if (Settings::leftPressed) {
				_int < max ? _int += step : _int = min;
			}
			if (Settings::rightPressed) {
				_int >= min ? _int -= step : _int = max;
			}
		}

		if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
			Draw::text(Tools::string_to_char("< " + std::to_string(_int) + " >"), Settings::integre, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.125f }, { 0.32f, 0.32f }, true);
		else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
			Draw::text(Tools::string_to_char("< " + std::to_string(_int) + " >"), Settings::integre, { Settings::menuX + 0.068f, (Settings::optionCount - (Settings::currentOption - 16)) * 0.035f + 0.12f }, { 0.32f, 0.32f }, true);

		if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
		else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
		else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
		return false;
	}

	bool widgets::add_float(const char* option, float& _float, int min, int max)
	{
		add_button(option);

		if (Settings::optionCount == Settings::currentOption) {
			if (Settings::leftPressed) {
				_float <= min ? _float = max : _float -= 0.1f;
			}
			if (Settings::rightPressed) {
				_float >= max ? _float = min : _float += 0.1f;
			}
			_float < min ? _float = max : _float > max ? _float = min : NULL;
		}

		if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
			Draw::text(Tools::string_to_char(std::to_string(_float)), Settings::optionText, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.128f }, { 0.32f, 0.32f }, true);
		else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
			Draw::text(Tools::string_to_char(std::to_string(_float)), Settings::optionText, { Settings::menuX + 0.068f, (Settings::optionCount - (Settings::currentOption - 16)) * 0.035f + 0.12f }, { 0.32f, 0.32f }, true);

		if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
		else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
		else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
		return false;
	}
	bool widgets::add_float(const char* option, float& _float, int min, int max, int step)
	{
		add_button(option);

		if (Settings::optionCount == Settings::currentOption) {
			if (Settings::leftPressed) {
				_float <= min ? _float = max : _float -= 0.1f;
			}
			if (Settings::rightPressed) {
				_float >= max ? _float = min : _float += 0.1f;
			}
			_float < min ? _float = max : _float > max ? _float = min : NULL;
		}

		if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
			Draw::text(Tools::string_to_char(std::to_string(_float)), Settings::optionText, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.128f }, { 0.32f, 0.32f }, true);
		else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
			Draw::text(Tools::string_to_char(std::to_string(_float)), Settings::optionText, { Settings::menuX + 0.068f, (Settings::optionCount - (Settings::currentOption - 16)) * 0.035f + 0.12f }, { 0.32f, 0.32f }, true);

		if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
		else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
		else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
		return false;
	}

	bool widgets::add_int_vector(const char* option, std::vector<int> Vector, int& position)
	{
		add_button(option);

		if (Settings::optionCount == Settings::currentOption) {
			int max = Vector.size() - 1;
			int min = 0;
			if (Settings::leftPressed) {
				position >= 1 ? position-- : position = max;
			}
			if (Settings::rightPressed) {
				position < max ? position++ : position = min;
			}
		}

		if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
			Draw::text(Tools::string_to_char(std::to_string(Vector[position])), Settings::optionText, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.125f }, { 0.5f, 0.5f }, true);
		else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
			Draw::text(Tools::string_to_char(std::to_string(Vector[position])), Settings::optionText, { Settings::menuX + 0.068f, (Settings::optionCount - (Settings::currentOption - 16)) * 0.035f + 0.12f }, { 0.5f, 0.5f }, true);

		if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
		else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
		else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
		return false;
	}

	bool widgets::add_float_vector(const char* option, std::vector<float> Vector, int& position)
	{
		add_button(option);

		if (Settings::optionCount == Settings::currentOption) {
			size_t max = Vector.size() - 1;
			int min = 0;
			if (Settings::leftPressed) {
				position >= 1 ? position-- : position = max;
			}
			if (Settings::rightPressed) {
				position < max ? position++ : position = min;
			}
		}

		if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
			Draw::text(Tools::string_to_char(std::to_string(Vector[position])), Settings::optionText, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.125f }, { 0.5f, 0.5f }, true);
		else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
			Draw::text(Tools::string_to_char(std::to_string(Vector[position])), Settings::optionText, { Settings::menuX + 0.068f, (Settings::optionCount - (Settings::currentOption - 16)) * 0.035f + 0.12f }, { 0.5f, 0.5f }, true);

		if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
		else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
		else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
		return false;
	}

	bool widgets::add_string_vector(const char* option, std::vector<std::string> Vector, int& position)
	{
		add_button(option);

		if (Settings::optionCount == Settings::currentOption) {
			size_t max = Vector.size() - 1;
			int min = 0;
			if (Settings::leftPressed) {
				position >= 1 ? position-- : position = max;
			}
			if (Settings::rightPressed) {
				position < max ? position++ : position = min;
			}
		}

		if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
			Draw::text(Tools::string_to_char((Vector[position])), Settings::optionText, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.125f }, { 0.5f, 0.5f }, true);
		else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
			Draw::text(Tools::string_to_char((Vector[position])), Settings::optionText, { Settings::menuX + 0.068f, (Settings::optionCount - (Settings::currentOption - 16)) * 0.035f + 0.12f }, { 0.5f, 0.5f }, true);

		if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
		else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
		else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
		return false;
	}

	bool widgets::add_string_vector(const char* option, std::vector<char*> Vector, int& position)
	{
		add_button(option);

		if (Settings::optionCount == Settings::currentOption) {
			size_t max = Vector.size() - 1;
			int min = 0;
			if (Settings::leftPressed) {
				position >= 1 ? position-- : position = max;
			}
			if (Settings::rightPressed) {
				position < max ? position++ : position = min;
			}
		}

		if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
			Draw::text(((Vector[position])), Settings::optionText, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.125f }, { 0.5f, 0.5f }, true);
		else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
			Draw::text(((Vector[position])), Settings::optionText, { Settings::menuX + 0.068f, (Settings::optionCount - (Settings::currentOption - 16)) * 0.035f + 0.12f }, { 0.5f, 0.5f }, true);

		if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
		else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
		else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
		return false;
	}

	void widgets::end()
	{
		int opcount = Settings::optionCount;
		int currop = Settings::currentOption;
		if (opcount >= 16) {
			Draw::text(Tools::string_to_char(std::to_string(currop) + " / " + std::to_string(opcount)), Settings::count, { Settings::menuX + 0.078f, 17 * 0.035f + 0.125f }, { 0.35f, 0.35f }, true);
			Draw::rect(Settings::optionRect, { Settings::menuX, 17 * 0.035f + 0.1415f }, { 0.21f, 0.035f });
			Draw::rect(Settings::line, { Settings::menuX, 17 * 0.035f + 0.1235f }, { 0.21f, 0.002f });

		}
		else if (opcount > 0) {
			Draw::text(Tools::string_to_char(std::to_string(currop) + " / " + std::to_string(opcount)), Settings::count, { Settings::menuX + 0.078f, (Settings::optionCount + 1) * 0.035f + 0.125f }, { 0.35f, 0.35f }, true);
			Draw::rect(Settings::optionRect, { Settings::menuX, (Settings::optionCount + 1) * 0.035f + 0.1415f }, { 0.21f, 0.035f });
			Draw::rect(Settings::line, { Settings::menuX, (Settings::optionCount + 1) * 0.035f + 0.1235f }, { 0.21f, 0.002f });
		}
	}

	void PlaySoundFrontend_default(const char* sound_name)
	{
		AUDIO::PLAY_SOUND_FRONTEND(-1, sound_name, "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
	}
	void PlaySoundFrontend_default2(const char* sound_name)
	{
		AUDIO::PLAY_SOUND_FRONTEND(-1, sound_name, "DLC_HEIST_BIOLAB_PREP_HACKING_SOUNDS", 0);
	}


	int widgets::Settings::keyPressDelay = 200;
	int widgets::Settings::keyPressPreviousTick = GetTickCount64();
	int widgets::Settings::keyPressDelay2 = 100;
	int widgets::Settings::keyPressPreviousTick2 = GetTickCount64();
	int widgets::Settings::keyPressDelay3 = 140;
	int widgets::Settings::keyPressPreviousTick3 = GetTickCount64();
	int widgets::Settings::openKey = VK_F4;
	int widgets::Settings::backKey = VK_NUMPAD0;
	int widgets::Settings::upKey = VK_NUMPAD8;
	int widgets::Settings::downKey = VK_NUMPAD2;
	int widgets::Settings::leftKey = VK_NUMPAD4;
	int widgets::Settings::rightKey = VK_NUMPAD6;
	int widgets::Settings::selectKey = VK_NUMPAD5;
	int widgets::Settings::arrowupKey = VK_UP;
	int widgets::Settings::arrowdownKey = VK_DOWN;
	int widgets::Settings::arrowleftKey = VK_LEFT;
	int widgets::Settings::arrowrightKey = VK_RIGHT;
	int widgets::Settings::enterKey = VK_RETURN;
	int widgets::Settings::deleteKey = VK_BACK;

	bool widgets::Settings::controllerinput = true;
	void widgets::Checks::controlls()
	{
		Settings::selectPressed = false;
		Settings::leftPressed = false;
		Settings::rightPressed = false;
		if (GetTickCount64() - Settings::keyPressPreviousTick > Settings::keyPressDelay) {
			if (GetTickCount64() - Settings::keyPressPreviousTick2 > Settings::keyPressDelay2) {
				if (GetTickCount64() - Settings::keyPressPreviousTick3 > Settings::keyPressDelay3) {
					if (IsKeyPressed(VK_MULTIPLY) || PAD::IS_DISABLED_CONTROL_PRESSED(0, ControlScriptRB) && PAD::IS_DISABLED_CONTROL_PRESSED(0, ControlPhoneRight) && Settings::controllerinput) {
						Settings::menuLevel == 0 ? MenuLevelHandler::MoveMenu(SubMenus::mainmenu) : Settings::menuLevel == 1 ? MenuLevelHandler::BackMenu() : novoid();
						Settings::keyPressPreviousTick = GetTickCount64();
					}
					else if (IsKeyPressed(VK_NUMPAD0) || PAD::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendCancel) && Settings::controllerinput) {
						Settings::menuLevel > 0 ? MenuLevelHandler::BackMenu() : novoid();
						if (Settings::menuLevel > 0)
							PlaySoundFrontend_default("BACK");

						Settings::keyPressPreviousTick = GetTickCount64();
					}
					else if (IsKeyPressed(VK_NUMPAD8) || PAD::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendUp) && Settings::controllerinput) {
						Settings::currentOption > 1 ? Settings::currentOption-- : Settings::currentOption = Settings::optionCount;
						if (Settings::menuLevel > 0)
							PlaySoundFrontend_default("NAV_UP_DOWN");

						Settings::keyPressPreviousTick2 = GetTickCount64();
					}
					else if (IsKeyPressed(VK_NUMPAD2) || PAD::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendDown) && Settings::controllerinput) {
						Settings::currentOption < Settings::optionCount ? Settings::currentOption++ : Settings::currentOption = 1;
						if (Settings::menuLevel > 0)
							PlaySoundFrontend_default("NAV_UP_DOWN");

						Settings::keyPressPreviousTick2 = GetTickCount64();
					}
					else if (IsKeyPressed(VK_NUMPAD6) || PAD::IS_DISABLED_CONTROL_PRESSED(0, ControlPhoneRight) && Settings::controllerinput) {
						Settings::leftPressed = true;
						if (Settings::menuLevel > 0)
							PlaySoundFrontend_default("NAV_UP_DOWN");

						Settings::keyPressPreviousTick3 = GetTickCount64();
					}
					else if (IsKeyPressed(VK_NUMPAD4) || PAD::IS_DISABLED_CONTROL_PRESSED(0, ControlPhoneLeft) && Settings::controllerinput) {
						Settings::rightPressed = true;
						if (Settings::menuLevel > 0)
							PlaySoundFrontend_default("NAV_UP_DOWN");

						Settings::keyPressPreviousTick3 = GetTickCount64();
					}
					else if (IsKeyPressed(VK_NUMPAD5) || PAD::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept) && Settings::controllerinput) {
						Settings::selectPressed = true;
						if (Settings::menuLevel > 0)
							PlaySoundFrontend_default("SELECT");

						Settings::keyPressPreviousTick = GetTickCount64();
					}
				}
			}
		}
		Settings::optionCount = 0;
	}

	char* widgets::Tools::string_to_char(std::string string)
	{
		return _strdup(string.c_str());
	}

	void widgets::MenuLevelHandler::MoveMenu(SubMenus menu)
	{
		Settings::menusArray[Settings::menuLevel] = Settings::currentMenu;
		Settings::optionsArray[Settings::menuLevel] = Settings::currentOption;
		Settings::menuLevel++;
		Settings::currentMenu = menu;
		Settings::currentOption = 1;
	}

	void widgets::MenuLevelHandler::BackMenu()
	{
		Settings::menuLevel--;
		Settings::currentMenu = Settings::menusArray[Settings::menuLevel];
		Settings::currentOption = Settings::optionsArray[Settings::menuLevel];
	}
}