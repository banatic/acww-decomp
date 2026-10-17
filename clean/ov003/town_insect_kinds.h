/* The start and update functions of the town insects' kinds (town_insect.h), the table
 * data_ov003_0223c2ac: for each kind 0-0x3b a function run once its files are loaded
 * (TownInsect_Load) or when a player lets it go (TownInsect_LetGo), and a function kept in
 * TownInsect.unk_170 and run each frame (TownInsect_Run).
 *
 * The start functions set the insect up through TownInsectKind_Begin, which most kinds reach
 * through a helper of their group. The update functions only pass the insect on to the
 * behaviour of their group, further on in overlay 3.
 *
 *   kinds                                          start                      update
 *   0-7                                            TownInsectKind_Start00To07 -> 02234b80
 *   8                                              TownInsectKind_Start08     -> 02232a44
 *   9, 0x10-0x14, 0x1f, 0x21, 0x22, 0x24, 0x26-0x2f, 0x34
 *                                                  TownInsectKind_StartLeaning -> 02231e24
 *   0xa                                            TownInsectKind_Start0A     -> 022335cc
 *   0xb, 0x3a                                      TownInsectKind_Start0B     -> 02233674
 *   0xc, 0xd, 0x1b-0x1d                            TownInsectKind_StartWaiting -> 02233d68
 *   0xe, 0xf, 0x1a, 0x20                           TownInsectKind_StartInArea -> 022314fc
 *   0x15-0x17                                      TownInsectKind_StartTurned -> 02234600
 *   0x18, 0x3b                                     TownInsectKind_Start18     -> 022334d8
 *   0x19                                           TownInsectKind_Start19     -> 02233930
 *   0x1e                                           TownInsectKind_Start1E     -> 0223345c
 *   0x23                                           TownInsectKind_Start23     -> 022325d4
 *   0x25, 0x39                                     TownInsectKind_Start25     -> 022337d8
 *   0x30                                           TownInsectKind_Start30     -> 02232874
 *   0x31                                           TownInsectKind_Start1E     -> 02232d30
 *   0x32                                           TownInsectKind_Start32     -> 02233890
 *   0x33                                           TownInsectKind_Start33     -> 022335cc
 *   0x35                                           TownInsectKind_Start35     -> 02231f20
 *   0x36                                           TownInsectKind_Start36     -> 02232640
 *   0x37                                           TownInsectKind_Start37     -> 02232640
 *   0x38                                           TownInsectKind_Start38     -> 02231e24 */
#ifndef CLEAN_OV003_TOWN_INSECT_KINDS_H
#define CLEAN_OV003_TOWN_INSECT_KINDS_H

#include "ov003/town_insect.h"
#include "types.h"

void TownInsectKind_Update38(TownInsect *insect);
void TownInsectKind_Start38(TownInsect *insect);
void TownInsectKind_Update23(TownInsect *insect);
void TownInsectKind_Start23(TownInsect *insect);
void TownInsectKind_Update18(TownInsect *insect);
void TownInsectKind_Start18(TownInsect *insect);
void TownInsectKind_Start37(TownInsect *insect);
void TownInsectKind_Start36(TownInsect *insect);
void TownInsectKind_Update36(TownInsect *insect);
void TownInsectKind_Update35(TownInsect *insect);
void TownInsectKind_Start35(TownInsect *insect);
void TownInsectKind_Update30(TownInsect *insect);
void TownInsectKind_Start30(TownInsect *insect);
void TownInsectKind_Update33(TownInsect *insect);
void TownInsectKind_Start33(TownInsect *insect);
void TownInsectKind_Update0A(TownInsect *insect);
void TownInsectKind_Start0A(TownInsect *insect);
void TownInsectKind_Update0B(TownInsect *insect);
void TownInsectKind_Start0B(TownInsect *insect);
void TownInsectKind_Update31(TownInsect *insect);
void TownInsectKind_Update1E(TownInsect *insect);
void TownInsectKind_Start1E(TownInsect *insect);
void TownInsectKind_StartInArea(TownInsect *insect);
void TownInsectKind_UpdateInArea(TownInsect *insect);
void TownInsectKind_BeginInArea(TownInsect *insect, int reached, int reach, int byte257, s16 pace);
void TownInsectKind_Update19(TownInsect *insect);
void TownInsectKind_Start19(TownInsect *insect);
void TownInsectKind_UpdateTurned(TownInsect *insect);
void TownInsectKind_StartTurned(TownInsect *insect);
void TownInsectKind_BeginTurned(TownInsect *insect, int reached, int reach, int height, u8 byte257, u8 byte259);
void TownInsectKind_StartWaiting(TownInsect *insect);
void TownInsectKind_UpdateWaiting(TownInsect *insect);
void TownInsectKind_BeginWaiting(TownInsect *insect, int reached, int reach, int byte257, u8 byte259);
void TownInsectKind_StartLeaning(TownInsect *insect);
void TownInsectKind_UpdateLeaning(TownInsect *insect);
void TownInsectKind_BeginLeaning(TownInsect *insect, int reached, int reach, int height, int forward);
void TownInsectKind_Update32(TownInsect *insect);
void TownInsectKind_Start32(TownInsect *insect);
void TownInsectKind_Update25(TownInsect *insect);
void TownInsectKind_Start25(TownInsect *insect);
void TownInsectKind_Start08(TownInsect *insect);
void TownInsectKind_Update08(TownInsect *insect);
void TownInsectKind_Start00To07(TownInsect *insect);
void TownInsectKind_BeginPaced(TownInsect *insect, int reached, int reach, int height, u8 byte257, int pace);
void TownInsectKind_Update00To07(TownInsect *insect);
short TownInsectKind_RandomAngle(void);
void TownInsectKind_Begin(TownInsect *insect, short unk_244, u8 reached, int reach, short angle_x, short angle_y, int height,
                          int above, u8 byte257, u8 on_ground);

#endif
