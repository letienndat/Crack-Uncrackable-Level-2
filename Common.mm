//
//  Common.mm
//  
//
//  Created by Le Tien Dat on 3/4/26.
//

#include "Common.h"

NS_ASSUME_NONNULL_BEGIN

@implementation Common

const char *frameworkName = NULL;
Common *common = [Common new];

-(void)setFrameworkName:(const char *)name_ {
    frameworkName = name_;
}
-(const char *)getFrameworkName {
    return frameworkName;
}

@end

NS_ASSUME_NONNULL_END
