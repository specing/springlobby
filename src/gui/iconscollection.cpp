/* This file is part of the Springlobby (GPL v2 or later), see COPYING */

#include "iconscollection.h"

#include "images/exists.xpm"
#include "images/nexists.xpm"

#include <wx/icon.h>

IconsCollection::IconsCollection()
{
	iconExists = nullptr;
	iconNExists = nullptr;
}

IconsCollection::~IconsCollection()
{
	wxDELETE(iconExists);
	wxDELETE(iconNExists);
}

IconsCollection* IconsCollection::Instance()
{
	if (m_Instance == nullptr) {
		m_Instance = new IconsCollection();
	}
	return m_Instance;
}

void IconsCollection::Release()
{
	if (m_Instance != nullptr) {
		delete m_Instance;
	}
}

wxIcon& IconsCollection::IconExists()
{
	if (iconExists == nullptr) {
		iconExists = new wxIcon(exists_xpm);
	}
	return *iconExists;
}

wxIcon& IconsCollection::IconNExists()
{
	if (iconNExists == nullptr) {
		iconNExists = new wxIcon(nexists_xpm);
	}
	return *iconNExists;
}

IconsCollection* IconsCollection::m_Instance = nullptr;
