#include<iostream>
using namespace std;

//mistakes
struct OutOfDequeError{
    int out;
    OutOfDequeError(int num){ out = num; }
};

void OutOfDequeErrorCall(OutOfDequeError mistake){
        cerr << "\nOut of deck\nCalled index " << mistake.out << "\n";
        cerr << flush;
}

struct EmptyDequeMistake{};

void EmptyDequeMistakeCall(){
    cerr << "\nYou've tried to delete the element when the size is already zero!\n";
    cerr << flush;
}

//deque description
template <typename T, int defsize = 0 > class deque
{
protected:
        T *v;
        int len;
        int beg;
        int user_size;
public:
        deque(int N = defsize) : v(nullptr), len(2), user_size(N)
        {
            if(N > 0) v = new T[N + 2];
            if(v) len = N + 2;
            beg = 1;
        }

        ~deque()
        {
            cout << "\nDestructor called!\n";
            delete [] v;
        }

        T& operator[] (const int i)
        {
            if(i >= user_size || i < 0) throw OutOfDequeError(i);
            return v[beg + i];
        }

        int length()
        {
            return user_size;
        }

        void push_back(T x) //нужно изменять размер deque если выходим за пределы
        {
            user_size++;
            v[beg + user_size - 1] = x;
            cout << "beg " << beg << " user_size " << user_size << " len " << len << "\n"; 
            if(beg + user_size - 1 == len)
            {
                cout << "push_back memory increase!\n";
                len = 2 * len;
                T *tmp = new T[len];
                for(int iter = 0; iter < user_size; iter++){
                    tmp[iter + beg] = v[iter + beg];
                    //cout << v[iter] << "\n";
                }
                delete [] v;
                v = tmp;
            }
            
        }

        void push_front(T x) //нужно изменять размер deque если выходим за пределы
        {
            beg--;
            user_size++;
            v[beg] = x;
            cout << "beg " << beg << " user_size " << user_size << " len " << len << "\n"; 
            if(beg == 0)
            {
                cout << "push_front memory increase!\n";
                len = 2 * len;
                T *tmp = new T[len];
                for(int iter = beg; iter < user_size; iter++){
                    tmp[iter + len/2] = v[iter];
                }
                beg = len/2;
                delete [] v;
                v = tmp;
            }
            
        }  

        void pop_back()
        {
            if(user_size == 0) throw EmptyDequeMistake();
            user_size--;
        }

        void pop_front()
        {
            if(user_size == 0) throw EmptyDequeMistake();
            user_size--;
            beg++;
        }

        friend ostream & operator<< (ostream & os, deque & deq)
        {   
            os << "\n";
            for(int iter = 0; iter < deq.length(); iter++){
                os << deq[iter] << " ";
            }
            os << "\n";
            return os;
        }       
};

int main()
{
    cout << "Hallo Walt!\n";
    try
    {
    //проверяю OutOfDequeError
    /*    deque<int> my_deque(2);
        my_deque[0] = 1;
        my_deque[1] = 2;
        cout << my_deque[0] << " " << my_deque[1] << "\n";
        my_deque[2] = 3;
        cout << my_deque[2];
*/

        deque<int> my_deq(2);
        my_deq[0] = 1;
        my_deq[1] = 2;
        my_deq.push_front(3);

        cout << my_deq.length();
        cout << my_deq << endl;

        my_deq.push_back(3);

        cout << my_deq.length();
        cout << my_deq << endl;

        my_deq.push_front(4);

        cout << my_deq.length();
        cout << my_deq << endl;

        my_deq.push_back(8);

        cout << my_deq.length();
        cout << my_deq << endl;

        //cout << my_deq[0] << " " << my_deq[1] << " " << my_deq[2]<< " " << my_deq[3] << "\n";
        //cout << my_deq.length();
        //cout << my_deq << endl;

        my_deq.pop_back();
        my_deq.pop_front();
        cout << my_deq.length();
        cout << my_deq;

        /* //проверяю EmptyDequeMistake
        my_deq.pop_front();
        my_deq.pop_front();
        my_deq.pop_front();
        my_deq.pop_front();
        my_deq.pop_back();
        */
    }
    catch(OutOfDequeError mistake)
    {
        OutOfDequeErrorCall(mistake);
    }
    catch(EmptyDequeMistake)
    {
        EmptyDequeMistakeCall();
    }

    return 0;
}