//
//  SetEmvIcsParamModel.h
//  PaxEasyLinkController
//
//  Created by hwapp Pax on 2020/1/11.
//  Copyright © 2020 jobten. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BaseRunCmdModel.h"
#import "EmvIcsParam.h"

NS_ASSUME_NONNULL_BEGIN

@interface SetEmvIcsParamModel : BaseRunCmdModel

@property (nonatomic, strong) EmvIcsParam *emvIcsParam;

@end

NS_ASSUME_NONNULL_END
