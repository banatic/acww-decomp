/* func_020919d4 @ 0x020919d4, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char b[4];
} UnkStruct_020919d4;

extern unsigned char data_021d52d8[];
extern int data_020d1828;
extern int data_020d1834;
extern int data_020d1744;
extern int func_02094bcc(void *, void *, void *);

void func_020919d4(void *self)
{
    UnkStruct_020919d4 local;
    void *p;
    short val;

    local = *(UnkStruct_020919d4 *) ((unsigned char *) self + 4);
    val = *(short *) (data_021d52d8 + local.b[0] * 0x1c + 0x10);
    if (val != 3) {
        p = &data_020d1828;
    } else {
        p = &data_020d1834;
    }
    func_02094bcc(self, p, &data_020d1744);
}
