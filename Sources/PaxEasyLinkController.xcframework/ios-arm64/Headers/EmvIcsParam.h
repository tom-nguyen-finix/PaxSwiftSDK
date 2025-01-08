//
//  EmvIcsParam.h
//  PaxEasyLinkController
//
//  Created by hwapp Pax on 2020/1/8.
//  Copyright © 2020 jobten. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
/*!
 @abstract EmvIcsParam
 */
@interface EmvIcsParam : NSObject
/*!
 cardDataInputCapability
 */
@property (nonatomic,assign) NSString *cardDataInputCapability;
/*!
 cvmCapability
 */
@property (nonatomic,assign) NSString *cvmCapability;
/*!
 securityCapability
 */
@property (nonatomic,assign) NSString *securityCapability;
/*!
 additionalTerminalCapabilities
 */
@property (nonatomic,assign) NSString *additionalTerminalCapabilities;
/*!
 getDataForPinTryCounter
 */
@property int getDataForPinTryCounter;
/*!
 bypassPinEntry
 */
@property int bypassPinEntry;
/*!
 subsequentBypassPinEntry
 */
@property int subsequentBypassPinEntry;
/*!
 exceptionFileSupported
 */
@property int exceptionFileSupported;
/*!
 forcedOnlineCapability
 */
@property int forcedOnlineCapability;
/*!
 issuerReferralsSupported
 */
@property int issuerReferralsSupported;

@end

NS_ASSUME_NONNULL_END
