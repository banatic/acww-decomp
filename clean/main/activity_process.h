/* The activity process (activity.h) as a process: made (ActivityProcess_New), created, run
 * and deleted, and its jobs 0 to 5 (activity_job.h; the jobs 6 to 0x1f are in
 * activity_jobs.h and activity_link_jobs.h).
 *
 * Its creation makes it the current activity (data_021f3c3c) and allocates from the current
 * heap the buffers the scene it runs in needs; its deletion frees them. In the scenes 9 and
 * 0xb of a linked session neither is done. Each frame it calls the step of its job. The job
 * table (data_021f3ea4) holds two member pointers for each job, its start and its step.
 *
 *   job 0  no job: each frame the job asked for (data_021f3c38) is started once the scene it
 *          belongs to is reached with the screen shown (data_021c75b8 2);
 *   job 1  message 1 of "sp_etc_sequence2", then (once talk 0 waits) the link status reset
 *          and the Wi-Fi session ended when this system's slot is taken, then the card checked
 *          and both copies written; then job 0xc;
 *   job 2  the same after message 0x66 of "sp_npc_gatekeeper"; then job 0xd;
 *   job 3  message 0x28 of "sp_etc_sequence1", then (once talk 0 waits) the clock set up, the
 *          villagers updated, the state block started anew (mode 2) and finished; then job 4;
 *   job 4  the card checked (after the object at data_021c779c + 0x20 is done) and both copies
 *          written; then job 0x10;
 *   job 5  message 12 of "sp_etc_sequence1", then the save's marks cleared and the three parts
 *          erased; then job 0xc.
 * When a card step fails, message 10 of "sp_etc_sequence2" is queued and the job stays where
 * it is for good. */
#ifndef CLEAN_MAIN_ACTIVITY_PROCESS_H
#define CLEAN_MAIN_ACTIVITY_PROCESS_H

#include "activity.h"
#include "types.h"

void ActivityProcess_StepJob5(Activity *activity);
void ActivityProcess_StartJob5(Activity *activity);
void ActivityProcess_StepJob4(Activity *activity);
void ActivityProcess_StartJob4(Activity *activity);
void ActivityProcess_StepJob3(Activity *activity);
void ActivityProcess_StartJob3(Activity *activity);
void ActivityProcess_StepJob2(Activity *activity);
void ActivityProcess_StartJob2(Activity *activity);
void ActivityProcess_StepJob1(Activity *activity);
void ActivityProcess_StartJob1(Activity *activity);
void ActivityProcess_StepJob0(Activity *activity);
void ActivityProcess_StartJob0(void);
void ActivityProcess_StartJob(Activity *activity, int job);
int ActivityProcess_Execute(Activity *activity);
int ActivityProcess_Delete(Activity *activity);
int ActivityProcess_Create(Activity *activity);
Activity *ActivityProcess_New(void);

#endif
