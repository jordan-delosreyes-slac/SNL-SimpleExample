# Define Firmware Version: v1.0.0.0
export PRJ_VERSION = 0x01000000

# Define release
ifndef RELEASE
export RELEASE = Kcu1500
endif

# Define the Makefile target
target: prom
