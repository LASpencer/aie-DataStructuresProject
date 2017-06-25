Data Structures Game Project
by L. Andrew Spencer 2017

This program plays a 2d platformer. The player must make their way to the door on the right side of the 
screen to win the game.

A repository for this project can be found at https://github.com/LASpencer/aie-DataStructuresProject


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

On running the game, a splash screen appears for a few seconds. When all game assets 
are loaded, you can press any key to skip to the menu screen instead of waiting.

The menu screen has Play and Quit buttons. Clicking Play begins the game.
While playing, you may quit the game by pausing (ESC) and clicking the Quit button
On reaching the door at the right of the screen, a Win Screen is shown. Clicking Quit
ends the program, and clicking Main Menu returns to the main menu so the game can be 
played again.

II. DESIGN
-----------

As required, this program uses custom container classes: Array (a dynamic array), List (a double linked
list), and Map (a search tree map). These containers are also used to implement Stack, Queue, and Deque
containers.

Documentation for the container classes used in this project can be found in the 
repository wiki at https://github.com/LASpencer/aie-DataStructuresProject/wiki/Containers

The program's state is managed through a stack state machine, GameStateMachine. The GameProjectApp
object (inheriting from the bootstrap Application class) contains a GameStateMachine object. During update
and draw, it calls the respective methods on the GameStateMachine. This in turn calls update on each
state in the stack (starting from the top), and then checks if the top state has set any flags for popping it,
pushing another state on top, or transferring to a new state. 
During Draw, it calls each state's draw method, but in reverse order (bottom to top). This means that during
the pause state, the game can still be seen behind the pause screen.

A state machine is also used for controlling the hero, with transitions based on player input and whether the
hero is touching the floor.

This program uses the Component, Factory, and Observer design patterns. 
Component is used in defining the behaviour of game entities. The Entity class has a position, a bitset of
identifying tags, and several components. The components currently used are Sprite (including MultiSprite) for
drawing the entity on the screen, Collider for testing collision with other entities, and Controller (implemented
with HeroController) for controlling the entity. During update and draw, components of the same type are updated
(and drawn) together. This means that systems such as collision detection and resolution can update as a single
unit, rather than being incrementally updated as each entity involved updates. It also allows code to be 
flexibly reused, as any entity that needs to perform some behaviour is just given the appropriate component.

Since entities are defined by their components and tags, rather than a class heirarchy of Entity subclasses, there
needs to be a way to create particular types of Entities. This is accomplished with the Factory design pattern. The
EntityFactory class is given a private method to produce each type of entity needed, by putting together the 
required components with the right data, and setting the appropriate tags. Calling its public createEntity method
with a value from the EntityType enumeration causes it to create the entity requested and add it to the 
GameProjectApp object's entities list.

The Observer pattern is used to allow objects to cause behaviour in other objects without creating a dependency 
between them. It involves two abstract classes: Subject, which provides an interface to add Observers to a list and
send them Event objects, and Observer which provides an interface for being notified of Events by a Subject. 
Event is a class that contains an EventID, indicating what the event is, and some subclasses have additional data.
So the CollisionEvent also contains information about the entity the Subject collided with, how their hitboxes were
tagged, and the penetration vector. Based on the information in the Event object, and the identity of the Subject
producing it, the Observer can respond accordingly without the Subject needing to know what, if any, response its 
Observers should have.

This is mainly used in collision resolution, as Collider components are also Subjects which notify their Observers 
when a collision occurs. It is also used in triggering state transitions: several states observe Button objects for
click events, and BattleState observes the door's collider for a collision with the player.


See the Design Document in the Docs folder for further details.


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

