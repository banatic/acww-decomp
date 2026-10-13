/* func_02091a24 @ 0x02091a24, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char b[4];
} UnkStruct_02091a24;

extern unsigned char data_021d52d8[];
extern int data_020d1840;
extern int data_020d184c;
extern int data_020d178c;
extern void func_02094bcc(void *, void *, void *);

void func_02091a24(void *self)
{
    UnkStruct_02091a24 local;
    void *p;
    short val;

    local = *(UnkStruct_02091a24 *) ((unsigned char *) self + 4);
    val = *(short *) (data_021d52d8 + local.b[0] * 0x1c + 0x10);
    if (val != 3) {
        p = &data_020d1840;
    } else {
        p = &data_020d184c;
    }
    func_02094bcc(self, p, &data_020d178c);
}
