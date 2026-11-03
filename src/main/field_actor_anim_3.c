/* field_actor_anim_3: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02010f5c @ 0x02010f5c, 0x10 bytes, Thumb
 * func_02010f48 @ 0x02010f48, 0x14 bytes, Thumb
 * func_02010ef4 @ 0x02010ef4, 0x54 bytes, Thumb
 * func_02010ecc @ 0x02010ecc, 0x28 bytes, Thumb
 */

typedef struct {
    char pad_00[0x73c];
    char unk_73C;
    char pad_73D[0x770 - 0x73c - 1];
    int unk_770;
} UnkStruct_02010ecc;

extern void func_02054860(int arg);
extern int func_02056f28(void *ptr, int arg);
extern int func_020645e0(void *ptr);
extern void func_02056778(void *ptr);

void func_02010ef4(void *self);
void func_02010ecc(UnkStruct_02010ecc *p);

void func_02010f5c(int arg)
{
    func_02054860(arg + 0x234);
}

void func_02010f48(int a)
{
    func_02010ef4((void *) a);
    func_02010ecc((UnkStruct_02010ecc *) a);
}

void func_02010ef4(void *self)
{
    unsigned int field;

    field = *(unsigned int *) ((char *) self + 0x76c);
    if (field == 0x16f) {
        return;
    }
    if (field == 0) {
        if (func_02056f28((char *) self + 0x710, 0) == 0 || func_020645e0((char *) self + 0x768) != 0) {
            func_02056778((char *) self + 0x710);
        }
    } else {
        func_02056778((char *) self + 0x710);
        return;
    }
}

void func_02010ecc(UnkStruct_02010ecc *p)
{
    if (p->unk_770 != 0x16f) {
        func_02056778((void *) &p->unk_73C);
    }
}
