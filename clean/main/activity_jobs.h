/* The jobs 6 to 0x13 of the activity process (activity.h, activity_job.h). Each job is two
 * functions in the table at data_021f3ea4: a start, called once when func_020a4e94 starts the
 * job, and a step, called once a frame while it runs. A step ends its job by starting another
 * one (job 0 for none).
 *
 *   job 6     a town player removed (the record data_021f3c34 the title's menu chose): the
 *             removal said in talk 0, then the card checked and written (both copies and the
 *             letters); then job 0xc;
 *   job 7     message 39 of "sp_etc_sequence3", then the card checked and both copies written;
 *             then job 0xf;
 *   job 8     once talk 0 is closed, the entry record's exit 1 taken;
 *   job 9     ... the scene 13 entered at the point data_020d1bfc;
 *   job 0xa   ... the scene 14 entered at the point data_020d1c14;
 *   job 0xb   ... the scene 0x2f entered;
 *   job 0xc   ... the save loaded and the state block started from it (or anew), then the
 *             scene 0x2c entered;
 *   job 0xd   ... func_020a53ec told (2, 3, 0, 0);
 *   job 0xe   ... with data_021c75b8 2, the start kind chosen and applied (start_kind.h), then
 *             the scene 0x2d entered;
 *   job 0xf   ... with data_021c75b8 2, the scene 0 entered in front of the town's building
 *             0x5000;
 *   job 0x10  ... the entry record's exit 2 taken in scene 6, exit 0 elsewhere;
 *   job 0x11  ... the entry record's exit 2 taken;
 *   job 0x12  the card checked, then the written copy and the letters written;
 *   job 0x13  the same, after the current player's flag 2 is cleared. */
#ifndef CLEAN_MAIN_ACTIVITY_JOBS_H
#define CLEAN_MAIN_ACTIVITY_JOBS_H

#include "activity.h"
#include "types.h"

void ActivityJobs_Start06(Activity *activity);
void ActivityJobs_Step06(Activity *activity);
void ActivityJobs_Start07(Activity *activity);
void ActivityJobs_Step07(Activity *activity);
void ActivityJobs_Start08(void);
void ActivityJobs_Step08(Activity *activity);
void ActivityJobs_Start09(void);
void ActivityJobs_Step09(Activity *activity);
void ActivityJobs_Start0A(void);
void ActivityJobs_Step0A(Activity *activity);
void ActivityJobs_Start0B(void);
void ActivityJobs_Step0B(Activity *activity);
void ActivityJobs_Start0C(void);
void ActivityJobs_Step0C(Activity *activity);
void ActivityJobs_Start0D(void);
void ActivityJobs_Step0D(Activity *activity);
void ActivityJobs_Start0E(void);
void ActivityJobs_Step0E(Activity *activity);
void ActivityJobs_Start0F(void);
void ActivityJobs_Step0F(Activity *activity);
void ActivityJobs_Start10(void);
void ActivityJobs_Step10(Activity *activity);
void ActivityJobs_Start11(void);
void ActivityJobs_Step11(Activity *activity);
void ActivityJobs_Start12(Activity *activity);
void ActivityJobs_Step12(Activity *activity);
void ActivityJobs_Start13(Activity *activity);
void ActivityJobs_Step13(Activity *activity);

#endif
