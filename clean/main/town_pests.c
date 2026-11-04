/* The town's pests: the trash and spoiled turnip flags of main (town_pests.h). */
#include "town_pests.h"

#include "clean.h"
#include "scene_query.h"
#include "session.h"
#include "ov003/town_insect.h"
#include "town_day.h"

#define FLAG_BIT_TRASH 0x80          /* byte 0x30 of data_021c79c4: flags[0] */
#define FLAG_BIT_SPOILED_TURNIP 0x40 /* flags[1] */

/* Overlay 3's flag for the ants, set when flags[1] was (data_ov003_02260538), and its function
 * that sets its flag for the flies data_ov003_0226054c. */
extern u8 data_ov003_02260538;

extern u8 data_021c776c[2];
extern u8 data_021c79c4[0x34];
extern NetSession *data_020ccf94;

/* func_02042200: data_021c79c4's object updated, then the trash and turnip flags read from it. */
void TownPests_Update(void)
{
    TownDay_Summarize();
    TownPests_ReadFlags(data_021c776c);
}
CLEAN_AS(func_02042200, TownPests_Update)

/* func_02042218: unless this system's slot of the session is taken, in scene 0 or 0x31: the
 * flags handed to overlay 3 (the spoiled turnips, flags[1], set its byte data_ov003_02260538
 * for the ants; either calls TownInsect_SetFlag54c for the flies) and cleared. */
void TownPests_Apply(u8 *flags)
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
CLEAN_AS(func_02042218, TownPests_Apply)

/* func_0204226c: flags[0] (trash) and flags[1] (spoiled turnips) set to bits 7 and 6 of data_021c79c4's byte 0x30. */
void TownPests_ReadFlags(u8 *flags)
{
    u8 bits = data_021c79c4[0x30];
    flags[0] = (bits & FLAG_BIT_TRASH) ? 1 : 0;
    flags[1] = (bits & FLAG_BIT_SPOILED_TURNIP) ? 1 : 0;
}
CLEAN_AS(func_0204226c, TownPests_ReadFlags)
