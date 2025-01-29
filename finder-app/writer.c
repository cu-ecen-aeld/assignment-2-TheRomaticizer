#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
#include <string.h>

int main(int argc, char *argv[]) {
    openlog("writer", LOG_PID | LOG_CONS, LOG_USER);

    if (argc != 3) {
        syslog(LOG_ERR, "Invalid number of arguments. Usage: %s <file_path> <text_string>", argv[0]);
        return 1;
    }

    const char *file_path = argv[1];
    const char *text_string = argv[2];

    FILE *file = fopen(file_path, "w");
    if (!file) {
        syslog(LOG_ERR, "Error opening file: %s", file_path);
        return 1;
    }

    if (fprintf(file, "%s", text_string) < 0) {
        syslog(LOG_ERR, "Error writing to file: %s", file_path);
        fclose(file);
        return 1;
    }

    syslog(LOG_DEBUG, "Successfully wrote '%s' to '%s'", text_string, file_path);

    fclose(file);
    closelog();
    return 0;
}
