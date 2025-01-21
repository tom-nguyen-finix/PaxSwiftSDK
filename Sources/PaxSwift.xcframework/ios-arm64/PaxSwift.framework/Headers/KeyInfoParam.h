//
//  KeyInfoParam.h
//  PaxEasyLinkController
//
//  Created by Joline Yang on 7/17/20.
//  Copyright © 2020 jobten. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "PaxEasyLinkConst.h"

NS_ASSUME_NONNULL_BEGIN
/*!
@abstract KeyInfoParam
*/
@interface KeyInfoParam : NSObject

/*!
Key type
 */
@property (nonatomic,assign)KeyType keyType;

/*!
Key group Index
 */
@property (nonatomic,assign)Byte groupIndex;

@end

NS_ASSUME_NONNULL_END
