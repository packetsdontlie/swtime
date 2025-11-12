#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <ctype.h>
#include <unistd.h>  /* for isatty() */

void print_help(void) {
    printf("Usage: swtime [epoch | beats | flags]\n");
    printf("  --help, -?         Show this help message\n");
    printf("  --beats-only       Output beats without '@' prefix\n");
    printf("  --rfc              Convert beats (from stdin) to RFC 2822 date\n");
    printf("  [epoch]            Convert epoch to Swatch .beats\n");
    printf("  [stdin]            Pipe date or beats into swtime\n");
}

int beats_from_epoch(time_t t) {
    return (int)(((t + 3600) % 86400) / 86.4);
}

time_t epoch_from_beats(int beats) {
    time_t base;
    base = time(NULL) / 86400 * 86400;
    return base + (time_t)(beats * 86.4) - 3600;
}

void print_rfc(time_t t) {
    char buffer[128];
    struct tm *tm_info;
    tm_info = localtime(&t);
    strftime(buffer, sizeof(buffer), "%a, %d %b %Y %H:%M:%S %Z", tm_info);
    printf("%s\n", buffer);
}

int main(int argc, char *argv[]) {
    int beats_only = 0;
    int rfc_mode = 0;
    int i;
    char input[128];
    time_t t;
    int beats;

    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-?") == 0) {
            print_help();
            return 0;
        }
        if (strcmp(argv[i], "--beats-only") == 0) {
            beats_only = 1;
        }
        if (strcmp(argv[i], "--rfc") == 0) {
            rfc_mode = 1;
        }
    }

    if (rfc_mode) {
        if (fgets(input, sizeof(input), stdin)) {
            beats = atoi(input);
            t = epoch_from_beats(beats);
            print_rfc(t);
            return 0;
        } else {
            fprintf(stderr, "No beats input received.\n");
            return 1;
        }
    }

    if (argc == 2 && isdigit(argv[1][0])) {
        t = atol(argv[1]);
        beats = beats_from_epoch(t);
        if (beats_only) {
            printf("%03d\n", beats);
        } else {
            printf("@%03d\n", beats);
        }
        return 0;
    }

    if (!isatty(fileno(stdin))) {
        if (fgets(input, sizeof(input), stdin)) {
            if (isdigit(input[0])) {
                beats = atoi(input);
                t = epoch_from_beats(beats);
                printf("%ld\n", (long)t);
            } else {
                t = time(NULL);
                beats = beats_from_epoch(t);
                if (beats_only) {
                    printf("%03d\n", beats);
                } else {
                    printf("@%03d\n", beats);
                }
            }
            return 0;
        }
    }

    t = time(NULL);
    beats = beats_from_epoch(t);
    if (beats_only) {
        printf("%03d\n", beats);
    } else {
        printf("@%03d\n", beats);
    }

    return 0;
}
