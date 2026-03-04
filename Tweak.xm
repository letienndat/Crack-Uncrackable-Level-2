#import "Macros.h"

#define NAME_BINARY "UnCrackable Level 2"

void setup();
void patch();
void appendLog(const char *log);

void setup() {
    [common setFrameworkName:NAME_BINARY];
    appendLog("Tweak loaded");

    // PATCH
    patch();
}

void patch() {
    appendLog("Start patching");

    // Patch check showJailbreakAlert
    patchOffset(0x100005958, "1F 01 00 71");

    appendLog("Patch done");
}

void appendLog(const char *log) {
    NSLog(@"%s: %s", NAME_BINARY, log);
}

__attribute__((constructor)) static void initalize() {
    timer(1) {
        setup();
    });
}