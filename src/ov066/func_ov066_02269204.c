/* func_ov066_02269204 @ 0x02269204, 0x38 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

typedef void (*handler_t)(void *);

struct ov066_0226bdf4 {
    char pad_00[0xbc];
    handler_t handler;
};

extern struct ov066_0226bdf4 *data_ov066_0226bdf4;

void func_ov066_02269204(void *arg)
{
    if (data_ov066_0226bdf4->handler) {
        data_ov066_0226bdf4->handler(arg);
    }
}
