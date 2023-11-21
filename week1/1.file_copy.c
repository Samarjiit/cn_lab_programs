#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

int main() {
    int fdread, fdwrite;
    char buffer[1024];
    ssize_t count, bytes_written; //ssize_t Used for a count of bytes

    // Open the source file in read-only mode
    fdread = open("source.txt", O_RDONLY);
    if (fdread == -1) {
        printf("Error opening source file");
        return 1;
    }

    // Open the destination file in write-only mode, creates if it doesn't exist
    fdwrite = open("destination.txt", O_WRONLY | O_CREAT, S_IRWXU );
    if (fdwrite == -1) {
        printf("Error opening destination file");
        close(fdwrite);
        return 1;
    }

    // Copy data from source file to destination file
    while (count > 0) {
        count = read(fdread, buffer, sizeof(buffer));
        bytes_written = write(fdwrite, buffer, count);
        if (bytes_written != count) {
            printf("Error writing to destination file");
            close(fdread);
            close(fdwrite);
            return 1;
        }
    }
    close(fdread);
    close(fdwrite);
    printf("File copied successfully!\n");
    return 0;
}
