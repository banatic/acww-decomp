/* func_020f3ab4 @ 0x020f3ab4, 0xcc bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f4220(void *self, int size, int count);
extern void func_020f41f4(void *self);
extern void func_020f4178(void *self);
extern void func_020f4130(void *self);
extern void func_020f40e8(void *self);
extern void func_020f40ac(void *self);
extern void *func_020eef70(void);
extern int func_0210e160(int a, void *b);
extern int NNS_SndHeapSaveState(void *heap);
extern int NNS_SndHeapGetCurrentLevel(void *heap);
extern int func_020f1d84(void *dest, int size);
extern int func_020f4038(void *self);
extern void func_020f97dc(void *p, int q);
extern void NNS_SndPlayerSetPlayerVolume(int player, int volume);

extern unsigned char data_021fd1bc[0x100];

typedef struct {
    unsigned char pad_00[8];
    unsigned char sub[0x14];
    unsigned char flag;
    unsigned char level;
} SObj;

void func_020f3ab4(SObj *self)
{
    void *heap;

    func_020f4220(self, 0x10ea0, 5);
    func_020f41f4(self);
    func_020f4178(self);
    func_020f4130(self);
    func_020f40e8(self);
    func_020f40ac(self);

    heap = func_020eef70();

    func_0210e160(9, heap);
    NNS_SndHeapSaveState(heap);
    self->level = NNS_SndHeapGetCurrentLevel(heap);

    func_020f1d84(data_021fd1bc, 0x90);
    func_020f4038(self);
    NNS_SndHeapSaveState(heap);
    self->flag = 1;

    data_021fd1bc[0x62] = 0;
    func_020f97dc(self->sub, 1);

    NNS_SndPlayerSetPlayerVolume(0x12, 0x3f);
    NNS_SndPlayerSetPlayerVolume(0x13, 0x3f);
}