/*
	PROJECT		<>	SA:MP Anticheat Plug-in
	LICENSE		<>	See LICENSE in the top level directory.
	AUTHOR(S)	<>	Lorenc_ (zeelorenc@hotmail.com)
	PURPOSE		<>  Providing datastructures for the internal SA:MP Server.


	Copyright (C) 2014 SA:MP Anticheat Plug-in.

	The Project is available on https://github.com/myudev/SAMPAC

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License along
	with this program; if not, see <http://www.gnu.org/licenses/>.
*/

#include 							< anticheat\global >
#include 							< anticheat\player >

#define squared(%0)					(%0*%0)

static const Float: aWaterPlaces[ 20 ] [ 4 ] =
{
    { 30.00, 2313.00, -1417.0, 23.000 }, { 15.00, 1280.00, -773.00, 1083.0 }, { 25.00, 2583.00, 2385.00, 15.000 }, { 20.00, 225.000, -1187.0, 74.000 },
    { 50.00, 1973.00, -1198.0, 17.000 }, { 180.0, 1937.00, 1589.00, 9.0000 }, { 55.00, 2142.00, 1285.00, 8.0000 }, { 45.00, 2150.00, 1132.00, 8.0000 },
    { 55.00, 2089.00, 1915.00, 10.000 }, { 32.00, 2531.00, 1567.00, 9.0000 }, { 21.00, 2582.00, 2385.00, 17.000 }, { 33.00, 1768.00, 2853.00, 10.000 },
    { 47.00, -2721.0, -466.00, 4.0000 }, { 210.0, -671.00, -1898.0, 6.0000 }, { 45.00, 1240.00, -2381.0, 9.0000 }, { 50.00, 1969.00, -1200.0, 18.000 },
    { 10.00, 513.000, -1105.0, 79.000 }, { 20.00, 193.000, -1230.0, 77.000 }, { 30.00, 1094.00, -672.00, 113.00 }, { 20.00, 1278.00, -805.00, 87.000 }
};

stock vCheckForFlyHacks( playerid, iTicks )
{	
	if( iTicks > p_FlyHacksTick[ playerid ] )
	{
		new
			pSurfingObject = GetPlayerSurfingObjectID( playerid ),
			pSurfingVehicle = GetPlayerSurfingVehicleID( playerid )
		;
		
		if( pSurfingVehicle == INVALID_VEHICLE_ID && pSurfingObject == INVALID_OBJECT_ID )
	    {
	        new 
	        	iAnimation = GetPlayerAnimationIndex( playerid );
	     
	     	if( iAnimation == 1538 || iAnimation == 1539 || iAnimation == 1543 )
	     	{
	     		if( !ac_IsPlayerInWater( playerid ) ) 
	     		{
	     			if( p_FlyHacksWarns{ playerid }++ >= 2 )
						CallLocalFunction( "OnPlayerCheatDetected", "dd", playerid, CHEAT_TYPE_FLYHACKS ), p_FlyHacksWarns{ playerid } = 3;
	     		}
	     		else p_FlyHacksWarns{ playerid } = 0;
	     	}
		}

		p_FlyHacksTick[ playerid ] = iTicks + 1000;
	}
}

stock ac_IsPlayerInWater( playerid )
{
    static
    	Float: X, Float: Y, Float: Z, i;

    if( GetPlayerPos( playerid, X, Y, Z ) )
    {
	 	if( ac_IsPointInArea( X, Y, 2347.080, 521.70, 2372.65, 545.1971 ) || ac_IsPointInArea( X, Y, 2286.61, 521.70, 2301.45, 545.1971 ) ) 
	 		return false; // Kar Fix

	 	if( ac_PointDistance( X, Y, -965.0, 2438.0 ) <= squared( 700.0 ) && Z < 44.0 )
	    	return true;
	  
		for( i = 0; i < sizeof( aWaterPlaces ); i++ )
		    if( ac_PointDistance( X, Y, aWaterPlaces[ i ] [ 1 ], aWaterPlaces[ i ] [ 2 ] ) <= squared( aWaterPlaces[ i ] [ 0 ] ) && Z < aWaterPlaces[ i ] [ 3 ] )
				return true;

	    return Z < 1.9 ? !( ac_PointDistance( X, Y, 618.4129, 863.3164 ) < squared( 200.0 ) ) : false;
	}
	return false;
}