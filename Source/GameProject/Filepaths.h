#pragma once
#include <string>

// Filepaths to assets used in game

namespace filepath {
	//Fonts
	const std::string consolas_path = "./font/consolas.ttf";
	const std::string consolas_bold_path = "./font/consolas_bold.ttf";
	const std::string consolas_italic_path = "./font/consolas_italic.ttf";

	//Audio
	const std::string menu_music = "./audio/Harp.ogg";
	const std::string win_music = "./audio/prepare_your_swords.ogg";
	const std::string castle_music = "./audio/dungeon002.ogg";

	//Textures
	// Backgrounds
	
	const std::string castle_background = "./textures/background.png";
	const std::string splash_background = "./textures/splashScreen.png";
	const std::string menu_background = "./textures/menu.png";
	const std::string win_background = "./textures/winScreen.png";

	// Tile sheets
	const std::string castle_tiles = "./textures/oppcastle-mod-tiles.png";
	
	// Hero spritesheets
	const std::string hero_sprite = "./textures/player/player-spritemap-v9.png";
	const std::string hero_robe = "./textures/armor/robe04-spritemap-v9.png";
	const std::string hero_armour = "./textures/armor/armor06-spritemap.png";
	const std::string hero_shield = "./textures/accessories/shield01-spritemap-v9.png";
	const std::string hero_helmet = "./textures/accessories/helm04-spritemap-v9.png";

}