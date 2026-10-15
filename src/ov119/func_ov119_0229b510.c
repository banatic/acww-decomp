/* func_ov119_0229b510 @ 0x0229b510, 0x98 bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

extern struct UnkStruct_0229b510 {
    char pad_00[0x64];
    int count;
} *data_020ccf94;

extern void func_ov002_02208d30(void *addr, int val);
extern int func_02073d90(void *arg);
extern void *func_02094fd4(void *buf);
extern int func_020984fc(int idx);
extern int func_02099870(int object);
extern void *func_02095074(int a, void *buf);
extern int func_ov002_02208ccc(void *a, void *b, void *c, unsigned char d);
extern void *func_02094fbc(void *buf);
extern int func_ov002_02208d4c(void *addr, int a, int b);
extern void func_ov119_0229a50c(void *p, int flag);

void func_ov119_0229b510(void *p)
{
    char sp[0x24];
    int i;
    struct UnkStruct_0229b510 *ptr;
    int count;

    *(unsigned char *) ((char *) p + 0xB0) = 7;
    func_ov002_02208d30((char *) p + 0x4c4, 0xA);

    ptr = data_020ccf94;
    if (func_02073d90(ptr) != 0) {
        count = ptr->count;
        i = 0;
        func_02094fd4(sp);
        for (; i < 4; i++) {
            int object;
            if (count == i) {
                continue;
            }
            if ((object = func_020984fc(i)) == 0) {
                continue;
            }
            {
                int ret = func_02099870(object);
                func_02095074(ret, sp);
                func_ov002_02208ccc((char *) p + 0xDC, (char *) p + 0x4c4, sp, (unsigned char) (i + 6));
            }
        }
        func_02094fbc(sp);
    }

    func_ov002_02208d4c((char *) p + 0x4c4, 0xCE, 5);
    func_ov002_02208d4c((char *) p + 0x4c4, 2, 0xA);
    func_ov119_0229a50c(p, 0);
}
