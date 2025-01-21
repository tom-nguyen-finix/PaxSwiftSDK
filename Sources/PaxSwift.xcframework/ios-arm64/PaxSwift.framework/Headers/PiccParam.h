//
//  PiccParam.h
//  PaxEasyLinkController
//
//  Created by Joline Yang on 7/5/22.
//  Copyright © 2022 jobten. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface PiccParam : NSObject

@property (nonatomic, copy) NSString *driverVer;
@property (nonatomic, copy) NSString *driverDate;

@property (nonatomic, assign) Boolean AConductWriteEnable;
@property (nonatomic, assign) Byte AConductVal;

@property (nonatomic, assign) Boolean MConductWriteEnable;
@property (nonatomic, assign) Byte MConductVal;

@property (nonatomic, assign) Boolean BConductWriteEnable;
@property (nonatomic, assign) Byte BConductVal;

@property (nonatomic, assign) Boolean cardBufferWriteEnable;
@property (nonatomic, assign) NSInteger cardBufferVal;

@property (nonatomic, assign) Boolean waitRetryLimitWriteEnable;
@property (nonatomic, assign) NSInteger waitRetryLimitVal;

@property (nonatomic, assign) Boolean cardTypeCheckWriteEnable;
@property (nonatomic, assign) Byte cardTypeCheckVal;

@property (nonatomic, assign) Boolean BCardRxThresholdWriteEnable;
@property (nonatomic, assign) Byte BCardRxThresholdVal;

@property (nonatomic, assign) Boolean FModulateWriteEnable;
@property (nonatomic, assign) Byte FModulateVal;

@property (nonatomic, assign) Boolean AModulateWriteEnable;
@property (nonatomic, assign) Byte AModulateVal;

@property (nonatomic, assign) Boolean ACardRxThresholdWriteEnable;
@property (nonatomic, assign) Byte ACardRxThresholdVal;

@property (nonatomic, assign) Boolean ACardAntennaGainWriteEnable;
@property (nonatomic, assign) Byte ACardAntennaGainVal;

@property (nonatomic, assign) Boolean BCardAntennaGainWriteEnable;
@property (nonatomic, assign) Byte BCardAntennaGainVal;

@property (nonatomic, assign) Boolean FCardAntennaGainWriteEnable;
@property (nonatomic, assign) Byte FCardAntennaGainVal;

@property (nonatomic, assign) Boolean FCardRxThresholdWriteEnable;
@property (nonatomic, assign) Byte FCardRxThresholdVal;

@property (nonatomic, assign) Boolean FConductWriteEnable;
@property (nonatomic, assign) Byte FConductVal;

@property (nonatomic, assign) Boolean userControlWriteEnable;
@property (nonatomic, assign) Byte userControlVal;

@property (nonatomic, assign) Boolean protocolLayerFwtSetWriteEnable;
@property (nonatomic, assign) NSInteger protocolLayerFwtSetVal;

@property (nonatomic, assign) Boolean piccCmdExchangeSetWriteEnable;
@property (nonatomic, assign) Byte piccCmdExchangeSetVal;

@end

NS_ASSUME_NONNULL_END
