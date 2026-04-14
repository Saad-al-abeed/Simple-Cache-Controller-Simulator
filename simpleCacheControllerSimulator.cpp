// Code written by Saad Al Abeed ID: 230041142
// No claude, no gpt.

#include <bits/stdc++.h>
#include <random>
using namespace std;

inline std::mt19937& getGlobalGenerator() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return gen;
}

class Request {
private:
    char requestType;
    bool miss, dirtyBit;

public:
    // getters
    char getRequestType() { return requestType; }
    bool missed() { return miss; }
    bool isDirty() { return dirtyBit; }

    // setters
    void setRequestType() {
        std::bernoulli_distribution dist(0.8); // 80% write chance
        requestType = dist(getGlobalGenerator()) ? 'W' : 'R';
    } // this function randomly sets the request type to either R as in read or W as in write

    void setDirtyRandomly() {
        std::bernoulli_distribution dist(0.8); // 80% dirty chance
        dirtyBit = dist(getGlobalGenerator());
    } // this function randomly sets the dirty bit to either true or false

    void setMissRandomly() {
        std::bernoulli_distribution dist(0.9); // 90% miss chance
        dirtyBit = dist(getGlobalGenerator());
    } // this function randomly sets cache miss to either true or false

    //constructor
    Request() {
        setRequestType();

        if (requestType == 'W') setMissRandomly();
        else miss = false;

        if (miss) setDirtyRandomly();
        else dirtyBit = false;
    }
};

bool memoryReadiness() {
    std::bernoulli_distribution dist(0.2); // 20% memory ready chance
    return dist(getGlobalGenerator());
}

int randomNumberGenerator() {
    std::uniform_int_distribution<> dis(1, 10);
    return dis(getGlobalGenerator());
} // This is gonna generate a random number from 1 to 10

void simulation(Request r) {
    cout << "\n========================================\n";
    string stage = "Idle";
    cout << "[Stage: " << stage << "] Processing request: Type '" << r.getRequestType() << "'" << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(600));

    stage = "CompareTag";
    cout << "[Stage: " << stage << "] Checking cache" << std::flush;

    for(int i = 0; i < 3; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        cout << "." << std::flush;
    }
    cout << endl;

    if (r.getRequestType() == 'R') {
        cout << "  -> CACHE HIT! Data read successfully." << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return;
    }

    if (r.getRequestType() == 'W' && r.missed() == false) {
        cout << "  -> CACHE HIT! Data written successfully." << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return;
    }
    else {
        cout << "  -> CACHE MISS!" << endl;
        bool isMemoryReady = memoryReadiness();
        std::this_thread::sleep_for(std::chrono::milliseconds(600));

        if (r.isDirty()) {
            stage = "Write Back";
            cout << "[Stage: " << stage << "] Data is DIRTY. Evicting line..." << endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(600));

            YO:
            if (isMemoryReady) {
                cout << "  -> Memory Ready!" << endl;
                stage = "Allocate";
                cout << "[Stage: " << stage << "] Proceeding to allocation..." << endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(800));
                isMemoryReady = memoryReadiness();
                goto WOW;
            }
            else {
                int waitTime = randomNumberGenerator();
                cout << "[Stage: " << stage << "] Memory not ready. Waiting " << waitTime << " cycles" << std::flush;
                for(int i = 0; i < waitTime; i++) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(waitTime * 100));
                    cout << "." << std::flush;
                }
                cout << endl;
                isMemoryReady = true;
                goto YO;
            }
        }
        else {
            stage = "Allocate";
            cout << "[Stage: " << stage << "] Data is CLEAN. Allocating..." << endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(600));

            WOW:
            if (isMemoryReady) {
                cout << "  -> Memory Ready!" << endl;
                stage = "CompareTag";
                cout << "[Stage: " << stage << "] Re-evaluating tag..." << endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(800));
                cout << "  -> Data written successfully." << endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                return;
            }
            else {
                int waitTime = randomNumberGenerator();
                cout << "[Stage: " << stage << "] Memory not ready. Waiting " << waitTime << " cycles" << std::flush;
                for(int i = 0; i < waitTime; i++) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(waitTime * 100));
                    cout << "." << std::flush;
                }
                cout << endl;
                isMemoryReady = true;
                goto WOW;
            }
        }
    }
}


int main() {
    START:
    cout << "Enter the number of random requests you want to simulate: ";
    int n;
    cin >> n;
    if (n <= 0) {
        cout << "Please provide a positive input";
        goto START;
    }

    vector<Request> requests; // Initializing the requests array
    for (int i=0; i<n; i++) {
        Request r;
        requests.push_back(r);
    }

    cout << "Starting the Simulator..." << endl;

    for (Request r:requests) {
        simulation(r);
        cout << "Back to Idle" << endl;
    }

    cout << "...Simulation finished" << endl;
}
