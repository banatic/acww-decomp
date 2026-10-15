/* func_020858ac @ 0x020858ac, 0x184 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b66b0(void);
extern int func_0207cec0(void *g, int x);
extern unsigned int func_0208150c(unsigned int);
extern int func_02003704(void *);
extern int func_020852e4(void *p);
extern int func_020a7278(void);
extern int func_02085d6c(void *p, void *q);
extern int func_020644cc(int);
extern void func_02077978(void *a, void *b, void *c);
extern void MI_CpuCopy8(void *a, void *b, int c);
extern int func_02073dd4(void *obj, int field);
extern int func_020791ec(void);
extern int func_020791bc(void);
extern int func_0207cf74(unsigned int);
extern int func_0207b3dc(void *g);
extern unsigned int func_0207b410(void *g);
extern int func_0209a654(unsigned char *);
extern int func_0207af30(void);
extern int func_0207f150(int st);
extern int func_02003348(int a, unsigned short b, void *c, void *d, void *e);

extern void *data_020ccf94;
extern unsigned char data_021e5a2c[];

void func_020858ac(void *p)
{
    int key;
    int st;
    int res;
    int action;
    int flag;
    unsigned short cmd[5];
    int tmp[3];

    key = func_020b66b0();
    st = func_0207cec0(data_021e5a2c, key);
    if (st == 0) {
        goto exit;
    }

    if (!func_02003704((void *) func_0208150c(st))) {
        goto exit;
    }

    cmd[0] = 0xfff1;
    cmd[1] = 0xfff1;
    tmp[0] = 0;
    tmp[1] = 0;
    tmp[2] = 0;
    cmd[2] = 0;
    cmd[3] = 0;
    cmd[4] = 0;

    cmd[0] = (unsigned short) ((key & 0xfff) | 0xe000);

    res = func_020852e4(cmd);

    if (func_020a7278()) {
        res = func_02085d6c(p, tmp);
        cmd[3] = (unsigned short) (func_020644cc(4) << 14);
    } else if (res != 0 && *(unsigned char *) res != 0) {
        func_02077978((void *) (res + 4), tmp, &tmp[2]);
        res += 9;
        MI_CpuCopy8((void *) res, &cmd[3], 2);
        res = 1;
    } else {
        res = func_02085d6c(p, tmp);
        cmd[3] = (unsigned short) (func_020644cc(4) << 14);
    }

    if (res == 0) {
        goto exit;
    }

    action = 0x85;
    flag = 0xd8;

    if (func_02073dd4(data_020ccf94, *(int *) ((char *) data_020ccf94 + 0x64)) == 0) {
        if (key == func_020791ec()) {
            action = 0x80;
            if (func_0207cf74((unsigned int) func_020791bc()) != 0) {
                cmd[1] = (unsigned short) ((func_020791bc() & 0xfff) | 0xe000);
                flag = 0x81;
            }
        } else if (key == func_0207b3dc(data_021e5a2c)) {
            if (func_0209a654((unsigned char *) func_0207b410(data_021e5a2c)) == 0) {
                action = 0x83;
            }
        } else {
            if (func_0207af30() == 0xa && func_0207f150(st) == 3) {
                action = 0x86;
            }
        }
    }

    func_02003348(action, cmd[0], tmp, &cmd[2], p);

    if (flag == 0xd8) {
        goto exit;
    }

    if (((cmd[1] & 0xf000) >> 12) == 0xe) {
        func_02085d6c(p, tmp);
        cmd[3] = (unsigned short) (func_020644cc(4) << 14);
        func_02003348(flag, cmd[1], tmp, &cmd[2], p);
    }

exit:
    return;
}
