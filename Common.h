//
//  Common.h
//  
//
//  Created by Le Tien Dat on 3/4/26.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface Common : NSObject

-(void)setFrameworkName:(const char *)name_;
-(const char *)getFrameworkName;

@end

NS_ASSUME_NONNULL_END
