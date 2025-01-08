//
//  KeyParam.h
//  PaxEasyLinkController
//
//  Created by hwapp Pax on 2020/1/17.
//  Copyright © 2020 jobten. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
/*!
 keyParam
 */
@interface KeyParam : NSObject
/*!
 srcKeyType
 */
@property (nonatomic, assign) Byte srcKeyType;
/*!
srcKeyIndex
*/
@property (nonatomic, assign) Byte srcKeyIndex;
/*!
dstKeyType
*/
@property (nonatomic, assign) Byte dstKeyType;
/*!
dstKeyIndex
*/
@property (nonatomic, assign) Byte dstKeyIndex;
/*!
dstKeyValue
*/
@property (nonatomic, copy) NSString *dstKeyValue;
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
