//
//  SetEmvAidParamModel.h
//  PaxEasyLinkController
//
//  Created by hwapp Pax on 2020/1/11.
//  Copyright © 2020 jobten. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BaseRunCmdModel.h"
#import "EmvAidParam.h"

NS_ASSUME_NONNULL_BEGIN

@interface SetEmvAidParamModel : BaseRunCmdModel

@property (nonatomic, strong) EmvAidParam *emvAidParam;

@end

NS_ASSUME_NONNULL_END
