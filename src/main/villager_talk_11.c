/* villager_talk_11: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0201e834 @ 0x0201e834, 0x8 bytes, Thumb
 * func_0201e7b8 @ 0x0201e7b8, 0x7c bytes, Thumb
 */

typedef struct {
    char pad_00[0x40];
    int unk_40;
} UnkStruct_0201e7b8_2;

typedef struct {
    char pad_00[0x20];
    unsigned char unk_20;
    unsigned char unk_21;
    char pad_22[2];
} UnkStruct_0201e7b8;

typedef struct {
    int a, b;
} Pair;

extern void func_0202a5e8(void *, void *);
extern int func_020644cc(int);
extern void func_0201cf74(UnkStruct_0201e7b8_2 *, UnkStruct_0201e7b8 *, int, void *, void *);
extern void func_0201cec8(UnkStruct_0201e7b8_2 *, UnkStruct_0201e7b8 *);
extern void func_0202da74(UnkStruct_0201e7b8_2 *, Pair);
extern void func_02068388(int, int);
extern int data_021c1e14;
extern int data_021c23c4;
extern int data_020c8928;
extern int data_020c8924;
extern int data_021c1d6c;
extern const Pair data_020d9358;

void func_0201e834(void *argument0, void *argument1)
{
    func_0202a5e8((void *) argument0, (void *) argument1);
}

void func_0201e7b8(UnkStruct_0201e7b8_2 *obj)
{
    UnkStruct_0201e7b8 s;
    void *p = &data_021c1e14;
    if ((func_020644cc(10) & 1) == 0) {
        p = &data_021c23c4;
    }
    func_0201cf74(obj, &s, 0, &data_020c8928, p);
    func_0201cf74(obj, &s, 1, &data_020c8924, &data_021c1d6c);
    s.unk_20 = 2;
    s.unk_21 = s.unk_20 - 1;
    func_0201cec8(obj, &s);
    func_0202da74(obj, data_020d9358);
    func_02068388(obj->unk_40, 1);
}
