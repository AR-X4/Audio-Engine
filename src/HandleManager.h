#ifndef HANDLE_MAN_H
#define HANDLE_MAN_H

#include "Handle.h"

class HandleManager
{
private:

	// constants
	static const unsigned int HANDLE_TABLE_SIZE = 20;
	static const unsigned int HANDLE_INVALID_STATE = 0x0;
	static const unsigned int HANDLE_STARTING_ID = 0xAAAA0000;

	// Nested class
	class HandleTable
	{
	public:
		HandleTable() = default;
		HandleTable(const HandleTable&) = delete;
		HandleTable& operator = (const HandleTable&) = delete;
		~HandleTable() = default;

		//Handle::ID id;
		std::atomic<unsigned int> id;
		std::mutex				  mtx;
	};


public:
	HandleManager();
	~HandleManager();

	//-----------------------------------------------------
	// You cannot copy the singleton
	//-----------------------------------------------------
	HandleManager(const HandleManager&) = delete;
	const HandleManager& operator = (const HandleManager&) = delete;

	//-----------------------------------------------------
	// Being strategic on what is expose or not
	//-----------------------------------------------------
	static Handle::Status ActivateHandle(Handle::ID& id, Handle::Index& index);

	static Handle::Status InvalidateHandle(Handle& handle);
	static Handle::Status ValidateHandle(const Handle& handle);

	static Handle::Status AquireResource(const Handle& handle);
	static Handle::Status ReleaseResource(const Handle& handle);

	//-----------------------------------------------------
	// Only for our DEBUG - remove for application
	//-----------------------------------------------------
	static void PrintTable();

private:
	//-----------------------------------------------------
	// Keeping internals... private
	//-----------------------------------------------------
	static HandleManager* GetInstance();
	Handle::ID GetNewID();
	bool FindNextAvailable(Handle::Index& index);

	Handle::Status IsHandleValid(const Handle& handle);
	Handle::Status IsHandleAndRangeValid(const Handle& handle);

	//-----------------------------------------------------
	// Raw data
	//-----------------------------------------------------
	HandleTable table[HANDLE_TABLE_SIZE];
	Handle::ID  srcID;
};

#endif

// ---  End of File ---------------
