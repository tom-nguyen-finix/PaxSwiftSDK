//
//  FinixAPIResponse+Ext.swift
//  PaxSwiftSDK
//
//  Created by Tom Nguyen on 1/7/25.
//

import Foundation

/**
 Fetch an Identity
 https://developers.finixpayments.com/apis/identities/fetch-an-identity/

 HTTP Request
 GET https://finix.sandbox-payments-api.com/identities/:IDENTITY_ID

 Parameters
 :IDENTITY_ID    ID of the Identity

 Response
 {
 "id" : "IDpYDM7J9n57q849o9E9yNrG",
 "application" : "APgPDQrLD52TYvqazjHJJchM",
 "entity" : {
 "title" : "CEO",
 "first_name" : "dwayne",
 "last_name" : "Sunkhronos",
 "email" : "user@example.org",
 "business_name" : "Petes Coffee",
 "business_type" : "INDIVIDUAL_SOLE_PROPRIETORSHIP",
 "doing_business_as" : "Petes Coffee",
 "phone" : "1234567890",
 "business_phone" : "+1 (408) 756-4497",
 "personal_address" : {
 "line1" : "741 Douglass St",
 "line2" : "Apartment 7",
 "city" : "San Mateo",
 "region" : "CA",
 "postal_code" : "94114",
 "country" : "USA"
 },
 "business_address" : {
 "line1" : "741 Douglass St",
 "line2" : "Apartment 8",
 "city" : "San Mateo",
 "region" : "CA",
 "postal_code" : "94114",
 "country" : "USA"
 },
 "mcc" : "0742",
 "dob" : {
 "day" : 27,
 "month" : 6,
 "year" : 1978
 },
 "max_transaction_amount" : 12000000,
 "amex_mid" : null,
 "discover_mid" : null,
 "url" : "www.PetesCoffee.com",
 "annual_card_volume" : 12000000,
 "has_accepted_credit_cards_previously" : true,
 "incorporation_date" : {
 "day" : 27,
 "month" : 6,
 "year" : 1978
 },
 "principal_percentage_ownership" : 50,
 "short_business_name" : null,
 "ownership_type" : "PRIVATE",
 "tax_authority" : null,
 "tax_id_provided" : true,
 "business_tax_id_provided" : true,
 "default_statement_descriptor" : "Petes Coffee"
 },
 "tags" : {
 "Studio Rating" : "4.7"
 },
 "created_at" : "2022-01-27T07:36:52.11Z",
 "updated_at" : "2022-01-27T07:36:52.00Z",
 "additional_underwriting_data" : {
 "annual_ach_volume" : 200000,
 "average_ach_transfer_amount" : 200000,
 "average_card_transfer_amount" : 200000,
 "business_description" : "SB3 vegan cafe",
 "card_volume_distribution" : {
 "card_present_percentage" : 30,
 "ecommerce_percentage" : 60,
 "mail_order_telephone_order_percentage" : 10
 },
 "credit_check_allowed" : true,
 "credit_check_ip_address" : "42.1.1.113",
 "credit_check_timestamp" : "2021-04-28T16:42:55Z",
 "credit_check_user_agent" : "Mozilla 5.0(Macintosh; IntelMac OS X 10 _14_6)",
 "merchant_agreement_accepted" : true,
 "merchant_agreement_ip_address" : "42.1.1.113",
 "merchant_agreement_timestamp" : "2021-04-28T16:42:55Z",
 "merchant_agreement_user_agent" : "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_6)",
 "refund_policy" : "MERCHANDISE_EXCHANGE_ONLY",
 "volume_distribution_by_business_type" : {
 "business_to_business_volume_percentage" : 100,
 "business_to_consumer_volume_percentage" : 0,
 "consumer_to_consumer_volume_percentage" : 0,
 "other_volume_percentage" : 0,
 "person_to_person_volume_percentage" : 0
 }
 },
 "_links" : {
 "self" : {
 "href" : "https://finix.sandbox-payments-api.com/identities/IDpYDM7J9n57q849o9E9yNrG"
 },
 "verifications" : {
 "href" : "https://finix.sandbox-payments-api.com/identities/IDpYDM7J9n57q849o9E9yNrG/verifications"
 },
 "merchants" : {
 "href" : "https://finix.sandbox-payments-api.com/identities/IDpYDM7J9n57q849o9E9yNrG/merchants"
 },
 "settlements" : {
 "href" : "https://finix.sandbox-payments-api.com/identities/IDpYDM7J9n57q849o9E9yNrG/settlements"
 },
 "authorizations" : {
 "href" : "https://finix.sandbox-payments-api.com/identities/IDpYDM7J9n57q849o9E9yNrG/authorizations"
 },
 "transfers" : {
 "href" : "https://finix.sandbox-payments-api.com/identities/IDpYDM7J9n57q849o9E9yNrG/transfers"
 },
 "payment_instruments" : {
 "href" : "https://finix.sandbox-payments-api.com/identities/IDpYDM7J9n57q849o9E9yNrG/payment_instruments"
 },
 "associated_identities" : {
 "href" : "https://finix.sandbox-payments-api.com/identities/IDpYDM7J9n57q849o9E9yNrG/associated_identities"
 },
 "disputes" : {
 "href" : "https://finix.sandbox-payments-api.com/identities/IDpYDM7J9n57q849o9E9yNrG/disputes"
 },
 "application" : {
 "href" : "https://finix.sandbox-payments-api.com/applications/APgPDQrLD52TYvqazjHJJchM"
 }
 }
 }
 */

extension FinixAPIResponse {
    typealias IdentityId = String

    struct Identity: Decodable {
        let id: IdentityId
        let application: String
        let entity: Entity
//        let tags: ResourceTags?
//        let created: Date
//        let udpated: Date

        private enum CodingKeys: String, CodingKey {
            case id
            case application
            case entity
//            case tags
//            case created = "created_at"
//            case updated = "updated_at"
        }
    }

    struct Entity: Decodable {
        let title: String
        let firstName: String
        let lastName: String
        let email: String
        let businessName: String
        let businessType: String
        let doingBusinessAs: String
        let phone: String
        let businesPhone: String
        let personalAddress: Address
        let businessAddress: Address
        let mcc: String

        enum CodingKeys: String, CodingKey {
            case title
            case firstName = "first_name"
            case lastName = "last_name"
            case email
            case businessName = "business_name"
            case businessType = "business_type"
            case doingBusinessAs = "doing_business_as"
            case phone
            case businesPhone = "business_phone"
            case personalAddress = "personal_address"
            case businessAddress = "business_address"
            case mcc
        }
    }

    struct Address: Decodable {
        let line1: String
        let line2: String?
        let city: String
        let region: String
        let postalCode: String
        let country: String

        var display: String {
            "\(line1) \(line2 ?? "")\(city) \(region) \(postalCode)"
        }

        enum CodingKeys: String, CodingKey {
            case line1
            case line2
            case city
            case region
            case postalCode = "postal_code"
            case country
        }
    }
}
