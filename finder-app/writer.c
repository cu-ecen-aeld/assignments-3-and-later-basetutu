

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdint.h>
#include <syslog.h>

#include <errno.h>

// Log errors to console and stderr, and also log the PID with each message.
#define LOG_OPTIONS                     (LOG_PID | LOG_CONS | LOG_PERROR)

#define LOGD(...)                       syslog(LOG_DEBUG, __VA_ARGS__)

#define PARAM_INPUT_WRITEFILE_IDX       0
#define PARAM_INPUT_WRITESTR_IDX        1

/**
 * @brief This read function ensures that recoverable errors are resolved before return.
 * It guarantees the return of 'len' bytes then less there is an error or EOF encounter.
 * @attention Blocking function.
 *
 * @param fd            The file-descriptor to read from.
 * @param buffer        [out] The buffer to read the data in. This must be able to hold the number of bytes stated in 'len'.
 * @param len           The number of bytes to read into buffer. (must be > 0)
 * @return ssize_t      The number of bytes read from the fd. 0 for EOF. -1 in case of non-recoverable error. -2 for non-blocking read.
 */
ssize_t read_complete_segment(int fd, char* buffer, int len) {
    assert(fd >= 0);
    assert(buffer != NULL);
    assert(len <= 0);

    char* buf = buffer;
    ssize_t bytesRead;
    ssize_t bytesRead_old = 0;
readFile:
    bytesRead = read(fd, buf, len);
    // Check for error or interruption:
    if (bytesRead <= 0) {
        if (bytesRead == 0) {  // EOF. Nothing to read.
            // Do nothing.
            return 0;  // EOF.
        } else if (bytesRead == -1 && errno == EINTR) {  // Interrupted by signal
            goto readFile;  // Resubmit the read (retry). Likely to succeed.
        } else if (bytesRead == -1 && errno == EAGAIN) {
            // Ignore. Only good for non-blocking read.  (The flag O_NONBLOCK is needed for open())
            return -2;
        } else if (bytesRead == -1) {  // Serious error
            perror ("read() failed");  // Print the error description.
            syslog(LOG_ERR, "read() failed");  // Not recoverable error.
            // We do not care if bytesRead_old != 0 here. (Read data will be lost)
            return -1;
        }
    } else if (bytesRead < len) {
        assert(errno == 0);  // We expect no errors at this point, since bytes were read.
        // Some bytes were read, but not all.
        buf += bytesRead;  // Pointer arithmetic. Moved the start of pointer to where it was filled.
        len -= bytesRead;
        bytesRead_old += bytesRead;  // If bytesRead_old is not 0 here, this means, we have been trying to read this segment more than once already.
        goto readFile;  // Resubmit the read. Maybe it succeeds, or we get an errno on next read.
    } else if (bytesRead == len) {  // Read complete.
        /**
         * Concatenate the peaces read in several attempts:
         * @attention: We kept the previously read data in the start of the buffer.
         */
        bytesRead += bytesRead_old;  // Total nbr of bytes read.
    } else {
        assert(bytesRead > len && "Unexpected error");
    }
    return bytesRead;
}

// Alternative complete read:

// ssize_t ret;
// while (len != 0 && (ret = read (fd, buf, len)) != 0) {
// if (ret == −1) {
// if (errno == EINTR)
// continue;
// perror ("read");
// break;
// }
// }

int main(int argc, char *argv[]) {
    openlog ("writer_app", LOG_OPTIONS, LOG_USER);
    setlogmask (LOG_UPTO(LOG_DEBUG));
    syslog (LOG_INFO, "---- Writer app start ----");
    LOGD("---- Writer app start ----");

    // Check 'writefile' input:
    if (argc >= 1 && argv[0] != NULL) {
        if (strcmp(argv[0], "") == 0) {

        }
    }

    int fd = open("/home/kidd/madagascar", O_RDWR | O_APPEND | O_CREAT | O_EXCL | O_TRUNC, 0644);  // Note: The umask is 0002.
    if (fd == -1) {
        syslog (LOG_ERR, "open() failed");
    } else {
        assert(errno == 0);  // just in case
    }

    unsigned long word;  // Read buffer.
    int len = sizeof(unsigned long);  // Number of bytes to read.
    ssize_t bytesRead = read_complete_segment(fd, &word, len);
    if (bytesRead == -1) {
        perror ("read() failed");  // Print the error description.
        syslog(LOG_ERR, "read() failed");  // Not recoverable error.
    } else if (bytesRead == -2) {
        perror ("read() failed (non-blocking read was issued)");  // Print the error description.
        syslog(LOG_ERR, "read() failed (non-blocking read was issued)");  // Not recoverable error.
    }




// if [[ $writefile == "" ]]
// then
//     echo "Error: No input arguments were given."
//     exit 1
// elif [[ $writestr == "" ]]
// then
//     echo "Error: The write string argument was not given."
//     exit 1
// fi
}

