//
//  ISyncAndProcessListener.h
//  PaxEasyLinkController
//
//  Created by Joline Yang on 8/31/22.
//  Copyright © 2022 jobten. All rights reserved.
//

#import <Foundation/Foundation.h>

/*!
@abstract ISyncAndProcessListener
 */
@protocol ISyncAndProcessListener <NSObject>
/*!
 @abstract  display message
 @param     message
 */
-(void)onDisplayStatus:(NSString *)message;
/*!
 @abstract  install status
 @param current current size that already be processed
 @param total total size
 */
-(void)onInstallStatus:(NSInteger)current total:(NSInteger)total;
/*!
 @abstract  if listener has been aborted
 @return listener status.
 <p> true: abort
 <p> false: not abort
 */
-(BOOL)abort;
/*!
 @abstract  download status
 @param downloadedLength current size that already be processed
 @param totalLength total size
 */
-(void)onDownloadStatus:(NSInteger) downloadedLength totalLength:(NSInteger) totalLength;

@end

