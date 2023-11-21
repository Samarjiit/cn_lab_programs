#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main() {
    FILE *source_file, *destination_file;
    char buffer[BUFFER_SIZE];
    size_t bytes_read, bytes_written;

    // Open the source file in read mode
    source_file = fopen("source.txt", "rb");
    if (source_file == NULL) {
        perror("Error opening source file");
        return 1;
    }

    // Open the destination file in write mode (creates if it doesn't exist)
    destination_file = fopen("destination.txt", "wb");
    if (destination_file == NULL) {
        perror("Error opening destination file");
        fclose(source_file);
        return 1;
    }

    // Copy data from source file to destination file
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), source_file)) > 0) {
        bytes_written = fwrite(buffer, 1, bytes_read, destination_file);
        if (bytes_written != bytes_read) {
            perror("Error writing to destination file");
            fclose(source_file);
            fclose(destination_file);
            return 1;
        }
    }

    // Close the files
    fclose(source_file);
    fclose(destination_file);

    printf("File copied successfully!\n");
    return 0;
}
