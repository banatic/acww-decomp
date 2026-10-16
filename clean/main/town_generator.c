/* The generator of a new town's acres (town_generator.h). */
#include "town_generator.h"

#include "acre_kind.h"
#include "clean.h"

/* The kind a new cell has, and the one past the last valid kind. */
#define TOWN_GENERATOR_KIND_NONE ACRE_KIND_LAST
/* The kind of the acres the special acres are put on. */
#define TOWN_GENERATOR_KIND_PLAIN 9
/* The flags an acre to upgrade must not have, and the flag added to it. */
#define TOWN_GENERATOR_NO_UPGRADE_FLAGS 0x8000c
#define TOWN_GENERATOR_UPGRADE_FLAG 0x100
/* The model an acre gets when no model has its kind. */
#define TOWN_GENERATOR_MODEL_FALLBACK 0x14
/* The candidates' file: 524 records of 16 bytes. */
#define TOWN_GENERATOR_CANDIDATES 524
#define TOWN_GENERATOR_CANDIDATE_SIZE 0x10
#define TOWN_GENERATOR_LISTED_MODELS 6
/* The most the models' files may add up to. */
#define TOWN_GENERATOR_MAX_FILES_SIZE 0x1ffb8u

static_assert(sizeof(TownGeneratorCell) == 8, "TownGeneratorCell is 8 bytes");
static_assert(offsetof(TownGenerator, candidates) == 0x120, "the candidates follow the cells");

extern void __register_global_object(void *object, void *destruct, void *record);
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void MI_CpuFill8(void *dst, u8 value, u32 size);
extern u32 func_020644cc(int range);                              /* a random number below `range` */
extern int func_02064328(char *buffer, const char *format, ...);  /* sprintf */
extern int func_0206487c(const char *path);                       /* a file's size */
extern char *func_0206e7bc(RecordFile *file, unsigned int entry); /* a record, NULL when unread */
extern void func_0206e808(RecordFile *file);                      /* closes the file */
extern void func_0206e854(RecordFile *file);                      /* reads all its records */
extern int func_0206e890(RecordFile *file, const char *path, int record_size, int records);
extern int func_0206e8b4(RecordFile *file);  /* its destructor */
extern void func_0206e8c4(RecordFile *file); /* its constructor */
/* The cells' destructor (nothing) and constructor, handed to the C++ runtime. */
extern void func_0209d038(void *cell);
extern void func_0209d03c(void *cell);

/* What TownGenerator_PlaceSpecials puts kind 0xb next to (1-4); others put it on row 3. */
extern unsigned int data_020e35d4;
/* The number of the candidate drawn last. */
extern int data_021dc580;
/* The cell TownGenerator_Cell answers outside the grid, built on first use, with its guard and
 * its record for destruction. */
extern u32 data_021dc584;
extern TownGeneratorCell data_021dc58c;
extern u8 data_021dc594[];
/* The four neighbours TownGenerator_PlaceBeside tries, built on first use, and their guard. */
extern u32 data_021dc588;
extern s16 data_021dc5a0[4][2];
/* The six models of which the town must use one. */
extern const s32 data_020d1ac0[TOWN_GENERATOR_LISTED_MODELS];
extern const char data_020e35d8[]; /* "/bg/a%d/%04x.arc" */
extern const char data_020e35ec[]; /* "/bg/rndCand.bin" */

static int town_generator_kind_at(TownGenerator *generator, unsigned int x, unsigned int z)
{
    return TownGenerator_Kind(TownGenerator_Cell(generator, x, z));
}

static void town_generator_set_kind_at(TownGenerator *generator, unsigned int x, unsigned int z, int kind)
{
    TownGenerator_SetKind(TownGenerator_Cell(generator, x, z), kind);
}

/* func_0209c574: lays a new town's acres out and writes their 36 model numbers to `layout`. */
void TownGenerator_LayOut(void *layout)
{
    TownGenerator generator;

    TownGenerator_Construct(&generator);
    TownGenerator_Generate(&generator, (int) data_020e35d4);
    TownGenerator_WriteModels(&generator, layout);
    TownGenerator_Destruct(&generator);
}
CLEAN_AS(func_0209c574, TownGenerator_LayOut)

/* func_0209c5a4 */
void TownGenerator_SetSpecialChoice(unsigned int choice)
{
    data_020e35d4 = choice;
}
CLEAN_AS(func_0209c5a4, TownGenerator_SetSpecialChoice)

/* func_0209c5b0: the inner acres' kinds from candidate `number` (modulo 524), or from one drawn at
 * random for a negative number; its number kept in data_021dc580. Nothing when the record cannot
 * be read. */
void TownGenerator_PickCandidate(TownGenerator *generator, int number)
{
    int candidate;
    if (number < 0) {
        candidate = (int) func_020644cc(TOWN_GENERATOR_CANDIDATES);
    } else {
        candidate = (int) ((unsigned int) number % TOWN_GENERATOR_CANDIDATES);
    }
    data_021dc580 = candidate;

    const u8 *kinds = (const u8 *) func_0206e7bc(&generator->candidates, (unsigned int) candidate);
    if (kinds == NULL) {
        return;
    }
    for (unsigned int z = 1; z < 5; z++) {
        for (unsigned int x = 1; x < 5; x++) {
            TownGenerator_SetKind(TownGenerator_Cell(generator, x, z), *kinds++);
        }
    }
}
CLEAN_AS(func_0209c5b0, TownGenerator_PickCandidate)

/* func_0209c618: the border acres: the top row 7, 0, 0, 0, 0, 8 (kind 2 over any inner acre of
 * kind 0x14), the bottom row 0x35, the left column 3 (4 at the bottom) and the right one 5 (6 at
 * the bottom). Then one of the inner acres (2, 1) and (3, 1) whose kind has none of the flags
 * 0x1000-0x40000, drawn at random, turned to kind 0xa with kind 1 above it. Whether there was one.
 * QUIRK: func_020644cc is still called, with a range of 0, when there is none. */
int TownGenerator_PlaceBorders(TownGenerator *generator)
{
    static const u8 top[TOWN_GENERATOR_SIDE] = {7, 0, 0, 0, 0, 8};
    for (unsigned int x = 0; x < TOWN_GENERATOR_SIDE; x++) {
        town_generator_set_kind_at(generator, x, 0, top[x]);
    }
    for (unsigned int x = 0; x < TOWN_GENERATOR_SIDE; x++) {
        town_generator_set_kind_at(generator, x, 5, 0x35);
    }
    for (unsigned int z = 1; z < 5; z++) {
        town_generator_set_kind_at(generator, 0, z, z == 4 ? 4 : 3);
    }
    for (unsigned int z = 1; z < 5; z++) {
        town_generator_set_kind_at(generator, 5, z, z == 4 ? 6 : 5);
    }

    for (unsigned int x = 1; x < 5; x++) {
        if (town_generator_kind_at(generator, x, 1) == 0x14) {
            town_generator_set_kind_at(generator, x, 0, 2);
        }
    }

    u32 count = 0;
    for (unsigned int x = 2; x <= 3; x++) {
        if (AcreKind_CountFlags1000(town_generator_kind_at(generator, x, 1)) == 0) {
            count++;
        }
    }
    u32 pick = func_020644cc((int) count);
    u32 seen = 0;
    for (unsigned int x = 2; x <= 3; x++) {
        if (AcreKind_CountFlags1000(town_generator_kind_at(generator, x, 1)) == 0) {
            if (seen == pick) {
                town_generator_set_kind_at(generator, x, 0, 1);
                town_generator_set_kind_at(generator, x, 1, 0xa);
                return 1;
            }
            seen++;
        }
    }
    return 0;
}
CLEAN_AS(func_0209c618, TownGenerator_PlaceBorders)

/* Whether an inner acre of kind `kind` may be upgraded: none of the flags 8, 4 and 0x80000, and
 * exactly one of 0x1000-0x40000. */
static int town_generator_can_upgrade(int kind)
{
    return (AcreKind_Flags(kind) & TOWN_GENERATOR_NO_UPGRADE_FLAGS) == 0 && AcreKind_CountFlags1000(kind) == 1;
}

/* func_0209c80c: one of the inner acres that may be upgraded, drawn at random, turned to its
 * upgraded kind (TownGenerator_UpgradedKind). Whether it changed: 0 when there is no such acre or
 * the drawn one has no upgraded kind. */
int TownGenerator_UpgradeOne(TownGenerator *generator)
{
    int count = 0;
    for (unsigned int z = 1; z < 5; z++) {
        for (unsigned int x = 1; x < 5; x++) {
            if (town_generator_can_upgrade(town_generator_kind_at(generator, x, z))) {
                count++;
            }
        }
    }
    if (count == 0) {
        return 0;
    }

    int pick = (int) func_020644cc(count);
    int seen = 0;
    for (unsigned int z = 1; z < 5; z++) {
        for (unsigned int x = 1; x < 5; x++) {
            if (!town_generator_can_upgrade(town_generator_kind_at(generator, x, z))) {
                continue;
            }
            if (pick == seen) {
                int upgraded = TownGenerator_UpgradedKind(town_generator_kind_at(generator, x, z));
                if (upgraded != town_generator_kind_at(generator, x, z)) {
                    town_generator_set_kind_at(generator, x, z, upgraded);
                    return 1;
                }
            }
            seen++;
        }
    }
    return 0;
}
CLEAN_AS(func_0209c80c, TownGenerator_UpgradeOne)

/* func_0209c988: kinds 0xe, 0xd and 0xc each put on an inner acre of kind 9 (stopping at the
 * first that finds none), then kind 0xb put next to the acre of kind 0xd, 0xe, 0xa or 0xc for
 * `choice` 1-4, else on one of the inner acres of row 3 of kind 9. Whether all were put. */
int TownGenerator_PlaceSpecials(TownGenerator *generator, int choice)
{
    if (TownGenerator_PlaceOnPlain(generator, 0xe) == 0) {
        return 0;
    }
    if (TownGenerator_PlaceOnPlain(generator, 0xd) == 0) {
        return 0;
    }
    if (TownGenerator_PlaceOnPlain(generator, 0xc) == 0) {
        return 0;
    }

    switch (choice) {
        case 1:
            return TownGenerator_PlaceBeside(generator, 0xd, 0xb);
        case 2:
            return TownGenerator_PlaceBeside(generator, 0xe, 0xb);
        case 3:
            return TownGenerator_PlaceBeside(generator, 0xa, 0xb);
        case 4:
            return TownGenerator_PlaceBeside(generator, 0xc, 0xb);
        default:
            break;
    }

    int count = 0;
    for (unsigned int x = 1; x < 5; x++) {
        if (town_generator_kind_at(generator, x, 3) == TOWN_GENERATOR_KIND_PLAIN) {
            count++;
        }
    }
    if (count == 0) {
        return 0;
    }
    int pick = (int) func_020644cc(count);
    int seen = 0;
    for (unsigned int x = 1; x < 5; x++) {
        if (town_generator_kind_at(generator, x, 3) == TOWN_GENERATOR_KIND_PLAIN) {
            if (pick == seen) {
                town_generator_set_kind_at(generator, x, 3, 0xb);
                return 1;
            }
            seen++;
        }
    }
    return 0;
}
CLEAN_AS(func_0209c988, TownGenerator_PlaceSpecials)

/* func_0209ca6c: kind `kind` put on one of the acres of kind 9 next to (left, right, below or
 * above) the first inner acre, row by row, of kind `beside`, drawn at random. Whether it was put.
 * QUIRK: the four neighbours are a function-local static table, built (without registration for
 * destruction) on the first call that finds the acre. */
int TownGenerator_PlaceBeside(TownGenerator *generator, int beside, int kind)
{
    unsigned int x = 1;
    unsigned int z;
    int found = 0;

    for (z = 1; z < 5; z++) {
        for (x = 1; x < 5; x++) {
            if (beside == town_generator_kind_at(generator, x, z)) {
                found = 1;
                break;
            }
        }
        if (found) {
            break;
        }
    }
    if (!found) {
        return 0;
    }

    if ((data_021dc588 & 1) == 0) {
        static const s16 neighbours[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
        for (int i = 0; i < 4; i++) {
            data_021dc5a0[i][0] = neighbours[i][0];
            data_021dc5a0[i][1] = neighbours[i][1];
        }
        data_021dc588 |= 1;
    }

    int count = 0;
    for (int i = 0; i < 4; i++) {
        unsigned int nx = x + (unsigned int) data_021dc5a0[i][0];
        unsigned int nz = z + (unsigned int) data_021dc5a0[i][1];
        if (town_generator_kind_at(generator, nx, nz) == TOWN_GENERATOR_KIND_PLAIN) {
            count++;
        }
    }
    if (count == 0) {
        return 0;
    }
    int pick = (int) func_020644cc(count);
    int seen = 0;
    for (int i = 0; i < 4; i++) {
        unsigned int nx = x + (unsigned int) data_021dc5a0[i][0];
        unsigned int nz = z + (unsigned int) data_021dc5a0[i][1];
        if (town_generator_kind_at(generator, nx, nz) == TOWN_GENERATOR_KIND_PLAIN) {
            if (pick == seen) {
                nx = x + (unsigned int) data_021dc5a0[i][0];
                nz = z + (unsigned int) data_021dc5a0[i][1];
                town_generator_set_kind_at(generator, nx, nz, kind);
                return 1;
            }
            seen++;
        }
    }
    return 0;
}
CLEAN_AS(func_0209ca6c, TownGenerator_PlaceBeside)

/* func_0209cb88: kind `kind` put on one of the inner acres of kind 9, drawn at random. Whether it
 * was put.
 * QUIRK: func_020644cc is still called, with a range of 0, when there is none. */
int TownGenerator_PlaceOnPlain(TownGenerator *generator, int kind)
{
    u32 count = 0;
    for (unsigned int z = 1; z < 5; z++) {
        for (unsigned int x = 1; x < 5; x++) {
            if (town_generator_kind_at(generator, x, z) == TOWN_GENERATOR_KIND_PLAIN) {
                count++;
            }
        }
    }

    u32 pick = func_020644cc((int) count);
    u32 seen = 0;
    for (unsigned int z = 1; z < 5; z++) {
        for (unsigned int x = 1; x < 5; x++) {
            if (town_generator_kind_at(generator, x, z) == TOWN_GENERATOR_KIND_PLAIN) {
                if (pick == seen) {
                    town_generator_set_kind_at(generator, x, z, kind);
                    return 1;
                }
                seen++;
            }
        }
    }
    return 0;
}
CLEAN_AS(func_0209cb88, TownGenerator_PlaceOnPlain)

/* func_0209cc10: the kind whose flags are those of `kind` with 0x100 added; `kind` itself when
 * there is none. */
int TownGenerator_UpgradedKind(int kind)
{
    int upgraded = AcreKind_Find(AcreKind_Flags(kind) | TOWN_GENERATOR_UPGRADE_FLAG);
    if (upgraded == ACRE_KIND_LAST) {
        return kind;
    }
    return upgraded;
}
CLEAN_AS(func_0209cc10, TownGenerator_UpgradedKind)

/* func_0209cc30: the cell of acre (x, z); outside the grid, a shared cell (kind 0x36, model 0
 * when built) that the callers may also write. */
TownGeneratorCell *TownGenerator_Cell(TownGenerator *generator, unsigned int x, unsigned int z)
{
    unsigned int index = (unsigned int) (uintptr_t) TownGenerator_CellIndex((unsigned char *) (uintptr_t) x, (int) z);
    if (index < TOWN_GENERATOR_CELLS) {
        return &generator->cells[index];
    }
    if ((data_021dc584 & 1) == 0) {
        TownGenerator_ConstructCell(&data_021dc58c);
        __register_global_object(&data_021dc58c, (void *) func_0209d038, data_021dc594);
        data_021dc584 |= 1;
    }
    return &data_021dc58c;
}
CLEAN_AS(func_0209cc30, TownGenerator_Cell)

/* func_0209cc84: whether an inner acre's model is one of the six of data_020d1ac0. */
int TownGenerator_HasListedModel(TownGenerator *generator)
{
    for (unsigned int z = 1; z < 5; z++) {
        for (unsigned int x = 1; x < 5; x++) {
            for (int i = 0; i < TOWN_GENERATOR_LISTED_MODELS; i++) {
                if (data_020d1ac0[i] == TownGenerator_Model(TownGenerator_Cell(generator, x, z))) {
                    return 1;
                }
            }
        }
    }
    return 0;
}
CLEAN_AS(func_0209cc84, TownGenerator_HasListedModel)

/* The model number `index` (from 0) among those of kind `kind` not yet in `used` (or all of
 * them without `unused_only`). */
static unsigned int town_generator_nth_model(int kind, const u8 *used, int unused_only, u32 index)
{
    u32 seen = 0;
    for (unsigned int model = 0; model < TOWN_GENERATOR_MODELS; model++) {
        if (kind == AcreKind_OfModel(model) && (!unused_only || used[model] == 0)) {
            if (seen == index) {
                return model;
            }
            seen++;
        }
    }
    return 0; /* not reached: the index is below the count */
}

/* The number of model numbers of kind `kind` not yet in `used` (or all of them without
 * `unused_only`). */
static u32 town_generator_count_models(int kind, const u8 *used, int unused_only)
{
    u32 count = 0;
    for (unsigned int model = 0; model < TOWN_GENERATOR_MODELS; model++) {
        if (kind == AcreKind_OfModel(model) && (!unused_only || used[model] == 0)) {
            count++;
        }
    }
    return count;
}

/* func_0209ccd4: each acre given a model of its kind drawn at random, one not given to another
 * acre while there is one. An acre whose kind no model has gets model 0x14, and then the result
 * is 0; else 1. */
int TownGenerator_AssignModels(TownGenerator *generator)
{
    int result = 1;
    u8 used[TOWN_GENERATOR_MODELS];

    MI_CpuFill8(used, 0, sizeof(used));
    for (unsigned int z = 0; z < TOWN_GENERATOR_SIDE; z++) {
        for (unsigned int x = 0; x < TOWN_GENERATOR_SIDE; x++) {
            int kind = town_generator_kind_at(generator, x, z);
            int unused_only = 1;
            u32 count = town_generator_count_models(kind, used, unused_only);
            if (count == 0) {
                unused_only = 0;
                count = town_generator_count_models(kind, used, unused_only);
            }
            if (count == 0) {
                result = 0;
                TownGenerator_SetModel(TownGenerator_Cell(generator, x, z), TOWN_GENERATOR_MODEL_FALLBACK);
                continue;
            }
            u32 pick = func_020644cc((int) count);
            unsigned int model = town_generator_nth_model(kind, used, unused_only, pick);
            TownGenerator_SetModel(TownGenerator_Cell(generator, x, z), (int) model);
            used[model] = 1;
        }
    }
    return result;
}
CLEAN_AS(func_0209ccd4, TownGenerator_AssignModels)

/* func_0209ce00: the 36 model numbers written to `models`, row by row. */
void TownGenerator_WriteModels(TownGenerator *generator, unsigned char *models)
{
    for (unsigned int z = 0; z < TOWN_GENERATOR_SIDE; z++) {
        for (unsigned int x = 0; x < TOWN_GENERATOR_SIDE; x++) {
            *models++ = (u8) TownGenerator_Model(TownGenerator_Cell(generator, x, z));
        }
    }
}
CLEAN_AS(func_0209ce00, TownGenerator_WriteModels)

/* func_0209ce34: the sizes of the files "/bg/a<model / 16>/<model, 4 hex digits>.arc" of the
 * distinct models of the acres, added up.
 * REQUIRES: every model below 0x86 (TownGenerator_AssignModels gives no other). */
int TownGenerator_ModelFilesSize(TownGenerator *generator)
{
    u8 counted[TOWN_GENERATOR_MODELS];
    char path[30];
    u32 size = 0;

    MI_CpuFill8(counted, 0, sizeof(counted));
    for (unsigned int z = 0; z < TOWN_GENERATOR_SIDE; z++) {
        for (unsigned int x = 0; x < TOWN_GENERATOR_SIDE; x++) {
            if (counted[TownGenerator_Model(TownGenerator_Cell(generator, x, z))] != 0) {
                continue;
            }
            int model = TownGenerator_Model(TownGenerator_Cell(generator, x, z));
            func_02064328(path, data_020e35d8, model >> 4, model);
            size += (u32) func_0206487c(path);
            counted[TownGenerator_Model(TownGenerator_Cell(generator, x, z))] = 1;
        }
    }
    return (int) size;
}
CLEAN_AS(func_0209ce34, TownGenerator_ModelFilesSize)

/* func_0209cec0: makes a layout (see town_generator.h), with the candidates' file open
 * meanwhile; `choice` as for TownGenerator_PlaceSpecials. Always 1. */
int TownGenerator_Generate(TownGenerator *generator, int choice)
{
    int done = 0;

    TownGenerator_OpenCandidates(generator);
    while (!done) {
        TownGenerator_PickCandidate(generator, -1);
        /* Each step runs even after one before it failed. */
        done = TownGenerator_PlaceBorders(generator) & 1;
        done = (done & TownGenerator_UpgradeOne(generator)) != 0;
        done = (done & TownGenerator_PlaceSpecials(generator, choice)) != 0;
        if (!done) {
            continue;
        }
        int models_done = 0;
        while (!models_done) {
            models_done = TownGenerator_AssignModels(generator) & 1;
            models_done = (models_done & TownGenerator_HasListedModel(generator)) != 0;
            if ((unsigned int) TownGenerator_ModelFilesSize(generator) > TOWN_GENERATOR_MAX_FILES_SIZE) {
                done = 0;
            }
        }
    }
    TownGenerator_CloseCandidates(generator);
    return 1;
}
CLEAN_AS(func_0209cec0, TownGenerator_Generate)

/* func_0209cf70 */
void TownGenerator_CloseCandidates(TownGenerator *generator)
{
    func_0206e808(&generator->candidates);
}
CLEAN_AS(func_0209cf70, TownGenerator_CloseCandidates)

/* func_0209cf80: opens "/bg/rndCand.bin" and reads its 524 candidates; whether it opened. */
int TownGenerator_OpenCandidates(TownGenerator *generator)
{
    if (func_0206e890(&generator->candidates, data_020e35ec, TOWN_GENERATOR_CANDIDATE_SIZE, TOWN_GENERATOR_CANDIDATES)) {
        func_0206e854(&generator->candidates);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_0209cf80, TownGenerator_OpenCandidates)

/* func_0209cfb8: the generator's destructor. */
TownGenerator *TownGenerator_Destruct(TownGenerator *generator)
{
    func_0206e8b4(&generator->candidates);
    __cxa_vec_cleanup(generator->cells, TOWN_GENERATOR_CELLS, sizeof(TownGeneratorCell), func_0209d038);
    return generator;
}
CLEAN_AS(func_0209cfb8, TownGenerator_Destruct)

/* func_0209cfe0: the generator's constructor: every cell new (kind 0x36, model 0). */
TownGenerator *TownGenerator_Construct(TownGenerator *generator)
{
    __cxa_vec_ctor(generator->cells, TOWN_GENERATOR_CELLS, sizeof(TownGeneratorCell), func_0209d03c, func_0209d038);
    func_0206e8c4(&generator->candidates);
    return generator;
}
CLEAN_AS(func_0209cfe0, TownGenerator_Construct)

/* func_0209d014: the index of acre (x, z) in the grid, x + 6 z.
 * QUIRK: it is computed as a pointer: x arrives as one and the index is returned as one. */
void *TownGenerator_CellIndex(unsigned char *x, int z)
{
    return (void *) ((uintptr_t) x + (uintptr_t) (unsigned int) z * TOWN_GENERATOR_SIDE);
}
CLEAN_AS(func_0209d014, TownGenerator_CellIndex)

/* func_0209d01c: the cell's kind set, unless `kind` is past the last kind; whether it was. */
int TownGenerator_SetKind(TownGeneratorCell *cell, int kind)
{
    if (kind < ACRE_KINDS) {
        cell->kind = kind;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_0209d01c, TownGenerator_SetKind)

/* func_0209d02c */
void TownGenerator_SetModel(TownGeneratorCell *cell, int model)
{
    cell->model = model;
}
CLEAN_AS(func_0209d02c, TownGenerator_SetModel)

/* func_0209d030 */
int TownGenerator_Kind(TownGeneratorCell *cell)
{
    return cell->kind;
}
CLEAN_AS(func_0209d030, TownGenerator_Kind)

/* func_0209d034 */
int TownGenerator_Model(TownGeneratorCell *cell)
{
    return cell->model;
}
CLEAN_AS(func_0209d034, TownGenerator_Model)

/* func_0209d038: a cell's destructor: nothing. */
void TownGenerator_DestructCell(void *cell)
{
    (void) cell;
}
CLEAN_AS(func_0209d038, TownGenerator_DestructCell)

/* func_0209d03c: a cell's constructor: kind 0x36, model 0. */
void TownGenerator_ConstructCell(TownGeneratorCell *cell)
{
    cell->kind = TOWN_GENERATOR_KIND_NONE;
    cell->model = 0;
}
CLEAN_AS(func_0209d03c, TownGenerator_ConstructCell)

/* func_0209d048: whether `model` is one of the six of data_020d1ac0. */
int TownGenerator_IsListedModel(int model)
{
    for (int i = 0; i < TOWN_GENERATOR_LISTED_MODELS; i++) {
        if (data_020d1ac0[i] == model) {
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_0209d048, TownGenerator_IsListedModel)
