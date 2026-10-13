/* func_0208fb24 @ 0x0208fb24, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x1c];
    unsigned int index_1c;
    unsigned char flag_20;
} Func0208fb24Struct;

extern unsigned short data_020d0bac[];
extern void func_02004644(int a, int b);

void func_0208fb24(Func0208fb24Struct *obj)
{
    unsigned short val = data_020d0bac[obj->index_1c];
    if (obj->flag_20) {
        obj->flag_20 = 0;
        func_02004644(val, 1);
    }
}
