/* Two flags of main (block_02042200.h). */
#include "block_02042200.h"

#include "clean.h"
#include "scene_query.h"
#include "session.h"
#include "ov003/town_insect.h"
#include "town_day.h"

#define FLAG_BIT_0 0x80 /* byte 0x30 of data_021c79c4: flags[0] */
#define FLAG_BIT_1 0x40 /* flags[1] */

/* Overlay 3's flag set when flags[1] was (data_ov003_02260538), and its function that sets
 * its flag data_ov003_0226054c. */
extern u8 data_ov003_02260538;

extern u8 data_021c776c[2];
extern u8 data_021c79c4[0x34];
extern NetSession *data_020ccf94;

/* func_02042200: data_021c79c4's object updated, then the two flags read from it. */
void Block02042200_Update(void)
{
    TownDay_Summarize();
    Block02042200_ReadFlags(data_021c776c);
}
CLEAN_AS(func_02042200, Block02042200_Update)

/* func_02042218: unless this system's slot of the session is taken, in scene 0 or 0x31: the
 * flags handed to overlay 3 (flags[1] sets its byte data_ov003_02260538; either calls
 * func_ov003_0222ddac) and cleared. */
void Block02042200_Apply(u8 *flags)
{
    if (Session_IsSlotTaken(data_020ccf94, data_020ccf94->local_slot)) {
        return;
    }
    if (SceneQuery_CurrentIs0() || SceneQuery_CurrentIs31()) {
        if (flags[1] != 0) {
            data_ov003_02260538 = 1;
        }
        if (flags[1] != 0 || flags[0] != 0) {
            TownInsect_SetFlag54c();
        }
        flags[0] = 0;
        flags[1] = 0;
    }
}
CLEAN_AS(func_02042218, Block02042200_Apply)

/* func_0204226c: flags[0] and flags[1] set to bits 7 and 6 of data_021c79c4's byte 0x30. */
void Block02042200_ReadFlags(u8 *flags)
{
    u8 bits = data_021c79c4[0x30];
    flags[0] = (bits & FLAG_BIT_0) ? 1 : 0;
    flags[1] = (bits & FLAG_BIT_1) ? 1 : 0;
}
CLEAN_AS(func_0204226c, Block02042200_ReadFlags)
