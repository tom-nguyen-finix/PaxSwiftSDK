//
//  EmvAidParam.h
//  PaxEasyLinkController
//
//  Created by hwapp Pax on 2020/1/8.
//  Copyright © 2020 jobten. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
/*!
  @abstract emvAidParam
*/
@interface EmvAidParam : NSObject
/*!
 appId
 */
@property (nonatomic,assign) NSString *applicationId;
/*!
 partialAidSelect
 */
@property int partialAidSelection;
/*!
 ifUseLocalAidName
 */
@property int ifUseLocalAidName;
/*!
 localAidName
 */
@property (nonatomic,assign) NSString *localAidName;
/*!
 terminalAidVersion
 */
@property (nonatomic,assign) NSString *terminalAidVersion;
/*!
 tacDenial
 */
@property (nonatomic,assign) NSString *tacDenial;
/*!
 tacOnline
 */
@property (nonatomic,assign) NSString *tacOnline;
/*!
 tacDefault
 */
@property (nonatomic,assign) NSString *tacDefault;
/*!
 floorLimit
 */
@property (nonatomic, assign) NSString *floorLimit;
/*!
 threshold
 */
@property int threshold;
/*!
 targetPercentage
 */
@property int targetPercentage;
/*!
 maxTargetPercentage
 */
@property int maxTargetPercentage;
/*!
 terminalDefaultTDOL
 */
@property (nonatomic,strong) NSString *terminalDefaultTDOL;
/*!
 terminalDefaultDDOL
 */
@property (nonatomic,strong) NSString *terminalDefaultDDOL;
/*!
 terminalRiskManagementData
 */
@property (nonatomic,strong) NSString *terminalRiskManagementData;

@end

NS_ASSUME_NONNULL_END
