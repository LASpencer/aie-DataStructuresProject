Data Structures Game Project
by L. Andrew Spencer 2017

This program plays a 2d platformer. The player must make their way to the door on the right side of the 
screen to win the game.

I. USE
-------

KEYBOARD CONTROLS
All screens:
F		Toggle FPS display

Battle:
A,D		Move left and right
S		Crouch
W		Jump
ESC		Pause/Unpause
`(Grave key)	Toggle showing hitboxes

On running 

II. DESIGN
-----------



This program uses three main design patterns: Component, Factory, and Observer

The Component pattern is used to define the behaviour of Entities in this game. An Entity
is an object with a position and various components. 
An entity may only have one component of any particular type. These types are given a particular value, 
returned by the component's getID method. The values are chosen to be powers of two, so they have no 
overlapping bits and so can be used for a bitset to easily check the components an entity has.

It also uses the State 

III. ATTRIBUTIONS
------------------

Accessories, armor, player and weapons sprite sheets from "Hero Spritesheets (Ars Notoria)" by Balmer
Available at https://opengameart.org/content/hero-spritesheets-ars-notoria

oppcastle tileset from "Spooky Castle Tileset" by Buch (https://opengameart.org/users/buch)
Available at https://opengameart.org/content/spooky-castle-tileset

winScreen.png uses image from "Fortress background/storyboard image" by Joakim Persson, 
Available at https://opengameart.org/content/fortress-backgroundstoryboard-image
under CC BY 3.0 license https://creativecommons.org/licenses/by/3.0/

menu.png uses images from "Castle in the Dark" by tamashihoshi
Available at https://opengameart.org/content/castle-in-the-dark
under CC BY 3.0 license https://creativecommons.org/licenses/by/3.0/
The work was originally in the form of an animated gif, and the frames were moved into tiles of the png image

"Prepare Your Swords" by Bojidar Marinov
Available at https://opengameart.org/content/prepare-your-swords

"Dungeon Ambience"(dungeon002.ogg) by yd
Available at https://opengameart.org/content/dungeon-ambience

"Soft Mysterious Harp Loop"(Harp.ogg) by Jordan Hake
Avaialbe at https://opengameart.org/content/soft-mysterious-harp-loop
under CC BY 3.0 license https://creativecommons.org/licenses/by/3.0/

Acknowledgements and licensing details for software dependencies can be found in the dependencies folder

