//
//  PiccApduRecv.h
//  PaxEasyLinkController
//
//  Created by Pax Technology on 10/17/22.
//  Copyright © 2022 jobten. All rights reserved.
//

#import <Foundation/Foundation.h>

/*!
@abstract PiccApduRecv
 */
@interface PiccApduRecv : NSObject

/*!
receive length
 */
@property (nonatomic, assign) NSInteger recvLen;
/*!
receive data
 */
@property (nonatomic, copy) NSData *recvData;

@end


