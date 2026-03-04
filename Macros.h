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
#import "KittyMemory/KittyUtils.hpp"
#import "lib/dobby.h"

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

// Patching offset with KittyMemory
void patchOffsetKitty(uint64_t offset, std::string hexBytes) {
	MemoryPatch patch = MemoryPatch::createWithHex([common getFrameworkName], offset, hexBytes);
	if(!patch.isValid()){
		NSLog(@"Invalid patch, failing offset: 0x%llX, please re-check the hex you entered.", offset);
		return;
	}
	if(!patch.Modify()) {
	  NSLog(@"Something went wrong while patching this offset: 0x%llX", offset);
    }
}

// Patching offset with Dobby
void patchOffsetDobby(uint64_t offset, std::string hexBytes) {
  uint64_t realOffset = getRealOffset(offset);

  if (!KittyUtils::String::ValidateHex(hexBytes)) {
	NSLog(@"Invalid hex string: %s, please re-check the hex you entered.", hexBytes.c_str());
	return;
  }

  int size = hexBytes.length() / 2;
  std::vector<uint8_t> patch_code;
  patch_code.resize(size);
  KittyUtils::dataFromHex(hexBytes, &patch_code[0]);

  void *address = (void *)realOffset;
  uint32_t before = 0;
  memcpy(&before, address, 4);
  NSLog(@"Verify before 0x%llX = 0x%08X", (unsigned long long)address, before);

  int status = DobbyCodePatch(address, patch_code.data(), size);
  NSLog(@"Patching address: 0x%llX for offset: 0x%llX with hex bytes: %s, status: %d", realOffset, offset, hexBytes.c_str(), status);

  uint32_t after = 0;
  memcpy(&after, address, 4);
  NSLog(@"Verify after 0x%llX = 0x%08X", (unsigned long long)address, after);

  if (status == -1) {
	NSLog(@"Something went wrong while patching address: 0x%llX for offset: 0x%llX with hex bytes: %s", realOffset, offset, hexBytes.c_str());
  }
}