
#ifndef _ConvertTime_h
#define _ConvertTime_h

#include <time.h>
#include <TimeLib.h>
//fortunately TimeLib and time.h's definitions of time_t are both unsigned 32 bit, otherwise there might be trouble.

//converts TimeLib's time representations to time.h's representations
inline void convertToTimeH(tmElements_t &timelib, tm &timeh){
  time_t t = makeTime(timelib) - UNIX_OFFSET;
  localtime_r(&t, &timeh);
}
inline void convertToTimeH(time_t timelib, tm &timeh){
  time_t t = timelib - UNIX_OFFSET;
  localtime_r(&t, &timeh);
}
inline time_t convertToTimeH(tmElements_t &timelib){
  return makeTime(timelib) - UNIX_OFFSET;
}
inline time_t convertToTimeH(time_t timelib){
  return timelib - UNIX_OFFSET;
}

//converts time.h's time representations to TimeLib's representations
inline void convertToTimeLib(tm &timeh, tmElements_t &timelib){
  breakTime(mktime(&timeh) + UNIX_OFFSET, timelib);
}
inline void convertToTimeLib(time_t timeh, tmElements_t &timelib){
  breakTime(timeh + UNIX_OFFSET, timelib);
}
inline time_t convertToTimeLib(tm &timeh){
  return mktime(&timeh) + UNIX_OFFSET;
}
inline time_t convertToTimeLib(time_t timeh){
  return timeh + UNIX_OFFSET;
}
#endif _ConvertTime_h
