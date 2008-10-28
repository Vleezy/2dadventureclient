#ifndef TLEVELBOARDCHANGE_H
#define TLEVELBOARDCHANGE_H

#include <vector>
#include <time.h>
#include "ICommon.h"
#include "CTimeout.h"
#include "CString.h"

class TLevelBoardChange
{
	public:
		// constructor - destructor
		TLevelBoardChange(const int pX, const int pY, const int pWidth, const int pHeight,
			const CString& pTiles, const CString& pOldTiles, const int respawn = 15)
			: x(pX), y(pY), width(pWidth), height(pHeight),
			tiles(pTiles), oldTiles(pOldTiles), modTime(time(0)) { timeout.setTimeout(respawn); }

		// functions
		CString getBoardStr(const CString ignore = "") const;
		void swapTiles();

		// get private variables
		int getX() const				{ boost::recursive_mutex::scoped_lock lock(m_preventChange); return x; }
		int getY() const				{ boost::recursive_mutex::scoped_lock lock(m_preventChange); return y; }
		int getWidth() const			{ boost::recursive_mutex::scoped_lock lock(m_preventChange); return width; }
		int getHeight() const			{ boost::recursive_mutex::scoped_lock lock(m_preventChange); return height; }
		CString getTiles() const		{ boost::recursive_mutex::scoped_lock lock(m_preventChange); return tiles; }
		time_t getModTime() const		{ boost::recursive_mutex::scoped_lock lock(m_preventChange); return modTime; }

		// set private variables
		void setModTime(time_t ntime)	{ boost::recursive_mutex::scoped_lock lock(m_preventChange); modTime = ntime; }

		CTimeout timeout;

	private:
		int x, y, width, height;
		CString tiles, oldTiles;
		time_t modTime;

		mutable boost::recursive_mutex m_preventChange;
};

#endif // TLEVELBOARDCHANGE_H
