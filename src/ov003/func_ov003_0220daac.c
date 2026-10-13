/* func_ov003_0220daac @ 0x0220daac, 0x94 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ccf94;
extern char *data_021c526c;
extern unsigned char data_ov003_02260540;
extern int data_ov003_02260558[3];

extern int func_02073908(int, int);
extern int func_020984fc(int);
extern void *func_02099728(void);
extern int func_0200f1a4(void *, int, unsigned short);
extern int func_0203b144(void);
extern int func_02036448(void *);
extern int func_0209129c(int);
extern int func_0200fa6c(void *, void *);

struct UnkStruct_0220daac {
    unsigned char pad_00[0x7d4];
    int unk_7D4;
};

void func_ov003_0220daac(void *a0)
{
    int x = data_020ccf94;
    int y = *(int *) ((char *) a0 + 0x800);

    if (func_02073908(x, y)) {
        int z = *(int *) ((char *) a0 + 0x800);
        void *p;

        func_020984fc(z);
        p = func_02099728();
        if (p) {
            func_0200f1a4(a0, 3, *(unsigned short *) p);
        }
        func_0203b144();
        func_02036448(data_021c526c + 0x1c4);
    }

    {
        int w = ((struct UnkStruct_0220daac *) a0)->unk_7D4;
        if (w != -1) {
            func_0209129c(w);
        }
    }

    {
        int local[3];

        func_0200fa6c(local, a0);
        data_ov003_02260540 = 0;
        data_ov003_02260558[0] = local[0];
        data_ov003_02260558[1] = local[1];
        data_ov003_02260558[2] = local[2];
    }
}
