/* func_020b0540 @ 0x020b0540, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char data[5];
    unsigned char flag;
} UnkStruct_020b0540;

extern int func_020b0a20(UnkStruct_020b0540 *p);

void func_020b0540(UnkStruct_020b0540 *base, unsigned int index)
{
    if (index < 3) {
        if (func_020b0a20(&base[index])) {
            base[index].flag = 0;
        }
    }
}
