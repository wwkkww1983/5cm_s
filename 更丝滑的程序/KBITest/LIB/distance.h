#ifndef DISTANCE_H_
#define DISTANCE_H_

#include "common.h"


#define SIDE_OUTOFLINE_FLAG                     ((DISTANCE_FLAGS&(0x01)))
#define FRONT_OUTOFLINE_FLAG                    ((DISTANCE_FLAGS&(0x02)))
#define CIRCLE_FLAG                             ((DISTANCE_FLAGS&(0x04)))
#define SLOPE_FLAG                              ((DISTANCE_FLAGS&(0x08)))
#define SLOPE_ACTIVE_FLAG                       ((DISTANCE_FLAGS&(0x10)))

#define SET_SIDE_OUTOFLINE_FLAG()               (DISTANCE_FLAGS|=(0x01))
#define SET_FRONT_OUTOFLINE_FLAG()              (DISTANCE_FLAGS|=(0x02))
#define SET_CIRCLE_FLAG()                       (DISTANCE_FLAGS|=(0x04))
#define SET_SLOPE_FLAG()                        (DISTANCE_FLAGS|=(0x08))
#define SET_SLOPE_ACTIVE_FLAG()                 (DISTANCE_FLAGS|=(0x10))

#define CLR_SIDE_OUTOFLINE_FLAG()               (DISTANCE_FLAGS&=~(0x01))
#define CLR_FRONT_OUTOFLINE_FLAG()              (DISTANCE_FLAGS&=~(0x02))
#define CLR_CIRCLE_FLAG()                       (DISTANCE_FLAGS&=~(0x04))
#define CLR_SLOPE_FLAG()                        (DISTANCE_FLAGS&=~(0x08))
#define CLR_SLOPE_ACTIVE_FLAG()                 (DISTANCE_FLAGS&=~(0x10))

void ADC_Read(int_16 Data_Res[][10]);
void ADC_Smoothing(int_16 Data_Res[][10],int_16 Data_New[],float Fil[]);
int_16 getX(int_16 Data_New[]);


#endif //DISTANCE_H_
