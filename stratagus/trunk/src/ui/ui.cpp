//   ___________		     _________		      _____  __
//   \_	  _____/______   ____   ____ \_   ___ \____________ _/ ____\/  |_
//    |    __) \_  __ \_/ __ \_/ __ \/    \  \/\_  __ \__  \\   __\\   __\ 
//    |     \   |  | \/\  ___/\  ___/\     \____|  | \// __ \|  |   |  |
//    \___  /   |__|    \___  >\___  >\______  /|__|  (____  /__|   |__|
//	  \/		    \/	   \/	     \/		   \/
//  ______________________                           ______________________
//			  T H E   W A R   B E G I N S
//	   FreeCraft - A free fantasy real time strategy game engine
//
/**@name ui.c		-	The user interface globals. */
//
//	(c) Copyright 1999-2001 by Lutz Sammer and Andreas Arens
//
//	FreeCraft is free software; you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published
//	by the Free Software Foundation; either version 2 of the License,
//	or (at your option) any later version.
//
//	FreeCraft is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//	GNU General Public License for more details.
//
//	$Id$

//@{

/*----------------------------------------------------------------------------
--	Includes
----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "freecraft.h"
#include "interface.h"
#include "map.h"
#include "ui.h"

/*----------------------------------------------------------------------------
--	Variables
----------------------------------------------------------------------------*/

global char RightButtonAttacks;		/// right button 0 move, 1 attack
global char FancyBuildings;		/// Mirror buildings 1 yes, 0 now.

/**
**	The user interface configuration
*/
global UI TheUI = {
    "default", 640, 480,		// interface selector
    100, 0, 100,			// contrast, brightness, saturation

    1,					// mouse scrolling
    0,					// reverse mouse
    -1,					// warp x
    -1,					// warp y
    MOUSEADJUST,			// mouse speed
    MOUSESCALE,				// mouse scale
};

#ifndef USE_CCL

/**
**	User interface 1.
*/
local UI UI1 = {
#define MAP_X	176
#define MAP_Y	16
#define MAP_W	14
#define MAP_H	14
#define TOP_X	0
#define TOP_Y	24+136
#define BOT_X	0
#define BOT_Y	24+136+176

    "human", 640, 480,			// interface selector

    100, 0, 100,			// contrast, brightness, saturation
    1,					// mouse scrolling
    0,					// reverse mouse
    -1,					// warp x
    -1,					// warp y
    MOUSEADJUST,			// mouse speed
    MOUSESCALE,				// mouse scale

    //	Filler 1
    { "graphic/Map border (Right,Humans).png" },
    MAP_X+MAP_W*TileSizeX,	0,

    //	Resource line
    { "graphic/Map border (Top,Humans).png" },
    MAP_X, 0,

    //	Flag original resources
    0,

    // resources
    {
	// time resource
	{ },
	// gold resource
	{ { "graphic/gold,wood,oil,mana.png" }, 0,
	MAP_X+ 20, 0, 14, 14,
	MAP_X+ 40, 1, },
	// wood resource
	{ { "graphic/gold,wood,oil,mana.png" }, 1,
	MAP_X+100, 0, 14, 14,
	MAP_X+120, 1, },
	//  oil resource
	{ { "graphic/gold,wood,oil,mana.png" }, 2,
	MAP_X+180, 0, 14, 14,
	MAP_X+200, 1, },
    },

    //	food resource
    { "graphic/food.png" }, 0,
    MAP_X+260, 0, 14, 14,
    MAP_X+280, 1,
    //	score resource
    { "graphic/score.png" }, 0,
    MAP_X+340, 0, 14, 14,
    MAP_X+360, 1,

    //	Info panel
    { "graphic/human panel.png" },
    TOP_X, TOP_Y, 176, 176,

    //	Completed bar
    ColorDarkGreen, TOP_X+12, TOP_Y+8+145, TOP_X+50, TOP_Y+8+145,

    //	Command button panel
    { "graphic/Panel (Bottom,Humans).png" },
    BOT_X, BOT_Y,

    //	The big map
    MAP_X, MAP_Y, MAP_X+MAP_W*TileSizeX, MAP_Y+MAP_H*TileSizeY,

    //	Menu button
    { "graphic/Minimap border (Top,Humans).png" },
    0, 0,

    //	Minimap
    { "graphic/Minimap (Humans).png" },
    0, 24,

    //	Status line
    { "graphic/Map border (Bottom,Humans).png" },
    MAP_X, 480-16,

    //
    //	Defines position and size of the different buttons.
    //
    {
    //	Menu button
	{  24,  2,128,17 },
    //	9 Character portraits
	{   6+TOP_X,TOP_Y+6, 46,38 },
	{  62+TOP_X,TOP_Y+6, 46,38 },
	{ 118+TOP_X,TOP_Y+6, 46,38 },
	{   6+TOP_X,TOP_Y+58, 46,38 },
	{  62+TOP_X,TOP_Y+58, 46,38 },
	{ 118+TOP_X,TOP_Y+58, 46,38 },
	{   6+TOP_X,TOP_Y+110, 46,38 },
	{  62+TOP_X,TOP_Y+110, 46,38 },
	{ 118+TOP_X,TOP_Y+110, 46,38 },
    //	9 Buttons interface
	{   6+BOT_X,BOT_Y+1, 46,38 },
	{  62+BOT_X,BOT_Y+1, 46,38 },
	{ 118+BOT_X,BOT_Y+1, 46,38 },
	{   6+BOT_X,BOT_Y+48, 46,38 },
	{  62+BOT_X,BOT_Y+48, 46,38 },
	{ 118+BOT_X,BOT_Y+48, 46,38 },
	{   6+BOT_X,BOT_Y+95, 46,38 },
	{  62+BOT_X,BOT_Y+95, 46,38 },
	{ 118+BOT_X,BOT_Y+95, 46,38 },
    },

    //
    //	Defines position and size of the training queue buttons.
    //
    {
	{   6+TOP_X,TOP_Y+ 56, 46,38 },
	{  62+TOP_X,TOP_Y+ 56, 46,38 },
	{ 118+TOP_X,TOP_Y+ 56, 46,38 },
	{   6+TOP_X,TOP_Y+103, 46,38 },
	{  62+TOP_X,TOP_Y+103, 46,38 },
	{ 118+TOP_X,TOP_Y+103, 46,38 }
    },

    //
    //	Define the cursors.
    //
    { "cursor-point"	},
    { "cursor-glass"	},
    { "cursor-cross"	},
    { "cursor-yellow-hair"	},
    { "cursor-green-hair"	},
    { "cursor-red-hair"	},
    { "cursor-scroll"	},
    { "cursor-arrow-e"	},
    { "cursor-arrow-ne"	},
    { "cursor-arrow-n"	},
    { "cursor-arrow-nw"	},
    { "cursor-arrow-w"	},
    { "cursor-arrow-s"	},
    { "cursor-arrow-sw"	},
    { "cursor-arrow-se"	},
};

// ----------------------------------------------------------------------------

/**
**	User interface 2.
*/
local UI UI2 = {
    "orc", 640, 480,			// interface selector

    100, 0, 100,			// contrast, brightness, saturation
    1,					// mouse scrolling
    0,					// reverse mouse
    -1,					// warp x
    -1,					// warp y
    MOUSEADJUST,			// mouse speed
    MOUSESCALE,				// mouse scale

    //	Filler 1
    { "graphic/Map border (Right,Orcs).png" },
    MAP_X+MAP_W*TileSizeX,	0,

    //	Resource line
    { "graphic/Map border (Top,Orcs).png" },
    MAP_X, 0,

    //	Flag original resources
    0,

    // resources
    {
	// time resource
	{ },
	// gold resource
	{ { "graphic/gold,wood,oil,mana.png" }, 0,
	MAP_X+ 20, 0, 14, 14,
	MAP_X+ 40, 1, },
	// wood resource
	{ { "graphic/gold,wood,oil,mana.png" }, 1,
	MAP_X+100, 0, 14, 14,
	MAP_X+120, 1, },
	//  oil resource
	{ { "graphic/gold,wood,oil,mana.png" }, 2,
	MAP_X+180, 0, 14, 14,
	MAP_X+200, 1, },
    },

    // food resource
    { "graphic/food.png" }, 0,
    MAP_X+260, 0, 14, 14,
    MAP_X+280, 1,
    // score resource
    { "graphic/score.png" }, 0,
    MAP_X+340, 0, 14, 14,
    MAP_X+360, 1,

    // Info panel
    { "graphic/orcish panel.png" },
    TOP_X, TOP_Y, 176, 176,

    // Completed bar
    ColorDarkGreen, TOP_X+12, TOP_Y+8+145, TOP_X+50, TOP_Y+8+145,

    // Command button panel
    { "graphic/Panel (Bottom,Orcs).png" },
    BOT_X, BOT_Y,

    // The big map
    MAP_X, MAP_Y, MAP_X+MAP_W*TileSizeX, MAP_Y+MAP_H*TileSizeY,

    // Menu button
    { "graphic/Minimap border (Top,Orcs).png" },
    0, 0,

    // Minimap
    { "graphic/Minimap (Orcs).png" },
    0, 24,

    // Status line
    { "graphic/Map border (Bottom,Orcs).png" },
    MAP_X, 480-16,

    //
    //	Defines position and size of the different buttons.
    //
    {
    // Menu button
	{  24,  2,128,17 },
    // 9 Character portraits
	{   6+TOP_X,TOP_Y+6, 46,38 },
	{  62+TOP_X,TOP_Y+6, 46,38 },
	{ 118+TOP_X,TOP_Y+6, 46,38 },
	{   6+TOP_X,TOP_Y+58, 46,38 },
	{  62+TOP_X,TOP_Y+58, 46,38 },
	{ 118+TOP_X,TOP_Y+58, 46,38 },
	{   6+TOP_X,TOP_Y+110, 46,38 },
	{  62+TOP_X,TOP_Y+110, 46,38 },
	{ 118+TOP_X,TOP_Y+110, 46,38 },
    // 9 Buttons interface
	{   6+BOT_X,BOT_Y+1, 46,38 },
	{  62+BOT_X,BOT_Y+1, 46,38 },
	{ 118+BOT_X,BOT_Y+1, 46,38 },
	{   6+BOT_X,BOT_Y+48, 46,38 },
	{  62+BOT_X,BOT_Y+48, 46,38 },
	{ 118+BOT_X,BOT_Y+48, 46,38 },
	{   6+BOT_X,BOT_Y+95, 46,38 },
	{  62+BOT_X,BOT_Y+95, 46,38 },
	{ 118+BOT_X,BOT_Y+95, 46,38 },
    },

    //
    //	Defines position and size of the training queue buttons.
    //
    {
	{   6+TOP_X,TOP_Y+ 56, 46,38 },
	{  62+TOP_X,TOP_Y+ 56, 46,38 },
	{ 118+TOP_X,TOP_Y+ 56, 46,38 },
	{   6+TOP_X,TOP_Y+103, 46,38 },
	{  62+TOP_X,TOP_Y+103, 46,38 },
	{ 118+TOP_X,TOP_Y+103, 46,38 }
    },
    //
    //	Define the cursors.
    //
    { "cursor-point"	},
    { "cursor-glass"	},
    { "cursor-cross"	},
    { "cursor-yellow-hair"	},
    { "cursor-green-hair"	},
    { "cursor-red-hair"	},
    { "cursor-scroll"	},
    { "cursor-arrow-e"	},
    { "cursor-arrow-ne"	},
    { "cursor-arrow-n"	},
    { "cursor-arrow-nw"	},
    { "cursor-arrow-w"	},
    { "cursor-arrow-s"	},
    { "cursor-arrow-sw"	},
    { "cursor-arrow-se"	},
};

#endif

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

#ifndef USE_CCL

/**
**	The default user interfaces.
*/
local UI* DefaultUIn[] = { &UI1, &UI2, NULL };

#endif

/**
**	The available user interfaces.
*/
global UI** UI_Table
#ifndef USE_CCL
     = DefaultUIn
#endif
    ;

/**
**	Initialize the user interface.
*/
global void InitUserInterface(void)
{
    int i;
    int best;

    // select the correct slot
    best=0;
    for( i=0; UI_Table[i]; ++i ) {
	if( !strcmp(ThisPlayer->RaceName,UI_Table[i]->Name) ) {
	    // perfect
	    if( VideoWidth==UI_Table[i]->Width
		    && VideoHeight==UI_Table[i]->Height  ) {
		best=i;
		break;
	    }
	    // too big
	    if( VideoWidth<UI_Table[i]->Width
		    || VideoHeight<UI_Table[i]->Height  ) {
		continue;
	    }
	    // best smaller
	    if( UI_Table[i]->Width*UI_Table[i]->Height>=
		    UI_Table[best]->Width*UI_Table[best]->Height  ) {
		best=i;
	    }
	}
    }

    // FIXME: overwrites already set slots?
    TheUI=*UI_Table[best];

    //
    //	Calculations
    //
    MapWidth=(TheUI.MapEndX-TheUI.MapX+TileSizeX)/TileSizeX;
    MapHeight=(TheUI.MapEndY-TheUI.MapY+TileSizeY)/TileSizeY;
}

/**
**	Load the user interface graphics.
*/
global void LoadUserInterface(void)
{
    int i;

    //
    //	Load graphics
    //
    if( TheUI.Filler1.File ) {
	TheUI.Filler1.Graphic=LoadGraphic(TheUI.Filler1.File);
    }
    if( TheUI.Resource.File ) {
	TheUI.Resource.Graphic=LoadGraphic(TheUI.Resource.File);
    }

    for( i=0; i<MaxCosts; ++i ) {
	// FIXME: reuse same graphics?
	if( TheUI.Resources[i].Icon.File ) {
	    TheUI.Resources[i].Icon.Graphic
		    =LoadGraphic(TheUI.Resources[i].Icon.File);
	}
    }

    // FIXME: reuse same graphics?
    if( TheUI.FoodIcon.File ) {
	TheUI.FoodIcon.Graphic=LoadGraphic(TheUI.FoodIcon.File);
    }
    // FIXME: reuse same graphics?
    if( TheUI.ScoreIcon.File ) {
	TheUI.ScoreIcon.Graphic=LoadGraphic(TheUI.ScoreIcon.File);
    }

    if( TheUI.InfoPanel.File ) {
	TheUI.InfoPanel.Graphic=LoadGraphic(TheUI.InfoPanel.File);
    }
    if( TheUI.ButtonPanel.File ) {
	TheUI.ButtonPanel.Graphic=LoadGraphic(TheUI.ButtonPanel.File);
    }
    if( TheUI.MenuButton.File ) {
	TheUI.MenuButton.Graphic=LoadGraphic(TheUI.MenuButton.File);
    }
    if( TheUI.Minimap.File ) {
	TheUI.Minimap.Graphic=LoadGraphic(TheUI.Minimap.File);
    }
    if( TheUI.StatusLine.File ) {
	TheUI.StatusLine.Graphic=LoadGraphic(TheUI.StatusLine.File);
    }

    //
    //	Resolve cursors
    //
    TheUI.Point.Cursor=CursorTypeByIdent(TheUI.Point.Name);
    TheUI.Glass.Cursor=CursorTypeByIdent(TheUI.Glass.Name);
    TheUI.Cross.Cursor=CursorTypeByIdent(TheUI.Cross.Name);
    TheUI.YellowHair.Cursor=CursorTypeByIdent(TheUI.YellowHair.Name);
    TheUI.GreenHair.Cursor=CursorTypeByIdent(TheUI.GreenHair.Name);
    TheUI.RedHair.Cursor=CursorTypeByIdent(TheUI.RedHair.Name);
    TheUI.Scroll.Cursor=CursorTypeByIdent(TheUI.Scroll.Name);

    TheUI.ArrowE.Cursor=CursorTypeByIdent(TheUI.ArrowE.Name);
    TheUI.ArrowNE.Cursor=CursorTypeByIdent(TheUI.ArrowNE.Name);
    TheUI.ArrowN.Cursor=CursorTypeByIdent(TheUI.ArrowN.Name);
    TheUI.ArrowNW.Cursor=CursorTypeByIdent(TheUI.ArrowNW.Name);
    TheUI.ArrowW.Cursor=CursorTypeByIdent(TheUI.ArrowW.Name);
    TheUI.ArrowSW.Cursor=CursorTypeByIdent(TheUI.ArrowSW.Name);
    TheUI.ArrowS.Cursor=CursorTypeByIdent(TheUI.ArrowS.Name);
    TheUI.ArrowSE.Cursor=CursorTypeByIdent(TheUI.ArrowSE.Name);

    if( TheUI.GameMenuePanel.File ) {
	TheUI.GameMenuePanel.Graphic=LoadGraphic(TheUI.GameMenuePanel.File);
    }
    if( TheUI.Menue1Panel.File ) {
	TheUI.Menue1Panel.Graphic=LoadGraphic(TheUI.Menue1Panel.File);
    }
    if( TheUI.Menue2Panel.File ) {
	TheUI.Menue2Panel.Graphic=LoadGraphic(TheUI.Menue2Panel.File);
    }
    if( TheUI.VictoryPanel.File ) {
	TheUI.VictoryPanel.Graphic=LoadGraphic(TheUI.VictoryPanel.File);
    }
    if( TheUI.ScenarioPanel.File ) {
	TheUI.ScenarioPanel.Graphic=LoadGraphic(TheUI.ScenarioPanel.File);
    }
}

/**
**	Clean up the user interface module.
*/
global void CleanUserInterface(void)
{
    int i;

    //
    //	Free the graphics. FIXME: if shared this crashs.
    //
    VideoSaveFree(TheUI.Filler1.Graphic);
    VideoSaveFree(TheUI.Resource.Graphic);

    for( i=0; i<MaxCosts; ++i ) {
	VideoSaveFree(TheUI.Resources[i].Icon.Graphic);
    }

    VideoSaveFree(TheUI.FoodIcon.Graphic);
    VideoSaveFree(TheUI.ScoreIcon.Graphic);
    VideoSaveFree(TheUI.InfoPanel.Graphic);
    VideoSaveFree(TheUI.ButtonPanel.Graphic);
    VideoSaveFree(TheUI.MenuButton.Graphic);
    VideoSaveFree(TheUI.Minimap.Graphic);
    VideoSaveFree(TheUI.StatusLine.Graphic);

    VideoSaveFree(TheUI.GameMenuePanel.Graphic);
    VideoSaveFree(TheUI.Menue1Panel.Graphic);
    VideoSaveFree(TheUI.Menue2Panel.Graphic);
    VideoSaveFree(TheUI.VictoryPanel.Graphic);
    VideoSaveFree(TheUI.ScenarioPanel.Graphic);

    memset(&TheUI,0,sizeof(TheUI));


    DebugLevel0Fn("FIXME: not complete written\n");
}

//@}
