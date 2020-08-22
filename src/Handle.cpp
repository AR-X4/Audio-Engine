

#include "HandleManager.h"
#include "Handle.h"

// --------------------------------------------------
// Handle
// --------------------------------------------------

Handle::Handle()
{
	//Activate
	Status status = HandleManager::ActivateHandle(this->id, this->index);
	assert(status == Status::SUCCESS);

	Trace::out("Handle(): new handle(%x):0x%X\n", this->index, this->id);
}

Handle::~Handle()
{
	// Invalidate handle;
	HandleManager::InvalidateHandle(*this);

	Trace::out("~Handle(): invalidate handle(%x):0x%X\n", this->index, this->id);
}

Handle::ID Handle::GetID() const
{
	return this->id;
}

Handle::Index Handle::GetIndex() const
{
	return this->index;
}

//---------------------------------------------------------------
// Tunneling... I only want handle.h to be used
//---------------------------------------------------------------
Handle::Status Handle::ValidateHandle(const Handle& handle)
{
	return HandleManager::ValidateHandle(handle);
}

Handle::Status Handle::InvalidateHandle(Handle& handle)
{
	return HandleManager::InvalidateHandle(handle);
}

Handle::Status Handle::AquireResource(const Handle& handle)
{
	return HandleManager::AquireResource(handle);
}

Handle::Status Handle::ReleaseResource(const Handle& handle)
{
	return HandleManager::ReleaseResource(handle);
}


// ---  End of File ---------------
