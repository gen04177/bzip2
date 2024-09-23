# bzip2

This payload is a tool to compress and encrypt files and decompress and decrypt them. The tool is developed in C and is designed to run on a jailbroken PS5 (1.xx-4.xx).

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

- The password must be 512 characters or less.
- The special character `&` is not accepted in the password.

## Credits
- J. Tornblom - SDK and required payloads.
