/* func_ov068_0226c58c @ 0x0226c58c, 0xb0 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u16 id;
    u8 name[12];
    u8 pad_0E;
    u8 sex;
} Name;

extern u8 *func_020826a8(int i);
extern Name *func_0208150c(void *p);
extern int memcmp(const void *a, const void *b, int n);
extern int func_020ea990(void *a, void *b);
extern int func_0200322c(void *a, void *b);
extern int func_0201a824(int a, int b);
extern s16 data_020c80f0;

u8 *func_ov068_0226c58c(void *self, u8 *obj)
{
    u8 *pos;
    s16 lim;
    u8 *c;
    int i;
    Name *mine;
    Name *other;

    pos = obj + 0x5c;
    lim = data_020c80f0;
    for (i = 0; i < 8; i++) {
        c = func_020826a8(i);
        if (c == 0) {
            continue;
        }
        if (*(void **) (c + 0x830) == 0) {
            continue;
        }
        mine = func_0208150c(*(void **) (obj + 0x830));
        other = func_0208150c(*(void **) (c + 0x830));
        if (other->id == mine->id && memcmp(other->name, mine->name, 12) == 0 && other->sex == mine->sex) {
            continue;
        }
        if (func_020ea990(pos, c + 0x5c) >= 0x3000) {
            continue;
        }
        if (func_0201a824((s16) (func_0200322c(pos, c + 0x5c) - *(s16 *) (obj + 0x8e)), lim) == 0) {
            continue;
        }
        return c;
    }
    return 0;
}
