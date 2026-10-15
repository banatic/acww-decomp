/* func_ov105_0229e2e0 @ 0x0229e2e0, 0x94 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

typedef struct Sub24A4 {
    int pad_00;
} Sub24A4;

typedef struct Sub2D40 {
    int pad_00;
} Sub2D40;

typedef struct UnkStruct_0229e2e0 {
    char pad_00[0x24a4];
    Sub24A4 sub24A4;
    char pad_24A8[0x898];
    Sub2D40 sub2D40;
} UnkStruct_0229e2e0;

extern int func_0208e4bc(void *p);
extern int func_ov002_0220b5ec(void *p, int flag);
extern int func_ov002_0220b59c(void *p, int flag);
extern void func_ov002_0220a0b4(void *p, int v1, int v2);
extern void func_ov002_0220a374(void *p, int flag);
extern int func_ov002_02208014(void *receiver);
extern void func_ov105_0229cfc0(void *p);
extern unsigned char *func_ov002_02208098(void *p, unsigned char value);
extern void func_ov002_0220a1dc(void *p);
extern unsigned short data_021fbe40[2];

void func_ov105_0229e2e0(UnkStruct_0229e2e0 *self)
{
    int v1;
    int v2;

    if (func_0208e4bc(&self->sub24A4) == 0) {
        v1 = func_ov002_0220b5ec(&self->sub2D40, 1);
        v2 = func_ov002_0220b59c(&self->sub2D40, 1);
        func_ov002_0220a0b4(&self->sub24A4, v1, v2);
        func_ov002_0220a374(&self->sub24A4, 1);
    }
    if (func_ov002_02208014(self) != 0) {
        func_ov105_0229cfc0(self);
        func_ov002_02208098(self, 5);
    } else {
        if ((data_021fbe40[1] & 1) || (data_021fbe40[1] & 2)) {
            func_ov002_0220a1dc(&self->sub24A4);
            func_ov002_02208098(self, 10);
        }
    }
}
