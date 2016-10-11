#ifndef MYLIB_NUMERICALOPERATION_HH
#define MYLIB_NUMERICALOPERATION_HH

#include "HeadersSL.hh"
#include "HeadersRoot.hh"
using namespace std;

/*!
  @fn template < typename T > T GetMean( vector < T >& vval )
  @brief get mean of the argument
  @param vval vector of T 
*/


template < typename T >
T GetMax( T* values , int num )
{
  T max = values[0];
  for( int i=1; i<num; i++ )
    if( max < values[i] )
      max = values[i];

  return max;
}


template < typename T >
T GetMean( vector < T >& vval )
{
  return accumulate( vval.begin(), vval.end(), 0 ) / (T)vval.size();
}

template < typename T >
T GetMean( T* val , int size, int first , int last )
{
  assert( last <= size );

  T sum = 0;
  for( int i=first; i<last; i++ )
    sum += val[i];

  return sum/(T)( last - first );
}

template < typename T >
T GetMean( T* val , int size, int first )
{
  int last = sizeof( val ) / sizeof( val[0] );
  return GetMean<T>( val , size, first , last );
}

template < typename T >
T GetMean( T* val , int size )
{
  return GetMean<T>( val , size, 0 );
}

template < typename T >
T GetMin( T* values , int num )
{
  T min = values[0];
  for( int i=1; i<num; i++ )
    if( min > values[i] )
      min = values[i];

  return min;
}



/*!
  @fn template < typename T > T GetStdDev( vector < T >& vval )
  @brief get standard deviation of the argument
  @param vval vector of T 
*/
template < typename T >
T GetStdDev( vector < T >& vval )
{

  T mean = GetMean<T>( vval );
  T sum = 0;

  for( int i=0; i<vval.size(); i++ )
    sum += pow( mean - vval[i] , 2 );

  return sqrt(sum / (T)vval.size() );
}



/*!
  @fn double Deg2Rad( double degree )
  @param
  @return
  @brief
 */
double Deg2Rad( double degree );

/*!
  @fn double Rad2Deg( double radian )
  @param
  @return
  @brief
 */
double Rad2Deg( double radian );


#endif
