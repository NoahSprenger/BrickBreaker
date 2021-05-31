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
	box2d

PRODUCTION_LINUX_ICON := sfml

PRODUCTION_LINUX_APP_NAME := SFML Boilerplate Linux
PRODUCTION_LINUX_APP_COMMENT := Boilerplate
