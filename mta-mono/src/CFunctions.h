/*********************************************************
*
*  Multi Theft Auto: San Andreas - Deathmatch
**********************************************************
*
*  Copyright � 2013, Innovation Roleplay Engine. 
*
*  All Rights Reserved.
*
*  Redistribution and use in source and binary forms,
*  with or without modification,
*  is permitted only for authors.
*
*********************************************************/

class CFunctions;

#ifndef __CFUNCTIONS_H
#define __CFUNCTIONS_H

#include "CModule.h"
#include "CResource.h"
#include "CResourceManager.h"

extern CModule* g_pModule;

class CFunctions
{
public:
		static int		monoInit				( lua_State* pLuaVM );
		static int		monoEventHandler		( lua_State* pLuaVM );
		static int		monoCommandHandler		( lua_State* pLuaVM );

};
#endif
