//
//  Macros.h
//  ModMenu
//
//  Created by Joey on 4/2/19.
//  Copyright © 2019 Joey. All rights reserved.
//

#import "Obfuscate.h"
#import "Foundation/Foundation.h"
#import "Common.h"
#import "KittyMemory/MemoryPatch.hpp"
#import "KittyMemory/writeData.hpp"

#include <substrate.h>
#include <mach-o/dyld.h>

extern Common *common;

// thanks to shmoo for the usefull stuff under this comment.
#define timer(sec) dispatch_after(dispatch_time(DISPATCH_TIME_NOW, sec * NSEC_PER_SEC), dispatch_get_main_queue(), ^
#define onMain(block) dispatch_async(dispatch_get_main_queue(), block)
#define HOOK(offset, ptr, orig) MSHookFunction((void *)getRealOffset(offset), (void *)ptr, (void **)&orig)
#define HOOK_NO_ORIG(offset, ptr) MSHookFunction((void *)getRealOffset(offset), (void *)ptr, NULL)

// Note to not prepend an underscore to the symbol. See Notes on the Apple manpage (https://developer.apple.com/library/archive/documentation/System/Conceptual/ManPages_iPhoneOS/man3/dlsym.3.html)
#define HOOKSYM(sym, ptr, org) MSHookFunction((void*)dlsym((void *)RTLD_DEFAULT, sym), (void *)ptr, (void **)&org)
#define HOOKSYM_NO_ORIG(sym, ptr)  MSHookFunction((void*)dlsym((void *)RTLD_DEFAULT, sym), (void *)ptr, NULL)
#define getSym(symName) dlsym((void *)RTLD_DEFAULT, symName)

uint64_t getRealOffset(uint64_t offset){
	return KittyMemory::getAbsoluteAddress([common getFrameworkName], offset);
}

// Patching a offset without switch.
void patchOffset(uint64_t offset, std::string hexBytes) {
	MemoryPatch patch = MemoryPatch::createWithHex([common getFrameworkName], offset, hexBytes);
	if(!patch.isValid()){
		NSLog(@"Invalid patch, failing offset: 0x%llX, please re-check the hex you entered.", offset);
		return;
	}
	if(!patch.Modify()) {
	  NSLog(@"Something went wrong while patching this offset: 0x%llX", offset);
    }
}
