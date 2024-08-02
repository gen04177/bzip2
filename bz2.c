#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <bzlib.h>

#define BUFFER_SIZE 4096

void compress_file(const char *input_filename, const char *output_filename) {
    printf("\n\nCompressing '%s' to '%s'\n", input_filename, output_filename);
    FILE *input_file = fopen(input_filename, "rb");
    if (!input_file) {
        perror("Failed to open input file");
        exit(EXIT_FAILURE);
    }

    FILE *output_file = fopen(output_filename, "wb");
    if (!output_file) {
        perror("Failed to open output file");
        fclose(input_file);
        exit(EXIT_FAILURE);
    }

    BZFILE *bz2_file;
    int bz_error;
    bz2_file = BZ2_bzWriteOpen(&bz_error, output_file, 9, 0, 30);
    if (bz_error != BZ_OK) {
        fprintf(stderr, "Failed to initialize BZ2_bzWriteOpen: %d\n", bz_error);
        fclose(input_file);
        fclose(output_file);
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    int n_read;
    while ((n_read = fread(buffer, 1, BUFFER_SIZE, input_file)) > 0) {
        BZ2_bzWrite(&bz_error, bz2_file, buffer, n_read);
        if (bz_error != BZ_OK) {
            fprintf(stderr, "BZ2_bzWrite error: %d\n", bz_error);
            BZ2_bzWriteClose(&bz_error, bz2_file, 0, NULL, NULL);
            fclose(input_file);
            fclose(output_file);
            exit(EXIT_FAILURE);
        }
    }

    BZ2_bzWriteClose(&bz_error, bz2_file, 0, NULL, NULL);
    fclose(input_file);
    fclose(output_file);

    if (bz_error != BZ_OK) {
        fprintf(stderr, "Failed to close BZ2_bzWriteClose: %d\n", bz_error);
        exit(EXIT_FAILURE);
    }
}

void decompress_file(const char *input_filename, const char *output_filename) {
    printf("\n\nDecompressing '%s' to '%s'\n", input_filename, output_filename);
    FILE *input_file = fopen(input_filename, "rb");
    if (!input_file) {
        perror("Failed to open input file");
        exit(EXIT_FAILURE);
    }

    FILE *output_file = fopen(output_filename, "wb");
    if (!output_file) {
        perror("Failed to open output file");
        fclose(input_file);
        exit(EXIT_FAILURE);
    }

    BZFILE *bz2_file;
    int bz_error;
    bz2_file = BZ2_bzReadOpen(&bz_error, input_file, 0, 0, NULL, 0);
    if (bz_error != BZ_OK) {
        fprintf(stderr, "Failed to initialize BZ2_bzReadOpen: %d\n", bz_error);
        fclose(input_file);
        fclose(output_file);
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    int n_read;
    while ((n_read = BZ2_bzRead(&bz_error, bz2_file, buffer, BUFFER_SIZE)) > 0) {
        if (bz_error != BZ_OK && bz_error != BZ_STREAM_END) {
            fprintf(stderr, "BZ2_bzRead error: %d\n", bz_error);
            BZ2_bzReadClose(&bz_error, bz2_file);
            fclose(input_file);
            fclose(output_file);
            exit(EXIT_FAILURE);
        }
        fwrite(buffer, 1, n_read, output_file);
    }

    BZ2_bzReadClose(&bz_error, bz2_file);
    fclose(input_file);
    fclose(output_file);

    if (bz_error != BZ_OK && bz_error != BZ_STREAM_END) {
        fprintf(stderr, "Failed to close BZ2_bzReadClose: %d\n", bz_error);
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "\n\nUsage: %s -c|-d <input_file> <output_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "-c") == 0) {
        compress_file(argv[2], argv[3]);
        printf("File '%s' successfully compressed to '%s'\n", argv[2], argv[3]);
    } else if (strcmp(argv[1], "-d") == 0) {
        decompress_file(argv[2], argv[3]);
        printf("File '%s' successfully decompressed to '%s'\n", argv[2], argv[3]);
    } else {
        fprintf(stderr, "Unknown option: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
