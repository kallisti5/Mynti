/*
 * Mynti Weather
 *
 * Copyright 2012-2013, Alexander von Gluck IV
 * Released under the terms of the MIT license
 *
 * http://unixzen.com, http://github.com/kallisti5
 */


#include <Application.h>
#include <Deskbar.h>


#define APPLICATION_SIG "application/x-vnd.Mynti"


class MyntiApp : public BApplication {
public:
                    MyntiApp();
	virtual         ~MyntiApp();
	void            ReadyToRun();
	void            MessageReceived(BMessage *message);
};

extern "C" _EXPORT BView* instantiate_deskbar_item();
