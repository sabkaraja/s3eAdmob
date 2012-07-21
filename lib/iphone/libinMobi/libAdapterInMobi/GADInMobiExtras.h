//
//  GADInMobiExtras.h
//

#import <Foundation/Foundation.h>

#import "GADAdNetworkExtras.h"
#import <CoreLocation/CoreLocation.h>

@interface GADInMobiExtras : NSObject <GADAdNetworkExtras>

/**
 * Provide additional values to be passed in the ad request as key-value pair.
 */
@property (nonatomic, retain) NSDictionary *additionalParameters;

/**
 * Provide user's city in the format "city-state-country" for
 * city-level targetting.
 */
- (void)setLocationWithCity:(NSString *)_city
                      state:(NSString *)_state
                    country:(NSString *)_country;

/**
 * The login ID value.
 */
@property (nonatomic, copy) NSString *loginID;

/**
 * The session ID value.
 */
@property (nonatomic, copy) NSString *sessionID;

/**
 * Postal code of the user may be used to deliver more relevant ads.
 */
@property( nonatomic,copy) NSString *postalCode;

/**
 * Area code of the user may be used to deliver more relevant ads.
 */
@property( nonatomic,copy) NSString *areaCode;

/**
 * Use contextually relevant strings to deliver more relevant ads.
 * Example: @"offers sale shopping"
 */
@property( nonatomic,copy) NSString *keywords;

/**
 * Search string provided by the user. Example: @"Hotel Bangalore India"
 */
@property( nonatomic,copy) NSString *searchString;

/**
 * Optional, if the user has specified income.
 * @note - Income should be in USD.
 */
@property( nonatomic,assign) NSUInteger income;

/**
 * Age of the user may be used to deliver more relevant ads.
 * @note - Look for the IMAdRequest.h class to set the relevant values. 
 */
@property( nonatomic,assign) NSUInteger age;

/**
 * Use contextually relevant strings to deliver more relevant ads.
 * Example: @"cars bikes racing"
 */
@property( nonatomic,copy) NSString *interests;

/**
 * Use this property to set the user's current location to deliver
 * more relevant ads.
 * Disclaimer: Do not use Core Location just for advertising.
 * Ensure that it is used in your app for more constructive reasons as well.
 * It is both a good idea and part of Apple's guidelines.
 */
@property (nonatomic,retain) CLLocation *location;

/**
 * For internal purpose only.
 */
@property (nonatomic, copy) NSString *cityLocation;

@end
