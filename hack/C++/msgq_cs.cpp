
// Interview Coding Exercise
// =========================
// Create a simple client-server app that produces the following
// output:
//
// Client app starting
// Enter server thread (num msgs: 3)
//   msg1:msg1
//   msg2:msg2
//   msg3:msg3
// Leave server thread (num msgs: 0)
// Client app exiting
//
// Requirements:
// 1. Server must be run as a thread.
// 2. Client passes messages to server using a std::queue.
// 3. Client must not exit until after server has processed all queue messages.
// 4. PLEASE KEEP IT SIMPLE!

#include <chrono>
#include <iostream>
#include <queue>
#include <thread>

using namespace std;
using namespace std::chrono_literals;

int main()
{
    std::vector<std::string> msgs = {"msg1", "msg2", "msg3"};
    std::queue<std::string> msg_q;
    bool done = false;

    //// TODO: IMPLEMENT SERVER AS A LAMBDA (RUNS AS A THREAD)
    auto server = [&done](std::queue<std::string> &msg_q) -> void
    // auto server = [](std::queue<std::string> &msg_q) -> void
    {
        cout << "Enter server thread (num msgs: " << msg_q.size() << ")" << std::endl;

        while (msg_q.size())
        {
            auto m = msg_q.front();
            cout << "  " << m << ":" << m << std::endl;
            msg_q.pop();
        }

        cout << "Leave server thread (num msgs: " << msg_q.size() << ")" << std::endl;
        done = true;
    };

    cout << "Client app starting" << std::endl;

    // prime the queue with all messages to be processed
    // by the server
    for (auto msg : msgs)
    {
        msg_q.push(msg);
    }

    // launch a server thread to print each message in duplicate,
    // colon separated (e.g. "msg1:msg1")
    // std::jthread instance(std::jthread([&server, &msg_q]()
    //                                    { server(msg_q); }));
    if (false)
    {
        std::jthread instance([&server, &msg_q]()
                              { server(msg_q); });
        instance.detach();
    }
    else
    {
        // std::jthread instance(&server, &msg_q);
        std::jthread instance([&server](std::queue<std::string> &q)
                              { server(q); }, msg_q);
        instance.detach();
    }

    cout << "Client app running" << std::endl;

    // poll for server thread to set the done flag
    // before exiting
    while (!done)
    {
        std::this_thread::sleep_for(1s);
    }

    cout << "Client app exiting" << std::endl;

    return 0;
}

int main2()
{
    int value = 42;

    std::jthread my_thread([](int val)
                           { std::cout << "Value: " << val << std::endl; }, 2 * value); // Pass 2 * value directly

    my_thread.join();

    return 0;
}