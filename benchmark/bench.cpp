#include <chrono>
#include <fstream>
#include <iostream>
#include <math.h>
#include <pthread.h>
#include <random>
#include <string>
#include <thread>
#include <vector>

// #define DEBUG

typedef struct thread_arg {
    pthread_t th_;
    pthread_mutex_t mutex_;
    std::uint64_t num_;
    std::uint64_t st_;
    std::uint64_t ed_;
    bool* stop_;
    bool* can_divide_;
};

void* isPrime(void* arg)
{
    using namespace std;
    uint64_t temp    = 0;
    thread_arg* data = (thread_arg*)arg;
    if (*data->stop_ == true) {
        return nullptr;
    } else {
        for (uint64_t i = data->st_; i <= data->ed_; i += 2) {
            temp = data->num_ % i;
            if (temp == 0) {
                pthread_mutex_lock(&data->mutex_);
                *data->can_divide_ = true;
                *data->stop_       = true;
                pthread_mutex_unlock(&data->mutex_);

#ifdef DEBUG
                cout << data->num_ << "is not prime" << endl;
                cout << "i: " << i << endl;
#endif
                return nullptr;
            }
        }
    }
    return nullptr;
}

void print_thread_arg(thread_arg th)
{
    using namespace std;
    cout << "num: " << th.num_ << endl;
    cout << "st: " << th.st_ << endl;
    cout << "ed: " << th.ed_ << endl;
}

std::vector<uint64_t> get_prime_list()
{
    using namespace std;
    ifstream fs;
    fs.open("../PrimeList.csv", ios::in);
    char temp[100];
    vector<uint64_t> prime_list;
    while (fs.getline(temp, 100, '\n')) {
        prime_list.push_back(stoull(temp, nullptr, 10));
    }
    return prime_list;
}

int main()
{
    using namespace std;
    uint64_t num;
    cout << "you have " << thread::hardware_concurrency() << " threads" << endl;

    auto start = chrono::system_clock::now();

    vector<thread_arg> th(thread::hardware_concurrency() * 2);
    bool can_divide = false;
    bool stop       = false;

    vector<uint64_t> prime_list = get_prime_list();
    uint times                  = prime_list.size();

    while (times) {

        can_divide = false;
        stop       = false;
        num        = prime_list[times - 1];
        cout << "\r" << prime_list.size() - times + 1 << " / " << prime_list.size() << string(20, ' ') << flush;
        long double sq_num = sqrt(static_cast<double>(num));

        for (size_t i = 0; i < th.size(); i++) {
            th[i].num_ = num;
            th[i].st_  = sq_num / th.size() * i;
            th[i].st_  = ((th[i].st_ <= 1) ? 3 : th[i].st_);
            th[i].ed_  = th[i].st_ + (sq_num / th.size());
            if (th[i].st_ % 2 == 0) {
                th[i].st_++;
            }
            th[i].can_divide_ = &can_divide;
            th[i].stop_       = &stop;
            // print_thread_arg(th[i]);
            pthread_create(&th[i].th_, NULL, isPrime, &th[i]);
        }

        for (size_t i = 0; i < th.size(); i++) {
            pthread_join(th[i].th_, NULL);
        }
        if (!can_divide) {
            times--;
        }
    }
    auto end  = chrono::system_clock::now();
    auto time = end - start;
    auto msec = chrono::duration_cast<chrono::milliseconds>(time).count();
    cout << msec << "[msec]" << endl;

    return 0;
}