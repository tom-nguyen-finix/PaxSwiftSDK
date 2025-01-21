//
//  PaxEasyLinkProtocol.h
//  PaxEasyLinkController
//
//  Created by pax on 16/8/19.
//  Copyright © 2016年 jobten. All rights reserved.
//
#import <Foundation/Foundation.h>
#import "PaxEasyLinkConst.h"
#import "PaxEasyLinkStatusCode.h"
#import "PaxKeyInfo.h"
#import "PaxKcvInfo.h"
#import "PaxTikInfo.h"
#import "KeyInfoParam.h"
#import "PiccMode.h"
#import "PiccParam.h"
#import "PiccCardInfo.h"
#import "PiccApduSend.h"
#import "PiccApduRecv.h"
#import "TrackData.h"
#import "ApduReq.h"
#import "ApduResp.h"
#import "ISyncAndProcessListener.h"
#import "SmartlandingSDK-Swift.h"

#pragma mark ===========BlueTooth=======================================
/*!
  @protocol PaxBluetoothDelegate
 */

/*!
 @abstract disconnected callback prototype (currently used for Bluetooth)
 @param addr    address
 @param name    name
 */
typedef void (^didDisconnectedBlock)(NSString *addr, NSString *name);

@protocol PaxBluetoothDelegate <NSObject>


/*!
 @abstract  Get version name
 @return NSString
 */
-(NSString *)getVersionName;

/*!
 @abstract  Search devices
 @param timeout timeout for searching devices (s)
 @param searchOneDeviceCB Success Block. @link onSearchOneDeviceCB @/link 
 */


- (void)startSearchDev:(NSInteger)timeout
  searchOneDeviceBlock:(onSearchOneDeviceCB)searchOneDeviceCB;

/*!
 @abstract  Search devices
 @param timeout timeout for searching devices (s)
 @param searchOneDeviceCB Success Block. @link onSearchOneDeviceCB @/link
 @param didFinished finish callback @link didFinishedBlock @/link
 */


- (void)startSearchDev:(NSInteger)timeout
  searchOneDeviceBlock:(onSearchOneDeviceCB)searchOneDeviceCB didFinished:(didFinishedBlock)didFinished;

/*!
 @abstract  Build connection with BT
 @param deviceUUID bluetooth identifier
 @return  @link PaxEasyLinkRetCode @/link
 */
-(PaxEasyLinkRetCode)connectDevice:(NSString *)deviceId;

/*!
 @abstract  Build connection with BT
 @param deviceUUID bluetooth identifier
 @param timeout bluetooth connection timeout
 @return  @link PaxEasyLinkRetCode @/link
 */
-(PaxEasyLinkRetCode)connectDevice:(NSString *)deviceId timeoutLength:(NSInteger)timeout;

/*!
 @abstract  Build connection with BT
 @param deviceUUID bluetooth identifier
 @param block  call back when bt disconnected
 @return @link  PaxEasyLinkRetCode @/link
 */
-(PaxEasyLinkRetCode)connectDevice:(NSString *)deviceId didDisconnectedBlock:(didDisconnectedBlock)block;

/*!
 @abstract  Build connection with BT
 @param deviceUUID bluetooth identifier
 @param timeout bluetooth connection timeout
 @param block  call back when bt disconnected
 @return @link  PaxEasyLinkRetCode @/link
 */
-(PaxEasyLinkRetCode)connectDevice:(NSString *)deviceId timeoutLength:(NSInteger)timeout didDisconnectedBlock:(didDisconnectedBlock)block;

/*!
 @abstract  Build connection with TCP/IP
 @param host ip of the pos terminal
 @param port
 @return @link PaxEasyLinkRetCode @/link
 */
-(PaxEasyLinkRetCode)connectDevice:(NSString *)host port:(NSInteger)port;

/*!
 @abstract closeDevice
 @return  @link PaxEasyLinkRetCode @/link
 */
- (PaxEasyLinkRetCode)closeDevice;

/*!
 @abstract  check if connected
 @return true:connected, false:no connected
 */
- (BOOL)isConnected;

@end

#pragma mark -- transaction========================================

/*!
 @protocol PaxTransDelegate
 */
@protocol PaxTransDelegate <NSObject>

/*!
 @abstract startTransaction
 @discussion
   Detect card(MSR, EMV CHIP, EMV Contactless), and do corresponding processing.
   Read track1, track2, track3 data, if MSR is swiped
   Application selection, initial processing, terminal risk management, ODA, CVM, 1st GAC, if EMV Chip card is inserted
   Application selection, get final selected application data, Paywave/Mastercard contactless/... processing, restriction processing, ODA, CVM, ..., if EMV contactless card is tapped
 @return  @link PaxEasyLinkRetCode @/link
 */
-(PaxEasyLinkRetCode) startTransaction;

/*!
 @abstract completeTransaction
 @discussion
   Issuer data verification, perform script for EMV, EMV contactless card
 @return @link PaxEasyLinkRetCode @/link
 */
-(PaxEasyLinkRetCode) completeTransaction;

/*!
 @abstract clearTransaction
 @discussion
   clear transaction data
 @return @link PaxEasyLinkRetCode @/link
 */
-(PaxEasyLinkRetCode) clearTransaction;

/*!
 @abstract getCardBinIndex
 @discussion
   get card bin index from card bin range list
 @param data card bin range list
 @param index [output] index of current card bin in card bin range list
 @return @link PaxEasyLinkRetCode @/link
 */
-(PaxEasyLinkRetCode) getCardBinIndex:(NSData *)data index:(NSData **)index;

/*!
 @abstract checkCardLuhn
  <p>Check current card number Luhn</p>
 <p>This is a time-consuming task, please do it on a new thread, cause you can't do time-consuming tasks on the UI thread directly.</p>
 
 @return @link PaxEasyLinkRetCode @/link
 */
-(PaxEasyLinkRetCode) checkCardLuhn;

/*!
 @abstract Get PINBLOCK
 @param PAN - non-shifted PAN data,  or "", if "", then POS terminal will use the PAN data stored (which read in StartTransaction API) to calculate the PINBLOCK
 @param pinCB [output] Pin
 @param ksnCB [output] ksn
 @return @link PaxEasyLinkRetCode @/link
 */
- (PaxEasyLinkRetCode) inputPin:(NSString *)PAN pinBlock:(NSData**)pinCB ksnBlock:(NSData**)ksnCB;
/*!
 @abstract Encrypt data
 @param data  data to be encrypted
 @param encrypyedData [output] encrypted Result
 @return @link PaxEasyLinkRetCode @/link
 */
- (PaxEasyLinkRetCode) encryptData: (NSData *)data encrypyedData:(NSData**)encrypyedData;


/*!
 @abstract increase ksn
 @return @link PaxEasyLinkRetCode @/link
*/
 
- (PaxEasyLinkRetCode)increaseKsn:(NSData *)data;
/*!
@abstract Get Key Information
@param keyInfoParam - KeyInfoParam
@param keyinfo [output] - key information, Enable Flag(1 byte) + Kcv(4 Bytes) +KSN(10 Bytes)
@return @link PaxEasyLinkRetCode @/link
*/
- (PaxEasyLinkRetCode) GetKeyInfo:(KeyInfoParam *)keyInfoParam KeyInfo:(NSData**)keyinfo;

/*!
 writekey
 
 @abstract Once received the CMD_WRITE_KEY command from Master devices, the POS terminal will write the key into PED with requested index

 @param keyInfo keyInfo
 @param kcvInfo kcvInfo
 @return @link PaxEasyLinkRetCode @/link
 */
- (PaxEasyLinkRetCode)writeKeyInfo:(PaxKeyInfo *)keyInfo kcvInfo:(PaxKcvInfo *)kcvInfo;


/*!
 writeTIK
 
 @abstract Write TIK into PED and optionally check KCV

 @param tilInfo tilInfo
 @param kcvInfo kcvInfo
 @return @link PaxEasyLinkRetCode @/link
 */
- (PaxEasyLinkRetCode)writeTIK:(PaxTikInfo *)tilInfo kcvInfo:(PaxKcvInfo *)kcvInfo;

/*!
 send cancel

 @return @link PaxEasyLinkRetCode @/link
 */
- (PaxEasyLinkRetCode)sendCancel;
/*!
 @abstract This API is used to calculate MAC. To encrypt data, please invoke setData API to set TAG 0210 (macKeyIdx) and TAG 0212 (macKeyType) first
 
 @param Parameters:<br>
        <p>data - data to be encrypted
        <p>mac - out parameter
 @return @link PaxEasyLinkRetCode @/link

 */
- (PaxEasyLinkRetCode)CalcMAC:(NSData*)data MAC:(NSData**)mac;
 /*!@abstract SetData
   Set up the TAG data (Terminal application parameter, Transaction parameter, EMV, EMV contactless)
 @param dataType see @link DataType @/link  TRANSACTION_DATA:1 CONFIGURATION_DATA:2
 @param dataList  TLV data list
 @param tagList tagList return
 @return @link PaxEasyLinkRetCode @/link
 */
- (PaxEasyLinkRetCode) setData:(NSInteger)dataType dataList:(NSData*)dataList tagList:(NSData**)tagList;
/*!
 @abstract GetData
  Get value the TAG list (Terminal application parameter, Transaction parameter, EMV, EMV contactless)
 @param dataType  see @link DataType @/link  TRANSACTION_DATA:1 CONFIGURATION_DATA:2
 @param tagList  TAG list
 @param dataList tagList return
 @return  @link PaxEasyLinkRetCode @/link
 */
- (PaxEasyLinkRetCode) getData:(NSInteger)dataType tagList:(NSData*)tagList dataList:(NSData **)dataList;

/*!
 @abstract GetData
 Get value the TAG list (Terminal application parameter, Transaction parameter, EMV, EMV contactless)
 @param dataType  see @link DataType @/link  TRANSACTION_DATA:1 CONFIGURATION_DATA:2
 @param tagList  TAG list
 @param tlvArray an array of MposTlvItem objects
 @return @link PaxEasyLinkRetCode @/link
 */
- (PaxEasyLinkRetCode) getData:(NSUInteger)dataType tagList:(NSData*)tagList tlvArray:(NSArray**)tlvArray;

/*!
 @abstract replaceData
 Replaces value of contact EMV or contactless EMV sensitive TAGs, transaction sensitive data.
 @param dataType  see @link DataType @/link  TRANSACTION_DATA:1 CONFIGURATION_DATA:2
 @param tlvData  TLV list to be replaced
 @param resultData out parameter, 2 bytes length + result content
 @return @link PaxEasyLinkRetCode @/link
 */
- (PaxEasyLinkRetCode) replaceData:(NSUInteger)dataType tlvData:(NSData *)tlvData resultData:(NSData **)resultData;

/*!
 @abstract showPage
  Show message which configured in UI XML file in POS terminal
 @param pageName - The name of page which configured in UI XML file. To show the page;
 @param timeOut - showPage timeOut(ms)
 @param pageContentInfo -
 @param actiontype: - ui action type  0:Message 1:Input 2:Menu 3:PICC light(no use) 4:signature 5:Coment start 6:RFU
 @param returnData: returned data like signature
 @discussion
  Set PageContentInfo arrayList, if need to change the displaying text of widget configured in UI XML.
 						eg. below is the configuration of textbox in UI XML file:
  						  "<TextBox name="prompt1" x="0" y="0" value="PAX" fontSize="0" textAlign="1" mode="0" keyAccept="1"></TextBox>"
 						If need to change the displaying text, set the showMsgInfo.widgetName = "prompt1", showMsgInfo.text = "PLS REMOVE CARD";
 @return @link PaxEasyLinkRetCode @/link
 */
- (PaxEasyLinkRetCode) showPage:(NSString *)pageName timeOut:(short)timeOut pageContentInfo:(NSArray *)pageContentInfo PageMagInfo:(PageMsgInfo**)pageMsgInfo;

/*!
 @abstract showPage
 Show message which configured in UI XML file in POS terminal
 @param pageName - The name of page which configured in UI XML file. To show the page;
 @param timeOut - showPage timeOut(ms)
 @param pageContentInfo -
 @discussion
 Set PageContentInfo arrayList, if need to change the displaying text of widget configured in UI XML.
 eg. below is the configuration of textbox in UI XML file:
 "<TextBox name="prompt1" x="0" y="0" value="PAX" fontSize="0" textAlign="1" mode="0" keyAccept="1"></TextBox>"
 If need to change the displaying text, set the showMsgInfo.widgetName = "prompt1", showMsgInfo.text = "PLS REMOVE CARD";
 @return @link PaxEasyLinkRetCode @/link
 */
- (PaxEasyLinkRetCode) showPage:(NSString *)pageName timeOut:(short)timeOut pageContentInfo:(NSArray *)pageContentInfo;

/*!
 @abstract showPage
 Show message which configured in UI XML file in POS terminal
 @param pageName - The name of page which configured in UI XML file. To show the page;
 @param timeOut - showPage timeOut(ms)
 @param actionType - current action type, see @link PaxEasyLinkConst @/link
 @param respLen - the required response length
 @param pageContentInfo -
 @discussion
 Set PageContentInfo arrayList, if need to change the displaying text of widget configured in UI XML.
 eg. below is the configuration of textbox in UI XML file:
 "<TextBox name="prompt1" x="0" y="0" value="PAX" fontSize="0" textAlign="1" mode="0" keyAccept="1"></TextBox>"
 If need to change the displaying text, set the showMsgInfo.widgetName = "prompt1", showMsgInfo.text = "PLS REMOVE CARD";
 @return @link PaxEasyLinkRetCode @/link
 */
- (PaxEasyLinkRetCode) showPage:(NSString *)pageName timeOut:(short)timeOut actionType:(EUIActionType)actionType respLen:(NSInteger)respLen pageContentInfo:(NSArray *)pageContentInfo PageMagInfo:(PageMsgInfo**)pageMsgInfo;


/*!
 @abstract fileDownLoad
  Send file to POS terminal,if update the UI in downloadProcessCB,UI must be updated in the main thread
 @param fileName - Name of file to be sent
 @param filePath - Path of file
 @param downloadProcessCB downloadProcess Block.see @link onProcessCB @/link
 @return @link PaxEasyLinkRetCode @/link
 */
-(PaxEasyLinkRetCode) fileDownLoad:(NSString *)fileName filePath:(NSString *)filePath processBlock:(onProcessCB)downloadProcessCB;

/*!
 @abstract fileDownLoad
   Send file to POS terminal,if update the UI in downloadProcessCB,UI must be updated in the main thread. can stop downLoad process by @link onStopCB @/link
 @param fileName - Name of file to be sent
 @param filePath - Path of file
 @param downloadProcessCB downloadProcess Block.see @link onProcessCB @/link
 @param stopDownLoadCB  stop download Block.see @link onStopCB @/link
 @return  @link PaxEasyLinkRetCode @/link
 */
-(PaxEasyLinkRetCode) fileDownLoad:(NSString *)fileName filePath:(NSString *)filePath processBlock:(onProcessCB)downloadProcessCB stopDownLoadBlock:(onStopCB)stopDownLoadCB;

/*!
 @abstract Switch communication mode
 @param protocolType
 @return @link PaxEasyLinkRetCode @/link
 */
-(PaxEasyLinkRetCode) switchCompatibleMode: (NSInteger)protoclType;

/*!
@abstract rkiRemoteKeyDownload
  Remote download key into mPOS device, update the UI in onStatusMessageCB,UI must be updated in the main thread.
@deprecated This method is deprecated and will be removed in a future version. Use the new rkiRemoteKeyDownload() with rkiBundlePath parameter instead.
@param hostUrl - URL  of RKI Server
@param hostPort - Port  of RKI Server
@param showStatusCB show status message Block.see @link onStatusMessageCB @/link
@return  @link PaxEasyLinkRetCode @/link
*/
-(PaxEasyLinkRetCode) rkiRemoteKeyDownload:(NSString *)hostUrl hostPort:(NSString *)hostPort statusMessageBlock:(onStatusMessageCB)showStatusCB __deprecated;

/*!
@abstract rkiRemoteKeyDownload
  Remote download key into mPOS device, update the UI in onStatusMessageCB,UI must be updated in the main thread.
@param hostUrl - URL  of RKI Server
@param hostPort - Port  of RKI Server
@param rkiBundlePath - path of rkiCert.bundle
@param showStatusCB show status message Block.see @link onStatusMessageCB @/link
@return  @link PaxEasyLinkRetCode @/link
*/
-(PaxEasyLinkRetCode) rkiRemoteKeyDownload:(NSString *)hostUrl hostPort:(NSString *)hostPort rkiBundlePath:(NSString *)rkiBundlePath statusMessageBlock:(onStatusMessageCB)showStatusCB;

/*!
@abstract rkiUnBindDevice
  Remote unbind mPOS device from RKI server,  update the UI in onStatusMessageCB,UI must be updated in the main thread.
@deprecated This method is deprecated and will be removed in a future version. Use the new rkiUnBindDevice() with rkiBundlePath parameter instead.
@param hostUrl - URL  of RKI Server
@param hostPort - Port  of RKI Server
@param showStatusCB show status message Block.see @link onStatusMessageCB @/link
@return  @link PaxEasyLinkRetCode @/link
*/
-(PaxEasyLinkRetCode) rkiUnBindDevice:(NSString *)hostUrl hostPort:(NSString *)hostPort statusMessageBlock:(onStatusMessageCB)showStatusCB __deprecated;

/*!
@abstract rkiUnBindDevice
  Remote unbind mPOS device from RKI server,  update the UI in onStatusMessageCB,UI must be updated in the main thread.
@param hostUrl - URL  of RKI Server
@param hostPort - Port  of RKI Server
@param rkiBundlePath - path of rkiCert.bundle
@param showStatusCB show status message Block.see @link onStatusMessageCB @/link
@return  @link PaxEasyLinkRetCode @/link
*/
-(PaxEasyLinkRetCode) rkiUnBindDevice:(NSString *)hostUrl hostPort:(NSString *)hostPort rkiBundlePath:(NSString *)rkiBundlePath statusMessageBlock:(onStatusMessageCB)showStatusCB;
/*!
@abstract rkiInjectOfflineKey
  Inject offline key into mPOS device,   update the UI in onStatusMessageCB,UI must be updated in the main thread.
@param filePath - offline key file name and path
@param showStatusCB show status message Block.see @link onStatusMessageCB @/link
@return  @link PaxEasyLinkRetCode @/link
*/
-(PaxEasyLinkRetCode) rkiInjectOfflineKey:(NSString *)filePath statusMessageBlock:(onStatusMessageCB)showStatusCB;

/*!
@abstract getRKICertList
  Inject offline key into mPOS device,   update the UI in onStatusMessageCB,UI must be updated in the main thread.
@param certListJson - rki certification list Josn Object
@param showStatusCB show status message Block.see @link onStatusMessageCB @/link
@return  @link PaxEasyLinkRetCode @/link
*/
-(PaxEasyLinkRetCode) getRKICertList:(NSString **)certListJson statusMessageBlock:(onStatusMessageCB)showStatusCB;

/*!
@abstract openPicc
  Power on and reset contactless module, and check whether initial status of the module is normal.
@return  @link PaxEasyLinkRetCode @/link
*/
-(PaxEasyLinkRetCode) piccOpen;

///*!
//@abstract readPicc
//  Read the current parameter settings, also can set the timeout of felic commands interaction
//@param piccParam output parameters - {@link PiccParam}
//@return  @linkPaxEasyLinkRetCode @/link
//*/
//-(PaxEasyLinkRetCode) piccReadParam:(PiccParam *)outPiccParam;
//
///*!
//@abstract writePicc
//  Write specific parameter settings to suit spcial application environment; also can set the timeout of felic commands interaction
//@param piccParam Input parameters - {@link PiccParam}
//@return  @linkPaxEasyLinkRetCode @/link
//*/
//-(PaxEasyLinkRetCode) piccWriteParam:(PiccParam *)inPiccParam;

/*!
@abstract detectPicc
 Detect PICC card according to appointed mode; when find the card, chooses and activates it.
@param mode - detect mode
    <p>@link EDetectMode @/link #EMV_AB @/link - Detect type A card and type B card once. It is an EMV detecting mode that usually be used.
    <p>@link EDetectMode @/link #ONLY_A @/link - Only detect type A card once; it is not permitted to find more than 1 type A card in inductive area
    <p>@link EDetectMode @/link #ONLY_B @/link - Only detect type B card once; it is not permitted to find more than 1 type B card in inductive area
    <p>@link EDetectMode @/link #ONLY_M @/link - Only detect type M1 card once; it is not permitted to find more than 1 type M1 card in inductive area
@param outPiccCardInfo Output parameters - {@link PiccCardInfo}
@return  @link PaxEasyLinkRetCode @/link
*/
-(PaxEasyLinkRetCode) piccDetect:(EDetectMode)mode piccCardInfo:(PiccCardInfo *)piccCardInfo;

/*!
@abstract removePicc
 Send stop command to card according to specific mode, or send halt command, or reset carrier, judge whether card is removed from inductive area in addition.
@param mode
    <p>@link EPiccRemoveMode @/link #HALT - quit after sending halt command to card; no card removed check during this process.
    <p>@link EPiccRemoveMode @/link  #REMOVE} - Send halt command to card, and execute card removed detection.
    <p>@link EPiccRemoveMode @/link #EMV - Comply with the remove card mode of EMV non-connected standard, Reset carrier, and execute card removed detection.
@param cid  Logical channel number returned from outer parameter PiccCardInfo.cid of piccDetect(EDetectMode, PiccCardInfo) API.
@return  @link PaxEasyLinkRetCode @/link
*/
-(PaxEasyLinkRetCode) piccRemove:(EPiccRemoveMode)mode cid:(Byte)cid;

/*!
@abstract closePicc
  Close PICC module, and make it in stop status.
@return  @link PaxEasyLinkRetCode @/link
*/
-(PaxEasyLinkRetCode) piccClose;

/*!
@abstract piccM1Authority
 Verify password A or B that should be submitted when reading/writing corresponding block of M1 card.
@param type     M1 Card key type
    <p>{@link EM1KeyType#TYPE_A} - Password A is submitted
    <p>{@link EM1KeyType#TYPE_B} - Password B is submitted
@param blockNo  - Specifies visiting block number.
@param pwd      - Password
@param serialNo - Points to first address of buffer storing card serial number; should point to serial number part of SerialInfo returned after calling                 {@link EasyLinkSdkManager#piccDetect(EDetectMode, PiccCardInfo)}, that is SerialInfo+1.
@return  @linkPaxEasyLinkRetCode @/link
*/
-(PaxEasyLinkRetCode) piccM1Authority:(EM1KeyType)type blockNo:(Byte)blockNo password:(NSData *)pwd serialNo:(NSData *)serialNo;

/*!
@abstract piccM1ReadBlock
 Read content of block specified by M1 card (totally 16 bytes).
@param blockNo       Used to appoint visiting block number, for 1K M1 card, its valid range is 0~63.
@param outBlockValue Points to the first address of buffer waiting for storing block content; the buffer should be allocated at least 16 bytes.
@return  @linkPaxEasyLinkRetCode @/link
*/
-(PaxEasyLinkRetCode) piccM1ReadBlock:(Byte)blockNo outBlockValue:(NSData **)outBlockValue;

///*!
//@abstract piccM1WriteBlock
// Write content of block specified by M1 card (totally 16 bytes).
//@param blockNo       Used to appoint visiting block number, for 1K M1 card, its valid range is 0~63.
//@param inBlockValue Points to the first address of buffer waiting for storing block content; the buffer should be allocated at least 16 bytes.
//@return  @linkPaxEasyLinkRetCode @/link
//*/
//-(PaxEasyLinkRetCode) piccM1WriteBlock:(Byte)blockNo outBlockValue:(NSMutableArray *)inBlockValue;

/*!
@abstract piccM1Operate
 Increase or decrease value of M1 card purse, and updates main purse or backup purse finally.
@param operateType   M1 Operate type
    <p>{@link EM1OperateType#INCREMENT} - Increase value
    <p>{@link EM1OperateType#DECREMENT} - Decrease value
    <p>{@link EM1OperateType#BACKUP} - Save as / backup operation
    1. If the block number of BlkNo and UpdateBlkNo are the same, use {@link EM1OperateType#INCREMENT} or {@link EM1OperateType#DECREMENT} to increase or decrease value of block number.
    2. If the block numbers are different, when use {@link EM1OperateType#INCREMENT} or {@link EM1OperateType#DECREMENT}, the value stored in BlkNo will have no changes,
    and the value of UpdateBlkNo block is equal to the increased or decreased value of BlkNo.
    3. If doing the {@link EM1OperateType#BACKUP} operation, the value is invalid, then stored the value of BlkNo to UpdateNo.
    <p>The block numbers which referred in this function must be Chunk, BlkNo and UpdateBlkNo must be in the same sector.
@param blockNo       Specifies visiting block number.
@param blockValue    Points to the first address of amount buffer waiting for increasing or decreasing value; amount is 4 bytes, and lower bytes ahead.
@param updateBlockNo Specifies number of block to which operation result will write. There are always two purses in M1 card: main purse and backup purse, in order to resume when abnormal error occurs in purse operation. Operation result of main purse is always written to backup purse.
@return  @linkPaxEasyLinkRetCode @/link
*/
-(PaxEasyLinkRetCode) piccM1Operate:(EM1OperateType)operateType blockNo:(Byte)blockNo blockValue:(NSData *)inBlockValue updateBlockNo:(Byte)updateBlockNo;

/*!
@abstract piccLight
 Control status of 4 LED lights of RF module
@param ledIndex  - 1 byte of Led index, 1 byte contain 8 bit, each bit:
    <p>BIT0: red light
    <p>BIT1: green light
    <p>BIT2: yellow light
    <p>BIT3: blue light
    <p>BIT4~BIT7: Reserved
@param ledStatus Led status
    <p>{@link ELedStatus#ON} - turn on the led of pointed index
    <p>{@link ELedStatus#OFF} - turn off the led of pointed index
@return  @linkPaxEasyLinkRetCode @/link
*/
-(PaxEasyLinkRetCode) piccLight:(Byte)ledindex ledStatus:(ELedStatus)ledStatus;

/*!
@abstract piccCmdExchange
 Processing APDU data interaction with card. Sending data of paucInData to the card directly, and receive the returned data.
@param piccApduSend Input parameter,{@link PiccApduSend} - Command data which are waiting to sent.
@param piccApduRecv Outer parameter, {@link PiccApduRecv} - Data of received card.
@return  @linkPaxEasyLinkRetCode @/link
*/
-(PaxEasyLinkRetCode) piccCmdExchange:(PiccApduSend *)piccApduSend piccApduRecv:(PiccApduRecv *)piccApduRecv;

/*!
@abstract msr open
 Open magnetic stripe reader
@return  @link PaxEasyLinkRetCode @/link
*/
-(PaxEasyLinkRetCode) msrOpen;

/*!
@abstract msr close
 Close magnetic stripe reader
@return  @link PaxEasyLinkRetCode @/link
*/
-(PaxEasyLinkRetCode) msrClose;

/*!
@abstract msr reset
 Soft reset magnetic stripe reader and clear the obtained magnetic card data
@return  @link PaxEasyLinkRetCode @/link
*/
-(PaxEasyLinkRetCode) msrReset;

/*!
@abstract msr swiped
 Detect a swiping action
@return  @link PaxEasyLinkRetCode @/link
*/
-(PaxEasyLinkRetCode) msrSwiped;

/*!
@abstract msr read
 Read MSR data.
@param track1 - track1 data, refer to @link TrackData @/link
    <p> &nbsp;; Track data status:@link TrackData @/link #status, 0 means succeeded, other value means failed
@param track2 - track2 data, refer to @link TrackData @/link
    <p> &nbsp;; Track data status:@link TrackData @/link #status , 0 means succeeded, other value means failed
@param track3 - track3 data, refer to @link TrackData @/link
    <p> &nbsp;; Track data status:@link TrackData @/link #status, 0 means succeeded, other value means failed
@return  @link PaxEasyLinkRetCode @/link
*/
-(PaxEasyLinkRetCode) msrRead:(TrackData *)track1 track2:(TrackData *)track2 track3:(TrackData *)track3;

/*!
@abstract icc open
 Open IC card reader
@param slot  - IC card channel number: 0 - 7, depend on slave pos.
    <p> &nbsp; prolin slave device:
    <p>&nbsp;  &nbsp; slot 0: ICC_USER_SLOT
    <p>&nbsp; &nbsp; slot 2: ICC_SAM1_SLOT
    <p>&nbsp; &nbsp; slot 3: ICC_SAM2_SLOT
    <p>&nbsp; &nbsp; slot 4: ICC_SAM3_SLOT
    <p>&nbsp; &nbsp; slot 5: ICC_SAM4_SLOT
@return  @link PaxEasyLinkRetCode @/link
*/
-(PaxEasyLinkRetCode) iccOpen:(Byte)slot;

/*!
@abstract icc close
 Close IC card reader
@param slot  - IC card channel number: 0 - 7, depend on slave pos.
    <p> &nbsp; prolin slave device:
    <p>&nbsp;  &nbsp; slot 0: ICC_USER_SLOT
    <p>&nbsp; &nbsp; slot 2: ICC_SAM1_SLOT
    <p>&nbsp; &nbsp; slot 3: ICC_SAM2_SLOT
    <p>&nbsp; &nbsp; slot 4: ICC_SAM3_SLOT
    <p>&nbsp; &nbsp; slot 5: ICC_SAM4_SLOT
@return  @link PaxEasyLinkRetCode @/link
*/
-(PaxEasyLinkRetCode) iccClose:(Byte)slot;

/*!
@abstract icc detect
 Test Whether there is a card in spceified slot
@param slot  - IC card channel number: 0 - 7, depend on slave pos.
    <p> &nbsp; prolin slave device:
    <p>&nbsp;  &nbsp; slot 0: ICC_USER_SLOT
    <p>&nbsp; &nbsp; slot 2: ICC_SAM1_SLOT
    <p>&nbsp; &nbsp; slot 3: ICC_SAM2_SLOT
    <p>&nbsp; &nbsp; slot 4: ICC_SAM3_SLOT
    <p>&nbsp; &nbsp; slot 5: ICC_SAM4_SLOT
@return  @link PaxEasyLinkRetCode @/link
*/
-(PaxEasyLinkRetCode) iccDetect:(Byte)slot;


//-(PaxEasyLinkRetCode) iccExchange;

/*!
@abstract icc init
 Initialize IC card device
@param slot  - IC card channel number: 0 - 7, depend on slave pos.
    <p> &nbsp; prolin slave device:
    <p>&nbsp;  &nbsp; slot 0: ICC_USER_SLOT
    <p>&nbsp; &nbsp; slot 2: ICC_SAM1_SLOT
    <p>&nbsp; &nbsp; slot 3: ICC_SAM2_SLOT
    <p>&nbsp; &nbsp; slot 4: ICC_SAM3_SLOT
    <p>&nbsp; &nbsp; slot 5: ICC_SAM4_SLOT
@param cardVoltage - Card voltage options:
    <p>&nbsp;  &nbsp; 0: 5V
    <p>&nbsp;  &nbsp; 1: 1.8V
    <p>&nbsp;  &nbsp; 2: 3V
@param supportPPS - Support PPS protocol
    <p>&nbsp;  &nbsp; 0: Unsupported
    <p>&nbsp;  &nbsp; 1: Supported
@param rate - Rate used in power-on reset
    <p>&nbsp;  &nbsp; 0: Standard rate 9600
    <p>&nbsp;  &nbsp; 1: Four times rate 38400
    <p>&nbsp; The rate mentioned here is a reference value in typical frequency (3.57MHz).
            The communication rate between IC card and card reader is closely related to working clock frequency provided by a specific machine.
@param standard - Supported standards:
    <p>&nbsp;  &nbsp; 0: EMV;
    <p>&nbsp;  &nbsp; 1: ISO7816, Most SAM cards only support ISO7816
    <p>&nbsp; If EMV mode is specified, the power on rate will be marked as invalid and it will use the standard rate by default.
@param atr - output param, the buffer should be allocated at least 34 bytes.
    <p>&nbsp;  &nbsp; The card will return response data of 34 bytes at most.the first byte is the length of atr
@return  @link PaxEasyLinkRetCode @/link
*/
-(PaxEasyLinkRetCode) iccInit:(Byte)slot cardVoltage:(Byte)cardVoltage supportPPS:(Byte)supportPPS rate:(Byte)rate standard:(Byte)standard atr:(NSData **)atr;

/*!
@abstract icc init
 Initialize IC card device
@param slot  - IC card channel number: 0 - 7, depend on slave pos.
    <p> &nbsp; prolin slave device:
    <p>&nbsp;  &nbsp; slot 0: ICC_USER_SLOT
    <p>&nbsp; &nbsp; slot 2: ICC_SAM1_SLOT
    <p>&nbsp; &nbsp; slot 3: ICC_SAM2_SLOT
    <p>&nbsp; &nbsp; slot 4: ICC_SAM3_SLOT
    <p>&nbsp; &nbsp; slot 5: ICC_SAM4_SLOT
 @param ctrlFlag - Whether to send "GET RESPONSE" command automatically under T=0 protocol
    <p>&nbsp; &nbsp; 0: no
    <p>&nbsp; &nbsp; 1: yes
 @param apduReq - refer to {@link ApduReq}
    <p>&nbsp; &nbsp; cmd: 4bytes, CLA,INS,P1,P2
    <p>&nbsp; &nbsp; lc: the length of data that send to icc card
    <p>&nbsp; &nbsp; data: the data send to icc card
    <p>&nbsp; &nbsp; le: expect length of icc response
 @param apduResp - refer to {@link ApduResp}
    <p>&nbsp; &nbsp; len: the data length return from icc card
    <p>&nbsp; &nbsp; data: the data response by card
    <p>&nbsp; &nbsp; swa: status word 1 of ICC
    <p>&nbsp; &nbsp; swb: status word 2 of ICC
 @return  @link PaxEasyLinkRetCode @/link
 */
-(PaxEasyLinkRetCode) iccCmdExchange:(Byte)slot ctrlFlag:(Byte)ctrlFlag apduReq:(ApduReq *)apduReq apduResp:(ApduResp *)apduResp;

@end



#pragma mark -- transaction========================================

/*!
 @protocol PaxSmartlandingDelegate
 */
@protocol PaxSmartlandingDelegate <NSObject>
/*!
@abstract Sync and process task
 Sync task and process task from given server
@param host  - server url
@param port  - server port
@param listener  - Implement listener ISyncAndProcessListener. @link ISyncAndProcessListener @/link
@return  @link PaxEasyLinkRetCode @/link
*/
-(PaxEasyLinkRetCode) syncAndProcessTask:(NSString*)host port:(int) port listener:(id<ISyncAndProcessListener>)listener;

@end


