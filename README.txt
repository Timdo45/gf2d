This is a prototype of a Roguelike game created to give the developer more experience in developing games in 2D using the SDL library

As of the writing of this, the game's features are:

	Different entities (player,upgrade items, enemies)
	Player ability to move and attack in the 4 cardinal directions (up,down,left,right) by using WASD to move and left click to attack
		direction is dictated by mouse position relative to the player 
	Different weapons that can be switched by pressing Left Shift
	The player can press 't' to save the game by instantly killing themselves
	The player can dash in a direction using the space bar up to the number of dashes they have
	Differnt upgrdes that can be accessed by colliding the player's hitbox with the box of the item and pressing 'f'
	These upgrades include:
		increased health
		increased maximum dashes
		increased number of revives
		increased speed
		increased number of Runes
	Players can purchase permanent upgrades by using Runes and pressing a different number:
			1 increases maximum health
			2 gains access to the spear weapon
			3 increases maximum number of dashes
			4 increases number of revives
	