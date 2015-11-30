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

#include "CMonoMTALib.h"

CMonoMTALib::CMonoMTALib( CMonoDomain* pDomain )
{
	this->m_pClass		= nullptr;
	this->m_pObject		= nullptr;

	this->m_pAssembly	= nullptr;
	this->m_pImage		= nullptr;
	this->m_pDomain		= pDomain;

	this->m_uiGCHandle	= 0;

	string strPath( CMonoInterface::GetBinariesDirectory() + "/" + pDomain->GetResource()->GetName() + "/MultiTheftAuto.dll" );

	this->m_pAssembly	= pDomain->OpenAssembly( strPath.c_str() );

	if( this->m_pAssembly )
	{
		this->m_pImage	= mono_assembly_get_image( this->m_pAssembly );

		if( this->m_pImage )
		{
			this->Color			= this->GetClass( "Color" );
			this->Vector2		= this->GetClass( "Vector2" );
			this->Vector3		= this->GetClass( "Vector3" );

			this->m_pClass		= this->GetClass( "MultiTheftAuto" );
			
			if( this->m_pClass )
			{
				this->m_pObject = this->m_pClass->New();

				//this->m_uiGCHandle = mono_gchandle_new( this->m_pObject, true );
			}
		}
	}
}

CMonoMTALib::~CMonoMTALib( void )
{
	if( this->m_uiGCHandle )
	{
		mono_gchandle_free( this->m_uiGCHandle );

		this->m_uiGCHandle = 0;
	}

	SAFE_DELETE( this->Color );
	SAFE_DELETE( this->Vector2 );
	SAFE_DELETE( this->Vector3 );
	SAFE_DELETE( this->m_pClass );

	this->m_pDomain		= nullptr;
	this->m_pAssembly	= nullptr;
	this->m_pImage		= nullptr;
	this->m_pObject		= nullptr;
}

CMonoClass* CMonoMTALib::GetClass( const char* szName )
{
	return this->GetDomain()->FindOrAdd( mono_class_from_name( this->m_pImage, "MultiTheftAuto", szName ) );
}

CMonoClass* CMonoMTALib::GetClass( const char* szNameSpace, const char* szName )
{
	char szBuffer[ 128 ];

	sprintf( szBuffer, "MultiTheftAuto.%s", szNameSpace );

	return this->GetDomain()->FindOrAdd( mono_class_from_name( this->m_pImage, szBuffer, szName ) );
}