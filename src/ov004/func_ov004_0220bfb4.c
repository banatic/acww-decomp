/* func_ov004_0220bfb4 @ 0x0220bfb4, 0x68 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O1,s
 */

extern void func_020984e8(void);
extern void func_020996a0(void);
extern void *func_020adf50(void);
extern int func_020adde4(unsigned short);
extern void func_0206844c(void *a, void *b, void *c);
extern void *data_ov004_0224fbe0;

typedef struct {
    char pad_00[0x10a];
    unsigned char state;
    char pad_10B[0x21];
    void *data;
} UnkStruct_0220bfb4;

void func_ov004_0220bfb4(UnkStruct_0220bfb4 *p)
{
    char buf[2];
    if (p->state == 1 || p->state == 2) {
        func_020984e8();
        func_020996a0();
        if (func_020adde4(*(unsigned short *) func_020adf50()) == 4) {
            buf[0] = 5;
            func_0206844c(p->data, &buf[0], data_ov004_0224fbe0);
        } else {
            buf[1] = 3;
            func_0206844c(p->data, &buf[1], data_ov004_0224fbe0);
        }
    }
}
