#import "Macros.h"

#define NAME_BINARY "UnCrackable Level 2"

void setup();
void patch();
void appendLog(const char *log);

void setup() {
    [common setFrameworkName:NAME_BINARY];
    appendLog("Tweak loaded");

    // PATCH OFFSETS
    patch();
}

void patch() {
    appendLog("========= Start patching =========");

    // Patch isJailbreak always is 0 (false)
    patchOffset(0x1000056c8, "08 00 80 52");
    patchOffset(0x1000056ec, "16 00 80 52");
    patchOffset(0x1000057c4, "08 00 80 52");

    appendLog("========= Patch done =========");
}

void appendLog(const char *log) {
    NSLog(@"%s: %s", NAME_BINARY, log);
}

__attribute__((constructor)) static void initalize() {
    timer(1) {
        setup();
    });
}