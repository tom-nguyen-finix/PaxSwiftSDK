//
//  EasyUtils.h
//  EasyLinkTestDemo
//
//  Created by  Shawn on 11/16/16.
//  Copyright (c) 2016 PAX. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface EasyUtils : NSObject
+ (NSString*)hexStringForData:(NSData*)data;
+ (NSString*)hexStringForChar:(unsigned char *)data len:(int)len;
+ (NSData*)dataForHexString:(NSString*)hexString;
@end
