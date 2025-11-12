/*
 * note that PHP has built-in internet time functionality with the use of
 * the date() command echo date("B"); will display the number of beats.  I
 * find the MilliBeat to be more useful, so i use this code and format it
 * appropriately with printf("%2.2f", swtime());
 * 
 * from Eric Kilfoil @ ypass.net
 */

function swtime()
{
  return((float) ((time()+3600) % 86400) / 86.4);
}
