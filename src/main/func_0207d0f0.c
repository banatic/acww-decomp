/* func_0207d0f0 @ 0x0207d0f0, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(void *a, int b);
extern int func_02003704(int c);
typedef struct {
    unsigned char pad_00[0x1e];
    unsigned char unk_1E;
} UnkStruct_0207d0f0;
extern UnkStruct_0207d0f0 *func_0207f270(void *a);

void func_0207d0f0(void *arg0, int arg1)
{
    if (func_02003704(func_0208150c(arg0, arg1))) {
        UnkStruct_0207d0f0 *p;
        int value;
        p = func_0207f270(arg0);
        value = arg1 + p->unk_1E;
        if (value < 0) {
            value = 0;
        } else if (value > 0x20) {
            value = 0x20;
        }
        p->unk_1E = value;
    }
}
