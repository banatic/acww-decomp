/* keyboard_entry_scene: 6 functions, module ov126
 * mwccarm 1.2/base -O4,s
 * func_ov126_022a1478 @ 0x022a1478, 0x8 bytes, Thumb
 * func_ov126_022a1448 @ 0x022a1448, 0x30 bytes, Thumb
 * func_ov126_022a1434 @ 0x022a1434, 0x14 bytes, Thumb
 * func_ov126_022a13fc @ 0x022a13fc, 0x38 bytes, Thumb
 * func_ov126_022a1394 @ 0x022a1394, 0x68 bytes, Thumb
 * func_ov126_022a12d4 @ 0x022a12d4, 0xc0 bytes, Thumb
 */

typedef struct UnkStruct_022a1448 {
    char pad_00[0xb0];
    int unk_B0;
    char pad_B4[0x3d10];
    int unk_3DC4;
    char pad_3DC8[0x22c];
    int unk_3FF4;
} UnkStruct_022a1448;

extern void func_ov126_0229f7a8(UnkStruct_022a1448 *p, int n);
extern void func_ov124_0229eea0(int *p);
extern void func_ov002_0220af74(int *p);
extern void func_02070b84(int *p);
extern void func_ov095_0229bf7c(char *ptr, int a);
extern void func_02001c08(int);
extern void func_020029e8(int, int);
extern void func_020028bc(int, int, int, int);
extern int func_ov124_0229f378(void *, int);
extern int func_02002c6c(int, int, int, int, int, int);
extern int func_ov095_0229c000(void *, const void *);
extern void func_ov126_022a0978(void *);
extern void func_ov095_0229bfd8(void *, int);
extern int func_ov095_0229c01c(int, int);
extern int data_ov126_022a2154;
extern int data_021fbe94;
extern int data_ov126_022a216c;
extern int func_ov095_0229b324(void *receiver);
extern void func_ov124_0229ef4c(void *ptr, int val);
extern int func_02002d14(void *a, int b, int c, int d, int e, int f);
extern void func_ov002_0220af94(void *receiver);
extern int func_ov126_0229f7c8(void *self, int val);
extern void *func_02070c08(void *ptr);
extern void func_020a8c1c(void *ptr);
extern int func_020b496c(int a, void *ptr);
extern int func_0206fca4(void);
extern int func_0207094c(void *ptr, int val);
extern void func_02070adc(void *ptr, int a, int b, int c, int d, int e, int f);
extern void func_02070a04(void *ptr, int a, int b);
extern int **func_02070be8(void *ptr);
extern unsigned char data_ov126_022a2140[];

void func_ov126_022a1434(char *p);

void func_ov126_022a1478(void *argument0)
{
    func_ov126_022a1434((char *) argument0);
}

void func_ov126_022a1448(UnkStruct_022a1448 *self)
{
    func_ov126_0229f7a8(self, 0x10);
    func_ov124_0229eea0(&self->unk_B0);
    func_ov002_0220af74(&self->unk_3DC4);
    func_02070b84(&self->unk_3FF4);
}

void func_ov126_022a1434(char *p)
{
    func_ov095_0229bf7c(p + 0x19c, 6);
}

void func_ov126_022a13fc(void)
{
    func_02001c08(0);
    func_020029e8(4, 3);
    func_020028bc(4, 0, 0, 0);
    func_020029e8(6, 2);
    func_020028bc(6, 0, 0, 0);
}

void func_ov126_022a1394(unsigned char *p)
{
    func_ov124_0229f378(p + 0xb0, 4);
    func_02002c6c((int) &data_ov126_022a2154, data_021fbe94, 4, 0x13d, 0x13d, 0x1e9);
    func_ov095_0229c000(p + 0x19c, &data_ov126_022a216c);
    func_ov126_022a0978(p);
    func_ov095_0229bfd8(p + 0x19c, 6);
    func_ov095_0229c01c((int) (p + 0x19c), 6);
}

static __inline char *get_3ff4(char *self)
{
    return self + 0x3ff4;
}

void func_ov126_022a12d4(char *self)
{
    unsigned char local[0x6c];
    int ret;
    int res;

    func_ov095_0229b324(self + 0x19c);
    func_ov124_0229ef4c(self + 0xb0, 6);
    func_02002d14(data_ov126_022a2140, data_021fbe94, 8, 5, 5, 5);
    func_ov002_0220af94(self + 0x3dc4);
    if (func_ov126_0229f7c8(self, 0x100) != 0) {
        func_02070c08(local);
        func_020a8c1c(local);
        ret = func_020b496c(0, local);
        res = func_0206fca4();
        if (res == 0x12) {
            func_0207094c(get_3ff4(self), 0x80);
        } else {
            func_0207094c(get_3ff4(self), 0x66);
        }
        func_02070adc(get_3ff4(self), 8, 0x1c0, 6, 15, 0, 0);
        func_02070a04(get_3ff4(self), 0, 0);
        func_02070be8(local);
    }
}
