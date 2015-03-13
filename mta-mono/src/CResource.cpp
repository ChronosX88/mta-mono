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

#include "CResource.h"
#include "CResourceManager.h"
#include "include/ILuaModuleManager.h"
#include "lua/CLuaFunctionDefinitions.h"

extern ILuaModuleManager10	*g_pModuleManager;
extern CResourceManager	*g_pResourceManager;

CResource::CResource( lua_State *pLuaVM, string sName )
{
	this->m_pLuaVM				= pLuaVM;
	this->m_sName				= sName;

	this->m_pMonoAssembly		= NULL;
	this->m_pMonoAssemblyLib	= NULL;
	this->m_pMonoGCHandle		= NULL;
	this->m_pMonoDomain			= NULL;
	this->m_pMonoImage			= NULL;
	this->m_pMonoImageLib		= NULL;
	this->m_pMonoClass			= NULL;
}

CResource::~CResource( void )
{
	if( this->m_pMonoGCHandle )
	{
		mono_gchandle_free( this->m_pMonoGCHandle );
	}

	if( this->m_pMonoDomain )
	{
		mono_domain_unload( this->m_pMonoDomain );
	}

	g_pResourceManager->RemoveFromList( this );
}

bool CResource::Init( void )
{
	if( this->m_pLuaVM )
	{
		string sDirectory	( "mods/deathmatch/resources/[ire]/" + this->m_sName + "/" );
		string sPath		( sDirectory + this->m_sName + ".dll" );
		string sNamespace	( this->m_sName );
		string sClass		( "Program" );

		this->m_pMonoDomain			= mono_domain_create_appdomain( const_cast< char* >( this->m_sName.c_str() ), NULL );

		if( !this->m_pMonoDomain )
		{
			g_pModuleManager->ErrorPrintf( "%s - failed to create appdomain\n", this->m_sName.c_str() );

			return false;
		}

		mono_domain_set( this->m_pMonoDomain, false );

		this->m_pMonoAssemblyLib	= mono_domain_assembly_open( this->m_pMonoDomain, ( sDirectory + "MultiTheftAuto.dll" ).c_str() );

		if( this->m_pMonoAssemblyLib )
		{
			this->m_pMonoImageLib	= mono_assembly_get_image( this->m_pMonoAssemblyLib );
		}

		this->m_pMonoAssembly		= mono_domain_assembly_open( this->m_pMonoDomain, sPath.c_str() );
		
		if( !this->m_pMonoAssembly )
		{
			g_pModuleManager->ErrorPrintf( "failed to open assembly '%s.dll'\n", this->m_sName.c_str() );

			return false;
		}

		this->m_pMonoImage	= mono_assembly_get_image( this->m_pMonoAssembly );
		this->m_pMonoClass	= mono_class_from_name( this->m_pMonoImage, sNamespace.c_str(), sClass.c_str() );

		MonoObject *pMonoObject = mono_object_new( this->m_pMonoDomain, this->m_pMonoClass );

		this->m_pMonoGCHandle = mono_gchandle_new( pMonoObject, true );

		mono_runtime_object_init( pMonoObject );

		return true;
	}

	return false;
}

void CResource::OnStopping( void )
{
}

void CResource::DoPulse( void )
{
}

bool CResource::RegisterFunction( const char *szFunctionName, lua_CFunction Func )
{
	if( !g_pModuleManager->RegisterFunction( this->m_pLuaVM, szFunctionName, Func ) )
	{
		g_pModuleManager->ErrorPrintf( "Failed to register function '%s' for %s", szFunctionName, this->m_sName.c_str() );

		return false;
	}

	return true;
}

CMonoClass* CResource::GetClassFromName( const char* szNamespace, const char* szName )
{
	MonoClass* pMonoClass = mono_class_from_name( this->m_pMonoImage, szNamespace, szName );

	if( !pMonoClass )
	{
		pMonoClass = mono_class_from_name( this->m_pMonoImageLib, szNamespace, szName );
	}

	if( pMonoClass )
	{
		return new CMonoClass( pMonoClass );
	}

	return NULL;
}

CMonoObject* CResource::NewObject( const char* szNamespace, const char* szName )
{
	CMonoClass* pClass = this->GetClassFromName( szNamespace, szName );
			
	if( pClass )
	{
		CMonoObject* pObject = pClass->New( mono_domain_get() );
				
		if( pObject )
		{
			return pObject;
		}
		else
		{
			g_pModuleManager->ErrorPrintf( "%s:%d: failed to create instance of '%s::%s'\n", __FILE__, __LINE__, szNamespace, szName );
		}
	}
	else
	{
		g_pModuleManager->ErrorPrintf( "%s:%d: class '%s::%s' not found\n", __FILE__, __LINE__, szNamespace, szName );
	}

	return NULL;
}

CMonoObject* CResource::NewObject( SColor& pColor )
{
	CMonoClass* pClass = this->GetClassFromName( "MultiTheftAuto", "Color" );
			
	if( pClass )
	{
		CMonoObject* pObject = pClass->New( mono_domain_get(), pColor );
				
		if( pObject )
		{
			return pObject;
		}
		else
		{
			g_pModuleManager->ErrorPrintf( "%s:%d: failed to create instance of 'MultiTheftAuto::Vector2'\n", __FILE__, __LINE__ );
		}
	}
	else
	{
		g_pModuleManager->ErrorPrintf( "%s:%d: class 'MultiTheftAuto::Vector2' not found\n", __FILE__, __LINE__ );
	}

	return NULL;
}

CMonoObject* CResource::NewObject( Vector2& vecVector )
{
	CMonoClass* pClass = this->GetClassFromName( "MultiTheftAuto", "Vector2" );
			
	if( pClass )
	{
		CMonoObject* pObject = pClass->New( mono_domain_get(), vecVector );
				
		if( pObject )
		{
			return pObject;
		}
		else
		{
			g_pModuleManager->ErrorPrintf( "%s:%d: failed to create instance of 'MultiTheftAuto::Vector2'\n", __FILE__, __LINE__ );
		}
	}
	else
	{
		g_pModuleManager->ErrorPrintf( "%s:%d: class 'MultiTheftAuto::Vector2' not found\n", __FILE__, __LINE__ );
	}

	return NULL;
}

CMonoObject* CResource::NewObject( Vector3& vecVector )
{
	CMonoClass* pClass = this->GetClassFromName( "MultiTheftAuto", "Vector3" );
			
	if( pClass )
	{
		CMonoObject* pObject = pClass->New( mono_domain_get(), vecVector );
				
		if( pObject )
		{
			return pObject;
		}
		else
		{
			g_pModuleManager->ErrorPrintf( "%s:%d: failed to create instance of 'MultiTheftAuto::Vector3'\n", __FILE__, __LINE__ );
		}
	}
	else
	{
		g_pModuleManager->ErrorPrintf( "%s:%d: class 'MultiTheftAuto::Vector3' not found\n", __FILE__, __LINE__ );
	}

	return NULL;
}

CMonoObject* CResource::NewObject( const char* szNamespace, const char* szName, void** args, int argc )
{
	CMonoClass* pClass = this->GetClassFromName( szNamespace, szName );
			
	if( pClass )
	{
		CMonoObject* pObject = pClass->New( mono_domain_get(), args, argc );
				
		if( pObject )
		{
			return pObject;
		}
		else
		{
			g_pModuleManager->ErrorPrintf( "%s:%d: failed to create instance of '%s::%s'\n", __FILE__, __LINE__, szNamespace, szName );
		}
	}
	else
	{
		g_pModuleManager->ErrorPrintf( "%s:%d: class '%s::%s' not found\n", __FILE__, __LINE__, szNamespace, szName );
	}

	return NULL;
}
