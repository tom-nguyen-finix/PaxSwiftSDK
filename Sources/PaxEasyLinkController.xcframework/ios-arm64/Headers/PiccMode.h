//
//  PiccMode.h
//  fat
//
//  Created by Joline Yang on 7/5/22.
//  Copyright © 2022 jobten. All rights reserved.
//

/*!
@abstract PiccSetupMode
 */
typedef enum {
    READ         = 0x52,
    WRITE        = 0x57,
}PiccSetupMode;

/*!
@abstract EDetectMode
 */
typedef enum {
    EMV_AB      = 0x00,
    ONLY_A      = 0x41,
    ONLY_B      = 0x42,
    ONLY_M      = 0x43,
} EDetectMode;

/*!
@abstract EPiccRemoveMode
 */
typedef enum {
    HALT        = 0x48,
    REMOVE      = 0x52,
    EMV         = 0x45,
}EPiccRemoveMode;

/*!
@abstract ELedStatus
 */
typedef enum {
    ON        = 0x01,
    OFF       = 0x00,
}ELedStatus;





