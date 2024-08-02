ifdef PS5_PAYLOAD_SDK
    include $(PS5_PAYLOAD_SDK)/toolchain/prospero.mk
else
    $(error PS5_PAYLOAD_SDK is undefined)
endif

CFLAGS := -O3
LDADD  := -lbz2

CFLAGS += $(shell $(PS5_PAYLOAD_SDK)/target/bin/sdl2-config --cflags)
LDADD  += $(shell $(PS5_PAYLOAD_SDK)/target/bin/sdl2-config --libs)

SRCS := bz2.c

ELF := bz2.elf

all: $(ELF)

$(ELF): $(SRCS)
	$(CC)  -o $@ $^ $(CFLAGS) $(LDADD)

clean:
	rm -f $(ELF)
