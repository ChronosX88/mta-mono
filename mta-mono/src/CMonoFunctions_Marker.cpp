/*********************************************************
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

#include "StdInc.h"
#include "CMonoFunctions.h"

// Marker create/destroy functions
DWORD CMonoFunctions::Marker::Create( MonoObject* pPosition, MonoString* msType, float fSize, MonoObject* pColor, DWORD pVisibleTo )
{
	if( RESOURCE )
	{
		const char* szType = mono_string_to_utf8( msType );

		return (DWORD)CLuaFunctionDefinitions::CreateMarker( RESOURCE->GetLua(), Vector3( pPosition ), szType, fSize, CMonoObject::GetColor( pColor ), (void*)pVisibleTo );
	}

	return NULL;
}


// Marker get functions
unsigned int CMonoFunctions::Marker::GetCount()
{
	if( RESOURCE )
	{
		unsigned int uiCount;
		
		if( CLuaFunctionDefinitions::GetMarkerCount( RESOURCE->GetLua(), uiCount ) )
		{
			return uiCount;
		}
	}

	return 0;
}

MonoString* CMonoFunctions::Marker::GetType( DWORD pUserData )
{
	if( RESOURCE )
	{
		char* szType = NULL;
		
		if( CLuaFunctionDefinitions::GetMarkerType( RESOURCE->GetLua(), (void*)pUserData, szType ) )
		{
			return RESOURCE->GetDomain()->NewString( szType );
		}
	}

	return NULL;
}

float CMonoFunctions::Marker::GetSize( DWORD pUserData )
{
	if( RESOURCE )
	{
		float fSize;
		
		if( CLuaFunctionDefinitions::GetMarkerSize( RESOURCE->GetLua(), (void*)pUserData, fSize ) )
		{
			return fSize;
		}
	}

	return 0.0f;
}

MonoObject* CMonoFunctions::Marker::GetColor( DWORD pUserData )
{
	if( RESOURCE )
	{
		SColor outColor;
		
		if( CLuaFunctionDefinitions::GetMarkerColor( RESOURCE->GetLua(), (void*)pUserData, outColor ) )
		{
			return RESOURCE->GetDomain()->GetMTALib()->Color->New( outColor );
		}
	}

	return NULL;
}

MonoObject* CMonoFunctions::Marker::GetTarget( DWORD pUserData )
{
	if( RESOURCE )
	{
		Vector3 vecPosition;
		
		if( CLuaFunctionDefinitions::GetMarkerTarget( RESOURCE->GetLua(), (void*)pUserData, vecPosition ) )
		{
			return RESOURCE->GetDomain()->GetMTALib()->Vector3->New( vecPosition );
		}
	}

	return NULL;
}

MonoString* CMonoFunctions::Marker::GetIcon( DWORD pUserData )
{
	if( RESOURCE )
	{
		char* szIcon = NULL;
		
		if( CLuaFunctionDefinitions::GetMarkerIcon( RESOURCE->GetLua(), (void*)pUserData, szIcon ) )
		{
			return RESOURCE->GetDomain()->NewString( szIcon );
		}
	}

	return NULL;
}


// Marker set functions
bool CMonoFunctions::Marker::SetType( DWORD pUserData, MonoString* msType )
{
	if( RESOURCE )
	{
		const char* szType = mono_string_to_utf8( msType );
		
		return CLuaFunctionDefinitions::SetMarkerType( RESOURCE->GetLua(), (void*)pUserData, szType );
	}

	return false;
}

bool CMonoFunctions::Marker::SetSize( DWORD pUserData, float fSize )
{
	if( RESOURCE )
	{
		return CLuaFunctionDefinitions::SetMarkerSize( RESOURCE->GetLua(), (void*)pUserData, fSize );
	}

	return false;
}

bool CMonoFunctions::Marker::SetColor( DWORD pUserData, MonoObject* pColor )
{
	if( RESOURCE )
	{
		return CLuaFunctionDefinitions::SetMarkerColor( RESOURCE->GetLua(), (void*)pUserData, CMonoObject::GetColor( pColor ) );
	}

	return false;
}

bool CMonoFunctions::Marker::SetTarget( DWORD pUserData, MonoObject* pTarget )
{
	if( RESOURCE )
	{
		return CLuaFunctionDefinitions::SetMarkerTarget( RESOURCE->GetLua(), (void*)pUserData, Vector3( pTarget ) );
	}

	return false;
}

bool CMonoFunctions::Marker::SetIcon( DWORD pUserData, MonoString* msIcon )
{
	if( RESOURCE )
	{
		const char* szIcon = mono_string_to_utf8( msIcon );
		
		return CLuaFunctionDefinitions::SetMarkerType( RESOURCE->GetLua(), (void*)pUserData, szIcon );
	}

	return false;
}
