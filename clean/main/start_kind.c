/* How the game is started (start_kind.h). */
#include "start_kind.h"

#include "clean.h"
#include "player_records.h"
#include "session.h"
#include "state_block.h"
#include "player_options.h"
#include "session_players.h"

extern u32 data_021f3c30; /* enum StartKind */

extern NetSession *data_020ccf94;
extern StateBlock data_021dc7a8;

/* The name the new player gets: six full-width letters, "ABCDEF". */
extern const u16 data_020e3a68[];

#define FIRST_RECORD 0
#define NEW_PLAYER_ARG 0

/* func_020a128c */
void StartKind_Clear(void)
{
    data_021f3c30 = START_KIND_NONE;
}
CLEAN_AS(func_020a128c, StartKind_Clear)

/* func_020a1298 */
int StartKind_IsUnchanged(void)
{
    return data_021f3c30 == START_KIND_UNCHANGED;
}
CLEAN_AS(func_020a1298, StartKind_IsUnchanged)

/* func_020a12ac */
int StartKind_IsPlayer0(void)
{
    return data_021f3c30 == START_KIND_PLAYER_0;
}
CLEAN_AS(func_020a12ac, StartKind_IsPlayer0)

/* func_020a12c0 */
int StartKind_IsNewPlayer(void)
{
    return data_021f3c30 == START_KIND_NEW_PLAYER;
}
CLEAN_AS(func_020a12c0, StartKind_IsNewPlayer)

/* func_020a12d4 */
int StartKind_IsNewTown(void)
{
    return data_021f3c30 == START_KIND_NEW_TOWN;
}
CLEAN_AS(func_020a12d4, StartKind_IsNewTown)

/* func_020a12e8 */
int StartKind_IsSet(void)
{
    return data_021f3c30 != START_KIND_NONE;
}
CLEAN_AS(func_020a12e8, StartKind_IsSet)

/* func_020a12fc */
void StartKind_SetUnchanged(void)
{
    data_021f3c30 = START_KIND_UNCHANGED;
}
CLEAN_AS(func_020a12fc, StartKind_SetUnchanged)

/* func_020a1308 */
void StartKind_SetPlayer0(void)
{
    data_021f3c30 = START_KIND_PLAYER_0;
}
CLEAN_AS(func_020a1308, StartKind_SetPlayer0)

/* func_020a1314 */
void StartKind_SetNewPlayer(void)
{
    data_021f3c30 = START_KIND_NEW_PLAYER;
}
CLEAN_AS(func_020a1314, StartKind_SetNewPlayer)

/* func_020a1320 */
void StartKind_SetNewTown(void)
{
    data_021f3c30 = START_KIND_NEW_TOWN;
}
CLEAN_AS(func_020a1320, StartKind_SetNewTown)

/* func_020a13e8: the start kind applied. For a new town the state block is set up first; then
 * this system's session player becomes player 0 with record 0 (START_KIND_PLAYER_0) or with the
 * first free town record, which gets a new player named "ABCDEF". */
void StartKind_Apply(void)
{
    if (StartKind_IsUnchanged() != 0) {
        return;
    }
    if (StartKind_IsNewTown() != 0) {
        StateBlock_Init(&data_021dc7a8);
    }
    if (StartKind_IsPlayer0() != 0) {
        NetSession *session = data_020ccf94;
        session->local_player = 0;
        SessionPlayers_SetRecordNumber(session->local_player, FIRST_RECORD);
        PlayerOptions_Store();
        return;
    }
    int number = PlayerRecords_FirstFree(data_021dc7a8.players);
    NetSession *session = data_020ccf94;
    session->local_player = 0;
    SessionPlayers_SetRecordNumber(session->local_player, number);
    PlayerRecords_NewPlayer(data_021dc7a8.players, data_020e3a68, NEW_PLAYER_ARG, number);
}
CLEAN_AS(func_020a13e8, StartKind_Apply)
