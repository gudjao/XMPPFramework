//
//  OMEMOModule.h
//  XMPPFramework
//
//  Created by Chris Ballinger on 4/21/16.
//
//

#import <Foundation/Foundation.h>
#import "XMPP.h"

#define XMLNS_OMEMO @"urn:xmpp:omemo:0"
#define XMLNS_OMEMO_DEVICELIST @"urn:xmpp:omemo:0:devicelist"
#define XMLNS_OMEMO_BUNDLES @"urn:xmpp:omemo:0:bundles"

NS_ASSUME_NONNULL_BEGIN
/**
 *  XEP-xxxx OMEMO Encryption
 *  https://conversations.im/xeps/multi-end.html
 *
 *  This specification defines a protocol for end-to-end encryption in one-on-one chats that may have multiple clients per account.
 */
@interface OMEMOModule : XMPPModule <XMPPStreamDelegate>

/** 
 * In order for other devices to be able to initiate a session with a given device, it first has to announce itself by adding its device ID to the devicelist PEP node.
 *
 * Devices MUST check that their own device ID is contained in the list whenever they receive a PEP update from their own account. If they have been removed, they MUST reannounce themselves.
 * 
 * The Device ID is a randomly generated integer between 1 and 2^31 - 1 wrapped in an NSNumber.
 */
- (void) publishDeviceIds:(NSArray<NSNumber*>*)deviceIds;


/**
 * A device MUST announce it's IdentityKey, a signed PreKey, and a list of PreKeys in a separate, per-device PEP node. The list SHOULD contain 100 PreKeys, but MUST contain no less than 20.
 * 
 * @param device is this device's deviceId
 * @param identityKey base64 encoded public key
 * @param signedPreKey base64 encoded signed public prekey
 * @param signedPreKeyId identifier for signedPreKey
 * @param signedPreKeySignature signature of signedPreKey, signed by identityKey
 * @param preKeys base64 preKey values keyed to unique integer preKeyIds
 */
- (void) publishBundleForDevice:(NSNumber*)deviceId
                    identityKey:(NSString*)identityKey
                   signedPreKey:(NSString*)signedPreKey
                 signedPreKeyId:(NSNumber*)signedPreKeyId
          signedPreKeySignature:(NSString*)signedPreKeySignature
                        preKeys:(NSDictionary<NSNumber*,NSString*>*)preKeys;

/**
 *  Fetches device bundle for a remote JID.
 */
- (void) fetchBundleForDevice:(NSNumber*)deviceId
                          jid:(XMPPJID*)jid;

/**
 In order to send a chat message, its <body> first has to be encrypted. The client MUST use fresh, randomly generated key/IV pairs with AES-128 in Galois/Counter Mode (GCM). For each intended recipient device, i.e. both own devices as well as devices associated with the contact, this key is encrypted using the corresponding long-standing axolotl session. Each encrypted payload key is tagged with the recipient device's ID. This is all serialized into a MessageElement.
 */
- (void) sendPayload:(NSString*)payload
               toJID:(XMPPJID*)jid
           elementID:(NSString*)eid
            deviceId:(NSNumber*)deviceId
  receivingDeviceIds:(NSDictionary<NSNumber*,NSString*>*)receivingDeviceIds
                  iv:(NSString*)iv;

@end

@protocol OMEMODelegate <NSObject>

/**
 * In order to determine whether a given contact has devices that support OMEMO, the devicelist node in PEP is consulted. Devices MUST subscribe to 'urn:xmpp:omemo:0:devicelist' via PEP, so that they are informed whenever their contacts add a new device. They MUST cache the most up-to-date version of the devicelist.
 */
- (void)omemo:(OMEMOModule*)omemo deviceListUpdate:(NSArray<NSNumber*>*)deviceIds fromJID:(XMPPJID*)fromJID message:(XMPPMessage*)message;

@end
NS_ASSUME_NONNULL_END