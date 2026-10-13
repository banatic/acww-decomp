/* func_02034fac @ 0x02034fac, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02037458(void *);

typedef struct UnkStruct_02034fac {
    unsigned char unk_00[0x11];
    unsigned char unk_11;
    unsigned char pad_12;
    unsigned char flag_0x13;
    unsigned char rest[0x08];
} UnkStruct_02034fac;

typedef struct {
    UnkStruct_02034fac elements[16];
    int count;
} Container;

void func_02034fac(Container *c)
{
    int n = c->count;
    UnkStruct_02034fac *end = (UnkStruct_02034fac *) ((char *) c + n * sizeof(UnkStruct_02034fac));
    UnkStruct_02034fac *e;

    for (e = (UnkStruct_02034fac *) c; e < end; e++) {
        if (func_02037458(e) != 0) {
            e->flag_0x13 = 1;
        }
        if (e != (UnkStruct_02034fac *) c && e->unk_11 != 0) {
            e->flag_0x13 = 1;
        }
    }
}
