/* func_020b8a5c @ 0x020b8a5c, 0x94 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct UnkStruct_020b8a5c *func_0203ab20(void);
extern int *func_02095794(int);
extern void func_0203f844(void *, void *);
extern void MTX_MultVec43(void *, void *, void *);
extern int func_0203c53c(void *);
extern int FX_Div(int, int);
extern void func_020eabc8(void *, int);
extern void func_0208aa60(void *, int, int);

struct UnkStruct_020b8a5c {
    long long data[6];
};
extern struct UnkStruct_020b8a5c data_021fbe48;
extern void *data_021c67a4;

void func_020b8a5c(void *p)
{
    struct UnkStruct_020b8a5c *src;
    int *ptr;
    int data[3];
    int buffer2[3];
    int buffer3[3];
    int tmp1, tmp2;

    src = func_0203ab20();
    data_021fbe48 = *src;

    ptr = func_02095794(4);
    if (ptr != 0) {
        data[0] = ptr[0];
        data[1] = ptr[1];
        data[2] = ptr[2];
        data[1] += 0x3c00;

        func_0203f844(buffer2, data);
        MTX_MultVec43(buffer2, &data_021fbe48, buffer3);

        tmp1 = FX_Div(0x60000, func_0203c53c(data_021c67a4));
        tmp2 = FX_Div(-tmp1, buffer3[2]);
        func_020eabc8(buffer3, tmp2);

        func_0208aa60((char *) p + 8, buffer3[0] >> 12, -buffer3[1] >> 12);
    }
}
