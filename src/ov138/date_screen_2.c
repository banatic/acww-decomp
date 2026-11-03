/* date_screen_2: 2 functions, module ov138
 * mwccarm 1.2/base -O4,s
 * func_ov138_0229c6e8 @ 0x0229c6e8, 0x50 bytes, Thumb
 * func_ov138_0229c688 @ 0x0229c688, 0x5e bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x95];
    unsigned char state;
    unsigned char pad_96[2];
    unsigned char data[4];
} UnkStruct_0229c6e8;

typedef struct {
    unsigned char pad_00[0x8d];
    unsigned char unk_8D;
    unsigned char pad_8E[0x94 - 0x8d - 1];
    unsigned char unk_94;
    unsigned char pad_95[0x98 - 0x94 - 1];
} UnkStruct_0229c688;

extern int func_ov138_0229c574(void *, int);
extern void func_ov002_0220a2b4(void *);
extern void func_ov002_0220a314(void *);
extern int func_ov138_0229c7a8(void *);
extern int func_ov138_0229c754(void *);
extern void func_ov002_0220a05c(void *obj, int a, int b, int c, int d);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov138_0229c554(void *self, int cmd);

void func_ov138_0229c688(UnkStruct_0229c688 *self, int a, int b);

void func_ov138_0229c6e8(UnkStruct_0229c6e8 *ptr)
{
    int v;
    int w;

    if (func_ov138_0229c574(ptr, 2) != 0 || (ptr->state != 3 && ptr->state != 4)) {
        func_ov002_0220a2b4(ptr->data);
    } else {
        func_ov002_0220a314(ptr->data);
    }

    v = func_ov138_0229c7a8(ptr);
    w = func_ov138_0229c754(ptr);
    func_ov138_0229c688((UnkStruct_0229c688 *) ptr, v, w);
}

void func_ov138_0229c688(UnkStruct_0229c688 *self, int a, int b)
{
    if (func_ov138_0229c574(self, 4)) {
        func_ov002_0220a05c((char *) self + 0x98, a, b, 2, 1);
    } else {
        func_ov002_0220a05c((char *) self + 0x98, a, b, 3, 1);
    }
    self->unk_94 = self->unk_8D;
    func_ov002_02208098((void *) (self), 8);
    func_ov138_0229c554(self, 4);
}
