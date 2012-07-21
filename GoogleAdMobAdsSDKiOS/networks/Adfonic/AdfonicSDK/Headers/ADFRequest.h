//
//  ADFRequest.h
//  Adfonic SDK
//
//  Copyright 2011-12 Adfonic Ltd. All rights reserved.
//

typedef enum {
	ADFRequestGenderUnknown = 0,
	ADFRequestGenderFemale,
	ADFRequestGenderMale,
} ADFRequestGender;

typedef struct {
	NSUInteger low;
	NSUInteger high;
} ADFRequesAgeRange;

@interface ADFRequest : NSObject

+ (NSDictionary *)configurationForRequest:(ADFRequest *)request;

+ (ADFRequest *)requestForType:(NSString *)type;
+ (ADFRequest *)requestForSlotID:(NSString *)slotID;

+ (void)setupRequest:(ADFRequest *)request withDictionary:(NSDictionary *)dict;

+ (void) performInstallAppTracking;

// Ad identifiers
@property (nonatomic, copy) NSString *slotIdentifier;
@property (nonatomic, copy) NSString *type;

#pragma mark Hints

//@property (nonatomic) NSTimeInterval autorefreshTime;

@property (nonatomic, copy) NSString *contentSizeIdentifier;

///@name Ad Loading Hints

/** Banner's context tags.
 
 This can be used as hints for the banner to try and load ads related to the context.
 
 If this is set to `nil`, it will try to load tags from the configuration file.
 Set this to an empty array if you want to override configuration file for empty values.
 */
@property (nonatomic, copy) NSArray *tags;

/** Banner's color scheme.
 
 The banner will try to load advertisments with a the specified color scheme.
 
 If this is set to `nil`, it will try to load color schemes from the configuration file.
 Set this to an empty string if you want to override configuration file for empty values.
 
 Valid values are `ADFColorSchemeBlue`, `ADFColorSchemeGreen`, `ADFColorSchemeOrange`,
 `ADFColorSchemePurple`, `ADFColorSchemeRed`, and `ADFColorSchemeYellow`.
 */
@property (nonatomic, copy) NSString *colorScheme;

/** User's gender. */
@property (nonatomic) ADFRequestGender gender;

/** User's date of birth. */
@property (nonatomic, copy) NSDate *dateOfBirth;

/** User's age, in years. */
@property (nonatomic) NSUInteger age;

/** User's age range.
 
 If range is equal to `{0,0}`, the receiver will try to load age range from the configuration file.
 Set the ageRange's location to `NSNotFound` if you want to override configuration file for empty values.
 */
@property (nonatomic) ADFRequesAgeRange ageRange;

/** Indicates whether user's location information can be used if available.
 
 If set to `YES`, will use the device's location to load ads local to the user.
 Setting this to `YES` will never cause a request dialoge to be shown to the user.
 It will use location only if the user has already granted permission to the App to use location.
 */
@property (nonatomic, getter=isLocationLookupEnabled) BOOL locationLookupEnabled;

@property (nonatomic) BOOL isTest;

@end
