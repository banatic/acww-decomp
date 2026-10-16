/* The build's label: the 32 bytes of the file "/BUILDTIME", read once at start-up into
 * data_021c5914 (the debug screen shows it). */
#ifndef CLEAN_MAIN_BUILD_TIME_H
#define CLEAN_MAIN_BUILD_TIME_H

#define BUILD_TIME_SIZE 0x20

void BuildTime_Load(void);

#endif
