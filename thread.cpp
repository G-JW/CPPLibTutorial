#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <mutex>

using std::cout;
using std::string;
using std::to_string;
using std::flush;
using std::endl;
using std::thread;
using namespace std::this_thread;   //get_id(), sleep_for(), sleep_until(), yield()
using std::mutex;
using std::atomic;

int counter = 0;
atomic<int> counter_atomic = 0;

mutex mutex_cout;
mutex mutex_counter;
mutex mutex_funcC;

void cout_mutex(string content);
void count();
void count_mutex();
void count_atomic();

int main()
{
	cout << "I'm main thread " << get_id() << endl;

	//wait for a instant
	yield();

	//loading animation
	std::chrono::system_clock::time_point until;
	cout << "loading";
	for (int i = 0; i < 3; i++) {
		cout << '.';
		//wait for 1 second
		until = std::chrono::system_clock::now();
		until += std::chrono::seconds(1);
		sleep_until(until);
		//sleep_for(std::chrono::seconds(1));
	}
	cout << endl;

	thread threads[10];
	for (thread &t : threads) {
		t = thread(count);
		//t = thread(count_mutex);
		//t = thread(count_atomic);
		mutex_cout.lock();
		cout << "I'm child thread " << t.get_id() << endl;
		mutex_cout.unlock();
		t.join();
		//t.detach();
	}
	system("pause");
	return 0;
}

void cout_mutex(string content)
{
	mutex_cout.lock();
	cout << content << endl;
	mutex_cout.unlock();
}

void count()
{
	int n = 1000;
	while (n--)
		counter++;
	cout_mutex("counter:" + to_string(counter));
}

void count_mutex()
{
	mutex_counter.lock();
	int n = 1000;
	while (n--)
		counter++;
	cout_mutex("counter:" + to_string(counter));
	mutex_counter.unlock();
}

void count_atomic()
{
	int n = 1000;
	while (n--)
		counter_atomic++;
	cout_mutex("counter:" + to_string(counter));
}