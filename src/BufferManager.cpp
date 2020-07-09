#include "BufferManager.h"

BufferManager* BufferManager::poInstance = nullptr;

BufferManager::BufferManager(int reserveNum, int reserveGrow)
    
{
    this->BaseInitialize(reserveNum, reserveGrow);
    this->poNodeCompare = new AudioBuffer();
    assert(this->poNodeCompare != nullptr);
}

BufferManager::~BufferManager() 
{
    delete this->poNodeCompare;
}

void BufferManager::Create(int reserveNum, int reserveGrow) {

    assert(reserveNum > 0);
    assert(reserveGrow > 0);

    // initialize the singleton here
    assert(poInstance == nullptr);

    // Do the initialization
    if (poInstance == nullptr)
    {
        poInstance = new BufferManager(reserveNum, reserveGrow);
    }
}

void BufferManager::Destory()
{
    //Trace::out("\n");
    //Trace::out("---- Destroy() ----\n");

    // Get the instance
    BufferManager* pMan = BufferManager::GetInstance();
    assert(pMan != nullptr);

    // Clean up what it current owns reserve and active
    pMan->BaseDestroy();

    // bye bye singleton
    delete pMan->poInstance;

}

BufferManager* BufferManager::GetInstance() {

    assert(poInstance != nullptr);
    return poInstance;
}


AudioBuffer* BufferManager::CreateBuffer(SoundId IDin) {
    BufferManager* pMan = BufferManager::GetInstance();
    assert(pMan != nullptr);

    AudioBuffer* pBuffer = (AudioBuffer*)pMan->BaseAdd();
    assert(pBuffer != nullptr);

    // Create a new one given a wash
    pBuffer->Set(IDin);

    return pBuffer;
}

AudioBuffer* BufferManager::FindBuffer(SoundId IDin)
{
    BufferManager* pBuffMan = GetInstance();
    assert(pBuffMan != nullptr);

    pBuffMan->poNodeCompare->Set(IDin);

    AudioBuffer* pBuffer = (AudioBuffer*)pBuffMan->BaseFind(pBuffMan->poNodeCompare);
    assert(pBuffer != nullptr);

    return pBuffer;
}

void BufferManager::DestroyBuffer(AudioBuffer* Nodein)
{
    BufferManager* pMan = BufferManager::GetInstance();
    assert(pMan != nullptr);

    assert(Nodein != nullptr);
    pMan->BaseRemove(Nodein);
}

void BufferManager::Dump()
{
    BufferManager* pMan = BufferManager::GetInstance();
    assert(pMan != nullptr);

    pMan->BaseDump();
}

DLink* BufferManager::DerivedCreateNode()
{
    DLink* pNode = new AudioBuffer();
    assert(pNode != nullptr);

    return pNode;
}

bool BufferManager::DerivedCompare(DLink* pLinkA, DLink* pLinkB)
{
    // This is used in baseFind() 
    assert(pLinkA != nullptr);
    assert(pLinkB != nullptr);

    AudioBuffer* pDataA = (AudioBuffer*)pLinkA;
    AudioBuffer* pDataB = (AudioBuffer*)pLinkB;

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

void BufferManager::DerivedWash(DLink* pLink)
{
    assert(pLink != nullptr);
    AudioBuffer* pNode = (AudioBuffer*)pLink;
    pNode->Wash();
}

void BufferManager::DerivedDumpNode(DLink* pLink)
{
    assert(pLink != nullptr);
    AudioBuffer* pData = (AudioBuffer*)pLink;
    pData->Dump();
}

void BufferManager::DerivedDestroyNode(DLink* pLink)
{
    assert(pLink);
    AudioBuffer* pData = (AudioBuffer*)pLink;
    delete pData;
}



