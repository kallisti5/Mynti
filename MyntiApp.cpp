/*
 * Mynti Weather
 *
 * Weather on your Haiku desktop
 * 2012, Alexander von Gluck IV <kallisti5@unixzen.com>
 *
 */


#include "MyntiApp.h"
#include "MyntiDeskbarView.h"

#include <Roster.h>


BView* instantiate_deskbar_item()
{
    return new MyntiDeskbarView;
}


MyntiApp::MyntiApp()
    : BApplication(APPLICATION_SIG)
{
	BDeskbar deskbar;
	if (!deskbar.HasItem(DESKBAR_ITEM_NAME))
	{
	    entry_ref ref;
	    be_roster->FindApp(APPLICATION_SIG, &ref);
	    deskbar.AddItem(&ref);
	}
	
	PostMessage(B_QUIT_REQUESTED);
}


MyntiApp::~MyntiApp()
{
}


void
MyntiApp::ReadyToRun()
{
}


void
MyntiApp::MessageReceived(BMessage *message)
{
    switch (message->what) {
    	default:
			BApplication::MessageReceived(message);
	}
}


int main(int , char **)
{
    MyntiApp app;
    app.Run();

    return 0;
}
