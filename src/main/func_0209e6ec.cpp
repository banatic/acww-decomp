/* func_0209e6ec @ 0x0209e6ec, 0xb0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0209e6ec;
typedef void (UnkStruct_0209e6ec::*PMF)();

extern PMF data_020e367c;
extern PMF data_020e3654;
extern PMF data_020e366c;
extern PMF data_020e3664;
extern PMF data_020e3684;
extern PMF data_020e3674;
extern PMF data_020e365c;

extern int data_021dc760;
extern PMF data_021dc770[7];

extern "C" void func_0209e6ec(UnkStruct_0209e6ec *self, int idx)
{
    if (!(data_021dc760 & 1)) {
        data_021dc770[0] = data_020e367c;
        data_021dc770[1] = data_020e3654;
        data_021dc770[2] = data_020e366c;
        data_021dc770[3] = data_020e3664;
        data_021dc770[4] = data_020e3684;
        data_021dc770[5] = data_020e3674;
        data_021dc770[6] = data_020e365c;
        data_021dc760 |= 1;
    }
    (self->*data_021dc770[idx])();
}
