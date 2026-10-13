/* func_020777f0 @ 0x020777f0, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_020777f0(void);
extern void *data_020ccf94;
extern void *func_0207b9d0(int);
extern unsigned char func_020794d8(void);
extern void *func_020794d0(void *p);
extern void func_020732f0(void *, const void *, unsigned int);
typedef struct {
    unsigned char pad_00[0x20];
    unsigned int unk_20;
    unsigned short unk_24;
} PStruct;
typedef struct {
    unsigned char a;
    unsigned short b;
    unsigned int c;
} UnkStruct_020777f0;
void func_020777f0(void)
{
    PStruct *p;
    int i;
    void *base;
    UnkStruct_020777f0 local;
    local.a = 3;
    i = 0;
    base = data_020ccf94;
    for (; i < 8; i++) {
        p = (PStruct *) func_0207b9d0(i);
        if (p != 0) {
            local.a = func_020794d8();
        } else {
            local.a = 3;
        }
        func_020732f0(base, &local.a, 1);
        func_020732f0(base, func_020794d0(p), 12);
        local.c = p->unk_20;
        func_020732f0(base, &local.c, 4);
        local.b = p->unk_24;
        func_020732f0(base, &local.b, 2);
    }
}
