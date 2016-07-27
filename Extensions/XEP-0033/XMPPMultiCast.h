//
//  MultiCast.h
//  TrustTextXMPP
//
//  Created by Min Kwon on 3/11/13.
//  Copyright (c) 2013 Min Kwon. All rights reserved.
//
//  This is a quick and dirty implementation of http://xmpp.org/extensions/xep-0033.html
//  This is not a full implementation.  It assumes that the server supports the extension.

#import <Foundation/Foundation.h>
#import "XMPP.h"

@interface XMPPMultiCast : XMPPModule {
}

- (void)sendMessage:(NSString*)msg from:(XMPPJID*)fromJid withId:(NSString*)uuid toServer:(NSString*)serverJid forUsers:(NSArray*)jids;

@end
