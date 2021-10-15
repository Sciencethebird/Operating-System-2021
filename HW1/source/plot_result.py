import matplotlib.pyplot as plt
import math
import statistics

result_files = ["main-base-result.txt",
                "main-fork-result.txt",
                "main-thread-mutex-result.txt" ]
tags = [ "single-process", "multi-process", "multi-thread"]

#result_files = ["main-thread-result.txt",
#                "main-thread-mutex-result.txt" ]
#tags = [ "multi-thread", "multi-thread w/ mutex"]

size_results = {}
count_results = {}
time_results = {}
time_error = {}
log_time_results = {}
log_time_error = {}

for file in result_files:
    with open(file, 'r') as f:
        size_results[file] = []
        count_results[file] = []
        time_results[file] = []
        time_error[file] = []
        log_time_results[file] = []
        log_time_error[file] = []

        for lines in f:
            data = lines.split(",")[:-1]
            size = []
            count = [] 
            time = []
            log_time = []
            for i in range(5):
                size.append(int(data[i*3]))
                count.append(int(data[i*3+1]))
                time.append( int(data[i*3+2]) )
                log_time.append( math.log(int(data[i*3+2]), 10) )
            print(size, count, time)
            t_error = statistics.stdev(time)
            t_avg = sum(time) / len(time)
            log_t_error = statistics.stdev(log_time)
            log_t_avg = sum(log_time) / len(log_time)
            size  = sum(size) / len(size)
            count = sum(count) / len(count)
            size_results[file].append(size)
            count_results[file].append(count)
            time_results[file].append(t_avg)
            time_error[file].append(t_error)
            log_time_results[file].append(log_t_avg)
            log_time_error[file].append(log_t_error)
            #time_results[file].append(int(time))

fig, (ax1, ax2) = plt.subplots(1, 2)
for i, file in enumerate(result_files): 
    print(count_results)      
    ax1.plot(size_results["main-fork-result.txt"], count_results[file], label = tags[i], zorder=10)
    #ax1.errorbar(size_results["main-thread-result.txt"], time_results[file], time_error[file], linestyle='None', marker='^')
    log_size = [math.log(x, 10) for x in size_results["main-fork-result.txt"] ]
    log_time = log_time_results[file]
    log_error = log_time_error[file]
    ax2.plot(log_size, log_time, label = tags[i], zorder=10)
    ax2.errorbar(log_size, log_time, log_error, linestyle='None', marker='^')

ax1.ticklabel_format(style='plain')
ax1.set_title(f"Thread Mutex Comparison")
ax1.set(xlabel='Thread Number(n)', ylabel='micro second')
ax1.legend()

ax2.set_title(f"log(time)-log(data_size) comparison")
ax2.set(xlabel='log(n)', ylabel='log(t)')
ax2.legend()

plt.show()
# plt.savefig("data-size-linear.png")
