/* The jobs 0x14 to 0x1f of the activity process (activity.h, activity_job.h): those it runs
 * while systems are linked. As for the other jobs (activity_jobs.h), each is a start, called
 * once when func_020a4e94 starts the job, and a step, called once a frame.
 *
 * Most steps first check the link (Session_IsLinkLost, with the AIDs it should have): when it
 * is lost the session's send timeout is raised (Session_RaiseSendTimeout) and the step does
 * nothing else that frame. "Sendable" below means the library overlay is in place
 * (LibraryOverlay_RequireAny) and the network can send (Net_CanSend).
 *
 *   job 0x14  waits for the slot mask, sends this system's block, then takes the state block
 *             received from the other system as its own (with the session's slots and
 *             players, the clock offset of system packet 10 and the town's maps) and takes an
 *             exit of the entry record;
 *   job 0x15  adds the slot data_021f3c1c to the session and sends it the members, the system
 *             command list, the share data, the link entries, the packed state block and the
 *             date and time;
 *   job 0x16  adds the slot data_021f3c1c to the session and sends it the sender's block;
 *   job 0x17  after the gatekeeper's message: reports, saves (ActivitySave_GuestSteps), then
 *             leaves the session; job 8;
 *   job 0x18  after the gatekeeper's message: gives out the exchange block of the link state's
 *             slot, saves (ActivitySave_HostSteps), and removes that slot; job 0xa;
 *   job 0x19  after the gatekeeper's message: reports, saves (ActivitySave_GuestSteps), and
 *             waits for the session's members to change; job 0xa;
 *   job 0x1a  after message 7 of "sp_etc_sequence2": saves (ActivitySave_HostSteps) and,
 *             on the start menu's leave choice, gives out the exchange blocks and leaves the
 *             session; job 8;
 *   job 0x1b  after message 7 of "sp_etc_sequence2": reports, saves
 *             (ActivitySave_GuestSteps) and, on the leave choice, leaves the session; job 0x11
 *             or 8;
 *   job 0x1c  message 35 of "sp_etc_sequence1", then overlay 66 loaded; job 0x1d;
 *   job 0x1d  a session started for a second system, waited for (600 frames while alone);
 *   job 0x1e  once system packet 20 named a slot: the state block started or flagged, the
 *             letters and a copy written to the card, and the answer of that slot exchanged;
 *   job 0x1f  this system's player sent (system packets 20-23), kept aside and cleared, the
 *             card written, and the answer of the other system exchanged. */
#ifndef CLEAN_MAIN_ACTIVITY_LINK_JOBS_H
#define CLEAN_MAIN_ACTIVITY_LINK_JOBS_H

#include "activity.h"
#include "types.h"

void ActivityLinkJobs_Start14(Activity *activity);
void ActivityLinkJobs_Step14(Activity *activity);
void ActivityLinkJobs_Start15(Activity *activity);
void ActivityLinkJobs_Step15(Activity *activity);
void ActivityLinkJobs_Start16(Activity *activity);
void ActivityLinkJobs_Step16(Activity *activity);
void ActivityLinkJobs_Start17(Activity *activity);
void ActivityLinkJobs_Step17(Activity *activity);
void ActivityLinkJobs_Start18(Activity *activity);
void ActivityLinkJobs_Step18(Activity *activity);
void ActivityLinkJobs_Start19(Activity *activity);
void ActivityLinkJobs_Step19(Activity *activity);
void ActivityLinkJobs_Start1A(Activity *activity);
void ActivityLinkJobs_Step1A(Activity *activity);
void ActivityLinkJobs_Start1B(Activity *activity);
void ActivityLinkJobs_Step1B(Activity *activity);
void ActivityLinkJobs_Start1C(Activity *activity);
void ActivityLinkJobs_Step1C(Activity *activity);
void ActivityLinkJobs_Start1D(Activity *activity);
void ActivityLinkJobs_Step1D(Activity *activity);
void ActivityLinkJobs_Start1E(Activity *activity);
void ActivityLinkJobs_Step1E(Activity *activity);
void ActivityLinkJobs_Start1F(Activity *activity);
void ActivityLinkJobs_Step1F(Activity *activity);

#endif
