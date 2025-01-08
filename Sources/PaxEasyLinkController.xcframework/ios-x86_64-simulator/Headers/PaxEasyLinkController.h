//
//  PaxEasyLinkController.h
//  PaxEasyLinkController
//
//  Created by pax on 16/8/19.
//  Copyright © 2016年 jobten. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "PaxEasyLinkConst.h"
#import "PaxEasyLinkProtocol.h"
#import "PaxReportResponse.h"
#import "BaseRunCmdModel.h"
#import "BaseReportModel.h"
#import "ReportData.h"
#import "EmvAidParam.h"
#import "EmvIcsParam.h"
#import "WriteKeyModel.h"
#import "WriteTikKeyModel.h"
#import "SetDataModel.h"
#import "SetEmvAidParamModel.h"
#import "SetEmvIcsParamModel.h"
#import "KeyParam.h"
#import "TikKeyParam.h"
#import "AppSelectRequest.h"

/*!
 @abstract PaxEasyReportDelegate
 */
@protocol PaxEasyReportDelegate <NSObject>//app遵守的协议
@optional



/*!@abstract  onReportSearchModeWithPrompts
 @param prompts  the prompts of current search card
 @param model The status “curSearchMode” is the current mode for searching card, valid value:
 1-MSR: swipe card 2-ICC: insert card 3-MSR: Mag swipe and ICC insert 4-PICC: tap card
 5 – MSR_PICC: Mag swipe and PICC tap; 6-ICC: ICC insert and PICC tap 7-MSR: Mag swipe, ICC insert and PICC tap 16-Fallback: fallback
 startTransaction completeTransaction to swipe card
 */
- (void)onReportSearchModeWithPrompts:(NSString *)prompts searchMode:(NSInteger)model;

/*!
 onReadCardWithPrompts
 @param prompts the prompts of the processing read card
 @param type  The “detectType” indicates the current card detecting type, valid value:
 0-contact 1-contactless 2-Magnetic
 @param readCardStatus The “status” indicates the status of card processing, valid value:
 0-Not Ready
 1-Idle
 2-Ready to Read
 3-Processing
 4-Card ReadSuccessfully
 5-Processing startTransaction completeTransa ctionError(Contactless error)
 6-Processing Error(Conditions for use of contactless not satisfied)
 7-Processing Error(Contactless collision detected)
 8-Processing Error(Card not removed from reader)
 9-Detected Card Successfully
 10-Card removed from reader
 */
- (void)onReadCardWithPrompts:(NSString*)prompts detectType:(NSInteger)type readCardStatus:(NSInteger)readCardStatus;

/*!
 onEnterPinWithPrompts

 @param prompts the processing prompts of enter
 @param pinLen The “pinLen” indicate current PIN length that user input.
 @param enterPinEvent  The “pinStatus” indicate the status of ENTER PIN, valid value:
 “INIT” “INPUT” “CANCEL” “CLEAR” “ENTER” “RETRY” “LAST”
 Note: “ENTER”
 means user press ENTER key to bypass the PIN entry;
 */
- (void)onEnterPinWithPrompts:(NSString*)prompts pinLen:(NSInteger)pinLen enterPinEvent:(NSString *)enterPinEvent;

/*!
 
 @param prompts The “prompts” is the prompt message to display on the screen.
 @param timeout  The “timeout” is the timeout for application selection, unit: second.
 @param appList The “appList” is the candidate application list for EMV application select.

 @return 1)The “selectApp” indicate the EMV application selection. 2) The “status” indicate the processing result of application selection, valid value:
 “NO_APP” “SUCCESS”
 1 – User cancel 2 – Timeout Note: If the POS
 terminal doesn’t have screen, then the reported appList shall be the EMV candidate application list;
 if the POS terminal has screen, then the reported appList shall be null;
 if application is null, then the status shall be respond with -1;
 3) The “appLabel” indicate the selected application. @link PaxReportResponse @/link.
 */
- (PaxReportResponse *)onSelectAppWithPrompts:(NSString *)prompts timeout:(int)timeout list:(NSArray *)appList;

/*!
 
 @param prompts The “prompts” is the prompt message to display on the screen.
 @param timeout  The “timeout” is the timeout for application selection, unit: second.
 @param appList The “appList” is the candidate application list for EMV application select.
 @param aidList The “appList” is the candidate aid list for EMV aid select.

 @return 1)The “selectApp” indicate the EMV application selection. 2) The “status” indicate the processing result of application selection, valid value:
 “NO_APP” “SUCCESS”
 1 – User cancel 2 – Timeout Note: If the POS
 terminal doesn’t have screen, then the reported appList shall be the EMV candidate application list;
 if the POS terminal has screen, then the reported appList shall be null;
 if application is null, then the status shall be respond with -1;
 3) The “appLabel” indicate the selected application. @link PaxReportResponse @/link.
 */
- (PaxReportResponse *)onSelectAppWithPrompts:(NSString *)prompts timeout:(int)timeout list:(NSArray *)appList list:(NSArray *)aidList;

/*!
 * Set parameter from smart device while startTransaction<br>
 * For example, if the payment app in smart device need to support multi-acquirer, then the payment app in smart device need to set the TAG 0219, 021A first. The EasyLink app will invoke getData to get the values of TAGs as TAG 0219, 021A indicated. Then pack the TLVs data and report to the smart device. The smart device need to unpack the TLV data, and can get to know the corresponding KEY information (PIN key type, PIN key index, etc) according to the unpacked TLV data, then set the TAG 0202, 0203 to the PinPad (EasyLink App)<br>
 * NOTE:<p>
 * 1.Except the multi-acquirer scenario, the smart device can also set the parameters to support different usage scenario.<br>
 * 2.If TAG 0205 and TAG 0206 are set, then the value of the sensitive data shall be encrypted.<br>
 *
 * @param prompts    "Please Set Param"
 * @param configTLVs reported data of config tag(such as 0219) which were set before startTransaction<br>
 *                   <p>“configTlv” is the TLV String converted from TLV(bcd) that the EasyLink App get these TLVs (bcd) data according to the TAGs as TAG 0219 indicated;<br>
 * @param emvTLVs    reported data of emv tag(such as 021A) which were set before startTransaction
 *                   <p>“emvTlv” is the TLV String converted from TLV(bcd) that the EasyLink App get the these TLVs (bcd) data according to the TAGs as TAG 021A indicated;<br>
 * @param timeout    timeout(s)
 * @return set param such as pin key index and type @link TlvItem @/link
 */
- (NSArray<TlvItem *> *)onSetParamToPinPadWithPrompts:(NSString *)prompts configTLVs:(NSArray<TlvItem *> *)configTLVs emvTLVs:(NSArray<TlvItem *> *)emvTLVs timeout:(NSInteger)timeout;

/********************************Date: 2019-12-26     Author: Sandy Yang    Action: Add*****************************/

/*!
  onRunCmdPrompts<br>
    Set commands and parameters to terminal to change the terminal parameters which will be loaded during different status of transaction process.
  @param ReprotList  the reported data from terminal, contains the status of transaction process, terminal default parameters                                             and TlvDataObject, the default parameters are usually EmvAidParam or ICSParam, and TlvDataObject                                             is usually contain the card information and others parameters which was configured by TAG:0219 and                                               TAG:021A @link BaseReportModel @/link<br>
                    <p>Currently, there are several status will be informed to client side, of course, whether the status is reported is configurable. it can be configured by the callBackCfg.report file<br>
                    <p> "setEMVAidParam"  -  terminal is at the status of setEMVAidParam, client can change the EMVAidParam or execute other cmd to set parameters to terminal, such as setDataCmd/writeKeyCmd/writeTIKCmd;<br>
                    <p> "setICSParam"  -  terminal is at the status of setICSParam, client can change the ICSParam or execute other cmd to set parameters to terminal, such as setDataCmd/writeKeyCmd/writeTIKCmd;<br>
                    <p> "readCardOK"  -  terminal has finished read card, client can send some Cmd, such as setDataCmd, writeKeyCmd, writeTikCmd to change the terminal parameters. such as achieve the scenes of different acquirer with different encryption key;<br>
  @param timeout    timeout(s)
  @return the ArrayList of object which contain cmd and parameter @link BaseRunCmdModel @/link
          <p> when status is "setEMVAidParam", client can change the default EmvAidParam, and by using the SetEmvAidParamModel to make the changes take effect.or send other cmd such as setDataCmd/writeKeyCmd/writeTIKCmd;<br>
          <p> when status is "setICSParam", client can change the default ICSParam, and by using the SetICSParamModel to make the changes take effect.or send other cmd such as setDataCmd/writeKeyCmd/writeTIKCmd;<br>
          <p> when status is "readCardOK", client can send some Cmd, such as
                        using the SetDataModel to execute setData operation.
                        using the WriteKeyModel to execute writeKey operation.
                        using the WriteTikKeyModel to execute writeTIK operation

 */
- (NSArray<BaseRunCmdModel *>*)onRunCmdPrompts:(NSArray<BaseReportModel *>*)ReportList timeout:(NSInteger)timeout;


/***************************************************end by Sandy Yang*******************************************************/
@end

@interface PaxEasyLinkController : NSObject<PaxBluetoothDelegate, PaxTransDelegate, PaxSmartlandingDelegate>

@property(nonatomic,weak) id<PaxEasyReportDelegate>delegate;
#pragma mark 单例模式

/*!
 @abstract get PaxEasyLinkController instance
 @return    PaxEasyLinkController instance
 */
+ (PaxEasyLinkController *)getInstance;

- (NSString *)getConnectedDevice;


@end

