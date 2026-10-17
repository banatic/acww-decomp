/* Overlay 55 (the exchange character, xct_exchange.h): its static initialiser, run when the
 * overlay is loaded, which fills in the functions of his talk's steps (data_ov055_02260f0c,
 * xct_exchange_talk.h) and of his states (data_ov055_02261084, XctExchange_SetState and
 * XctExchange_Update), copied from the overlay's constants (C++ pointers to member functions,
 * which the compiler does not fold into the tables). */
#include <stdint.h>

#include "clean.h"
#include "types.h"
#include "xct_exchange.h"
#include "xct_exchange_talk.h"

/* The tables. */
extern XctExchangeTalkStep data_ov055_02260f0c[XCT_EXCHANGE_TALK_STEPS];
extern XctExchangeStep data_ov055_02261084[XCT_EXCHANGE_STATES];
/* The null member pointer, and each step's and state's functions. */
extern const MemberPointer __ptmf_null;
extern const MemberPointer data_ov055_02260e64, data_ov055_02260e6c, data_ov055_02260e74, data_ov055_02260e7c,
    data_ov055_02260e84, data_ov055_02260e8c, data_ov055_02260e94, data_ov055_02260e9c, data_ov055_02260ea4;

/* __sinit_ov055_02260db4: the talk's steps 0 to 3 (none, then XctExchangeTalk_StepExchanging,
 * XctExchangeTalk_StepDone and XctExchangeTalk_StepStopping), then the entries and updates of
 * his three states in order. The address of the states' table. */
int Ov055Init_XctExchangeTables(void)
{
    data_ov055_02260f0c[XCT_EXCHANGE_TALK_STEP_NONE].run = __ptmf_null;
    data_ov055_02260f0c[XCT_EXCHANGE_TALK_STEP_EXCHANGING].run = data_ov055_02260e84;
    data_ov055_02260f0c[XCT_EXCHANGE_TALK_STEP_DONE].run = data_ov055_02260e94;
    data_ov055_02260f0c[XCT_EXCHANGE_TALK_STEP_STOPPING].run = data_ov055_02260e64;
    data_ov055_02261084[XCT_EXCHANGE_WAIT].enter = data_ov055_02260e74;  /* XctExchange_EnterWait */
    data_ov055_02261084[XCT_EXCHANGE_WAIT].update = data_ov055_02260e9c; /* XctExchange_UpdateWait */
    data_ov055_02261084[XCT_EXCHANGE_TALK].enter = data_ov055_02260e6c;  /* XctExchange_EnterTalk */
    data_ov055_02261084[XCT_EXCHANGE_TALK].update = data_ov055_02260ea4; /* XctExchange_UpdateTalk */
    data_ov055_02261084[XCT_EXCHANGE_DONE].enter = data_ov055_02260e8c;  /* XctExchange_EnterDone */
    data_ov055_02261084[XCT_EXCHANGE_DONE].update = data_ov055_02260e7c; /* XctExchange_UpdateDone */
    return (int) (uintptr_t) data_ov055_02261084;
}
CLEAN_AS(__sinit_ov055_02260db4, Ov055Init_XctExchangeTables)
