# File Organization and Space-Time Trade-off Analysis

## 📌 Overview

This project cleans a large-scale password dataset, converts it into a standard format, and stores it on the disk using three distinct data storage methods: Plain Text (Raw), Hash, and Compressed. The primary goal is to practically examine the "Space-Time Trade-off" concept, which is a fundamental principle in modern databases and file systems.

The project measures and analyzes the effects of different storage formats on disk space utilization, search performance, and CPU/memory load.

## 🚀 Features

* **Efficient Data Preprocessing:** Cleans hidden carriage return (`\r`) characters and empty lines from raw data.


* **Duplicate Removal:** Utilizes the `std::unordered_set` data structure, which provides an $O(1)$ search cost, to ensure the dataset consists of completely unique records.


* **Multiple Storage Implementations:**
* **Raw Storage:** Baseline uncompressed `.bin` file.


* **Hashed Storage:** Uses OpenSSL's `EVP_Digest` to convert passwords into 32-character hexadecimal MD5 hashes.


* **Compressed Storage:** Compresses data into binary format using the `gzopen` and `gzputs` functions from the zlib library.




* **Comprehensive Benchmarking:** Executes a Linear Search ($O(N)$) on 100 random passwords, tracking search times in microseconds, disk sizes in bytes, and measuring RAM consumption via streaming.



## 🛠️ Technologies & Tools

* **Language:** C++


* **Compiler Environment:** MSYS2 (MinGW-w64) with g++ (GCC)


* **Libraries:**
* `Zlib` (`<zlib.h>`): For data compression and decompression.


* `OpenSSL` (`<openssl/evp.h>`): For generating MD5 hashes via the EVP API.


* Standard Libraries: `<chrono>` (time measurement) and `<fstream>` (file I/O).


* Windows API: `<psapi.h>` (RAM tracking).





## 📂 Project Architecture

The project is built with a strictly modular architecture to ensure data integrity and maintainability:

* **`RawData/`**: Contains the raw input data.


* **`Processed/`**: Stores the cleaned, standardized reference data.


* **`Storage/`**: Houses the output files for the Raw, Hashed, and Compressed methods.


* **`Code/`**: Contains the C++ source files:


* `main.cpp`: Manages control flow and triggers performance tests.


* `preprocess.cpp`: Reads raw data, cleans it, and removes duplicates.


* `storage.cpp`: Handles writing data to the disk in all three formats.


* `search.cpp`: Runs benchmark tests on 100 random targets.


* `compression.cpp`: Manages `zlib` read/write operations.


* `utils.cpp`: Helper tools for MD5 calculation, RAM tracking, and file size measurement.





## 📊 Performance Results & Analysis

The program tested 100 random passwords against the three storage methods. During operations, the CPU ran at 100% load on a single core, while RAM usage remained highly efficient at ~8.2 MB due to stream processing.

| Method | Size (Bytes) | Compression Ratio | Avg. Time (µs) | Max Time (µs) | Decomp. Time (µs) |
| --- | --- | --- | --- | --- | --- |
| **Raw** | 881,877 | - | 1609.22 | 3369 | - |
| **Hashed** | 3,399,966 | - | 2594.58 | 5240 | - |
| **Compressed** | 373,167 | 0.42 | 1792.68 | 19,832 | 19,792 |
| Note: Data derived from the project report.

 |  |  |  |  |  |

### 💡 Key Takeaways (The Trade-offs)

* **Space Saving:** The Compressed method reduces data size by 58% (ratio of 0.42), offering the best disk space optimization. Conversely, the Hashed method quadruples the file size due to its fixed 32-character output.


* **Speed:** Raw storage is the fastest (1.6 ms average) as it compares direct text without overhead.


* **The Bottleneck:** Compressed data creates a massive time and CPU bottleneck during searches because the file must first be decompressed (taking ~20 ms alone).


* **Security vs. Speed:** MD5 hashing increases search time due to CPU overhead and higher disk read costs, but it provides robust data security since plain text is never stored.



**Conclusion:**
Use **Hashed** storage if maximum security is required at the cost of disk space. Use **Compressed** storage for archival data where disk space is limited and searches are rare. Use **Raw** storage when search speed is the critical priority, and security is not a concern.

## 🔗 References

* SecLists Password Repository: [danielmiessler/SecLists](https://github.com/danielmiessler/SecLists)

* [C++ Standard Library Documentation](https://cplusplus.com/)

* OpenSSL EVP Library Documentation


* Zlib Compression Algorithm Guide
