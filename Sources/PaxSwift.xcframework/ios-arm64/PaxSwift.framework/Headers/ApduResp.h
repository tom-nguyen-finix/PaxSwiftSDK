//
//  ApduResp.h
//  PaxEasyLinkController
//
//  Created by Pax Technology on 10/18/22.
//  Copyright © 2022 jobten. All rights reserved.
//

#import <Foundation/Foundation.h>

/*!
@abstract ApduResp
 */
@interface ApduResp : NSObject

/*!
length
 */
@property (nonatomic, assign) NSInteger len;

/*!
data
 */
@property (nonatomic, copy) NSData *data;

/*!
swa
 */
@property (nonatomic, assign) Byte swa;

/*!
swb
 */
@property (nonatomic, assign) Byte swb;

@end
