/* func_ov068_0226befc @ 0x0226befc, 0x138 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov068_0226c8b0(void *obj, const void *ptr);
extern void func_0202e118(void *, const void *);
extern void func_ov068_0226cce8(void *, const void *, int);
extern void func_ov068_0226cce4(void *, int);
extern int func_ov068_0226c0f4(const void *, const void *);
extern int func_ov068_0226c0e0(const void *, const void *);
extern int func_ov068_0226cc20(const void *, const void *);
extern int func_ov068_0226c520(const void *, const void *);
extern int func_ov068_02266e7c(const void *);
extern int func_ov068_0226c1dc(const void *, const void *);
extern int func_ov068_0226c034(const void *, const void *);
extern int func_ov068_0226c63c(const void *, const void *);
extern short data_ov068_02276724[];

typedef struct UnkStruct_0226befc {
    unsigned char pad_00[0x98];
    void *unk_98;
    unsigned char pad_9C[0x9F4 - 0x9C];
    unsigned char unk_9F4[0x12];
    unsigned short unk_A06;
} UnkStruct_0226befc;

int func_ov068_0226befc(void *obj, const void *ptr)
{
    int flag = 0;
    char buffer[8];

    if (func_ov068_0226c8b0(obj, ptr)) {
        func_0202e118(buffer, ptr);
        if (*(unsigned short *) buffer != 0xFFF1) {
            func_ov068_0226cce8(obj, ptr, 0x10);
            func_ov068_0226cce4(obj, 2);
        } else {
            func_ov068_0226cce8(obj, ptr, 2);
        }
        flag = 1;
        goto exit;
    }

    if (func_ov068_0226c0f4(obj, ptr)) {
        func_ov068_0226cce8(obj, ptr, 0x11);
        flag = 1;
        goto exit;
    }

    if (((const UnkStruct_0226befc *) ptr)->unk_A06 >= data_ov068_02276724[0]) {
        func_ov068_0226cce8(obj, ptr, 0x15);
        flag = 1;
        goto exit;
    }

    if (func_ov068_0226c0e0(obj, ptr)) {
        func_ov068_0226cce8(obj, ptr, 0x13);
        flag = 1;
        goto exit;
    }

    if (func_ov068_0226cc20(obj, ptr)) {
        func_ov068_0226cce8(obj, ptr, 7);
        flag = 1;
        goto exit;
    }

    if (func_ov068_0226c520(obj, ptr)) {
        flag = 1;
        goto exit;
    }

    if (func_ov068_02266e7c(&((const UnkStruct_0226befc *) ptr)->unk_9F4[0])) {
        func_ov068_0226cce8(obj, ptr, 0x0b);
        flag = 1;
        goto exit;
    }

    if (func_ov068_0226c1dc(obj, ptr)) {
        flag = 1;
        goto exit;
    }

    if (func_ov068_0226c034(obj, ptr)) {
        func_ov068_0226cce8(obj, ptr, 0x17);
        flag = 1;
        goto exit;
    }

    if (((const UnkStruct_0226befc *) ptr)->unk_98 != 0) {
        if (func_ov068_0226c63c(obj, ptr)) {
            flag = 1;
        }
    }

exit:
    return flag;
}
