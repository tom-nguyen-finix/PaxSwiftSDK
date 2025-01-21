//
//  PaxAppList.h
//  PaxEasyLinkController
//
//  Created by Joline Yang on 7/15/20.
//  Copyright © 2020 jobten. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
/*!
@abstract PaxAppList
*/
@interface PaxAppList : NSObject

@property (nonatomic, copy) NSString *appLabel;

@property (nonatomic, assign) NSInteger appIndex;

@end

NS_ASSUME_NONNULL_END
