/* func_01ffcb2c @ 0x01ffcb2c, 0x2e bytes, Thumb, module itcm
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char *data;
} UnkStruct_01ffcb2c;

extern UnkStruct_01ffcb2c *func_01ffcb5c(int, int);

unsigned char func_01ffcb2c(int a, int b)
{
    UnkStruct_01ffcb2c *p;
    p = func_01ffcb5c(a >> 4, b >> 4);
    if (p) {
        return p->data[(a & 0xf) + ((b & 0xf) << 4)];
    }
    return 0x15;
}
