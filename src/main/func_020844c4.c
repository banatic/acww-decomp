/* func_020844c4 @ 0x020844c4, 0x90 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209fa30(void *p);
extern int func_02073dd4(void *obj, int field);
extern int func_020b65c4(void);
extern int func_02084af0(void);
extern int func_02084ad0(void);
extern int func_02085d2c(int a, int b);
extern int func_02084d5c(unsigned short *p, void *q, void *r);

extern void *data_020ccf94;
extern unsigned char data_020e54a8;
extern char data_020e1d8c;
extern void *data_020d0644;
extern char data_021f3b85[];

int func_020844c4(int param0)
{
    int ret;
    void *obj;

    ret = func_0209fa30(data_021f3b85);
    obj = data_020ccf94;

    if (func_02073dd4(obj, *(int *) ((char *) obj + 0x64)) != 0) {
        goto fail;
    }

    if (param0 != 0) {
        unsigned int flag = (data_020e54a8 == 0) ? 1 : 0;
        if (flag == 0) {
            goto fail;
        }
        if (func_020b65c4() == 0x2c) {
            goto fail;
        }
    }

    if (ret != 0) {
        goto fail;
    }

    if (func_02084af0() != 0) {
        goto fail;
    }
    if (func_02084ad0() != 0) {
        goto fail;
    }

    if (func_02085d2c(0x3c, 0) == 0) {
        goto fail;
    }

    {
        unsigned short local = 0xd00d;
        return func_02084d5c(&local, &data_020e1d8c, data_020d0644);
    }

fail:
    return 0;
}
