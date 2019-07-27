#ifndef	__CEJU_H
#define	__CEJU_H

#include "my_define.h"

extern void InitUltrasonicDistance(void);  

extern unsigned int getDistance(void);  
  
extern unsigned int getDistanceState(void);  
  
extern unsigned char refreshDistance(void);  

void chaoshengbo(void);

void chaoshengbo_2(void);

extern unsigned char refreshDistance_2(void);
#endif
