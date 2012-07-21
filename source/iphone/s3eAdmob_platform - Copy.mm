/*
 * iphone-specific implementation of the s3eAdmob extension.
 * Add any platform-specific functionality here.
 */
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
#import <UIKit/UIKit.h>


#include "s3eAdmob_internal.h"
#include "s3eEdk.h"
#include "s3eEdk_iphone.h"

#define S3E_CURRENT_EXT ADMOB
#include "s3eEdkError.h"
#define S3E_DEVICE_ADMOB S3E_EXT_ADMOB_HASH

#include "GADBannerView.h"
#include "GADBannerViewDelegate.h"
#include "stdio.h"

#import "GADInterstitial.h"


GADBannerView * bannerView_;
GADInterstitial *interstitial_;

s3eResult s3eAdmobInit_platform()
{
#ifdef DEBUG
	NSLog(@"s3eAdmob Init");
#endif
    return S3E_RESULT_SUCCESS;
}

void s3eAdmobTerminate_platform()
{
#ifdef DEBUG
	NSLog(@"s3eAdmob Term");
#endif
}

s3eResult s3eAdmobStart_platform(const char* pub_id, int ad_type, int orientation, int x, int y)
{
	bannerView_ = [[[GADBannerView alloc] initWithAdSize:kGADAdSizeBanner] autorelease];
	
	NSString * sPubId = [NSString stringWithUTF8String:pub_id];
	bannerView_.adUnitID = sPubId;
	
	UIViewController *controller = s3eEdkGetUIViewController();
	UIView *view = s3eEdkGetUIView();
	controller.view = view;
	
	bannerView_.rootViewController = controller;  
	
	[bannerView_ loadRequest:[GADRequest request]];
	
    return S3E_RESULT_SUCCESS;
}

s3eResult s3eAdmobResize_platform(int ad_type)
{
    return S3E_RESULT_ERROR;
}

s3eResult s3eAdmobShow_platform()
{
    return S3E_RESULT_ERROR;
}

s3eResult s3eAdmobRefresh_platform()
{
    return S3E_RESULT_ERROR;
}

s3eResult s3eAdmobHide_platform()
{
    if (bannerView_ == nil)
	{
		return S3E_RESULT_ERROR;
	}
	bannerView_.hidden = true;
	return S3E_RESULT_SUCCESS;
}

s3eResult s3eAdmobMove_platform(int orientation, int x, int y)
{
    return S3E_RESULT_ERROR;
}

s3eResult s3eAdmobShowInterstitial_platform(const char* med_id)
{
	s3eEdkCallbacksEnqueue(S3E_EXT_ADMOB_HASH, S3E_ADMOB_CALLBACK_INTERSTITIAL_END,
		NULL, 0, NULL, S3E_FALSE, NULL, NULL);
						   
	
	interstitial_ = [[GADInterstitial alloc] init];
	NSString * sPubId = [NSString stringWithUTF8String:med_id];
	interstitial_.adUnitID = sPubId;
	
    return S3E_RESULT_SUCCESS;
}

s3eResult s3eAdmobShowSplash_platform(const char* med_id)
{
    return S3E_RESULT_ERROR;
}
