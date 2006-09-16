//       _________ __                 __
//      /   _____//  |_____________ _/  |______     ____  __ __  ______
//      \_____  \\   __\_  __ \__  \\   __\__  \   / ___\|  |  \/  ___/
//      /        \|  |  |  | \// __ \|  |  / __ \_/ /_/  >  |  /\___ |
//     /_______  /|__|  |__|  (____  /__| (____  /\___  /|____//____  >
//             \/                  \/          \//_____/            \/
//  ______________________                           ______________________
//                        T H E   W A R   B E G I N S
//         Stratagus - A free fantasy real time strategy game engine
//
/**@name menus.cpp - The menu function code. */
//
//      (c) Copyright 1999-2006 by Andreas Arens, Jimmy Salmon, Nehal Mistry
//
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; only version 2 of the License.
//
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
//      02111-1307, USA.
//
//      $Id$

//@{

/*----------------------------------------------------------------------------
--  Includes
----------------------------------------------------------------------------*/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

#include "stratagus.h"

#include "SDL.h"

#include "iocompat.h"

#include "unittype.h"
#include "video.h"
#include "player.h"
#include "font.h"
#include "tileset.h"
#include "map.h"
#include "minimap.h"
#include "interface.h"
#include "menus.h"
#include "cursor.h"
#include "iolib.h"
#include "network.h"
#include "netconnect.h"
#include "settings.h"
#include "ui.h"
#include "campaign.h"
#include "sound_server.h"
#include "sound.h"
#include "script.h"
#include "editor.h"
#include "commands.h"
#include "actions.h"
#include "net_lowlevel.h"
#include "master.h"
#include "construct.h"


/*----------------------------------------------------------------------------
-- Prototypes for local functions
----------------------------------------------------------------------------*/

#if 0
static void EditorEndMenu(void);
#endif

/*----------------------------------------------------------------------------
-- Prototypes for action handlers and helper functions
----------------------------------------------------------------------------*/

// Victory, lost
#if 0
static void GameMenuEnd(void);
static void SaveReplayOk(void);
#endif

// Scenario select
#if 0
static void ScenSelectTPMSAction(Menuitem *mi, int i);
#endif

// Program start
#if 0
static void MultiPlayerGameMenu(void);
#endif

// Custom game setup
#if 0
static void GameSetupInit(Menu *menu);
static void ScenSelectMenu(void);
static void CustomGameStart(void);
static void GameCancel(void);
static void GameRCSAction(Menuitem *mi, int i);
static void GameRESAction(Menuitem *mi, int i);
static void GameUNSAction(Menuitem *mi, int i);
static void GameTSSAction(Menuitem *mi, int i);
static void GameGATAction(Menuitem *mi, int i);
static void CustomGameOPSAction(Menuitem *mi, int i);
#endif

// Net create join
#if 0
static void JoinNetGameMenu(void);
static void CreateNetGameMenu(void);
static void CreateInternetGameMenu(void);

// Multi net type
static void MultiPlayerLANGame(void);
static void MultiPlayerInternetGame(void);
#endif

// Net multi setup
#if 0
static void MultiGameSetupInit(Menu *menu);
static void MultiGameSetupExit(Menu *menu);
static void MultiScenSelectMenu(void);
static void MultiGameStart(void);
static void MultiGameCancel(void);
static void MultiGameFWSAction(Menuitem *mi, int i);
#endif

// Net multi client
#if 0
static void TerminateNetConnect(void);
static void MultiGameClientInit(Menu *menu);
static void MultiGameClientExit(Menu *menu);
static void MultiGameClientDrawFunc(Menuitem *mi);
static void MultiClientReady(void);
static void MultiClientNotReady(void);
static void MultiClientCancel(void);
static void MultiClientRCSAction(Menuitem *mi, int i);
static void MultiClientCheckboxAction(Menuitem *mi);
static void MultiClientUpdate(int initial);
#endif

// Net connecting
#if 0
static void NetConnectingInit(Menu *menu);
static void NetConnectingExit(Menu *menu);
static void NetConnectingCancel(void);
#endif

// Confirm delete
#if 0
static void DeleteConfirmOk(void);
#endif

// Editor select
#if 0
static void EditorNewMap(void);
static void EditorMainLoadMap(void);
static void EditorSelectCancel(void);
#endif

// Editor new
#if 0
static void EditorNewDrawFunc(Menuitem *mi);
static void EditorNewMapDescriptionEnterAction(Menuitem *mi, int key);
static void EditorNewMapSizeEnterAction(Menuitem *mi, int key);
static void EditorNewOk(void);
static void EditorNewCancel(void);
#endif

// Editor main load map
#if 0
static void EditorMainLoadInit(Menu *menu);
static void EditorMainLoadExit(Menu *menu);
static void EditorMainLoadVSAction(Menuitem *mi);
static void EditorMainLoadOk(void);
static void EditorMainLoadCancel(void);
static int EditorMainLoadRDFilter(char *pathbuf, FileList *fl);
#endif

// Editor load map
#if 0
static void EditorLoadOk(void);
static void EditorLoadCancel(void);
#endif

// Editor menu
#if 0
static void EditorMapPropertiesMenu(void);
static void EditorPlayerPropertiesMenu(void);
static void EditorQuitToMenu(void);
#endif

// Editor map properties
#if 0
static void EditorMapPropertiesEnterAction(Menuitem *mi, int key);
static void EditorMapPropertiesOk(void);
#endif

// Editor player properties
#if 0
static void EditorPlayerPropertiesDrawFunc(Menuitem *mi);
static void EditorPlayerPropertiesEnterAction(Menuitem *mi, int key);
#endif

// Editor edit resource
#if 0
static void EditorEditResourceEnterAction(Menuitem *mi,int key);
static void EditorEditResourceOk(void);
static void EditorEditResourceCancel(void);
#endif

// Editor edit ai properties
#if 0
static void EditorEditAiPropertiesCheckbox(Menuitem *mi);
static void EditorEditAiPropertiesOk(void);
static void EditorEditAiPropertiesCancel(void);
#endif

// Editor save
#if 0
static void EditorSaveInit(Menu *menu);
static void EditorSaveExit(Menu *menu);
static void EditorSaveVSAction(Menuitem *mi);
static void EditorSaveEnterAction(Menuitem *mi, int key);
static void EditorSaveOk(void);
static void EditorSaveCancel(void);
static int EditorSaveRDFilter(char *pathbuf, FileList *fl);
#endif

// Editor save confirm
#if 0
static void EditorSaveConfirmInit(Menu *menu);
static void EditorSaveConfirmOk(void);
static void EditorSaveConfirmCancel(void);
#endif

// Metaserver
//static void MultiGameMasterReport(void);
//static void EnterMasterAction(Menuitem *mi, int key);
#if 0
static void ShowMetaServerList(void); // Addition for Magnant
static void MultiMetaServerGameSetupInit(Menu *menu); // init callback
static void MultiMetaServerGameSetupExit(Menu *menu); // exit callback
static void SelectGameServer(Menuitem *mi); // Game Server selection so that client joins the game
static void AddGameServer(void); //Add Game Server on Meta server
static int MetaServerConnectError(void); // Display error message
static void MultiMetaServerClose(void); //Close Master Server connection
#endif
static void ChangeGameServer(void); //Change Game Parameters on Meta server

//others
#if 0
static void GameMenuReturn(void);
static void NetErrorMenu(char *error);
#endif
void NetworkGamePrepareGameSettings(void);

#if 0
static void MultiGamePTSAction(Menuitem *mi, int o);
static void NetMultiPlayerDrawFunc(Menuitem *mi);
static void MultiGamePlayerSelectorsUpdate(int initial);
#endif

/*----------------------------------------------------------------------------
-- Variables
----------------------------------------------------------------------------*/

	/// Hash table of all the menus
std::map<std::string, Menu *> MenuMap;

	/// Editor cancel button pressed
static int EditorCancelled;


/**
** Other client and server selection state for Multiplayer clients
*/
ServerSetup ServerSetupState;
ServerSetup LocalSetupState;

static char ScenSelectPath[1024];        /// Scenario selector path
static char ScenSelectDisplayPath[1024]; /// Displayed selector path
static char ScenSelectFileName[128];     /// Scenario selector name
#if 0
static char ScenSelectPathName[128];     /// Path name.

static char SelectedFileExist;           /// True if ScenSelectFileName is an existing file.
#endif

char MenuMapFullPath[1024];              /// Selected map path+name

#if 0
static char *SaveDir;                    /// Save game directory
static char TempPathBuf[PATH_MAX];       /// Temporary buffer for paths
#endif

/// FIXME: -> ccl...
static char *mgptsoptions[] = {
	"Available",
	"Computer",
	"Closed",
};

/*----------------------------------------------------------------------------
-- Functions
----------------------------------------------------------------------------*/

////////////////////
// Map info stuff //
////////////////////

#if 0
/**
**  Allocate and deep copy a MapInfo structure
**
**  @param orig  source of the copy.
**
**  @return copy of orig.
*/
static CMapInfo *DuplicateMapInfo(const CMapInfo *orig)
{
	CMapInfo *dest;

	Assert(orig);

	dest = new CMapInfo;
	memcpy(dest, orig, sizeof(CMapInfo));
	if (orig->Description) {
		dest->Description = new_strdup(orig->Description);
	}
	if (orig->Filename) {
		dest->Filename = new_strdup(orig->Filename);
	}

	return dest;
}
#endif

#if 0
/**
**  Free map info data
**
**  @param fl  File list to free.
**  @param n   Size of file list.
*/
static void FreeMapInfos(std::vector<FileList> *fl, int n)
{
	int i;

	Assert(fl);
	Assert(0 <= n);

	for (i = 0; i < n; i++) {
		if ((*fl)[i].xdata) {
			FreeMapInfo((*fl)[i].xdata);
			delete (*fl)[i].xdata;
			(*fl)[i].xdata = NULL;
		}
		delete[] (*fl)[i].name;
		(*fl)[i].name = NULL;
	}
}
#endif

////////////////
// LBRetrieve //
////////////////

#if 0
/**
**  Listbox retrieve callback.
**
**  @param mi    Listbox.
**  @param i     Line to retrieve.
**
**  @return string to display in listbox.
*/
static char *LBRetrieve(const Menuitem *mi, int i)
{
	std::vector<FileList> *fl;
	static char buffer[1024];

	Assert(mi->MiType == MiTypeListbox);
	Assert(i >= 0);

	if (i >= mi->D.Listbox.noptions) {
		return NULL;
	}
	fl = (std::vector<FileList> *)mi->D.Listbox.options;
	if ((*fl)[i].type) {
		strcpy(buffer, "   ");
	} else {
		strcpy(buffer, "D  ");
	}

	strcat(buffer, (*fl)[i].name);
	return buffer;
}
#endif

#if 0
/**
**  Listbox retrieve callback and draw some info.
**
**  @param mi    Listbox.
**  @param i     Line to retrieve.
**
**  @return string to display in listbox.
*/
static char *LBRetrieveAndInfo(const Menuitem *mi, int i)
{
	std::vector<FileList> *fl;
	CMapInfo *info;

	Assert(mi->MiType == MiTypeListbox);
	Assert(i >= 0);

	if (i >= mi->D.Listbox.noptions) {
		return NULL;
	}
	fl = (std::vector<FileList> *)mi->D.Listbox.options;
	info = (*fl)[i].xdata;
	if ((*fl)[i].type && i == mi->D.Listbox.curopt && info) {
		static char buffer[1024];
		int j;
		int n;

		// Draw optional description.
		if (info->Description) {
			VideoDrawText(mi->Menu->X + 8, mi->Menu->Y + 254, LargeFont, info->Description);
		}
		// Draw map size.
		sprintf(buffer, "%d x %d", info->MapWidth, info->MapHeight);
		VideoDrawText(mi->Menu->X + 8, mi->Menu->Y + 254 + 20, LargeFont, buffer);

		// Draw number of players.
		for (n = j = 0; j < PlayerMax; j++) {
			if (info->PlayerType[j] == PlayerPerson) {
				n++;
			}
		}
		if (n == 1) {
			VideoDrawText(mi->Menu->X + 8, mi->Menu->Y + 254 + 40, LargeFont, "1 player");
		} else {
			sprintf(buffer, "%d players", n);
			VideoDrawText(mi->Menu->X + 8, mi->Menu->Y + 254 + 40, LargeFont, buffer);
		}
	}
	return LBRetrieve(mi, i);
}
#endif

////////////////
//  LBAction  //
////////////////

#if 0
/**
**  Update path and file name with the listbox.
**
**  @param mi    listbox.
**  @param i     line in the listbox.
**
**  @return 0 if nothing selected, 1 for file, 2 for directory.
*/
static int PathLBAction(const Menuitem *mi, int i)
{
	std::vector<FileList> *fl;

	Assert(mi->MiType == MiTypeListbox);
	Assert(i >= 0);

	ScenSelectFileName[0] = '\0';
	ScenSelectPathName[0] = '\0';
	SelectedFileExist = 0;
	if (i >= mi->D.Listbox.noptions) {
		return 0;
	}
	fl = (std::vector<FileList> *)mi->D.Listbox.options;
	if ((*fl)[i].type) {
		Assert(strlen((*fl)[i].name) < sizeof(ScenSelectFileName));
		strcpy(ScenSelectFileName, (*fl)[i].name);
		SelectedFileExist = 1;
		return 1;
	} else {
		Assert(strlen((*fl)[i].name) < sizeof(ScenSelectPathName));
		strcpy(ScenSelectPathName, (*fl)[i].name);
		return 2;
	}
}
#endif

#if 0
/**
**  Editor save listbox action callback
*/
static void EditorSaveLBAction(Menuitem *mi, int i)
{
	Assert(mi->MiType == MiTypeListbox);
	Assert(i >= 0);

	PathLBAction(mi, i);
	sprintf(mi->Menu->Items[3].D.Input.buffer, "%s~!_", ScenSelectFileName);
	mi->Menu->Items[3].D.Input.nch = strlen(ScenSelectFileName);
}
#endif

//////////////
//  LBInit  //
//////////////

#if 0
/**
**  Listbox exit callback.
**
**  @param mi  Listbox to free.
*/
static void LBExit(Menuitem *mi)
{
	std::vector<FileList> *fl;

	Assert(mi->MiType == MiTypeListbox);

	if (!mi->D.Listbox.noptions) {
		return ;
	}
	fl = (std::vector<FileList> *)mi->D.Listbox.options;
	FreeMapInfos(fl, mi->D.Listbox.noptions);
	delete fl;
	mi->D.Listbox.options = NULL;
	mi->D.Listbox.noptions = 0;
	mi[1].Flags |= MI_FLAGS_DISABLED;
}
#endif

#if 0
/**
**  Listbox init callback.
**
**  @param mi      Listbox to free.
**  @param path    Path
**  @param filter  Filter
*/
static void LBInit(Menuitem *mi, const char *path, int (*filter)(char *, FileList *))
{
	int noptions;

	Assert(mi->MiType == MiTypeListbox);
	Assert(path);

	LBExit(mi);

	mi->D.Listbox.options = (void *)new std::vector<FileList>;
	mi->D.Listbox.noptions = ReadDataDirectory(path, filter,
		*(std::vector<FileList> *)mi->D.Listbox.options);

	noptions = mi->D.Listbox.noptions;
	mi->D.Listbox.startline = 0;
	if (mi->D.Listbox.noptions > 0) {
		mi->D.Listbox.curopt = 0;
		mi->D.Listbox.cursel = 0;
	} else {
		mi->D.Listbox.curopt = -1;
		mi->D.Listbox.cursel = -1;
	}
	mi[1].D.VSlider.percent = 0;
	mi[1].D.HSlider.percent = 0;
	PathLBAction(mi, 0);
	if (noptions > mi->D.Listbox.nlines) {
		mi[1].Flags &= ~MI_FLAGS_DISABLED;
	} else {
		mi[1].Flags |= MI_FLAGS_DISABLED;
	}
}
#endif

#if 0
/**
** Editor main load listbox init callback
*/
static void EditorMainLoadLBInit(Menuitem *mi)
{
	LBInit(mi, ScenSelectPath, EditorMainLoadRDFilter);
}
#endif

#if 0
/**
** Editor save listbox init callback
*/
static void EditorSaveLBInit(Menuitem *mi)
{
	LBInit(mi, ScenSelectPath, EditorSaveRDFilter);
	sprintf(mi->Menu->Items[3].D.Input.buffer, "%s~!_", ScenSelectFileName);
	mi->Menu->Items[3].D.Input.nch = strlen(ScenSelectFileName);
}
#endif

/////////////////////
// Folder.         //
/////////////////////

#if 0
/**
**  Go to parent folder.
**
**  @return 1 if path have changed.
*/
static int ParentFolder()
{
	char *cp;

	if (!ScenSelectDisplayPath[0]) {
		return 0;
	}
	cp = strrchr(ScenSelectDisplayPath, '/');
	if (cp) {
		*cp = '\0';
	} else {
		ScenSelectDisplayPath[0] = '\0';
	}
	cp = strrchr(ScenSelectPath, '/');
	Assert(cp);
	*cp = 0;
	SelectedFileExist = 0;
	ScenSelectPathName[0] = '\0';
	ScenSelectFileName[0] = '\0';
	return 1;
}
#endif

#if 0
/**
** Scenario select folder button
*/
static void ScenSelectFolder(void)
{
	if (ParentFolder()) {
		ScenSelectLBInit(CurrentMenu->Items + 1);
	}
}
#endif

#if 0
/**
** Editor main load folder button
*/
static void EditorMainLoadFolder(void)
{
	if (ParentFolder()) {
		EditorMainLoadLBInit(CurrentMenu->Items + 1);
	}
}
#endif

#if 0
/**
** Editor save folder button
*/
static void EditorSaveFolder(void)
{
	if (ParentFolder()) {
		EditorSaveLBInit(CurrentMenu->Items + 1);
	}
}
#endif

#if 0
/**
** Initialize the hash table of menu functions
*/
void InitMenuFuncHash(void)
{
	HASHADD(NULL, "null");

#if 1 // Must be rename and remove duplicate.
	HASHADD(LBRetrieve, "save-game-lb-retrieve");
	HASHADD(LBRetrieve, "load-game-lb-retrieve");
	HASHADD(LBRetrieve, "editor-save-lb-retrieve");

	HASHADD(LBRetrieveAndInfo, "editor-load-lb-retrieve");
	HASHADD(LBRetrieveAndInfo, "scen-select-lb-retrieve");
	HASHADD(LBRetrieveAndInfo, "editor-main-load-lb-retrieve");

	HASHADD(PathLBAction, "scen-select-lb-action");
	HASHADD(PathLBAction, "load-game-lb-action");
	HASHADD(PathLBAction, "editor-main-load-lb-action");
	HASHADD(PathLBAction, "editor-load-lb-action");
	HASHADD(EditorSaveLBAction, "editor-save-lb-action");

#endif

// Game menu
	HASHADD(GameMenuReturn,"game-menu-return");

// Victory, lost
	HASHADD(GameMenuEnd,"game-menu-end");
	HASHADD(SaveReplayOk,"save-replay-ok");

// Scenario select
	HASHADD(ScenSelectTPMSAction,"scen-select-tpms-action");
	HASHADD(ScenSelectFolder,"scen-select-folder");

// Program start
	HASHADD(MultiPlayerGameMenu,"multi-player-game-menu");

// Custom game setup
	HASHADD(GameSetupInit,"game-setup-init");
	HASHADD(ScenSelectMenu,"scen-select-menu");
	HASHADD(CustomGameStart,"custom-game-start");
	HASHADD(GameCancel,"game-cancel");
	HASHADD(GameRCSAction,"game-rcs-action");
	HASHADD(GameRESAction,"game-res-action");
	HASHADD(GameUNSAction,"game-uns-action");
	HASHADD(GameTSSAction,"game-tss-action");
	HASHADD(GameGATAction,"game-gat-action");
	HASHADD(CustomGameOPSAction,"custom-game-ops-action");

// Net create join
	HASHADD(JoinNetGameMenu,"net-join-game");
	HASHADD(CreateNetGameMenu,"net-create-game");
	HASHADD(CreateInternetGameMenu,"net-internet-create-game");

// Multi net type
	HASHADD(MultiPlayerLANGame,"net-lan-game");
	HASHADD(MultiPlayerInternetGame,"net-internet-game");

// Net multi setup
	HASHADD(MultiGameSetupInit,"multi-game-setup-init");
	HASHADD(MultiGameSetupExit,"multi-game-setup-exit");
	HASHADD(MultiScenSelectMenu,"multi-scen-select");
	HASHADD(MultiGameStart,"multi-game-start");
	HASHADD(MultiGameCancel,"multi-game-cancel");
	HASHADD(MultiGamePTSAction,"multi-game-pts-action");
	HASHADD(MultiGameFWSAction,"multi-game-fws-action");

// Net multi client
	HASHADD(TerminateNetConnect,"terminate-net-connect");
	HASHADD(MultiGameClientInit,"multi-game-client-init");
	HASHADD(MultiGameClientExit,"multi-game-client-exit");
	HASHADD(MultiGameClientDrawFunc,"multi-client-draw-func");
	HASHADD(MultiClientReady,"multi-client-ready");
	HASHADD(MultiClientNotReady,"multi-client-not-ready");
	HASHADD(MultiClientCancel,"multi-client-cancel");
	HASHADD(MultiClientRCSAction,"multi-client-rcs-action");
	HASHADD(MultiClientCheckboxAction,"multi-client-checkbox-action");
	HASHADD(NetMultiPlayerDrawFunc,"net-multi-player-draw-func");

// Net connecting
	HASHADD(NetConnectingInit,"net-connecting-init");
	HASHADD(NetConnectingExit,"net-connecting-exit");
	HASHADD(NetConnectingCancel,"net-connecting-cancel");

// Confirm delete
	HASHADD(DeleteConfirmOk,"delete-confirm-ok");

// Editor select
	HASHADD(EditorNewMap,"editor-new-map");
	HASHADD(EditorMainLoadMap,"editor-main-load-map");
	HASHADD(EditorSelectCancel,"editor-select-cancel");

// Editor new
	HASHADD(EditorNewDrawFunc,"editor-new-draw-func");
	HASHADD(EditorNewMapDescriptionEnterAction,"editor-new-map-description-enter-action");
	HASHADD(EditorNewMapSizeEnterAction,"editor-new-map-size-enter-action");
	HASHADD(EditorNewOk,"editor-new-ok");
	HASHADD(EditorNewCancel,"editor-new-cancel");

// Editor main load map
	HASHADD(EditorMainLoadInit,"editor-main-load-init");
	HASHADD(EditorMainLoadExit,"editor-main-load-exit");
	HASHADD(EditorMainLoadVSAction,"editor-main-load-vs-action");
	HASHADD(EditorMainLoadOk,"editor-main-load-ok");
	HASHADD(EditorMainLoadCancel,"editor-main-load-cancel");
	HASHADD(EditorMainLoadFolder,"editor-main-load-folder");

// Editor load map
	HASHADD(EditorMainLoadInit,"editor-load-init");
	HASHADD(EditorMainLoadExit,"editor-load-exit");
	HASHADD(EditorMainLoadVSAction,"editor-load-vs-action");
	HASHADD(EditorLoadOk,"editor-load-ok");
	HASHADD(EditorLoadCancel,"editor-load-cancel");
	HASHADD(EditorMainLoadFolder,"editor-load-folder");

// Editor menu
	HASHADD(EditorSaveMenu,"editor-save-menu");
	HASHADD(EditorLoadMenu,"editor-load-menu");
	HASHADD(EditorMapPropertiesMenu,"editor-map-properties-menu");
	HASHADD(EditorPlayerPropertiesMenu,"editor-player-properties-menu");
	HASHADD(EditorQuitToMenu,"editor-quit-to-menu");

// Editor map properties
	HASHADD(EditorMapPropertiesEnterAction,"editor-map-properties-enter-action");
	HASHADD(EditorMapPropertiesOk,"editor-map-properties-ok");
	HASHADD(EditorEndMenu,"editor-end-menu");

// Editor player properties
	HASHADD(EditorPlayerPropertiesDrawFunc,"editor-player-properties-draw-func");
	HASHADD(EditorPlayerPropertiesEnterAction,"editor-player-properties-enter-action");

// Editor edit resource
	HASHADD(EditorEditResourceEnterAction,"editor-edit-resource-enter-action");
	HASHADD(EditorEditResourceOk,"editor-edit-resource-ok");
	HASHADD(EditorEditResourceCancel,"editor-edit-resource-cancel");

// Editor edit ai properties
	HASHADD(EditorEditAiPropertiesCheckbox,"editor-edit-ai-properties-checkbox");
	HASHADD(EditorEditAiPropertiesOk,"editor-edit-ai-properties-ok");
	HASHADD(EditorEditAiPropertiesCancel,"editor-edit-ai-properties-cancel");

// Editor save
	HASHADD(EditorSaveInit,"editor-save-init");
	HASHADD(EditorSaveExit,"editor-save-exit");
	HASHADD(EditorSaveFolder,"editor-save-folder");
	HASHADD(EditorSaveVSAction,"editor-save-vs-action");
	HASHADD(EditorSaveEnterAction,"editor-save-enter-action");
	HASHADD(EditorSaveOk,"editor-save-ok");
	HASHADD(EditorSaveCancel,"editor-save-cancel");

// Editor save confirm
	HASHADD(EditorSaveConfirmInit,"editor-save-confirm-init");
	HASHADD(EditorSaveConfirmOk,"editor-save-confirm-ok");
	HASHADD(EditorSaveConfirmCancel,"editor-save-confirm-cancel");

// Metaserver
	HASHADD(ShowMetaServerList,"metaserver-list");
	HASHADD(MultiMetaServerGameSetupInit,"metaserver-list-init");
	HASHADD(MultiMetaServerGameSetupExit,"metaserver-list-exit");
	HASHADD(SelectGameServer,"select-game-server");
	HASHADD(MultiMetaServerClose,"menu-internet-end-menu");
}
#endif

/*----------------------------------------------------------------------------
--  Button action handler and Init/Exit functions
----------------------------------------------------------------------------*/

#if 0
/**
** Leave menus and return to game mode
*/
static void GameMenuReturn(void)
{
	InterfaceState = IfaceStateNormal;
	UI.StatusLine.Clear();
	GamePaused = false;
}
#endif

#if 0
/**
** Load game ok button callback
*/
static void LoadGameOk(void)
{
	if (!ScenSelectFileName[0]) {
		return ;
	}
	sprintf(TempPathBuf, "%s/%s", SaveDir, ScenSelectFileName);
	CommandLogDisabled = 1;
	SaveGameLoading = 1;
	CleanModules();
	LoadCcl();
	LoadGame(TempPathBuf);
	Callbacks = &GameCallbacks;
	SetMessage(_("Loaded game: %s"), TempPathBuf);
	GuiGameStarted = 1;
	GameMenuReturn();
	SelectedFileExist = 0;
	ScenSelectFileName[0] = '\0';
	ScenSelectPathName[0] = '\0';
}
#endif

#if 0
/**
**  End the running game from menu.
*/
static void GameMenuEnd(void)
{
	InterfaceState = IfaceStateNormal;
	GameRunning = false;
	CursorOn = CursorOnUnknown;
	CurrentMenu = NULL;
}
#endif

#if 0
/**
** Save replay Ok button.
*/
static void SaveReplayOk(void)
{
	FILE *fd;
	Menu *menu;
	char *buf;
	struct stat s;
	char *ptr;

	menu = FindMenu("menu-save-replay");

	if (strchr(menu->Items[1].D.Input.buffer, '/')) {
		ErrorMenu("Name cannot contain '/'");
		return;
	}
	if (strchr(menu->Items[1].D.Input.buffer, '\\')) {
		ErrorMenu("Name cannot contain '\\'");
		return;
	}

#ifdef WIN32
	sprintf(TempPathBuf, "%s/logs/",GameName);
#else
	sprintf(TempPathBuf, "%s/%s/%s", getenv("HOME"), STRATAGUS_HOME_PATH,GameName);
	strcat(TempPathBuf, "/logs/");
#endif
	ptr = TempPathBuf + strlen(TempPathBuf);
	sprintf(ptr, "log_of_stratagus_%d.log", ThisPlayer->Index);

	stat(TempPathBuf, &s);
	buf = new char[s.st_size];
	fd = fopen(TempPathBuf, "rb");
	fread(buf, s.st_size, 1, fd);
	fclose(fd);

	strncpy(ptr, menu->Items[1].D.Input.buffer, menu->Items[1].D.Input.nch);
	ptr[menu->Items[1].D.Input.nch] = '\0';
	if (!strcasestr(menu->Items[1].D.Input.buffer, ".log")) {
		strcat(ptr, ".log");
	}

	fd = fopen(TempPathBuf, "wb");
	if (!fd) {
		ErrorMenu("Cannot write to file");
		delete[] buf;
		return;
	}
	fwrite(buf, s.st_size, 1, fd);
	fclose(fd);

	delete[] buf;
	//CloseMenu();
	SelectedFileExist = 0;
	ScenSelectFileName[0] = '\0';
	ScenSelectPathName[0] = '\0';
}
#endif

/**
**  Get map info from select path+name
*/
static void GetInfoFromSelectPath(void)
{
	int i;

	if (!ScenSelectFileName[0]) {
		return;
	}
	if (ScenSelectPath[0]) {
		i = strlen(ScenSelectPath);
		strcat(ScenSelectPath, "/");
	} else {
		i = 0;
	}
	strcat(ScenSelectPath, ScenSelectFileName); // Final map name with path
	if (strcasestr(ScenSelectFileName, ".smp")) {
		LoadStratagusMapInfo(ScenSelectPath);
	}
	ScenSelectPath[i] = '\0'; // Remove appended part
}

#if 0
/**
** Enter select scenario menu.
*/
static void ScenSelectMenu(void)
{
	Menu *menu;
	int n;
	int j;
	int t;

	ProcessMenu("menu-select-scenario", 1);

	GetInfoFromSelectPath();

	menu = FindMenu("menu-custom-game");
	for (n = j = 0; j < PlayerMax; ++j) {
		t = Map.Info.PlayerType[j];
		if (t == PlayerPerson || t == PlayerComputer) {
			n++;
		}
	}
	menu->Items[12].D.Pulldown.noptions = n;
	if (menu->Items[12].D.Pulldown.curopt >= n) {
		menu->Items[12].D.Pulldown.curopt = 0;
	}
}
#endif

#if 0
/**
** Enter multiplayer select scenario menu.
*/
static void MultiScenSelectMenu(void)
{
	Menu *menu;
	unsigned flags;

	// FIXME: remove when cm works with multiplayer
	menu = FindMenu("menu-select-scenario");
	flags = menu->Items[6].Flags;
	menu->Items[6].Flags = MI_FLAGS_DISABLED;

	ScenSelectMenu();
	MultiGamePlayerSelectorsUpdate(1);

	menu->Items[6].Flags = MI_FLAGS_DISABLED;
}
#endif

#if 0
/**
** Start campaign from menu.
**
** @param number Number of the compaign.
*/
static void StartCampaignFromMenu(int number)
{
#if 0
	// JOHNS: this is currently not needed:

	// Any Campaign info should be displayed through a DrawFunc() Item
	// in the CAMPAIN_CONT menu processed below...
	ProcessMenu("menu-campaign-continue", 1);
	// Set GuiGameStarted = 1 to actually run a game here...
	// See CustomGameStart() for info...
#endif

	PlayCampaign(Campaigns[number]->Ident);
	GuiGameStarted = 1;

	// FIXME: johns otherwise crash in UpdateDisplay -> DrawMinimapCursor
	//CloseMenu();
}
#endif

#if 0
/**
** Start processing join a network game menu.
*/
static void JoinNetGameMenu(void)
{
	char server_host_buffer[64];
	char *port;
	Menu *menu;

	//
	//  Prepare enter ip/hostname menu
	//
	if (NetworkArg) {
		strncpy(server_host_buffer, NetworkArg, 24);
		server_host_buffer[24] = 0;
		if (NetworkPort != NetworkDefaultPort) {
			strcat(server_host_buffer, ":");
			port = new char[10];
			sprintf(port, "%d", NetworkPort);
			strcat(server_host_buffer, port);
			delete[] port;
		}
	} else {
		server_host_buffer[0] = '\0';
	}
	menu = FindMenu("menu-enter-server");
	strcat(server_host_buffer, "~!_");
	menu->Items[1].D.Input.buffer = server_host_buffer;
	menu->Items[1].D.Input.nch = strlen(server_host_buffer) - 3;
	menu->Items[1].D.Input.maxch = 60;
	if (menu->Items[1].D.Input.nch) {
		menu->Items[2].Flags &= ~MI_FLAGS_DISABLED;
	} else {
		menu->Items[2].Flags |= MI_FLAGS_DISABLED;
	}

	ProcessMenu("menu-enter-server", 1);

	if (menu->Items[1].D.Input.nch == 0) {
		return;
	}

	if ( (port = strchr(server_host_buffer, ':')) != NULL) {
		NetworkPort = atoi(port + 1);
		port[0] = 0;
	}

	// Now finally here is the address
	server_host_buffer[menu->Items[1].D.Input.nch] = 0;
	if (NetworkSetupServerAddress(server_host_buffer)) {
		NetErrorMenu("Unable to lookup host.");
		return;
	}
	NetworkInitClientConnect();
	if (!NetConnectRunning) {
		TerminateNetConnect();
		return;
	}

	delete[] NetworkArg;
	NetworkArg = new_strdup(server_host_buffer);

	// Here we really go...
	ProcessMenu("menu-net-connecting", 1);

	if (GuiGameStarted) {
		//CloseMenu();
	}
}
#endif

#if 0
/**
**  Network connect menu init.
*/
static void NetConnectingInit(Menu *menu)
{
	menu->Items[1].D.Text.text = NewStringDesc(NetServerText);
	menu->Items[2].D.Text.text = NewStringDesc(NetTriesText);
}
#endif

#if 0
/**
**  Network connect menu exit.
*/
static void NetConnectingExit(Menu *menu)
{
	FreeStringDesc(menu->Items[1].D.Text.text);
	FreeStringDesc(menu->Items[2].D.Text.text);
	delete menu->Items[1].D.Text.text;
	delete menu->Items[2].D.Text.text;
	menu->Items[1].D.Text.text = NULL;
	menu->Items[2].D.Text.text = NULL;
}
#endif

#if 0
/**
**  Cancel button of network connect menu pressed.
*/
static void NetConnectingCancel(void)
{
	NetworkExitClientConnect();
	// Trigger TerminateNetConnect() to call us again and end the menu
	NetLocalState = ccs_usercanceled;
	//CloseMenu();
}
#endif

#if 0
/**
**  Call back from menu loop, if network state has changed.
*/
static void TerminateNetConnect(void)
{
	switch (NetLocalState) {
		case ccs_unreachable:
			NetErrorMenu("Cannot reach server.");
			NetConnectingCancel();
			return;
		case ccs_nofreeslots:
			NetErrorMenu("Server is full.");
			NetConnectingCancel();
			return;
		case ccs_serverquits:
			NetErrorMenu("Server gone.");
			NetConnectingCancel();
			return;
		case ccs_incompatibleengine:
			NetErrorMenu("Incompatible engine version.");
			NetConnectingCancel();
			return;
		case ccs_badmap:
			NetErrorMenu("Map not available.");
			NetConnectingCancel();
			return;
		case ccs_incompatiblenetwork:
			NetErrorMenu("Incompatible network version.");
			NetConnectingCancel();
			return;
		case ccs_usercanceled:
			NetConnectingCancel();
			return;
		case ccs_started:
			NetworkGamePrepareGameSettings();
			CustomGameStart();
			return;
		default:
			break;
	}

	DebugPrint("NetLocalState %d\n" _C_ NetLocalState);
	NetConnectRunning = 2;
	GuiGameStarted = 0;
	ProcessMenu("menu-net-multi-client", 1);
	if (GuiGameStarted) {
		GameMenuReturn();
	} else {
		NetConnectingCancel();
	}
}
#endif

#if 0
/**
** Start processing network game setup menu (server).
*/
static void CreateNetGameMenu(void)
{
	GuiGameStarted = 0;
	ProcessMenu("menu-multi-setup", 1);
	if (GuiGameStarted) {
		GameMenuReturn();
	}
}
#endif

#if 0
/**
** Start process network game setup menu (server).
** Internet game, register with meta server
*/
static void CreateInternetGameMenu(void)
{
	GuiGameStarted = 0;
	AddGameServer();
	ProcessMenu("menu-multi-setup", 1);
	if (GuiGameStarted) {
		GameMenuReturn();
	}

}
#endif

#if 0
/**
** Multiplayer game start game button pressed.
*/
static void MultiGameStart(void)
{
	if (MetaServerInUse) {
		SendMetaCommand("StartGame", "");
	}

	GameSettings.Presets[0].Race = SettingsPresetMapDefault;

	NetworkServerStartGame();
	NetworkGamePrepareGameSettings();

	CustomGameStart();
}
#endif

#if 0
/**
** Enter multiplayer game menu.
*/
static void MultiPlayerGameMenu(void)
{
	char NameBuf[32];
	Menu *menu;

	menu = FindMenu("menu-enter-name");
	menu->Items[1].D.Input.buffer = NameBuf;
	strcpy(NameBuf, LocalPlayerName);
	strcat(NameBuf, "~!_");
	menu->Items[1].D.Input.nch = strlen(NameBuf) - 3;
	menu->Items[1].D.Input.maxch = 15;
	menu->Items[2].Flags &= ~MI_FLAGS_DISABLED;

	ProcessMenu("menu-enter-name", 1);

	if (menu->Items[1].D.Input.nch == 0) {
		return;
	}

	NameBuf[menu->Items[1].D.Input.nch] = 0; // Now finally here is the name
	memset(LocalPlayerName, 0, 16);
	strcpy(LocalPlayerName, NameBuf);

	// FIXME: Only save if player name changed
	SavePreferences();

	GuiGameStarted = 0;
	if (!MasterHost) {
		// No Metaserver Configured - Go right to LAN Game.
		ProcessMenu("menu-create-join-menu", 1);
	} else {
		ProcessMenu("menu-multi-net-type-menu", 1);
	}


	DebugPrint("GuiGameStarted: %d\n" _C_ GuiGameStarted);
	if (GuiGameStarted) {
		GameMenuReturn();
	}
}
#endif

#if 0
/**
** Process LAN/P2P game menu
*/
static void MultiPlayerLANGame(void)
{
	ProcessMenu("menu-create-join-menu", 1);
	MetaServerInUse = 0;
	if (GuiGameStarted) {
		GameMenuReturn();
	}
}
#endif

#if 0
/**
** Process Internet game menu
*/
static void MultiPlayerInternetGame(void)
{
	//Connect to Meta Server
	if (MetaInit() == -1 ) {
		MetaServerInUse = 0;
		MetaServerConnectError();
		return;
	}
	MetaServerInUse = 1;
	ProcessMenu("menu-internet-create-join-menu", 1);
	if (GuiGameStarted) {
		GameMenuReturn();
	}
}
#endif

#if 0
/**
**  Scenario select map type action callback
*/
static void ScenSelectTPMSAction(Menuitem *mi, int i)
{
	mi = mi->Menu->Items + 1;
	ScenSelectLBInit(mi);
}
#endif

#if 0
/**
** Custom game cancel button callback
*/
static void GameCancel(void)
{
	FreeMapInfo(&Map.Info);
	//CloseMenu();
}
#endif

#if 0
/**
** Custom game start game button pressed.
*/
static void CustomGameStart(void)
{
	int i;
	char *p;

	if (ScenSelectPath[0]) {
		strcat(ScenSelectPath, "/");
		strcat(ScenSelectPath, ScenSelectFileName); // Final map name with path
		p = ScenSelectPath + strlen(StratagusLibPath) + 1;
		strcpy(CurrentMapPath, p);
	} else {
		strcpy(CurrentMapPath, ScenSelectFileName);
		strcat(ScenSelectPath, ScenSelectFileName); // Final map name with path
	}

	for (i = 0; i < MAX_OBJECTIVES; i++) {
		if (GameIntro.Objectives[i]) {
			delete[] GameIntro.Objectives[i];
			GameIntro.Objectives[i] = NULL;
		}
	}
	GameIntro.Objectives[0] = new_strdup(DefaultObjective);

	GuiGameStarted = 1;
	//CloseMenu();
}
#endif

#if 0
/**
** Single player custom game menu entered.
*/
static void GameSetupInit(Menu *menu)
{
	Menu *custom_menu;
	int n;
	int j;
	int t;
	char *s;

	//
	//  No old path, setup the default.
	//
	if (!*CurrentMapPath || *CurrentMapPath == '.' || *CurrentMapPath == '/') {
		strcpy(CurrentMapPath, DefaultMap);
	}

	DebugPrint("Map   path: %s\n" _C_ CurrentMapPath);
	strcpy(ScenSelectPath, StratagusLibPath);
	if (*ScenSelectPath) {
		strcat(ScenSelectPath, "/");
	}
	strcat(ScenSelectPath, CurrentMapPath);
	if ((s = strrchr(ScenSelectPath, '/'))) {
		strcpy(ScenSelectFileName, s + 1);
		*s = '\0';
	}
	strcpy(ScenSelectDisplayPath, CurrentMapPath);
	if ((s = strrchr(ScenSelectDisplayPath, '/'))) {
		*s = '\0';
	} else {
		*ScenSelectDisplayPath = '\0';
	}
	DebugPrint("Start path: %s\n" _C_ ScenSelectPath);

	GetInfoFromSelectPath();

	custom_menu = FindMenu("menu-custom-game");
	for (n = j = 0; j < PlayerMax; ++j) {
		t = Map.Info.PlayerType[j];
		if (t == PlayerPerson || t == PlayerComputer) {
			++n;
		}
	}
	custom_menu->Items[12].D.Pulldown.noptions = n;
	if (custom_menu->Items[12].D.Pulldown.curopt >= n) {
		custom_menu->Items[12].D.Pulldown.curopt = 0;
	}
}
#endif

#if 0
/**
**  Menu setup race pulldown action.
**
**  @note 0 is default-race.
*/
static void GameRCSAction(Menuitem *mi, int i)
{
	int n;
	int x;

	if (mi->D.Pulldown.curopt == i) {
		for (n = 0, x = 0; n < PlayerRaces.Count; ++n) {
			if (PlayerRaces.Visible[n]) {
				if (x + 1 == i) {
					break;
				}
				++x;
			}
		}
		if (i != 0) {
			GameSettings.Presets[0].Race = x;
		} else {
			GameSettings.Presets[0].Race = SettingsPresetMapDefault;
		}
		ServerSetupState.Race[0] = i;
		NetworkServerResyncClients();
	}
}
#endif

#if 0
/**
** Game resources action callback
*/
static void GameRESAction(Menuitem *mi, int i)
{
	int v[] = { SettingsResourcesMapDefault, SettingsResourcesLow,
				SettingsResourcesMedium, SettingsResourcesHigh };

	if (!mi || mi->D.Pulldown.curopt == i) {
		GameSettings.Resources = v[i];
		ServerSetupState.ResourcesOption = i;
		if (mi) {
			NetworkServerResyncClients();
		}
	}
}

/**
** Game units action callback
*/
static void GameUNSAction(Menuitem *mi, int i)
{
	if (!mi || mi->D.Pulldown.curopt == i) {
		GameSettings.NumUnits = i ? SettingsNumUnits1 : SettingsNumUnitsMapDefault;
		ServerSetupState.UnitsOption = i;
		if (mi) {
			NetworkServerResyncClients();
		}
	}
}

/**
** Game tilesets action callback
*/
static void GameTSSAction(Menuitem *mi, int i)
{
	if (!mi || mi->D.Pulldown.curopt == i) {
		// Subtract 1 for default option.
		GameSettings.Terrain = i - 1;
		ServerSetupState.TilesetSelection = i;
		if (mi) {
			NetworkServerResyncClients();
		}
	}
}

/**
** Called if the pulldown menu of the game type is changed.
*/
static void GameGATAction(Menuitem *mi, int i)
{
	if (!mi || mi->D.Pulldown.curopt == i) {
		GameSettings.GameType = i ? SettingsGameTypeMelee + i - 1 : SettingsGameTypeMapDefault;
		ServerSetupState.GameTypeOption = i;
		if (mi) {
			NetworkServerResyncClients();
		}
	}
}
#endif

#if 0
/**
** Game opponents action callback
*/
static void CustomGameOPSAction(Menuitem *mi, int i)
{
	GameSettings.Opponents = i ? i : SettingsPresetMapDefault;
}
#endif

#if 0
/**
** Menu setup fog-of-war pulldown action.
*/
static void MultiGameFWSAction(Menuitem *mi, int i)
{
	if (!mi || mi->D.Pulldown.curopt == i) {
		DebugPrint("Update fow %d\n" _C_ i);
		switch (i) {
			case 0:
				Map.NoFogOfWar = false;
				FlagRevealMap = 0;
				GameSettings.NoFogOfWar = false;
				GameSettings.RevealMap = 0;
				break;
			case 1:
				Map.NoFogOfWar = true;
				FlagRevealMap = 0;
				GameSettings.NoFogOfWar = true;
				GameSettings.RevealMap = 0;
				break;
			case 2:
				Map.NoFogOfWar = false;
				FlagRevealMap = 1;
				GameSettings.NoFogOfWar = false;
				GameSettings.RevealMap = 1;
				break;
			case 3:
				Map.NoFogOfWar = true;
				FlagRevealMap = 1;
				GameSettings.NoFogOfWar = true;
				GameSettings.RevealMap = 1;
				break;
		}
		ServerSetupState.FogOfWar = i;
		if (mi) {
			NetworkServerResyncClients();
		}
	}
}
#endif

#if 0
/**
** Multiplayer menu player server states.
*/
static void MultiGamePTSAction(Menuitem *mi, int o)
{
	Menu *menu;
	int i;

	menu = FindMenu("menu-multi-setup");
	i = mi - menu->Items - SERVER_PLAYER_STATE;
	// JOHNS: Must this be always true?
	// ARI: NO! think of client menus!
	// Assert(i >= 0 && i <= PlayerMax - 1);

	if (i > 0 && i < PlayerMax-1) {
		if (mi->D.Pulldown.curopt == o) {
			if (mi->D.Pulldown.noptions == 2) { // computer slot
				ServerSetupState.CompOpt[i] = o + 1;
			} else {
				ServerSetupState.CompOpt[i] = o;
			}
			MultiGamePlayerSelectorsUpdate(3); // Recalc buttons on server
			NetworkServerResyncClients();
		}
	}

}
#endif

/**
** Multiplayer network game final race an player type setup.
*/
void NetworkGamePrepareGameSettings(void)
{
	int c;
	int h;
	int i;
	int num[PlayerMax];
	int comp[PlayerMax];
	int v;

	DebugPrint("NetPlayers = %d\n" _C_ NetPlayers);

	GameSettings.NetGameType=SettingsMultiPlayerGame;

#ifdef DEBUG
	for (i = 0; i < PlayerMax-1; i++) {
		printf("%02d: CO: %d   Race: %d   Host: ", i, ServerSetupState.CompOpt[i], ServerSetupState.Race[i]);
		if (ServerSetupState.CompOpt[i] == 0) {
			for (h = 0; h < NetPlayers; h++) {
				if (Hosts[h].PlyNr == i) {
					printf("%s", Hosts[h].PlyName);
				}
			}
		}
		printf("\n");
	}
#endif

	// Make a list of the available player slots.
	for (c = h = i = 0; i < PlayerMax; i++) {
		if (Map.Info.PlayerType[i] == PlayerPerson) {
			num[h++] = i;
		}
		if (Map.Info.PlayerType[i] == PlayerComputer) {
			comp[c++] = i; // available computer player slots
		}
	}
	for (i = 0; i < h; i++) {
		switch(ServerSetupState.CompOpt[num[i]]) {
			case 0:
				GameSettings.Presets[num[i]].Type = PlayerPerson;
				v = ServerSetupState.Race[num[i]];
				if (v != 0) {
					int n;
					int x;

					for (n = 0, x = 0; n < PlayerRaces.Count; ++n) {
						if (PlayerRaces.Visible[n]) {
							if (x + 1 == v) {
								break;
							}
							++x;
						}
					}
					GameSettings.Presets[num[i]].Race = x;
				} else {
					GameSettings.Presets[num[i]].Race = SettingsPresetMapDefault;
				}
				break;
			case 1:
				GameSettings.Presets[num[i]].Type = PlayerComputer;
				break;
			case 2:
				GameSettings.Presets[num[i]].Type = PlayerNobody;
			default:
				break;
		}
	}
	for (i = 0; i < c; i++) {
		if (ServerSetupState.CompOpt[comp[i]] == 2) { // closed..
			GameSettings.Presets[comp[i]].Type = PlayerNobody;
			DebugPrint("Settings[%d].Type == Closed\n" _C_ comp[i]);
		}
	}

#ifdef DEBUG
	for (i = 0; i < NetPlayers; i++) {
		Assert(GameSettings.Presets[Hosts[i].PlyNr].Type == PlayerPerson);
		;
	}
#endif
}

/**
** Player selectors have changed.
** Caution: Called by map change (initial = 1)!
** Caution: Called by network events from clients (initial = 2)!
** Caution: Called by button action on server (initial = 3)!
*/
static void MultiGamePlayerSelectorsUpdate(int initial)
{
	Menu *menu;
	int i;
	int h;
	int c;
	int avail;
	int ready;
	int plyrs;

	menu = FindMenu("menu-multi-setup");

	// FIXME: What this has to do:
	// Use lag gem as KICK button
	//  Notify clients about MAP change: (initial = 1...)

	// Calculate available slots from map info
	for (c = h = i = 0; i < PlayerMax; i++) {
		if (Map.Info.PlayerType[i] == PlayerPerson) {
			h++; // available interactive player slots
		}
		if (Map.Info.PlayerType[i] == PlayerComputer) {
			c++; // available computer player slots
		}
	}

	avail = h;
	plyrs = 0;
	// Setup the player menu
	for (ready = i = 1; i < PlayerMax-1; i++) {
		if (initial == 1) {
			if (i < h) {
				ServerSetupState.CompOpt[i] = 0;
			}
			menu->Items[SERVER_PLAYER_READY - 1 + i].Flags = MI_FLAGS_DISABLED;
			menu->Items[SERVER_PLAYER_LAG - 1 + i].Flags = MI_FLAGS_DISABLED;

			// FIXME: don't forget to throw out additional players
			//   without available slots here!

		}
		if (Hosts[i].PlyNr) {
			menu->Items[SERVER_PLAYER_STATE + i].Flags |= MI_FLAGS_INVISIBLE;
			menu->Items[SERVER_PLAYER_TEXT + i].Flags &= ~MI_FLAGS_INVISIBLE;

			menu->Items[SERVER_PLAYER_READY - 1 + i].Flags = MI_FLAGS_DISABLED;
			++plyrs;
			if (ServerSetupState.Ready[i]) {
				menu->Items[SERVER_PLAYER_READY - 1 + i].D.Checkbox.Checked = 1;
				++ready;
			}

			menu->Items[SERVER_PLAYER_LAG - 1 + i].Flags = MI_FLAGS_DISABLED;
		} else {
			// don't allow network and button events to intercept server player's action on pulldown buttons!
			if (!(menu->Items[SERVER_PLAYER_STATE + i].Flags & MI_FLAGS_CLICKED)) {
				if (initial == 1 ||
					(initial == 2 && menu->Items[SERVER_PLAYER_STATE + i].MiType != MiTypePulldown)) {
					menu->Items[SERVER_PLAYER_STATE + i].Flags = MI_FLAGS_NONE;
					menu->Items[SERVER_PLAYER_TEXT + i].Flags |= MI_FLAGS_INVISIBLE;
					menu->Items[SERVER_PLAYER_STATE + i].D.Pulldown.curopt = ServerSetupState.CompOpt[i];
				}
			}
			if (i < h && ServerSetupState.CompOpt[i] != 0) {
				avail--;
			}

			menu->Items[SERVER_PLAYER_READY - 1 + i].Flags = MI_FLAGS_DISABLED;
			menu->Items[SERVER_PLAYER_LAG - 1 + i].Flags = MI_FLAGS_DISABLED;
		}


		if (i >= h) {
			// Allow to switch off (close) preset ai-computer slots
			// FIXME: evaluate game type...
			if (initial == 1 && i < h + c) {
				menu->Items[SERVER_PLAYER_STATE + i].Flags &= ~MI_FLAGS_DISABLED;
				menu->Items[SERVER_PLAYER_STATE + i].D.Pulldown.noptions = 2;
				menu->Items[SERVER_PLAYER_STATE + i].D.Pulldown.options = mgptsoptions + 1;
				menu->Items[SERVER_PLAYER_STATE + i].D.Pulldown.curopt = 0;
				ServerSetupState.CompOpt[i] = 1;
				menu->Items[SERVER_PLAYER_STATE + i].D.Pulldown.curopt = ServerSetupState.CompOpt[i] - 1;
			}

			menu->Items[SERVER_PLAYER_READY - 1 + i].Flags = MI_FLAGS_DISABLED;
			menu->Items[SERVER_PLAYER_LAG - 1 + i].Flags = MI_FLAGS_DISABLED;
		}

		if (i >= h + c) {
			menu->Items[SERVER_PLAYER_STATE + i].D.Pulldown.defopt = 2;
			menu->Items[SERVER_PLAYER_STATE + i].D.Pulldown.curopt = 2;
			menu->Items[SERVER_PLAYER_STATE + i].Flags = MI_FLAGS_DISABLED;
		}
	}


	// Tell connect state machines how many interactive players we can have
	NetPlayers = avail;
	// Check if all players are ready.
	DebugPrint("READY to START: AVAIL = %d, READY = %d\n" _C_ avail
			_C_ ready);

	// Disable the select scenario after players have joined.
	if (plyrs) {
		// disable Select Scenario button
		menu->Items[2].Flags = MI_FLAGS_DISABLED;
	} else {
		// enable Select Scenario button
		menu->Items[2].Flags = 0;
	}
	if (ready == avail) {
		if (menu->Items[3].Flags == MI_FLAGS_DISABLED) {
			// enable start game button
			menu->Items[3].Flags = 0;
		}
	} else {
		// disable start game button
		menu->Items[3].Flags = MI_FLAGS_DISABLED;
	}

	if (MetaServerInUse) {
		ChangeGameServer();
	}
}

#if 0
/**
** Update client network menu.
*/
static void MultiClientUpdate(int initial)
{
	Menu *menu;
	int i;
	int h;
	int c;

	menu = FindMenu("menu-net-multi-client");

	//  Calculate available slots from map info
	for (c = h = i = 0; i < PlayerMax; i++) {
		if (Map.Info.PlayerType[i] == PlayerPerson) {
			h++; // available interactive player slots
		}
		if (Map.Info.PlayerType[i] == PlayerComputer) {
			c++; // available computer player slots
		}
	}

	//
	// Setup defaults, reset values.
	//
	if (initial) {
		menu->Items[CLIENT_PLAYER_STATE].Flags |= MI_FLAGS_INVISIBLE;
		menu->Items[CLIENT_PLAYER_TEXT].Flags &= ~MI_FLAGS_INVISIBLE;
		memset(&ServerSetupState, 0, sizeof(ServerSetup));
		memset(&LocalSetupState, 0, sizeof(ServerSetup));
	}
	for (i = 1; i < PlayerMax - 1; i++) {
		//
		// Johns: This works only if initial. Hosts[i].PlyNr is later lost.
		//
		if (Hosts[i].PlyNr || i == NetLocalHostsSlot) {
			menu->Items[CLIENT_PLAYER_STATE + i].Flags |= MI_FLAGS_INVISIBLE;
			menu->Items[CLIENT_PLAYER_TEXT + i].Flags &= ~MI_FLAGS_INVISIBLE;
			if (i == NetLocalHostsSlot) {
				menu->Items[CLIENT_PLAYER_READY - 1 + i].Flags = MI_FLAGS_DISABLED;
			} else {
				menu->Items[CLIENT_PLAYER_READY - 1 + i].Flags = MI_FLAGS_NONE;
			}
		} else {
			menu->Items[CLIENT_PLAYER_STATE + i].Flags &= ~MI_FLAGS_INVISIBLE;
			menu->Items[CLIENT_PLAYER_TEXT + i].Flags |= MI_FLAGS_INVISIBLE;
			menu->Items[CLIENT_PLAYER_STATE + i].Flags |= MI_FLAGS_DISABLED;
			menu->Items[CLIENT_PLAYER_STATE + i].D.Pulldown.curopt =
				ServerSetupState.CompOpt[i];
			menu->Items[CLIENT_PLAYER_READY - 1 + i].Flags = MI_FLAGS_INVISIBLE;
		}

		menu->Items[CLIENT_PLAYER_READY - 1 + i].D.Checkbox.Checked = !!ServerSetupState.Ready[i];

#if 0
		if (i != NetLocalHostsSlot) {
		//if (i >= h) {
			menu->Items[CLIENT_PLAYER_STATE + i].D.Pulldown.curopt =
				ServerSetupState.CompOpt[i];
		}
#endif

		// Unused slots are always disabled.
		if (i >= h + c) {
			menu->Items[CLIENT_PLAYER_READY - 1 + i].Flags =
				MI_FLAGS_INVISIBLE;
			menu->Items[CLIENT_PLAYER_STATE + i].D.Pulldown.defopt =
				menu->Items[CLIENT_PLAYER_STATE + i].D.Pulldown.curopt = 2;
			menu->Items[CLIENT_PLAYER_STATE + i].Flags = MI_FLAGS_DISABLED;
		}
	}
}
#endif

#if 0
/**
**  Multiplayer server menu init callback
*/
static void MultiGameSetupInit(Menu *menu)
{
	int i;
	int h;

	// FIXME: Remove this when .cm is supported
	if (*CurrentMapPath && strstr(CurrentMapPath, ".cm\0")) {
		*CurrentMapPath = '\0';
	}

	GameSetupInit(menu);
	NetworkInitServerConnect();
	menu->Items[SERVER_PLAYER_STATE].Flags |= MI_FLAGS_INVISIBLE;
	MultiGameFWSAction(NULL, menu->Items[27].D.Pulldown.defopt);

	memset(&ServerSetupState, 0, sizeof(ServerSetup));
	// Calculate available slots from map info
	for (h = i = 0; i < PlayerMax; i++) {
		if (Map.Info.PlayerType[i] == PlayerPerson) {
			++h; // available interactive player slots
		}
	}
	for (i = h; i < PlayerMax - 1; ++i) {
		ServerSetupState.CompOpt[i] = 1;
	}
	MultiGamePlayerSelectorsUpdate(1);

	if (MetaServerInUse) {
		ChangeGameServer();
	}

}
#endif

#if 0
/**
**  Multiplayer server menu exit callback
*/
static void MultiGameSetupExit(Menu *menu)
{
}
#endif

#if 0
/**
**  Cancel button of server multi player menu pressed.
*/
static void MultiGameCancel(void)
{
	NetworkExitServerConnect();

	if (MetaServerInUse) {
		SendMetaCommand("AbandonGame", "");
	}

	FreeMapInfo(&Map.Info);

	NetPlayers = 0; // Make single player menus work again!
	GameCancel();
}
#endif

#if 0
/**
**  Draw the multi player setup menu.
*/
static void NetMultiPlayerDrawFunc(Menuitem *mi)
{
	Menu *menu;
	int i;
	const char *nc;
	const char *rc;

	menu = FindMenu("menu-multi-setup");
	i = mi - menu->Items - SERVER_PLAYER_TEXT;
	if (i >= 0 && i < PlayerMax - 1) { // Ugly test to detect server
		if (i > 0) {
			menu->Items[SERVER_PLAYER_READY - 1 + i].Flags &=
				~MI_FLAGS_DISABLED;
			// Note: re-disabled in MultiGamePlayerSelectorsUpdate()
			// for kicked out clients!!
			if (ServerSetupState.Ready[i]) {
				menu->Items[SERVER_PLAYER_READY - 1 + i].Flags |= MI_FLAGS_DISABLED;
				menu->Items[SERVER_PLAYER_READY - 1 + i].D.Checkbox.Checked = 1;
			} else {
				menu->Items[SERVER_PLAYER_READY - 1 + i].Flags |= MI_FLAGS_DISABLED;
				menu->Items[SERVER_PLAYER_READY - 1 + i].D.Checkbox.Checked = 0;
			}
			if (ServerSetupState.LastFrame[i] + 30 > FrameCounter) {
				menu->Items[SERVER_PLAYER_LAG - 1 + i].Flags |= MI_FLAGS_DISABLED;
				menu->Items[SERVER_PLAYER_LAG - 1 + i].D.Checkbox.Checked = 1;
			} else {
				menu->Items[SERVER_PLAYER_LAG - 1 + i].Flags |= MI_FLAGS_DISABLED;
			}

		}
	} else {
		menu = FindMenu("menu-net-multi-client");
		i = mi - menu->Items - CLIENT_PLAYER_TEXT;
		if (i > 0) {
			menu->Items[CLIENT_PLAYER_READY - 1 + i].Flags &=
				~MI_FLAGS_DISABLED;
			if (i == NetLocalHostsSlot) {
				menu->Items[CLIENT_PLAYER_READY - 1 + i].Flags &= ~MI_FLAGS_DISABLED;
			} else {
				menu->Items[CLIENT_PLAYER_READY - 1 + i].Flags |= MI_FLAGS_DISABLED;
			}
		}
	}

	GetDefaultTextColors(&nc, &rc);
	SetDefaultTextColors(rc, rc);
	VideoDrawText(UI.Offset640X + mi->XOfs, UI.Offset480Y + mi->YOfs, GameFont, Hosts[i].PlyName);

	SetDefaultTextColors(nc, rc);
}
#endif

#if 0
/**
**  Cancel button of multiplayer client menu pressed.
*/
static void MultiClientCancel(void)
{
	NetworkDetachFromServer();
	FreeMapInfo(&Map.Info);
	// GameCancel();
}
#endif

#if 0
/**
**  Multiplayer client menu init callback
*/
static void MultiGameClientInit(Menu *menu)
{
	// GameSetupInit(mi);
	MultiClientUpdate(1);
	if (LocalSetupState.Ready[NetLocalHostsSlot]) {
		menu->Items[2].Flags = MI_FLAGS_DISABLED;
		menu->Items[3].Flags = 0;
		menu->Items[CLIENT_RACE].Flags = MI_FLAGS_DISABLED;
	} else {
		menu->Items[3].Flags = MI_FLAGS_DISABLED;
		menu->Items[2].Flags = 0;
		menu->Items[CLIENT_RACE].Flags = 0;
	}
}
#endif

#if 0
/**
**  Multiplayer client menu exit callback
*/
static void MultiGameClientExit(Menu *menu)
{
}
#endif

#if 0
/**
**  Multiplayer client gem action. Toggles ready flag.
*/
static void MultiClientCheckboxAction(Menuitem *mi)
{
	int i;

	i = mi - mi->Menu->Items - CLIENT_PLAYER_READY + 1;
	if (i == NetLocalHostsSlot) {
		LocalSetupState.Ready[i] = !LocalSetupState.Ready[i];
		if (LocalSetupState.Ready[i]) {
			mi->Menu->Items[2].Flags = MI_FLAGS_DISABLED;
			mi->Menu->Items[3].Flags = 0;
			mi->Menu->Items[CLIENT_RACE].Flags = MI_FLAGS_DISABLED;
		} else {
			mi->Menu->Items[3].Flags = MI_FLAGS_DISABLED;
			mi->Menu->Items[2].Flags = 0;
			mi->Menu->Items[CLIENT_RACE].Flags = 0;
		}
		MultiClientUpdate(0);
	}
}
#endif

#if 0
/**
**  Multiplayer client races action callback
*/
static void MultiClientRCSAction(Menuitem *mi, int i)
{
	if (mi->D.Pulldown.curopt == i) {
		LocalSetupState.Race[NetLocalHostsSlot] = mi->D.Pulldown.noptions - 1 - i;
		MultiClientUpdate(0);
	}
}
#endif

#if 0
/**
** Multiplayer client ready button
*/
static void MultiClientReady(void)
{
	Menu *menu;

	menu = FindMenu("menu-net-multi-client");
	menu->Items[2].Flags = MI_FLAGS_DISABLED;
	menu->Items[3].Flags = 0;
	menu->Items[CLIENT_RACE].Flags = MI_FLAGS_DISABLED;
	LocalSetupState.Ready[NetLocalHostsSlot] = 1;
	MultiClientUpdate(0);
}
#endif

#if 0
/**
** Multiplayer client not ready button
*/
static void MultiClientNotReady(void)
{
	Menu *menu;

	menu = FindMenu("menu-net-multi-client");
	menu->Items[3].Flags = MI_FLAGS_DISABLED;
	menu->Items[2].Flags = 0;
	menu->Items[CLIENT_RACE].Flags = 0;
	LocalSetupState.Ready[NetLocalHostsSlot] = 0;
	MultiClientUpdate(0);
}
#endif

/**
** Callback from netconnect loop in Client-Sync state:
** Compare local state with server's information
** and force update when changes have occured.
*/
void NetClientCheckLocalState(void)
{
	if (LocalSetupState.Ready[NetLocalHostsSlot] != ServerSetupState.Ready[NetLocalHostsSlot]) {
		NetLocalState = ccs_changed;
		return;
	}
	if (LocalSetupState.Race[NetLocalHostsSlot] != ServerSetupState.Race[NetLocalHostsSlot]) {
		NetLocalState = ccs_changed;
		return;
	}
	/* ADD HERE */
}

/**
** FIXME: docu
*/
int NetClientSelectScenario(void)
{
	char *cp;

	cp = strrchr(MenuMapFullPath, '/');
	if (cp) {
		strcpy(ScenSelectFileName, cp + 1);
		*cp = 0;
		strcpy(ScenSelectPath, MenuMapFullPath);
		*cp = '/';
	} else {
		strcpy(ScenSelectFileName, MenuMapFullPath);
		ScenSelectPath[0] = 0;
	}

	FreeMapInfo(&Map.Info);
	LoadStratagusMapInfo(MenuMapFullPath);
	return 0;
}

/**
** FIXME: docu
*/
void NetConnectForceDisplayUpdate(void)
{
	MultiGamePlayerSelectorsUpdate(2);
}

#if 0
/**
** Update client menu to follow server menu.
*/
void NetClientUpdateState(void)
{
	Menu *menu;

	menu = FindMenu("menu-net-multi-client");

	GameRESAction(NULL, ServerSetupState.ResourcesOption);
	menu->Items[CLIENT_RESOURCE].D.Pulldown.curopt =
		ServerSetupState.ResourcesOption;

	GameUNSAction(NULL, ServerSetupState.UnitsOption);
	menu->Items[CLIENT_UNITS].D.Pulldown.curopt =
		ServerSetupState.UnitsOption;

	MultiGameFWSAction(NULL, ServerSetupState.FogOfWar);
	menu->Items[CLIENT_FOG_OF_WAR].D.Pulldown.curopt =
		ServerSetupState.FogOfWar;

	GameTSSAction(NULL, ServerSetupState.TilesetSelection);
	menu->Items[CLIENT_TILESET].D.Pulldown.curopt =
		ServerSetupState.TilesetSelection;

	GameGATAction(NULL, ServerSetupState.GameTypeOption);
	menu->Items[CLIENT_GAMETYPE].D.Pulldown.curopt =
		ServerSetupState.GameTypeOption;

	MultiClientUpdate(0);
	DebugPrint("NetClientUpdateState\n");
}
#endif

/**
** Setup Editor Paths
*/
void SetupEditor(void)
{
	char *s;
	//
	//  Create a default path + map.
	//
	if (!*CurrentMapPath || *CurrentMapPath == '.' || *CurrentMapPath == '/') {
		strcpy(CurrentMapPath, DefaultMap);
	}

	//
	// Use the last path.
	//
	strcpy(ScenSelectPath, StratagusLibPath);
	if (*ScenSelectPath) {
		strcat(ScenSelectPath, "/");
	}
	strcat(ScenSelectPath, CurrentMapPath);
	if ((s = strrchr(ScenSelectPath, '/'))) {
		strcpy(ScenSelectFileName, s + 1);
		*s = '\0';
	}
	strcpy(ScenSelectDisplayPath, CurrentMapPath);
	if ((s = strrchr(ScenSelectDisplayPath, '/'))) {
		*s = '\0';
	} else {
		*ScenSelectDisplayPath = '\0';
	}

}


#if 0
/**
** Editor select cancel button callback
*/
static void EditorSelectCancel(void)
{
	//QuitToMenu = 1;
	Editor.Running = EditorNotRunning;
	//CloseMenu();
}
#endif

#if 0
/**
** Called from menu, for new editor map.
*/
static void EditorNewMap(void)
{
	Menu *menu;
	char width[10];
	char height[10];
	char description[36];

	EditorCancelled = 0;

	menu = FindMenu("menu-editor-new");
	menu->Items[2].D.Input.buffer = description;
	strcpy(description, "~!_");
	menu->Items[2].D.Input.nch = strlen(description) - 3;
	menu->Items[2].D.Input.maxch = 31;
	menu->Items[4].D.Input.buffer = width;
	strcpy(width, "128~!_");
	menu->Items[4].D.Input.nch = strlen(width) - 3;
	menu->Items[4].D.Input.maxch = 4;
	menu->Items[5].D.Input.buffer = height;
	strcpy(height, "128~!_");
	menu->Items[5].D.Input.nch = strlen(width) - 3;
	menu->Items[5].D.Input.maxch = 4;
	ProcessMenu("menu-editor-new", 1);

	if (EditorCancelled) {
		return;
	}

	description[strlen(description) - 3] = '\0';
	Map.Info.Description = new_strdup(description);
	Map.Info.MapWidth = atoi(width);
	Map.Info.MapHeight = atoi(height);

	Video.ClearScreen();

	*CurrentMapPath = '\0';

	GuiGameStarted = 1;
	//CloseMenu();
}
#endif

#if 0
/**
** Editor new map draw func
*/
static void EditorNewDrawFunc(Menuitem *mi)
{
}
#endif

#if 0
/**
** Editor new map, map description input box callback
*/
static void EditorNewMapDescriptionEnterAction(Menuitem *mi, int key)
{
}
#endif

#if 0
/**
** Editor new map, size input box callback
*/
static void EditorNewMapSizeEnterAction(Menuitem * mi, int key)
{
	if (mi->D.Input.nch > 0
			&& !isdigit(mi->D.Input.buffer[mi->D.Input.nch - 1])) {
		strcpy(mi->D.Input.buffer + (--mi->D.Input.nch), "~!_");
	}
}
#endif

#if 0
/**
** Editor new map ok button
*/
static void EditorNewOk(void)
{
	Menu *menu;
	unsigned value1;
	unsigned value2;

	menu = CurrentMenu;
	value1 = atoi(menu->Items[4].D.Input.buffer);
	value2 = atoi(menu->Items[5].D.Input.buffer);

	if (value1 < 32 || value2 < 32) {
		if (value1 < 32) {
			sprintf(menu->Items[4].D.Input.buffer, "32~!_");
			menu->Items[4].D.Input.nch = strlen(menu->Items[4].D.Input.buffer) - 3;
		}
		if (value2 < 32) {
			sprintf(menu->Items[5].D.Input.buffer, "32~!_");
			menu->Items[5].D.Input.nch = strlen(menu->Items[5].D.Input.buffer) - 3;
		}
		ErrorMenu("Size smaller than 32");
	} else if (value1 > 1024 || value2 > 1024) {
		if (value1 == 0) {
			sprintf(menu->Items[4].D.Input.buffer, "1024~!_");
			menu->Items[4].D.Input.nch = strlen(menu->Items[4].D.Input.buffer) - 3;
		}
		if (value2 == 0) {
			sprintf(menu->Items[5].D.Input.buffer, "1024~!_");
			menu->Items[5].D.Input.nch = strlen(menu->Items[5].D.Input.buffer) - 3;
		}
		ErrorMenu("Size larger than 1024");
	} else if (value1 / 32 * 32 != value1 || value2/32*32 != value2) {
		if (value1 / 32 * 32 != value1) {
			sprintf(menu->Items[4].D.Input.buffer, "%d~!_", (value1 + 16) / 32 * 32);
			menu->Items[4].D.Input.nch = strlen(menu->Items[4].D.Input.buffer) - 3;
		}
		if (value2 / 32 * 32 != value2) {
			sprintf(menu->Items[5].D.Input.buffer, "%d~!_", (value2 + 16) / 32 * 32);
			menu->Items[5].D.Input.nch = strlen(menu->Items[5].D.Input.buffer) - 3;
		}
		ErrorMenu("Size must be a multiple of 32");
	}
	else {
		char tilemodel[PATH_MAX];

		sprintf(Map.TileModelsFileName, "scripts/tilesets/%s.lua",
				menu->Items[7].D.Pulldown.options[menu->Items[7].D.Pulldown.curopt]);
		sprintf(tilemodel, "%s/scripts/tilesets/%s.lua", StratagusLibPath,
				menu->Items[7].D.Pulldown.options[menu->Items[7].D.Pulldown.curopt]);
		LuaLoadFile(tilemodel);
		//CloseMenu();
	}
}
#endif

#if 0
/**
** Editor new map cancel button
*/
static void EditorNewCancel(void)
{
	EditorCancelled = 1;
	//CloseMenu();
}
#endif

#if 0
/**
** Editor main load map menu
*/
static void EditorMainLoadMap(void)
{
	char *p;
	char *s;

	EditorCancelled = 0;
	ProcessMenu("menu-editor-main-load-map", 1);
	GetInfoFromSelectPath();

	if (EditorCancelled) {
		return;
	}

	Video.ClearScreen();

	if (ScenSelectPath[0]) {
		s = ScenSelectPath + strlen(ScenSelectPath);
		*s = '/';
		strcpy(s+1, ScenSelectFileName); // Final map name with path
		p = ScenSelectPath + strlen(StratagusLibPath) + 1;
		strcpy(CurrentMapPath, p);
		*s = '\0';
	} else {
		strcpy(CurrentMapPath, ScenSelectFileName);
	}
	
	GuiGameStarted = 1;
	//CloseMenu();
}
#endif

#if 0
/**
** Editor main load init callback
*/
static void EditorMainLoadInit(Menu *menu)
{
	EditorMainLoadLBInit(menu->Items + 1);
}
#endif

#if 0
/**
** Editor main load exit callback
*/
static void EditorMainLoadExit(Menu *menu)
{
	LBExit(menu->Items + 1);
}
#endif

#if 0
/**
** Editor main load ok button
*/
static void EditorMainLoadOk(void)
{
	Menu *menu;
	Menuitem *mi;

	menu = CurrentMenu;
	mi = &menu->Items[1];
	if (ScenSelectPathName[0]) {
		strcat(ScenSelectPath, "/");
		strcat(ScenSelectPath, ScenSelectPathName);
		if (ScenSelectDisplayPath[0]) {
			strcat(ScenSelectDisplayPath, "/");
		}
		strcat(ScenSelectDisplayPath, ScenSelectPathName);
		EditorMainLoadLBInit(mi);
	} else if (ScenSelectFileName[0]) {
		//CloseMenu();
	}
}
#endif

#if 0
/**
** Editor main load cancel button
*/
static void EditorMainLoadCancel(void)
{
	char *s;

	EditorCancelled=1;

	//
	//  Use last selected map.
	//
	DebugPrint("Map   path: %s\n" _C_ CurrentMapPath);
	strcpy(ScenSelectPath, StratagusLibPath);
	if (*ScenSelectPath) {
		strcat(ScenSelectPath, "/");
	}
	strcat(ScenSelectPath, CurrentMapPath);
	if ((s = strrchr(ScenSelectPath, '/'))) {
		strcpy(ScenSelectFileName, s + 1);
		*s = '\0';
	}
	strcpy(ScenSelectDisplayPath, CurrentMapPath);
	if ((s = strrchr(ScenSelectDisplayPath, '/'))) {
		*s = '\0';
	} else {
		*ScenSelectDisplayPath = '\0';
	}

	DebugPrint("Start path: %s\n" _C_ ScenSelectPath);

	//CloseMenu();
}
#endif

#if 0
/**
** Editor main load vertical slider action callback
*/
static void EditorMainLoadVSAction(Menuitem *mi)
{
}
#endif

/**
**  Editor load map menu
*/
void EditorLoadMenu(void)
{
	char *p;
	char *s;

	EditorCancelled = 0;
	ProcessMenu("menu-editor-load", 1);
	GetInfoFromSelectPath();

	if (EditorCancelled) {
		return;
	}

	Video.ClearScreen();

	if (ScenSelectPath[0]) {
		s = ScenSelectPath + strlen(ScenSelectPath);
		*s = '/';
		strcpy(s + 1, ScenSelectFileName); // Final map name with path
		p = ScenSelectPath + strlen(StratagusLibPath) + 1;
		strcpy(CurrentMapPath, p);
		*s = '\0';
	} else {
		strcpy(CurrentMapPath, ScenSelectFileName);
	}

	Editor.MapLoaded = true;
	Editor.Running = EditorNotRunning;
	//CloseMenu();
}

#if 0
/**
** Editor main load ok button
*/
static void EditorLoadOk(void)
{
	Menu *menu;
	Menuitem *mi;

	menu = CurrentMenu;
	mi = &menu->Items[1];
	if (ScenSelectPathName[0]) {
		strcat(ScenSelectPath, "/");
		strcat(ScenSelectPath, ScenSelectPathName);
		if (ScenSelectDisplayPath[0]) {
			strcat(ScenSelectDisplayPath, "/");
		}
		strcat(ScenSelectDisplayPath, ScenSelectPathName);
		EditorMainLoadLBInit(mi);
	} else if (ScenSelectFileName[0]) {
		//CloseMenu();
	}
}
#endif

#if 0
/**
** Editor main load cancel button
*/
static void EditorLoadCancel(void)
{
	char *s;

	EditorCancelled = 1;

	//
	//  Use last selected map.
	//
	DebugPrint("Map   path: %s\n" _C_ CurrentMapPath);
	strcpy(ScenSelectPath, StratagusLibPath);
	if (*ScenSelectPath) {
		strcat(ScenSelectPath, "/");
	}
	strcat(ScenSelectPath, CurrentMapPath);
	if ((s = strrchr(ScenSelectPath, '/'))) {
		strcpy(ScenSelectFileName, s + 1);
		*s = '\0';
	}
	strcpy(ScenSelectDisplayPath, CurrentMapPath);
	if ((s = strrchr(ScenSelectDisplayPath, '/'))) {
		*s = '\0';
	} else {
		*ScenSelectDisplayPath = '\0';
	}

	DebugPrint("Start path: %s\n" _C_ ScenSelectPath);

	EditorEndMenu();
}
#endif

#if 0
/**
** Editor map properties menu
*/
static void EditorMapPropertiesMenu(void)
{
	Menu *menu;
	char description[36];
	char size[30];

	menu = FindMenu("menu-editor-map-properties");

	menu->Items[2].D.Input.buffer = description;
	strcpy(description, Map.Info.Description);
	strcat(description, "~!_");
	menu->Items[2].D.Input.nch = strlen(description) - 3;
	menu->Items[2].D.Input.maxch = 31;

	sprintf(size, "%d x %d", Map.Info.MapWidth, Map.Info.MapHeight);
	menu->Items[4].D.Text.text = NewStringDesc(size);
	menu->Items[6].D.Pulldown.defopt = 0;

	// FIXME: Remove the version pulldown
	menu->Items[8].D.Pulldown.defopt = 1;
	menu->Items[8].Flags = static_cast<unsigned int>(-1);

	ProcessMenu("menu-editor-map-properties", 1);
	FreeStringDesc(menu->Items[4].D.Text.text);
	delete menu->Items[4].D.Text.text;
	menu->Items[4].D.Text.text = NULL;
}
#endif

#if 0
/**
** Editor map properties input box callback
*/
static void EditorMapPropertiesEnterAction(Menuitem *mi, int key)
{
}
#endif

#if 0
/**
** Editor map properties ok button
*/
static void EditorMapPropertiesOk(void)
{
	Menu *menu;
	char *description;

	menu = CurrentMenu;

	description = menu->Items[2].D.Input.buffer;
	description[strlen(description)-3] = '\0';
	delete[] Map.Info.Description;
	Map.Info.Description = new_strdup(description);

	#if 0
	// MAPTODO
	// Change the terrain
	old = Map.Info.MapTerrain;
	if (old != menu->Items[6].D.Pulldown.curopt) {
		Map.Info.MapTerrain = menu->Items[6].D.Pulldown.curopt;
		delete[] Map.Info.MapTerrainName;
		Map.Info.MapTerrainName = new_strdup(TilesetWcNames[Map.Info.MapTerrain]);
		delete[] Map.TerrainName;
		Map.TerrainName = new_strdup(TilesetWcNames[Map.Info.MapTerrain]);
		Map.Tileset = Tilesets[Map.Info.MapTerrain];

		LoadTileset();
		SetPlayersPalette();
		PreprocessMap();
		LoadConstructions();
		LoadUnitTypes();
		LoadIcons();
		UpdateMinimapTerrain();
	}
	#endif


	EditorEndMenu();
}
#endif

#if 0
/**
** Editor player properties draw func
*/
static void EditorPlayerPropertiesDrawFunc(Menuitem *mi)
{
}
#endif

#if 0
/**
** Editor player properties input box callback
*/
static void EditorPlayerPropertiesEnterAction(Menuitem *mi, int key)
{
	if (mi->D.Input.nch > 0 && !isdigit(mi->D.Input.buffer[mi->D.Input.nch - 1])) {
		strcpy(mi->D.Input.buffer + (--mi->D.Input.nch), "~!_");
	}
}
#endif

#if 0
	/// Player type conversion from internal fc to menu number
static int PlayerTypesFcToMenu[] = {
	0,
	0,
	4,
	5,
	1,
	0,
	2,
	3,
};
#endif

#if 0
	/// Player type conversion from menu to internal fc number
static int PlayerTypesMenuToFc[] = {
	PlayerPerson,
	PlayerComputer,
	PlayerRescuePassive,
	PlayerRescueActive,
	PlayerNeutral,
	PlayerNobody,
};
#endif

#if 0
/**
**  Convert player ai from internal fc number to menu number
**
**  @param ainame  Ai name
**  @param menu    Pulldown menu item
*/
static int PlayerSetAiToMenu(char *ainame, MenuitemPulldown *menu)
{
	int i;

	menu->defopt = 0;
	for (i = 0; i < menu->noptions; ++i) {
		if(!strcmp(menu->options[i], ainame)) {
			menu->defopt = i;
		}
	}
	DebugPrint("Invalid Ai number: %s\n" _C_ ainame);
	return i;
}
#endif

#if 0
/**
**  Get the ai ident from the pulldown menu
**
**  @param menu  Pulldown menu item
*/
static char *PlayerGetAiFromMenu(MenuitemPulldown *menu)
{
	return menu->options[menu->curopt];
}
#endif

#if 0
/**
** Edit player properties menu
*/
static void EditorPlayerPropertiesMenu(void)
{
	Menu *menu;
	char gold[PlayerMax][15];
	char lumber[PlayerMax][15];
	char oil[PlayerMax][15];
	int i;

	menu = FindMenu("menu-editor-player-properties");

#define RACE_POSITION 21
#define TYPE_POSITION 38
#define AI_POSITION 55
#define GOLD_POSITION 72
#define LUMBER_POSITION 89
#define OIL_POSITION 106

	for (i = 0; i < PlayerMax; ++i) {
		menu->Items[RACE_POSITION + i].D.Pulldown.defopt = Map.Info.PlayerSide[i];
		menu->Items[TYPE_POSITION + i].D.Pulldown.defopt = PlayerTypesFcToMenu[Map.Info.PlayerType[i]];
		PlayerSetAiToMenu(Players[i].AiName, &menu->Items[AI_POSITION + i].D.Pulldown);
		sprintf(gold[i], "%d~!_", Players[i].Resources[GoldCost]);
		sprintf(lumber[i], "%d~!_", Players[i].Resources[WoodCost]);
		sprintf(oil[i], "%d~!_", Players[i].Resources[OilCost]);
		menu->Items[GOLD_POSITION + i].D.Input.buffer = gold[i];
		menu->Items[GOLD_POSITION + i].D.Input.nch = strlen(gold[i]) - 3;
		menu->Items[GOLD_POSITION + i].D.Input.maxch = 7;
		menu->Items[LUMBER_POSITION + i].D.Input.buffer = lumber[i];
		menu->Items[LUMBER_POSITION + i].D.Input.nch = strlen(lumber[i]) - 3;
		menu->Items[LUMBER_POSITION + i].D.Input.maxch = 7;
		menu->Items[OIL_POSITION + i].D.Input.buffer = oil[i];
		menu->Items[OIL_POSITION + i].D.Input.nch = strlen(oil[i]) - 3;
		menu->Items[OIL_POSITION + i].D.Input.maxch = 7;
	}

	ProcessMenu("menu-editor-player-properties", 1);

	for (i = 0; i < PlayerMax; ++i) {
		Map.Info.PlayerSide[i] = menu->Items[RACE_POSITION + i].D.Pulldown.curopt;
		Map.Info.PlayerType[i] = PlayerTypesMenuToFc[menu->Items[TYPE_POSITION + i].D.Pulldown.curopt];
		strcpy(Players[i].AiName, 
				PlayerGetAiFromMenu(&menu->Items[AI_POSITION + i].D.Pulldown));
		Players[i].Resources[GoldCost] = atoi(gold[i]);
		Players[i].Resources[WoodCost] = atoi(lumber[i]);
		Players[i].Resources[OilCost] = atoi(oil[i]);
	}
}
#endif

/**
** Edit resource properties
*/
void EditorEditResource(void)
{
	Menu *menu;
	char buf[13];
	char buf2[32];

	menu = FindMenu("menu-editor-edit-resource");

	sprintf(buf2, "Amount of %s:", DefaultResourceNames[UnitUnderCursor->Type->GivesResource]);
	menu->Items[0].D.Text.text = NewStringDesc(buf2);
	sprintf(buf, "%d~!_", UnitUnderCursor->ResourcesHeld);
	menu->Items[1].D.Input.buffer = buf;
	menu->Items[1].D.Input.nch = strlen(buf) - 3;
	menu->Items[1].D.Input.maxch = 6;
	ProcessMenu("menu-editor-edit-resource", 1);
	FreeStringDesc(menu->Items[0].D.Text.text);
	delete menu->Items[0].D.Text.text;
	menu->Items[0].D.Text.text = NULL;
}

#if 0
/**
** Key pressed in menu-editor-edit-resource
*/
static void EditorEditResourceEnterAction(Menuitem *mi,int key)
{
	if (mi->D.Input.nch > 0 && !isdigit(mi->D.Input.buffer[mi->D.Input.nch - 1])) {
		strcpy(mi->D.Input.buffer + (--mi->D.Input.nch), "~!_");
	} else if (key==10 || key==13) {
		EditorEditResourceOk();
	}
}
#endif

#if 0
/**
** Ok button from menu-editor-edit-resource
*/
static void EditorEditResourceOk(void)
{
	Menu *menu;
	unsigned value;

	menu = CurrentMenu;
	value = atoi(menu->Items[1].D.Input.buffer);
	if (value < 2500) {
		strcpy(menu->Items[1].D.Input.buffer, "2500~!_");
		menu->Items[1].D.Input.nch = 4;
		menu = FindMenu("menu-editor-error");
		menu->Items[1].D.Text.text = NewStringDesc("Must be greater than 2500");
	} else if (value > 655000) {
		strcpy(menu->Items[1].D.Input.buffer, "655000~!_");
		menu->Items[1].D.Input.nch = 6;
		menu = FindMenu("menu-editor-error");
		menu->Items[1].D.Text.text = NewStringDesc("Must be smaller than 655000");
	} else if (value / 2500 * 2500 != value) {
		value = (value + 1250)/ 2500 * 2500;
		sprintf(menu->Items[1].D.Input.buffer, "%d~!_", value);
		menu->Items[1].D.Input.nch = strlen(menu->Items[1].D.Input.buffer) - 3;
		menu = FindMenu("menu-editor-error");
		menu->Items[1].D.Text.text = NewStringDesc("Must be a multiple of 2500");
	} else {
		UnitUnderCursor->ResourcesHeld = value;
		GameMenuReturn();
		return;
	}
	ProcessMenu("menu-editor-error", 1);
	FreeStringDesc(menu->Items[1].D.Text.text);
	delete menu->Items[1].D.Text.text;
	menu->Items[1].D.Text.text = NULL;
}
#endif

#if 0
/**
** Cancel button from menu-editor-edit-resource
*/
static void EditorEditResourceCancel(void)
{
	GameMenuReturn();
}
#endif

/**
** Edit ai properties
*/
void EditorEditAiProperties(void)
{
	Menu *menu;

	menu = FindMenu("menu-editor-edit-ai-properties");
	if (UnitUnderCursor->Active) {
		menu->Items[1].D.Checkbox.Checked = 1;
		menu->Items[3].D.Checkbox.Checked = 0;
	} else {
		menu->Items[1].D.Checkbox.Checked = 0;
		menu->Items[3].D.Checkbox.Checked = 1;
	}

	ProcessMenu("menu-editor-edit-ai-properties", 1);
}

#if 0
/**
** Active or Passive gem clicked in menu-editor-edit-ai-properties
*/
static void EditorEditAiPropertiesCheckbox(Menuitem *mi)
{
	if (&mi->Menu->Items[1] == mi) {
		mi->D.Checkbox.Checked = 1;
		mi->Menu->Items[3].D.Checkbox.Checked = 0;
	} else {
		mi->D.Checkbox.Checked = 1;
		mi->Menu->Items[1].D.Checkbox.Checked = 0;
	}
}
#endif

#if 0
/**
** Ok button from menu-editor-edit-ai-properties
*/
static void EditorEditAiPropertiesOk(void)
{
	Menu *menu;

	menu = CurrentMenu;
	if (menu->Items[1].D.Checkbox.Checked) {
		UnitUnderCursor->Active = 1;
	} else {
		UnitUnderCursor->Active = 0;
	}
	GameMenuReturn();
}
#endif

#if 0
/**
** Cancel button from menu-editor-edit-ai-properties
*/
static void EditorEditAiPropertiesCancel(void)
{
	GameMenuReturn();
}
#endif

/**
** Save map from the editor
**
** @return 0 for success, -1 for error
*/
int EditorSaveMenu(void)
{
	Menu *menu;
	char path[PATH_MAX];
	char *s;
	char *p;
	int ret;

	ret = 0;
	menu = FindMenu("menu-editor-save");

	EditorCancelled = 0;

	strcpy(path, "~!_");
	menu->Items[3].D.Input.buffer = path;
	menu->Items[3].D.Input.maxch = PATH_MAX - 4;

	ProcessMenu("menu-editor-save", 1);

	if (!EditorCancelled) {
		if (Editor.WriteCompressedMaps && !strstr(path, ".gz")) {
			sprintf(path, "%s/%s.gz", ScenSelectPath, ScenSelectFileName);
		} else {
			sprintf(path, "%s/%s", ScenSelectPath, ScenSelectFileName);
		}
		if (EditorSaveMap(path) == -1) {
			ret = -1;
		} else {
			// Only change map path if we were able to save the map
			s = ScenSelectPath + strlen(ScenSelectPath);
			*s = '/';
			strcpy(s + 1, ScenSelectFileName); // Final map name with path
			p = ScenSelectPath + strlen(StratagusLibPath) + 1;
			strcpy(CurrentMapPath, p);
			*s = '\0';
		}
	}
	return ret;
}

#if 0
/**
**  Editor save init callback
*/
static void EditorSaveInit(Menu *menu)
{
	if (!*ScenSelectPath) {
		sprintf(ScenSelectPath, "%s/maps", StratagusLibPath);
	}
	EditorSaveLBInit(menu->Items + 1);
}
#endif

#if 0
/**
**  Editor save exit callback
*/
static void EditorSaveExit(Menu *menu)
{
	LBExit(menu->Items + 1);
}
#endif

#if 0
/**
** Editor save ok button
*/
static void EditorSaveOk(void)
{
	Menu *menu;
	Menuitem *mi;
	int i;

	menu = CurrentMenu;
	mi = &menu->Items[1];
	i = mi->D.Listbox.curopt;
	if (i < mi->D.Listbox.noptions) {
		if (mi->Menu->Items[3].D.Input.nch == 0 && ScenSelectPathName[0]) {
			strcat(ScenSelectPath, "/");
			strcat(ScenSelectPath, ScenSelectPathName);
			if (ScenSelectDisplayPath[0]) {
				strcat(ScenSelectDisplayPath, "/");
			}
			strcat(ScenSelectDisplayPath, ScenSelectPathName);
			EditorSaveLBInit(mi);
		} else {
			strcpy(ScenSelectFileName, menu->Items[3].D.Input.buffer); // Final map name
			ScenSelectFileName[strlen(ScenSelectFileName) - 3] = '\0';
			if (!strcasestr(ScenSelectFileName, ".smp")) {
				strcat(ScenSelectFileName, ".smp");
			}
			sprintf(TempPathBuf, "%s/%s.gz", ScenSelectPath, ScenSelectFileName);
			if (!access(TempPathBuf, F_OK)) {
				ProcessMenu("menu-editor-save-confirm", 1);
				if (EditorCancelled) {
					EditorCancelled = 0;
					return;
				}
			}
			EditorEndMenu();
		}
	}
}
#endif

#if 0
/**
** Editor save cancel button
*/
static void EditorSaveCancel(void)
{
	EditorCancelled = 1;
	EditorEndMenu();
}
#endif

#if 0
/**
** Editor save vertical slider action callback
*/
static void EditorSaveVSAction(Menuitem *mi)
{
}
#endif

#if 0
/**
** Editor save input callback
*/
static void EditorSaveEnterAction(Menuitem *mi, int key)
{
	Assert(mi->MiType == MiTypeInput);

	strncpy(ScenSelectFileName, mi->D.Input.buffer, mi->D.Input.nch);
	ScenSelectFileName[mi->D.Input.nch] = '\0';
	ScenSelectPathName[0] = '\0';
	SelectedFileExist = 0;
	if (mi->D.Input.nch != 0) {
		if (key == 10 || key == 13) {
			EditorSaveOk();
		}
	}
}
#endif

#if 0
/**
** Editor save confirm init callback
*/
static void EditorSaveConfirmInit(Menu *menu)
{
	menu->Items[2].D.Text.text = NewStringDesc(ScenSelectFileName);
}
#endif

#if 0
/**
** Editor save confirm ok button
*/
static void EditorSaveConfirmOk(void)
{
	FreeStringDesc(CurrentMenu->Items[2].D.Text.text);
	delete CurrentMenu->Items[2].D.Text.text;
	CurrentMenu->Items[2].D.Text.text = NULL;
	EditorEndMenu();
}
#endif

#if 0
/**
** Editor save confirm cancel button
*/
static void EditorSaveConfirmCancel(void)
{
	FreeStringDesc(CurrentMenu->Items[2].D.Text.text);
	delete[] CurrentMenu->Items[2].D.Text.text;
	CurrentMenu->Items[2].D.Text.text = NULL;
	EditorCancelled = 1;
	EditorEndMenu();
	SelectedFileExist = 0;
	ScenSelectFileName[0] = '\0';
	ScenSelectPathName[0] = '\0';
}
#endif

#if 0
/**
** Called from menu, to quit editor to menu.
**
** @todo Should check if modified file should be saved.
*/
static void EditorQuitToMenu(void)
{
	//QuitToMenu = 1;
	Editor.Running = EditorNotRunning;
	//CloseMenu();
	SelectedFileExist = 0;
	ScenSelectFileName[0] = '\0';
	ScenSelectPathName[0] = '\0';
}
#endif

#if 0
/**
** End menus state of the editor.
*/
static void EditorEndMenu(void)
{
	CursorOn = CursorOnUnknown;
	CurrentMenu = NULL;

	InterfaceState = IfaceStateNormal;
	EditorUpdateDisplay();
	InterfaceState = IfaceStateMenu;
}
#endif

#if 0
/**
** Net error menu
**
** @param error Error message
*/
static void NetErrorMenu(char *error)
{
    	Menu *menu;

	menu = FindMenu("menu-net-error");
	menu->Items[1].D.Text.text = NewStringDesc(error);
	ProcessMenu("menu-net-error", 1);
	FreeStringDesc(menu->Items[1].D.Text.text);
	delete menu->Items[1].D.Text.text;
	menu->Items[1].D.Text.text = NULL;
}
#endif

/**
** Error menu
**
** @param error Error message
*/
void ErrorMenu(char *error)
{
	Menu *menu;
	int oldx;
	int oldy;

	menu = FindMenu("menu-net-error");
	oldx = menu->X;
	oldy = menu->Y;
	menu->X = (Video.Width - menu->Width) / 2;
	menu->Y = (Video.Height - menu->Height) / 2;
	menu->Items[1].D.Text.text = NewStringDesc(error);
	ProcessMenu("menu-net-error", 1);
	FreeStringDesc(menu->Items[1].D.Text.text);
	delete menu->Items[1].D.Text.text;
	menu->Items[1].D.Text.text = NULL;
	menu->X = oldx;
	menu->Y = oldy;
}

/*----------------------------------------------------------------------------
--  Metaserver
----------------------------------------------------------------------------*/

#if 0
/**
**  FIXME: docu
*/
static void MultiGameMasterReport(void)
{
// CloseMenu();

	ProcessMenu("metaserver-list", 1);
	if (GuiGameStarted) {
		GameMenuReturn();
	}

}
#endif

#if 0
/**
**  Menu for Mater Server Game list.
*/
static void ShowMetaServerList(void)
{
	//CloseMenu();

	GuiGameStarted = 0;
	ProcessMenu("metaserver-list", 1);
	if (GuiGameStarted) {
		GameMenuReturn();
	}
}
#endif

#if 0
/**
**  Multiplayer server menu init callback
**
**  Mohydine: Right now, because I find it simpler, the client is sending
**            n commands, one for each online game.
**  @todo: well, redo this :)
*/
static void MultiMetaServerGameSetupInit(Menu *menu)
{
	int i;
	int j;
	int k;
	int numparams;
	int nummenus;
	char *parameter;
	char *reply;
	char *port;

	SendMetaCommand("NumberOfGames", "");

	reply = NULL;
	// receive
	// check okay
	if (RecvMetaReply(&reply) == -1) {
		//TODO: Notify player that connection was aborted...
		nummenus = 1;
	} else {
		for (i = 0; i < 3; ++i) {
			GetMetaParameter(reply, 0, &parameter);
			nummenus = atoi(parameter);
			delete[] parameter;
			if (nummenus == 0) {
				RecvMetaReply(&reply);
			}
			else {
				break;
			}
		}

	}

	--nummenus;
	// Meta server only sends matching version
	// Only Displays games from Matching version

	i = 1;
	k = 0;
	numparams = 5; // TODO: To be changed if more params are sent

	// Retrieve list of online game from the meta server
	for (j = 4; j <= nummenus * (numparams + 1); j += numparams + 1) { // loop over the number of items in the menu
		// TODO: hard coded.
		// Check if connection to meta server is there.

		SendMetaCommand("GameNumber","%d\n",k + 1);
		i = RecvMetaReply(&reply);
		if (i == 0) {
			// fill the menus with the right info.
			menu->Items[j].D.Text.text = NULL;
			menu->Items[j + 1].D.Text.text = NULL;
			menu->Items[j + 2].D.Text.text = NULL;
			menu->Items[j + 3].D.Text.text = NULL;
			menu->Items[j + 4].D.Text.text = NULL;
			menu->Items[j + 5].Flags = MI_FLAGS_INVISIBLE;
		} else {
			GetMetaParameter(reply, 0, &parameter);       // Player Name
			menu->Items[j].D.Text.text = NewStringDesc(parameter);
			delete[] parameter;
			GetMetaParameter(reply, 3, &parameter);       // IP
			GetMetaParameter(reply, 4, &port);            // port
			sprintf(parameter, "%s:%s", parameter, port); // IP:Port
			menu->Items[j + 1].D.Text.text = NewStringDesc(parameter);
			delete[] parameter;
			delete[] port;
			GetMetaParameter(reply, 6, &parameter);
			menu->Items[j + 2].D.Text.text = NewStringDesc(parameter);
			delete[] parameter;
			GetMetaParameter(reply, 7, &parameter);
			menu->Items[j + 3].D.Text.text = NewStringDesc(parameter);
			delete[] parameter;
			GetMetaParameter(reply, 8, &parameter);
			menu->Items[j + 4].D.Text.text = NewStringDesc(parameter);
			menu->Items[j + 5].D.Checkbox.Checked = 0;
			delete[] parameter;
		}
		++k;
	}

	// Don't display slots not in use
	// FIXME: HardCoded Number of Items in list
	// 5 is the hardcoded value
	for (; j <= numparams * 5; j += numparams + 1) {
		// fill the menus with the right info.
		menu->Items[j].D.Text.text = NULL;
		menu->Items[j + 1].D.Text.text = NULL;
		menu->Items[j + 2].D.Text.text = NULL;
		menu->Items[j + 3].D.Text.text = NULL;
		menu->Items[j + 4].D.Text.text = NULL;
		menu->Items[j + 5].Flags = MI_FLAGS_DISABLED;
	}
}
#endif

#if 0
/**
**  Multiplayer server menu exit callback
*/
static void MultiMetaServerGameSetupExit(Menu *menu)
{
	int i;
	int j;
	int numparam;
	int nummenu;

	numparam = 5;
	nummenu = 6;
	for (j = 4; j <= numparam * nummenu; ++j) {
		for (i = 0; i < numparam; ++i) {
			FreeStringDesc(menu->Items[i + j].D.Text.text);
			delete menu->Items[i + j].D.Text.text;
			menu->Items[i + j].D.Text.text = NULL;
		}
	}
// CloseMenu();
// CloseMenu();
}
#endif

#if 0
/**
**  Action taken when a player select an online game
*/
static void SelectGameServer(Menuitem *mi)
{
	char server_host_buffer[64];
	char *port;
	int j;
	char *tmp;

	j = mi - mi->Menu->Items;
	mi->Menu->Items[j].D.Checkbox.Checked = 0;
	//CloseMenu();

	tmp = EvalString(mi->Menu->Items[j - 4].D.Text.text);
	strcpy(server_host_buffer, tmp);
	delete[] tmp;

	// Launch join directly
	if ((port = strchr(server_host_buffer, ':')) != NULL) {
		NetworkPort = atoi(port + 1);
		port[0] = 0;
	}

	// Now finally here is the address
// server_host_buffer[menu->Items[1].D.Input.nch] = 0;
	if (NetworkSetupServerAddress(server_host_buffer)) {
		NetErrorMenu("Unable to lookup host.");
		ProcessMenu("metaserver-list", 1);
		return;
	}
	NetworkInitClientConnect();
	if (!NetConnectRunning) {
		TerminateNetConnect();
		return;
	}

	delete[] NetworkArg;
	NetworkArg = new_strdup(server_host_buffer);

	// Here we really go...
	ProcessMenu("menu-net-connecting", 1);

	if (GuiGameStarted) {
		//CloseMenu();
	}
}
#endif

#if 0
/**
**  Action to add a game server on the meta-server.
*/
static void AddGameServer(void)
{
	// send message to meta server. meta server will detect IP address.
	// Meta-server will return "BUSY" if the list of online games is busy.

	SendMetaCommand("AddGame", "%s\n%d\n%s\n%s\n%s\n%s\n",
		"IP", NetworkPort, "Name", "Map", "Players", "Free");

	// FIXME: Get Reply from Queue
}
#endif

/**
**  Action to add a game server on the meta-server.
*/
static void ChangeGameServer(void)
{
	int i;
	int freespots;
	int players;

	// send message to meta server. meta server will detect IP address.
	// Meta-server will return "ERR" if the list of online games is busy.

	freespots = 0;
	players = 0;
	for (i = 0; i < PlayerMax - 1; ++i) {
		if (Map.Info.PlayerType[i] == PlayerPerson) {
			++players;
		}
		if (ServerSetupState.CompOpt[i] == 0) {
			++freespots;
		}
	}
	SendMetaCommand("ChangeGame", "%s\n%s\n%d\n%d\n",
		"Name", ScenSelectFileName, players, freespots - 1);

	// FIXME: Get Reply from Queue
}

#if 0
/**
**  FIXME: docu
*/
static int MetaServerConnectError(void)
{
	Invalidate();
	NetErrorMenu("Cannot Connect to Meta-Server");
	return 0;
}
#endif

#if 0
/**
**  Close MetaServer connection
*/
static void MultiMetaServerClose(void)
{
	MetaClose();
	MetaServerInUse = 0;
	//CloseMenu();
}
#endif

//@}
