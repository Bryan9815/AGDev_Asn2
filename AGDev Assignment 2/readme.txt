Move forward, left, backward, right (In game) - WASD by default, can be changed in Gameplay.lua file

WASD - Up, down, left, right (In menu)

QE - Switch back and forth from Audio Settings page to Game Settings page, highlighted in UI

Spacebar - Jump (In game), Activate Button (In menu)

Left Mouse Button - Shoot

R - Reload weapon

IJKLOP - light movement
1,2 - toggle front face culling
3,4 - toggle wireframe mode
5,6,7 - toggle point, directional, spotlight

Audio Settings and Game Settings are cascading game states from the Options State.

List of Waypoints printed out on console at start of gameplay is done by a C function called in the LuaCfunction.lua file

Player starting position, mouse sensitivity, player walking speed, max ammo, starting ammo, total ammo, starting total ammo,
ground position, ground scale, number of waypoints, waypoint positions, movement input, sound effects volume, music volume,
window mode (fullscreen/window) and window resolution are all saved & loaded by Lua.