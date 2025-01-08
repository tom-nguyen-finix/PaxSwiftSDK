//
//  BaseReportModel.h
//  PaxEasyLinkController
//
//  Created by hwapp Pax on 2020/1/11.
//  Copyright © 2020 jobten. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "PaxEasyLinkConst.h"

NS_ASSUME_NONNULL_BEGIN

@interface BaseReportModel : NSObject
/*！
 status
 */
@property (nonatomic, strong) NSString *status;
/*!
 configTlvList
 */
@property (nonatomic, strong) NSArray<TlvItem *> *configTlvList;
/*!
 emvTlvList
 */
@property (nonatomic, strong) NSArray<TlvItem *> *emvTlvList;


@end

NS_ASSUME_NONNULL_END
