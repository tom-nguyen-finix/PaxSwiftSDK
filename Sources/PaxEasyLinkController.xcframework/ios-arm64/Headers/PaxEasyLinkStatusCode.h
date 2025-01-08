//
//  PaxEasyLinkStatusCode.h
//  PaxEasyLinkController
//
//  Created by pax on 16/8/22.
//  Copyright © 2016年 jobten. All rights reserved.
//

#import <Foundation/Foundation.h>
/*!
 @abstract Return codes of EasyLink
 @discussion Please use @link  statusCode2String:@/link to transfer the return code into human readable string
 @constant EL_RET_OK = 0                        success
 
 @constant EL_COMM_RET_BASE                     BASE COMM error start value
 @constant EL_COMM_RET_CONNECTED                COMM connected
 @constant EL_COMM_RET_DISCONNECT_FAIL          COMM disconnect failed
 @constant EL_COMM_RET_PARAM_FILE_NOT_EXIS      param file not exist
 @constant EL_COMM_RET_OPEN_COMPATIBLE_MODE_FAIL open compatible mode fail
 
 @constant EL_UI_RET_BASE                       BASE UI error start value
 @constant EL_UI_RET_INVALID_WIDGETNAME         invalid widget name
 @constant EL_UI_RET_TIME_OUT                   time out
 @constant EL_UI_RET_INVALID_PAGE               invalid page
 @constant EL_UI_RET_PARSE_UI_FAILED            parse ui failed
 @constant EL_UI_RET_VALUESIZEERROR             widget value size
 @constant EL_UI_RET_INPUT_TYPE_ERROR           input type not find
 @constant EL_UI_RET_INVALID_WIDGETVALUE        invalid widget value
 @constant EL_UI_RET_USER_CANCEL                cancel exit
 @constant EL_UI_RET_MENUITEMNUM_ERROR          menuitem number = 0
 @constant EL_UI_RET_UNKOWN_ERROR               unknown error
 @constant EL_UI_RET_GETSIGNDATA_FALI           get signature data failed
 
 
 @constant EL_SECURITY_RET_BASE                 BASE security error start value
 @constant EL_SECURITY_RET_NO_KEY               key doesnot
 @constant EL_SECURITY_RET_PARAM_INVALID        Parameter
 @constant EL_SECURITY_RET_ENCRYPT_DATA_ERR     Encrypt data error
 @constant EL_SECURITY_RET_GET_PIN_BLOCK_ERR    Get pin block error
 @constant EL_SECURITY_RET_NO_PIN_INPUT         Not input pin
 @constant EL_SECURITY_RET_INPUT_CANCEL         user cancel
 @constant EL_SECURITY_RET_INPUT_TIMEOUT        input timeout
 @constant EL_SECURITY_RET_KEY_TYPE_ERR         key type error
 
 *****************abandoned return code*************************
 @constant EL_TRANS_RET_BASE					BASE transaction error start value
 @constant EL_TRANS_RET_ICC_RESET_ERR			ICC data reset error
 @constant EL_TRANS_RET_ICC_CMD_ERR				ICC command error
 @constant EL_TRANS_RET_ICC_BLOCK				ICC block
 @constant EL_TRANS_RET_EMV_RSP_ERR				EMV respond error
 @constant EL_TRANS_RET_EMV_APP_BLOCK			EMV app block
 @constant EL_TRANS_RET_EMV_NO_APP				EMV no app
 @constant EL_TRANS_RET_EMV_USER_CANCEL			EMV user cancel
 @constant EL_TRANS_RET_EMV_TIME_OUT			EMV timeout
 @constant EL_TRANS_RET_EMV_DATA_ERR			EMV data error
 @constant EL_TRANS_RET_EMV_NOT_ACCEPT			EMV transaction not accept
 @constant EL_TRANS_RET_EMV_DENIAL				EMV transaction denial
 @constant EL_TRANS_RET_EMV_KEY_EXP				EMV key expired
 @constant EL_TRANS_RET_EMV_NO_PINPAD			EMV no pinpad or pinpad not work
 @constant EL_TRANS_RET_EMV_NO_PASSWORD			EMV no pin
 @constant EL_TRANS_RET_EMV_SUM_ERR				EMV checksum error
 @constant EL_TRANS_RET_EMV_NOT_FOUND			EMV data not found
 @constant EL_TRANS_RET_EMV_NO_DATA				EMV no specified data
 @constant EL_TRANS_RET_EMV_OVERFLOW			EMV data overflow
 @constant EL_TRANS_RET_NO_TRANS_LOG			EMV translog entry
 @constant EL_TRANS_RET_RECORD_NOTEXIST			EMV no record
 @constant EL_TRANS_RET_LOGITEM_NOTEXIST		EMV no log item
 @constant EL_TRANS_RET_ICC_RSP_6985			EMV icc responded code 6985
 @constant EL_TRANS_RET_CLSS_USE_CONTACT		EMV use contact interface
 @constant EL_TRANS_RET_EMV_FILE_ERR			EMV file error
 @constant EL_TRANS_RET_CLSS_TERMINATE			EMV clss transaction terminated
 @constant EL_TRANS_RET_CLSS_FAILED				EMV clss transaction failed
 @constant EL_TRANS_RET_CLSS_DECLINE			EMV clss transaction declined
 @constant EL_TRANS_RET_CLSS_TRY_ANOTHER_CARD	Try another card (DPAS Only)
 @constant EL_TRANS_RET_PARAM_ERR				EMV error param
 @constant EL_TRANS_RET_CLSS_WAVE2_OVERSEA		International transaction(for VISA AP PayWave Level2 IC card use)
 @constant EL_TRANS_RET_CLSS_WAVE2_TERMINATED	Wave2 DDA response TLV format error
 @constant EL_TRANS_RET_CLSS_WAVE2_US_CARD		US card(for VISA AP PayWave L2 IC card use)
 @constant EL_TRANS_RET_CLSS_WAVE3_INS_CARD		Need to use IC card for the transaction(for VISA PayWave IC card use)
 @constant EL_TRANS_RET_CLSS_RESELECT_APP		Select the next AID in candidate list
 @constant EL_TRANS_RET_CLSS_CARD_EXPIRED		IC card is expired
 @constant EL_TRANS_RET_EMV_NO_APP_PPSE_ERR		No application is supported(Select PPSE is error)
 @constant EL_TRANS_RET_CLSS_USE_VSDC			Switch to contactless PBOC
 @constant EL_TRANS_RET_CLSS_CVMDECLINE			CVM result in decline for AE
 @constant EL_TRANS_RET_CLSS_REFER_CONSUMER_DEVICE	  Status Code returned by IC card is 6986, please see phone
 @constant EL_TRANS_RET_CLSS_LAST_CMD_ERR		      The last read record command is error(qPBOC Only)
 @constant EL_TRANS_RET_CLSS_API_ORDER_ERR	          Try another card (DPAS Only)
 @constant EL_EMV_RET_TRANS_FAIL					  transaction failed
 @constant EL_EMV_RET_TRANS_DECLINED				  transaction declined
 *****************abandoned return code*************************
 
 @constant EL_TRANS_RET_BASE                      base transaction error start value
 @constant EL_TRANS_RET_READ_CARD_FAIL            read card data fail
 @constant EL_TRANS_RET_CARD_BLOCKED              card is blocked
 @constant EL_TRANS_RET_USER_CANCELED             user cancel transaction
 @constant EL_TRANS_RET_TIME_OUT                  timeout
 @constant EL_TRANS_RET_CARD_DATA_ERROR           card data error
 @constant EL_TRANS_RET_TRANS_NOT_ACCEPT          trancation isn't accepted
 @constant EL_TRANS_RET_TRANS_FAILED              trancation is failed
 @constant EL_TRANS_RET_TRASN_DECLINED            trancation is declined
 @constant EL_TRANS_RET_NOT_SUPPORT               trancation is not supported
 @constant EL_TRANS_RET_EXPIRED                   card expired
 @constant EL_TRANS_RET_CARD_LUHN                   card  luhn error
 
 @constant EL_FILEDOWNLOAD_ERR_BASE					  BASE filedownload error start value
 @constant EL_FILEDOWNLOAD_ERR_INVALID_PARAM		      invalid parameter
 @constant EL_FILEDOWNLOAD_ERR_DOWNLOAD_FILE_FAIL	  firmware file save failed
 @consatnt EL_FILEDOWNLOAD_RET_FIRMWARE_FAIL           download firmware failed
 @constant EL_FILEDOWNLOAD_ERR_FILE_OVERSIZE			  file over size
 ***********abandoned return code***************
 @constant EL_FILEDOWNLOAD_ERR_NOT_ALLOWED				  file not allowed
 ***********abandoned return code***************
 @constant EL_FILEDOWNLOAD_ERR_PARSE_ERR				  parse file failed
 
 
 @constant EL_PARAM_RET_BASE                          Base return code for parameter management module
 @constant EL_PARAM_RET_ERR_DATA                      Input data error.
 @constant EL_PARAM_RET_INVALID_PARAM                 Invalid parameter.
 @constant EL_PARAM_RET_PARTIAL_FAILED                Partial operation failed.
 @constant EL_PARAM_RET_ALL_FAILED                    All operation failed.
 @constant EL_PARAM_RET_BUFFER_TOO_SMALL T            the output buffer size is not enough.
 @constant EL_PARAM_RET_API_ORDER_ERR                 APIs are invoked in wrong order
 @constant EL_PARAM_RET_ENCRYPT_SENSITIVE_DATA_FAILED encrypted sensitive data failed
 
 @constant EL_SDK_RET_BASE                            Base return code for SDK
 @constant EL_SDK_RET_PARAM_INVALID                   invalid param
 @constant EL_SDK_RET_COMM_CONNECT_ERR                comm connect err
 @constant EL_SDK_RET_COMM_DISCONNECT_ERR             comm disconnect err
 @constant EL_SDK_RET_COMM_DISCONNECTED               comm disconnected
 @constant EL_SDK_RET_COMM_SEND_ERR                   comm sent err
 @constant EL_SDK_RET_COMM_RECV_ERR                   comm recv err
 @constant EL_SDK_PROTO_RET_BASE                      Base return code for proto err
 @constant EL_SDK_RET_PROTO_GENERAL_ERR               general error
 @constant EL_SDK_RET_PROTO_ARG_ERR                   argument error
 @constant EL_SDK_RET_PROTO_PACKET_TOO_LONG           packet too long
 @constant EL_SDK_RET_PROTO_NO_ENOUGH_DATA            receive data not enough
 @constant EL_SDK_RET_PROTO_DATA_FORMAT               data format error
 @constant EL_SDK_RET_PROTO_TIMEOUT timeout           timeout
 */

typedef enum {
    
    EL_RET_OK                               = 0,
    EL_COMM_ERROR                           = -1,
    EL_CMD_NOT_SUPPORT                      = 0x9999,
    EL_GENERAL                              = -1,
    EL_ARG                                  = -2,
    EL_PROTO_CONN                           = -100,
    EL_PROTO_SEND                           = -101,
    EL_PROTO_RECV                           = -102,
    EL_PROTO_PACKAGE_TOO_LONG               = -103,
    EL_PROTO_NO_ENOUGH_DATA                 = -104,
    EL_PROTO_CHECKSUM                       = -105,
    EL_PROTO_DATA_FORMAT                    = -106,
    EL_PROTO_NAKED                          = -107,
    EL_PROTO_SYNC                           = -108,
    EL_PROTO_NOT_CONFIRM                    = -109,
    EL_PROTO_CANCEL                         = -110,
    
    EL_COMM_RET_BASE                       = 1000,
    EL_COMM_RET_CONNECTED                  = (EL_COMM_RET_BASE +1),
    EL_COMM_RET_DISCONNECT_FAIL            = (EL_COMM_RET_BASE +2),
    EL_COMM_RET_NOTCONNECTED               = (EL_COMM_RET_BASE +3),
    EL_COMM_RET_PARAM_FILE_NOT_EXIST       = (EL_COMM_RET_BASE + 4),
    EL_COMM_RET_BUSY                       = (EL_COMM_RET_BASE + 5),  // Use for IPC communicate with server
    EL_COMM_INPUT_DATA_OVERFLOW            = (EL_COMM_RET_BASE + 6),// the size of input data from client side larger than the terminal buffer.
    EL_COMM_READER_TAMPER                  = (EL_COMM_RET_BASE + 7),// reader tamper
    
    
    EL_UI_RET_BASE						    =(2000),
    EL_UI_RET_INVALID_WIDGETNAME		    =(EL_UI_RET_BASE + 1),
    EL_UI_RET_TIME_OUT					    =(EL_UI_RET_BASE + 2),
    EL_UI_RET_INVALID_PAGE			        =(EL_UI_RET_BASE +3),
    EL_UI_RET_PARSE_UI_FAILED			    =(EL_UI_RET_BASE +4),
    EL_UI_RET_VALUESIZEERROR			    =(EL_UI_RET_BASE +5),
    EL_UI_RET_INPUT_TYPE_ERROR 		        =(EL_UI_RET_BASE + 6),
    EL_UI_RET_INVALID_WIDGETVALUE 	        =(EL_UI_RET_BASE + 7),
    EL_UI_RET_USER_CANCEL				    =(EL_UI_RET_BASE + 8),
    EL_UI_RET_MENUITEMNUM_ERROR		        =(EL_UI_RET_BASE + 9),
    EL_UI_RET_UNKOWN_ERROR                  =(EL_UI_RET_BASE + 10),
    EL_UI_RET_GETSIGNDATA_FAIL              =(EL_UI_RET_BASE + 11),
    EL_UI_RET_CARD_NUMBER_NOT_MATCH         =(EL_UI_RET_BASE + 12),
    
    EL_SECURITY_RET_BASE					=3000,
    EL_SECURITY_RET_NO_KEY					=(EL_SECURITY_RET_BASE + 1),
    EL_SECURITY_RET_PARAM_INVALID			=(EL_SECURITY_RET_BASE + 2),
    EL_SECURITY_RET_ENCRYPT_DATA_ERR		=(EL_SECURITY_RET_BASE + 3),
    EL_SECURITY_RET_GET_PIN_BLOCK_ERR		=(EL_SECURITY_RET_BASE + 4),
    EL_SECURITY_RET_NO_PIN_INPUT			=(EL_SECURITY_RET_BASE + 5),
    EL_SECURITY_RET_INPUT_CANCEL			=(EL_SECURITY_RET_BASE + 6),
    EL_SECURITY_RET_INPUT_TIMEOUT			=(EL_SECURITY_RET_BASE + 7),
    EL_SECURITY_RET_KEY_TYPE_ERR            =(EL_SECURITY_RET_BASE + 8),
    EL_SECURITY_ERR_PED_WAIT_INTERVAL       =(EL_SECURITY_RET_BASE + 9),
    
    EL_WRITE_KEY_RET_BASE                   = 3110,
    EL_WRITE_KEY_NO_KEY                     = (EL_WRITE_KEY_RET_BASE+1),
    EL_WRITE_KEY_KEYIDX_ERR                 = (EL_WRITE_KEY_RET_BASE+2),
    EL_WRITE_KEY_DERIVE_ERR                 = (EL_WRITE_KEY_RET_BASE+3),
    EL_WRITE_KEY_CHECK_KEY_FAIL             = (EL_WRITE_KEY_RET_BASE+4),
    EL_WRITE_KEY_NO_PIN_INPUT               = (EL_WRITE_KEY_RET_BASE+5),
    EL_WRITE_KEY_INPUT_CANCEL               = (EL_WRITE_KEY_RET_BASE+6),
    EL_WRITE_KEY_WAIT_INTERVAL              = (EL_WRITE_KEY_RET_BASE+7),
    EL_WRITE_KEY_CHECK_MODE_ERR             = (EL_WRITE_KEY_RET_BASE+8),
    EL_WRITE_KEY_NO_RIGHT_USE               = (EL_WRITE_KEY_RET_BASE+9),
    EL_WRITE_KEY_KEY_TYPE_ERR               = (EL_WRITE_KEY_RET_BASE+10),
    EL_WRITE_KEY_EXPLEN_ERR                 = (EL_WRITE_KEY_RET_BASE+11),
    EL_WRITE_KEY_DSTKEY_IDX_ERR             = (EL_WRITE_KEY_RET_BASE+12),
    EL_WRITE_KEY_SRCKEY_IDX_ERR             = (EL_WRITE_KEY_RET_BASE+13),
    EL_WRITE_KEY_KEY_LEN_ERR                = (EL_WRITE_KEY_RET_BASE+14),
    EL_WRITE_KEY_INPUT_TIMEOUT              = (EL_WRITE_KEY_RET_BASE+15),
    EL_WRITE_KEY_NO_ICC                     = (EL_WRITE_KEY_RET_BASE+16),
    EL_WRITE_KEY_CC_NO_INIT                 = (EL_WRITE_KEY_RET_BASE+17),
    EL_WRITE_KEY_GROUP_IDX_ERR              = (EL_WRITE_KEY_RET_BASE+18),
    EL_WRITE_KEY_PARAM_PTR_NULL             = (EL_WRITE_KEY_RET_BASE+19),
    EL_WRITE_KEY_LOCKED                     = (EL_WRITE_KEY_RET_BASE+20),
    EL_WRITE_KEY_ERROR                      = (EL_WRITE_KEY_RET_BASE+21),
    EL_WRITE_KEY_NOMORE_BUF                 = (EL_WRITE_KEY_RET_BASE+22),
    EL_WRITE_KEY_NEED_ADMIN                 = (EL_WRITE_KEY_RET_BASE+23),
    EL_WRITE_KEY_DUKPT_OVERFLOW             = (EL_WRITE_KEY_RET_BASE+24),
    EL_WRITE_KEY_KCV_CHECK_FAIL             = (EL_WRITE_KEY_RET_BASE+25),
    EL_WRITE_KEY_SRCKEY_TYPE_ERR            = (EL_WRITE_KEY_RET_BASE+26),
    EL_WRITE_KEY_UNSPT_CMD                  = (EL_WRITE_KEY_RET_BASE+27),
    EL_WRITE_KEY_COMM_ERR                   = (EL_WRITE_KEY_RET_BASE+28),
    EL_WRITE_KEY_NO_UAPUK                   = (EL_WRITE_KEY_RET_BASE+29),
    EL_WRITE_KEY_ADMIN_ERR                  = (EL_WRITE_KEY_RET_BASE+30),
    EL_WRITE_KEY_DOWNLOAD_INACTIVE          = (EL_WRITE_KEY_RET_BASE+31),
    EL_WRITE_KEY_KCV_ODD_CHECK_FAIL         = (EL_WRITE_KEY_RET_BASE+32),
    EL_WRITE_KEY_PED_DATA_RW_FAIL           = (EL_WRITE_KEY_RET_BASE+33),
    EL_WRITE_KEY_ICC_CMD_ERR                = (EL_WRITE_KEY_RET_BASE+34),
    EL_WRITE_KEY_INPUT_CLEAR                = (EL_WRITE_KEY_RET_BASE+39),
    EL_WRITE_KEY_NO_FREE_FLASH              = (EL_WRITE_KEY_RET_BASE+43),
    EL_WRITE_KEY_DUKPT_NEED_INC_KSN         = (EL_WRITE_KEY_RET_BASE+44),
    EL_WRITE_KEY_KCV_MODE_ERR               = (EL_WRITE_KEY_RET_BASE+45),
    EL_WRITE_KEY_DUKPT_NO_KCV               = (EL_WRITE_KEY_RET_BASE+46),
    EL_WRITE_KEY_PIN_BYPASS_BYFUNKEY        = (EL_WRITE_KEY_RET_BASE+47),
    EL_WRITE_KEY_MAC_ERR                    = (EL_WRITE_KEY_RET_BASE+48),
    EL_WRITE_KEY_CRC_ERR                    = (EL_WRITE_KEY_RET_BASE+49),
    EL_WRITE_KEY_PARAM_INVALID              = (EL_WRITE_KEY_RET_BASE+50),
    
    
    EL_TRANS_RET_BASE						= 4000,
    EL_TRANS_RET_READ_CARD_FAIL             =(EL_TRANS_RET_BASE + 2),
    EL_TRANS_RET_CARD_BLOCKED               =(EL_TRANS_RET_BASE + 3),
    EL_TRANS_RET_USER_CANCELED              =(EL_TRANS_RET_BASE + 7),
    EL_TRANS_RET_TIME_OUT                   =(EL_TRANS_RET_BASE + 8),
    EL_TRANS_RET_CARD_DATA_ERROR            =(EL_TRANS_RET_BASE + 9),
    EL_TRANS_RET_TRANS_NOT_ACCEPT           =(EL_TRANS_RET_BASE + 10),
    EL_TRANS_RET_TRANS_FAILED               =(EL_TRANS_RET_BASE + 43),
    EL_TRANS_RET_TRASN_DECLINED             =(EL_TRANS_RET_BASE +44),
    EL_TRANS_RET_NOT_SUPPORT                =(EL_TRANS_RET_BASE +45),
    EL_TRANS_RET_EXPIRED                    =(EL_TRANS_RET_BASE +46),
    EL_TRANS_RET_CARD_LUHN                  =(EL_TRANS_RET_BASE +47),
    
    //abandoned return code
    /*EL_TRANS_RET_ICC_RESET_ERR				=(EL_TRANS_RET_BASE + 1),
     EL_TRANS_RET_ICC_CMD_ERR				=(EL_TRANS_RET_BASE + 2),
     EL_TRANS_RET_ICC_BLOCK					=(EL_TRANS_RET_BASE + 3),
     EL_TRANS_RET_EMV_RSP_ERR				=(EL_TRANS_RET_BASE + 4),
     EL_TRANS_RET_EMV_APP_BLOCK				=(EL_TRANS_RET_BASE + 5),
     EL_TRANS_RET_EMV_NO_APP					=(EL_TRANS_RET_BASE + 6),
     EL_TRANS_RET_EMV_USER_CANCEL			=(EL_TRANS_RET_BASE + 7),
     EL_TRANS_RET_EMV_TIME_OUT				=(EL_TRANS_RET_BASE + 8),
     EL_TRANS_RET_EMV_DATA_ERR				=(EL_TRANS_RET_BASE + 9),
     EL_TRANS_RET_EMV_NOT_ACCEPT				=(EL_TRANS_RET_BASE + 10),
     EL_TRANS_RET_EMV_DENIAL					=(EL_TRANS_RET_BASE + 11),
     EL_TRANS_RET_EMV_KEY_EXP				=(EL_TRANS_RET_BASE + 12),
     EL_TRANS_RET_EMV_NO_PINPAD				=(EL_TRANS_RET_BASE + 13),
     EL_TRANS_RET_EMV_NO_PASSWORD			=(EL_TRANS_RET_BASE + 14),
     EL_TRANS_RET_EMV_SUM_ERR				=(EL_TRANS_RET_BASE + 15),
     EL_TRANS_RET_EMV_NOT_FOUND				=(EL_TRANS_RET_BASE + 16),
     EL_TRANS_RET_EMV_NO_DATA				=(EL_TRANS_RET_BASE + 17),
     EL_TRANS_RET_EMV_OVERFLOW				=(EL_TRANS_RET_BASE + 18),
     EL_TRANS_RET_NO_TRANS_LOG				=(EL_TRANS_RET_BASE + 19),
     EL_TRANS_RET_RECORD_NOTEXIST			=(EL_TRANS_RET_BASE + 20),
     EL_TRANS_RET_LOGITEM_NOTEXIST			=(EL_TRANS_RET_BASE + 21),
     EL_TRANS_RET_ICC_RSP_6985				=(EL_TRANS_RET_BASE + 22),
     EL_TRANS_RET_CLSS_USE_CONTACT			=(EL_TRANS_RET_BASE + 23),
     EL_TRANS_RET_EMV_FILE_ERR				=(EL_TRANS_RET_BASE + 24),
     EL_TRANS_RET_CLSS_TERMINATE				=(EL_TRANS_RET_BASE + 25),
     EL_TRANS_RET_CLSS_FAILED				=(EL_TRANS_RET_BASE + 26),
     EL_TRANS_RET_CLSS_DECLINE				=(EL_TRANS_RET_BASE + 27),
     EL_TRANS_RET_CLSS_TRY_ANOTHER_CARD		=(EL_TRANS_RET_BASE + 28),
     
     EL_TRANS_RET_PARAM_ERR					=(EL_TRANS_RET_BASE + 30),
     EL_TRANS_RET_CLSS_WAVE2_OVERSEA			=(EL_TRANS_RET_BASE + 31),
     EL_TRANS_RET_CLSS_WAVE2_TERMINATED		=(EL_TRANS_RET_BASE + 32),
     EL_TRANS_RET_CLSS_WAVE2_US_CARD			=(EL_TRANS_RET_BASE + 33),
     EL_TRANS_RET_CLSS_WAVE3_INS_CARD		=(EL_TRANS_RET_BASE + 34),
     EL_TRANS_RET_CLSS_RESELECT_APP			=(EL_TRANS_RET_BASE + 35),
     EL_TRANS_RET_CLSS_CARD_EXPIRED			=(EL_TRANS_RET_BASE + 36),
     EL_TRANS_RET_EMV_NO_APP_PPSE_ERR		=(EL_TRANS_RET_BASE + 37),
     EL_TRANS_RET_CLSS_USE_VSDC				=(EL_TRANS_RET_BASE + 38),
     EL_TRANS_RET_CLSS_CVMDECLINE			=(EL_TRANS_RET_BASE + 39),
     EL_TRANS_RET_CLSS_REFER_CONSUMER_DEVICE	=(EL_TRANS_RET_BASE + 40),
     EL_TRANS_RET_CLSS_LAST_CMD_ERR			=(EL_TRANS_RET_BASE + 41),
     EL_TRANS_RET_CLSS_API_ORDER_ERR			=(EL_TRANS_RET_BASE + 42),
     EL_TRANS_RET_EMV_FAIL					=(EL_TRANS_RET_BASE + 43),
     EL_TRANS_RET_EMV_DECLINED				=(EL_TRANS_RET_BASE + 44),*/
    
    
    
    EL_FILEDOWNLOAD_RET_BASE						=(7000),
    EL_FILEDOWNLOAD_ERR_INVALID_PARAM				=(EL_FILEDOWNLOAD_RET_BASE+1),
    EL_FILEDOWNLOAD_ERR_DOWNLOAD_FILE_FAIL			=(EL_FILEDOWNLOAD_RET_BASE+2),
    EL_FILEDOWNLOAD_RET_FIRMWARE_FAIL               =(EL_FILEDOWNLOAD_RET_BASE+3),
    EL_FILEDOWNLOAD_RET_FILE_OVERSIZE               =(EL_FILEDOWNLOAD_RET_BASE+4),
    EL_FILEDOWNLOAD_RET_PARSE_ERR                   =(EL_FILEDOWNLOAD_RET_BASE + 5),
    EL_FILEDOWNLOAD_RET_SIGN_ERR                    =(EL_FILEDOWNLOAD_RET_BASE + 6),
    
    EL_PARAM_RET_BASE                            = 5000,
    EL_PARAM_RET_ERR_DATA                        = (EL_PARAM_RET_BASE + 1),
    EL_PARAM_RET_INVALID_PARAM                   = (EL_PARAM_RET_BASE + 2),
    EL_PARAM_RET_PARTIAL_FAILED                  = (EL_PARAM_RET_BASE + 3),
    EL_PARAM_RET_ALL_FAILED                      = (EL_PARAM_RET_BASE + 4),
    EL_PARAM_RET_BUFFER_TOO_SMALL                = (EL_PARAM_RET_BASE + 5),
    EL_PARAM_RET_API_ORDER_ERR	                 = (EL_PARAM_RET_BASE + 6),
    EL_PARAM_RET_ENCRYPT_SENSITIVE_DATA_FAILED	 =(EL_PARAM_RET_BASE + 7),
    EL_PARAM_RET_SET_CONFIG_TLV_CMD_ERROR        = (EL_PARAM_RET_BASE + 8),
    EL_PARAM_RET_SET_EMV_TLV_CMD_ERROR           = (EL_PARAM_RET_BASE + 9),
    EL_PARAM_RET_UNSUPPORT_CARD                  = (EL_PARAM_RET_BASE + 10),
    
    
    EL_GENERAL_RET_BASE                 = 6000,
    EL_GENERAL_RET_TIMEOUT              = (EL_GENERAL_RET_BASE + 1),
    EL_GENERAL_RET_INVALID_PARAM        = (EL_GENERAL_RET_BASE + 2),
    EL_GENERAL_RET_DEVICE_NOT_EXIST     = (EL_GENERAL_RET_BASE + 3),
    EL_GENERAL_RET_DEVICE_BUSY          = (EL_GENERAL_RET_BASE + 4),
    EL_GENERAL_RET_DEVICE_NOT_OPEN      = (EL_GENERAL_RET_BASE + 5),
    EL_GENERAL_RET_USER_CANCELED        = (EL_GENERAL_RET_BASE + 6),
    EL_GENERAL_RET_CMD_NOT_SUPPORT      = (EL_GENERAL_RET_BASE + 7),
    
    
    
    EL_SDK_RET_BASE                              = 9000,
    EL_SDK_RET_PARAM_INVALID                     = (EL_SDK_RET_BASE + 1),
    EL_SDK_RET_COMM_CONNECT_ERR                  = (EL_SDK_RET_BASE + 2),
    EL_SDK_RET_COMM_DISCONNECT_ERR               = (EL_SDK_RET_BASE + 3),
    EL_SDK_RET_COMM_DISCONNECTED                 = (EL_SDK_RET_BASE + 4),
    EL_SDK_RET_COMM_SEND_ERR                     = (EL_SDK_RET_BASE + 5),
    EL_SDK_RET_COMM_RECV_ERR                     = (EL_SDK_RET_BASE + 6),
    EL_SDK_RET_FILE_NOT_EXIST                    = (EL_SDK_RET_BASE + 7),
    EL_SDK_RET_GET_DATA_FAIL                     = (EL_SDK_RET_BASE + 8),
    EL_SDK_RET_BT_NOT_ENABLED                    = (EL_SDK_RET_BASE + 9),
    EL_SDK_RET_ENC_SESSION_KEY_DEC_ERR           = (EL_SDK_RET_BASE + 10),
    
    
    EL_SDK_PROTO_RET_BASE                        = 9500,
    EL_SDK_RET_PROTO_GENERAL_ERR                 = (EL_SDK_PROTO_RET_BASE + 1),
    EL_SDK_RET_PROTO_ARG_ERR                     = (EL_SDK_PROTO_RET_BASE + 2),
    EL_SDK_RET_PROTO_PACKET_TOO_LONG             = (EL_SDK_PROTO_RET_BASE + 3),
    EL_SDK_RET_PROTO_NO_ENOUGH_DATA              = (EL_SDK_PROTO_RET_BASE + 4),
    EL_SDK_RET_PROTO_DATA_FORMAT                 = (EL_SDK_PROTO_RET_BASE + 5),
    EL_SDK_RET_PROTO_TIMEOUT                     = (EL_SDK_PROTO_RET_BASE + 6),
    
    //RKI error
    EL_RKI_RET_BASE                              = 1400,
    EL_RKI_RET_BIND_PHASE_ONE                    = (EL_RKI_RET_BASE + 1),
    EL_RKI_RET_BIND_PHASE_TWO                    = (EL_RKI_RET_BASE + 2),
    EL_RKI_RET_REBIND_PHASE_ONE                  = (EL_RKI_RET_BASE + 3),
    EL_RKI_RET_REBIND_PHASE_TWO                  = (EL_RKI_RET_BASE + 4),
    EL_RKI_RET_DOWNLOAD_PHASE_ONE                = (EL_RKI_RET_BASE + 5),
    EL_RKI_RET_DOWNLOAD_PHASE_TWO                = (EL_RKI_RET_BASE + 6),
    EL_RKI_RET_PARAM_NULL_ERR                    = (EL_RKI_RET_BASE + 7),
    EL_RKI_RET_INIT_ERR                          = (EL_RKI_RET_BASE + 8),
    EL_RKI_RET_COMM_ERR                          = (EL_RKI_RET_BASE + 9),
    EL_RKI_RET_CONSTRUCT_TLV_ERR                 = (EL_RKI_RET_BASE + 10),
    
    EL_RKI_RET_GET_DEVICE_INFO_ERR               = (EL_RKI_RET_BASE + 11),
    EL_RKI_RET_GET_DA_CERT_ERR                   = (EL_RKI_RET_BASE + 12),
    EL_RKI_RET_GET_DE_CERT_ERR                   = (EL_RKI_RET_BASE + 13),
    EL_RKI_RET_GET_RKI_INFO_ERR                  = (EL_RKI_RET_BASE + 14),
    EL_RKI_RET_PARSE_TLV_ERR                     = (EL_RKI_RET_BASE + 15),
    EL_RKI_RET_SERVICE_REJECT                    = (EL_RKI_RET_BASE + 16),
    EL_RKI_RET_SERVER_CERT_EXPIRE                = (EL_RKI_RET_BASE + 17),
    EL_RKI_RET_SERVER_CLOSE_ERR                  = (EL_RKI_RET_BASE + 18),
    EL_RKI_RET_GEN_DE_AUTH_DATA_ERR              = (EL_RKI_RET_BASE + 19),
    EL_RKI_RET_GET_AUTH_DATA_ERR                 = (EL_RKI_RET_BASE + 20),
    EL_RKI_RET_CERT_INFO_ERR                     = (EL_RKI_RET_BASE + 21),
    
    EL_RKI_RET_WRITE_AUTH_KEY_ERR                = (EL_RKI_RET_BASE + 22),
    EL_RKI_RET_DE_AUTH_TOKEN_ERR                 = (EL_RKI_RET_BASE + 23),    //EL_RKI_RET_RKI_AUTH_TOKEN_ERR
    EL_RKI_RET_WRITE_KMS_ID_ERR                  = (EL_RKI_RET_BASE + 24),
    EL_RKI_RET_VERIFY_PUK_ERR                    = (EL_RKI_RET_BASE + 25),
    EL_RKI_RET_INJECT_KEY_ERR                    = (EL_RKI_RET_BASE + 26),
    
    EL_RKI_RET_PINPAD_PROTOCOL_ERR               = (EL_RKI_RET_BASE + 27),
    EL_RKI_RET_PINPAD_INIT_ERR                   = (EL_RKI_RET_BASE + 28),
    
    EL_RKI_RET_UNBIND_WRITE_KEY_LIST_ERR         = (EL_RKI_RET_BASE + 29),
    EL_RKI_RET_UNBIND_PHASE_ONE                  = (EL_RKI_RET_BASE + 30),
    EL_RKI_RET_UNBIND_PHASE_TWO                  = (EL_RKI_RET_BASE + 31),
    
    EL_RKI_RET_INJECT_OFFLINE_KEY                = (EL_RKI_RET_BASE + 32),
    EL_RKI_RET_OFFLINE_KEY_ERR                   = (EL_RKI_RET_BASE + 33),
    EL_RKI_RET_OFFLINE_KEY_TOO_LONG              = (EL_RKI_RET_BASE + 34),
    
    EL_RKI_RET_END                               = (EL_RKI_RET_BASE + 99),
    
    EL_RKI_SERVER_RET_COMM_TIMEOUT               = 303,    //comm connect err
    EL_RKI_SERVER_RET_COMM_NET_ERR               = 305,    //comm net err
    EL_RKI_SERVER_RET_COMM_DISCONNECTED          = 307,    //comm disconnected
    EL_RKI_SERVER_RET_COMM_NOT_CONNECT           = 308,    //comm net not connect
    EL_RKI_SERVER_RET_COMM_SEND_ERR              = 309,    //comm sent err
    EL_RKI_SERVER_RET_COMM_RECV_ERR              = 310,    //comm recv err
    EL_RKI_SERVER_RET_PARAM_INVALID              = 602,    //invalid param
    EL_RKI_SERVER_RET_COMM_CONNECT_ERR           = 1201,        //comm connect err
    EL_RKI_SERVER_RET_SSL_CERT_ERR               = 1202,        //invalid cert
    
    
    // Smartlanding return code;
    EL_SML_RET_BASE                              = 1600,
    EL_SML_DB_SAVE_ERROR                         = EL_SML_RET_BASE + 1,
    EL_SML_DB_OPEN_ERROR                         = EL_SML_RET_BASE + 2,
    EL_SML_COMM_NO_CERT                          = EL_SML_RET_BASE + 3,
    EL_SML_COMM_DNS_ERROR                        = EL_SML_RET_BASE + 4,
    EL_SML_COMM_SEND_ERR                         = EL_SML_RET_BASE + 5,
    EL_SML_COMM_RECV_ERR                         = EL_SML_RET_BASE + 6,
    EL_SML_COMM_NEW_SSL_CTX_ERR                  = EL_SML_RET_BASE + 7,
    EL_SML_COMM_CREATE_SOCKET_ERR                = EL_SML_RET_BASE + 8,
    EL_SML_COMM_SET_SOCKET_OPT_ERR               = EL_SML_RET_BASE + 9,
    EL_SML_COMM_CONNECT_ERR                      = EL_SML_RET_BASE + 10,
    EL_SML_PACK_PARAM_ERR                        = EL_SML_RET_BASE + 11,
    EL_SML_PACK_TYPE_NOT_SUPPORT                 = EL_SML_RET_BASE + 12,
    EL_SML_UNPACK_FORMAT                         = EL_SML_RET_BASE + 13,
    EL_SML_UNPACK_LRC                            = EL_SML_RET_BASE + 14,
    EL_SML_DEVICE_OPEN_ERR                       = EL_SML_RET_BASE + 15,
    EL_SML_DEVICE_CONFIG_ERR                     = EL_SML_RET_BASE + 16,
    EL_SML_COMM_PARAM_ERR                        = EL_SML_RET_BASE + 17,
    EL_SML_NOT_SUPPORT_RKI_COM                   = EL_SML_RET_BASE + 18,
    EL_SML_EVN_CHECK_ERR                         = EL_SML_RET_BASE + 19,
    EL_SML_EVN_CLEAR_TASK_ERR                    = EL_SML_RET_BASE + 20,
    EL_SML_SERVER_ERR                            = EL_SML_RET_BASE + 21,
    EL_SML_DOWNLOAD_ERR                          = EL_SML_RET_BASE + 22,
    EL_SML_DOWNLOAD_MD5_ERR                      = EL_SML_RET_BASE + 23,
    EL_SML_RET_COMM_HOST_ERROR                   = EL_SML_RET_BASE + 51,
    EL_SML_RET_SYNC_ERROR                        = EL_SML_RET_BASE + 52,
    EL_SML_RET_PROCESS_ERROR                     = EL_SML_RET_BASE + 53,
    EL_SML_RET_APP_INSTALL_ERROR                 = EL_SML_RET_BASE + 54,
    EL_SML_RET_RKI_DOWNLOAD_ERROR                = EL_SML_RET_BASE + 55,
    EL_SML_RET_INVALID_DOWNLOAD_FILE             = EL_SML_RET_BASE + 56,
    EL_SML_RET_TERMINAL_NOT_REGISTER             = EL_SML_RET_BASE + 57,
    EL_SML_USER_CANCEL                           = EL_SML_RET_BASE + 99,
    
    
    //picc return code
    EL_PICC_BASE                                = 8000,
    EL_PICC_PARAM_ERROR                         = EL_PICC_BASE + 1,
    EL_PICC_RF_MODULE_CLOSE                     = EL_PICC_BASE + 2,
    EL_PICC_NO_SPECIFIC_CARD_IN_AREA            = EL_PICC_BASE + 3,
    EL_PICC_TOO_MUCH_CARD_IN_AREA               = EL_PICC_BASE + 4,
    EL_PICC_RESP_PROTOCOL_ERROR                 = EL_PICC_BASE + 5,
    EL_PICC_CARD_NOT_ACTIVATED                  = EL_PICC_BASE + 6,
    EL_PICC_MULTI_CARD_CONFLICT                 = EL_PICC_BASE + 7,
    EL_PICC_NO_RESPONSE_TIMEOUT                 = EL_PICC_BASE + 8,
    EL_PICC_PROTOCOL_ERROR                      = EL_PICC_BASE + 9,
    EL_PICC_COMM_TRANSMIT_ERROR                 = EL_PICC_BASE + 10,
    EL_PICC_M1_CARD_AUTH_FAIL                   = EL_PICC_BASE + 11,
    EL_PICC_SECTOR_NOT_CERTIFIED                = EL_PICC_BASE + 12,
    EL_PICC_DATA_FORMAT_INCORRECT               = EL_PICC_BASE + 13,
    EL_PICC_CARD_STILL_IN_AREA                  = EL_PICC_BASE + 14,
    EL_PICC_CARD_STATUS_ERROR                   = EL_PICC_BASE + 15,
    EL_PICC_INTERFACE_CHIP_ERROR                = EL_PICC_BASE + 16,
    EL_PICC_PAR_FLAG                            = EL_PICC_BASE + 17,
    EL_PICC_CRC_FLAG                            = EL_PICC_BASE + 18,
    EL_PICC_ECD_FLAG                            = EL_PICC_BASE + 19,
    EL_PICC_EMD_FLAG                            = EL_PICC_BASE + 20,
    EL_PICC_PARAMFILE_FLAG                      = EL_PICC_BASE + 21,
    EL_PICC_USER_CANCEL                         = EL_PICC_BASE + 22,
    EL_PICC_CARRIER_OBTAIN_FLAG                 = EL_PICC_BASE + 23,
    EL_PICC_CONFIG_FLAG                         = EL_PICC_BASE + 24,
    EL_PICC_RXLEN_EXCEED_FLAG                   = EL_PICC_BASE + 25,
    EL_PICC_NOT_IDLE_FLAG                       = EL_PICC_BASE + 26,
    EL_PICC__NOT_POLLING_FLAG                   = EL_PICC_BASE + 27,
    EL_PICC_NOT_WAKEUP_FLAG                     = EL_PICC_BASE + 28,
    EL_PICC_NOT_SUPPORT                         = EL_PICC_BASE + 29,
    EL_PICC_BATTERY_VOLTAGE_TOO_LOW             = EL_PICC_BASE + 30,
    EL_PICC_CHIP_ERROR                          = EL_PICC_BASE + 31,
    //msr return code
    EL_MSR_BASE                                 = 8200,
    EL_MSR_RET_FAILED                           = EL_MSR_BASE + 1,
    EL_MSR_RET_HEADE                            = EL_MSR_BASE + 2,
    EL_MSR_RET_END                              = EL_MSR_BASE + 3,
    EL_MSR_RET_LRC                              = EL_MSR_BASE + 4,
    EL_MSR_RET_PAR                              = EL_MSR_BASE + 5,
    EL_MSR_RET_NOT_SWIPED                       = EL_MSR_BASE + 6,
    EL_MSR_RET_NO_DATA                          = EL_MSR_BASE + 7,
    EL_MSR_END_RET_ZERO                         = EL_MSR_BASE + 8,
    EL_MSR_PED_RET_DECRYPT                      = EL_MSR_BASE + 9,
    EL_MSR_RET_NO_TRACK                         = EL_MSR_BASE + 10,
    //icc return code
    EL_ICC_BASE                                 = 8400,
    EL_ICC_RET_SCI_HW_NOCARD                    = EL_ICC_BASE + 1,
    EL_ICC_RET_SCI_HW_STEP                      = EL_ICC_BASE + 2,
    EL_ICC_RET_SCI_HW_PARITY                    = EL_ICC_BASE + 3,
    EL_ICC_RET_SCI_HW_TIMEOUT                   = EL_ICC_BASE + 4,
    EL_ICC_RET_SCI_TCK                          = EL_ICC_BASE + 5,
    EL_ICC_RET_SCI_ATR_TS                       = EL_ICC_BASE + 6,
    EL_ICC_RET_SCI_ATR_TA1                      = EL_ICC_BASE + 7,
    EL_ICC_RET_SCI_ATR_TD1                      = EL_ICC_BASE + 8,
    EL_ICC_RET_SCI_ATR_TA2                      = EL_ICC_BASE + 9,
    EL_ICC_RET_SCI_ATR_TB1                      = EL_ICC_BASE + 10,
    EL_ICC_RET_SCI_ATR_TB2                      = EL_ICC_BASE + 11,
    EL_ICC_RET_SCI_ATR_TC2                      = EL_ICC_BASE + 12,
    EL_ICC_RET_SCI_ATR_TD2                      = EL_ICC_BASE + 13,
    EL_ICC_RET_SCI_ATR_TA3                      = EL_ICC_BASE + 14,
    EL_ICC_RET_SCI_ATR_TB3                      = EL_ICC_BASE + 15,
    EL_ICC_RET_SCI_ATR_TC3                      = EL_ICC_BASE + 16,
    EL_ICC_RET_SCI_T_ORDER                      = EL_ICC_BASE + 17,
    EL_ICC_RET_SCI_PPS_PPSS                     = EL_ICC_BASE + 18,
    EL_ICC_RET_SCI_PPS_PPS0                     = EL_ICC_BASE + 19,
    EL_ICC_RET_SCI_PPS_PCK                      = EL_ICC_BASE + 20,
    EL_ICC_RET_SCI_T0_PARAM                     = EL_ICC_BASE + 21,
    EL_ICC_RET_SCI_T0_REPEAT                    = EL_ICC_BASE + 22,
    EL_ICC_RET_SCI_T0_PROB                      = EL_ICC_BASE + 23,
    EL_ICC_RET_SCI_T1_PARAM                     = EL_ICC_BASE + 24,
    EL_ICC_RET_SCI_T1_BWT                       = EL_ICC_BASE + 25,
    EL_ICC_RET_SCI_T1_CWT                       = EL_ICC_BASE + 26,
    EL_ICC_RET_SCI_T1_BREP                      = EL_ICC_BASE + 27,
    EL_ICC_RET_SCI_T1_LRC                       = EL_ICC_BASE + 28,
    EL_ICC_RET_SCI_T1_NAD                       = EL_ICC_BASE + 29,
    EL_ICC_RET_SCI_T1_LEN                       = EL_ICC_BASE + 30,
    EL_ICC_RET_SCI_T1_PCB                       = EL_ICC_BASE + 31,
    EL_ICC_RET_SCI_T1_SRC                       = EL_ICC_BASE + 32,
    EL_ICC_RET_SCI_T1_SRL                       = EL_ICC_BASE + 33,
    EL_ICC_RET_SCI_T1_SRA                       = EL_ICC_BASE + 34,
    EL_ICC_RET_SCI_PARAM                        = EL_ICC_BASE + 35,
    EL_ICC_RET_SCI_OTHER_ERROR                  = EL_ICC_BASE + 36,
    EL_ICC_RET_SCI_CHANNEL                      = EL_ICC_BASE + 37,
    EL_ICC_RET_SCI_DATA_LEN                     = EL_ICC_BASE + 38,
    EL_ICC_RET_SCI_T1_ABORT                     = EL_ICC_BASE + 39,
    EL_ICC_RET_SCI_T1_EDC                       = EL_ICC_BASE + 40,
    EL_ICC_RET_SCI_T1_SYNC                      = EL_ICC_BASE + 41,
    EL_ICC_RET_SCI_T1_EG                        = EL_ICC_BASE + 42,
    EL_ICC_RET_SCI_T1_BG                        = EL_ICC_BASE + 43,
    EL_ICC_RET_SCI_T1_IFSC                      = EL_ICC_BASE + 44,
    EL_ICC_RET_SCI_T1_IFSD                      = EL_ICC_BASE + 45,
    EL_ICC_RET_SCI_CHAR_GROUP_INVALID           = EL_ICC_BASE + 46,
    EL_ICC_RET_SCI_ATR_TC1                      = EL_ICC_BASE + 47,
    EL_ICC_RET_SCI_ATR_DATA_LEN                 = EL_ICC_BASE + 48,
    EL_ICC_RET_SCI_T0_TIMEOUT                   = EL_ICC_BASE + 49,
    EL_ICC_RET_SCI_T0_RESENT                    = EL_ICC_BASE + 50,
    EL_ICC_RET_SCI_T0_RECEIVE                   = EL_ICC_BASE + 51,
    EL_ICC_RET_SCI_T0_STATUS_BYTE_INVALID       = EL_ICC_BASE + 52,
    EL_ICC_RET_SCI_RE_CHAR_GROUP                = EL_ICC_BASE + 53,
    EL_ICC_RET_SCI_COMM_ERROR                   = EL_ICC_BASE + 54,
    
    
    
} PaxEasyLinkRetCode;
/*!
 @abstract PaxEasyLinkStatusCode managers the return code
 */

@interface PaxEasyLinkStatusCode : NSObject
/*!
 @abstract get PaxEasyLinkStatusCode instance
 */

+ (id)sharedInstance;

/*!
 @abstract convert the return code to the human readable string
 @param code return code
 @return the converted string
 */
- (NSString *)statusCode2String:(PaxEasyLinkRetCode)code;

@end
