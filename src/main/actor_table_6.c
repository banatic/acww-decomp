/* actor_table_6: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02082ba0 @ 0x02082ba0, 0x1e bytes, Thumb
 * func_02082b80 @ 0x02082b80, 0x20 bytes, Thumb
 * func_02082b60 @ 0x02082b60, 0x20 bytes, Thumb
 * func_02082afc @ 0x02082afc, 0x62 bytes, Thumb
 * func_02082ab0 @ 0x02082ab0, 0x4c bytes, Thumb
 * func_02082a84 @ 0x02082a84, 0x2c bytes, Thumb
 * func_02082a44 @ 0x02082a44, 0x40 bytes, Thumb
 */

typedef struct {
    int unk_00;
    unsigned short unk_04;
} UnkStruct_02082b80;

struct UnkStruct_02082b60 {
    int unk_00;
    unsigned short unk_04;
};

struct Entry {
    int value;
    unsigned short extra;
};

struct Entry_02082a84 {
    int a;
    unsigned short b;
};

extern void func_020828e0(void *dst, void *src, int size);
extern int func_0204bcdc(void *a);
extern int func_0204bc64(void *a);

void func_02082b80(int unused, UnkStruct_02082b80 *ptr, int count);

void func_02082ba0(void *arg0)
{
    void *p = arg0;
    func_02082b80((int) p, (UnkStruct_02082b80 *) p, 8);
    func_020828e0(p, (char *) p + 0x40, 4);
}

void func_02082b80(int unused, UnkStruct_02082b80 *ptr, int count)
{
    int i;
    for (i = 0; i < count; i++) {
        ptr->unk_00 = 0;
        ptr->unk_04 = 0xfff1;
        ptr++;
    }
}

int func_02082b60(int unused, const struct UnkStruct_02082b60 *p)
{
    if (p->unk_00 != 0 && ((p->unk_04 & 0xf000) >> 12) == 0xe) {
        return 1;
    }
    return 0;
}

int func_02082afc(struct Entry *a, unsigned short *b)
{
    int i;
    int found = -1;
    for (i = 0; i < 8; i++) {
        struct Entry *e = &a[i];
        int match;
        if (func_0204bcdc(&e->extra) != 0) {
            match = (func_0204bc64(&e->extra) == func_0204bc64(b)) ? 1 : 0;
        } else {
            match = (e->extra == *b) ? 1 : 0;
        }
        if (match) {
            found = i;
            break;
        }
    }
    return found;
}

int func_02082ab0(struct Entry *a, int val, unsigned short *c)
{
    int flag = 0;
    if (func_02082afc(a, c) == -1) {
        unsigned short temp = 0xfff1;
        int index = func_02082afc(a, &temp);
        if (index >= 0 && index < 8) {
            a[index].value = val;
            a[index].extra = *c;
            flag = 1;
        }
    }
    return flag;
}

int func_02082a84(struct Entry_02082a84 *arr, unsigned short *argument1)
{
    int idx = func_02082afc((struct Entry *) arr, (unsigned short *) argument1);
    int ret = 0;
    if (idx >= 0 && idx < 8) {
        arr[idx].a = 0;
        arr[idx].b = 0xfff1;
        ret = 1;
    }
    return ret;
}

unsigned int func_02082a44(const void *table, unsigned short id)
{
    unsigned short key = 0xfff1;
    unsigned int result;
    int idx;

    result = 0;
    key = (unsigned short) ((id & 0x0fff) | 0xe000);
    idx = func_02082afc((struct Entry *) table, (unsigned short *) (&key));
    if (idx >= 0 && idx < 8) {
        result = ((unsigned int *) ((const char *) table + idx * 8))[0];
    }
    return result;
}
