// v1.0.1
//
//  MobFoxBannerView.h
//

#import <UIKit/UIKit.h>

enum {
    MobFoxErrorUnknown = 0,
    MobFoxErrorServerFailure = 1,
    MobFoxErrorInventoryUnavailable = 2,
};

@class MobFoxBannerView;

@protocol MobFoxBannerViewDelegate <NSObject>

- (NSString *)publisherIdForMobFoxBannerView:(MobFoxBannerView *)banner;

@optional

// called if an ad has been successfully retrieved
- (void)mobfoxBannerViewDidLoadMobFoxAd:(MobFoxBannerView *)banner;

// called if no banner is available or there is an error
- (void)mobfoxBannerView:(MobFoxBannerView *)banner didFailToReceiveAdWithError:(NSError *)error;

// called when user taps on a banner
- (BOOL)mobfoxBannerViewActionShouldBegin:(MobFoxBannerView *)banner willLeaveApplication:(BOOL)willLeave;

// called when the modal web view will be disaplyed
- (void)mobfoxBannerViewActionWillPresent:(MobFoxBannerView *)banner;

// called when the modal web view is about to be cancelled
// At this point you should restart any foreground activities paused as part of mobfoxBannerViewActionWillPresent:
- (void)mobfoxBannerViewActionWillFinish:(MobFoxBannerView *)banner;

// called when the modal web view is cancelled and the user is returning to the app
- (void)mobfoxBannerViewActionDidFinish:(MobFoxBannerView *)banner;

// called when a user tap results in Application Switching
- (void)mobfoxBannerViewActionWillLeaveApplication:(MobFoxBannerView *)banner;

@end




@interface MobFoxBannerView : UIView 
{
	NSString *advertisingSection;  // formerly know as "spot"
	BOOL bannerLoaded;
	BOOL bannerViewActionInProgress;
	UIViewAnimationTransition refreshAnimation;
	
	__unsafe_unretained id <MobFoxBannerViewDelegate> delegate;
	
	// internals
	UIImage *_bannerImage;
	BOOL _tapThroughLeavesApp;
	BOOL _shouldScaleWebView;
	BOOL _shouldSkipLinkPreflight;
	BOOL _statusBarWasVisible;
	NSURL *_tapThroughURL;
	NSInteger _refreshInterval;
	NSTimer *_refreshTimer;
    BOOL    refreshTimerOff;  // if the SDK is used with Google's Meditaion Adaptor we want our Refresh Off
	
    
}

@property(nonatomic, assign) IBOutlet __unsafe_unretained id <MobFoxBannerViewDelegate> delegate;
@property(nonatomic, copy) NSString *advertisingSection;
@property(nonatomic, assign) UIViewAnimationTransition refreshAnimation;


@property(nonatomic, readonly, getter=isBannerLoaded) BOOL bannerLoaded;
@property(nonatomic, readonly, getter=isBannerViewActionInProgress) BOOL bannerViewActionInProgress;

@property(nonatomic, assign) BOOL    refreshTimerOff;

@end

extern NSString * const MobFoxErrorDomain;