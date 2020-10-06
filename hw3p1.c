#include <stdio.h>
#define X 0
#define Y 1
typedef enum{FALSE, TRUE} bool;
typedef int tPointi[2];

bool Intersect(tPointi a, tPointi b, tPointi c, tPointi d);
int CrossProduct(tPointi a, tPointi b, tPointi c, tPointi d);
bool LeftOn(tPointi a, tPointi b, tPointi c);
bool Left(tPointi a, tPointi b, tPointi c);
bool Collinear(tPointi a, tPointi b, tPointi c);

//---------------------------------------------------------
// Homework answer starts here
bool RayRayIntersect(tPointi a, tPointi b, tPointi c, tPointi d)
{
    // if the segment ab and cd Intersect, return true
    if (Intersect(a,b,c,d)) return TRUE;
    int cp = CrossProduct(a,b,c,d); // Crossproduct
    if (cp > 0)
        // a has to be on the left of cd
        // and c has to be on the right of ab
        return LeftOn(c,d,a) && !Left(a,b,c);
    else if(cp < 0)
        // a has to be on the right of cd
        // and c has to be on the left of ab
        return !Left(c,d,a) && LeftOn(a,b,c);

    // cp == 0, ab and cd are parallel
    // If not collinear, ab and cd can never intersect
    if (!Collinear(a,b,c)) return FALSE;

    // if ab and cd are parallel to X axis
    // we use X values
    if (a[Y] - b[Y] == 0)
    {
        // if ab is the same direction as cd
        // a[X] - b[X] should have the same sign as c[X] - b[X]
        // and they will intersect
        if ((a[X]-b[X]>0) ^ (c[X]-d[X]<0)) return TRUE;

        // if ab and cd are not in the same direction
        // we have the following situations in which they would intersect:
        // -----------> x axis direction
        // 1.     a---->b   d<--------c
        // 2.     c---->d   b<--------a
        // otherwise ab and cd would not intersect
        return ((a[X] < b[X]) && (b[X] < d[X]) && (d[X] < c[X]))
             || (c[X] < d[X]) && (d[X] < b[X]) && (b[X] < a[X]);
    }
    else // else we use Y values
    {
      // if ab is the same direction as cd
      // a[Y] - b[Y] should have the same sign as c[Y] - b[Y]
      // and they will intersect
      if ((a[Y]-b[Y]>0) ^ (c[Y]-d[Y]<0))
          return TRUE;
      // if ab and cd are not in the same direction
      // we have the following situations in which they would intersect:
      // (Not necessary for ab and cd to be parallel to y axis originally;
      // since ab and cd are collinear, we can project both of them
      // to the y axis without changing the outcome.
      // Therefore we can ignore the x values here)
      // -----------> y axis direction
      // 1.     a---->b   d<--------c
      // 2.     c---->d   b<--------a
      // otherwise ab and cd would not intersect
      return ((a[Y] < b[Y]) && (b[Y] < d[Y]) && (d[Y] < c[Y]))
          || (c[Y] < d[Y]) && (d[Y] < b[Y]) && (b[Y] < a[Y]);
    }
    return FALSE;
}

// Homework answers ends here
// -------------------------------------------------------------------------
// Below are helper funcitons from textbook chapt. 1

int Area2(tPointi a, tPointi b, tPointi c)
{
    return (b[X] - a[X]) * (c[Y] -a[Y]) -
        (c[X] - a[X]) * (b[Y] - a[Y]);
}

bool Left(tPointi a, tPointi b, tPointi c)
{
    return Area2(a, b, c) > 0;
}

bool LeftOn(tPointi a, tPointi b, tPointi c)
{
    return Area2(a, b, c) >= 0;
}

bool Collinear(tPointi a, tPointi b, tPointi c)
{
  return Area2(a,b,c) == 0;
}

bool Xor(bool x, bool y)
{
  return !x ^ !y;
}

bool IntersectProp(tPointi a, tPointi b, tPointi c, tPointi d)
{
  if(
    Collinear(a,b,c) ||
    Collinear(a,b,d) ||
    Collinear(c,d,a) ||
    Collinear(c,d,b)
  )
  return FALSE;

  return Xor(Left(a,b,c), Left(a,b,d))
      && Xor(Left(c,d,a), Left(c,d,b));
}

bool Between(tPointi a, tPointi b, tPointi c)
{
  tPointi ba, ca;
  if(!Collinear(a,b,c))
    return FALSE;
  if(a[X] != b[X])
    return ((a[X] <= c[X]) && (c[X] <= b[X])) ||
           ((a[X] >= c[X]) && c[X]>=b[X]);
  else
    return ((a[Y] <= c[Y]) && (c[Y] <= b[Y])) ||
           ((a[Y] >= c[Y]) && c[Y]>=b[Y]);
}

bool Intersect(tPointi a, tPointi b, tPointi c, tPointi d)
{
  if (IntersectProp(a,b,c,d)) return TRUE;
  else if(Between(a,b,c) || Between(a,b,d) ||Between(c,d,a) || Between(c,d,b))
    return TRUE;
  else
    return FALSE;
}

int CrossProduct(tPointi a, tPointi b, tPointi c, tPointi d)
{
    return (b[X] - a[X]) * (d[Y]-c[Y]) - (b[Y] - a[Y]) * (d[X] - c[X]);
}



int main()
{
    tPointi a,b,c,d;
    a[0] = 5;
    a[1] = 5;

    b[0] = 7;
    b[1] = 5;

    c[X] = 5;
    c[Y] = 2;

    d[X] = 5;
    d[Y] = 3;

    printf("Crossproduct: %i\n", CrossProduct(a,b,c,d));
    printf("Intersect: %i", RayRayIntersect(a, b, c, d));

    return 0;
}
