//
//  ApduReq.h
//  fat
//
//  Created by Pax Technology on 10/18/22.
//  Copyright © 2022 jobten. All rights reserved.
//

#import <Foundation/Foundation.h>

/*!
@abstract ApduReq
 */
@interface ApduReq : NSObject

/*!
CLA,INS,P1,P2
 */
@property (nonatomic, assign) NSData *cmd;

/*!
the length of data that send to icc card
 */
@property (nonatomic, assign) NSInteger lc;

/*!
data
 */
@property (nonatomic, assign) NSData *data;

/*!
expect length of icc response
 */
@property (nonatomic, assign) NSInteger le;

@end
