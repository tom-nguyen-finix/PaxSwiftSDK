//
//  WriteKeyModel.h
//  PaxEasyLinkController
//
//  Created by hwapp Pax on 2020/1/11.
//  Copyright © 2020 jobten. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BaseRunCmdModel.h"
#import "KeyParam.h"

NS_ASSUME_NONNULL_BEGIN
/*!
 @abstract writeKeyModel
 */
@interface WriteKeyModel : BaseRunCmdModel
/*!
  keyParam
 */
@property (nonatomic, strong) KeyParam *keyParam;

@end

NS_ASSUME_NONNULL_END
