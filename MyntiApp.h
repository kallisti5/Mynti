/*
 * Mynti Weather
 *
 * Weather on your Haiku desktop
 * 2012, Alexander von Gluck IV <kallisti5@unixzen.com>
 *
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
