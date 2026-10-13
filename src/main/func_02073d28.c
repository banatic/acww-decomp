/* func_02073d28 @ 0x02073d28, 0x3a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[8];
    char *base;
    char pad_0C[0x64 - 0xc];
    int limit;
} UnkStruct_02073d28;

extern int func_02073918(UnkStruct_02073d28 *p, int idx);

char *func_02073d28(UnkStruct_02073d28 *p, int idx)
{
    if (idx >= 4) {
        return p->base;
    }
    if (func_02073918(p, idx) != 0) {
        return 0;
    }
    if (idx < p->limit) {
        return p->base + (idx << 12);
    }
    return p->base + ((idx - 1) << 12);
}
