// VersionInfoUpdater - generates updated version data on each build cycle

#include "stdafx.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// this is a captive program used only internally in the build, so the
// data sources are trusted; allow the old-style insecure CRTL functions
#pragma warning(disable:4996)


int main(int argc, char **argv)
{
	// check arguments
	if (argc != 3)
	{
		printf("Usage: VersionInfoUpdater <BuildNumberFile.txt> <BuildInfoFile.h>\n");
		exit(2);
	}
	const char *buildNumberFile = argv[1];
	const char *versionInfoFile = argv[2];

	// read the previous build number
	FILE *fp = fopen(buildNumberFile, "r");
	if (fp == 0)
	{
		printf("Unable to open build number file \"%s\" for reading\n", buildNumberFile);
		exit(2);
	}
	int buildNumber;
	if (fscanf(fp, "%d", &buildNumber) != 1)
	{
		printf("Unable to read build number from \"%s\"\n", buildNumberFile);
		exit(2);
	}
	fclose(fp);

	// update the build number
	buildNumber += 1;

	// write back the new build number
	if ((fp = fopen(buildNumberFile, "w")) == 0)
	{
		printf("Unable to re-open build number file \"%s\" for writing\n", buildNumberFile);
		exit(2);
	}
	fprintf(fp, "%d\n", buildNumber);
	fclose(fp);

	// open the generated file
	if ((fp = fopen(versionInfoFile, "w")) == 0)
	{
		printf("Unable to open version info file \"%s\" for writing\n", versionInfoFile);
		exit(2);
	}

	// get the current date and time
	time_t t;
	time(&t);
	const struct tm *tm = localtime(&t);

	// write the generated data
	fprintf(fp, "// Generated file - do not edit\n"
		"#define VSN_BUILD_NUMBER   %d\n"
		"#define VSN_BUILD_DATE     \"%04d-%02d-%02d:%02d:%02d\"\n"
		"#define VSN_BUILD_YEAR     %d\n"
		"\n",
		buildNumber,
		tm->tm_year + 1900, tm->tm_mon, tm->tm_mday, tm->tm_hour, tm->tm_min,
		tm->tm_year + 1900);
	fclose(fp);

	// success
	exit(0);
}

