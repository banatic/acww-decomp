/* func_02084188 @ 0x02084188, 0x88 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02088394(void);
extern int func_02084af0(void);
extern int func_02084ad0(void);
extern int func_020b65c4(void);
extern int func_02073dd4(void *p, int field);
extern int func_02085d2c(int a, int b);
extern int func_02084d5c(void *ptr, void *src, int val);

extern unsigned char data_020e54a8;
typedef struct {
    unsigned char pad_00[0x64];
    int unk_64;
} UnkStruct_02084188;
extern UnkStruct_02084188 *data_020ccf94;
extern char data_020e1d8c;
extern int data_020d0644;

int func_02084188(void *arg0)
{
    unsigned short local;
    unsigned int flag;

    if (func_02088394() == 0) {
        goto fail;
    }
    if (func_02084af0() != 0) {
        goto fail;
    }
    if (func_02084ad0() != 0) {
        goto fail;
    }

    if (arg0 != 0) {
        flag = (data_020e54a8 == 0) ? 1 : 0;
        if (flag == 0) {
            goto fail;
        }
        if (func_020b65c4() == 0x2c) {
            goto fail;
        }
    }

    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) != 0) {
        goto fail;
    }
    if (func_02085d2c(0x3d, 0) != 0) {
        goto fail;
    }

    local = 0xd023;
    return func_02084d5c(&local, &data_020e1d8c, data_020d0644);

fail:
    return 0;
}
