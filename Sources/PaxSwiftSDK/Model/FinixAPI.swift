//
//  FinixAPI.swift
//  FinixPOS
//
//  Created by Jack Tihon on 3/17/20.
//  Copyright © 2020 Finix Payments, Inc. All rights reserved.
//

import Foundation

typealias MerchantId = String

// Internal API mappings. Not to be exposed to clients
internal enum FinixAPIResponse {
    // Response from calling merchants for a specific merchant. We are only interested in "processor_details" to initialize TriPOS
    internal struct MerchantsResponse: Decodable {
        let id: MerchantId
        let application: String
        let identity: IdentityId
        let merchantName: String

        let mcc: String
        let processorDetails: MerchantProcessorDetails // nested data

        private enum CodingKeys: String, CodingKey {
            case id
            case application
            case identity
            case merchantName = "merchant_name"
            case mcc
            case processorDetails = "processor_details"
        }
    }

    // The interior node from the above `MerchantsResponse` call.
    internal struct MerchantProcessorDetails: Decodable {
        let accountId: String
        let applicationId: String
        let acceptorId: String
        let accountToken: String

        private enum CodingKeys: String, CodingKey {
            case accountId = "account_id"
            case applicationId = "id"
            case acceptorId = "acceptor_id"
            case accountToken = "account_token"
        }
    }

    internal struct DeviceProcessorDetail: Decodable {
        let laneId: String
        let terminalId: String

        private enum CodingKeys: String, CodingKey {
            case laneId = "terminal_id"
            case terminalId = "terminal_batch_id"
        }
    }
}

/**
 Fetch a Merchant

 https://developers.finixpayments.com/apis/merchants/fetch-a-merchant/

 HTTP Request
 GET https://finix.sandbox-payments-api.com/merchants/:MERCHANT_ID

 URL Parameters
 :MERCHANT_ID    ID of the Merchant

 RESPONSE
 {
   "id" : "MUucec6fHeaWo3VHYoSkUySM",
   "application" : "APgPDQrLD52TYvqazjHJJchM",
   "identity" : "IDpYDM7J9n57q849o9E9yNrG",
   "verification" : "VIdikDHXv7x8nWyJg8JZemGx",
   "merchant_profile" : "MPzW2oRPtkLxK3fymcMACFi",
   "processor" : "DUMMY_V1",
   "processing_enabled" : true,
   "settlement_enabled" : true,
   "gross_settlement_enabled" : false,
   "creating_transfer_from_report_enabled" : true,
   "card_expiration_date_required" : true,
   "card_cvv_required" : false,
   "tags" : {
     "key_2" : "value_2"
   },
   "mcc" : "0742",
   "mid" : "FNX7CwmebftudY7i5mA4qF6XT",
   "merchant_name" : "Petes Coffee",
   "settlement_funding_identifier" : "UNSET",
   "ready_to_settle_upon" : "RECONCILIATION",
   "fee_ready_to_settle_upon" : "RECONCILIATION",
   "level_two_level_three_data_enabled" : false,
   "created_at" : "2022-01-27T07:36:58.19Z",
   "updated_at" : "2022-01-27T07:36:58.46Z",
   "onboarding_state" : "APPROVED",
   "processor_details" : {
     "mid" : "FNX7CwmebftudY7i5mA4qF6XT",
     "api_key" : "secretValue"
   },
   "_links" : {
     "self" : {
       "href" : "https://finix.sandbox-payments-api.com/merchants/MUucec6fHeaWo3VHYoSkUySM"
     },
     "identity" : {
       "href" : "https://finix.sandbox-payments-api.com/identities/IDpYDM7J9n57q849o9E9yNrG"
     },
     "verifications" : {
       "href" : "https://finix.sandbox-payments-api.com/merchants/MUucec6fHeaWo3VHYoSkUySM/verifications"
     },
     "merchant_profile" : {
       "href" : "https://finix.sandbox-payments-api.com/merchant_profiles/MPzW2oRPtkLxK3fymcMACFi"
     },
     "application" : {
       "href" : "https://finix.sandbox-payments-api.com/applications/APgPDQrLD52TYvqazjHJJchM"
     },
     "verification" : {
       "href" : "https://finix.sandbox-payments-api.com/verifications/VIdikDHXv7x8nWyJg8JZemGx"
     }
   }
 }

 **/
