/* func_ov114_0229d088 @ 0x0229d088, 0x7c bytes, Thumb, module ov114
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x808];
    char buffer[0xAA8];
    unsigned char flag_12b0;
    char pad_12B1[0x4];
    unsigned char flag_12b5;
    char pad_12B6[0x1];
    unsigned char mode_12b7;
    unsigned char flag_12b8;
} UnkStruct_0229d088;

extern const char data_ov114_0229dbac[];
extern const char data_ov114_0229dbbc[];

extern void func_020a8c1c(void *ptr);
extern int func_020b4a20(void *buf, unsigned char *byte, const char *data);
extern unsigned char func_ov114_0229d030(UnkStruct_0229d088 *obj);
extern void func_ov114_0229cf58(UnkStruct_0229d088 *obj);

void func_ov114_0229d088(UnkStruct_0229d088 *obj)
{
    unsigned char flag;
    unsigned char mode;
    unsigned char local;
    const char *ptr;

    flag = obj->flag_12b8;
    mode = obj->mode_12b7;

    switch (mode) {
        case 0:
            ptr = data_ov114_0229dbac;
            break;
        case 1:
            ptr = data_ov114_0229dbbc;
            break;
        default:
            break;
    }

    if (flag == 0xff) {
        func_020a8c1c(obj->buffer);
        obj->flag_12b0 = 1;
    } else {
        local = flag;
        func_020b4a20(obj->buffer, &local, ptr);
        obj->flag_12b0 = func_ov114_0229d030(obj);
    }

    obj->flag_12b5 = 0;
    func_ov114_0229cf58(obj);
}
