#include <iostream>
#include <math.h>
#include <pthread.h>
#include <random>
#include <thread>
#include <vector>

typedef struct thread_arg {
    pthread_t th_;
    std::uint64_t num_;
    std::uint64_t st_;
    std::uint64_t ed_;
    bool is_prime_;
};

void* isPrime(void* arg)
{
    using namespace std;
    uint64_t temp    = 0;
    thread_arg* data = (thread_arg*)arg;
    for (uint64_t i = data->st_; i <= data->ed_; i += 2) {
        temp = data->num_ % i;
        if (temp == 0) {
            data->is_prime_ = true;
            return nullptr;
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

int main(int argc, char* argv[])
{
    using namespace std;
    uint64_t num;
    random_device rnd; // 非決定的な乱数生成器
    mt19937_64 mt(rnd());

    uint times = 0;
    if (argc == 2 && argv[1] > 0) {
        times = atoi(argv[1]);
    } else {
        cout << "times: ";
        cin >> times;
    }

    vector<thread_arg> th(thread::hardware_concurrency() * 2);
    while (times--) {
        num = mt();
        if (num % 2 == 0) {
            num++;
        }
        // cout << "num: " << num << endl;
        uint64_t sq_num = sqrt(static_cast<double>(num));

        for (size_t i = 0; i < th.size(); i++) {
            th[i].num_ = num;
            th[i].st_  = sq_num / th.size() * i;
            if (th[i].st_ % 2 == 0) {
                th[i].st_++;
            }
            th[i].ed_       = th[i].st_ + sq_num / th.size() * (i + 1);
            th[i].is_prime_ = false;
            pthread_create(&th[i].th_, NULL, isPrime, &th[i]);
        }
        for (size_t i = 0; i < th.size(); i++) {
            pthread_join(th[i].th_, NULL);
        }
        for (size_t i = 0; i < th.size(); i++) {
            if (th[i].is_prime_) {
                cout << num << " is prime" << endl;
                break;
            }
        }
    }

    return 0;
}