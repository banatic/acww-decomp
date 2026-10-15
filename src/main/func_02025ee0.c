/* func_02025ee0 @ 0x02025ee0, 0x98 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0209b91c(int *);
extern int func_0209bd44(void *);
extern unsigned int func_0202d9c4(void *);
extern int func_0209bc40(unsigned char *);
extern int func_020984e8(void);
extern int func_02099870(int object);
extern void func_0209b9cc(int *, int, void *, int, int);
extern void func_020784f8(int, int, void *, int, int);
extern int func_0207f270(int);
extern int func_020794d0(int);
extern void func_0209bd5c(void *);
extern int *data_020ccf94;

struct UnkStruct_02025ee0 {
    char pad_00[0x100];
    int *unk_100;
    char pad_104[0x60];
    int *unk_164;
};

void func_02025ee0(struct UnkStruct_02025ee0 *self)
{
    int forwarded_value;

    int r7;
    int r6 = *((int *) ((char *) self->unk_100 + 0x830));
    int flag = 0;

    if (func_0209bd44((void *) func_0209b91c(self->unk_164)) == 0) {
        r7 = func_0209bc40((unsigned char *) func_0202d9c4(self));
        flag = 1;
    } else {
        r7 = func_0209bc40((unsigned char *) func_0209b91c(self->unk_164));
    }

    (forwarded_value = (int) func_020984e8());
    {
        int temp = func_02099870((int) forwarded_value);
        func_0209b9cc(self->unk_164, r7, (char *) self + 0x124, temp, flag);
    }

    func_020784f8(r6, r7, (char *) self + 0x124, data_020ccf94[25], flag);

    func_0209bd5c((void *) func_020794d0((int) func_0207f270(r6)));
}
