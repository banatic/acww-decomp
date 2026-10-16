/* Flags in the large state block (state_block.h). */
#include "state_block.h"

#include "acre_map.h"
#include "autoload_2/process.h" /* MemberFn */
#include "bbs.h"
#include "bottle_mail.h"
#include "clean.h"
#include "clock.h"
#include "constellations.h"
#include "design.h"
#include "design_sets.h"
#include "fox_shop.h"
#include "house_looks.h"
#include "letter_store.h"
#include "mail.h"
#include "museum_record.h"
#include "nook_store.h"
#include "player_record.h"
#include "player_records.h"
#include "room_cells.h"
#include "room_interior.h"
#include "room_object_state.h"
#include "scene_claim.h"
#include "shop_list_a.h"
#include "snowmen.h"
#include "sound.h"
#include "town_layout.h"
#include "town_objects.h"
#include "villager_kinds.h"
#include "villager_plots.h"
#include "villager_residents.h"
#include "villager_roster.h"
#include "villager_state.h"
#include "villager_town.h"

#define FLAGS_OFFSET 0x173f4 /* one word: flags 0-31 */

static volatile u32 *flags_of(u32 *block)
{
    return (volatile u32 *) ((u8 *) block + FLAGS_OFFSET);
}

/* func_0209f100. Flags 32 and above do not exist and are ignored. */
void StateBlock_ClearFlag(u32 *block, u32 flag)
{
    if (flag < 32) {
        *flags_of(block) &= ~(1u << flag);
    }
}
CLEAN_AS(func_0209f100, StateBlock_ClearFlag)

/* func_0209f128 */
void StateBlock_SetFlag(u32 *block, u32 flag)
{
    if (flag < 32) {
        *flags_of(block) |= 1u << flag;
    }
}
CLEAN_AS(func_0209f128, StateBlock_SetFlag)

/* func_0209f150: whether `flag` is set; flags 32 and above never are. */
int StateBlock_TestFlag(u32 *block, u32 flag)
{
    return flag < 32 && (*flags_of(block) & (1u << flag)) != 0;
}
CLEAN_AS(func_0209f150, StateBlock_TestFlag)

/* ---- Setting up, starting and destructing the block ---- */

#define STATE_BLOCK_START_MODES 7
#define SCENE_6 6                       /* the scene in which StateBlock_StartMode2 leaves the town as it is */
#define LETTER_STORE_PLAYER_SIZE 0x3200 /* one player's letters in the block of letters */

static_assert(sizeof(StateBlock) == 0x173fc, "the state block's size (StateBlock_Clear)");
static_assert(sizeof(StateBlockTown) == 14, "a town's number and name");
static_assert(offsetof(StateBlock, players) == 0x14 && offsetof(StateBlock, villagers) == 0x9284, "state block");
static_assert(offsetof(StateBlock, mailboxes) == 0x13144 && offsetof(StateBlock, part_16800) == 0x16800, "state block");
static_assert(offsetof(StateBlock, museum) == 0x17150 && offsetof(StateBlock, clock_offset) == 0x173cc, "state block");
static_assert(offsetof(StateBlock, flags) == FLAGS_OFFSET && offsetof(StateBlock, part_173f8) == 0x173f8, "state block");

extern StateBlock data_021dc7a8;
extern void *data_021fbe94; /* the current heap */

/* The table StateBlock_Start fills on its first call (data_021dc770, guarded by bit 0 of
 * data_021dc760) from the member function pointers at data_020e3654..data_020e3684. */
extern u32 data_021dc760;
extern MemberFn data_021dc770[STATE_BLOCK_START_MODES];
extern const MemberFn data_020e367c, data_020e3654, data_020e366c, data_020e3664, data_020e3684, data_020e3674, data_020e365c;

/* The default town (StateBlock_StartMode3). */
extern const StateBlockTown data_020e368c;
/* A sound effect for each value of func_0203d470. */
extern const int data_020d1b90[];

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void MI_CpuFill8(void *dst, u8 value, u32 size);
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
/* The destructors of a part at 0x16800 and of a mailbox, handed to __cxa_vec_cleanup. */
extern void func_0203a68c(void *object);
extern void *func_020980a4(void *box);

/* The date and time the game keeps at data_021cfc98, copied out. */
extern void func_0206f80c(DateTime *when);

/* A town's number and name: copied in, set up empty, destructed. */
extern void func_02064244(StateBlockTown *town, const StateBlockTown *from);
extern void func_020642e0(StateBlockTown *town);
extern void func_020642f8(StateBlockTown *town);
/* A design creator's town (DesignCreator, design_sets.h): setting it, and where it is. */
extern void func_02095038(DesignCreator *creator, StateBlockTown *town);
extern StateBlockTown *func_02095040(DesignCreator *creator);

extern void func_0204d0ac(AcreMap *map);

/* What the parts of the block without a Clean name are given. */
extern void func_0209fa40(u8 *part);
extern int func_0209faac(u8 *part, const void *from);
extern void func_0209fad4(u8 *part);
extern void func_0209fae4(u8 *part);
extern int func_0209fb3c(u8 *part);
extern void func_0209fb5c(u8 *part);
extern void func_0209fb64(u8 *part);
extern void func_0209fb6c(u8 *part);
extern void func_0203a4ec(u8 *part);
extern void func_0203a500(u8 *part);
extern void func_0203a5f4(u8 *part);
extern void func_0203a658(u8 *part);
extern void func_0203a66c(u8 *part);
extern void func_0203a678(u8 *part);
extern void func_02041194(u8 *part);
extern void func_020411f4(u8 *part);
extern void func_020411fc(u8 *part);
extern void func_02041294(u8 *part);
extern void func_0204cdfc(u8 *part);
extern void func_0204ce64(u8 *part);
extern void func_0204cf0c(u8 *part);
extern void func_0205bf88(u8 *part);
extern void func_0205bf90(u8 *part);
extern void func_0205bfbc(u8 *part);
extern void func_02060f40(u8 *part);
extern void func_0206108c(u8 *part);
extern int func_02061118(u8 *part);
extern void func_02063eb8(u8 *part);
extern void *func_02063ed4(u8 *part);
extern void func_0206ea3c(u8 *part);
extern void func_0206ea54(u8 *part);
extern void func_0208683c(u8 *part);
extern void func_02086874(u8 *part);
extern char *func_020868a0(u8 *part);
extern void func_02087138(u8 *part);
extern void func_02087140(u8 *part);
extern void func_02087164(u8 *part);
extern void func_020871b0(u8 *part);
extern void func_020871b8(u8 *part);
extern void func_020871c4(u8 *part);
extern void func_0208722c(u8 *part);
extern void func_02087234(u8 *part);
extern int func_0208724c(u8 *part);
extern void func_02087480(u8 *part);
extern void func_02087800(u8 *part);
extern void func_02087830(u8 *part);
extern void func_0208784c(u8 *part);
extern void func_02088248(u8 *part);
extern void func_02088250(u8 *part);
extern int func_02088264(u8 *part);
extern void *func_02088450(u8 *part);
extern void func_02090018(u8 *part);
extern int func_02090020(u8 *part);
extern void func_02090174(u8 *part);
extern void func_0209019c(u8 *part);
extern char *func_020901a0(u8 *part);
extern void func_020c176c(u8 *part);
extern void func_020c17f0(u8 *part);
extern void func_020c17f8(u8 *part);
extern void func_020c1818(u8 *part);
extern void func_020882f0(u8 *part);

/* Parts of a player's record without a Clean name. */
extern void func_02088aa0(u8 *field);
extern void func_02088ac0(u8 *field);
extern void func_02088b68(u8 *field);

/* Game state outside the block. */
extern void func_0202f164(void);
extern int func_0203d470(void);
extern void func_02046830(void);
extern int func_0205a2f0(void);
extern void func_0205bdb0(void);
extern void func_0206f614(void);
extern void func_02085e18(void);
extern void func_02085e94(void);
extern void func_02088318(void);
extern void func_020a128c(void);
extern int func_020a1368(void); /* the block of letters (letter_store.h), or 0 */
extern u8 func_020b65c4(void);  /* the scene */
extern void func_020ba2e0(void);
extern void func_020ba38c(void);
extern void func_020ba39c(void);
extern void func_020ba3ac(void);
extern void *func_0208b500(void);
extern void func_0208d0bc(void *object, int a, int b);
/* An object (func_0208602c) and the parts of it that func_020860b8..func_020860c8 give. */
extern void *func_0208602c(void);
extern void func_02086034(void *object);
extern void func_02086130(void *object);
extern void *func_020860b8(void *object);
extern void *func_020860c0(void *object);
extern void *func_020860c4(void *object);
extern void *func_020860c8(void *object);
extern int func_0208786c(void *part);
extern void func_02087e64(void *part);
extern void func_02087e9c(void *part, int value);
extern void func_02087eb0(void *part);
extern void func_02087f58(void *part);

static VillagerTown *villagers_of(StateBlock *block)
{
    return (VillagerTown *) block->villagers;
}

/* func_0209e604: what every start (StateBlock_Start) is followed by: the parts of the town
 * that live outside the block reset, the visitors and the villagers' states cleared, and the
 * villagers told the current player. */
void StateBlock_FinishStart(StateBlock *block)
{
    func_0209fa40(block->part_173dd);
    func_02085e94();
    func_02085e18();
    VillagerTown_ClearByte18AndCounters(villagers_of(block));
    func_02086130(func_0208602c());
    RoomCells_ResetAll();
    RoomObjectState_Clear();
    TownObjects_ResetRecordedModes();
    TownObjects_ResetVisits();
    RoomInterior_ClearScenes();
    func_02041194(block->part_17218);
    func_020c176c(block->part_1737e);
    func_02046830();
    NookStore_Refresh((NookStore *) block->nook_store, 0);
    func_0206ea3c(block->part_173c0);
    func_02087f58(func_020860c4(func_0208602c()));
    func_02087e64(func_020860c0(func_0208602c()));
    func_02086034(func_0208602c());
    func_0208786c(func_020860b8(func_0208602c()));
    func_0208d0bc(func_0208b500(), 0, 1);
    func_0202f164();
    VillagerTown_PickIndex161(villagers_of(block));
    func_0206f614();
    TownObjects_ClearExtraVisitors();
    VillagerTown_SetByte1E(villagers_of(block), PlayerRecords_Current());
    VillagerState_ClearWord168();
    VillagerState_ClearAllFlag2();
    VillagerState_ClearAllTallies();
    VillagerState_ClearAllFlag0();
}
CLEAN_AS(func_0209e604, StateBlock_FinishStart)

/* `fn` called on `object` (MemberFn, autoload_2/process.h). */
static void call_member(const MemberFn *fn, void *object)
{
    uintptr_t self = (uintptr_t) object + (uintptr_t) (intptr_t) ((fn->adj - (fn->adj & 1)) / 2);
    uintptr_t target = fn->ptr;
    if ((fn->adj & 1) != 0) {
        uintptr_t vtable = *(const u32 *) self;
        target = *(const u32 *) (vtable + fn->ptr);
    }
    ((void (*)(void *)) target)((void *) self);
}

/* func_0209e6ec: the block started in `mode` (0-6) through a table of the modes' member
 * functions, StateBlock_StartMode0 to StateBlock_StartMode6; the table is a function-local
 * static that the first call fills.
 * REQUIRES: mode is 0-6. */
void StateBlock_Start(StateBlock *block, int mode)
{
    if ((data_021dc760 & 1) == 0) {
        data_021dc770[0] = data_020e367c;
        data_021dc770[1] = data_020e3654;
        data_021dc770[2] = data_020e366c;
        data_021dc770[3] = data_020e3664;
        data_021dc770[4] = data_020e3684;
        data_021dc770[5] = data_020e3674;
        data_021dc770[6] = data_020e365c;
        data_021dc760 |= 1;
    }
    call_member(&data_021dc770[mode], block);
}
CLEAN_AS(func_0209e6ec, StateBlock_Start)

/* func_0209e79c: the clock offset set so that the clock reads the date and time kept at
 * data_021cfc98 (func_0206f80c), then the clock started. */
void StateBlock_SetClockOffset(StateBlock *block)
{
    ClockOffset *offset = &block->clock_offset;
    ClockOffset_Clear(offset);
    DateTime kept = {0};
    func_0206f80c(&kept);
    DateTime when;
    MI_CpuCopy8(&kept, &when, sizeof(DateTime));
    int minutes = ClockOffset_MinutesTo(offset, &when);
    MI_CpuCopy8(&kept, &when, sizeof(DateTime));
    int seconds = ClockOffset_SecondsTo(offset, &when);
    offset->minutes = minutes;
    offset->seconds = (s16) seconds;
    Clock_Init();
}
CLEAN_AS(func_0209e79c, StateBlock_SetClockOffset)

/* func_0209e7fc: when there is a town map, its models set and its data loaded, then
 * func_0204d0ac. `block` is not read. */
void StateBlock_LoadTownMap(StateBlock *block)
{
    (void) block;
    if (AcreMap_Town() != 0) {
        AcreMap_SetTownModels((AcreMap *) (uintptr_t) AcreMap_Town());
        AcreMap_LoadTownData((AcreMap *) (uintptr_t) AcreMap_Town());
        func_0204d0ac((AcreMap *) (uintptr_t) AcreMap_Town());
    }
}
CLEAN_AS(func_0209e7fc, StateBlock_LoadTownMap)

/* func_0209e828: a new town's parts set up, and the block marked as set up
 * (StateBlock_IsSetUp). The villagers are dealt only when there is a current player. */
void StateBlock_SetUpTown(StateBlock *block)
{
    block->marker = STATE_BLOCK_SET_UP;
    func_0209fb64(block->part_173f8);
    VillagerResidents_StartTown(villagers_of(block));
    VillagerPlot_GiveHouses(villagers_of(block));
    VillagerKind_ClearAll();
    if (PlayerRecords_Current() != NULL) {
        VillagerKind_Deal(villagers_of(block));
    }
    HouseLooks_Reset((HouseLooksRecord *) block->house_looks);
    func_02060f40(block->part_0f52c);
    AcreMap_SetRoomsModels();
    AcreMap_LoadRoomsData();
    ShopDesigns_Reset((ShopDesigns *) block->shop_designs);
    func_0205bdb0();
    func_02063eb8(block->part_173d4);
    Bbs_Init((Bbs *) block->bbs);
    NookStore_Reset((NookStore *) block->nook_store);
    ShopListA_Reset((ShopListA *) block->shop_list_a);
    FoxShop_Reset((FoxShop *) block->fox_shop);
    func_0204ce64(block->part_17254);
    func_020c17f8(block->part_1737e);
    func_020411fc(block->part_17218);
    func_02088248(block->part_16ad0);
    func_02087800(block->part_17364);
    func_0208722c(block->part_17344);
    func_020871b0(&block->part_0f52a);
    func_0208683c(block->part_172fc);
    func_0205bf88(block->part_173c8);
    func_0206ea54(block->part_173c0);
    func_0203a5f4(block->part_172c0);
    func_02087138(&block->part_0f52b);
    func_0209019c(block->part_11c70);
}
CLEAN_AS(func_0209e828, StateBlock_SetUpTown)

/* func_0209e974: the current player made a resident of the block's town: the record's last
 * play date set to today and its town to the block's, the designs it made in its old town
 * moved to the new one, flags 0x24-0x26 and 0xf cleared with the parts they go with, and the
 * record reset for a new town (PlayerRecord_ResetForNewTown). */
void StateBlock_MovePlayerHere(StateBlock *block)
{
    u8 *record = PlayerRecords_Current();
    StateBlockTown old_town = *func_02095040(PlayerRecord_Player(record));

    Calendar_Today(PlayerRecord_LastPlayDate(record));
    func_02095038(PlayerRecord_Player(record), &block->town);
    PlayerDesigns *designs = PlayerRecord_Designs(record);
    PlayerDesigns_UpdateTown(designs, PlayerRecord_Player(record), (u8 *) &old_town);
    PlayerRecord_ClearFlag(record, 0x24);
    PlayerRecord_ClearFlag(record, 0x25);
    PlayerRecord_ClearFlag(record, 0x26);
    func_02088ac0(PlayerRecord_Field2416(record));
    PlayerRecord_ClearFlag(record, 0xf);
    func_02088aa0(PlayerRecord_Field2416(record));
    func_020882f0(PlayerRecord_Field242C(record));
    PlayerRecord_ResetForNewTown(record);
    func_020642f8(&old_town);
}
CLEAN_AS(func_0209e974, StateBlock_MovePlayerHere)

/* What modes 5, 4 and 1 begin with: the town map loaded, the rooms set up and the clock
 * started. */
static void load_town(StateBlock *block)
{
    StateBlock_LoadTownMap(block);
    AcreMap_SetRoomsModels();
    AcreMap_LoadRoomsData();
    Clock_Init();
}

/* The snowballs left lying reset and the town's upper settings applied. */
static void settle_town(StateBlock *block)
{
    Snowmen_ResetLooseBalls(Snowmen_LooseBalls());
    TownLayout_SetUpperSettings((unsigned int) (uintptr_t) block->layout);
}

/* The end of modes 6, 5, 1 and 0: villager index 0x16c cleared (-1), the villagers outdoors
 * updated keeping their time, func_02087eb0, and the villagers searched. */
static void finish_villagers(StateBlock *block)
{
    VillagerState_SetIndex16C(-1);
    VillagerRoster_UpdateOutdoors(villagers_of(block), 1);
    func_02087eb0(func_020860c8(func_0208602c()));
    VillagerTown_SearchAll(villagers_of(block));
}

/* Flags 1 and 0x23 set and 9 cleared in a player's record, as a start that makes the player
 * a resident does. */
static void mark_resident(u8 *record)
{
    PlayerRecord_SetFlag(record, 1);
    PlayerRecord_SetFlag(record, 0x23);
    PlayerRecord_ClearFlag(record, 9);
}

/* func_0209ea24 (mode 6): a new town generated, and the current player moved into it. */
void StateBlock_StartMode6(StateBlock *block)
{
    u8 *record = PlayerRecords_Current();
    StateBlock_SetClockOffset(block);
    TownLayout_Generate(block->layout, data_021fbe94);
    StateBlock_LoadTownMap(block);
    func_0209faac(block->part_173dd, NULL);
    StateBlock_MovePlayerHere(block);
    StateBlock_SetUpTown(block);
    settle_town(block);
    SceneClaim_Reset();
    mark_resident(record);
    finish_villagers(block);
}
CLEAN_AS(func_0209ea24, StateBlock_StartMode6)

/* func_0209eac8 (mode 5): the town loaded, and the current player moved into it. */
void StateBlock_StartMode5(StateBlock *block)
{
    u8 *record = PlayerRecords_Current();
    load_town(block);
    StateBlock_MovePlayerHere(block);
    mark_resident(record);
    VillagerTown_Update(villagers_of(block), 0);
    VillagerPlot_GiveHouses(villagers_of(block));
    VillagerKind_ClearAll();
    VillagerKind_Deal(villagers_of(block));
    settle_town(block);
    SceneClaim_Reset();
    PlayerRecord_SetByte2452(record, 0);
    finish_villagers(block);
}
CLEAN_AS(func_0209eac8, StateBlock_StartMode5)

/* func_0209eb74 (mode 4): the town loaded and its villagers updated without the designs
 * (VillagerTown_Update); flag 0 cleared in each of the town's player records.
 * QUIRK: the records are those of the game's block (data_021dc7a8), whatever `block` is. */
void StateBlock_StartMode4(StateBlock *block)
{
    load_town(block);
    VillagerTown_Update(villagers_of(block), 1);
    VillagerPlot_GiveHouses(villagers_of(block));
    VillagerState_SetIndex16C(-1);
    VillagerRoster_UpdateOutdoors(villagers_of(block), 1);
    func_020ba39c();
    func_02087eb0(func_020860c8(func_0208602c()));
    for (int i = 0; i < STATE_BLOCK_PLAYERS; i++) {
        u8 *record = PlayerRecords_TownRecord(data_021dc7a8.players, i);
        if (record != NULL) {
            PlayerRecord_SetFlag0(record, 0);
        }
    }
}
CLEAN_AS(func_0209eb74, StateBlock_StartMode4)

/* func_0209ebec (mode 3): a new town with the default name (data_020e368c) and no clock
 * offset. */
void StateBlock_StartMode3(StateBlock *block)
{
    ClockOffset_Clear(&block->clock_offset);
    Clock_Init();
    TownLayout_Generate(block->layout, data_021fbe94);
    StateBlock_LoadTownMap(block);
    func_02064244(&block->town, &data_020e368c);
    StateBlock_SetUpTown(block);
    settle_town(block);
    VillagerState_SetIndex16C(-1);
    VillagerRoster_UpdateOutdoors(villagers_of(block), 0);
    func_0209fb5c(block->part_173f8);
    func_020ba38c();
    func_02087eb0(func_020860c8(func_0208602c()));
}
CLEAN_AS(func_0209ebec, StateBlock_StartMode3)

/* func_0209ec74 (mode 2): the town loaded (in scene 6 its map, rooms, clock and the
 * villagers' update are left out), then the day's mail, the sound effect for func_0203d470's
 * value and the town's other systems brought up to date. In scene 6, with villager index
 * 0x16c at -1, a player record with flag 2 and without flag 0x23 gets func_02088b68 and
 * func_02087e9c. Flag 2 is then set and the villager letter sent; outside scene 6 the
 * villagers are searched. */
void StateBlock_StartMode2(StateBlock *block)
{
    u8 *record = PlayerRecords_Current();
    if (func_020b65c4() != SCENE_6) {
        load_town(block);
        VillagerTown_Update(villagers_of(block), 0);
    }
    VillagerPlot_GiveHouses(villagers_of(block));
    VillagerKind_ClearAll();
    VillagerKind_Deal(villagers_of(block));
    settle_town(block);
    SceneClaim_Reset();
    func_0205a2f0();
    SoundSys_SetCaptureEffect(data_020d1b90[func_0203d470()]);
    func_02088318();
    BottleMail_ReceiveDrifting();
    Constellations_FileDraft();
    Mail_DeliverWaiting();
    func_020a128c();
    func_020ba3ac();
    func_020ba2e0();
    func_02087480(block->part_17364);
    VillagerTown_PickBirthdayVisitor(villagers_of(block), NULL);
    VillagerRoster_UpdateOutdoors(villagers_of(block), 1);
    if (func_020b65c4() == SCENE_6 && VillagerState_GetIndex16C() == -1 && PlayerRecord_TestFlag(record, 0x23) == 0 &&
        PlayerRecord_TestFlag(record, 2) != 0) {
        func_02088b68(PlayerRecord_Field2416(record));
        func_02087e9c(func_020860c8(func_0208602c()), 1);
    }
    PlayerRecord_SetFlag(record, 2);
    PlayerRecord_SendVillagerLetter(record);
    if (func_020b65c4() != SCENE_6) {
        VillagerTown_SearchAll(villagers_of(block));
    }
}
CLEAN_AS(func_0209ec74, StateBlock_StartMode2)

/* func_0209ed90 (mode 1): the town loaded, and the current player made its resident with
 * its designs reset. */
void StateBlock_StartMode1(StateBlock *block)
{
    u8 *record = PlayerRecords_Current();
    load_town(block);
    func_02095038(PlayerRecord_Player(record), &block->town);
    PlayerDesigns *designs = PlayerRecord_Designs(record);
    PlayerDesigns_Reset(designs, PlayerRecord_Player(record));
    mark_resident(record);
    VillagerTown_Update(villagers_of(block), 0);
    VillagerPlot_GiveHouses(villagers_of(block));
    VillagerKind_ClearAll();
    VillagerKind_Deal(villagers_of(block));
    settle_town(block);
    SceneClaim_Reset();
    PlayerRecord_SetByte2452(record, 0);
    finish_villagers(block);
}
CLEAN_AS(func_0209ed90, StateBlock_StartMode1)

/* func_0209ee54 (mode 0): a new town generated, and the current player made its resident
 * with its designs reset. */
void StateBlock_StartMode0(StateBlock *block)
{
    u8 *record = PlayerRecords_Current();
    StateBlock_SetClockOffset(block);
    TownLayout_Generate(block->layout, data_021fbe94);
    StateBlock_LoadTownMap(block);
    func_0209faac(block->part_173dd, NULL);
    func_02095038(PlayerRecord_Player(record), &block->town);
    PlayerDesigns *designs = PlayerRecord_Designs(record);
    PlayerDesigns_Reset(designs, PlayerRecord_Player(record));
    StateBlock_SetUpTown(block);
    settle_town(block);
    SceneClaim_Reset();
    mark_resident(record);
    finish_villagers(block);
}
CLEAN_AS(func_0209ee54, StateBlock_StartMode0)

/* func_0209ef10: what the town keeps of player `player` (0-3) forgotten: its mailbox, its
 * part at 0x16800, its museum donations, its designs' items, its part of the fox's shop and,
 * when the block of letters exists, its letters. */
void StateBlock_ForgetPlayer(StateBlock *block, int player)
{
    MailBox_Init((MailBox *) block->mailboxes[player]);
    func_0203a678(block->part_16800[player]);
    MuseumRecord_ForgetPlayer((MuseumRecord *) block->museum, player);
    Design_RemovePlayerItems(player);
    FoxShop_ClearPlayer((u8) player);
    int letters = func_020a1368();
    if (letters != 0) {
        LetterStore_Clear((MailLetter *) (uintptr_t) (u32) (letters + LETTER_STORE_PLAYER_SIZE * player));
    }
}
CLEAN_AS(func_0209ef10, StateBlock_ForgetPlayer)

/* func_0209ef7c: the block cleared and each of its parts set up empty. */
void StateBlock_Init(StateBlock *block)
{
    StateBlock_Clear(block);
    for (int i = 0; i < STATE_BLOCK_PLAYERS; i++) {
        StateBlock_ForgetPlayer(block, i);
    }
    func_020642e0(&block->town);
    PlayerRecords_ClearTown(block->players);
    VillagerRoster_Init(villagers_of(block));
    ShopListA_Init((ShopListA *) block->shop_list_a);
    FoxShop_Init((FoxShop *) block->fox_shop);
    TownLayout_Clear(block->layout);
    Bbs_Clear((Bbs *) block->bbs);
    func_0206108c(block->part_0f52c);
    func_0204cdfc(block->part_17254);
    func_020c17f0(block->part_1737e);
    NookStore_Initialize((NookStore *) block->nook_store);
    func_02088250(block->part_16ad0);
    func_02087830(block->part_17364);
    func_02087234(block->part_17344);
    func_020871b8(&block->part_0f52a);
    func_02086874(block->part_172fc);
    MailPostOffice_Init((MailPostOffice *) block->post_office);
    func_0203a658(block->part_172c0);
    func_0203a4ec(block->part_172de);
    Constellations_ResetStore((ConstellationStore *) block->constellations);
    BottleMail_InitState((BottleState *) block->bottle);
    func_02090018(block->part_1704c);
    func_0205bf90(block->part_173c8);
    func_0209fad4(block->part_173dd);
    Snowmen_ForgetAll((SnowmenRecord *) block->snowmen);
    func_020411f4(block->part_17218);
    func_020882f0(block->part_173e2);
    func_02087140(&block->part_0f52b);
    func_02090174(block->part_11c70);
}
CLEAN_AS(func_0209ef7c, StateBlock_Init)

/* func_0209f0f0 */
void StateBlock_Clear(StateBlock *block)
{
    MI_CpuFill8(block, 0, sizeof(StateBlock));
}
CLEAN_AS(func_0209f0f0, StateBlock_Clear)

/* func_0209f180: whether a town was set up in the block and the part at 0x173f8 says so too. */
int StateBlock_IsSetUp(StateBlock *block)
{
    return block->marker == STATE_BLOCK_SET_UP && func_0209fb3c(block->part_173f8) != 0;
}
CLEAN_AS(func_0209f180, StateBlock_IsSetUp)

/* func_0209f1a8: the destructor (registered at start-up): the parts destructed from the last
 * to the first. */
StateBlock *StateBlock_Destruct(StateBlock *block)
{
    func_0209fb6c(block->part_173f8);
    func_02088450(block->part_173e2);
    func_0209fae4(block->part_173dd);
    func_02063ed4(block->part_173d4);
    func_0205bfbc(block->part_173c8);
    Snowmen_DestructRecords((SnowmenRecord *) block->snowmen);
    ShopListA_Destruct((ShopListA *) block->shop_list_a);
    FoxShop_Destruct((FoxShop *) block->fox_shop);
    func_020c1818(block->part_1737e);
    func_0208784c(block->part_17364);
    func_0208724c(block->part_17344);
    func_020868a0(block->part_172fc);
    func_0203a500(block->part_172de);
    func_0203a66c(block->part_172c0);
    func_0204cf0c(block->part_17254);
    func_02041294(block->part_17218);
    NookStore_Destruct((NookStore *) block->nook_store);
    MuseumRecord_Destruct((MuseumRecord *) block->museum);
    func_02090020(block->part_1704c);
    BottleMail_DestructState((BottleState *) block->bottle);
    HouseLooks_Destruct((HouseLooksRecord *) block->house_looks);
    func_02088264(block->part_16ad0);
    __cxa_vec_cleanup(block->part_16800, STATE_BLOCK_PLAYERS, sizeof(block->part_16800[0]), func_0203a68c);
    Constellations_DestructList((ConstellationStore *) block->constellations);
    MailPostOffice_Destruct((MailPostOffice *) block->post_office);
    __cxa_vec_cleanup(block->mailboxes, STATE_BLOCK_PLAYERS, sizeof(block->mailboxes[0]),
                      (void (*)(void *))(uintptr_t) func_020980a4);
    Bbs_Destruct((Bbs *) block->bbs);
    func_020901a0(block->part_11c70);
    ShopDesigns_Destruct((ShopDesigns *) block->shop_designs);
    func_02061118(block->part_0f52c);
    func_02087164(&block->part_0f52b);
    func_020871c4(&block->part_0f52a);
    TownLayout_Destruct(block->layout);
    VillagerRoster_Destruct(villagers_of(block));
    PlayerRecords_DestructTown(block->players);
    func_020642f8(&block->town);
    return block;
}
CLEAN_AS(func_0209f1a8, StateBlock_Destruct)
