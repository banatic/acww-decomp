/* system_packet_2: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0207553c @ 0x0207553c, 0xc bytes, Thumb
 * func_02075514 @ 0x02075514, 0x28 bytes, Thumb
 * func_020754e8 @ 0x020754e8, 0x2c bytes, Thumb
 */

extern void func_020a6cd4(int);
extern void *data_020ccf94;
extern int func_02073d68(void *arg);
extern void func_02073d6c(void *arg, unsigned char byte);
extern int func_020b65c4(void);
extern int func_020a132c(void);
extern void func_020a125c(int, int);

void func_0207553c(unsigned char *payload, unsigned int length, int player)
{
    func_020a6cd4(1);
}

void func_02075514(unsigned char *payload, unsigned int length, int player)
{
    void *value;
    value = data_020ccf94;
    if (func_02073d68(value) == 3) {
        func_02073d6c(value, *payload);
    }
}

void func_020754e8(unsigned char *payload, unsigned int length, int player)
{
    if (func_020b65c4() == 0xd || func_020b65c4() == 0x2f) {
        if (func_020a132c() != 0) {
            func_020a125c(func_020a132c(), 1);
        }
    }
}
