//
//  TrackData.h
//  PaxEasyLinkController
//
//  Created by Joline Yang on 7/8/22.
//  Copyright © 2022 jobten. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
@abstract TrackData
 */
@interface TrackData : NSObject

/*!
Track Data Status
 */
@property (nonatomic, assign) NSInteger status;
/*!
Track Data
 */
@property (nonatomic, copy) NSData *trackData;

@end

NS_ASSUME_NONNULL_END
