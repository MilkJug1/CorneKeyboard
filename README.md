# CorneKeyboard

This is my custom firmware for my Corne Keyboard, [photo here], actively being worked on and will constantly changed

Keyboard is built with an Elite Pi so some specific things for an Elite pi are here.

WPM Animations are from another repo, [marekpiechut/qmk-animations](https://github.com/marekpiechut/qmk-animations). 

Install this under the `crkbd/keymaps` under MilkJug or whatever folder name you want.

Currently uses: 
- 2 OLED Screens
- WPM Calculations
- RP2040 Double Tap Reset to Flash
- RGB Matrix with some existing animations (A lot of them I have included, if you plan to use a different microcontroller, 
, might want to remove some of those `#define`s in the `config.h` file)
- Currently has 4 layers, plan to add some more, but still have to figure out what I want
- Layout(Mainly referring to a lot of the mod-keys, LSFT, LCTL, and others) are subject to change, still have to find a comfortable way that I can use them that doesn't affect gaming
- Tap Dancing and Tap-Hold was being used, had to remove them for the time being because of issues that It was causing for gaming, will figure something out
- Has VIA support, default corne config doesn't have it 
- Split WPM handling 

## Planned
- Have Tap-Dances, Tap-holds, and some more layers (Maybe even a layer for colemak 👀)
- Much nicer and different OLED Graphics, want to add something more than what I have so far, still figuring out something.


## TODO/Still Broken
~~- One LED (On the actual keyboard) is still a bit messed up, should prob fix that~~
~~- Weird issue where Layouts aren't uploading or saving correctly (Could be an issue with swp files with Neovim and maybe VIA?)~~

- Actually find a way to incorporate using this into gaming better, bit annoying for the moment when playing some games.
    - Kind of fixed? Have a dedicated Gaming layer at the current moment.



