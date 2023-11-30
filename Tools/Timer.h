#ifndef SDIZO_TIMER_H
#define SDIZO_TIMER_H

class Timer {
    long long int frequency, start, elapsed;
    long long int read_QPC();
public:
    Timer();

    void run();
    void stop();
    double readS();
    double readMs();
    void printResult();
    double getTimeMs();
};


#endif //SDIZO_TIMER_H
