//
//  TikKeyParam.h
//  PaxEasyLinkController
//
//  Created by hwapp Pax on 2020/1/17.
//  Copyright © 2020 jobten. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
/*!
 @abstract tikKeyParam
 */
@interface TikKeyParam : NSObject
/*!
 groupIndex
 */
@property (nonatomic, assign) Byte groupIndex;
/*!
srcKeyIndex
*/
@property (nonatomic, assign) Byte srcKeyIndex;
/*!
keyValue
*/
@property (nonatomic, copy) NSString *keyValue;
/*!
ksn
*/
@property (nonatomic, copy) NSString *ksn;
/*!
checkMode
*/
@property (nonatomic, assign) Byte checkMode;
/*!
checkBuf
*/
@property (nonatomic, copy) NSString *checkBuf;

@end

NS_ASSUME_NONNULL_END
