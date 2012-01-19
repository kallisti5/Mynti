/*
 * Mynti Weather
 *
 * Weather on your Haiku desktop
 * 2012, Alexander von Gluck IV <kallisti5@unixzen.com>
 *
 */


#include <View.h>


#define DESKBAR_ITEM_NAME "MyntiWeather"
#define DESKBAR_VIEW_NAME "MyntiView"

const rgb_color TEXT_COLOR = { 0, 0, 0 };


class MyntiDeskbarView : public BView
{
public:
    MyntiDeskbarView();
    MyntiDeskbarView(BMessage* message);

    virtual status_t Archive(BMessage* archive, bool depth = true) const;
    static MyntiDeskbarView* Instantiate(BMessage* archive);
	virtual void Draw(BRect updateRect);

    virtual void MessageReceived(BMessage* message);
	virtual void MouseDown(BPoint point);

    virtual void Pulse();

private:
	uint32 fWeatherConditions;

	typedef BView superView;
	virtual void QuitRequested();

};
