FROM debian:sid

RUN apt-get update
RUN apt-get install -y clang g++ libc++-dev libc++abi-dev

WORKDIR /root
ADD testcase.cpp .

RUN clang++ -g -std=c++20 -o testcase.clang testcase.cpp
RUN g++ -g -std=c++20 -o testcase.gnu testcase.cpp
RUN clang++ -g -std=c++20 -stdlib=libc++ -o testcase.clang.libcxx testcase.cpp
