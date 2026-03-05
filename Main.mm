#import "Macros.h"
#import <UIKit/UIKit.h>

#define NAME_BINARY "UnCrackable Level 2"

void patch();

static void didFinishLaunching(CFNotificationCenterRef center, void *observer,
                               CFStringRef name, const void *object,
                               CFDictionaryRef userInfo) {
  timer(1) {
    // UIAlertController *alert = [UIAlertController
    //     alertControllerWithTitle:NSSENCRYPT("Success")
    //                      message:NSSENCRYPT("Tweak Loaded!")
    //               preferredStyle:UIAlertControllerStyleAlert];
    // [alert addAction:[UIAlertAction
    //                      actionWithTitle:NSSENCRYPT("OK")
    //                                style:UIAlertActionStyleDefault
    //                              handler:^(UIAlertAction *__unused action) {
    //                                setup();
    //                              }]];

    // UIViewController *topVC = [common getTopViewController];
    // [topVC presentViewController:alert
    //                     animated:YES
    //                   completion:^{
    //                     LOG(@"Tweak loaded!");
    //                   }];

    LOG(@"Tweak loaded!");
    setup();
  });
}

void setup() {
  [common setFrameworkName:NAME_BINARY];

  // PATCH OFFSETS
  patch();
}

void patch() {
  LOG(@"========= Start patching =========");

  // Patch isJailbreak always is 0 (false)
  patchOffset(0x1000056c8, "08 00 80 52");
  patchOffset(0x1000056ec, "16 00 80 52");
  patchOffset(0x1000057c4, "08 00 80 52");

  LOG(@"========= Patch done =========");
}

__attribute__((constructor)) static void initalize() {
  CFNotificationCenterAddObserver(
      CFNotificationCenterGetLocalCenter(), NULL, &didFinishLaunching,
      (CFStringRef)UIApplicationDidFinishLaunchingNotification, NULL,
      CFNotificationSuspensionBehaviorDeliverImmediately);
}