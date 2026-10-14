/* func_020507b8 @ 0x020507b8, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020edf70(unsigned int size);
extern void func_020ee660(void *p);
extern void __cxa_vec_ctor(void *obj, int a, int b, void (*cb1)(void), void (*cb2)(void));
extern void func_0209d2b8(void *arg);
extern void func_0205072c(void);
extern void func_02050704(void);

typedef struct {
    void *unk_00;
    unsigned char pad_04[0x4c];
    unsigned int unk_50;
    unsigned char pad_54[0x5ac];
    unsigned int unk_600;
} UnkStruct_020507b8;

extern unsigned char data_020da13c[];
extern unsigned char data_020dce48[];

void *func_020507b8(void)
{
    UnkStruct_020507b8 *p = (UnkStruct_020507b8 *) func_020edf70(0x618);
    if (p != 0) {
        func_020ee660(p);
        p->unk_00 = (void *) data_020da13c;
        p->unk_00 = (void *) data_020dce48;
        __cxa_vec_ctor(&p->unk_50, 4, 0x16c, func_0205072c, func_02050704);
        func_0209d2b8(&p->unk_600);
    }
    return p;
}
