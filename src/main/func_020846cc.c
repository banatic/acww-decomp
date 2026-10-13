/* func_020846cc @ 0x020846cc, 0x118 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02073dd4(void *obj, int field);
extern int func_020b65c4(void);
extern int func_020847e4(void);
extern int func_02084890(void);
extern int func_02084ad0(void);
extern int func_02084b14(void *p, int n);
extern int func_02041608(void);
extern int func_02084d34(unsigned int, unsigned int, unsigned int);
extern int func_02084d5c(unsigned short *p, unsigned int q, unsigned int r);

extern void *data_020ccf94;
extern unsigned char data_020e54a8;
extern unsigned int data_020e1b88;
extern unsigned int data_020e1d8c;
extern unsigned int data_020d0644;
extern int data_020d0664[];

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
} UnkStruct_020846cc;
extern UnkStruct_020846cc data_020d06a4[];

int func_020846cc(int param0)
{
    void *obj;
    int idx;
    int t;
    int allowed;

    obj = data_020ccf94;
    if (func_02073dd4(obj, *(int *) ((char *) obj + 0x64)) != 0) {
        goto late;
    }

    allowed = 1;
    if (param0 != 0) {
        int v = 0;
        unsigned int ok = (data_020e54a8 == 0) ? 1 : 0;
        if (ok != 0) {
            if (func_020b65c4() != 0x2c) {
                v = 1;
            }
        }
        if (v == 0) {
            allowed = 0;
        }
    }

    if (func_020847e4() != 0) {
        if (allowed == 0) {
            goto ret0;
        }
        return func_02084d34((unsigned int) &data_020e1b88, (unsigned int) &data_020e1d8c, data_020d0644);
    }

    idx = -1;
    if (func_02084ad0() == 0) {
        idx = func_02084b14(data_020d06a4, 8);
    }
    if (idx != -1) {
        t = data_020d0664[idx];
        if (t != func_02041608() && t != 0x13) {
            idx = -1;
        }
    }
    if (idx != -1) {
        if (allowed == 0) {
            goto ret0;
        }
        return func_02084d34((unsigned int) &data_020d06a4[idx].unk_04, (unsigned int) &data_020e1d8c, data_020d0644);
    }
    if (func_02084890() != 0) {
        goto ret0;
    }
    if (func_020b65c4() != 9) {
        goto ret0;
    }
    {
        unsigned short loc = 0xd025;
        return func_02084d5c(&loc, (unsigned int) &data_020e1d8c, data_020d0644);
    }

late:
    if (func_020b65c4() != 9) {
        goto ret0;
    }
    {
        unsigned short loc2 = 0xd025;
        return func_02084d5c(&loc2, (unsigned int) &data_020e1d8c, data_020d0644);
    }
ret0:
    return 0;
}
