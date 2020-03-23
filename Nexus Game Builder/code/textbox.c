
// -----------------------------------------------------------------------------------------------------

BMAP *bmpTextboxEmpty = "#2x2x32"; // an empty bitmap, used on textbox removing time

STRING *strTemp = ""; // a temporal string for textbox string parsing
STRING *strTail = ""; // a temporal string for textbox string edition

var evnTextboxButtonClick (var _but, PANEL *_pan); // an event for the textbox button 

LRESULT CALLBACK onMessageOld(HWND _hwnd, UINT _msg, WPARAM _wParam, LPARAM _lParam); // a protoype for backing the engines message handler

// -----------------------------------------------------------------------------------------------------

typedef struct TEXTBOX {
	var posX;
	var posY;
	var sizeX;
	var sizeY;
	var fontScale;
	var paddingX;
	var paddingY;
	var borderSize;
	COLOR bgColor;
	COLOR textColor;
	COLOR selectColor;
	FONT *font;
	STRING *string;
	var flags;
	// --------------
	PANEL *panel;
	TEXT *text;
	var width;
	var height;
	BMAP *bmpTextbox;
	BMAP *bmpSelected;
	var buttonID;
	var spaceWidth;
	// --------------
	struct TEXTBOX *next;
} TEXTBOX;

TEXTBOX *textboxStack = NULL;
TEXTBOX *textboxMe = NULL;

// -----------------------------------------------------------------------------------------------------

TEXT *txtTextboxCursor = { // the cursor of string edition
	string = ("|");
	flags = LIGHT;
}

// -----------------------------------------------------------------------------------------------------

// get a pointer the the last character defined by _asc
// returns NULL if not found
char *str_last_asc (STRING *_strT, int _asc, int _offset) {
	char *_char = _strT->chars + (int)str_len(_strT) - 1 - _offset;
	char *_charLast = _strT->chars - 1;
	for (; _char>_charLast; _char-=1)
		if(*_char == _asc)
			return _char;
	return NULL;
}

// put spaces instead of tabs and linebreaks in a string 
void str_clean_tabs_and_linebreaks (STRING *_strT) {
	int _last = str_len(_strT) - 1;
	char *_char = _strT->chars;
	char *_charLast = _strT->chars + (int)str_len(_strT);
	for (; _char<_charLast; _char+=1)
		if((*_char == 13) || (*_char == 9) || (*_char == 10))
			*_char = 32;
}

// -----------------------------------------------------------------------------------------------------

// draws the bitmap used in the button created as textbox
void drawTextbox (TEXTBOX *_tb, BMAP *_bmp, COLOR *_colBg, COLOR *_colBorder) {
	bmap_rendertarget(_bmp, 0, 0);
		var _width = bmap_width(_bmp);
		var _height = bmap_height(_bmp);
		draw_quad(NULL, nullvector, NULL, vector(_width, _height, 0), NULL, _colBorder, 100, 0); 
		draw_quad(NULL, vector(_tb->borderSize, _tb->borderSize, 0), NULL, vector(_width - _tb->borderSize * 2, _height - _tb->borderSize * 2, 0), NULL, _colBg, 100, 0); 
		draw_obj(_tb->text);
	bmap_rendertarget(NULL, 0, 0);
}

// -----------------------------------------------------------------------------------------------------

// puts the cursor at the current character of the current string of txtTextboxEdition
void txtTextboxCursorLocate () {
	DEBUG_VAR(textboxMe->spaceWidth, 200);
	DEBUG_VAR(textboxMe->font->dx, 220);
	STRING *_strT = (textboxMe->text->pstring)[txtTextboxCursor->skill_y];
	str_cpy(strTemp, _strT);
	char *_char = strTemp->chars + (int)txtTextboxCursor->skill_x;
	*_char = NULL; 
	txtTextboxCursor->pos_x = 1 + textboxMe->panel->pos_x + textboxMe->posX + (str_width(strTemp, textboxMe->font) * textboxMe->fontScale) + textboxMe->borderSize + textboxMe->paddingX - textboxMe->spaceWidth / 2;
	if (*(_char - 1) == 32)
		txtTextboxCursor->pos_x += (textboxMe->spaceWidth * textboxMe->fontScale) - textboxMe->spaceWidth * textboxMe->fontScale;
	txtTextboxCursor->pos_y = textboxMe->panel->pos_y + textboxMe->posY + txtTextboxCursor->skill_y * (textboxMe->font->dy * textboxMe->fontScale) + textboxMe->borderSize + textboxMe->paddingY;
}

// -----------------------------------------------------------------------------------------------------

// copies the content of txtTextboxEdition to a string starting in the string stated by the index parameter
void textToString (TEXTBOX *_tb, STRING *_strTarget, int _index) {
	TEXT *_text = _tb->text;
	str_cpy(_strTarget, "");
	STRING **_strPtr = _text->pstring + _index;
	STRING **_strLast = _text->pstring + (int)_text->strings;
	for (; _strPtr<_strLast; _strPtr+=1)
		str_cat(_strTarget, *_strPtr);
}

// copies a string to txtTextboxEdition word by word starting in the string stated by the index parameter
// warning: the string is emptied!!
void textFromString (TEXTBOX *_tb, STRING *_strSource, int _index) {
	TEXT *_text = _tb->text;
	int _i = _index;
	for(; _i<_text->strings; _i+=1)
		str_cpy((_text->pstring)[_i], "");
	while (*_strSource->chars == 32) 
		str_clip(_strSource, 1);
	STRING *_strCurrent = (_text->pstring)[_index];
	while(str_len(_strSource) > 0) {
		int _nextSpace = str_stri(_str(_strSource->chars + 1), " ") + 1;
		if (_nextSpace == 1) {
			_nextSpace = str_len(_strSource);
		} else if ((_nextSpace == 2) && (*_strSource->chars == 32)) {
			str_clip(_strSource, 1);
			continue;
		}
		char *_char = _strSource->chars + _nextSpace;
		char _charOld = *_char;
		*_char = NULL;
		int _width = str_width(_strSource, _tb->font) * _tb->fontScale;
		for (; _width > _tb->width; _width = str_width(_strSource, _tb->font) * _tb->fontScale) {
			_nextSpace -= 1;
			*_char = _charOld;
			_char -= 1;
			_charOld = *_char;
			*_char = NULL;
		}
		if((str_width(_strCurrent, _tb->font) * _tb->fontScale) + _width > _tb->width) {
			if (_index == _tb->sizeY - 1)
				break;
			_strCurrent = (_text->pstring)[_index+=1];
		}
		str_cat(_strCurrent, _strSource); 
		*_char = _charOld;
		str_clip(_strSource, _nextSpace);
	}
}

// copies the string of a textbox to txtTextboxEdition word by word and draws the two bitmaps of the textbox
void textboxUpdate (TEXTBOX *_tb) {
	if (_tb == textboxMe)
		return;
	TEXT *_text = _tb->text;
	str_cpy(strTemp, _tb->string);
	textFromString(_tb, strTemp, 0);
	drawTextbox(_tb, _tb->bmpTextbox, &_tb->bgColor, &_tb->textColor);
	drawTextbox(_tb, _tb->bmpSelected, &_tb->bgColor, &_tb->selectColor);
}

// states the cursor pos same as it was in the previous string, if exists
void txtTextboxCursorRowUpOverload () {
	if (txtTextboxCursor->skill_y > 0) {
		txtTextboxCursor->skill_y -= 1;
		txtTextboxCursor->skill_x += str_len((textboxMe->text->pstring)[txtTextboxCursor->skill_y]);
	}
}

// set a valid cursor position from overloaded
void txtTextboxCursorResetOverload () {
	TEXT *_text = textboxMe->text;
	var _stringLength = str_len((_text->pstring)[txtTextboxCursor->skill_y]);
	while (txtTextboxCursor->skill_x > _stringLength) {
		if (txtTextboxCursor->skill_y < textboxMe->sizeY - 1) {
			txtTextboxCursor->skill_y += 1;
			txtTextboxCursor->skill_x -= _stringLength;
			_stringLength = str_len((_text->pstring)[txtTextboxCursor->skill_y]);
		} else {
			txtTextboxCursor->skill_x = _stringLength;
			break;
		}
	}
}

// windows message handler for textbox edition
LRESULT CALLBACK textboxMessageHandler(HWND _hwnd, UINT _msg, WPARAM _wParam, LPARAM _lParam) {
	switch (_msg) {
		case WM_CHAR:
			switch (_wParam) {
				case 8:  // backspace
				case 13: // enter
				case 27: // escape
					break;
				default:
					STRING *_strCurrent = (textboxMe->text->pstring)[txtTextboxCursor->skill_y];
					char *_char = _strCurrent->chars + (int)txtTextboxCursor->skill_x;
					char _key[2];
					_key[0] = _wParam;
					_key[1] = NULL;
					
					STRING *tempStr = "!\"#$%&'()*+,-./0123456789:;<=>?@abcdefghijklmnopqrstuvwxyz[\]^_|~";
					var pos = str_stri(tempStr, _str(_key));					
					if (pos <= 0) {
						if (_wParam != 32)
							break;
						else if (txtTextboxCursor->skill_x == 0)
							break;
						else if ((*(_char - 1) == 32) || (*_char == 32))
							break;
					}
					str_cpy(strTail, _char);
					*_char = NULL;
					str_cat(_strCurrent, _key);
					str_cat(_strCurrent, strTail);
					txtTextboxCursor->skill_x += 1;
					txtTextboxCursorRowUpOverload ();
					textToString (textboxMe, strTemp, txtTextboxCursor->skill_y);
					textFromString (textboxMe, strTemp, txtTextboxCursor->skill_y);
					txtTextboxCursorResetOverload ();
					txtTextboxCursorLocate ();
					drawTextbox(textboxMe, textboxMe->bmpSelected, &textboxMe->bgColor, &textboxMe->selectColor);
					break;			
			}
		case WM_KEYDOWN:
			switch (_wParam) {
				case 13: // enter or escape
				case 27: 
					textboxMe = NULL;
					break;
				case 8: // backspace or delete
				case 46:
					STRING *_strCurrent = (textboxMe->text->pstring)[txtTextboxCursor->skill_y];
					char *_charLast = _strCurrent->chars + (int)txtTextboxCursor->skill_x;
					if (_wParam == 8) {
						if(txtTextboxCursor->skill_y == 0)
							if (txtTextboxCursor->skill_x == 0)
								break;
						str_cpy(strTail, _charLast);
						*(_charLast - 1) = NULL;
						txtTextboxCursor->skill_x -= 1;
					} else {
						if(str_len(_strCurrent) > txtTextboxCursor->skill_x) {
							str_cpy(strTail, _charLast + 1);
							*_charLast = NULL;
						} else if (txtTextboxCursor->skill_y < textboxMe->sizeY - 1) {
							str_cpy(strTail, "");
							str_clip((textboxMe->text->pstring)[txtTextboxCursor->skill_y + 1], 1);
						}
					}
					str_cat(_strCurrent, strTail);
					txtTextboxCursorRowUpOverload ();
					textToString (textboxMe, strTemp, txtTextboxCursor->skill_y);
					textFromString (textboxMe, strTemp, txtTextboxCursor->skill_y);
					txtTextboxCursorResetOverload ();
					txtTextboxCursorLocate ();
					drawTextbox(textboxMe, textboxMe->bmpSelected, &textboxMe->bgColor, &textboxMe->selectColor);
					break;
				case 37: // left
					if (txtTextboxCursor->skill_x > 1) {
						txtTextboxCursor->skill_x -= 1;
						txtTextboxCursorLocate ();
					} else if (txtTextboxCursor->skill_y > 0) {
						txtTextboxCursor->skill_y -= 1;
						txtTextboxCursor->skill_x = str_len((textboxMe->text->pstring)[txtTextboxCursor->skill_y]);
						txtTextboxCursorLocate ();
					} else {
						txtTextboxCursor->skill_x = 0;
						txtTextboxCursorLocate ();
					}
					break;
				case 39: // right
					if (txtTextboxCursor->skill_x < str_len((textboxMe->text->pstring)[txtTextboxCursor->skill_y])) {
						txtTextboxCursor->skill_x += 1;
						txtTextboxCursorLocate ();
					} else if (txtTextboxCursor->skill_y < textboxMe->sizeY - 1) {
						if (str_len((textboxMe->text->pstring)[txtTextboxCursor->skill_y + 1]) > 0) {
							txtTextboxCursor->skill_y += 1;
							txtTextboxCursor->skill_x = 1;
							txtTextboxCursorLocate ();
						}
					}
					break;
				case 38: // up
					if (txtTextboxCursor->skill_y > 0) {
						txtTextboxCursor->skill_y -= 1;
						txtTextboxCursor->skill_x = minv(txtTextboxCursor->skill_x, str_len((textboxMe->text->pstring)[txtTextboxCursor->skill_y]));
						txtTextboxCursorLocate ();
					}
					break;
				case 40: // down
					if (txtTextboxCursor->skill_y < textboxMe->sizeY - 1) {
						var _stringLength = str_len((textboxMe->text->pstring)[txtTextboxCursor->skill_y + 1]);
						if ((_stringLength > 0) && (txtTextboxCursor->skill_y < textboxMe->sizeY - 1)) {
							txtTextboxCursor->skill_y += 1;
							if (txtTextboxCursor->skill_x == 0)
								txtTextboxCursor->skill_x = 1;
							else
								txtTextboxCursor->skill_x = minv(txtTextboxCursor->skill_x, _stringLength);
							txtTextboxCursorLocate ();
						}
					}
					break;
			}
	}
	return onMessageOld(_hwnd, _msg, _wParam, _lParam);
}

void txtTextboxCursorByMouse (TEXTBOX *_textbox) {
	TEXT *_text = _textbox->text;
	var _minY = _textbox->panel->pos_y + _textbox->posY + _textbox->borderSize + _textbox->paddingY;
	var _row = clamp(floor((mouse_pos.y - _minY) / (_textbox->font->dy * _textbox->fontScale)), 0, _textbox->sizeY - 1); 
	txtTextboxCursor->skill_y = _row;
	for (; txtTextboxCursor->skill_y>0; txtTextboxCursor->skill_y-=1)
		if(str_len((_text->pstring)[txtTextboxCursor->skill_y]) > 0)
			break;
	if (_row != txtTextboxCursor->skill_y) {
		txtTextboxCursor->skill_x = str_len((_text->pstring)[txtTextboxCursor->skill_y]);
	} else {
		str_cpy(strTemp, (_text->pstring)[txtTextboxCursor->skill_y]);
		var _minX = _textbox->panel->pos_x + _textbox->posX + _textbox->borderSize + _textbox->paddingX;
		var _posX = maxv(mouse_pos.x - _minX, 1);
		txtTextboxCursor->skill_x = str_len(strTemp);
		var _width = str_width(strTemp, _textbox->font) * _textbox->fontScale;
		char *_char = strTemp->chars + (int)txtTextboxCursor->skill_x - 1;
		if(*_char == 32)
			_width += (_textbox->spaceWidth * _textbox->fontScale) - _textbox->spaceWidth * _textbox->fontScale;
		for (; _width>_posX; _char-=1, txtTextboxCursor->skill_x-=1) {
			_width -= str_width(_str(_char), _textbox->font) * _textbox->fontScale;
			if(*_char == 32)
				_width -= (_textbox->spaceWidth * _textbox->fontScale) - _textbox->spaceWidth * _textbox->fontScale;
			*_char = NULL;
		}
	}
	if (txtTextboxCursor->skill_x == 0) {
		if (txtTextboxCursor->skill_y > 0) {
			txtTextboxCursor->skill_y -= 1;
			txtTextboxCursor->skill_x = str_len((_text->pstring)[txtTextboxCursor->skill_y]);
		}
	}
	txtTextboxCursorLocate();
}

void textboxEdit () {
	onMessageOld = on_message;
	on_message = textboxMessageHandler;
	TEXTBOX *_textbox = textboxMe;
	layer_sort(txtTextboxCursor, _textbox->panel->layer + 1);
	vec_set(&txtTextboxCursor->blue, &_textbox->textColor);
	txtTextboxCursor->font = _textbox->font;
	txtTextboxCursor->scale_x = _textbox->text->scale_x;
	txtTextboxCursor->scale_y = _textbox->text->scale_y;
	txtTextboxCursor->flags |= SHOW;
	pan_setbutton(_textbox->panel, _textbox->buttonID, 0, _textbox->posX, _textbox->posY, _textbox->bmpSelected, _textbox->bmpSelected, _textbox->bmpSelected, _textbox->bmpSelected, NULL, NULL, NULL); // deactivate the textbox button
	textboxUpdate (_textbox);
	txtTextboxCursorByMouse (_textbox);
	var _timer = total_ticks + TEXTBOX_CURSOR_LAPSE;
	var _mouseLeft = 1;
	while(_textbox == textboxMe) {
		if (mouse_left && !_mouseLeft) {
			if (mouse_panel != _textbox->panel) {
				textboxMe = NULL;
				break;
			}
			var _minX = _textbox->panel->pos_x + _textbox->posX;
			var _minY = _textbox->panel->pos_y + _textbox->posY;
			if((_minX > mouse_pos.x) || (_minX + _textbox->width + (_textbox->borderSize + _textbox->paddingX) * 2 < mouse_pos.x) || (_minY > mouse_pos.y) || (_minY + _textbox->height + (_textbox->borderSize + _textbox->paddingY) * 2 < mouse_pos.y)) {
				textboxMe = NULL;
				break;
			} else {
				txtTextboxCursorByMouse (_textbox);
			}
		}
		_mouseLeft = mouse_left;
		if (_timer < total_ticks) {
			_timer = total_ticks + TEXTBOX_CURSOR_LAPSE;
			txtTextboxCursor->flags ^= SHOW;
		}
		wait(1);
	}
	if(key_esc) {
		textboxUpdate (_textbox);
	} else {
		textToString (_textbox, _textbox->string, 0);
		drawTextbox(_textbox, _textbox->bmpTextbox, &_textbox->bgColor, &_textbox->textColor);
	}
	txtTextboxCursor->flags &= ~SHOW;
	pan_setbutton(_textbox->panel, _textbox->buttonID, 0, _textbox->posX, _textbox->posY, _textbox->bmpSelected, _textbox->bmpTextbox, _textbox->bmpSelected, _textbox->bmpTextbox, evnTextboxButtonClick, NULL, NULL); // restore the texbox button
	on_message = onMessageOld;
}

// -----------------------------------------------------------------------------------------------------

// event of the textbox button
var evnTextboxButtonClick (var _but, PANEL *_pan) {
	switch (event_type) {
		case EVENT_CLICK:
			textboxMe = textboxStack;
			for(; textboxMe!=NULL; textboxMe=textboxMe->next) {
				if (textboxMe->panel!=_pan || textboxMe->buttonID!=_but)
					continue;
				wait(1); // let end previous edition loop, if any
				textboxEdit ();
				break;
			}
			break;
	}
}

TEXTBOX *pan_textbox_create (PANEL *_pan, TEXTBOX_CONFIG *_config) {
	TEXTBOX *_textbox = sys_malloc(sizeof(TEXTBOX));
	memset(_textbox, 0, sizeof(TEXTBOX));
	memcpy(_textbox, _config, sizeof(TEXTBOX_CONFIG));
	if (_textbox->string == NULL) {
		_textbox->string = str_create("");
		_textbox->flags |= TEXTBOX_REMOVE_STRING;
	} else {
		str_clean_tabs_and_linebreaks(_textbox->string);
	}
	if (_textbox->font == NULL)
		_textbox->font = fntTextboxDefault;
	_textbox->sizeX = maxv(_textbox->sizeX, 1);
	_textbox->sizeY = maxv(_textbox->sizeY, 1);
	_textbox->fontScale = maxv(_textbox->fontScale, 0.1);
	_textbox->paddingX = maxv(_textbox->paddingX, 1);
	_textbox->paddingY = maxv(_textbox->paddingY, 1);
	_textbox->borderSize = maxv(_textbox->borderSize, 1);
	_textbox->panel = _pan;
	TEXT *_text = _textbox->text = txt_create(0, 1);
	set(_text, LIGHT);
	_text->scale_x = _textbox->fontScale;
	_text->scale_y = _textbox->fontScale;
	vec_set(&_text->blue, &_textbox->textColor);
	_text->font = _textbox->font;
	_text->pos_x = _textbox->borderSize + _textbox->paddingX;
	_text->pos_y = _textbox->borderSize + _textbox->paddingY;
	while (_text->strings < _textbox->sizeY)
		txt_addstring(_text, str_create(""));
	_textbox->spaceWidth = _textbox->font->dx * _textbox->fontScale;
	_textbox->width = _textbox->sizeX * _textbox->spaceWidth;
	_textbox->height = _textbox->sizeY * (_textbox->font->dy * _textbox->fontScale);
	_textbox->bmpTextbox = bmap_createblack(_textbox->width + _textbox->borderSize * 2 + _textbox->paddingX * 2 + _textbox->spaceWidth, _textbox->height + _textbox->borderSize * 2 + _textbox->paddingY * 2, 24);
	drawTextbox(_textbox, _textbox->bmpTextbox, &_textbox->bgColor, &_textbox->textColor);
	_textbox->bmpSelected = bmap_createblack(bmap_width(_textbox->bmpTextbox), bmap_height(_textbox->bmpTextbox), 24);
	drawTextbox(_textbox, _textbox->bmpSelected, &_textbox->bgColor, &_textbox->selectColor);
	_textbox->buttonID = pan_setbutton(_pan, 0, 0, _textbox->posX, _textbox->posY, _textbox->bmpSelected, _textbox->bmpTextbox, _textbox->bmpSelected, _textbox->bmpTextbox, evnTextboxButtonClick, NULL, NULL /*evnTextboxButtonLeave, evnTextboxButtonOver*/);
	_textbox->next = textboxStack;
	textboxStack = _textbox;
	_textbox->panel->size_x = maxv(_textbox->panel->size_x, _textbox->posX + bmap_width(_textbox->bmpTextbox));
	_textbox->panel->size_y = maxv(_textbox->panel->size_y, _textbox->posY + bmap_height(_textbox->bmpTextbox));
	textboxUpdate (_textbox);
	textToString (_textbox, _textbox->string, 0);
	return _textbox;
}

void pan_textbox_remove (var _textboxHandle) {
	TEXTBOX *_textbox = (TEXTBOX*)_textboxHandle;
	if(_textbox == textboxMe) {
		textboxMe = NULL;
		wait(1);
	}
	if(_textbox->flags & TEXTBOX_REMOVE_FONT)
		ptr_remove(_textbox->font);
	if(_textbox->flags & TEXTBOX_REMOVE_STRING)
		ptr_remove(_textbox->string);
	pan_setbutton(_textbox->panel, _textbox->buttonID, 0, screen_size.x, screen_size.y, bmpTextboxEmpty, bmpTextboxEmpty, bmpTextboxEmpty, bmpTextboxEmpty, NULL, NULL, NULL);
	bmap_remove(_textbox->bmpTextbox);
	bmap_remove(_textbox->bmpSelected);
	STRING **_strPtr = _textbox->text->pstring;
	STRING **_strLast = _textbox->text->pstring + (int)_textbox->text->strings;
	for (; _strPtr<_strLast; _strPtr+=1)
		str_remove(*_strPtr);
	ptr_remove(_textbox->text);
	TEXTBOX *_tbPrev = NULL;
	TEXTBOX *_tb = textboxStack;
	for (; _tb!=NULL; _tbPrev=_tb, _tb=_tb->next) {
		if (_tb != _textbox)
			continue;
		if (_tbPrev == NULL)
			textboxStack = _textbox->next;
		else
			_tbPrev->next = _textbox->next;
		sys_free(_textbox);
		break;
	}
}

void pan_textbox_remove_all () {
	textboxMe = NULL;
	//wait(1); // this will cause 'unfreed' memory issue, on exit
	TEXTBOX *_tb = textboxStack;
	for (; _tb!=NULL; _tb=textboxStack) {
		textboxStack = _tb->next;
		if(_tb->flags & TEXTBOX_REMOVE_FONT)
			ptr_remove(_tb->font);
		if(_tb->flags & TEXTBOX_REMOVE_STRING)
			ptr_remove(_tb->string);
		pan_setbutton(_tb->panel, _tb->buttonID, 0, screen_size.x, screen_size.y, bmpTextboxEmpty, bmpTextboxEmpty, bmpTextboxEmpty, bmpTextboxEmpty, NULL, NULL, NULL);
		bmap_remove(_tb->bmpTextbox);
		bmap_remove(_tb->bmpSelected);
		STRING **_strPtr = _tb->text->pstring;
		STRING **_strLast = _tb->text->pstring + (int)_tb->text->strings;
		for (; _strPtr<_strLast; _strPtr+=1)
			str_remove(*_strPtr);
		ptr_remove(_tb->text);
		sys_free(_tb);
	}
}