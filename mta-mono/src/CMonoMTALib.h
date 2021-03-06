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

class CMonoMTALib;

#ifndef __CMONOMTALIB_H
#define __CMONOMTALIB_H

#include "CMonoDomain.h"
#include "CMonoClass.h"

class CMonoMTALib
{
private:
	MonoImage*			m_pImage;
	CMonoDomain*		m_pDomain;

public:
	CMonoClass*			Color;
	CMonoClass*			Vector2;
	CMonoClass*			Vector3;

public:
						CMonoMTALib			( CMonoDomain* pDomain );
						~CMonoMTALib		( void );

	CMonoClass*			GetClass			( const char* szName ) const;
	CMonoClass*			GetClass			( const char* szNameSpace, const char* szName ) const;

	inline CMonoDomain*	GetDomain			( void ) const	{ return this->m_pDomain; }
};

#endif