/* func_0203f394 @ 0x0203f394, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_0203f394;

extern UnkStruct_0203f394 *data_020ccf94;
extern int OSiHeapInfo[];
extern unsigned char data_020dab94;

extern int func_02073d90(void *);
extern void func_02073820(void *);
extern void func_020737f0(void *, unsigned char *, int);
extern void func_02073770(void *, int, int);

void func_0203f394(unsigned int arg)
{
    UnkStruct_0203f394 *p;
    p = data_020ccf94;
    if (func_02073d90(p)) {
        int field;
        unsigned char buf[12];
        UnkStruct_0203f394 *q;
        field = p->unk_64;
        if (field == 0) {
            OSiHeapInfo[field] = arg;
        } else {
            data_020dab94 = 0;
            buf[0] = 0;
            buf[1] = arg;
            buf[2] = arg >> 8;
            buf[3] = arg >> 16;
            buf[4] = arg >> 24;
            q = data_020ccf94;
            func_02073820(q);
            func_020737f0(q, buf, 5);
            func_02073770(q, 23, 0);
        }
    }
}
