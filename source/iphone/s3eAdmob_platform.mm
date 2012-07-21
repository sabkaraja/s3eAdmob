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

#include "GADAdSize.h"
#include "GADBannerView.h"
#include "GADBannerViewDelegate.h"
#include "stdio.h"

#import "GADInterstitial.h"

//GADInterstitialDelegate implementation start
@interface s3eAdmobInterstitialDelegate : NSObject<GADInterstitialDelegate>
@end

@implementation s3eAdmobInterstitialDelegate

- (void)interstitialDidReceiveAd:(GADInterstitial *)ad
{
#ifdef DEBUG
	NSLog(@"s3eAdmob InterstitialDidReceiveAd");
#endif
	[ad presentFromRootViewController: s3eEdkGetUIViewController()];

	s3eEdkCallbacksEnqueue(S3E_EXT_ADMOB_HASH, S3E_ADMOB_CALLBACK_AD_LOAD,
						   NULL, 0, NULL, S3E_FALSE, NULL, NULL);
}

- (void)interstitial:(GADInterstitial *)ad
    didFailToReceiveAdWithError:(GADRequestError *)error
{
#ifdef DEBUG
	NSLog(@"s3eAdmob didFailToReceiveAdWithError");
#endif
	s3eEdkCallbacksEnqueue(S3E_EXT_ADMOB_HASH, S3E_ADMOB_CALLBACK_AD_FAIL,
						   NULL, 0, NULL, S3E_FALSE, NULL, NULL);
}

- (void)interstitialWillPresentScreen:(GADInterstitial *)ad
{
#ifdef DEBUG
	NSLog(@"s3eAdmob interstitialWillPresentScreen");
#endif
	s3eEdkCallbacksEnqueue(S3E_EXT_ADMOB_HASH, S3E_ADMOB_CALLBACK_INTERSTITIAL_BEGIN,
						   NULL, 0, NULL, S3E_FALSE, NULL, NULL);
}


- (void)interstitialDidDismissScreen:(GADInterstitial *)ad
{
#ifdef DEBUG
	NSLog(@"s3eAdmob interstitialDidDismissScreen");
#endif
	s3eEdkCallbacksEnqueue(S3E_EXT_ADMOB_HASH, S3E_ADMOB_CALLBACK_INTERSTITIAL_END,
						   NULL, 0, NULL, S3E_FALSE, NULL, NULL);
}
@end
//GADInterstitialDelegate implementation end

struct s3eAdmobGlobal{
       GADBannerView * bannerView_;
       CGSize size;
} s3eAdmobGlobal_;

GADBannerView * bannerView_;
GADInterstitial * interstitial_;
s3eAdmobInterstitialDelegate * delegate = nil;

s3eResult s3eAdmobInit_platform()
{
#ifdef DEBUG
	NSLog(@"s3eAdmob s3eAdmobInit");
#endif
	delegate = [[s3eAdmobInterstitialDelegate alloc] init];
    return S3E_RESULT_SUCCESS;
}

void s3eAdmobTerminate_platform()
{
#ifdef DEBUG
	NSLog(@"s3eAdmob Term");
#endif
	//[delegate release];
}

s3eResult s3eAdmobStart_platform(const char* pub_id, int ad_type, int orientation, int x, int y)
{
	GADAdSize size;
	if(ad_type == Admob_kGADAdSizeBanner)
      size = kGADAdSizeBanner;
    else if(ad_type == Admob_kGADAdSizeMediumRectangle)
      size = kGADAdSizeMediumRectangle;
    else if(ad_type == Admob_kGADAdSizeFullBanner)
      size = kGADAdSizeFullBanner;
    else if(ad_type == Admob_kGADAdSizeLeaderBoard)
      size = kGADAdSizeLeaderboard;
    else if(ad_type == Admob_kGADAdSizeSkyscraper)
      size = kGADAdSizeSkyscraper;
	else
		return S3E_RESULT_ERROR;
	  
	s3eAdmobGlobal_.size = size.size;
	
	CGRect rect = CGRectMake(0, 0, size.size.width, size.size.height);
    //if(s3eAdmobGlobal_.bannerView_ == nil) 
	{
		s3eAdmobGlobal_.bannerView_ = [[GADBannerView alloc] initWithFrame:rect];
	}
	
	NSString * sPubId = [NSString stringWithUTF8String:pub_id];
	s3eAdmobGlobal_.bannerView_.adUnitID = sPubId;
	
	s3eAdmobGlobal_.bannerView_.rootViewController = s3eEdkGetUIViewController();
    [s3eEdkGetUIView() addSubview:s3eAdmobGlobal_.bannerView_];

	[s3eAdmobGlobal_.bannerView_ loadRequest:[GADRequest request]];
	
    return S3E_RESULT_SUCCESS;
}

s3eResult s3eAdmobResize_platform(int ad_type)
{
    return S3E_RESULT_ERROR;
}

s3eResult s3eAdmobShow_platform()
{
    if (s3eAdmobGlobal_.bannerView_ == nil)
	{
		return S3E_RESULT_ERROR;
	}
	s3eAdmobGlobal_.bannerView_.hidden = NO;
    return S3E_RESULT_SUCCESS;
}

s3eResult s3eAdmobRefresh_platform()
{
    GADRequest *request = [GADRequest request];
    [s3eAdmobGlobal_.bannerView_ loadRequest:request];

    return S3E_RESULT_SUCCESS;

}

s3eResult s3eAdmobHide_platform()
{
    if (s3eAdmobGlobal_.bannerView_ == nil)
	{
		return S3E_RESULT_ERROR;
	}
	s3eAdmobGlobal_.bannerView_.hidden = YES;
	return S3E_RESULT_SUCCESS;
}

s3eResult s3eAdmobMove_platform(int orientation, int x, int y)
{
	s3eAdmobGlobal_.bannerView_.transform = CGAffineTransformMakeRotation(M_PI * orientation / 2.0);
	s3eAdmobGlobal_.bannerView_.center = CGPointMake(s3eAdmobGlobal_.size.width / 2 + x, s3eAdmobGlobal_.size.height / 2 + y);

    return S3E_RESULT_ERROR;
}

s3eResult s3eAdmobShowInterstitial_platform(const char* med_id)
{
#ifdef DEBUG
	NSLog(@"s3eAdmob s3eAdmobShowInterstitial");
#endif
	

	interstitial_ = [[GADInterstitial alloc] init];
	interstitial_.delegate = delegate;

	NSString * sPubId = [NSString stringWithUTF8String:med_id];
	interstitial_.adUnitID = sPubId;

	GADRequest *request = [GADRequest request];
	
	[interstitial_ loadRequest: request];
	
    return S3E_RESULT_SUCCESS;
}

s3eResult s3eAdmobShowSplash_platform(const char* med_id)
{
    return S3E_RESULT_ERROR;
}
