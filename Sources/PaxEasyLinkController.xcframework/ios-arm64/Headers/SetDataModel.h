//
//  SetDataModel.h
//  PaxEasyLinkController
//
//  Created by hwapp Pax on 2020/1/11.
//  Copyright © 2020 jobten. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BaseRunCmdModel.h"
#import "PaxEasyLinkConst.h"

NS_ASSUME_NONNULL_BEGIN
/*!
 @abstract baseRunCmdModel
 */
@interface SetDataModel : BaseRunCmdModel
/*!
 configTlvs
 */
@property (nonatomic, strong) NSArray<TlvItem *> *configTlvs;
/*!
 emvTlvs
 */
@property (nonatomic, strong) NSArray<TlvItem *> *emvTlvs;

@end

NS_ASSUME_NONNULL_END
