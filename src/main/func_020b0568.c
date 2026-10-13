/* func_020b0568 @ 0x020b0568, 0x2a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b0a20(void *);

typedef struct {
    char data[6];
} UnkStruct_020b0568;

int func_020b0568(UnkStruct_020b0568 *arg)
{
    unsigned int i;
    for (i = 0; i < 3; i++) {
        if (func_020b0a20(arg + i) == 0) {
            return 0;
        }
    }
    return 1;
}
