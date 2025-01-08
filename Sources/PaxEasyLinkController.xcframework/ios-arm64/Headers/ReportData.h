//
//  ReportData.h
//  PaxEasyLinkController
//
//  Created by hwapp Pax on 2020/1/11.
//  Copyright © 2020 jobten. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BaseReportModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface ReportData<ObjectType> : BaseReportModel

@property (nonatomic,strong) ObjectType param;

-(void)setParam:(ObjectType)param;
-(ObjectType)getParam;

@end
NS_ASSUME_NONNULL_END
