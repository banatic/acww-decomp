/* The search for the nearest sound mark (sound_mark.h). */
#include "sound_mark.h"

#include "clean.h"
#include "main/acre_map.h"
#include "main/acre_record.h"
#include "main/bg_models.h"

static_assert(offsetof(SoundMarkSearch, position) == 0x04, "position");
static_assert(offsetof(SoundMarkSearch, distance) == 0x10, "distance");
static_assert(offsetof(SoundMarkSearch, kind) == 0x14, "kind");
static_assert(sizeof(SoundMarkSearch) == 0x18, "search");
static_assert(sizeof(AcreRecord) == ACRE_MAP_ACRE_SIZE, "acre record");

/* An acre's coordinate from a position, and back: acres are 32.0 units (1 << 17) wide. */
#define SOUND_MARK_ACRE_SHIFT 17
/* How far a mark may be at most to begin with, in acres' widths. */
#define SOUND_MARK_FIRST_REACH 8

/* The scene's map of acres. */
extern AcreMap *data_021c80bc;
/* An acre's width in world units (32.0). */
extern int data_020ca0ec;

/* func_ov003_0221ef90: the kind of the nearest mark. */
int SoundMark_Kind(SoundMarkSearch *search)
{
    return search->kind;
}
CLEAN_AS(func_ov003_0221ef90, SoundMark_Kind)

/* func_ov003_0221ef94: where the nearest mark is, NULL when none was found. */
Vec3 *SoundMark_Position(SoundMarkSearch *search)
{
    if (search->found) {
        return &search->position;
    }
    return NULL;
}
CLEAN_AS(func_ov003_0221ef94, SoundMark_Position)

/* func_ov003_0221efa4: nothing found yet, kind SOUND_MARK_KIND_11, and only marks closer than
 * 8 acres' width taken. */
void SoundMark_Init(SoundMarkSearch *search)
{
    search->found = 0;
    search->position.x = 0;
    search->position.y = 0;
    search->position.z = 0;
    search->kind = SOUND_MARK_KIND_11;
    search->distance = data_020ca0ec * SOUND_MARK_FIRST_REACH;
}
CLEAN_AS(func_ov003_0221efa4, SoundMark_Init)

/* func_ov003_0221efc0: the search's destructor, which does nothing. */
void SoundMark_Destruct(SoundMarkSearch *search)
{
    (void) search;
}
CLEAN_AS(func_ov003_0221efc0, SoundMark_Destruct)

/* func_ov003_0221efc4: a mark of `kind` at `position`, `distance` away, is kept when it is
 * closer than the one kept (1), else left (0). */
int SoundMark_Offer(SoundMarkSearch *search, int distance, const Vec3 *position, int kind)
{
    if (distance < search->distance) {
        search->position.x = position->x;
        search->position.y = position->y;
        search->position.z = position->z;
        search->distance = distance;
        search->kind = kind;
        search->found = 1;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov003_0221efc4, SoundMark_Offer)

/* func_ov003_0221efec: searches the marks of the acre of `point` and of the eight around it,
 * row by row along z, for the nearest of the kinds looked at; returns `search`.
 * QUIRK: an acre's corner is its coordinates times 32.0 here, whatever data_020ca0ec says. */
SoundMarkSearch *SoundMark_FindNearest(SoundMarkSearch *search, const Vec3 *point)
{
    SoundMark_Init(search);
    int acre_x = point->x >> SOUND_MARK_ACRE_SHIFT;
    int acre_z = point->z >> SOUND_MARK_ACRE_SHIFT;

    for (int dz = -1; dz <= 1; dz++) {
        for (int dx = -1; dx <= 1; dx++) {
            int x = acre_x + dx;
            int z = acre_z + dz;
            fx32 corner_x = (fx32) ((u32) x << SOUND_MARK_ACRE_SHIFT);
            fx32 corner_z = (fx32) ((u32) z << SOUND_MARK_ACRE_SHIFT);
            const u8 *marks = (const u8 *) (uintptr_t) (u32) SoundMark_AcreFile(search, (unsigned int) x, (unsigned int) z);
            if (marks == NULL) {
                continue;
            }
            unsigned int count = (unsigned int) BgModels_MarkCount((const s16 *) (const void *) marks);
            for (unsigned int i = 0; i < count; i++) {
                BgMark mark;
                BgModels_MarkAt(&mark, marks, (int) i);
                switch (mark.kind) {
                    case SOUND_MARK_KIND_5:
                    case SOUND_MARK_KIND_F:
                    case SOUND_MARK_KIND_11:
                    case SOUND_MARK_KIND_12: {
                        Vec3 at;
                        at.x = corner_x + mark.x;
                        at.y = 0;
                        at.z = corner_z + mark.z;
                        int distance = Vec_DistanceXZ(&at, point);
                        SoundMark_Offer(search, distance, &at, mark.kind);
                        break;
                    }
                    default:
                        break;
                }
            }
        }
    }
    return search;
}
CLEAN_AS(func_ov003_0221efec, SoundMark_FindNearest)

/* func_ov003_0221f0b8: the "bsd0" file of the background model of acre (x, z), 0 when there is
 * no such acre or model. */
int SoundMark_AcreFile(SoundMarkSearch *search, unsigned int x, unsigned int z)
{
    const BgModel *model = (const BgModel *) (uintptr_t) (u32) SoundMark_AcreBgModel((int) (uintptr_t) search, x, z);
    if (model != NULL) {
        return (int) (uintptr_t) model->bsd;
    }
    return 0;
}
CLEAN_AS(func_ov003_0221f0b8, SoundMark_AcreFile)

/* func_ov003_0221f0d0: the background model of acre (x, z) of the scene's map, 0 when there is
 * no map, no such acre or no model. */
int SoundMark_AcreBgModel(int unused, unsigned int x, unsigned int z)
{
    (void) unused;
    const AcreMap *map = data_021c80bc;
    if (map != NULL) {
        const AcreRecord *acre = NULL;
        if (x < (unsigned int) map->acres_wide && z < (unsigned int) map->acres_high && map->acres != NULL) {
            acre = (const AcreRecord *) (const void *) (map->acres +
                                                        (z * (unsigned int) map->acres_wide + x) * ACRE_MAP_ACRE_SIZE);
        }
        if (acre != NULL) {
            return (int) (uintptr_t) acre->bg_model;
        }
    }
    return 0;
}
CLEAN_AS(func_ov003_0221f0d0, SoundMark_AcreBgModel)
