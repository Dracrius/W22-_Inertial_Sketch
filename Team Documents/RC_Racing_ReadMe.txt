======
Welcome
to
RC Racing
======
			an UE4 project by Inertial Sketch
		_____________________________________________________________________________________________

		1. Controls
		- W, L Joytick, R Trigger control acceleration
		- S, L Joytick, L Trigger control reverse
		- A + D, L Joytick control turning
		- A + D, L Joytick control rollover
		- Space, A Button control power-up usage
		- Escape, Backspace, Select Button Open Pause menu

		* Rollover used as a mechanism to return player-character to upright position when
		flipped over.
		
		* Powers-ups may vary from player-character enhancements such as acceleration boosts,
		to projectile objects that can collide with other players to disrupt them.
		_____________________________________________________________________________________________

		2. Gameplay

		RC Racing is a free-for-all racing game where networked players compete against one
		and other to see who can complete the track first. The game features a map with multiple
		branching paths that players can use to determine the best possible route they can take
		relative to their position in the race. Some paths are shorter and more direct but feature
		a challenging obstacle to complete. Some paths are longer but have power-up objects the
		player can overlap to improve their position in the race.

		Currently the map is based on a public park and will feature several obstacles to match
		the aesthetic. Currently slides, swing, sandboxes, ramps, bridges are planned for obstacles
		although they are not currently featured in Alpha 1. Additionally, a Trap, Bowling Ball, 
		Freeze, Boost and Firework power-ups are initially implimented and testable in the Test Map
		by picking up the Battery Pickups that will pick power-ups.

		The first player to complete three laps around the course will be determined the winner
		of the race once lap systems are implemented.
		_____________________________________________________________________________________________

		3. Menu (UI)

		The game has a Menu UI that allow the player to pick a map from the Local Race menu. The 
		UI is currently only mouse controlled so a cursor will be enabled while menus are active. 
		The goal of the menu UI will be to allow players to select network or solo play, to
		select their vehicle, and to adjust settings such as, volume, and Username which will be 
		saved. The Volume, and Username menus currently do nothing until save files are implimented.

		The in-game UI will feature relevant information to the player such as position, any
		power-ups currently held by the player, speed, and the elapsed time of the race.
		Currently there is also a pause menu which allows you to return to menu, to change tracks
		or to quit. The pause menu is configured to use the escape key but do to the editor's use 
		of it to quit the backspace key is also mapped to open the pause menu.
		
		_____________________________________________________________________________________________

		4. VR
		
		Basic VR support has been implimented. Do to the complications with menus there is no way 
		to use the current implimentation of the UI in VR. Because of this when launched in VR
		the Project will automatically load into the Test map. VR controls are configured
		for the Vive, Index and technically Oculus but due to Issues on my local system I can
		only test with SteamVR and my Quest and UE4 appears to have a broken Oculus Layout
		for SteamVR as nothing matches what is set. For this reason I used a Gamepad but
		from past experience if using the Oculus SDK it should work mine just wasn't finding my
		headset.
		
		If you flip the car the camera currently follows the springarm which will put you underground
		unfortunatly this may make users uncomfortable but I hope to solve it in the coming weeks.
		
		