/* func_020b9fd0 @ 0x020b9fd0, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ba13c(void *p);
extern void func_020ba184(void *p);
extern void func_020ba160(void *p);

struct data {
    unsigned char pad_00[0xe];
    unsigned char type;
    unsigned char pad_0F;
    int value;
};

int func_020b9fd0(struct data *obj)
{
    switch (obj->type) {
        case 0:
            func_020ba13c(&obj->value);
            break;
        case 1:
            func_020ba184(&obj->value);
            break;
        case 2:
            func_020ba160(&obj->value);
            break;
    }
    return 1;
}
