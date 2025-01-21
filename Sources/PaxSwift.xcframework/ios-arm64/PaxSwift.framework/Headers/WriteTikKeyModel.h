//
//  WriteTikKeyModel.h
//  PaxEasyLinkController
//
//  Created by hwapp Pax on 2020/1/11.
//  Copyright © 2020 jobten. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BaseRunCmdModel.h"
#import "TikKeyParam.h"

NS_ASSUME_NONNULL_BEGIN
/*!
@abstract writeTikKeyModel
*/
@interface WriteTikKeyModel : BaseRunCmdModel
/*!
 tikKeyParam
*/
@property (nonatomic, strong) TikKeyParam *tikKeyParam;

@end

NS_ASSUME_NONNULL_END
