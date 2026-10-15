/* func_ov103_0229d450 @ 0x0229d450, 0x94 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e4bc(unsigned char *);
extern int func_ov002_0220b5ec(unsigned char *, int);
extern int func_ov002_0220b59c(unsigned char *, int);
extern void func_ov002_0220a0b4(unsigned char *, int, int);
extern void func_ov002_0220a374(unsigned char *, int);
extern int func_ov002_02208014(unsigned char *);
extern void func_ov103_0229c7ec(unsigned char *);
extern unsigned char *func_ov002_02208098(unsigned char *, unsigned char value);
extern void func_ov002_0220a1dc(unsigned char *);

typedef struct {
    unsigned short unk_00;
    unsigned short unk_02;
} UnkStruct_0229d450;
extern UnkStruct_0229d450 data_021fbe40;

void func_ov103_0229d450(unsigned char *p)
{
    if (func_0208e4bc(p + 0x2274) == 0) {
        int a = func_ov002_0220b5ec(p + 0x2b10, 1);
        int b = func_ov002_0220b59c(p + 0x2b10, 1);
        func_ov002_0220a0b4(p + 0x2274, a, b);
        func_ov002_0220a374(p + 0x2274, 1);
    }
    if (func_ov002_02208014(p) != 0) {
        func_ov103_0229c7ec(p);
        func_ov002_02208098(p, 3);
    } else {
        if (((data_021fbe40.unk_02 & 1) != 0) || ((data_021fbe40.unk_02 & 2) != 0)) {
            func_ov002_0220a1dc(p + 0x2274);
            func_ov002_02208098(p, 8);
        }
    }
}
