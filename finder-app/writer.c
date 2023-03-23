
#include <syslog.h>

// Log errors to console and stderr, and also log the PID with each message.
#define LOG_OPTIONS                     (LOG_PID | LOG_CONS | LOG_PERROR)

int main(int argc, char *argv[]) {
    openlog ("writer_app", LOG_OPTIONS, LOG_USER);
    setlogmask (LOG_UPTO(LOG_DEBUG));
    syslog (LOG_INFO, "---- Writer app start ----");

}

