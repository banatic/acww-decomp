/* func_ov003_0221a090 @ 0x0221a090, 0x44 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_0221a004(void *, int);

struct func_ov003_0221a090_data {
    char pad_00[0x378];
    unsigned short flags;
};

void func_ov003_0221a090(struct func_ov003_0221a090_data *param0, int action)
{
    switch (action) {
        case 0:
            func_ov003_0221a004(param0, 1);
            break;
        case 1:
            func_ov003_0221a004(param0, 1);
            param0->flags &= ~0x100;
            break;
        case 8:
            func_ov003_0221a004(param0, 0);
            break;
    }
}
