// v1.0.1
//
//  MobFoxVideoInterstitialViewController.h
//  MobFoxVideoInterstitial
//

#import <UIKit/UIKit.h>

enum {
    MobFoxInterstitialViewErrorUnknown = 0,
    MobFoxInterstitialViewErrorServerFailure = 1,
    MobFoxInterstitialViewErrorInventoryUnavailable = 2,
};

typedef enum {
    MobFoxAdTypeVideoToInterstitial = 0,
    MobFoxAdTypeVideo = 1,
    MobFoxAdTypeInterstitial = 2,
    MobFoxAdTypeInterstitialToVideo = 3,
    MobFoxAdTypeNoAdInventory = 4,
    MobFoxAdTypeError = 5,
    MobFoxAdTypeUnknown = 6
} MobFoxAdType;

typedef enum {
    MobFoxAdGroupVideo = 0,
    MobFoxAdGroupInterstitial = 1
} MobFoxAdGroupType;

@class MobFoxVideoInterstitialViewController;
@class MobFoxAdBrowserViewController;

@protocol MobFoxVideoInterstitialViewControllerDelegate <NSObject>

- (NSString *)publisherIdForMobFoxVideoInterstitialView:(MobFoxVideoInterstitialViewController *)videoInterstitial;

@optional

// called if a Video/Interstitial Ad has been successfully retrieved and is ready to display via - (void)presentAd:(MobFoxAdType)advertType:
- (void)mobfoxVideoInterstitialViewDidLoadMobFoxAd:(MobFoxVideoInterstitialViewController *)videoInterstitial advertTypeLoaded:(MobFoxAdType)advertType;

// called if no Video/Interstitial is available or there is an error
- (void)mobfoxVideoInterstitialView:(MobFoxVideoInterstitialViewController *)banner didFailToReceiveAdWithError:(NSError *)error;

// Sent immediately before interstitial is shown to the user. At this point you should pause any animations, timers or other activities that assume user interaction and save app state, much like on UIApplicationDidEnterBackgroundNotification. Remember that the user may press Home or touch links to other apps like App Store or iTunes within the interstitial, leaving your app.
- (void)mobfoxVideoInterstitialViewActionWillPresentScreen:(MobFoxVideoInterstitialViewController *)videoInterstitial;

// Sent immediately before interstitial leaves the screen. At this point you should restart any foreground activities paused as part of interstitialWillPresentScreen:
- (void)mobfoxVideoInterstitialViewWillDismissScreen:(MobFoxVideoInterstitialViewController *)videoInterstitial;

// Sent when the user has dismissed interstitial and it has left the screen.
- (void)mobfoxVideoInterstitialViewDidDismissScreen:(MobFoxVideoInterstitialViewController *)videoInterstitial;

// called when a user tap results in Application Switching
- (void)mobfoxVideoInterstitialViewActionWillLeaveApplication:(MobFoxVideoInterstitialViewController *)videoInterstitial;

@end

@interface MobFoxVideoInterstitialViewController : UIViewController
{
    
    BOOL advertLoaded;
	BOOL advertViewActionInProgress;
    
    // For Video & Interstitial Adverts it is possible for MobFox to return "location aware" adverts
    // You must specifically tell the framework to use Location aware adverts by setting locationAwareAdverts. 
    // In addition you must also set a valid latitude & longitude  by calling :
    //    
    //    - (void)setLocationWithLatitude:(CGFloat)latitude longitude:(CGFloat)longitude;
    //
    // just before requesting an new Interstitial Advert
    
    BOOL locationAwareAdverts;
    
    __unsafe_unretained id <MobFoxVideoInterstitialViewControllerDelegate> delegate;
    
    MobFoxAdBrowserViewController *_browser;
    
}

@property(nonatomic, assign) IBOutlet __unsafe_unretained id <MobFoxVideoInterstitialViewControllerDelegate> delegate;
@property(nonatomic, readonly, getter=isAdvertLoaded) BOOL advertLoaded;
@property(nonatomic, readonly, getter=isAdvertViewActionInProgress) BOOL advertViewActionInProgress;
@property(nonatomic, assign) BOOL locationAwareAdverts;

// ********* Request a new advert from MobFox ********* 
// If an ad is successfuly received & setup, the delegate method 
// mobfoxVideoInterstitialViewDidLoadMobFoxAd is called with details of the advertType returned
- (void)requestAd;


// ********* Once an ad has been successfully received, use presentAd to display the Advert ********* 
// For example presentAd could be called from the delegate method mobfoxVideoInterstitialViewDidLoadMobFoxAd
// Either way the advertType returned with the delegate should be passed into presentAd 
- (void)presentAd:(MobFoxAdType)advertType;


// ********* If you are using locationAwareAdverts you must set the latitude & longitude to use  ********* ]
// Set to each to nil if you nolonger want to us these values
- (void)setLocationWithLatitude:(CGFloat)latitude longitude:(CGFloat)longitude;


// ********* The following are ONLY used for Demo ad testing and SHOULD NOT be used in a released app ********* 

- (void)requestDemoVideoAdvert; 
- (void)requestDemoInterstitualAdvert;
- (void)requestDemoVideoToInterstitualAdvert;
- (void)requestDemoInterstitualToVideoAdvert;

@end

extern NSString * const MobFoxVideoInterstitialErrorDomain;