#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define STARDATE_ORIGIN  10997827200
#define STARDATE_SECONDS 34367.0564

static char *months[12] = {
	"January", "February", "March", "April", "May", "June",
	"July", "August", "September", "October", "November", "December"
};

static void time2stardate(time_t time, double *stardate) {
	*stardate = ((double)time - STARDATE_ORIGIN) / STARDATE_SECONDS;
}

static void calendar2stardate(char *calendar, double *stardate) {
	int mon = 0, mday = 0, year = 0, hour = 0, min = 0, sec = 0, i = 0, l = 0;
	char *month = NULL;
	struct tm tm = {
		.tm_year = 0,
		.tm_mon = 0,
		.tm_mday = 0,
		.tm_hour = 0,
		.tm_min = 0,
		.tm_sec = 0
	};

	month = malloc(sizeof(char) * 10);
	(void)sscanf(calendar, "%s %d, %d %d:%d:%d", month, &mday, &year, &hour, &min, &sec);

	for (i = 0, l = 12; i < l; i += 1) {
		if (strcmp(month, months[i]) == 0) {
			mon = i;
		}
	}

	tm.tm_year = year - 1900;
	tm.tm_mon = mon;
	tm.tm_mday = mday;
	tm.tm_hour = hour;
	tm.tm_min = min;
	tm.tm_sec = sec;

	time2stardate(mktime(&tm), stardate);

	if (month) {
		free(month);
	}
}

static void stardate2calendar(double stardate, char **calendar) {
	int mon = 0, mday = 0, year = 0, hour = 0, min = 0, sec = 0;
	size_t size = 28;
	time_t time = 0;
	struct tm *tm = NULL;

	time = (time_t)floor(stardate * STARDATE_SECONDS);
	time += STARDATE_ORIGIN;

	tm = localtime(&time);

	year = tm->tm_year + 1900;
	mon = tm->tm_mon;
	mday = tm->tm_mday;
	hour = tm->tm_hour;
	min = tm->tm_min;
	sec = tm->tm_sec;

	*calendar = malloc(sizeof(char) * size);
	(void)snprintf(*calendar, size, "%s %d, %d %s%d%s%d%s%d", months[mon], mday, year, hour < 10 ? "0" : "", hour, min < 10 ? ":0" : ":", min, sec < 10 ? ":0" : ":", sec);
}

static void usage(char *exec) {
	printf("Usage: %s [-c,--calendar \"<date>\"]\n", exec);
	printf("%*s [-s,--stardate <stardate>]\n", (int)strlen(exec) + 7, " ");
}

int main(int argc, char *argv[]) {
	int rc = 0;
	double stardate = 0.0;
	char *action = NULL, *calendar = NULL;

	if (argc > 1) {
		action = argv[1];

		if (strcmp(action, "-h") == 0 || strcmp(action, "--help") == 0) {
			usage(argv[0]);

			rc = 1;
			goto cleanup;
		}

		if (argc > 2) {
			if (strcmp(action, "-s") == 0 || strcmp(action, "--stardate") == 0) {
				stardate = atof(argv[2]);

				stardate2calendar(stardate, &calendar);
				printf("%s\n", calendar);
			} else if (strcmp(action, "-c") == 0 || strcmp(action, "--calendar") == 0) {
				calendar = malloc(sizeof(char) * strlen(argv[2]) + 1);
				strcpy(calendar, argv[2]);

				calendar2stardate(calendar, &stardate);
				printf("%.2f\n", stardate);
			} else {
				printf("Unknown action %s\n", action);

				rc = 1;
				goto cleanup;
			}
		} else {
			printf("Unknown action %s\n", action);

			rc = 1;
			goto cleanup;
		}
	} else {
		time2stardate(time(0), &stardate);
		printf("%.2f\n", stardate);
	}

cleanup:
	if (calendar) {
		free(calendar);
	}

	return rc;
}