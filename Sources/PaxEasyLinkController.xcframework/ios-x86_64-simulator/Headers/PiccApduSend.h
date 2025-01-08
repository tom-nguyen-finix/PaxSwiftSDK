//
//  PiccApduSend.h
//  fat
//
//  Created by Pax Technology on 10/17/22.
//  Copyright © 2022 jobten. All rights reserved.
//

#import <Foundation/Foundation.h>

/*!
@abstract PiccApduSend
 */
@interface PiccApduSend : NSObject

/*!
send length
 */
@property (nonatomic, assign) NSInteger sendLen;
/*!
send data 
 */
@property (nonatomic, copy) NSData *sendData;

@end
