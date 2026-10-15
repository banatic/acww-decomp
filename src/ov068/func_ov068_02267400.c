/* func_ov068_02267400 @ 0x02267400, 0x68 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_02019e00(char *);
extern int func_02019df8(char *);
extern int func_ov068_0226c0a4(void *);
extern int func_02019c6c(char *, int, unsigned short);
extern void func_ov068_0226cce8(void *, void *, int);
extern unsigned short data_020c80f8;

void func_ov068_02267400(void *param0, void *param1)
{
    if (func_02019e00(((char *) param1) + 0x564) != 8) {
        return;
    }
    if (func_02019df8(((char *) param1) + 0x564) != 0x1a) {
        return;
    }
    if (*(unsigned int *) (((char *) param0) + 0x20) != 0) {
        return;
    }
    if (func_ov068_0226c0a4(param0) != 0) {
        return;
    }
    if (((*(unsigned int *) (((char *) param1) + 0x190) << 4) >> 16) != 0) {
        return;
    }
    func_02019c6c(((char *) param1) + 0x564, 1, data_020c80f8);
    func_ov068_0226cce8(param0, param1, 0);
}
