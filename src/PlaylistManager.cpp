#include "PlaylistManager.h"

PlaylistManager* PlaylistManager::poInstance = nullptr;

PlaylistManager::PlaylistManager(int reserveNum, int reserveGrow)
{
    this->BaseInitialize(reserveNum, reserveGrow);

    this->poNodeCompare = new Playlist();
    assert(this->poNodeCompare != nullptr);

}

PlaylistManager::~PlaylistManager()
{
    delete this->poNodeCompare;
}

void PlaylistManager::Create(int reserveNum, int reserveGrow) {

    assert(reserveNum > 0);
    assert(reserveGrow > 0);

    // initialize the singleton here
    assert(poInstance == nullptr);

    // Do the initialization
    if (poInstance == nullptr)
    {
        poInstance = new PlaylistManager(reserveNum, reserveGrow);
    }
}

void PlaylistManager::Destroy()
{
    //Trace::out("\n");
    //Trace::out("---- Destroy() ----\n");

    // Get the instance
    PlaylistManager* pMan = PlaylistManager::GetInstance();
    assert(pMan != nullptr);

    // Clean up what it current owns reserve and active
    pMan->BaseDestroy();

    // bye bye singleton
    delete pMan->poInstance;
}

Playlist* PlaylistManager::CreatePlaylist(SoundId IDin)
{
    PlaylistManager* pListMan = GetInstance();
    assert(pListMan != nullptr);

    Playlist* pList = (Playlist*)pListMan->BaseAdd();
    assert(pList != nullptr);

    // Create a new one given a wash
    pList->Set(IDin);

    return pList;
}

//Playlist* PlaylistManager::FindPlaylist(SoundId IDin)
//{
//    PlaylistManager* pListMan = GetInstance();
//    assert(pListMan != nullptr);
//
//    pListMan->poNodeCompare->SetID(IDin);
//
//    Playlist* pList = (Playlist*)pListMan->BaseFind(pListMan->poNodeCompare);
//    assert(pList != nullptr);
//
//    return pList;
//}

void PlaylistManager::DestroyPlaylist(Playlist* Nodein)
{
    PlaylistManager* pMan = PlaylistManager::GetInstance();
    assert(pMan != nullptr);

    assert(Nodein != nullptr);
    pMan->BaseRemove(Nodein);

    Trace::out("Destroyed Playlist\n");

}

void PlaylistManager::Dump()
{
    PlaylistManager* pMan = PlaylistManager::GetInstance();
    assert(pMan != nullptr);

    pMan->BaseDump();
}

DLink* PlaylistManager::DerivedCreateNode()
{
    DLink* pNode = new Playlist();
    assert(pNode != nullptr);

    return pNode;
}

bool PlaylistManager::DerivedCompare(DLink* pLinkA, DLink* pLinkB)
{
    // This is used in baseFind() 
    assert(pLinkA != nullptr);
    assert(pLinkB != nullptr);

    Playlist* pDataA = (Playlist*)pLinkA;
    Playlist* pDataB = (Playlist*)pLinkB;

    bool status = false;
    SoundId A_id;
    SoundId B_id;

    pDataA->GetID(A_id);
    pDataB->GetID(B_id);

    if (A_id == B_id)
    {
        status = true;
    }

    return status;
}

void PlaylistManager::DerivedWash(DLink* pLink)
{
    assert(pLink != nullptr);
    Playlist* pNode = (Playlist*)pLink;
    pNode->Wash();
}

void PlaylistManager::DerivedDumpNode(DLink* pLink)
{
    assert(pLink != nullptr);
    Playlist* pData = (Playlist*)pLink;
    pData->Dump();
}

void PlaylistManager::DerivedDestroyNode(DLink* pLink)
{
    assert(pLink);
    Playlist* pData = (Playlist*)pLink;
    delete pData;
}

PlaylistManager* PlaylistManager::GetInstance() {

    assert(poInstance != nullptr);
    return poInstance;
}







