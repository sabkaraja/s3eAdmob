//
//  ADFInterstitial.h
//  Adfonic SDK
//
//  Copyright 2011-12 Adfonic Ltd. All rights reserved.
//

@class ADFRequest;
@class ADFInterstitial;
@class ADFBannerView;

@protocol ADFInterstitialDelegate <NSObject>

@optional

- (void)interstitialDidReceiveAd:(ADFInterstitial *)ad;


- (void)interstitial:(ADFInterstitial *)ad didFailToReceiveAdWithError:(NSError *)error;

- (void)interstitialWillPresentScreen:(ADFInterstitial *)ad;


- (void)interstitialWillDismissScreen:(ADFInterstitial *)ad;

- (void)interstitialDidDismissScreen:(ADFInterstitial *)ad;

- (void)interstitialWillLeaveApplication:(ADFInterstitial *)ad;

- (void)interstitialActionWillBegin:(ADFBannerView *)banner willLeaveApplication:(BOOL)willLeave;

@end

@interface ADFInterstitial : NSObject

@property (nonatomic, readonly) BOOL isReady;

@property (nonatomic, assign) NSObject <ADFInterstitialDelegate> *delegate;

- (void)loadRequest:(ADFRequest *)request;

- (void)presentFromRootViewController:(UIViewController *)rootViewController;

@end
