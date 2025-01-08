//
//  AppSelectRequest.h
//  PaxEasyLinkController
//
//  Created by Joline Yang on 6/30/22.
//  Copyright © 2022 jobten. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
/*!
 @abstract AppSelectRequest
 */
@interface AppSelectRequest : NSObject

@property NSString *appPreName;

@property NSString *appLabel;

@property NSString *issDiscrData;

@property NSString *aid;

@property int aidLen;

@property int priority;

@property NSString *appName;

+ (NSString *)toString:(AppSelectRequest *)appInfo;

@end

NS_ASSUME_NONNULL_END
