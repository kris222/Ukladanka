#ifndef MOJESZABLONY_H
#define MOJESZABLONY_H
#include <vector>
///
/// Szablon funkcji do rysowania objektu (jesli ma metode Rysuj())
/// (nieuzyty )
///
template <typename  T>
void Rysuj(T& x )
{
     x.Rysuj();
}
///
/// Szablon funkcji do sortowania babelkowego vectora
///
template < typename T > void Sortuj(  std::vector<T> &a, int n )
{
    int i;
    int j;
    T temp ;
    for(i=0; i<n; i++)
    {
        for(j=i+1; j<n; j++)
        {
            if(a[i]>a[j])
            {
                temp=a[i];
                a[i]=a[j];
                a[j]=temp;
            }
        }
    }
}
#endif // MOJESZABLONY_H
