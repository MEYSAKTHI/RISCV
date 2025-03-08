#include <bits/stdc++.h>
using namespace std;

/* no write or data access   */
long long int hit = 0;
long long int miss = 0;
long long int miss_pending=0;
long long int write_through=0;
long long int write_noallocate=0;

const uint64_t RANGE_MIN = 0;
const uint64_t RANGE_MAX = (1ULL << 40) - 1;
const uint64_t MEAN = RANGE_MAX / 2;
const double STD_DEV = (1ULL << 14) + (1ULL<<10);
const long long int sample_size = 1ULL<<25; // Adjust to 5000, 10000, or more as needed

struct cach {
    vector<bool> valid = vector<bool>(8, false);
    vector<long long int> tag = vector<long long int>(8, 0);
    vector<bool> miss = vector<bool>(8, false);
};

class cache {
private:
    vector<cach> cache_mem = vector<cach>(64);

public:
    void access(long long int tag, long long int set_index, long long int offset, bool read) {
        for (int i = 0; i < 8; i++) {
            if (cache_mem[set_index].tag[i] == tag && cache_mem[set_index].valid[i] && !cache_mem[set_index].miss[i] ) {
                hit++;
                if(!read)
                {
                    write_through++;
                 //   cout<<"updating memory "<<"writing to memory "<<endl;
                }
                return;
            }
            if (cache_mem[set_index].miss[i] && cache_mem[set_index].tag[i] == tag) {
                miss_pending++;
                hit++;
                set_miss(set_index, i);
                return;
            }
        }
        miss++;
         if(!read)
        {
            write_noallocate++;
        //    cout<<"writing to memory "<<"no allocate "<<endl;
        //    cout<<"writing to memory " << endl;
            return ;
        }
        int index = evict(set_index);
        cache_mem[set_index].tag[index] = tag;
        cache_mem[set_index].valid[index] =  true;
        cache_mem[set_index].miss[index] = true;
    }

    int evict(long long int set_index) {
        for (int i = 0; i < 8; i++) {
            if (!cache_mem[set_index].valid[i]) {
                return i;
            }
        }
        return rand() % 8;
    }

    void set_miss(int set_index, int i) {
        cache_mem[set_index].miss[i] = false;
        cache_mem[set_index].valid[i] = true;
    }
};

class cpu {
private:
    uint64_t num;
    long int tag;
    long int offset;
    long int set_index;
    bool read;
    cache ca;

public:
    uint64_t random_normal_clamped() {
        static std::random_device rd;
        static std::mt19937_64 gen(rd());
        std::normal_distribution<double> dist(MEAN, STD_DEV);
        do {
            num = static_cast<uint64_t>(dist(gen));
        } while (num < RANGE_MIN || num > RANGE_MAX);
        read = rand() % 2;
        return num;
    }

    void splitter() {
        random_normal_clamped();
        long long int ba = (long long int)num / 64;
        tag = ba / 64;
        offset = (num) % 64;
        set_index = ba % 64;
    }

    void execute() {
        splitter();
        ca.access(tag, set_index, offset, read);
    }
};

int main() {
    cpu c;
    for (long long int i = 0; i < sample_size; i++) {
        c.execute();
    }
    cout << "Hit ratio: " << (double)hit / (double)sample_size << endl;
    cout << "Miss ratio: " << (double)miss / (double)sample_size << endl;
 //   cout << "Miss pending ratio: " << (double)miss_pending / (double)sample_size << endl;
    cout << "Miss pending: " << miss_pending << endl;
    cout << "Total accesses: " << sample_size << endl;
    cout << "Total hits: " << hit << endl;
    cout << "Total misses: " << miss << endl;
    cout << "Total miss pending: " << miss_pending << endl;
    cout << "Write-through: " << write_through << endl;
    cout << "Write-no-allocate: " << write_noallocate << endl;
    cout << "1"<< ((double)hit + (double)miss)/(double)sample_size << endl;
    return 0;
}