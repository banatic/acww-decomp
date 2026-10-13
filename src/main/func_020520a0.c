/* func_020520a0 @ 0x020520a0, 0x78 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

extern void *data_020ccf94;
extern int func_02073d90(void *);
extern void func_02073820(void *);
extern void func_020737f0(void *, void *, int);
extern void func_02073770(void *, int, int);

void func_020520a0(int a, int b, int c)
{
    unsigned char data;

    if (func_02073d90(data_020ccf94) == 0) {
        return;
    }

    data = (data & ~0x3f) | (a & 0x3f);
    data = (data & ~0x40) | ((b & 1) << 6);
    {
        int flag = (c == 4) ? 0 : 1;
        data = (data & ~0x80) | ((flag & 1) << 7);
    }

    {
        void *ptr = data_020ccf94;
        func_02073820(ptr);
        func_020737f0(ptr, &data, 1);
        func_02073770(ptr, 0x19, c);
    }
}
