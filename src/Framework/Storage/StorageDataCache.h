#ifndef STORAGEDATACACHE_H
#define STORAGEDATACACHE_H

#include "System/Containers/InList.h"
#include "System/Buffers/Buffer.h"
#include "StorageDataPage.h"

#define DCACHE StorageDataCache::Get()

class StorageDataCache
{
public:
	static StorageDataCache*	Get();

	StorageDataPage*			GetPage();
	void						FreePage(StorageDataPage* page);

	void						RegisterHit(StorageDataPage* page);
	void						Checkin(StorageDataPage* page);
	void						Checkout(StorageDataPage* page);

private:
	StorageDataCache();
	
	InList<StorageDataPage>		freeList;
	InList<StorageDataPage>		lruList;
	StorageDataPage*			pageArea;
	Buffer*						bufferArea;
	unsigned					num;
};

#endif
