#pragma once
//Dacz Krisztian, dkim2226, 511/2

template <class T>
class Rendezes {
protected:
    virtual bool kisebb(T a, T b) = 0;
    virtual void csere(T& a, T& b) = 0;
public:
    virtual void rendez(T* tomb, int n) = 0;
};

class Stat {
private:
    unsigned int ido, nHasonlit, nCsere;
    std::clock_t c;

protected:
    void kezd() 
    {
        c = clock();
    }

    void vege() 
    {
        ido = (clock() - c) / (CLOCKS_PER_SEC / 1000);
    }

    void init()
    {
        ido = 0;
        nHasonlit = 0;
        nCsere = 0;
    }

    void incHasonlit()
    {
        nHasonlit++;
    }

    void incCsere() 
    {
        nCsere++;
    }

public:
    Stat() 
    {
        init();
    }

    unsigned int getIdo() 
    {
        return ido;
    }

    unsigned int getHasonlit() 
    {
        return nHasonlit;
    }

    unsigned int getCsere() 
    {
        return nCsere;
    }
};

template <class T>
class BuborekosRendezes : public Rendezes<T> 
{
protected:
    bool kisebb(T a, T b)
    {
        return a < b;
    }

    void csere(T& a, T& b) 
    {
        T temp = a;
        a = b;
        b = temp;
    }

public:
    void rendez(T* tomb, int n) 
    {
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = 0; j < n - i - 1; j++) 
            {
                if (kisebb(tomb[j + 1], tomb[j])) 
                {
                    csere(tomb[j], tomb[j + 1]);
                }
            }
        }
    }
};

template <class T>
class BuborekosRendezesT : public BuborekosRendezes<T>, public Stat 
{
protected:
    bool kisebb(T a, T b)
    {
        incHasonlit();
        return BuborekosRendezes<T>::kisebb(a, b);
    }

    void csere(T& a, T& b) {
        incCsere();
        BuborekosRendezes<T>::csere(a, b);
    }

public:
    void rendez(T* tomb, int n) 
    {
        init();
        kezd();
        BuborekosRendezes<T>::rendez(tomb, n);
        vege();
    }
};

template <class T>
class QuickSort : public Rendezes<T> 
{
private:
    void qsort(T* a, int bal, int jobb)
    {
        if (bal < jobb) {
            int pivot = particional(a, bal, jobb);
            qsort(a, bal, pivot - 1);
            qsort(a, pivot + 1, jobb);
        }
    }

    int particional(T* a, int bal, int jobb) 
    {
        T pivot = a[jobb];
        int i = bal - 1;

        for (int j = bal; j <= jobb - 1; j++) 
        {
            if (kisebb(a[j], pivot)) {
                i++;
                csere(a[i], a[j]);
            }
        }

        csere(a[i + 1], a[jobb]);
        return i + 1;
    }

protected:
    bool kisebb(T a, T b) 
    {
        return a < b;
    }

    void csere(T& a, T& b) 
    {
        T temp = a;
        a = b;
        b = temp;
    }

public:
    void rendez(T* tomb, int n) 
    {
        qsort(tomb, 0, n - 1);
    }
};

template <class T>
class QuickSortT : public QuickSort<T>, public Stat 
{
protected:
    bool kisebb(T a, T b) 
    {
        incHasonlit();
        return QuickSort<T>::kisebb(a, b);
    }

    void csere(T& a, T& b) 
    {
        incCsere();
        QuickSort<T>::csere(a, b);
    }

public:
    void rendez(T* tomb, int n) 
    {
        init();
        kezd();
        QuickSort<T>::rendez(tomb, n);
        vege();
    }
};
