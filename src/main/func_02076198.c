/* func_02076198 @ 0x02076198, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern void func_020736bc(void *src, void *dst, int size);
extern int func_02077898(void *p);
extern void func_02077a34(void *a, void *b, void *c);
extern void func_0205f9d4(signed char a, signed char b, unsigned char c, int d, int e);

void func_02076198(unsigned int count)
{
    unsigned char data[7];
    unsigned int i = 0;
    void *g = data_020ccf94;
    int flag = i;
    int val;

    for (; i < count; i += 5) {
        func_020736bc(g, &data[2], 5);
        val = func_02077898(&data[2]);
        func_02077a34(&data[4], &data[0], &data[1]);
        func_0205f9d4((signed char) data[5], (signed char) data[6], data[0], val, (data[1] != 0) ? 1 : flag);
    }
}
