//
//  DebugLogger.swift
//  FinixPOS
//
//  Created by Jack Tihon on 12/20/21.
//  Copyright © 2021 Finix Payments. All rights reserved.
//

import Foundation

protocol LoggerProtocol {
    func error(_ items: Any...)
    func warn(_ items: Any...)
    func info(_ items: Any...)
    func debug(_ items: Any...)
}

/// Log messages to file and/or console
class DebugLogger {
    struct Level: OptionSet {
        let rawValue: Int
        static let error = Level(rawValue: 1 << 0)
        static let warn = Level(rawValue: 1 << 1)
        static let info = Level(rawValue: 1 << 2)
        static let debug = Level(rawValue: 1 << 3)
        static let verbose: Level = [.error, .warn, .info, .debug]
    }

    var level: Level = .verbose
}

extension DebugLogger: LoggerProtocol {
    private func output(_ items: [Any]) {
        let output: String = items.map {
            if let str = $0 as? String {
                return str
            } else {
                return String(describing: $0)
            }
        }.joined()
        print(output)
    }

    func error(_ items: Any...) {
        guard level.contains(.error) else {
            return
        }
        output(items)
    }

    // HAX to get array of objects to print properly because we can't splat a variadic list to pass into print/debugPrint
    func error(_ arr: [Any]) {
        guard level.contains(.error) else {
            return
        }
        output(arr)
    }

    func warn(_ items: Any...) {
        guard level.contains(.warn) else {
            return
        }
        output(items)
    }

    // HAX to get array of objects to print properly because we can't splat a variadic list to pass into print/debugPrint
    func warn(_ arr: [Any]) {
        guard level.contains(.warn) else {
            return
        }
        output(arr)
    }

    func info(_ items: Any...) {
        guard level.contains(.info) else {
            return
        }
        output(items)
    }

    // HAX to get array of objects to print properly because we can't splat a variadic list to pass into print/debugPrint
    func info(_ arr: [Any]) {
        guard level.contains(.info) else {
            return
        }
        output(arr)
    }

    func debug(_ items: Any...) {
        guard level.contains(.debug) else {
            return
        }
        output(items)
    }

    // HAX to get array of objects to print properly because we can't splat a variadic list to pass into print/debugPrint
    func debug(_ arr: [Any]) {
        guard level.contains(.debug) else {
            return
        }
        output(arr)
    }
}

class FinixLogger {
    struct Component: OptionSet {
        let rawValue: Int
        static let finix = Component(rawValue: 1 << 0)
        static let http = Component(rawValue: 1 << 1)
        static let express = Component(rawValue: 1 << 2)
        static let all: Component = [.finix, .http, .express]
    }

    var logger = DebugLogger()
    var component: Component = .finix

    func log(_ items: Any...) {
        guard component.contains(.finix) else {
            return
        }
        logger.info(items)
    }

    func http(_ items: Any...) {
        guard component.contains(.http) else {
            return
        }
        var output: [Any] = ["[HTTP]"]
        output.append(contentsOf: items)
        logger.info(output)
    }

    func http(request: URLRequest) {
        guard component.contains(.http) else {
            return
        }
        let url = request.url?.absoluteString ?? ""
        let method = request.httpMethod ?? ""
        guard let body = request.httpBody else {
            http("REQUEST: \(method) \(url)")
            return
        }
        let jsonBody = String(data: body, encoding: .utf8) ?? ""
        http("REQUEST: \(method) \(url)\n\(jsonBody)")
    }

    func http(error: Error) {
        http("Error: \(error.localizedDescription)")
    }

    func http(response: HTTPURLResponse) {
        guard component.contains(.http) else {
            return
        }
        let url = response.url?.absoluteString ?? ""
        let status = response.statusCode
        logger.info("[HTTP]RESPONSE: \(status) \(url)")
    }

    func http(responseData data: Data?) {
        guard let data = data else {
            logger.info("[HTTP]RESPONSE Data empty")
            return
        }
        let dataString = String(data: data, encoding: .utf8) ?? "not a string"
        logger.info("[HTTP]RESPONSE DATA:\n\(dataString)")
    }

    private func formatXML(_ xmlString: String) -> String? {
        #if os(macOS)
            do {
                let xml = try XMLDocument(xmlString: xmlString) // macOS 10.4
                let data = xml.xmlData(options: .nodePrettyPrint)
                let str: String? = String(data: data, encoding: .utf8)
                return str
                return xmlString // TODO: can't parse XML
            } catch {
                print(error.localizedDescription)
            }
            return nil
        #else
            return xmlString // iOS doesn't have XML pretty printing
        #endif
    }

    func express(_ items: Any...) {
        guard component.contains(.express) else {
            return
        }
        var output: [Any] = ["[Express]"]

        let processed: [Any] = items.map {
            if let src = $0 as? String, let pretty = self.formatXML(src) {
                return pretty
            } else {
                return $0
            }
        }
        output.append(contentsOf: processed)
        logger.info(output)
    }
}

extension FinixLogger: LoggerProtocol {
    func error(_ items: Any...) {
        logger.error(items)
    }

    func warn(_ items: Any...) {
        logger.warn(items)
    }

    func info(_ items: Any...) {
        logger.info(items)
    }

    func debug(_ items: Any...) {
        logger.debug(items)
    }
}
