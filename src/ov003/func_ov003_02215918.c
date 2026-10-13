/* func_ov003_02215918 @ 0x02215918, 0x40 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_020e8ed8(int a, int b);
extern void func_020113e0(short *p, int v, short s);
extern void func_020110a0(void *p, short *q);

typedef struct {
    char pad_00[0x5c];
    int unk_5C;
    char pad_60[0x64 - 0x60];
    int unk_64;
    char pad_68[0x8e - 0x68];
    short unk_8E;
    char pad_90[0x5d0 - 0x90];
    int arr[3];
} UnkStruct_02215918;

void func_ov003_02215918(UnkStruct_02215918 *this)
{
    short s;
    short val;
    int *base;
    int d1, d2, res;

    base = this->arr;
    d1 = base[0] - this->unk_5C;
    d2 = base[2] - this->unk_64;
    res = func_020e8ed8(d1, d2);
    val = this->unk_8E;
    s = val;
    func_020113e0(&s, res, val);
    func_020110a0(this, &s);
}
