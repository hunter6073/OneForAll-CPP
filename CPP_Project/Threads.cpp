// this script contains a demonstration of thread usage

# include <iostream> // this is the library for c++
# include <thread> // library for threds
# include "util.h" // utility library to format output

using namespace std;

// A dummy function 
void foo(int Z)
{
    for (int i = 0; i < Z; i++) {
        cout << "Thread using function pointer as callable\n";
    }
}

// A callable object 
class thread_obj {
public:
    void operator()(int x)
    {
        for (int i = 0; i < x; i++)
            cout << "Thread using function object as callable\n";
    }
};


void ShowThreads() {// show the common usage of threads

    cout << "[Thread01] Threads 1 and 2 and 3 "
        "operating independently:" << endl;

    // This thread is launched by using  
    // function pointer as callable 
    thread th1(foo, 3);

    // This thread is launched by using 
    // function object as callable 
    thread th2(thread_obj(), 3); // give the thread function a parameter of 3

    // Define a Lambda Expression 
    auto f = [](int x) {
        for (int i = 0; i < x; i++)
            cout << "Thread using lambda"
            " expression as callable\n";
    };

    // This thread is launched by using  
    // lamda expression as callable 
    thread th3(f, 3);

    // Wait for the threads to finish 
    // Wait for thread t1 to finish, it means all functions in t1 will be performed in a whole
    th1.join();

    /* Note:
    detatch() doesn't kill thread either. Actually it tells std::thread that this thread should continue
    to run even when std::thread object is destroyed. 
    C++ checks in std::thread destructor that thread is either joined or 
    detached and terminates program if this check fails
    */
    th2.detach();

    // Wait for thread t3 to finish 
    th3.join();

}
