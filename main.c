#ifndef __PROGTEST__
#include <stdio.h>
#include <assert.h>
#define INVALID_DATE (-1)
#endif /* __PROGTEST__ */


int passedLeapYears ( int y ){
  int i;
  int ply = 0;
  for (i = 2000; i <= y; ++i){
    if ((i % 4 == 0 && i % 100 != 0) || (i % 400 == 0 && i % 4000 != 0)){
      ++ply;
    }
  }
  return ply;
}

int isLeapYear ( int y ){
  if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0 && y % 4000 != 0)){
    return 1;
  }
  else
    return 0;
}

int monthsToDays ( int m ){
  int i;
  int days = 0;
  for (i = 1; i <= m; ++i){
    switch (i){
      case 1:
        days += 31;
        break;
      case 2:
        days += 28;
        break;
      case 3:
        days += 31;
        break;
      case 4:
        days += 30;
        break;
      case 5:
        days += 31;
        break;
      case 6:
        days += 30;
        break;
      case 7:
        days += 31;
        break;
      case 8:
        days += 31;
        break;
      case 9:
        days += 30;
        break;
      case 10:
        days += 31;
        break;
      case 11:
        days += 30;
        break;
      case 12:
        days += 31;
        break;
    }
  }
  return days;
}

int convertToDays ( int y, int m, int d ){
  int days = 0;

  days = ( y - 2000 ) * 365 + passedLeapYears( y ) + monthsToDays( m-1 ) + d;

  if ( isLeapYear(y) == 1 && m < 3 )
    days -= 1;
  return days;
}

int getYears ( int days ){
  int years = 2000;

  while (days > 365 + isLeapYear(years)){
    days -= (365 + isLeapYear(years));
    years += 1;
  }
  return years;
}

int getMonths ( int days ){
  int years = getYears(days);
  int passedLeapYs = passedLeapYears(years);
  int unor = 28;
  int m = 1;
  int d = days - (years-2000) * 365;
  d -= passedLeapYs;

  if ( isLeapYear(years) == 1){
    unor = 29;
    d += 1;
  }


  while (d > 0){
    switch (m){
      case 1:
        d -= 31;
        m += 1;
        break;
      case 2:
        d -= unor;
        m += 1;
        break;
      case 3:
        d -= 31;
        m += 1;
        break;
      case 4:
        d -= 30;
        m += 1;
        break;
      case 5:
        d -= 31;
        m += 1;
        break;
      case 6:
        d -= 30;
        m += 1;
        break;
      case 7:
        d -= 31;
        m += 1;
        break;
      case 8:
        d -= 31;
        m += 1;
        break;
      case 9:
        d -= 30;
        m += 1;
        break;
      case 10:
        d -= 31;
        m += 1;
        break;
      case 11:
        d -= 30;
        m += 1;
        break;
      case 12:
        d -= 31;
        m += 1;
        break;
    }
  }
  if (d <= 0){
    switch (m){
      case 1:
        d += 31;
        break;
      case 2:
        d += unor;
        break;
      case 3:
        d += 31;
        break;
      case 4:
        d += 30;
        break;
      case 5:
        d += 31;
        break;
      case 6:
        d += 30;
        break;
      case 7:
        d += 31;
        break;
      case 8:
        d += 31;
        break;
      case 9:
        d += 30;
        break;
      case 10:
        d += 31;
        break;
      case 11:
        d += 30;
        break;
      case 12:
        d += 31;
        break;
    }
    m -= 1;
  }
  return m;
}

int getDays( int days ){
  int d = days + 1 - convertToDays(getYears(days), getMonths(days), 1);
  return d;
}


double hoursToDay ( double h, double m, double s){
  return (( h * 3600 + m * 60 + s ) / ( 24 * 60 * 60 ));
}

int checkDate( int y, int m, int d ){
  int i = 0;
  if (isLeapYear(y) == 1 && m == 2){
    i = 1;
  }

  if (y < 2000 || m < 1 || m > 12 || d < 1 || d > (monthsToDays(m) - monthsToDays(m-1) +i)){
    return 0;
  }
  return 1;
}

int isFullMoon ( int y, int m, int d ){
  if (checkDate(y,m,d) == 1){
    double ref = convertToDays( 2000, 7, 16 ) + hoursToDay( 13, 55, 12 );
    double fullMoonPeriod = 29.53059027;
    double firstFullMoon = 0;

    int days = convertToDays( y, m, d );

    while (ref > 30){
      ref -= fullMoonPeriod;
    }
    firstFullMoon = ref;

    while (days > firstFullMoon){
      firstFullMoon += fullMoonPeriod;
    }
    if (days < firstFullMoon && (days + 1) > firstFullMoon){
      return 1;
    }
    else
      return 0;
  }
  else
    return INVALID_DATE;


}


int prevFullMoon ( int y, int m, int d, int * prevY, int * prevM, int * prevD ){
  if (checkDate(y,m,d) == 1){
    int days = convertToDays( y, m, d ) - 1;

    if (days < 25){
      *prevY = 1999;
      *prevM = 12;
      *prevD = 22;
      return 1;
    }

    while (isFullMoon(getYears(days), getMonths(days), getDays(days)) != 1){
      days -= 1;
    }
    *prevY = getYears(days);
    *prevM = getMonths(days);
    *prevD = getDays(days);
    return 1;
  }
  else
    return INVALID_DATE;



}

int nextFullMoon ( int y, int m, int d, int * nextY, int * nextM, int * nextD ){
  if (checkDate(y,m,d) == 1){
    int days = convertToDays( y, m, d ) + 1;
    while (isFullMoon(getYears(days), getMonths(days), getDays(days)) != 1){

      days += 1;
    }
    *nextY = getYears(days);
    *nextM = getMonths(days);
    *nextD = getDays(days);
    return 1;
  }
  else
    return INVALID_DATE;

}
#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
  int y, m, d;

  
  assert ( nextFullMoon ( 2029, 2, 28, &y, &m, &d ) == 1 && y == 2029 && m == 3 && d == 29 );


  assert ( prevFullMoon ( 2045, 3, 1, &y, &m, &d ) == 1 && y == 2045 && m == 2 && d == 1 );
  assert ( nextFullMoon ( 2012, 8, 22, &y, &m, &d ) == 1 && y == 2012 && m == 9 && d == 1 );
  assert ( nextFullMoon ( 2026, 5, 26, &y, &m, &d ) == 1 && y == 2026 && m == 5 && d == 31 );
  assert ( isFullMoon (2026, 5, 1) == 1 );
  assert ( nextFullMoon ( 2026, 4, 4, &y, &m, &d ) == 1 && y == 2026 && m == 5 && d == 1 );
  assert ( nextFullMoon ( 2026, 5, 26, &y, &m, &d ) == 1 && y == 2026 && m == 5 && d == 31 );
  assert ( prevFullMoon ( 2037, 5, 21, &y, &m, &d ) == 1 && y == 2037 && m == 4 && d == 29 );
  assert ( prevFullMoon ( 2100, 10, 17, &y, &m, &d ) == 1 && y == 2100 && m == 9 && d == 18 );
  assert ( prevFullMoon (2025, 7, 10, &y, &m, &d ) == 1 && y == 2025 && m == 6 && d == 11);
  assert ( prevFullMoon ( 2037, 1, 15, &y, &m, &d ) == 1 && y == 2037 && m == 1 && d == 1 );
  assert ( prevFullMoon ( 2047, 3, 11, &y, &m, &d ) == 1 && y == 2047 && m == 2 && d == 10);
  assert ( prevFullMoon ( 2010, 1, 30, &y, &m, &d ) == 1 && y == 2009 && m == 12 && d == 31);
  assert ( nextFullMoon ( 2029, 2, 28, &y, &m, &d ) == 1 && y == 2029 && m == 3 && d == 29 );
  //
  assert ( isFullMoon ( 2007, 5, 31 ) == 1 );
  assert ( isFullMoon ( 2017, 11, 4 ) == 1 );

  assert ( prevFullMoon ( 2000, 1, 4, &y, &m, &d ) == 1 && y == 1999 && m == 12 && d == 22 );
  //
  assert ( prevFullMoon ( 2007, 6, 5, &y, &m, &d ) == 1 && y == 2007 && m == 5 && d == 31 );
  assert ( prevFullMoon ( 2000, 2, 18, &y, &m, &d ) == 1 && y == 2000 && m == 1 && d == 21 );
  assert ( prevFullMoon ( 20888, 3, 24, &y, &m, &d ) == 1 && y == 20888 && m == 2 && d == 24 );
  assert ( prevFullMoon ( 2100, 12, 31, &y, &m, &d ) == 1 && y == 2100 && m == 12 && d == 16);
  assert ( prevFullMoon ( 2029, 1, 2, &y, &m, &d ) == 1 && y == 2028 && m == 12 && d == 31);
  assert ( prevFullMoon ( 20048, 7, 28, &y, &m, &d ) == 1 && y == 20048 && m == 7 && d == 2);
  assert ( prevFullMoon ( 2000, 1, 21, &y, &m, &d ) == 1  && y == 1999 && m == 12 && d == 22 );
  assert ( prevFullMoon ( 2048, 2, 26, &y, &m, &d ) == 1 && y == 2048 && m == 1 && d == 30);

  assert ( isFullMoon ( 2000, 14, 10 ) == INVALID_DATE );
  assert ( prevFullMoon ( 2000, 11, 31, &y, &m, &d ) == INVALID_DATE );
  assert ( nextFullMoon ( 2001, 2, 29, &y, &m, &d ) == INVALID_DATE );
  assert ( prevFullMoon ( 2100, 2, 29, &y, &m, &d ) == INVALID_DATE );

  assert ( isFullMoon ( 2000, 7, 16 ) == 1 );
  assert ( isFullMoon ( 2017, 1, 11 ) == 0 );
  assert ( isFullMoon ( 2017, 1, 12 ) == 1 );
  assert ( isFullMoon ( 2017, 1, 13 ) == 0 );
  assert ( isFullMoon ( 2017, 11, 3 ) == 0 );
  assert ( isFullMoon ( 2017, 11, 4 ) == 1 );
  assert ( isFullMoon ( 2017, 11, 5 ) == 0 );
  assert ( isFullMoon ( 2019, 12, 11 ) == 1 );
  assert ( isFullMoon ( 2019, 12, 12 ) == 0 );
  assert ( isFullMoon ( 2019, 12, 13 ) == 0 );

  // assert ( prevFullMoon ( 2000, 1, 1, &y, &m, &d ) == 1 && y == 1999 && m == 12 && d == 22 );
  assert ( prevFullMoon ( 2017, 1, 11, &y, &m, &d ) == 1 && y == 2016 && m == 12 && d == 14 );
  assert ( prevFullMoon ( 2017, 1, 12, &y, &m, &d ) == 1 && y == 2016 && m == 12 && d == 14 );
  assert ( prevFullMoon ( 2017, 1, 13, &y, &m, &d ) == 1 && y == 2017 && m == 1 && d == 12 );
  assert ( prevFullMoon ( 2017, 11, 3, &y, &m, &d ) == 1 && y == 2017 && m == 10 && d == 5 );
  assert ( prevFullMoon ( 2017, 11, 4, &y, &m, &d ) == 1 && y == 2017 && m == 10 && d == 5 );
  assert ( prevFullMoon ( 2017, 11, 5, &y, &m, &d ) == 1 && y == 2017 && m == 11 && d == 4 );
  assert ( prevFullMoon ( 2019, 12, 11, &y, &m, &d ) == 1 && y == 2019 && m == 11 && d == 12 );
  assert ( prevFullMoon ( 2019, 12, 12, &y, &m, &d ) == 1 && y == 2019 && m == 12 && d == 11 );
  assert ( prevFullMoon ( 2019, 12, 13, &y, &m, &d ) == 1 && y == 2019 && m == 12 && d == 11 );
  assert ( nextFullMoon ( 2017, 1, 11, &y, &m, &d ) == 1 && y == 2017 && m == 1 && d == 12 );
  assert ( nextFullMoon ( 2017, 1, 12, &y, &m, &d ) == 1 && y == 2017 && m == 2 && d == 11 );
  assert ( nextFullMoon ( 2017, 1, 13, &y, &m, &d ) == 1 && y == 2017 && m == 2 && d == 11 );
  assert ( nextFullMoon ( 2017, 11, 3, &y, &m, &d ) == 1 && y == 2017 && m == 11 && d == 4 );
  assert ( nextFullMoon ( 2017, 11, 4, &y, &m, &d ) == 1 && y == 2017 && m == 12 && d == 3 );
  assert ( nextFullMoon ( 2017, 11, 5, &y, &m, &d ) == 1 && y == 2017 && m == 12 && d == 3 );
  assert ( nextFullMoon ( 2019, 12, 11, &y, &m, &d ) == 1 && y == 2020 && m == 1 && d == 10 );
  assert ( nextFullMoon ( 2019, 12, 12, &y, &m, &d ) == 1 && y == 2020 && m == 1 && d == 10 );
  assert ( nextFullMoon ( 2019, 12, 13, &y, &m, &d ) == 1 && y == 2020 && m == 1 && d == 10 );
  assert ( nextFullMoon ( 2000, 2, 29, &y, &m, &d ) == 1 && y == 2000 && m == 3 && d == 20 );
  assert ( isFullMoon ( 2017, 1, 12 ) == 1 );
  assert ( isFullMoon ( 2017, 2, 11 ) == 1 );
  assert ( isFullMoon ( 2017, 3, 12 ) == 1 );
  assert ( isFullMoon ( 2017, 4, 11 ) == 1 );
  assert ( isFullMoon ( 2017, 5, 10 ) == 1 );
  assert ( isFullMoon ( 2017, 6, 9 ) == 1 );
  assert ( isFullMoon ( 2017, 7, 9 ) == 1 );
  assert ( isFullMoon ( 2017, 8, 7 ) == 1 );
  assert ( isFullMoon ( 2017, 9, 6 ) == 1 );
  assert ( isFullMoon ( 2017, 10, 5 ) == 1 );
  assert ( isFullMoon ( 2017, 11, 4 ) == 1 );
  assert ( isFullMoon ( 2017, 12, 3 ) == 1 );
  assert ( isFullMoon ( 2018, 1, 2 ) == 1 );
  assert ( isFullMoon ( 2018, 1, 31 ) == 1 );
  assert ( isFullMoon ( 2018, 3, 2 ) == 1 );
  assert ( isFullMoon ( 2018, 3, 31 ) == 1 );
  assert ( isFullMoon ( 2018, 4, 30 ) == 1 );
  assert ( isFullMoon ( 2018, 5, 29 ) == 1 );
  assert ( isFullMoon ( 2018, 6, 28 ) == 1 );
  assert ( isFullMoon ( 2018, 7, 27 ) == 1 );
  assert ( isFullMoon ( 2018, 8, 26 ) == 1 );
  assert ( isFullMoon ( 2018, 9, 25 ) == 0 );
  assert ( isFullMoon ( 2018, 10, 24 ) == 1 );
  assert ( isFullMoon ( 2018, 11, 23 ) == 1 );
  assert ( isFullMoon ( 2018, 12, 22 ) == 1 );
  assert ( isFullMoon ( 2019, 1, 21 ) == 1 );
  assert ( isFullMoon ( 2019, 2, 19 ) == 1 );
  assert ( isFullMoon ( 2019, 3, 21 ) == 1 );
  assert ( isFullMoon ( 2019, 4, 19 ) == 1 );
  assert ( isFullMoon ( 2019, 5, 18 ) == 0 );
  assert ( isFullMoon ( 2019, 6, 17 ) == 1 );
  assert ( isFullMoon ( 2019, 7, 16 ) == 0 );
  assert ( isFullMoon ( 2019, 8, 15 ) == 1 );
  assert ( isFullMoon ( 2019, 9, 14 ) == 1 );
  assert ( isFullMoon ( 2019, 10, 13 ) == 1 );
  assert ( isFullMoon ( 2019, 11, 12 ) == 1 );
  assert ( isFullMoon ( 2019, 12, 12 ) == 0 );
  assert ( isFullMoon ( 2004, 2, 29 ) == 0 );
  return 0;
}
#endif /* __PROGTEST__ */
