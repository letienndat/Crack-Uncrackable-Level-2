TARGET := iphone:clang:latest:13.0
INSTALL_TARGET_PROCESSES = UnCrackable Level 2
FINALPACKAGE = 1
_IGNORE_WARNINGS = 1

THEOS_PACKAGE_SCHEME = rootless

ifeq ($(THEOS_PACKAGE_SCHEME),rootless)
THEOS_PACKAGE_DIR = rootless
else ifeq ($(THEOS_PACKAGE_SCHEME),roothide)
THEOS_PACKAGE_DIR = roothide
else
THEOS_PACKAGE_DIR = rootful
endif

KITTYMEMORY_PATH = KittyMemory
KITTYMEMORY_SRC = $(wildcard $(KITTYMEMORY_PATH)/*.cpp)
COMMON_SRC = Common.mm
DOBBY_SRC = lib/libdobby.a

include $(THEOS)/makefiles/common.mk

TWEAK_NAME = CrackUncrackableLevel2

$(TWEAK_NAME)_FRAMEWORKS = Foundation UIKit
$(TWEAK_NAME)_FILES = Tweak.xm $(KITTYMEMORY_SRC) $(COMMON_SRC)
$(TWEAK_NAME)_CFLAGS = -fobjc-arc
$(TWEAK_NAME)_CCFLAGS = -std=c++17 -DkITTYMEMORY_DEBUG
$(TWEAK_NAME)_LDFLAGS = $(DOBBY_SRC)

ifeq ($(_IGNORE_WARNINGS), 1)
$(TWEAK_NAME)_CCFLAGS += -w
endif

include $(THEOS_MAKE_PATH)/tweak.mk
