//
//  KeyInfo.h
//  PaxEasyLink
//
//  Created by jim.J on 2019/4/2.
//  Copyright © 2019 PAX. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "PaxEasyLinkConst.h"

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract PaxKeyInfo
 */
@interface PaxKeyInfo : NSObject

/*!
 Source key type
 */
@property (nonatomic,assign)KeyType srcKeyType;

/*!
 Soure key index
 */
@property (nonatomic,assign)Byte srcKeyIndex;

/*!
 Destination key type
 */
@property (nonatomic,assign)KeyType dstKeyType;

/*!
 Destination key index
 */
@property (nonatomic,assign)Byte dstKeyIndex;

/*!
 Destination Key len
 */
@property (nonatomic,assign)Byte dstKeyLen;

/*!
 Destination key value
 */
@property (nonatomic,copy)NSData *dstKeyValue;
@end

NS_ASSUME_NONNULL_END
