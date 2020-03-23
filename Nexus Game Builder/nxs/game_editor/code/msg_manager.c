/*#########################################################################################################################################################
NEXUS MESSAGE MANAGER :: By Brian Pressley (Evo) (Evoeon) :::: Message Manager Script
Function loops controls all saving/loading/editing of all editor textboxes
TEXTBOX FEATURE : "textbox.h" "textbox.c" Created By TXESMI

1. First textbox script section : CHAPTER MENU
2. Second textbox script section : CONTENT MENU
#########################################################################################################################################################*/

//########################
//SECTION 1 : Chapter Menu
//########################

//1  =  Textboxes are created, active, and will save input
//2  =  Textboxes are loading/filling saved data
//3  =  All Textboxes are cleared to the default string text
//4+ =  A textbox is cleared to an empty string whenever the X (Reset String) button for it is clicked
int textbox_active = 0;

//CHAPTER EDITOR USER MESSAGES - TEXTBOX STRINGS
STRING* ch_message_title = " ";
STRING* ch_message_start = " ";
STRING* ch_message_final = " ";


//PANEL FOR TEXTBOX : CHAPTER TITLE
PANEL *panTextbox_Title = {
	pos_x = 180;
	pos_y = 190;
	size_x = 558;
	size_y = 32;
	blue = 255;
	green = 255;
	red = 255;
	layer = 21;
	flags = LIGHT;
}
//DEFINE TEXTBOX CHAPTER TITLE
var ch_textbox_Title() {
	TEXTBOX_CONFIG _config;
	_config.posX = 0;
	_config.posY = 0;
	_config.sizeX = 107;
	_config.sizeY = 1;
	_config.paddingX = 8;
	_config.paddingY = 4;
	_config.borderSize = 0;
	_config.backgroundColor.red = 255;
	_config.backgroundColor.green = 255;
	_config.backgroundColor.blue = 255;
	_config.textColor.red = 1;
	_config.textColor.green = 1;
	_config.textColor.blue = 1;
	_config.selectColor.red = 0;
	_config.selectColor.green = 0;
	_config.selectColor.blue = 0;
	_config.font = font_create("Arial#22");
	_config.string = str_create("Input Title Name....");
	_config.flags = TEXTBOX_REMOVE_STRING | TEXTBOX_REMOVE_FONT;
	return pan_textbox_create (panTextbox_Title, &_config);
}


//PANEL FOR TEXTBOX A
PANEL *panTextbox_A = {
	pos_x = 180;
	pos_y = 252;
	size_x = 558;
	size_y = 145;
	blue = 255;
	green = 255;
	red = 255;
	layer = 21;
	flags = LIGHT;
}
//DEFINE TEXTBOX A
var ch_textbox_A() {
	TEXTBOX_CONFIG _config;
	_config.posX = 0;
	_config.posY = 0;
	_config.sizeX = 107;
	_config.sizeY = 6;
	_config.paddingX = 8;
	_config.paddingY = 4;
	_config.borderSize = 0;
	_config.backgroundColor.red = 255;
	_config.backgroundColor.green = 255;
	_config.backgroundColor.blue = 255;
	_config.textColor.red = 1;
	_config.textColor.green = 1;
	_config.textColor.blue = 1;
	_config.selectColor.red = 0;
	_config.selectColor.green = 0;
	_config.selectColor.blue = 0;
	_config.font = font_create("Arial#22");
	_config.string = str_create("Input Message....");
	_config.flags = TEXTBOX_REMOVE_STRING | TEXTBOX_REMOVE_FONT;
	return pan_textbox_create (panTextbox_A, &_config);
}


//PANEL FOR TEXTBOX B
PANEL *panTextbox_B = {
	pos_x = 180;
	pos_y = 435;
	size_x = 558;
	size_y = 145;
	blue = 255;
	green = 255;
	red = 255;
	layer = 21;
	flags = LIGHT;
}
//DEFINE TEXTBOX B
var ch_textbox_B() {
	TEXTBOX_CONFIG _config;
	_config.posX = 0;
	_config.posY = 0;
	_config.sizeX = 107;
	_config.sizeY = 6;
	_config.paddingX = 8;
	_config.paddingY = 4;
	_config.borderSize = 0;
	_config.backgroundColor.red = 255;
	_config.backgroundColor.green = 255;
	_config.backgroundColor.blue = 255;
	_config.textColor.red = 1;
	_config.textColor.green = 1;
	_config.textColor.blue = 1;
	_config.selectColor.red = 0;
	_config.selectColor.green = 0;
	_config.selectColor.blue = 0;
	_config.font = font_create("Arial#22");
	_config.string = str_create("Input Message....");
	_config.flags = TEXTBOX_REMOVE_STRING | TEXTBOX_REMOVE_FONT;
	return pan_textbox_create (panTextbox_B, &_config);
}


//TEXTBOX MANAGER FOR CHAPTER MENU
void ch_menu_textboxes()
{	
	//Create editor textboxes.
	textbox_active=1;//Controls what the textboxes on the chapter menu need to do
	TEXTBOX *_myTextboxHandleTitle = ch_textbox_Title(); //var _myTextboxHandleTitle = ch_textbox_Title();//Chapter Title Textbox
	TEXTBOX *_myTextboxHandle1 = ch_textbox_A();//var _myTextboxHandle1 = ch_textbox_A();//Chapter Message A Textbox
	TEXTBOX *_myTextboxHandle2 = ch_textbox_B();//var _myTextboxHandle2 = ch_textbox_B();//Chapter Message B Textbox
	
	//Chapter Menu Textbox Loop
	while(1)
	{
		if(textbox_active==1)//Active. Save written strings.
		{
			str_cpy(ch_message_title, ((TEXTBOX*)_myTextboxHandleTitle)->string);
			str_cpy(ch_message_start, ((TEXTBOX*)_myTextboxHandle1)->string);
			str_cpy(ch_message_final, ((TEXTBOX*)_myTextboxHandle2)->string);
		}
		if(textbox_active==2)//Loading Chapter File. Load saved strings.
		{
			str_cpy(((TEXTBOX*)_myTextboxHandleTitle)->string, ch_message_title);
			textboxUpdate(_myTextboxHandleTitle);
			
			str_cpy(((TEXTBOX*)_myTextboxHandle1)->string, ch_message_start);
			textboxUpdate(_myTextboxHandle1);
			
			str_cpy(((TEXTBOX*)_myTextboxHandle2)->string, ch_message_final);
			textboxUpdate(_myTextboxHandle2);
			textbox_active=1;
		}
		if(textbox_active==3)//Closing Menu. Reset the textboxes.
		{
			str_cpy(((TEXTBOX*)_myTextboxHandleTitle)->string, "Input Chapter Title....");
			textboxUpdate(_myTextboxHandleTitle);
			
			str_cpy(((TEXTBOX*)_myTextboxHandle1)->string, "Input Message....");
			textboxUpdate(_myTextboxHandle1);
			
			str_cpy(((TEXTBOX*)_myTextboxHandle2)->string, "Input Message....");
			textboxUpdate(_myTextboxHandle2);
			textbox_active=1;
		}
		if(textbox_active==4)//Resets chapter title textbox when X (Reset Text) bu is pressed
		{
			//RESET CHAPTER TITLE TEXT
			str_cpy(((TEXTBOX*)_myTextboxHandleTitle)->string, "");
			textboxUpdate(_myTextboxHandleTitle);
			textbox_active=1;
		}
		if(textbox_active==5)//Resets message A textbox when X (Reset Text) bu is pressed
		{
			//RESET CHAPTER MSG A TEXT
			str_cpy(((TEXTBOX*)_myTextboxHandle1)->string, "");
			textboxUpdate(_myTextboxHandle1);
			textbox_active=1;
		}
		if(textbox_active==6)//Resets message B textbox when X (Reset Text) bu is pressed
		{
			//RESET CHAPTER MSG B TEXT
			str_cpy(((TEXTBOX*)_myTextboxHandle2)->string, "");
			textboxUpdate(_myTextboxHandle2);
			textbox_active=1;
		}
		
		if(textbox_active==10)//Ends the textbox loop when editor is closed
		{
			break;
		}
		wait(1);
	}
}


//########################
//SECTION 2 : Content Menu
//########################

//1  =  Textboxes are created, active, and will save input
//2  =  Textboxes are loading/filling saved data
//3  =  All Textboxes are cleared to the default string text
//4+ =  A textbox is cleared to an empty string whenever the X (Reset String) button for it is clicked
int content_textbox_active = 0;


//CONTENT MANAGER CUSTOM ACTION/FUNCTION NAME - TEXTBOX STRING
STRING* cm_action_name = " ";


//PANEL FOR TEXTBOX : CONTENT MANAGER
PANEL *panTextbox_funcName = {
	pos_x = 704;
	pos_y = 215;
	size_x = 328;
	size_y = 18;
	blue = 255;
	green = 255;
	red = 255;
	layer = 17;
	flags = LIGHT;
}
//DEFINE TEXTBOX FOR CONTENT MANAGER
var cm_funcName_txtbox() {
	TEXTBOX_CONFIG _config;
	_config.posX = 0;
	_config.posY = 0;
	_config.sizeX = 107;
	_config.sizeY = 1;
	_config.paddingX = 0;
	_config.paddingY = 0;
	_config.borderSize = 0;
	_config.backgroundColor.red = 255;
	_config.backgroundColor.green = 255;
	_config.backgroundColor.blue = 255;
	_config.textColor.red = 1;
	_config.textColor.green = 1;
	_config.textColor.blue = 1;
	_config.selectColor.red = 0;
	_config.selectColor.green = 0;
	_config.selectColor.blue = 0;
	_config.font = font_create("Arial#14b");
	_config.string = str_create("");
	_config.flags = TEXTBOX_REMOVE_STRING | TEXTBOX_REMOVE_FONT;
	return pan_textbox_create (panTextbox_funcName, &_config);
}


//TEXTBOX MANAGER FOR CONTENT MENU
void content_menu_textboxes()
{	
	//Create editor textboxes.
	content_textbox_active=1;//Controls what the textboxes on the chapter menu need to do
	TEXTBOX *_cm_set_textbox_funcname = cm_funcName_txtbox();
	
	//Content Menu Textbox Loop
	while(1)
	{
		if(content_textbox_active==1)//Active. Save written strings.
		{
			str_cpy(cm_action_name, ((TEXTBOX*)_cm_set_textbox_funcname)->string);
		}
		if(content_textbox_active==2)//Loading Content File. Load saved strings.
		{
			str_cpy(((TEXTBOX*)_cm_set_textbox_funcname)->string, cm_action_name);
			textboxUpdate(_cm_set_textbox_funcname);
			content_textbox_active=1;
		}
		if(content_textbox_active==3)//Closing Menu. Reset the textboxes.
		{
			str_cpy(((TEXTBOX*)_cm_set_textbox_funcname)->string, "EMPTY");
			textboxUpdate(_cm_set_textbox_funcname);
			content_textbox_active=1;
		}
		if(content_textbox_active==4)//Resets Content menu textbox when X (Reset Text) bu is pressed
		{
			//RESET CONTENT TEXT
			str_cpy(((TEXTBOX*)_cm_set_textbox_funcname)->string, "");
			textboxUpdate(_cm_set_textbox_funcname);
			content_textbox_active=1;
		}
		
		if(content_textbox_active==10)//Ends the textbox loop when editor is closed
		{
			break;
		}
		wait(1);
	}
}