
FONT *fntTextboxDefault = "ackfont.tga"; // The font used as default

// -----------------------------------------------------------------------------------------------------

#define TEXTBOX_CURSOR_LAPSE           4

// -----------------------------------------------------------------------------------------------------

// TEXTBOX_CONFIG flags
#define TEXTBOX_REMOVE_STRING          (1<<0) // remove the string when textbox is removed
#define TEXTBOX_REMOVE_FONT            (1<<1) // remove the font when textbox is removed

typedef struct TEXTBOX_CONFIG {
	var posX;
	var posY;
	var sizeX;
	var sizeY;
	var fontScale;
	var paddingX;
	var paddingY;
	var borderSize;
	COLOR backgroundColor;
	COLOR textColor;
	COLOR selectColor;
	FONT *font;
	STRING *string;
	var flags;
} TEXTBOX_CONFIG;

// -----------------------------------------------------------------------------------------------------

// Creates a textbox
// Returns a texbox handler
var pan_textbox_create (PANEL *_pan, TEXTBOX_CONFIG *_config);

// Removes a textbox, its panel must exist
void pan_textbox_remove (var _textboxHandle);

// Removes all existing textboxes
void pan_textbox_remove_all ();

// Updates a textbox
// does not work with active textboxes
void textboxUpdate (var _textboxHandle);

// -----------------------------------------------------------------------------------------------------

#include "textbox.c"