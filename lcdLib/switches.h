#ifndef lcd_switches
#define lcd_switches

void state_select(int);
void switch_init();
void switch_interrupt_handler();
int sec_noBtnPress;
int btnPress;
int soap;
int carrot;
int ball;
int sleep;
#endif
