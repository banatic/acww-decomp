/* overlay_slots: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0204f8ec @ 0x0204f8ec, 0x48 bytes, Thumb
 * func_0204f8bc @ 0x0204f8bc, 0x30 bytes, Thumb
 */

struct Entry {
    unsigned char type;
    unsigned char count;
    unsigned char pad_02[10];
};

typedef struct {
    unsigned char a;
    unsigned char b;
    unsigned char c;
    int d;
    int e;
} UnkStruct_0204f8bc;

extern struct Entry data_021c80f4[12];
extern void OS_Terminate(void);
extern void func_0204f9ec(struct Entry *);

void func_0204f8ec(unsigned char key)
{
    struct Entry *p = 0;
    unsigned int i = 0;
    goto test;
loop: {
    struct Entry *e = &data_021c80f4[i];
    if (e->type == key) {
        p = e;
        if (e->count != 0) {
            e->count--;
        }
    }
}
    i++;
test:
    if (i < 12) {
        goto loop;
    }

    if (p == 0) {
        OS_Terminate();
    }

    if (p->count == 0) {
        func_0204f9ec(p);
    }
}

void func_0204f8bc(void)
{
    unsigned int i = 0;
    goto check;
loop:
    ((UnkStruct_0204f8bc *) data_021c80f4)[i].a = 0xff;
    ((UnkStruct_0204f8bc *) data_021c80f4)[i].b = 0;
    ((UnkStruct_0204f8bc *) data_021c80f4)[i].c = 0;
    ((UnkStruct_0204f8bc *) data_021c80f4)[i].d = 0;
    ((UnkStruct_0204f8bc *) data_021c80f4)[i].e = 0;
    i++;
check:
    if (i < 12) {
        goto loop;
    }
}
