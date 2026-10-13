/* func_020b0678 @ 0x020b0678, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char data[6];
} UnkStruct_020b0678;

extern void func_020b0a3c(UnkStruct_020b0678 *arg);

void func_020b0678(UnkStruct_020b0678 *arg)
{
    unsigned int i;
    for (i = 0; i < 3; i++) {
        func_020b0a3c(&arg[i]);
    }
}
