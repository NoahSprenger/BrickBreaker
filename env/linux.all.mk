CC := g++
CFLAGS := $(CFLAGS) -fpic

LIB_DIRS := \
	/usr/local/lib

INCLUDE_DIRS := \
	/usr/local/include

BUILD_FLAGS := \
	$(BUILD_FLAGS) \
	-pthread

LINK_LIBRARIES := \
	$(LINK_LIBRARIES) \
	stdc++fs \
	X11 \
	box2d \
	imsfml \
	GL

PRODUCTION_LINUX_ICON := logo

PRODUCTION_LINUX_APP_NAME := Brick Breaker
PRODUCTION_LINUX_APP_COMMENT := Brick Breaker game made for Gr12 Comp Sci class
