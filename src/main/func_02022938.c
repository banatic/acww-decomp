/* func_02022938 @ 0x02022938, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#define ITEM_NONE 0xfff1

typedef struct {
    u8 pad_00[0x830];
    u8 *name;
} Player;

typedef struct {
    u8 pad_00[0x100];
    Player *player;
} UnkStruct_02022938;

extern void func_0202e118(u16 *item, Player *player);
extern void func_02022bbc(UnkStruct_02022938 *self, int n, const void *data);
extern void func_0202bd40(UnkStruct_02022938 *self, int n, u8 *name);
extern const u8 data_020c8d28[];

static inline BOOL ItemIsNone(const u16 *item)
{
    return *item == ITEM_NONE;
}

static inline BOOL ItemIsSpecial(const u16 *item)
{
    return *item >= 0x1380 && *item <= 0x139f;
}

int func_02022938(UnkStruct_02022938 *self)
{
    u16 item;

    func_0202e118(&item, self->player);
    if (ItemIsNone(&item) || ItemIsSpecial(&item)) {
        func_02022bbc(self, 3, data_020c8d28);
        func_0202bd40(self, 5, self->player->name);
        return 1;
    }
    return 0;
}
