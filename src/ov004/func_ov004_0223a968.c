/* func_ov004_0223a968 @ 0x0223a968, 0x50 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char *p;
    int n;
} UnkStruct_0223a968;

extern UnkStruct_0223a968 data_ov004_02247cf4[];
extern int func_0209ded0(void);
extern void func_0209def4(void *buf);

int func_ov004_0223a968(void *receiver)
{
    unsigned char buf[4];
    unsigned char *rec;
    UnkStruct_0223a968 *e;
    int i;
    unsigned short key;

    e = &data_ov004_02247cf4[func_0209ded0()];
    func_0209def4(buf);
    i = e->n - 1;
    key = *(unsigned short *) buf;
    for (; i >= 0; i--) {
        rec = e->p + i * 3;
        buf[3] = rec[1];
        buf[2] = rec[2];
        if (key >= *(unsigned short *) (buf + 2)) {
            return rec[0];
        }
    }
    return 0xff;
}
