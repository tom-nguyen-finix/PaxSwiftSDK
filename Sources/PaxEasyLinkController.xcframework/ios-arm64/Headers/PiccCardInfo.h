//
//  PiccCardInfo.h
//  fat
//
//  Created by Joline Yang on 7/6/22.
//  Copyright © 2022 jobten. All rights reserved.
//
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
/*!
 @abstract PiccCardInfo
 */
@interface PiccCardInfo : NSObject

@property (nonatomic, assign) Byte cardType;
@property (nonatomic, assign) Byte cid;
@property (nonatomic, copy) NSData* serialInfo;
@property (nonatomic, copy) NSData* other;

@end

NS_ASSUME_NONNULL_END

