/* town_list_states: 6 functions, module ov141
 * mwccarm 1.2/base -O4,s
 * func_ov141_0229a960 @ 0x0229a960, 0x8 bytes, Thumb
 * func_ov141_0229a934 @ 0x0229a934, 0x2c bytes, Thumb
 * func_ov141_0229a91c @ 0x0229a91c, 0x16 bytes, Thumb
 * func_ov141_0229a8d0 @ 0x0229a8d0, 0x4c bytes, Thumb
 * func_ov141_0229a850 @ 0x0229a850, 0x80 bytes, Thumb
 * func_ov141_0229a834 @ 0x0229a834, 0x1c bytes, Thumb
 */

extern void func_020b9ccc(void *);
extern void func_ov002_0220af74(void *);
extern void func_ov139_02299ac0(void *);
extern void func_ov141_0229a280(void *p);
extern void func_ov139_02299a80(void *p);
extern void func_02001c08(int);
extern void func_020029e8(int, int);
extern void func_020028bc(int, int, int, int);
extern void func_ov139_022999f8(void *);
extern void func_ov139_022999c4(void *);
extern int func_02064af4(const void *, void *, int);
extern void func_0206fdd4(void *, int, int, int, int, int);
extern void func_ov141_02299f6c(void *, int);
extern int func_02002d14(const void *, int, int, int, int, int);
extern unsigned char data_ov141_0229afa8[];
extern unsigned char data_ov141_0229afbc[];
extern int data_021fbe94;
extern void func_ov139_02299964(void *receiver);
extern void func_ov002_0220af94(void *receiver);

void func_ov141_0229a91c(void *p);

void func_ov141_0229a960(void *argument0)
{
    func_ov141_0229a91c(argument0);
}

void func_ov141_0229a934(void *self)
{
    func_020b9ccc((char *) self + 0xc68);
    func_ov002_0220af74((char *) self + 0xa9c);
    func_ov139_02299ac0((char *) self + 0x94);
}

void func_ov141_0229a91c(void *p)
{
    func_ov141_0229a280(p);
    func_ov139_02299a80((char *) p + 0x94);
}

void func_ov141_0229a8d0(void)
{
    func_02001c08(0);
    func_020029e8(6, 2);
    func_020028bc(6, 0, 0, 0);
    func_020029e8(4, 2);
    func_020028bc(4, 0, 0, 0);
    func_020029e8(3, 2);
    func_020028bc(3, 0, 0, 0);
}

void func_ov141_0229a850(char *self)
{
    func_ov139_022999f8(self + 0x94);
    func_ov139_022999c4(self + 0x94);
    func_02064af4(data_ov141_0229afa8, self + 0x127c, 0x800);
    func_0206fdd4(self + 0x127c, 7, 8, 0x10, 0x13, 7);
    func_0206fdd4(self + 0x127c, 0x12, 8, 0x19, 0x13, 7);
    func_ov141_02299f6c(self, 4);
    func_02002d14(data_ov141_0229afbc, data_021fbe94, 6, 3, 3, 3);
}

void func_ov141_0229a834(void *self)
{
    func_ov139_02299964((char *) self + 0x94);
    func_ov002_0220af94((char *) self + 0xa9c);
}
