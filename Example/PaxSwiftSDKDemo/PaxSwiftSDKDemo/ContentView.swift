//
//  ContentView.swift
//  PaxSwiftSDKDemo
//
//  Created by Tom Nguyen on 1/7/25.
//

import SwiftUI
import PaxSwift

struct ContentView: View {
    var body: some View {
        VStack {
            Image(systemName: "globe")
                .imageScale(.large)
                .foregroundStyle(.tint)
            Text("Hello, world!")
        }
        .padding()
        .onAppear {
            let client = FinixClient(config: .init(environment: .QA, credentials: .init(username: "test", password: "test"), application: "test", version: "2.0", merchantId: "test", mid: "test", deviceType: .Pax, deviceId: "test"))
            print(client)
        }
    }
}

#Preview {
    ContentView()
}
