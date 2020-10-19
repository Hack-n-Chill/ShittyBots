#define _XOPEN_SOURCE
#include "image.h"
#include "http_stream.h"


                char head[400];
                sprintf(head, "--mjpegstream\r\nContent-Type: image/jpeg\r\nContent-Length: %zu\r\n\r\n", outlen);
                _write(s, head, 0);
                int n = _write(s, (char*)(&outbuf[0]), outlen);
                cerr << "known client: " << s << ", sent = " << n << ", must be sent outlen = " << outlen << endl;
                if (n < (int)outlen)
                {
                    cerr << "MJPG_sender: kill client " << s << endl;
                    //::shutdown(s, 2);
                    close_socket(s);
                    FD_CLR(s, &master);
                }
            }
        }
        if (close_all_sockets) {
            int result = close_socket(sock);
            cerr << "MJPG_sender: close acceptor: " << result << " \n\n";
        }
        return true;
    }
};
// ----------------------------------------

static std::mutex mtx_mjpeg;

//struct mat_cv : cv::Mat { int a[0]; };

void send_mjpeg(mat_cv* mat, int port, int timeout, int quality)
{
    try {
        std::lock_guard<std::mutex> lock(mtx_mjpeg);
        static MJPG_sender wri(port, timeout, quality);
        //cv::Mat mat = cv::cvarrToMat(ipl);
        wri.write(*(cv::Mat*)mat);
        std::cout << " MJPEG-stream sent. \n";
    }
    catch (...) {
        cerr << " Error in send_mjpeg() function \n";
    }
}
// ----------------------------------------

std::string get_system_frame_time_string()
{
    std::time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    static std::mutex mtx;
    std::lock_guard<std::mutex> lock(mtx);
    struct tm *tmp_buf = localtime(&t);
    char buff[256];
    std::strftime(buff, 256, "%A %F %T", tmp_buf);
    std::string system_frame_time = buff;
    return system_frame_time;
}
// ----------------------------------------


#ifdef __CYGWIN__
int send_http_post_request(char *http_post_host, int server_port, const char *videosource,
    detection *dets, int nboxes, int classes, char **names, long long int frame_id, int ext_output, int timeout)
{
    std::cerr << " send_http_post_request() isn't implemented \n";
    return 0;
}
#else   //  __CYGWIN__

#ifndef   NI_MAXHOST
#define   NI_MAXHOST 1025
#endif

#ifndef   NI_NUMERICHOST
#define NI_NUMERICHOST  0x02
#endif

//#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"

// https://webhook.site/
// https://github.com/yhirose/cpp-httplib
// sent POST http request
int send_http_post_request(char *http_post_host, int server_port, const char *videosource,
    detection *dets, int nboxes, int classes, char **names, long long int frame_id, int ext_output, int timeout)
{
    const float thresh = 0.005; // function get_network_boxes() has already filtred dets by actual threshold

    std::string message;

    for (int i = 0; i < nboxes; ++i) {
        char labelstr[4096] = { 0 };
        int class_id = -1;
        for (int j = 0; j < classes; ++j) {
            int show = strncmp(names[j], "dont_show", 9);
            if (dets[i].prob[j] > thresh && show) {
                if (class_id < 0) {
                    strcat(labelstr, names[j]);
                    class_id = j;
                    char buff[10];
                    sprintf(buff, " (%2.0f%%)", dets[i].prob[j] * 100);
                    strcat(labelstr, buff);
                }
                else {
                    strcat(labelstr, ", ");
                    strcat(labelstr, names[j]);
                }
                printf("%s: %.0f%% ", names[j], dets[i].prob[j] * 100);
            }
        }
        if (class_id >= 0) {
            message += std::string(names[class_id]) + std::string(", id: ") + std::to_string(class_id) + "\n";
        }
    }

    if (!message.empty())
    {
        std::string time = get_system_frame_time_string();
        message += "\ntime:\n" + time + "\n";
        message += "videosource:\n" + std::string(videosource);

        std::string http_post_host_str = http_post_host;
        int slash_index = http_post_host_str.find("/");

        std::string http_path = http_post_host_str.substr(slash_index, http_post_host_str.length() - slash_index);
        http_post_host_str = http_post_host_str.substr(0, slash_index);

        // send HTTP-Post request
        httplib::Client cli(http_post_host_str.c_str(), server_port, timeout);
        auto res = cli.Post(http_path.c_str(), message, "text/plain");

        return 1;
    }

    return 0;
}
#endif   //  __CYGWIN__

#endif      // OPENCV

// -----------------------------------------------------

#if __cplusplus >= 201103L || _MSC_VER >= 1900  // C++11

#include <chrono>
#include <iostream>

static std::chrono::steady_clock::time_point steady_start, steady_end;
static double total_time;

double get_time_point() {
    std::chrono::steady_clock::time_point current_time = std::chrono::steady_clock::now();
    //uint64_t now = std::chrono::duration_cast<std::chrono::milliseconds>(current_time.time_since_epoch()).count();
    return std::chrono::duration_cast<std::chrono::microseconds>(current_time.time_since_epoch()).count();
}

void start_timer() {
    steady_start = std::chrono::steady_clock::now();
}

void stop_timer() {
    steady_end = std::chrono::steady_clock::now();
}

double get_time() {
    double took_time = std::chrono::duration<double>(steady_end - steady_start).count();
    total_time += took_time;
    return took_time;
}

void stop_timer_and_show() {
    stop_timer();
    std::cout << " " << get_time() * 1000 << " msec" << std::endl;
}

void stop_timer_and_show_name(char *name) {
    stop_timer();
    std::cout << " " << name;
    std::cout << " " << get_time() * 1000 << " msec" << std::endl;
}

void show_total_time() {
    std::cout << " Total: " << total_time * 1000 << " msec" << std::endl;
}


int custom_create_thread(custom_thread_t * tid, const custom_attr_t * attr, void *(*func) (void *), void *arg)
{
    std::thread *ptr = new std::thread(func, arg);
    *tid = (custom_thread_t *)ptr;
    if (tid) return 0;
    else return -1;
}

int custom_join(custom_thread_t tid, void **value_ptr)
{
    std::thread *ptr = (std::thread *)tid;
    if (ptr) {
        ptr->join();
        delete ptr;
        return 0;
    }
    else printf(" Error: ptr of thread is NULL in custom_join() \n");

    return -1;
}

int custom_atomic_load_int(volatile int* obj)
{
    const volatile std::atomic<int>* ptr_a = (const volatile std::atomic<int>*)obj;
    return std::atomic_load(ptr_a);
}

void custom_atomic_store_int(volatile int* obj, int desr)
{
    volatile std::atomic<int>* ptr_a = (volatile std::atomic<int>*)obj;
    std::atomic_store(ptr_a, desr);
}

#if !defined(__MINGW64__)
void this_thread_sleep_for(int ms_time)
{
    std::chrono::milliseconds dura(ms_time);
    std::this_thread::sleep_for(dura);
}
#else
void this_thread_sleep_for(int ms_time)
{
    std::cerr << " this_thread_sleep_for() isn't implemented \n";
    return;
}
#endif

void this_thread_yield()
{
    std::this_thread::yield();
}

#else // C++11
#include <iostream>

double get_time_point() { return 0; }
void start_timer() {}
void stop_timer() {}
double get_time() { return 0; }
void stop_timer_and_show() {
    std::cout << " stop_timer_and_show() isn't implemented " << std::endl;
}
void stop_timer_and_show_name(char *name) { stop_timer_and_show(); }
void total_time() {}
#endif // C++11
