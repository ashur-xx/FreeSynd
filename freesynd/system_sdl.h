/************************************************************************
 *                                                                      *
 *  FreeSynd - a remake of the classic Bullfrog game "Syndicate".       *
 *                                                                      *
 *   Copyright (C) 2005  Stuart Binge  <skbinge@gmail.com>              *
 *   Copyright (C) 2005  Joost Peters  <joostp@users.sourceforge.net>   *
 *   Copyright (C) 2006  Trent Waddington <qg@biodome.org>              *
 *   Copyright (C) 2010  Benoit Blancard <benblan@users.sourceforge.net>*
 *                                                                      *
 *    This program is free software;  you can redistribute it and / or  *
 *  modify it  under the  terms of the  GNU General  Public License as  *
 *  published by the Free Software Foundation; either version 2 of the  *
 *  License, or (at your option) any later version.                     *
 *                                                                      *
 *    This program is  distributed in the hope that it will be useful,  *
 *  but WITHOUT  ANY WARRANTY;  without even  the implied  warranty of  *
 *  MERCHANTABILITY  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  *
 *  General Public License for more details.                            *
 *                                                                      *
 *    You can view the GNU  General Public License, online, at the GNU  *
 *  project's  web  site;  see <http://www.gnu.org/licenses/gpl.html>.  *
 *  The full text of the license is also included in the file COPYING.  *
 *                                                                      *
 ************************************************************************/

#ifndef SYSTEM_SDL_H
#define SYSTEM_SDL_H

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL/SDL.h>
#endif

#include "common.h"
#include "system.h"

//! Implementation of the System interface for SDL.
/*!
 * This class implements the System interface based on the SDL library.
 *  - Mouse Cursor\n
 *    In order to display colorfull cursors, the SDL cursor display is disabled
 *    and is manually managed by this class.\n
 *    A surface is loaded with a collection of sprites, and every time the 
 *    mouse moves, the corresponding sprite is blit on screen at the
 *    mouse coordinates.\n
 *    If the SDLSystem fails to load the cursor surface, the default SDL cursor
 *    will be used, but not change will affect the cursor, except hide/show.
 */
class SystemSDL : public System {
public:
    SystemSDL(int depth = 32);
    ~SystemSDL();

    void updateScreen();
    void handleEvents();
    void delay(int msec);

    void setPalette6b3(const uint8 *pal, int cols = 256);
    void setPalette8b3(const uint8 *pal, int cols = 256);
    void setColor(uint8 index, uint8 r, uint8 g, uint8 b);

    void hideCursor();
    void showCursor();
    void useMenuCursor();
    void usePointerCursor();
    void useTargetCursor();
    void usePickupCursor();

protected:
    //! Loads the graphic file that contains the cursor sprites.
    bool loadCursorSprites();

protected:
    /*! A constant that holds the cursor icon width and height.*/
    static const int CURSOR_WIDTH;
    int depth_;
    bool scale_;
    /*! Cursor visibility.*/
    bool cursor_visible_;
    /*! Cursor screen coordinates. */
    int cursor_x_;
    /*! Cursor screen coordinates. */
    int cursor_y_;
    /*! Current cursor hotspot.*/
    int cursor_hs_x_;
    /*! Current cursor hotspot.*/
    int cursor_hs_y_;

    SDL_Surface *screen_surf_;
    SDL_Surface *temp_surf_;
    /*! 
     * A surface that holds all cursors
     * images.
     */
    SDL_Surface *cursor_surf_;
    /*! A rect that identify the part of
     * the cursor surface for the current cursor.*/
    SDL_Rect cursor_rect_;
    /*! A flag that tells that cursor must be updated because
     the mouse has moved or the cursor has changed.*/
    bool update_cursor_;
};

#endif
