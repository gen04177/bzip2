# bzip2

This payload is a tool to compress and encrypt files and decompress and decrypt them. The tool is developed in C and is designed to run on a PS5 with Jailbreak (3.xx-4.xx).

## Prerequisites

- elfldr.elf
- shsrv.elf
- ftpsrv.elf

## How to Use

1 - Send the elfldr.elf payload to port 9020.
2 - Send the shsrv.elf payload to port 9021.
3 - Send the ftpsrv.elf payload to port 9021.
4 - Copy the bz2.elf payload to the /data directory on your PS5.
5 - Execute telnet [PS5-IP] 2323.
6 - `cd /data`
7 - Run the command `hbldr bz2.elf --help` FMI.

## Compress and Encrypt a File:

`hbldr bz2.elf -c <input_file> <output_file> -p <password>`

e.g.:

`hbldr bz2.elf -c /data/file.ex /data/file.ex.bz2 -p 123456`

## Decrypt and Decompress a File:

`hbldr bz2.elf -d <input_file> <output_file> -p <password>`

e.g.:

`hbldr bz2.elf -d /data/file.ex.bz2 /data/file.ex.2 -p 123456`

## Known Limitations

- Ensure the same password is used for both encryption and decryption.
- Incorrect password during decryption will result in an error message and the output file will be deleted.
- The password must be 128 characters or less.

## Credits
Credits to J. Tornblom for the SDK and required payloads.
