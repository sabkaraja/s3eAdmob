//
//  ADFConstants.h
//  Adfonic SDK
//
//  Copyright 2011-12 Adfonic Ltd. All rights reserved.
//

extern NSString * const ADFErrorDomain;

// size identifiers

//CGSizeMake(320, 50)
extern NSString * const ADFBannerContentSizeIdentifierPhonePortrait;

//CGSizeMake(300, 250)
extern NSString * const ADFBannerContentSizeIdentifierMPU;

//CGSizeMake(728, 90)
extern NSString * const ADFBannerContentSizeIdentifierLeaderboard;

//CGSizeMake(120, 600)
extern NSString * const ADFBannerContentSizeIdentifierSkyscraper;

//CGSizeMake(468, 60)
extern NSString * const ADFBannerContentSizeIdentifierBanner;

//Full screen banner
extern NSString * const ADFBannerContentSizeIdentifierInterstitial;

// color schemes
extern NSString * const ADFColorSchemeBlue;
extern NSString * const ADFColorSchemeGreen;
extern NSString * const ADFColorSchemeOrange;
extern NSString * const ADFColorSchemePurple;
extern NSString * const ADFColorSchemeRed;
extern NSString * const ADFColorSchemeYellow;


/// Returns an array of all content size identifiers the manager knows about
/**
 @discussion This is defined for testing purposes.
 */
NSArray * __ADF_ContentSizeIdentifiers();

#pragma mark Error Codes

enum __ADFErrorCode {
	__ADFErrorCodeMockError = -1,
	__ADFErrorCodeNoHTML = 1,
    __ADFErrorCodeIncorrectSizeIdentifier,
	__ADFErrorCodeNoAdToServe,
	__ADFErrorCodeUnknownAdfonicAPIError,
	__ADFErrorCodeInvalidSlotIdentifier
};


#pragma mark Configuration File Keys

#define kADFConfigFileName				@"AdfonicConfigurations"

// Configuration Keys
#define kADFConfigKeySlots				@"slots"

#define kADFConfigKeySlotIdentifier		@"slotIdentifier"
#define kADFConfigKeySizeIdentifier     @"sizeIdentifier"
#define kADFConfigKeyBannerType			@"type"
#define kADFConfigKeyIsTest				@"isTest"
#define kADFConfigKeyColorScheme		@"colorScheme"
#define kADFConfigKeyAgeLow				@"ageLow"
#define kADFConfigKeyAgeHigh			@"ageHigh"
#define kADFConfigKeyTags				@"tags"
#define kADFConfigKeyLocationLookup		@"allowLocationLookup"