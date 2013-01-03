/*
 * Mynti Weather
 *
 * Copyright 2012-2013, Alexander von Gluck IV
 * Released under the terms of the MIT license
 *
 * http://unixzen.com, http://github.com/kallisti5
 */


#include "MyntiApp.h"
#include "MyntiDeskbarView.h"
#include "MyntiImages.h"

#include <Bitmap.h>
#include <IconUtils.h>
#include <MenuItem.h>
#include <PopUpMenu.h>

#include <stdio.h>


MyntiDeskbarView::MyntiDeskbarView()
    :
    BView(BRect(0, 0, 1, 1), 0, 0, 0)
{
}


MyntiDeskbarView::MyntiDeskbarView(BMessage* message)
    :
	BView(BRect(0, 0, 15, 15), DESKBAR_ITEM_NAME,B_FOLLOW_NONE,
		B_WILL_DRAW | B_PULSE_NEEDED),
	fWeatherTemperature(32),
	fWeatherConditions(0)
{
	SetFont(be_plain_font);
	SetViewColor(B_TRANSPARENT_COLOR);
	
	float shelfWidth = StringWidth("100o") + 18;
	ResizeTo(shelfWidth, 15);
}


status_t
MyntiDeskbarView::Archive(BMessage* archive, bool depth) const
{
    superView::Archive(archive, depth);

    archive->AddString("add_on", APPLICATION_SIG);
    archive->AddString("class", DESKBAR_VIEW_NAME);

    return B_OK;
}


MyntiDeskbarView*
MyntiDeskbarView::Instantiate(BMessage* archive)
{
    if (validate_instantiation(archive, DESKBAR_VIEW_NAME))
    {
        return new MyntiDeskbarView(archive);
    }

    return NULL;
}


void
MyntiDeskbarView::Draw(BRect updateRect)
{
	superView::Draw(updateRect);


	BBitmap bitmap(BRect(0,0,15,15), B_RGB32);

	switch(fWeatherConditions) {
		case 0:
			BIconUtils::GetVectorIcon(kImageNoData, sizeof(kImageNoData), &bitmap);
			break;
		case 1:
			BIconUtils::GetVectorIcon(kImageSun, sizeof(kImageSun), &bitmap);
			break;
		case 2:
			BIconUtils::GetVectorIcon(kImageRain, sizeof(kImageRain), &bitmap);
			break;
		case 3:
			BIconUtils::GetVectorIcon(kImageSnow, sizeof(kImageSnow), &bitmap);
			break;
		default:
			BIconUtils::GetVectorIcon(kImageNoData, sizeof(kImageNoData), &bitmap);
	}
			

	char string[5];
	sprintf(string, "%" B_PRId32 "\xc2\xb0", fWeatherTemperature);
	
	font_height height; 
	GetFontHeight(&height);
	
	float width = StringWidth(string);
	BRect rect = Bounds();
	float x = 18;
	float y = 1 + height.ascent
	            + (rect.Height() - (height.ascent + height.descent))/2;
	
	SetHighColor(Parent()->ViewColor());
	SetLowColor(Parent()->ViewColor());
	FillRect(updateRect);
	SetDrawingMode(B_OP_ALPHA);
	DrawBitmap(&bitmap);

	SetHighColor(TEXT_COLOR);
	SetDrawingMode(B_OP_OVER);
	DrawString(string, BPoint(x, y));
}


void
MyntiDeskbarView::MessageReceived(BMessage* msg)
{
	switch (msg->what) {
		case B_QUIT_REQUESTED:
			QuitRequested();
			break;
		default:
			superView::MessageReceived(msg);
			break;
	}
}


void
MyntiDeskbarView::MouseDown(BPoint point)
{
    BPopUpMenu* menu = new BPopUpMenu("Mynti", false, false);

    menu->AddItem(new BMenuItem("Quit", new BMessage(B_QUIT_REQUESTED)));
    menu->SetTargetForItems(this);

    ConvertToScreen(&point);
    menu->Go(point, true, false, true);

    delete menu;
}


void
MyntiDeskbarView::Pulse()
{
	fWeatherTemperature++;
	fWeatherConditions++;
	if (fWeatherConditions > 3)
		fWeatherConditions = 0;
	if (fWeatherTemperature > 199)
		fWeatherTemperature = 0;

	// TODO: check for Weather Update here
	Invalidate();
}


void
MyntiDeskbarView::QuitRequested()
{
    BDeskbar deskbar;
    deskbar.RemoveItem(DESKBAR_ITEM_NAME);
}
