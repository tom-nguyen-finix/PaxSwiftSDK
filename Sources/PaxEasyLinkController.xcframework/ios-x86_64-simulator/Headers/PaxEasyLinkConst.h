//
//  PaxEasyLinkConst.h
//  PaxEasyLinkController
//
//  Created by pax on 16/8/19.
//  Copyright © 2016年 jobten. All rights reserved.
//

//
//
/*!
  @abstract BluetoothInfo
 */

@interface BluetoothInfo : NSObject

/*!
 @abstract identifier
 */
@property (nonatomic, copy) NSString *deviceId;
/*!
 @abstract bluetooth name
 */
@property (nonatomic, copy) NSString *deviceName;

@end

/*!
 @abstract PageContentInfo
 */
@interface PageContentInfo : NSObject
/*!
 @abstract widget name
 */
@property (nonatomic, copy) NSString *widgetName;
/*!
 @abstract text
 */
@property (nonatomic, copy) NSString *text;

@end

/*!
 @abstract EUIActionType
 @constant UI_ACTION_SIGNATURE the signature returned by the pos terminal which is signed by the customer.JBIG format
 @constant UI_ACTION_COMMENT_STAR the number of stars returned by the pos terminal which is commented or rated by customer.
 */
typedef enum
{
    UI_ACTION_MESSAGE = 0,
    UI_ACTION_INPUT = 1,
    UI_ACTION_MENU = 2,
    UI_ACTION_PICC_LIGHT = 3,
    UI_ACTION_SIGNATURE = 4,
    UI_ACTION_COMMENT_STAR = 5,
    UI_ACTION_RFU
    
}EUIActionType;

typedef enum{
  PED_NONE = 0x00,
  PED_TLK = 0x01,
  PED_TMK = 0x02,
  PED_TPK = 0x03,
  PED_TAK = 0x04,
  PED_TDK = 0x05,
  PED_TIK = 0x10,
}KeyType;

/*!
 @abstract PageMsgInfo
 */
@interface PageMsgInfo: NSObject

/*!
 @abstract actionType
 */
@property (nonatomic, assign) EUIActionType actionType;

/*!
 @abstract pageData
 */
@property (nonatomic, copy) NSData *pageData;
@end


/*!
 @abstract a BER-TLV item
 */
@interface TlvItem : NSObject

/*!
 @abstract tag
 */
@property NSData *tag;
/*!
 @abstract value
 */
@property NSData *value;

@end

 /*!
 @abstract DataType
 @constant TRANSACTION_DATA  standard emv tlv tag data
 @constant CONFIGURATION_DATA config data
 */
typedef enum
{
    TRANSACTION_DATA = 1,     //standard emv tlv tag data
    CONFIGURATION_DATA,       //config data
} DataType;

#pragma mark 回调函数========================================
/*!
 @abstract deviceInfo return block. see BluetoothInfo
 @param deviceInfo device Info. see @link BluetoothInfo @/link
 */
typedef void (^onSearchOneDeviceCB)(BluetoothInfo *deviceInfo);

typedef void (^didFinishedBlock)();

/*!
 @abstract	processing block
 @param 	current current process value
 @param 	total total process value
 */
typedef void (^onProcessCB)(NSInteger current, NSInteger total);


/*!
 @abstract  status message block
 @param     message current status message
 */
typedef void (^onStatusMessageCB)(NSString *message);

/*!
 @abstract stop download block
 @return   YES:will stop downloading process NO:download
 */
typedef BOOL (^onStopCB)(void);
#pragma mark --设置日志等级========================================
/*!
 @abstract pax log level
 @constant PAX_LOG_LEVEL_NONE   no log
 @constant PAX_LOG_LEVEL_ERR    error log
 @constant PAX_LOG_LEVEL_WRN    warning log
 @constant PAX_LOG_LEVEL_DBG    debug log
 @constant PAX_LOG_LEVEL_INFO   all log
 */
typedef enum {
    
    PAX_LOG_LEVEL_NONE    = 0,
    PAX_LOG_LEVEL_ERR     = 1,
    PAX_LOG_LEVEL_WRN     = 2,
    PAX_LOG_LEVEL_DBG     = 3,
    PAX_LOG_LEVEL_INFO    = 4
    
} PaxLogLevel;
/*!
 @abstractset log level
 @param level log level
 @return	void
 */
void PaxSetLogLevel(PaxLogLevel level);

typedef NS_ENUM(Byte, EM1KeyType) {
    TYPE_A = 0X41,
    TYPE_B = 0X42
};

typedef NS_ENUM(Byte, EM1OperateType) {
    BACKUP = 0x3e,
    DECREMENT = 0x2d,
    INCREMENT = 0x2b,
};
