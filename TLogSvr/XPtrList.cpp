// XPtrList.cpp: implementation of the CXPtrList class.
////////////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "XPtrList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

////////////////////////////////////////////////////////////////////////////////////////
// Construction/Destruction
////////////////////////////////////////////////////////////////////////////////////////
CXPtrList::CXPtrList()
{
	::InitializeCriticalSection(&m_cs);
}

CXPtrList::~CXPtrList()
{
	::DeleteCriticalSection(&m_cs);
}


////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////
void CXPtrList::AddTail(void* pObject)
{
	EnterCriticalSection(&m_cs);

		CPtrList::AddTail(pObject);

	LeaveCriticalSection(&m_cs);
}

////////////////////////////////////////////////////////////////////////////////////////
//	Remove Head
////////////////////////////////////////////////////////////////////////////////////////
void* CXPtrList::RemoveHead()
{
	void* pObject = NULL;

	EnterCriticalSection(&m_cs);

		//	pObject = CPtrList::RemoveHead();

		//	2004.04.19 Duke Kim 추가		
		if( !CPtrList::IsEmpty() )
			pObject = CPtrList::RemoveHead();


	LeaveCriticalSection(&m_cs);

	return pObject;
}


////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////
void CXPtrList::RemoveAll()
{
	EnterCriticalSection(&m_cs);

		CPtrList::RemoveAll();

	LeaveCriticalSection(&m_cs);
}

////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////
POSITION CXPtrList::Find(void *pObject)
{
	POSITION pos = NULL;

	EnterCriticalSection(&m_cs);

		pos = CPtrList::Find(pObject);

	LeaveCriticalSection(&m_cs);

	return pos;
}

////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////
void CXPtrList::RemoveAt(POSITION pos)
{
	EnterCriticalSection(&m_cs);

		CPtrList::RemoveAt(pos);

	LeaveCriticalSection(&m_cs);
}

////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////
POSITION CXPtrList::FindIndex( int nIndex )
{
	POSITION pos = NULL;

	EnterCriticalSection(&m_cs);

		pos = CPtrList::FindIndex( nIndex );

	LeaveCriticalSection(&m_cs);

	return pos;
}

////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////
DWORD CXPtrList::GetCount()
{
	DWORD dwCount = 0;

	EnterCriticalSection(&m_cs);

		dwCount = CPtrList::GetCount();

	LeaveCriticalSection(&m_cs);

	return dwCount;
}

////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////
void CXPtrList::RemovePtr(void* pObject)
{
	POSITION pos = NULL;

	EnterCriticalSection(&m_cs);

		pos = CPtrList::Find( pObject );

		if( pos )
			CPtrList::RemoveAt( pos );

	LeaveCriticalSection(&m_cs);
}

////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////
BOOL CXPtrList::IsEmpty()
{
	BOOL b = 0;

	EnterCriticalSection(&m_cs);

		b = CPtrList::IsEmpty();

	LeaveCriticalSection(&m_cs);

	return b;
}


////////////////////////////////////////////////////////////////////////////////////////
//	해당 포인터에 LIST정보를 반환 시킴
////////////////////////////////////////////////////////////////////////////////////////
int CXPtrList::CopyTmpList(void *pList[])
{
	int nCount = 0;

	EnterCriticalSection(&m_cs);
	
		
		for(POSITION pos = GetHeadPosition(); pos != NULL;)
		{
			void *pTempVoid;
			pTempVoid	= GetNext(pos);
			
			if( pTempVoid != NULL	)
			{
				pList[nCount] = pTempVoid;			
			}

			nCount ++;
		}	

	LeaveCriticalSection(&m_cs);

	return	nCount;
}
