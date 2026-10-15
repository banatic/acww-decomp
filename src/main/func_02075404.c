/* func_02075404 @ 0x02075404, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b65c4(void);
extern void *func_020a132c(void);
extern int func_020ec260(void);
extern void func_020a1238(void *, int, unsigned char);

void func_02075404(unsigned char *payload, unsigned int length, int player)
{
    if (func_020b65c4() == 0x2e || func_020b65c4() == 9) {
        void *p = func_020a132c();
        if (p != 0) {
            if (func_020ec260() == 0) {
                func_020a1238(p, player, *payload);
            } else {
                func_020a1238(p, 0, *payload);
            }
        }
    }
}
