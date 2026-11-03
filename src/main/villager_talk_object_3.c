/* villager_talk_object_3: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02025148 @ 0x02025148, 0x88 bytes, Thumb
 * func_020250c8 @ 0x020250c8, 0x80 bytes, Thumb
 * func_02024fe4 @ 0x02024fe4, 0xe4 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int a;
    unsigned char b;
} Config;

typedef struct {
    int unk_00;
    int unk_04;
} Pair;

typedef struct {
    char pad_00[0xc8];
    Pair unk_C8;
    char pad_D0[0x30];
    void *unk_100;
    char buf[30];
    unsigned char unk_122;
} UnkStruct_02025148;

typedef struct {
    void *ptr;
    unsigned char byte;
} UnkStruct_02025148_2;

typedef struct Entry Entry;

struct Entry {
    unsigned char pad_00[0x830];
    void *unk_830;
};

typedef struct UnkStruct_020250c8 {
    unsigned char pad_00[0x100];
    Entry *unk_100;
    unsigned char pad_104[0x20];
    char unk_124[0x40];
    void *unk_164;
} UnkStruct_020250c8;

struct UnkStruct_02024fe4_2 {
    unsigned char pad_00[0x164];
    void *unk_164;
};

struct UnkStruct_02024fe4 {
    int a;
    int b;
};

extern unsigned int func_0202d9c4(unsigned int *);
extern int func_0209bc40(unsigned char *);
extern unsigned int func_0208150c(int);
extern int func_020036e8(unsigned char *);
extern int func_0202da38(void *, char *, char *, int, int, int, int, int, int);
extern Config data_020c8d08;
extern Config data_020c8d20;
extern Pair data_020d8f18;
extern int func_0204bcdc(void *p);
extern int func_02080834(void *a, void *b);
extern int func_0209b69c(void *a, unsigned char b);
extern void func_0207860c(void *a, unsigned char b);
extern void func_0209bb90(int a, int b);
extern void func_02078648(void *a, int b);
extern int func_0207f270(void *a);
extern void func_02079478(int a);
extern struct UnkStruct_02024fe4 data_020d8f10;
extern struct UnkStruct_02024fe4 data_020d8e80;
extern struct UnkStruct_02024fe4 data_020d9050;
extern u32 func_0209b914(void *);
extern void *func_02029910(void *);
extern void func_020157d4(void *, int (*)(unsigned short *, int), unsigned char, unsigned char);
extern void func_02015800(struct UnkStruct_02024fe4_2 *, void *, int, int);
extern int func_02015828(struct UnkStruct_02024fe4_2 *, int);
extern void func_0202dbf0(struct UnkStruct_02024fe4_2 *, struct UnkStruct_02024fe4);
extern void *func_0209bb70(void *);
extern void *func_02029a18(void *);
extern int func_02029e18(unsigned short *, int);
extern int func_02029e5c(unsigned short *, int);
extern int func_02029ea0(unsigned short *, int);

void func_02025148(UnkStruct_02025148 *param0, UnkStruct_02025148_2 *param1)
{
    Config *config;
    int value;
    int result;
    config = &data_020c8d08;
    if (func_0209bc40((unsigned char *) func_0202d9c4((unsigned int *) param0)) == 1) {
        config = &data_020c8d20;
    }
    value = *((int *) (((char *) param0->unk_100) + 0x830));
    result = func_020036e8((unsigned char *) func_0208150c(value));
    func_0202da38(param0, param0->buf, (char *) (&param0->unk_122), 0x1e, result, config->a, (unsigned char) config->b, 0, 0);
    param1->ptr = param0->buf;
    param1->byte = param0->unk_122;
    param0->unk_C8 = data_020d8f18;
}

void func_020250c8(UnkStruct_020250c8 *p)
{
    void *entry;

    entry = p->unk_100->unk_830;

    if (func_0209bc40((unsigned char *) ((int) func_0202d9c4((unsigned int *) p))) == 4) {
        if (func_0204bcdc(&p->unk_124) != 0) {
            func_0207860c(entry, (unsigned char) func_0209b69c(p->unk_164, (unsigned char) func_02080834(entry, &p->unk_124)));
        }
    }

    func_0209bb90((int) func_0202d9c4((unsigned int *) p), 1);
    func_02078648(entry, 1);
    func_02079478(func_0207f270(entry));
}

void func_02024fe4(struct UnkStruct_02024fe4_2 *o)
{
    switch (func_0209bc40((unsigned char *) ((void *) func_0202d9c4((unsigned int *) o)))) {
        case 2:
            if (func_0209b914(o->unk_164) <= 1) {
                func_020157d4(o, func_02029e18, 0xd, 1);
            } else {
                func_02015800(o, func_02029910(o->unk_164), 0xd, 1);
            }
            func_02015828(o, 0);
            func_0202dbf0(o, data_020d8f10);
            break;
        case 3:
            if (func_0209b914(o->unk_164) <= 1) {
                func_020157d4(o, func_02029e5c, 0xd, 1);
            } else {
                func_02015800(o, func_02029a18(func_0209bb70((void *) func_0202d9c4((unsigned int *) o))), 0xd, 1);
            }
            func_02015828(o, 0);
            func_0202dbf0(o, data_020d8e80);
            break;
        case 4:
            func_020157d4(o, func_02029ea0, 0xd, 1);
            func_02015828(o, 0);
            func_0202dbf0(o, data_020d9050);
            break;
    }
}
