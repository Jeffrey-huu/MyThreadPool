#include <iostream>
#include <chrono>
#include <thread>
using namespace std;

#include "threadpool.h"

/*
举例：1 + ... + 30000的和
thread1: 1 + ... + 10000
thread2: 10001 + ... + 20000
...
main thread: 给每一个线程分配计算的区间，并等待它们算完返回结果，合并最终的结果即可
*/

using uLong = unsigned long long;

class MyTask : public Task
{
public:
    MyTask(int begin, int end) : begin_(begin), end_(end) {}

    Any run()
    {
        std::cout << "tid:" << std::this_thread::get_id() << "begin!" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3));

        uLong sum = 0;
        for (uLong i = begin_; i <= end_; i++)
            sum += i;

        std::cout << "tid:" << std::this_thread::get_id() << "end!" << std::endl;

        return sum;
    }

private:
    int begin_;
    int end_;
};

int main()
{
    {
        ThreadPool pool;
        //用户自己设置线程池的工作模式
        pool.setMode(PoolMode::MODE_CACHED);
        //开始启动线程池
        pool.start(2);

        // Result res1 = pool.submitTask(std::make_shared<MyTask>(1, 100000000));
        // Result res2 = pool.submitTask(std::make_shared<MyTask>(100000001, 200000000));
        pool.submitTask(std::make_shared<MyTask>(100000001, 200000000));
        pool.submitTask(std::make_shared<MyTask>(100000001, 200000000));
        pool.submitTask(std::make_shared<MyTask>(100000001, 200000000));

        //uLong sum1 = res1.get().cast_<uLong>();
        //cout << sum1 << endl; 
    }

    cout << "main over!" << endl;
    getchar();
    
#if 0
    {
        ThreadPool pool;
        // 用户自己设置线程池的工作模式
        pool.setMode(PoolMode::MODE_CACHED);
        // 开始启动线程池
        pool.start(4);

        Result res1 = pool.submitTask(std::make_shared<MyTask>(1, 100000000));
        Result res2 = pool.submitTask(std::make_shared<MyTask>(100000001, 200000000));
        Result res3 = pool.submitTask(std::make_shared<MyTask>(200000001, 300000000));
        pool.submitTask(std::make_shared<MyTask>(200000001, 300000000));

        pool.submitTask(std::make_shared<MyTask>(200000001, 300000000));
        pool.submitTask(std::make_shared<MyTask>(200000001, 300000000));

        // 随着task被执行完，task对象没了，依赖于task对象的Result对象也没了
        uLong sum1 = res1.get().cast_<uLong>();  
        uLong sum2 = res2.get().cast_<uLong>();
        uLong sum3 = res3.get().cast_<uLong>();

        cout << (sum1 + sum2 + sum3) << endl;
    }
    


    /*uLong sum = 0;
    for (uLong i = 1; i <= 300000000; i++)
        sum += i;
    cout << sum << endl;*/

    /*pool.submitTask(std::make_shared<MyTask>());
    pool.submitTask(std::make_shared<MyTask>());
    pool.submitTask(std::make_shared<MyTask>());
    pool.submitTask(std::make_shared<MyTask>());
    pool.submitTask(std::make_shared<MyTask>());
    pool.submitTask(std::make_shared<MyTask>());
    pool.submitTask(std::make_shared<MyTask>());
    pool.submitTask(std::make_shared<MyTask>());
    pool.submitTask(std::make_shared<MyTask>());*/
 
    getchar();

#endif
    //return 0;
}