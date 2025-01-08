//
//  PaxManager.swift
//  PaxMposSDK
//
//  Created by Jack Tihon on 5/3/24.
//

import Foundation
import PaxEasyLinkControllerWrapper

// delegate to handle card reader prompts
protocol PaxManagerDelegate: AnyObject {
    // on needing a tap/swipe/insert
    func promptForCard(manager: PaxManager, prompt: String)

    // when done reading card
    func didReadCard(manager: PaxManager, prompt: String)
}

enum TransactionResult {
    case success
    case failure(FinixError)
}

// Manager card reader resource
class PaxManager: NSObject {
    init(logger: FinixLogger) {
        self.logger = logger
        PaxSetLogLevel(PAX_LOG_LEVEL_INFO) // set to highest log level
//        PAX_LOG_LEVEL_WRN
//        PAX_LOG_LEVEL_DBG
//        PaxSetLogLevel(PAX_LOG_LEVEL_ERR)

        super.init()
        easyLink.delegate = self
    }

    private var easyLink: PaxEasyLinkController {
        PaxEasyLinkController.getInstance()
    }

    weak var delegate: PaxManagerDelegate?

    public var logger: FinixLogger

    private let transactionQueue: DispatchQueue = .init(label: "PaxManager", qos: .userInteractive, attributes: [.concurrent])
}

/// These values come  from PaxEasyLinkConst.h - enum DataType
internal enum PaxDataType: UInt {
    case transactionData = 1 // DataType.TRANSACTION_DATA
    case configurationData = 2 // DataType.CONFIGURATION_DATAa

    var asInt: Int { Int(rawValue) }
}

// Low-level read/write methods

private extension PaxManager {
    /// low-level set data
    func getData(type dataType: UInt, tagList: Data, tlvArray: inout NSArray?) -> Bool {
        let rv = easyLink.getData(dataType, tagList: tagList, tlvArray: &tlvArray)
        guard rv == EL_RET_OK else {
            logger.error("getData returned \(rv)")
            logReturnValue(rv)
            return false
        }
        return true
    }

    /// low-level set data
    /// @parameters
    /// - dataType: DataModel.DataType
    /// - dataList:  TLV data list
    /// - tagList: tagListReturn
    func setData(type dataType: Int, dataList: Data, tagList: inout NSData?) -> Bool {
        let rv = easyLink.setData(dataType, dataList: dataList, tagList: &tagList)
        guard rv == EL_RET_OK else {
            logger.error("setData returned \(rv)")
            logReturnValue(rv)
            return false
        }
        return true
    }
}

// internal interface methods
extension PaxManager {
    // get data and return into `tlv`
    func getData(ofType dataType: PaxDataType, tags: [EMVTag], tlv: inout [FinixTLVItem]) -> Bool {
        // convert from mposTLVItem
        let dataType = dataType.rawValue
        let tagList: Data = convert(tags)

        let inputTagsStringList = tags.map(\.data.hexadecimal)
        logger.debug("PaxManager:getData: input tags = [\(inputTagsStringList)]")
        logger.debug("PaxManager:getData: tags raw data = [\(tagList.hexadecimal)]")

        var tlvArray: NSArray?
        let rv = getData(type: dataType, tagList: tagList, tlvArray: &tlvArray)
        guard rv == true else {
            return false
        }

        guard let tlvArray else {
            // nothing returned
            return true
        }
        for item in tlvArray {
            guard let item = item as? TlvItem else {
                continue
            }
            tlv.append(.init(item))
        }
        return true
    }

    // get data and return into `tlv`
    func getDataWithRawReturnValue(ofType dataType: PaxDataType, tags: [EMVTag], tlv: inout [FinixTLVItem]) -> PaxEasyLinkRetCode {
        // convert from mposTLVItem
        let dataType = dataType.rawValue
        let tagList: Data = convert(tags)

        let inputTagsStringList = tags.map(\.data.hexadecimal)
        logger.debug("PaxManager:getData: input tags = [\(inputTagsStringList)]")
        logger.debug("PaxManager:getData: tags raw data = [\(tagList.hexadecimal)]")

        var tlvArray: NSArray?
        let rv = easyLink.getData(dataType, tagList: tagList, tlvArray: &tlvArray)

        guard let tlvArray else {
            // nothing returned
            return rv
        }
        for item in tlvArray {
            guard let item = item as? TlvItem else {
                continue
            }
            tlv.append(.init(item))
        }
        return rv
    }

    // send data to reader
    func setData(ofType dataType: PaxDataType, dataList: [Data], tagList _: inout [EMVTag]) -> Bool {
        let dataType = dataType.asInt
        var rawTagList: NSData?

        // TODO: merge dataList into one blob
        var mergedData = Data()
        dataList.forEach { mergedData.append($0) }

        let rv = setData(type: dataType, dataList: mergedData, tagList: &rawTagList)
        guard rv == true else {
            logger.info("failed", rawTagList)
            return false
        }
        return true
    }
}

extension PaxManager: PaxTransactionProcessing {
    // send configuration data
    func configure() -> Bool {
        logger.info("PaxManager: configure start")
        let configTLVrawString = "020201010203010502040100"
        let configTLV = configTLVrawString.hexadecimal!

        logger.debug("configuring with ")
        var failedTags: [EMVTag] = []
        let rv = setData(ofType: .configurationData, dataList: [configTLV], tagList: &failedTags)
        guard rv == true else {
            logger.debug("PaxManager: configure failed with tags: ", failedTags)
            logger.info("PaxManager: configure finished with error")
            return false
        }
        logger.info("PaxManager: configure finished with success", " failedTags = \(failedTags)")
        return true
    }

    /** setup the transaction
        - amount - currency.. must be USD!

     */
    func setupTransaction(amount: Currency, date: Date) -> Bool {
        // TODO: set up transaction parameters

        let yearMonthDayFormatter = DateFormatter()
        yearMonthDayFormatter.dateFormat = "yyMMdd"

        let timeFormatter = DateFormatter()
        timeFormatter.dateFormat = "HHmmss"

        let transactionHeader = "9C0100"

        let transactionDateHeader = "9a03"
        let transactionDate = yearMonthDayFormatter.string(from: date) // + yyMMdd bcd

        let transactionTimeHeader = "9f2103"
        let transactionTime = timeFormatter.string(from: date) // + HHmmss

        // NOTE: amount can only be 6 characters
        let amountsHeader = "9f0206"
        let amountEncoded = String(format: "%012d", amount.amount)

        assert(amountEncoded.count == 12, "amount string too long. expected 12 but got \(amountEncoded.count) instead!")
        let amount = amountEncoded + amountEncoded // +  3bytes for amount, 3bytes for authorized. Amount, Authorised (Numeric)

        let transactionData = [transactionHeader,
                                       transactionDateHeader, transactionDate,
                                       transactionTimeHeader, transactionTime,
                                       amountsHeader,
                                       amountEncoded]

        logger.debug("PaxManager: setupTransaction tranaction data ", transactionData)

        // TODO: BCD conversion?
        let dataList: [Data] = transactionData.map {
            $0.hexadecimal!
        }

        var failedTags: [EMVTag] = []
        let rv = setData(ofType: .transactionData, dataList: dataList, tagList: &failedTags)

        guard rv == true else {
            logger.info("PaxManager: setupTransaction failed ", failedTags)
            return false
        }
        logger.info("PaxManager: setupTransaction success ", failedTags)
        return true
    }

    func startTransaction() -> TransactionResult {
        let rv = easyLink.startTransaction()
        guard rv == EL_RET_OK else {
            logger.debug("PaxManager: startTransaction failed with \(rv)")
            logReturnValue(rv)

            switch rv.rawValue {
            case 4000..<5000:
                return .failure(FinixError(code: .BadCard, message: "Card not accepted by terminal"))
            default:
                return .failure(FinixError(code: .Unknown, message: "Unknown error occurred"))
            }
        }

        return .success
    }

    func completeTransaction() -> Bool {
        let rv = easyLink.completeTransaction()
        guard rv == EL_RET_OK else {
            debugPrint("startTransaction failed with \(rv)")
            return false
        }
        return true
    }

    func clearTransaction() -> Bool {
        let rv = easyLink.clearTransaction()
        guard rv == EL_RET_OK else {
            debugPrint("startTransaction failed with \(rv)")
            return false
        }
        return true
    }

    // get the Aid value
    func readAidValue() -> FinixTLVItem? {
        let aidTag = EMVTag.TagValue.AID.tag
        var tlvValues: [FinixTLVItem] = []
        if getData(ofType: .transactionData, tags: [aidTag], tlv: &tlvValues) {
            logger.info("PaxManager: readAidValue success. tlvValues = ", tlvValues)
        } else {
            logger.error("PaxManager: readAidValue failed. tlvValues = ", tlvValues)
        }
        return tlvValues.first
    }

    // Aka CurrentTxnType in EasyLink Appendix 3
    enum CardInputType: UInt8 {
        case none = 0
        case magneticSwipeCard = 1
        case fallbackSwipeCard = 2
        case emvContactCard = 3
        case contactlessCard = 4
        case manualPANentry = 5
        case fallbackWithNoApp = 6
        case unknown = 0xFF

        var inputMethod: FinixOperation.CardReader.CardInputMethod? {
            switch self { case .none:
                return nil
            case .magneticSwipeCard:
                return .swipe
            case .fallbackSwipeCard:
                return .swipe
            case .emvContactCard:
                return .chip
            case .contactlessCard:
                return .contactless
            case .manualPANentry:
                return nil
            case .fallbackWithNoApp:
                return nil
            case .unknown:
                return nil
            }
        }
    }

    // read the card's input type
    private func getInputType() -> CardInputType? {
        let cardReadTag: EMVTag = .TagValue.PaxCardReadMethod.tag
        var tlvOutput: [FinixTLVItem] = []
        let rv = getData(ofType: .configurationData, tags: [cardReadTag], tlv: &tlvOutput)

        guard rv else {
            logger.info("PaxManager: getInputType failed with \(rv)")
            return nil
        }

        logger.info("PaxManager: getInputType success with: ", tlvOutput)

        let item = tlvOutput.first?.tlv
        guard let item else {
            logger.info("PaxManager: getInputType fiailed to get tlvitem")
            return nil
        }

        logger.info("tag: \(item.tag!)  value: \(String(describing: item.value))")
        let tagValue: UInt8 = item.value.withUnsafeBytes { pointer in
            pointer.load(as: UInt8.self)
        }
        let inputType = CardInputType(rawValue: tagValue)

        logger.info("Card Input Type: \(String(describing: inputType))")
        return inputType
    }

    // getting track 2 data from a tap or chip
    private func getEMVContactlessTrack2() -> [FinixTLVItem] {
        let track2Tag: EMVTag = .TagValue.PaxEMVContactlessTrack2.tag
        var tlvItems: [FinixTLVItem] = []
        let rv = getData(ofType: .transactionData, tags: [track2Tag], tlv: &tlvItems)

        if rv == true {
            logger.info("PaxManager: getEMVContactlessTrack2 succeeded. tlvItems = ", tlvItems)
        } else {
            logger.info("PaxManager: getEMVContactlessTrack2 failed. tlvItems = ", tlvItems)
        }
        return tlvItems
    }

    private func getSwipeTrack2() -> String? {
        let track2Tag: EMVTag = .TagValue.swipeTrack2.tag
        return getData(tag: track2Tag)
    }

    private func getSwipeTrack1() -> String? {
        let track1Tag: EMVTag = .TagValue.swipeTrack1.tag
        return getData(tag: track1Tag)
    }

    private func getData(tag: EMVTag) -> String? {
        // getting track 2 data from a swipe
        var tlvItems: [FinixTLVItem] = []
        let rv = getData(ofType: .configurationData, tags: [tag], tlv: &tlvItems)

        if rv == true {
            logger.info("PaxManager: getData succeeded. tlvItems = ", tlvItems)
        } else {
            logger.info("PaxManager: getData failed. tlvItems = ", tlvItems)
        }
        guard let track2data = tlvItems.first?.tlv.value else {
            logger.error("no tlv item for track2")
            return nil
        }
        guard let track2 = String(data: track2data, encoding: .ascii) else {
            logger.error("no ascii string from track2 data")
            return nil
        }

        return track2
    }

    internal func parseTrack2(_ track2: String) -> Track2Data {
        logger.info("passed in track 2 =", track2)
        return Track2Util.parseTrack2(track2)
    }

    func getEMVAndCardData() -> EMVData? {
        // get tag value 9F06
        guard let aidValue = readAidValue() else {
            logger.error("PaxManager: getEMVAndCardData: ERROR: AID value read failed.")
            return nil
        }
        logger.info("AID VALUE: \(aidValue)")

        // determine card type
        let cardType = EMVUtil.cardType(from: aidValue)
        logger.info("PaxManager:getEMVAndCardData: cardType = \(cardType.rawValue)")

        // get the tags appropriate for the card type
        let rawCardTags = EMVUtil.cardTags(for: cardType)
        logger.info("PaxManager:getEMVAndCardData: rawTags = \(rawCardTags)")

        // read EMV tags
        let cardTags = rawCardTags.map { EMVTag(hexString: $0)! }

        var tlvItems: [FinixTLVItem] = []
        let rv = getDataWithRawReturnValue(ofType: .transactionData, tags: cardTags, tlv: &tlvItems)

        logger.info("PaxManager:getEMVAndCardData: success for card type \(cardType.rawValue). tlv =", tlvItems)
        var emvData = Data()

        // encode data in TLV format
        for item in tlvItems {
            let valueLengthInBytes: UInt8 = .init(item.tlv.value.count)
            let lengthData: [UInt8] = [valueLengthInBytes]
            logger.info("EMV: tag=\(item.tlv.tag.hexadecimal) length=\(valueLengthInBytes) value=\(item.tlv.value.hexadecimal)")

            if valueLengthInBytes != 0 {
                emvData.append(item.tlv.tag)
                emvData.append(contentsOf: lengthData)
                emvData.append(item.tlv.value)
            } else {
                logger.info("skipping")
            }
        }

        let outputTags = tlvItems.map(\.tlv.tag.hexadecimal)
        compareCardTags(cardType: cardType, rawCardTags, outputTags)

        // TODO: check return value
        logReturnValue(rv)
        return EMVData(data: emvData)
    }

    // compare two sets of tags. log the intersection and which are only in each other set
    private func compareCardTags(cardType: CardType, _ cardTags: [String], _ outputTags: [String]) {
        let firstSet: Set = .init(cardTags.map { $0.lowercased() })
        let secondSet: Set = .init(outputTags.map { $0.lowercased() })

        let intersection = firstSet.intersection(secondSet)
        let onlyInFirst = firstSet.subtracting(secondSet)
        let onlyInSecond = secondSet.subtracting(firstSet)

        logger.info("""
            cardType = \(cardType.rawValue)
            cardTags = \(firstSet)
            outputTags = \(secondSet)

            intersection = \(intersection)
            only in card = \(onlyInFirst)
            only in returned = \(onlyInSecond)
        """)
    }

    func sanitizeTrack1(_ track1: String?) -> String? {
        guard let track1 = track1 else {
            return nil
        }
        var sanitized = track1
        if sanitized.first == "%" {
            sanitized = String(sanitized.dropFirst())
        }
        if sanitized.last == "?" {
            sanitized = String(sanitized.dropLast())
        }
        return sanitized
    }

    func readCardData() -> (CardInputType?, CardDetails?) {
        // get input type
        guard let inputType = getInputType() else {
            logger.info("PaxManager: readCardData: getInputType failed.")
            return (nil, nil)
        }

        // parse card data
        switch inputType {
        case .none:
            logger.info("PaxManager: readCardData: unsupported card method")
        case .magneticSwipeCard:
            logger.info("PaxManager: readCardData: Card Swipe")
            guard let track2 = getSwipeTrack2() else {
                logger.error("PaxManager: readCardData. swipe track2 read failed!")
                return (inputType, nil)
            }
            let parsedTrack2 = parseTrack2(track2)

            let track1 = getSwipeTrack1()
            let sanitizedTrack1 = sanitizeTrack1(track1)

            return (inputType, CardDetails(cardNumber: parsedTrack2.cardNumber,
                                           expiry: parsedTrack2.expiryDate,
                                           emv: nil,
                                           track1: sanitizedTrack1, // Get track1
                                           track2: parsedTrack2.sanitizedTrack2))

        case .fallbackSwipeCard:
            // TODO: is this same as swipe above?
            logger.info("PaxManager: readCardData: unsupported card method")
        case .emvContactCard, .contactlessCard:
            logger.info("PaxManager: readCardData: Contactless")
            guard let track2 = getEMVContactlessTrack2().first?.tlv.value.hexadecimal else {
                logger.error("PaxManager: readCardData. EMV track2 read failed!")
                return (inputType, nil)
            }
            let parsedTrack2 = parseTrack2(track2)
            let emvCardData: EMVData? = getEMVAndCardData()

            logger.info("PaxManager: readCardData: Contactless: got:", [track2, parsedTrack2, emvCardData?.data.hexadecimal ?? ""])
            return (inputType, CardDetails(cardNumber: parsedTrack2.cardNumber,
                                           expiry: parsedTrack2.expiryDate,
                                           emv: emvCardData?.data.hexadecimal.uppercased() ?? nil,
                                           track1: nil,
                                           track2: parsedTrack2.sanitizedTrack2))
        case .manualPANentry,
             .fallbackWithNoApp:
            logger.info("PaxManager: readCardData: unsupported card method")
        case .unknown:
            logger.info("PaxManager: readCardData: unsupported card method")
        }

        return (nil, nil)
    }

    func finishTransaction() -> Bool {
        let completeRV = easyLink.completeTransaction()
        let clearRV = easyLink.clearTransaction()
        guard completeRV == EL_RET_OK, clearRV == EL_RET_OK else {
            return false
        }
        return true
    }

    func cancelTransaction() {
        transactionQueue.async { [self] in
            logger.info("PaxManager: cancelTransaction")
            let sendCancelRv = easyLink.sendCancel()
            logger.info("sendCancel \(sendCancelRv)")
            logReturnValue(sendCancelRv)

            let rv = easyLink.clearTransaction()
            logger.info("clearTransaction \(rv)")
            logReturnValue(rv)
        }
    }
}

/**
 to run a transaction, PaxManager must go through the following steps:

    * configure() -- set card reader params
    * setupTransaction() -- set the transaction amount -- primes the card reader?
    * startTransaction() -- run the transaction
    * completeTransaction() -- finish processing

    NOTE: make sure to call `clearTransaction()` to clear out previously set-up transaction
 */
protocol PaxTransactionProcessing {
    // call this before a transaction
    func configure() -> Bool
    func setupTransaction(amount: Currency, date: Date) -> Bool
    func startTransaction() -> TransactionResult
    func readCardData() -> (PaxManager.CardInputType?, CardDetails?)
    func completeTransaction() -> Bool
    func clearTransaction() -> Bool
    func cancelTransaction() // cancel in-flight operation?

    // get the aid value
    func readAidValue() -> FinixTLVItem?
}

extension PaxManager {
    typealias DoTransactionCompletion = (CardInputType?, CardDetails?, Error?) -> Void

    public func doTransaction(amount: Currency, completion: DoTransactionCompletion?) {
        // finish any pending work first
        _ = finishTransaction()

        let configureRv = configure()
        guard configureRv == true else {
            debugPrint("configure failed!")
            return
        }

        let date = Date() // now

        let setupTransactionRv = setupTransaction(amount: amount, date: date)
        guard setupTransactionRv == true else {
            logger.info("setupTransaction failed!")
            return
        }

        // NOTE: This is happening on a background queue because operations are synchronous!

        transactionQueue.async {
            // NOTE: this should trigger a card read
            let rv = self.startTransaction()

            switch rv {
            case .failure(let startTransactionError):
                self.logger.info("startTransaction failed!")

                let clearTransactionResult = self.clearTransaction()
                guard clearTransactionResult == true else {
                    self.logger.info("startTransaction: clearTransaction failed!")
                    completion?(nil, nil, startTransactionError)
                    return
                }

                completion?(nil, nil, startTransactionError)
                return
            case .success:
                break
            }

            let (inputType, cardDetails) = self.readCardData()

            guard let cardDetails else {
                let rv = self.clearTransaction()
                if rv != true {
                    self.logger.info("clear transaction failed!")
                    let error = FinixError(code: .TransactionError(.unknown), message: "No card data read.")
                    completion?(nil, nil, nil)
                    return
                }
                return
            }

            // done
            completion?(inputType, cardDetails, nil)
        } // async
    }
}

public typealias DownloadStatusCallback = (_ filename: String, _ progress: Int, _ total: Int) -> Void

extension PaxManager {
    // needed to get reader up to date
    // NOTE: must be run from the main thread
    public func downloadFiles(_ progressCallback: DownloadStatusCallback?) {
        transactionQueue.async {
            let files = [
                ("emv_param", "emv", "emv_param.emv"),
                ("clss_param", "clss", "clss_param.clss"),
                ("EASYLINK_LITE", "bin", "EASYLINK_LITE.bin")
            ]

            files.forEach { resource, fileExtension, filename in
                let path = Bundle(for: Self.self).path(forResource: resource, ofType: fileExtension)
                self.logger.info("path = \(path)")
                let returnCode = self.easyLink.fileDownLoad(filename, filePath: path) { progress, total in
                    print("\(progress) / \(total)")
                    DispatchQueue.main.async {
                        progressCallback?(filename, progress, total)
                    }
                }
                print("RETCODE: \(returnCode)")
            }
        }
    }
}

extension PaxManager {
    func logReturnValue(_ rv: PaxEasyLinkRetCode) {
        switch rv {
        case EL_RET_OK:
            logger.info("EL_RET_OK")

        // 1000 series
        case EL_COMM_RET_CONNECTED: // 1001
            logger.info("EL_COMM_RET_CONNECTED")
        case EL_COMM_RET_DISCONNECT_FAIL:
            logger.info("EL_COMM_RET_DISCONNECT_FAIL")
        case EL_COMM_RET_NOTCONNECTED:
            logger.info("EL_COMM_RET_NOTCONNECTED")

        // 4000 series
        case EL_TRANS_RET_READ_CARD_FAIL:
            logger.info("EL_TRANS_RET_READ_CARD_FAIL")
        case EL_TRANS_RET_CARD_BLOCKED:
            logger.info("EL_TRANS_RET_CARD_BLOCKED")
        case EL_TRANS_RET_USER_CANCELED:
            logger.info("EL_TRANS_RET_USER_CANCELED")
        case EL_TRANS_RET_TIME_OUT:
            logger.info("EL_TRANS_RET_TIME_OUT")
        case EL_TRANS_RET_CARD_DATA_ERROR:
            logger.info("EL_TRANS_RET_CARD_DATA_ERROR")
        case EL_TRANS_RET_TRANS_NOT_ACCEPT:
            logger.info("EL_TRANS_RET_TRANS_NOT_ACCEPT")
        case EL_TRANS_RET_TRANS_FAILED:
            logger.info("EL_TRANS_RET_TRANS_FAILED")
        case EL_TRANS_RET_TRASN_DECLINED:
            logger.info("EL_COMM_RET_NOTCONNECTED")
        case EL_TRANS_RET_NOT_SUPPORT:
            logger.info("EL_TRANS_RET_NOT_SUPPORT")
        case EL_TRANS_RET_EXPIRED:
            logger.info("EL_TRANS_RET_EXPIRED")
        case EL_TRANS_RET_CARD_LUHN:
            logger.info("EL_TRANS_RET_CARD_LUHN")

        // 5000 series
        case EL_PARAM_RET_ERR_DATA:
            logger.error("setData:ERROR: EL_PARAM_RET_ERR_DATA")
        case EL_PARAM_RET_INVALID_PARAM:
            logger.error("setData:ERROR: EL_PARAM_RET_INVALID_PARAM")
        case EL_PARAM_RET_PARTIAL_FAILED:
            logger.error("setData:ERROR: EL_PARAM_RET_PARTIAL_FAILED")
        case EL_PARAM_RET_ALL_FAILED:
            logger.error("setData:ERROR: EL_PARAM_RET_ALL_FAILED")
        case EL_PARAM_RET_BUFFER_TOO_SMALL:
            logger.error("setData:ERROR: EL_PARAM_RET_BUFFER_TOO_SMALL")
        case EL_PARAM_RET_API_ORDER_ERR:
            logger.error("setData:ERROR: EL_PARAM_RET_API_ORDER_ERR")
        case EL_PARAM_RET_ENCRYPT_SENSITIVE_DATA_FAILED:
            logger.error("setData:ERROR: EL_PARAM_RET_ENCRYPT_SENSITIVE_DATA_FAILED")
        case EL_PARAM_RET_SET_CONFIG_TLV_CMD_ERROR:
            logger.error("setData:ERROR: EL_PARAM_RET_SET_CONFIG_TLV_CMD_ERROR")
        case EL_PARAM_RET_SET_EMV_TLV_CMD_ERROR:
            logger.error("setData:ERROR: EL_PARAM_RET_SET_EMV_TLV_CMD_ERROR")
        default:
            break
        }
    }
}

extension PaxManager: PaxEasyReportDelegate {
    // waiting for card
    func onReportSearchMode(withPrompts prompts: String!, searchMode model: Int) {
        logger.info("PaxManager: onReportSearchMode prompts: \(prompts ?? ""), searchMode: \(model)")
        delegate?.promptForCard(manager: self, prompt: prompts)
    }

    // card data read
    func onReadCard(withPrompts prompts: String!, detectType type: Int, readCardStatus: Int) {
        // TODO: report status
        logger.info("PaxManager: onReadCard prompts: \(prompts ?? ""), detectType: \(type), readCardStatus: \(readCardStatus)")
        delegate?.didReadCard(manager: self, prompt: prompts)
    }
}
