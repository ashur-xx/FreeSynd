/************************************************************************
 *                                                                      *
 *  FreeSynd - a remake of the classic Bullfrog game "Syndicate".       *
 *                                                                      *
 *   Copyright (C) 2005  Stuart Binge  <skbinge@gmail.com>              *
 *   Copyright (C) 2005  Joost Peters  <joostp@users.sourceforge.net>   *
 *   Copyright (C) 2006  Trent Waddington <qg@biodome.org>              *
 *   Copyright (C) 2006  Tarjei Knapstad <tarjei.knapstad@gmail.com>    *
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

#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include "mapobject.h"

class VehicleInstance;

/*!
 * Vehicle class.
 */
class Vehicle {
public:
    Vehicle(const char *vehicle_name, int first_anim);

    const char *name() { return name_.c_str(); }

    void draw(int x, int y, int dir, int frame);
    void drawOnFire(int x, int y, int dir, int frame);
    void drawBurnt(int x, int y, int dir, int frame);

    VehicleInstance *createInstance(int map);

protected:
    std::string name_;
    int anims_;
};

/*!
 * Vehicle instance class.
 */
class VehicleInstance : public ShootableMovableMapObject {
public:
    VehicleInstance(Vehicle *vehicle, int m);
    virtual ~VehicleInstance() {}

    bool animate(int elapsed);
    void draw(int x, int y);

protected:
    Vehicle *vehicle_;

    bool walkable(int x, int y, int z);
};

#endif
