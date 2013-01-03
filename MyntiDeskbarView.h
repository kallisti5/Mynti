/*
 * Mynti Weather
 *
 * Copyright 2012-2013, Alexander von Gluck IV
 * Released under the terms of the MIT license
 *
 * http://unixzen.com, http://github.com/kallisti5
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
	int32 fWeatherTemperature;

	typedef BView superView;
	virtual void QuitRequested();

};
